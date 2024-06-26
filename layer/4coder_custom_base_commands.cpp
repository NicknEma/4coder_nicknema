#ifndef FCODER_CUSTOM_BASE_COMMANDS_CPP
#define FCODER_CUSTOM_BASE_COMMANDS_CPP

// This file implements some of the custom layer's commands. They will be listed in the command lister (by default opened with Alt + X) and they can be bound to a key, either in code or via the bindings.4coder file. Some of the commands are not in this file, but in places closer to related functionality. The startup command is in entry.cpp, and the bindings-related commands are in bindings.cpp

// The file contains commands for:
// - Searching for strings
// - Jumping to identifier definitions
// - Moving the cursor in different ways
// - Auto-indenting and auto-completing
// - Commenting and uncommenting ranges
// - Opening files
// - Counting lines of code

// @Todo(ema): Add
// - Switch between naming styles (camelCase, PascalCase, snake_case, Pascal_Snake_Case, UPPER_SNAKE_CASE)

//~ Misc commands.

// TODO(rjf): Remove once Allen adds official version.
CUSTOM_COMMAND_SIG(f4_leave_event_unhandled)
CUSTOM_DOC("when bound to keystroke, ensures the event falls through to text insertion") {
    leave_current_input_unhandled(app);
}

// In battery saving mode, the cursor isn't animated. The global_battery_saver variable is in ubiquitous.h
CUSTOM_COMMAND_SIG(toggle_battery_saver)
CUSTOM_DOC("Toggles battery saving mode.") {
	global_battery_saver = !global_battery_saver;
}

CUSTOM_COMMAND_SIG(toggle_compilation_expand)
CUSTOM_DOC("Expands or minimizes the compilation window.") {
	// 'global_compilation_view' and 'global_compilation_view_expanded' are defined in ubiquitous.h
	// @Cleanup: What happens if we move them here?
	
	Buffer_ID     buffer = view_get_buffer(app, global_compilation_view, Access_Always);
    Face_ID      face_id = get_face_id(app, buffer);
    Face_Metrics metrics = get_face_metrics(app, face_id);
    if (global_compilation_view_expanded ^= 1) { // @Cleanup: AHA! Assignment statement in expression! Why wasn't this detected by the compiler?
        view_set_split_pixel_size(app, global_compilation_view, cast(i32)(metrics.line_height*32.f));
    } else {
        view_set_split_pixel_size(app, global_compilation_view, cast(i32)(metrics.line_height*4.f));
    }
}

//~ Moving the cursor

NAMESPACE_BEGIN(nne)

function i64 F4_Boundary_TokenAndWhitespace(Application_Links *app, Buffer_ID buffer, 
											Side side, Scan_Direction direction, i64 pos)
{
	using namespace nne;
	
    i64 result = boundary_non_whitespace(app, buffer, side, direction, pos);
    Token_Array tokens = get_token_array_from_buffer(app, buffer);
    if (tokens.tokens != 0){
        switch (direction){
            case Scan_Forward:
            {
                i64 buffer_size = buffer_get_size(app, buffer);
                result = buffer_size;
                if(tokens.count > 0)
                {
                    Token_Iterator_Array it = token_iterator_pos(0, &tokens, pos);
                    Token *token = token_it_read(&it);
                    
                    if(token == 0)
                    {
                        break;
                    }
                    
                    // NOTE(rjf): Comments/Strings
                    if(token->kind == TokenBaseKind_Comment ||
                       token->kind == TokenBaseKind_LiteralString)
                    {
                        result = boundary_non_whitespace(app, buffer, side, direction, pos);
                        break;
                    }
                    
                    // NOTE(rjf): All other cases.
                    else
                    {
                        if (token->kind == TokenBaseKind_Whitespace)
                        {
                            // token_it_inc_non_whitespace(&it);
                            // token = token_it_read(&it);
                        }
                        
                        if (side == Side_Max){
                            result = token->pos + token->size;
                            
                            token_it_inc_all(&it);
                            Token *ws = token_it_read(&it);
                            if(ws != 0 && ws->kind == TokenBaseKind_Whitespace &&
                               get_line_number_from_pos(app, buffer, ws->pos + ws->size) ==
                               get_line_number_from_pos(app, buffer, token->pos))
                            {
                                result = ws->pos + ws->size;
                            }
                        }
                        else{
                            if (token->pos <= pos){
                                token_it_inc_non_whitespace(&it);
                                token = token_it_read(&it);
                            }
                            if (token != 0){
                                result = token->pos;
                            }
                        }
                    }
                    
                }
            }break;
            
            case Scan_Backward:
            {
                result = 0;
                if (tokens.count > 0){
                    Token_Iterator_Array it = token_iterator_pos(0, &tokens, pos);
                    Token *token = token_it_read(&it);
                    
                    Token_Iterator_Array it2 = it;
                    token_it_dec_non_whitespace(&it2);
                    Token *token2 = token_it_read(&it2);
                    
                    // NOTE(rjf): Comments/Strings
                    if(token->kind == TokenBaseKind_Comment ||
                       token->kind == TokenBaseKind_LiteralString ||
                       (token2 && 
                        token2->kind == TokenBaseKind_Comment ||
                        token2->kind == TokenBaseKind_LiteralString))
                    {
                        result = boundary_non_whitespace(app, buffer, side, direction, pos);
                        break;
                    }
                    
                    if (token->kind == TokenBaseKind_Whitespace){
                        token_it_dec_non_whitespace(&it);
                        token = token_it_read(&it);
                    }
                    if (token != 0){
                        if (side == Side_Min){
                            if (token->pos >= pos){
                                token_it_dec_non_whitespace(&it);
                                token = token_it_read(&it);
                            }
                            result = token->pos;
                        }
                        else{
                            if (token->pos + token->size >= pos){
                                token_it_dec_non_whitespace(&it);
                                token = token_it_read(&it);
                            }
                            result = token->pos + token->size;
                        }
                    }
                }
            }break;
        }
    }
    return(result);
}

// TODO(rjf): Replace with the final one from Jack's layer.
function i64 F4_Boundary_CursorTokenOrBlankLine_TEST(Application_Links *app, Buffer_ID buffer, 
													 Side side, Scan_Direction direction, i64 pos)
{
	using namespace nne;
	
    Scratch_Block scratch(app);
    
    Range_i64_Array scopes = get_enclosure_ranges(app, scratch, buffer, pos, FindNest_Scope);
    // NOTE(jack): The outermost scope
    Range_i64 outer_scope = scopes.ranges[scopes.count - 1];
    
    // NOTE(jack): As we are issuing a move command here I will assume that buffer is the active buffer.
    View_ID view = get_active_view(app, Access_Always);
    i64 active_cursor_pos = view_get_cursor_pos(app, view);
    Token_Array tokens = get_token_array_from_buffer(app, buffer);
    Token_Iterator_Array active_cursor_it = token_iterator_pos(0, &tokens, active_cursor_pos);
    Token *active_cursor_token = token_it_read(&active_cursor_it);
    
    String_Const_u8 cursor_string = push_buffer_range(app, scratch, buffer, Ii64(active_cursor_token));
    i64 cursor_offset = pos - active_cursor_token->pos;
    
    // NOTE(jack): If the cursor token is not an identifier, we will move to empty lines
    i64 result = get_pos_of_blank_line_grouped(app, buffer, direction, pos);
    result = view_get_character_legal_pos_from_pos(app, view, result);
    if (tokens.tokens != 0)
    {
        // NOTE(jack): if the the cursor token is an identifier, and we are inside of a scope
        // perform the cursor occurance movement.
        if (active_cursor_token->kind == TokenBaseKind_Identifier && !(scopes.count == 0))
        {
            // NOTE(jack): Reset result to prevent token movement to escape to blank line movement
            // when you are on the first/last token in the outermost scope.
            result = pos;
            Token_Iterator_Array it = token_iterator_pos(0, &tokens, pos);
            
            for (;;)
            {
                b32 done = false;
                // NOTE(jack): Incremenet first so we dont move to the same cursor that the cursor is on.
                switch (direction)
                {
                    // NOTE(jack): I am using it.ptr->pos because its easier than reading the token with
                    // token_it_read
                    case Scan_Forward:
                    {
                        if (!token_it_inc_non_whitespace(&it) || it.ptr->pos >= outer_scope.end) {
                            done = true;
                        }
                    } break;
                    
                    case Scan_Backward:
                    {
                        if (!token_it_dec_non_whitespace(&it) || it.ptr->pos < outer_scope.start) {
                            done = true;
                        }
                    } break;
                }
                
                if (!done) 
                {
                    Token *token = token_it_read(&it);
                    String_Const_u8 token_string = push_buffer_range(app, scratch, buffer, Ii64(token));
                    if (string_match(cursor_string, token_string)) {
                        result = token->pos + cursor_offset;
                        break;
                    }
                }
                else 
                {
                    break;
                }
            }
        }
    }
    
    return result ;
}

NAMESPACE_END()

CUSTOM_COMMAND_SIG(move_left_if_no_selection)
CUSTOM_DOC("Moves the cursor one character to the left. If the mode is set to notepad-like and something is selected, just unselect the text instead.") {
	Scratch_Block scratch(app);
	
    Input_Modifier_Set mods = system_get_keyboard_modifiers(scratch);
    View_ID            view = get_active_view(app, Access_ReadVisible);
    
	if (fcoder_mode != FCoderMode_NotepadLike || view_get_cursor_pos(app, view) == view_get_mark_pos(app, view) || has_modifier(&mods, KeyCode_Shift)) {
        view_set_cursor_by_character_delta(app, view, -1);
    }
	
    no_mark_snap_to_cursor_if_shift(app, view);
}

CUSTOM_COMMAND_SIG(move_right_if_no_selection)
CUSTOM_DOC("Moves the cursor one character to the right. If the mode is set to notepad-like and something is selected, just unselect the text instead.") {
    Scratch_Block scratch(app);
	
    Input_Modifier_Set mods = system_get_keyboard_modifiers(scratch);
    View_ID            view = get_active_view(app, Access_ReadVisible);
	
    if (fcoder_mode != FCoderMode_NotepadLike || view_get_cursor_pos(app, view) == view_get_mark_pos(app, view) || has_modifier(&mods, KeyCode_Shift)) {
        view_set_cursor_by_character_delta(app, view, +1);
    }
    
	no_mark_snap_to_cursor_if_shift(app, view);
}

#if 0
// These are never used... @Unused.
CUSTOM_COMMAND_SIG(f4_move_previous_token_occurrence)
CUSTOM_DOC("Moves the cursor to the previous occurrence of the token that the cursor is over.") {
    Scratch_Block scratch(app);
    current_view_scan_move(app, Scan_Backward, push_boundary_list(scratch, nne::F4_Boundary_CursorTokenOrBlankLine_TEST));
}

CUSTOM_COMMAND_SIG(f4_move_next_token_occurrence)
CUSTOM_DOC("Moves the cursor to the next occurrence of the token that the cursor is over.") {
    Scratch_Block scratch(app);
    current_view_scan_move(app, Scan_Forward, push_boundary_list(scratch, nne::F4_Boundary_CursorTokenOrBlankLine_TEST));
}
#endif

#if 0
// @Note: These already exist in base 4coder, but they call 'boundary_token'.
// What's the difference between 4coder's 'boundary_token' and 'F4_Boundary_TokenAndWhitespace'?
CUSTOM_COMMAND_SIG(f4_move_right_token_boundary)
CUSTOM_DOC("Seek right for boundary between alphanumeric characters and non-alphanumeric characters.") {
    Scratch_Block scratch(app);
    current_view_scan_move(app, Scan_Forward, push_boundary_list(scratch, nne::F4_Boundary_TokenAndWhitespace));
}

CUSTOM_COMMAND_SIG(f4_move_left_token_boundary)
CUSTOM_DOC("Seek left for boundary between alphanumeric characters and non-alphanumeric characters.") {
    Scratch_Block scratch(app);
    current_view_scan_move(app, Scan_Backward, push_boundary_list(scratch, nne::F4_Boundary_TokenAndWhitespace));
}
#endif

//- Deleting stuff

CUSTOM_COMMAND_SIG(backspace_token_boundary)
CUSTOM_DOC("Deletes left to a token boundary.") {
    Scratch_Block scratch(app);
    current_view_boundary_delete(app, Scan_Backward, push_boundary_list(scratch, nne::F4_Boundary_TokenAndWhitespace));
}

CUSTOM_COMMAND_SIG(delete_token_boundary)
CUSTOM_DOC("Deletes right to a token boundary.") {
    Scratch_Block scratch(app);
    current_view_boundary_delete(app, Scan_Forward, push_boundary_list(scratch, nne::F4_Boundary_TokenAndWhitespace));
}

CUSTOM_COMMAND_SIG(backspace_alpha_numeric_or_camel_boundary)
CUSTOM_DOC("Deletes left to a alphanumeric or camel boundary.") {
    Scratch_Block scratch(app);
    current_view_boundary_delete(app, Scan_Backward, push_boundary_list(scratch, boundary_alpha_numeric, boundary_alpha_numeric_camel));
}

CUSTOM_COMMAND_SIG(delete_alpha_numeric_or_camel_boundary)
CUSTOM_DOC("Deletes right to an alphanumeric or camel boundary.") {
    Scratch_Block scratch(app);
    current_view_boundary_delete(app, Scan_Forward, push_boundary_list(scratch, boundary_alpha_numeric, boundary_alpha_numeric_camel));
}

//- Alternative movement keys

// @Note(ema): The difference between this and the 4coder default one is that this actually goes to the beginning of the line.
// Why does one check if view exists and the other one just rolls with it?
CUSTOM_COMMAND_SIG(f4_home)
CUSTOM_DOC("Goes to the beginning of the line.") {
	seek_pos_of_visual_line(app, Side_Min);
    View_ID view = get_active_view(app, Access_ReadWriteVisible);
    Buffer_Scroll scroll = view_get_buffer_scroll(app, view);
    scroll.target.pixel_shift.x = 0;
    view_set_buffer_scroll(app, view, scroll, SetBufferScroll_NoCursorChange);
}

CUSTOM_COMMAND_SIG(f4_home_first_non_whitespace)
CUSTOM_DOC("Goes to the beginning of the line.") {
    using namespace nne;
	
	View_ID view = get_active_view(app, Access_Read);
    Buffer_ID buffer = view_get_buffer(app, view, Access_Read);
    if (view && buffer) {
        i64 start_pos = view_get_cursor_pos(app, view);
        seek_pos_of_visual_line(app, Side_Min);
        i64 end_pos = view_get_cursor_pos(app, view);
        i64 line = get_line_number_from_pos(app, buffer, start_pos);
        
        // NOTE(rjf): If we are on the first column, go to the first non-whitespace
        // in the line.
        if (start_pos == end_pos && start_pos == get_line_start_pos(app, buffer, line)) {
            Scratch_Block scratch(app);
            String_Const_u8 string = push_buffer_line(app, scratch, buffer, line);
            for (u64 i = 0; i < string.size; i += 1) {
                if (!character_is_whitespace(string.str[i])) {
                    view_set_cursor_by_character_delta(app, view, (i64)i);
                    break;
                }
            }
        }
        
        // NOTE(rjf): If we hit any non-whitespace, move to the first possible
        // non-whitespace instead of the front of the line entirely.
        else  {
            Scratch_Block scratch(app);
            String_Const_u8 string = push_buffer_range(app, scratch, buffer, Ii64(start_pos, end_pos));
            
            b32 skipped_non_whitespace = 0;
            {
                for (i64 i = string.size-1; i >= 0; i -= 1) {
                    if (!character_is_whitespace(string.str[i])) {
                        skipped_non_whitespace = 1;
                        break;
                    }
                }
            }
            
            if (skipped_non_whitespace) {
                for (i64 i = 0; i < cast(i64)string.size; i += 1) {
                    if (!character_is_whitespace(string.str[i])) {
                        view_set_cursor_by_character_delta(app, view, i);
                        break;
                    }
                }
            }
        }
        
        // NOTE(rjf): Scroll all the way left.
        {
            Buffer_Scroll scroll = view_get_buffer_scroll(app, view);
            scroll.target.pixel_shift.x = 0;
            view_set_buffer_scroll(app, view, scroll, SetBufferScroll_NoCursorChange);
        }
    }
}

//~ Searching

namespace nne {
	
	function void search_current_buffer(Application_Links *app, Scan_Direction dir) {
		Scratch_Block scratch(app);
		
		View_ID   view   = get_active_view(app, Access_Read);
		Buffer_ID buffer = view_get_buffer(app, view, Access_Read);
		if (view && buffer) {
			i64 cursor      = view_get_cursor_pos(app, view);
			i64 mark        = view_get_mark_pos(app, view);
			i64 cursor_line = get_line_number_from_pos(app, buffer, cursor);
			i64 mark_line   = get_line_number_from_pos(app, buffer, mark);
			String_Const_u8 query_init = (fcoder_mode != FCoderMode_NotepadLike || cursor == mark || cursor_line != mark_line) ? SCu8() : push_buffer_range(app, scratch, buffer, Ii64(cursor, mark));
			isearch(app, dir, cursor, query_init);
		}
	}
	
}

CUSTOM_COMMAND_SIG(search__prioritize_highlighted)
CUSTOM_DOC("Searches the current buffer forward. If something is highlighted, it will fill search query with it.") {
    nne::search_current_buffer(app, Scan_Forward);
}

CUSTOM_COMMAND_SIG(reverse_search__prioritize_highlighted)
CUSTOM_DOC("Searches the current buffer backwards. If something is highlighted, it will fill search query with it.") {
    nne::search_current_buffer(app, Scan_Backward);
}

//~ Writing text

// @Note(ema): The point of this is explained in notes.h; it's just for enabling power mode.
CUSTOM_COMMAND_SIG(f4_write_text_input)
CUSTOM_DOC("Inserts whatever text was used to trigger this command.") {
    write_text_input(app);
	
#if 0
    nne::F4_PowerMode_CharacterPressed();
    User_Input      in     = get_current_input(app);
    String_Const_u8 insert = to_writable(&in);
    nne::F4_PowerMode_Spawn(app, get_active_view(app, Access_ReadWriteVisible), insert.str ? insert.str[0] : 0);
#endif
}

CUSTOM_COMMAND_SIG(f4_write_text_and_auto_indent)
CUSTOM_DOC("Inserts text and auto-indents the line on which the cursor sits if any of the text contains 'layout punctuation' such as ;:{}()[]# and new lines.") {
    custom__write_text_and_auto_indent(app);
	
#if 0
    nne::F4_PowerMode_CharacterPressed();
    User_Input      in     = get_current_input(app);
    String_Const_u8 insert = to_writable(&in);
    nne::F4_PowerMode_Spawn(app, get_active_view(app, Access_ReadWriteVisible), insert.str ? insert.str[0] : 0);
#endif
}

// These two are useful for who doesn't have them on the keyboard (like me UwU)
CUSTOM_COMMAND_SIG(write_backtick)
CUSTOM_DOC("Inserts a ` at the cursor.") {
	write_string(app, string_u8_litexpr("`"));
}

CUSTOM_COMMAND_SIG(write_tilde)
CUSTOM_DOC("Inserts a ~ at the cursor.") {
	write_string(app, string_u8_litexpr("~"));
}

//~ Jumping to definitions

NAMESPACE_BEGIN(nne)

internal void F4_GoToDefinition(Application_Links *app, Index__Note *note, b32 same_panel) {
    if (note != 0 && note->file != 0) {
        View_ID view = get_active_view(app, Access_Always);
        Rect_f32 region = view_get_buffer_region(app, view);
        f32 view_height = rect_height(region);
        Buffer_ID buffer = note->file->buffer;
        if (!same_panel) {
            view = get_next_view_looped_primary_panels(app, view, Access_Always);
        }
        point_stack_push_view_cursor(app, view);
        view_set_buffer(app, view, buffer, 0);
        i64 line_number = get_line_number_from_pos(app, buffer, note->range.min);
        Buffer_Scroll scroll = view_get_buffer_scroll(app, view);
        scroll.position.line_number = line_number;
        scroll.target.line_number = line_number;
        scroll.position.pixel_shift.y = scroll.target.pixel_shift.y = -view_height*0.5f;
        view_set_buffer_scroll(app, view, scroll, SetBufferScroll_SnapCursorIntoView);
        view_set_cursor(app, view, seek_pos(note->range.min));
        view_set_mark(app, view, seek_pos(note->range.min));
    }
}

internal Index__Note *F4_FindMostIntuitiveNoteInDuplicateChain(Index__Note *note, Buffer_ID cursor_buffer, i64 cursor_pos) {
    using namespace nne;
	
	Index__Note *result = note;
    if (note != 0) {
        Index__Note *best_note_based_on_cursor = 0;
        for (Index__Note *candidate = note; candidate; candidate = candidate->next) {
            Index__File *file = candidate->file;
            if (file != 0) {
                if (cursor_buffer == file->buffer &&
					candidate->range.min <= cursor_pos && cursor_pos <= candidate->range.max) {
                    if (candidate->next) {
                        best_note_based_on_cursor = candidate->next;
                        break;
                    } else {
                        best_note_based_on_cursor = note;
                        break;
                    }
                }
            }
        }
        
        if (best_note_based_on_cursor) {
            result = best_note_based_on_cursor;
        } else if (note->flags & Index__Note_Flag_Prototype) {
            for (Index__Note *candidate = note; candidate; candidate = candidate->next) {
                if (!(candidate->flags & Index__Note_Flag_Prototype)) {
                    result = candidate;
                    break;
                }
            }
        }
    }
    return result;
}

NAMESPACE_END()

CUSTOM_COMMAND_SIG(f4_go_to_definition)
CUSTOM_DOC("Goes to the definition of the identifier under the cursor.") {
	using namespace nne;
	
    View_ID view = get_active_view(app, Access_Always);
    Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
    Scratch_Block scratch(app);
    String_Const_u8 string = push_token_or_word_under_active_cursor(app, scratch);
    Index__Note *note = index__lookup_note(string);
    note = F4_FindMostIntuitiveNoteInDuplicateChain(note, buffer, view_get_cursor_pos(app, view));
    F4_GoToDefinition(app, note, 0);
}

CUSTOM_COMMAND_SIG(f4_go_to_definition_same_panel)
CUSTOM_DOC("Goes to the definition of the identifier under the cursor in the same panel.") {
	using namespace nne;
	
    View_ID view = get_active_view(app, Access_Always);
    Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
    Scratch_Block scratch(app);
    String_Const_u8 string = push_token_or_word_under_active_cursor(app, scratch);
    Index__Note *note = index__lookup_note(string);
    note = F4_FindMostIntuitiveNoteInDuplicateChain(note, buffer, view_get_cursor_pos(app, view));
    F4_GoToDefinition(app, note, 1);
}

//~ Listing definitions

NAMESPACE_BEGIN(nne)

internal void _F4_PushListerOptionForNote(Application_Links *app, Arena *arena, Lister *lister, Index__Note *note) {
	using namespace nne;
	
    if (note && note->file) {
        Index__File *file = note->file;
        Buffer_ID buffer = file->buffer;
        
        Tiny_Jump *jump = push_array(arena, Tiny_Jump, 1);
        jump->buffer = buffer;
        jump->pos = note->range.first;
        
        String_Const_u8 buffer_name = push_buffer_unique_name(app, arena, buffer);
        String_Const_u8 name = push_stringf(arena, "[%.*s] %.*s", string_expand(buffer_name), string_expand(note->string));
        String_Const_u8 sort = S8Lit("");
        switch (note->kind) {
            case Index__Note_Kind_Type: {
                sort = push_stringf(arena, "type [%s] [%s]",
                                    note->flags & Index__Note_Flag_Prototype ? "prototype" : "def",
                                    note->flags & Index__Note_Flag_Sum_Type ? "sum" : "product");
            } break;
            
            case Index__Note_Kind_Function: {
                sort = push_stringf(arena, "function [%s]", note->flags & Index__Note_Flag_Prototype ? "prototype" : "def");
            } break;
            
            case Index__Note_Kind_Macro: {
                sort = S8Lit("macro");
            } break;
            
            case Index__Note_Kind_Constant: {
                sort = S8Lit("constant");
            } break;
            
            case Index__Note_Kind_Comment_Tag: {
                sort = S8Lit("comment tag");
            } break;
            
            case Index__Note_Kind_Comment_ToDo: {
                sort = S8Lit("TODO");
            } break;
            
            default: break;
        }
        
		lister_add_item(lister, name, sort, jump, 0);
    }
}

internal void F4_JumpToLocation(Application_Links *app, View_ID view, Buffer_ID buffer, i64 pos) {
	using namespace nne;
	
    // NOTE(rjf): This function was ripped from 4coder's jump_to_location. It was copied
    // and modified so that jumping to a location didn't cause a selection in notepad-like
    // mode.
    
    view_set_active(app, view);
    Buffer_Seek seek = seek_pos(pos);
    set_view_to_location(app, view, buffer, seek);
    
    if (auto_center_after_jumps) {
        center_view(app);
    }
	
    view_set_cursor(app, view, seek);
    view_set_mark(app, view, seek);
}

NAMESPACE_END()

CUSTOM_UI_COMMAND_SIG(f4_search_for_definition__project_wide)
CUSTOM_DOC("List all definitions in the index and jump to the one selected by the user.") {
	using namespace nne;
	
    char *query = "Index (Project):";
    
    Scratch_Block scratch(app);
    Lister_Block lister(app, scratch);
    lister_set_query(lister, query);
    lister_set_default_handlers(lister);
    
    index__lock();
    {
        for (Buffer_ID buffer = get_buffer_next(app, 0, Access_Always); buffer != 0; buffer = get_buffer_next(app, buffer, Access_Always)) {
            Index__File *file = index__lookup_file(app, buffer);
            if (file != 0) {
                for (Index__Note *note = file->first_note; note; note = note->next_sibling) {
                    _F4_PushListerOptionForNote(app, scratch, lister, note);
                }
            }
        }
    }
    index__unlock();
    
    Lister_Result l_result = run_lister(app, lister);
    Tiny_Jump result = {};
    if (!l_result.canceled && l_result.user_data != 0){
        block_copy_struct(&result, (Tiny_Jump*)l_result.user_data);
    }
    
    if (result.buffer != 0) {
        View_ID view = get_this_ctx_view(app, Access_Always);
        point_stack_push_view_cursor(app, view);
        F4_JumpToLocation(app, view, result.buffer, result.pos);
    }
}

CUSTOM_UI_COMMAND_SIG(f4_search_for_definition__current_file)
CUSTOM_DOC("List all definitions in the current file and jump to the one selected by the user.") {
	using namespace nne;
	
    char *query = "Index (File):";
    
    View_ID view = get_active_view(app, Access_Always);
    Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
    
    Scratch_Block scratch(app);
    Lister_Block lister(app, scratch);
    lister_set_query(lister, query);
    lister_set_default_handlers(lister);
    
    index__lock();
    {
        Index__File *file = index__lookup_file(app, buffer);
        if (file != 0) {
            for (Index__Note *note = file->first_note; note; note = note->next_sibling) {
                _F4_PushListerOptionForNote(app, scratch, lister, note);
            }
        }
    }
    index__unlock();
    
    Lister_Result l_result = run_lister(app, lister);
    Tiny_Jump result = {};
    if (!l_result.canceled && l_result.user_data != 0) {
        block_copy_struct(&result, (Tiny_Jump*)l_result.user_data);
    }
    
    if (result.buffer != 0) {
        View_ID view_id = get_this_ctx_view(app, Access_Always);
        point_stack_push_view_cursor(app, view_id);
        F4_JumpToLocation(app, view_id, result.buffer, result.pos);
    }
}

#if 0
// @Note(ema): Figure out if this is udeful. Maybe @Rename(ema) to toggle_parenthetical_side? Or either way find a better name.
CUSTOM_COMMAND_SIG(f4_toggle_enclosure_side)
CUSTOM_DOC("Moves the cursor between the open/close brace/paren/bracket of the closest enclosure.") {
	using namespace nne;
	
    View_ID view = get_active_view(app, Access_Always);
    Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
    i64 pos = view_get_cursor_pos(app, view);
    
    // NOTE(rjf): Adjust position if it's on the start or end of an enclosure.
    {
        Token_Array tokens = get_token_array_from_buffer(app, buffer);
        
        Token_Iterator_Array it = token_iterator_pos(0, &tokens, pos);
        Token *token = token_it_read(&it);
        if (token) {
            if (token->kind == TokenBaseKind_ScopeOpen ||
				token->kind == TokenBaseKind_ParentheticalOpen) {
                pos += 1;
                goto end;
            }
        }
        
        token_it_dec_all(&it);
        token = token_it_read(&it);
        if (token) {
            if (token->kind == TokenBaseKind_ScopeClose ||
				token->kind == TokenBaseKind_ParentheticalClose) {
                pos -= 1;
                goto end;
            }
        }
        
        end:;
    }
    
    Scratch_Block scratch(app);
    Range_i64_Array ranges = get_enclosure_ranges(app, scratch, buffer, pos,
                                                  FindNest_Scope | FindNest_Paren);
    if (ranges.count > 0) {
        Range_i64 nearest_range = ranges.ranges[0];
        if (pos == nearest_range.min+1) {
            pos = nearest_range.max;
        } else {
            pos = nearest_range.min;
        }
        view_set_cursor(app, view, seek_pos(pos));
        no_mark_snap_to_cursor_if_shift(app, view);
    }
}
#endif

//~ Working with projects

CUSTOM_UI_COMMAND_SIG(f4_open_project)
CUSTOM_DOC("Open a project by navigating to the project file.") {
	using namespace nne;
	
    for (;;) {
        Scratch_Block scratch(app);
        View_ID view = get_this_ctx_view(app, Access_Always);
        File_Name_Result result = get_file_name_from_user(app, scratch, "Open Project:", view);
        if (result.canceled) break;
        
        String_Const_u8 file_name = result.file_name_activated;
        if (file_name.size == 0) {
            file_name = result.file_name_in_text_field;
        }
        if (file_name.size == 0) break;
        
        String_Const_u8 path = result.path_in_text_field;
        String_Const_u8 full_file_name = push_u8_stringf(scratch, "%.*s/%.*s",
                                                         string_expand(path), string_expand(file_name));
        
        if (result.is_folder) {
            set_hot_directory(app, full_file_name);
            continue;
        }
        
        if (character_is_slash(file_name.str[file_name.size - 1])) {
            File_Attributes attribs = system_quick_file_attributes(scratch, full_file_name);
            if (HasFlag(attribs.flags, FileAttribute_IsDirectory)){
                set_hot_directory(app, full_file_name);
                continue;
            }
            if (string_looks_like_drive_letter(file_name)){
                set_hot_directory(app, file_name);
                continue;
            }
            if (query_create_folder(app, file_name)){
                set_hot_directory(app, full_file_name);
                continue;
            }
            break;
        }
        
        set_hot_directory(app, full_file_name);
        load_project(app);
        break;
    }
}

// @Todo(ema): Make another one of these. Preserve the original one in case somebody wants to use the r4 version.
CUSTOM_COMMAND_SIG(f4_setup_new_project)
CUSTOM_DOC("Sets up a blank 4coder project provided some user folder.") {
	using namespace nne;
	
    Scratch_Block scratch(app);
    Query_Bar_Group bar_group(app);
    
    // NOTE(rjf): Query user for project folder.
    u8 project_folder_absolute[1024];
    {
        Query_Bar path_bar = {};
        path_bar.prompt = string_u8_litexpr("Absolute Path To Project Folder: ");
        path_bar.string = SCu8(project_folder_absolute, (u64)0);
        path_bar.string_capacity = sizeof(project_folder_absolute);
        if (query_user_string(app, &path_bar)) {
            String_Const_u8 full_file_name = push_u8_stringf(scratch, "%.*s/",
                                                             string_expand(path_bar.string));
            set_hot_directory(app, full_file_name);
            
            String_Const_u8 project_file_path = push_u8_stringf(scratch, "%.*s/project.4coder", string_expand(path_bar.string));
            FILE *file = fopen((char *)project_file_path.str, "wb");
            if (file) {
                
                char *string = R"PROJ(version(1);
                  
                  project_name = "New Project";
                  
                  patterns =
                  {
                      "*.c",
                      "*.cpp",
                      "*.jai",
                      "*.odin",
                      "*.zig",
                      "*.h",
                      "*.inc",
                      "*.bat",
                      "*.sh",
                      "*.4coder",
                      "*.txt",
                  };
                  
                  blacklist_patterns =
                  {
                      ".*",
                  };
                  
                  load_paths =
                  {
                      {
                          { {"."}, .recursive = true, .relative = true }, .os = "win"
                      },
                  };
                  
                  command_list =
                  {
                      {
                          .name = "build",
                          .out = "*compilation*",
                          .footer_panel = true,
                          .save_dirty_files = true,
                          .cursor_at_end = false,
                          .cmd =
                          {
                              { "echo Windows build command not implemented for 4coder project.", .os = "win" },
        { "echo Linux build command not implemented for 4coder project.", .os = "linux" },
                          },
                      },
                      
                      {
                          .name = "run",
                          .out = "*compilation*",
                          .footer_panel = true,
                          .save_dirty_files = true,
                          .cursor_at_end = false,
                          .cmd =
                          {
                              { "echo Windows run command not implemented for 4coder project.", .os = "win" },
        { "echo Linux run command not implemented for 4coder project.", .os = "linux" },
                          },
                      },
                      
                  };
                  
                  fkey_command[1] = "build";
                  fkey_command[2] = "run";
        )PROJ";
                
                fprintf(file, "%s", string);
                fclose(file);
                load_project(app);
            } else {
                // TODO(rjf): Error.
            }
        }
    }
    
    load_project(app);
}

//~ Indentation and autocomplete

NAMESPACE_BEGIN(nne)

function void F4_ReIndentLine(Application_Links *app, Buffer_ID buffer, i64 line, i64 indent_delta)
{
    using namespace nne;
	
	Scratch_Block scratch(app);
    String_Const_u8 line_string = push_buffer_line(app, scratch, buffer, line);
    i64 line_start_pos = get_line_start_pos(app, buffer, line);
    
    Range_i64 line_indent_range = Ii64(0, 0);
    i64 tabs_at_beginning = 0;
    i64 spaces_at_beginning = 0;
    for(u64 i = 0; i < line_string.size; i += 1)
    {
        if(line_string.str[i] == '\t')
        {
            tabs_at_beginning += 1;
        }
        else if(character_is_whitespace(line_string.str[i]))
        {
            spaces_at_beginning += 1;
        }
        else if(!character_is_whitespace(line_string.str[i]))
        {
            line_indent_range.max = (i64)i;
            break;
        }
    }
    
    // NOTE(rjf): Indent lines.
    {
        Range_i64 indent_range =
        {
            line_indent_range.min + line_start_pos,
            line_indent_range.max + line_start_pos,
        };
        
        i64 indent_width = (i64)def_get_config_u64(app, vars_save_string_lit("indent_width"));
        b32 indent_with_tabs = def_get_config_b32(vars_save_string_lit("indent_with_tabs"));
        i64 spaces_per_indent_level = indent_width;
        i64 indent_level = spaces_at_beginning / spaces_per_indent_level + tabs_at_beginning;
        i64 new_indent_level = indent_level + indent_delta;
        
        String_Const_u8 indent_string = indent_with_tabs ? S8Lit("\t") : push_stringf(scratch, "%.*s", Min(indent_width, 16),
                                                                                      "                ");
        buffer_replace_range(app, buffer, indent_range, S8Lit(""));
        for(i64 i = 0; i < new_indent_level; i += 1)
        {
            buffer_replace_range(app, buffer, Ii64(line_start_pos), indent_string);
        }
    }
    
}

internal void
F4_ReIndentLineRange(Application_Links *app, Buffer_ID buffer, Range_i64 range, i64 indent_delta)
{
    using namespace nne;
	
	for(i64 i = range.min; i <= range.max; i += 1)
    {
        F4_ReIndentLine(app, buffer, i, indent_delta);
    }
}

internal Range_i64
F4_LineRangeFromPosRange(Application_Links *app, Buffer_ID buffer, Range_i64 pos_range)
{
    using namespace nne;
	
	Range_i64 lines_range =
        Ii64(get_line_number_from_pos(app, buffer, pos_range.min),
             get_line_number_from_pos(app, buffer, pos_range.max));
    return lines_range;
}

internal Range_i64
F4_PosRangeFromLineRange(Application_Links *app, Buffer_ID buffer, Range_i64 line_range)
{
    using namespace nne;
	
	if(line_range.min > line_range.max)
    {
        i64 swap = line_range.max;
        line_range.max = line_range.min;
        line_range.min = swap;
    }
    Range_i64 pos_range =
        Ii64(get_line_start_pos(app, buffer, line_range.min),
             get_line_end_pos(app, buffer, line_range.max));
    return pos_range;
}

internal void
F4_ReIndentPosRange(Application_Links *app, Buffer_ID buffer, Range_i64 range, i64 indent_delta)
{
    using namespace nne;
	
	F4_ReIndentLineRange(app, buffer,
                         F4_LineRangeFromPosRange(app, buffer, range),
                         indent_delta);
}

internal void
F4_AdjustCursorAndMarkForIndentation(Application_Links *app, View_ID view, i64 original_cursor, i64 original_mark, Range_i64 original_line_range)
{
    using namespace nne;
	
	Buffer_ID buffer = view_get_buffer(app, view, Access_Read);
    Scratch_Block scratch(app);
    if(original_cursor == original_mark)
    {
        i64 start_pos = get_line_start_pos(app, buffer, original_line_range.min);
        i64 new_pos = start_pos;
        String_Const_u8 line = push_buffer_line(app, scratch, buffer, original_line_range.min);
        for(u64 i = 0; i < line.size; i += 1)
        {
            if(!character_is_whitespace(line.str[i]))
            {
                new_pos = start_pos + (i64)i;
                break;
            }
        }
        
        view_set_cursor(app, view, seek_pos(new_pos));
        view_set_mark(app, view, seek_pos(new_pos));
    }
    else
    {
        Range_i64 range = F4_PosRangeFromLineRange(app, buffer, original_line_range);
        view_set_cursor(app, view, seek_pos(original_cursor > original_mark ? range.max : range.min));
        view_set_mark(app, view, seek_pos(original_cursor > original_mark ? range.min : range.max));
    }
}

NAMESPACE_END()

CUSTOM_COMMAND_SIG(f4_autocomplete_or_indent)
CUSTOM_DOC("Tries to autocomplete the word currently being typed, and inserts indentation if such a word is not found.")
{
    using namespace nne;
	
	ProfileScope(app, "[F4] Word Complete");
    
    View_ID view = get_active_view(app, Access_ReadWriteVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
    
    if(buffer != 0)
    {
        Managed_Scope scope = view_get_managed_scope(app, view);
        
        b32 first_completion = false;
        Rewrite_Type *rewrite = scope_attachment(app, scope, view_rewrite_loc, Rewrite_Type);
        if (*rewrite != Rewrite_WordComplete){
            first_completion = true;
        }
        
        set_next_rewrite(app, view, Rewrite_WordComplete);
        
        Word_Complete_Iterator *it = word_complete_get_shared_iter(app);
        local_persist b32 initialized = false;
        local_persist Range_i64 range = {};
        
        if(first_completion || !initialized)
        {
            ProfileScope(app, "[F4] Word Complete State Init");
            initialized = false;
            i64 pos = view_get_cursor_pos(app, view);
            Range_i64 needle_range = get_word_complete_needle_range(app, buffer, pos);
            if(range_size(needle_range) > 0)
            {
                initialized = true;
                range = needle_range;
                word_complete_iter_init(buffer, needle_range, it);
            }
        }
        
        // NOTE(rjf): Word-Complete
        if(initialized)
        {
            ProfileScope(app, "[F4] Word Complete Apply");
            
            word_complete_iter_next(it);
            String_Const_u8 str = word_complete_iter_read(it);
            
            buffer_replace_range(app, buffer, range, str);
            
            range.max = range.min + str.size;
            view_set_cursor_and_preferred_x(app, view, seek_pos(range.max));
        }
        
        // NOTE(rjf): Insert indentation if autocomplete failed
        else if(initialized == 0)
        {
            i64 pos = view_get_cursor_pos(app, view);
            i64 mark = view_get_mark_pos(app, view);
            Range_i64 pos_range = Ii64(pos, mark);
            Range_i64 line_range = F4_LineRangeFromPosRange(app, buffer, pos_range);
            
            History_Group group = history_group_begin(app, buffer);
            F4_ReIndentPosRange(app, buffer, Ii64(pos, mark), +1);
            F4_AdjustCursorAndMarkForIndentation(app, view, pos, mark, line_range);
            history_group_end(group);
            no_mark_snap_to_cursor(app, view);
        }
    }
}

CUSTOM_COMMAND_SIG(f4_unindent)
CUSTOM_DOC("Unindent the selected range.")
{
    using namespace nne;
	
	Scratch_Block scratch(app);
    
    View_ID view = get_active_view(app, Access_ReadWrite);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWrite);
    i64 pos = view_get_cursor_pos(app, view);
    i64 mark = view_get_mark_pos(app, view);
    Range_i64 pos_range = Ii64(pos, mark);
    Range_i64 line_range = F4_LineRangeFromPosRange(app, buffer, pos_range);
    History_Group group = history_group_begin(app, buffer);
    F4_ReIndentPosRange(app, buffer, Ii64(pos, mark), -1);
    F4_AdjustCursorAndMarkForIndentation(app, view, pos, mark, line_range);
    history_group_end(group);
    no_mark_snap_to_cursor(app, view);
}

NAMESPACE_BEGIN(nne)

function void
F4_GenerateHotDirectoryFileList_Project(Application_Links *app, Lister *lister)
{
#if 0
    Scratch_Block scratch(app, lister->arena);
    
    Project_File_Pattern_Array whitelist = current_project.pattern_array;
    Project_File_Pattern_Array blacklist = current_project.blacklist_pattern_array;
    
    Temp_Memory temp = begin_temp(lister->arena);
    String_Const_u8 hot = push_hot_directory(app, lister->arena);
    if (!character_is_slash(string_get_character(hot, hot.size - 1))){
        hot = push_u8_stringf(lister->arena, "%.*s/", string_expand(hot));
    }
    lister_set_text_field(lister, hot);
    lister_set_key(lister, string_front_of_path(hot));
    
    File_List file_list = system_get_file_list(scratch, hot);
    end_temp(temp);
    
    File_Info **one_past_last = file_list.infos + file_list.count;
    
    lister_begin_new_item_set(app, lister);
    
    hot = push_hot_directory(app, lister->arena);
    push_align(lister->arena, 8);
    if(hot.str != 0)
    {
        String_Const_u8 empty_string = string_u8_litexpr("");
        Lister_Prealloced_String empty_string_prealloced = lister_prealloced(empty_string);
        
        // NOTE(rjf): Add all directories.
        for (File_Info **info = file_list.infos; info < one_past_last; info += 1)
        {
            if (!HasFlag((**info).attributes.flags, FileAttribute_IsDirectory)) continue;
            String_Const_u8 file_name = push_u8_stringf(lister->arena, "%.*s/",
                                                        string_expand((**info).file_name));
            lister_add_item(lister, lister_prealloced(file_name), empty_string_prealloced, file_name.str, 0);
        }
        
        // NOTE(rjf): Add files, if they match with the project paths.
        for (File_Info **info = file_list.infos;
             info < one_past_last;
             info += 1){
            if (HasFlag((**info).attributes.flags, FileAttribute_IsDirectory)) continue;
            String_Const_u8 file_name = push_string_copy(lister->arena, (**info).file_name);
            
            if(match_in_pattern_array(file_name, whitelist) &&
               !match_in_pattern_array(file_name, blacklist))
            {
                char *is_loaded = "";
                char *status_flag = "";
                
                Buffer_ID buffer = {};
                
                {
                    Temp_Memory path_temp = begin_temp(lister->arena);
                    List_String_Const_u8 list = {};
                    string_list_push(lister->arena, &list, hot);
                    string_list_push_overlap(lister->arena, &list, '/', (**info).file_name);
                    String_Const_u8 full_file_path = string_list_flatten(lister->arena, list);
                    buffer = get_buffer_by_file_name(app, full_file_path, Access_Always);
                    end_temp(path_temp);
                }
                
                if (buffer != 0){
                    is_loaded = "LOADED";
                    Dirty_State dirty = buffer_get_dirty_state(app, buffer);
                    switch (dirty){
                        case DirtyState_UnsavedChanges:  status_flag = " *"; break;
                        case DirtyState_UnloadedChanges: status_flag = " !"; break;
                        case DirtyState_UnsavedChangesAndUnloadedChanges: status_flag = " *!"; break;
                    }
                }
                String_Const_u8 status = push_u8_stringf(lister->arena, "%s%s", is_loaded, status_flag);
                lister_add_item(lister, lister_prealloced(file_name), lister_prealloced(status), file_name.str, 0);
            }
        }
    }
#endif
}

function File_Name_Result
F4_GetFileNameFromUser_Project(Application_Links *app, Arena *arena, String_Const_u8 query, View_ID view)
{
    using namespace nne;
	
	Lister_Handlers handlers = lister_get_default_handlers();
    handlers.refresh = F4_GenerateHotDirectoryFileList_Project;
    handlers.write_character = lister__write_character__file_path;
    handlers.backspace = lister__backspace_text_field__file_path;
    
    Lister_Result l_result = run_lister_with_refresh_handler(app, arena, query, handlers);
    
    File_Name_Result result = {};
    result.canceled = l_result.canceled;
    if (!l_result.canceled){
        result.clicked = l_result.activated_by_click;
        if (l_result.user_data != 0){
            String_Const_u8 name = SCu8((u8*)l_result.user_data);
            result.file_name_activated = name;
            result.is_folder = character_is_slash(string_get_character(name, name.size - 1));
        }
        result.file_name_in_text_field = string_front_of_path(l_result.text_field);
        
        String_Const_u8 path = {};
        if (l_result.user_data == 0 && result.file_name_in_text_field.size == 0 && l_result.text_field.size > 0){
            result.file_name_in_text_field = string_front_folder_of_path(l_result.text_field);
            path = string_remove_front_folder_of_path(l_result.text_field);
        }
        else{
            path = string_remove_front_of_path(l_result.text_field);
        }
        if (character_is_slash(string_get_character(path, path.size - 1))){
            path = string_chop(path, 1);
        }
        result.path_in_text_field = path;
    }
    
    return(result);
}

NAMESPACE_END()

CUSTOM_UI_COMMAND_SIG(f4_interactive_open_or_new_in_project)
CUSTOM_DOC("Interactively open a file out of the file system, filtered to files only in the project.")
{
    using namespace nne;
	
	for(;;)
    {
        Scratch_Block scratch(app);
        View_ID view = get_this_ctx_view(app, Access_Always);
        File_Name_Result result = F4_GetFileNameFromUser_Project(app, scratch, S8Lit("Open (File In Project):"), view);
        if (result.canceled) break;
        
        String_Const_u8 file_name = result.file_name_activated;
        if (file_name.size == 0){
            file_name = result.file_name_in_text_field;
        }
        if (file_name.size == 0) break;
        
        String_Const_u8 path = result.path_in_text_field;
        String_Const_u8 full_file_name = push_u8_stringf(scratch, "%.*s/%.*s",
                                                         string_expand(path), string_expand(file_name));
        
        if(result.is_folder)
        {
            set_hot_directory(app, full_file_name);
            continue;
        }
        
        if(character_is_slash(file_name.str[file_name.size - 1]))
        {
            File_Attributes attribs = system_quick_file_attributes(scratch, full_file_name);
            if(HasFlag(attribs.flags, FileAttribute_IsDirectory))
            {
                set_hot_directory(app, full_file_name);
                continue;
            }
            if(string_looks_like_drive_letter(file_name))
            {
                set_hot_directory(app, file_name);
                continue;
            }
            if(query_create_folder(app, file_name))
            {
                set_hot_directory(app, full_file_name);
                continue;
            }
            break;
        }
        
        Buffer_ID buffer = create_buffer(app, full_file_name, 0);
        if (buffer != 0){
            view_set_buffer(app, view, buffer, 0);
        }
        break;
    }
}

//~ Commenting and uncommenting

NAMESPACE_BEGIN(nne)

// @Note(ema): The first "Line" refers to the style of comment (// vs /*) and the second "Line" refers to a line in the source code.
internal void F4_SetLineCommentedOnLine(Application_Links *app, Buffer_ID buffer, i64 *cursor_p, i64 *mark_p, b32 commented) {
    i64 cursor      = *cursor_p;
    i64 mark        = *mark_p;
    i64 cursor_line = get_line_number_from_pos(app, buffer, cursor);
    i64 mark_line   = get_line_number_from_pos(app, buffer, mark);
    
    if (cursor_line == mark_line) {
        i64 line = cursor_line;
        i64 line_start = get_pos_past_lead_whitespace_from_line_number(app, buffer, line);
        b32 already_has_comment = c_line_comment_starts_at_position(app, buffer, line_start);
        
		// @Rename(ema): "commented" -> "should_comment" ??
        if (commented) {
            if (!already_has_comment) {
                buffer_replace_range(app, buffer, Ii64(line_start), string_u8_litexpr("//"));
                cursor = mark += 2;
            }
        } else {
            if (already_has_comment) {
                buffer_replace_range(app, buffer, Ii64(line_start, line_start + 2), string_u8_empty);
                cursor = mark -= 2;
            }
        }
    }
    
    *cursor_p = cursor;
    *mark_p = mark;
}

internal void F4_SetBlockCommentedOnRange(Application_Links *app, Buffer_ID buffer, i64 *cursor_p, i64 *mark_p, b32 commented) {
    Scratch_Block scratch(app);
    
    i64       cursor = *cursor_p;
    i64       mark   = *mark_p;
    Range_i64 range  = Ii64(cursor, mark);
    
    if (commented) {
        buffer_replace_range(app, buffer, Ii64(range.max, range.max), S8Lit("*/"));
        buffer_replace_range(app, buffer, Ii64(range.min, range.min), S8Lit("/*"));
        
		if (cursor > mark) { cursor += 4; }
        else               { mark   += 4; }
    } else if (range.max - range.min >= 2) {
        String_Const_u8 opener = push_buffer_range(app, scratch, buffer, Ii64(range.min, range.min+2));
        String_Const_u8 closer = push_buffer_range(app, scratch, buffer, Ii64(range.max-2, range.max));
        
		if (string_match(opener, S8Lit("/*")) && string_match(closer, S8Lit("*/"))) {
            buffer_replace_range(app, buffer, Ii64(range.max-2, range.max), S8Lit(""));
            buffer_replace_range(app, buffer, Ii64(range.min, range.min+2), S8Lit(""));
            
			if (cursor > mark) { cursor -= 4; }
            if (mark > cursor) { mark   -= 4; }
        }
    }
    
    *cursor_p = cursor;
    *mark_p = mark;
}

function b32 F4_CBlockCommentStartsAtPosition(Application_Links *app, Buffer_ID buffer, i64 pos) {
    b32 alread_has_comment = false;
    u8  check_buffer[2];
    if (buffer_read_range(app, buffer, Ii64(pos, pos + 2), check_buffer)) {
        if (check_buffer[0] == '/' && check_buffer[1] == '*') {
            alread_has_comment = true;
        }
    }
	
    return alread_has_comment;
}

internal void F4_SetCommentedOnRange(Application_Links *app, Buffer_ID buffer, i64 *cursor_p, i64 *mark_p, b32 commented) {
    Scratch_Block scratch(app);
    
    i64         cursor = *cursor_p;
    i64         mark   = *mark_p;
    Range_i64   range  = Ii64(cursor, mark);
    Range_i64   line_range = F4_LineRangeFromPosRange(app, buffer, range);
    Token_Array tokens = get_token_array_from_buffer(app, buffer);
    
    if (range.min == range.max) {                  // NOTE(rjf): No selection
        F4_SetLineCommentedOnLine(app, buffer, &cursor, &mark, commented);
    } else if (line_range.min == line_range.max) { // NOTE(rjf): Single-Line Selection
        Token *min_token = get_token_from_pos(app, &tokens, (u64)range.min);
        Token *max_token = get_token_from_pos(app, &tokens, (u64)range.max);
        
        if (min_token == max_token && min_token && min_token->kind == TokenBaseKind_Comment) {
			// Selection is inside comment
			
#if 0
			// @Cleanup(ema): Check if this works the same way. Remove the other, less clear line.
			if (commented) {
				comment_line(app);
			} else {
				uncomment_line(app);
			}
#else
            (commented ? comment_line : uncomment_line)(app);
#endif
        } else {
			// Selection is not inside comment
            
			F4_SetBlockCommentedOnRange(app, buffer, &cursor, &mark, commented);
        }
    } else if (line_range.min != line_range.max) { // NOTE(rjf): Multi-Line Selection
        if (commented) {
            i64 min_pos = Min(cursor, mark);
            i64 line = get_line_number_from_pos(app, buffer, min_pos);
            i64 start_of_line = get_line_start_pos(app, buffer, line);
            
            if (min_pos == start_of_line) {
                // NOTE(rjf): Selection starts on first column.
				
				for (i64 i = line_range.min; i <= line_range.max; i += 1) {
                    i64 cursor2 = get_line_start_pos(app, buffer, i);
                    i64 mark2   = get_line_end_pos(app, buffer, i);
                    F4_SetLineCommentedOnLine(app, buffer, &cursor2, &mark2, commented);
                }
				
                if (cursor < mark) {
                    cursor = get_line_start_pos(app, buffer, line_range.min);
                    mark   = get_line_end_pos(app, buffer, line_range.max);
                } else {
                    mark   = get_line_start_pos(app, buffer, line_range.min);
                    cursor = get_line_end_pos(app, buffer, line_range.max);
                }
            } else {
                // NOTE(rjf): Selection does not start on first column.
				
				F4_SetBlockCommentedOnRange(app, buffer, &cursor, &mark, 1);
            }
        } else {
            b32 starts_with_block_comment = F4_CBlockCommentStartsAtPosition(app, buffer, range.min);
            if (starts_with_block_comment) {
                F4_SetBlockCommentedOnRange(app, buffer, &cursor, &mark, 0);
            } else {
                for (i64 i = line_range.min; i <= line_range.max; i += 1) {
                    i64 cursor2 = get_line_start_pos(app, buffer, i);
                    i64 mark2   = get_line_start_pos(app, buffer, i);
                    F4_SetLineCommentedOnLine(app, buffer, &cursor2, &mark2, 0);
                }
				
                if (cursor < mark) {
                    cursor = get_line_start_pos(app, buffer, line_range.min);
                    mark   = get_line_end_pos(app, buffer, line_range.max);
                } else {
                    mark   = get_line_start_pos(app, buffer, line_range.min);
                    cursor = get_line_end_pos(app, buffer, line_range.max);
                }
            }
        }
    }
    
    *cursor_p = cursor;
    *mark_p = mark;
}

NAMESPACE_END()

// @Rename(ema): Remove f4_ prefix
CUSTOM_COMMAND_SIG(f4_comment_selection)
CUSTOM_DOC("Performs VS-style commenting on the selected range.") {
    View_ID   view   = get_active_view(app, Access_ReadWriteVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
    i64       cursor = view_get_cursor_pos(app, view);
    i64       mark   = view_get_mark_pos(app, view);
    
    History_Group group = history_group_begin(app, buffer);
    nne::F4_SetCommentedOnRange(app, buffer, &cursor, &mark, 1);
    view_set_cursor(app, view, seek_pos(cursor));
    view_set_mark(app, view, seek_pos(mark));
    history_group_end(group);
    no_mark_snap_to_cursor(app, view);
}

CUSTOM_COMMAND_SIG(f4_uncomment_selection)
CUSTOM_DOC("Performs VS-style uncommenting on the selected range.") {
    View_ID   view   = get_active_view(app, Access_ReadWriteVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
    i64       cursor = view_get_cursor_pos(app, view);
    i64       mark   = view_get_mark_pos(app, view);
	
    History_Group group = history_group_begin(app, buffer);
    nne::F4_SetCommentedOnRange(app, buffer, &cursor, &mark, 0);
    view_set_cursor(app, view, seek_pos(cursor));
    view_set_mark(app, view, seek_pos(mark));
    history_group_end(group);
    no_mark_snap_to_cursor(app, view);
}

//~ Misc

CUSTOM_COMMAND_SIG(f4_remedy_open_cursor)
CUSTOM_DOC("Opens the active panel's file in an actively-running RemedyBG instance, and moves to the cursor's line position.") {
    // using namespace nne;
	
	Scratch_Block scratch(app);
	
    View_ID   view        = get_active_view(app, Access_Read);
    Buffer_ID buffer      = view_get_buffer(app, view, Access_Read);
    String8   buffer_name = push_buffer_file_name(app, scratch, buffer);
	
    i64 pos  = view_get_cursor_pos(app, view);
    i64 line = get_line_number_from_pos(app, buffer, pos);
	
    String8 hot_directory = push_hot_directory(app, scratch);
	
    Child_Process_ID child_id = create_child_process(app, hot_directory, push_stringf(scratch, "remedybg.exe open-file %.*s %i", string_expand(buffer_name), cast(int)line));
    cast(void)child_id;
}

CUSTOM_COMMAND_SIG(f4_bump_to_column)
CUSTOM_DOC("Insert the required number of spaces to get to a specified column number.") {
    // using namespace nne;
	
	View_ID   view    = get_active_view(app, Access_Always);
    Buffer_ID buffer  = view_get_buffer(app, view, Access_Always);
    Face_ID   face_id = get_face_id(app, buffer);
    Face_Description description = get_face_description(app, face_id);
    
    Query_Bar_Group group(app);
    u8 string_space[256];
    Query_Bar bar = {};
    bar.prompt = string_u8_litexpr("Column Number: ");
    bar.string = SCu8(string_space, cast(u64)0);
    bar.string_capacity = sizeof(string_space);
    
	if (query_user_number(app, &bar)) {
        i64 column_number = cast(i64)string_to_integer(bar.string, 10);
        i64 cursor = view_get_cursor_pos(app, view);
        i64 cursor_line = get_line_number_from_pos(app, buffer, cursor);
        i64 cursor_column = cursor - get_line_start_pos(app, buffer, cursor_line) + 1;
        i64 spaces_to_insert = column_number - cursor_column;
        History_Group history_group = history_group_begin(app, buffer);
		
        for (i64 i = 0; i < spaces_to_insert; i += 1) {
            buffer_replace_range(app, buffer, Ii64(cursor, cursor), str8_lit(" "));
        }
		
        view_set_cursor(app, view, seek_pos(cursor+spaces_to_insert));
        view_set_mark(app, view, seek_pos(cursor+spaces_to_insert));
        history_group_end(history_group);
    }
}

#endif // FCODER_CUSTOM_BASE_COMMANDS_CPP
