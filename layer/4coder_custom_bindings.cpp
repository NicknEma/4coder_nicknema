#ifndef FCODER_CUSTOM_BINDINGS_CPP
#define FCODER_CUSTOM_BINDINGS_CPP

//~ Global keybinding modes
// @Note(ema): GlobalKeybindingMode is defined in ubiquitous.h
// @Note(ema): 0, 1, 2 and 3 aren't really helpful names... at least explain here what they are.

CUSTOM_COMMAND_SIG(switch_to_keybinding_0)
CUSTOM_DOC("Switch the keybindings to mode 0.") {
	global_keybinding_mode = Keybinding_Mode_0;
}

CUSTOM_COMMAND_SIG(switch_to_keybinding_1)
CUSTOM_DOC("Switch the keybindings to mode 1.") {
	global_keybinding_mode = Keybinding_Mode_1;
}

CUSTOM_COMMAND_SIG(switch_to_keybinding_2)
CUSTOM_DOC("Switch the keybindings to mode 2.") {
	global_keybinding_mode = Keybinding_Mode_2;
}

CUSTOM_COMMAND_SIG(switch_to_keybinding_3)
CUSTOM_DOC("Switch the keybindings to mode 3.") {
	global_keybinding_mode = Keybinding_Mode_3;
}

NAMESPACE_BEGIN(nne)

struct Command_Map_ID_Pair {
	Command_Map_ID From;
	Command_Map_ID To;
};
global Command_Map_ID_Pair GlobalCommandMapReroute[4] = {};

function Implicit_Map_Result implicit_map_function(Application_Links *app, String_ID lang, String_ID mode, Input_Event *event) {
    Implicit_Map_Result result = {};
    
    View_ID view = get_this_ctx_view(app, Access_Always);
    
	Command_Map_ID orig_id = default_get_map_id(app, view);
    Command_Map_ID map_id = orig_id;
	if (global_keybinding_mode == Keybinding_Mode_1) {
		for (int PairIndex = 0; PairIndex < ArrayCount(GlobalCommandMapReroute); PairIndex += 1) {
			if (GlobalCommandMapReroute[PairIndex].From == map_id) {
				map_id = GlobalCommandMapReroute[PairIndex].To;
				break;
			}
		}
	}
	
	Command_Binding binding = map_get_binding_recursive(&framework_mapping, map_id, event);
	if (!binding.custom) {
		binding = map_get_binding_recursive(&framework_mapping, orig_id, event);
	} else {
		Allow_Break();
	}
    
    // TODO(allen): map_id <-> map name?
    result.map = 0;
    result.command = binding.custom;
    
    return result;
}


//~ NOTE(rjf): Bindings

// @Cleanup(ema): Why are these bindings "absolutely necessary"? Figure out and explain.
function void set_absolutely_necessary_bindings(Mapping *mapping) {
    String_ID global_map_id = vars_save_string_lit("keys_global");
    String_ID file_map_id   = vars_save_string_lit("keys_file");
    String_ID code_map_id   = vars_save_string_lit("keys_code");
    
	String_ID global_command_map_id = vars_save_string_lit("keys_global_1");
	String_ID file_command_map_id   = vars_save_string_lit("keys_file_1");
    String_ID code_command_map_id   = vars_save_string_lit("keys_code_1");
    
	::implicit_map_function = nne::implicit_map_function;
	
	MappingScope();
    SelectMapping(mapping);
    
	// Global bindings (affecting the whole editor)
    SelectMap(global_map_id);
    BindCore(custom_startup,   CoreCode_Startup);
    BindCore(default_try_exit, CoreCode_TryExit);
    Bind(exit_4coder,          KeyCode_F4, KeyCode_Alt);
    BindMouseWheel(mouse_wheel_scroll);
    BindMouseWheel(mouse_wheel_change_face_size, KeyCode_Control);
    
	// Text files related bindings
    SelectMap(file_map_id);
    ParentMap(global_map_id);
    BindTextInput(f4_write_text_input); // Every time there's text input, call this command.
    BindMouse(click_set_cursor_and_mark, MouseCode_Left);             // Mouse left pressed           => set cursor and mark
    BindMouseRelease(click_set_cursor,   MouseCode_Left);             // Mouse left released          => set cursor
    BindCore(click_set_cursor_and_mark,  CoreCode_ClickActivateView); // View activated               => set cursor and mark
    BindMouseMove(click_set_cursor_if_lbutton);                       // Mouse left helf + mouse move => set cursor
    
	// Code files related bindings (what counts as a code file is specified in the config.4coder file)
    SelectMap(code_map_id);
    ParentMap(file_map_id);
    BindTextInput(nne__write_text_and_auto_indent); // Every time there's text input in a code file, call this command. @Todo(ema): This doesn't work? What? If I step through the code in VS studio, writing text breaks on the default write_text_input.
    BindMouse(f4_lego_click_store_token_1, MouseCode_Right); // @Todo(ema): Figure out what these 2 do (lego isn't a terribly good name...)
    BindMouse(f4_lego_click_store_token_2, MouseCode_Middle);
    
	// @Todo(ema): Figure out what all this is. And also why these variables are declared at the top but only used here.
    SelectMap(global_command_map_id);
	ParentMap(global_map_id);
	GlobalCommandMapReroute[0].From = global_map_id;
	GlobalCommandMapReroute[0].To = global_command_map_id;
	
    SelectMap(file_command_map_id);
	ParentMap(global_command_map_id);
	GlobalCommandMapReroute[1].From = file_map_id;
	GlobalCommandMapReroute[1].To = file_command_map_id;
	
    SelectMap(code_command_map_id);
	ParentMap(file_command_map_id);
	GlobalCommandMapReroute[2].From = code_map_id;
	GlobalCommandMapReroute[2].To = code_command_map_id;
}

// This function is only called when we fail to load the bindings.4coder file. When that happens, we hardcode in some bindings.
function void set_default_bindings(Mapping *mapping) {
    String_ID global_map_id = vars_save_string_lit("keys_global");
    String_ID file_map_id   = vars_save_string_lit("keys_file");
    String_ID code_map_id   = vars_save_string_lit("keys_code");
    
    MappingScope();
    SelectMapping(mapping);
	
	// Global bindings.
    SelectMap(global_map_id);
    Bind(keyboard_macro_start_recording , KeyCode_U, KeyCode_Control);
    Bind(keyboard_macro_finish_recording, KeyCode_U, KeyCode_Control, KeyCode_Shift);
    Bind(keyboard_macro_replay,           KeyCode_U, KeyCode_Alt);
    Bind(change_active_panel,             KeyCode_Comma, KeyCode_Control);
    Bind(change_active_panel_backwards,   KeyCode_Comma, KeyCode_Control, KeyCode_Shift);
    Bind(interactive_new,                 KeyCode_N, KeyCode_Control);
    Bind(interactive_open_or_new,         KeyCode_O, KeyCode_Control);
    Bind(open_in_other,                   KeyCode_O, KeyCode_Alt);
    Bind(interactive_kill_buffer,         KeyCode_K, KeyCode_Control);
    Bind(interactive_switch_buffer,       KeyCode_I, KeyCode_Control);
    Bind(project_go_to_root_directory,    KeyCode_H, KeyCode_Control);
    Bind(save_all_dirty_buffers,          KeyCode_S, KeyCode_Control, KeyCode_Shift);
    Bind(change_to_build_panel,           KeyCode_Period, KeyCode_Alt);
    Bind(close_build_panel,               KeyCode_Comma, KeyCode_Alt);
    Bind(goto_next_jump,                  KeyCode_N, KeyCode_Alt);
    Bind(goto_prev_jump,                  KeyCode_N, KeyCode_Alt, KeyCode_Shift);
    Bind(build_in_build_panel,            KeyCode_M, KeyCode_Alt);
    Bind(goto_first_jump,                 KeyCode_M, KeyCode_Alt, KeyCode_Shift);
    Bind(toggle_filebar,                  KeyCode_B, KeyCode_Alt);
    Bind(execute_any_cli,                 KeyCode_Z, KeyCode_Alt);
    Bind(execute_previous_cli,            KeyCode_Z, KeyCode_Alt, KeyCode_Shift);
    Bind(command_lister,                  KeyCode_X, KeyCode_Alt);
    Bind(project_command_lister,          KeyCode_X, KeyCode_Alt, KeyCode_Shift);
    Bind(list_all_functions_current_buffer_lister, KeyCode_I, KeyCode_Control, KeyCode_Shift);
    Bind(project_fkey_command, KeyCode_F1);
    Bind(project_fkey_command, KeyCode_F2);
    Bind(project_fkey_command, KeyCode_F3);
    Bind(project_fkey_command, KeyCode_F4);
    Bind(project_fkey_command, KeyCode_F5);
    Bind(project_fkey_command, KeyCode_F6);
    Bind(project_fkey_command, KeyCode_F7);
    Bind(project_fkey_command, KeyCode_F8);
    Bind(project_fkey_command, KeyCode_F9);
    Bind(project_fkey_command, KeyCode_F10);
    Bind(project_fkey_command, KeyCode_F11);
    Bind(project_fkey_command, KeyCode_F12);
    Bind(project_fkey_command, KeyCode_F13);
    Bind(project_fkey_command, KeyCode_F14);
    Bind(project_fkey_command, KeyCode_F15);
    Bind(project_fkey_command, KeyCode_F16);
    
    // Custom bindings.
    {
        Bind(open_panel_vsplit, KeyCode_P, KeyCode_Control);
        Bind(open_panel_hsplit, KeyCode_Minus, KeyCode_Control);
        Bind(close_panel, KeyCode_P, KeyCode_Control, KeyCode_Shift);
        Bind(f4_search_for_definition__project_wide, KeyCode_J, KeyCode_Control);
        Bind(f4_search_for_definition__current_file, KeyCode_J, KeyCode_Control, KeyCode_Shift);
        Bind(f4_toggle_battery_saver, KeyCode_Tick, KeyCode_Alt);
        Bind(move_right_token_boundary, KeyCode_Right, KeyCode_Shift, KeyCode_Control);
        Bind(move_left_token_boundary, KeyCode_Left, KeyCode_Shift, KeyCode_Control);
    }
    
	// File related bindings.
    SelectMap(file_map_id);
    ParentMap(global_map_id);
    Bind(delete_char,            KeyCode_Delete);
    Bind(backspace_char,         KeyCode_Backspace);
    Bind(move_up,                KeyCode_Up);
    Bind(move_down,              KeyCode_Down);
    Bind(move_left,              KeyCode_Left);
    Bind(move_right,             KeyCode_Right);
    Bind(seek_end_of_line,       KeyCode_End);
    Bind(f4_home,            KeyCode_Home);
    Bind(page_up,                KeyCode_PageUp);
    Bind(page_down,              KeyCode_PageDown);
    Bind(goto_beginning_of_file, KeyCode_PageUp, KeyCode_Control);
    Bind(goto_end_of_file,       KeyCode_PageDown, KeyCode_Control);
    Bind(move_up_to_blank_line_end,        KeyCode_Up, KeyCode_Control);
    Bind(move_down_to_blank_line_end,      KeyCode_Down, KeyCode_Control);
    Bind(move_left_whitespace_boundary,    KeyCode_Left, KeyCode_Control);
    Bind(move_right_whitespace_boundary,   KeyCode_Right, KeyCode_Control);
    Bind(move_line_up,                     KeyCode_Up, KeyCode_Alt);
    Bind(move_line_down,                   KeyCode_Down, KeyCode_Alt);
    Bind(backspace_alpha_numeric_boundary, KeyCode_Backspace, KeyCode_Control);
    Bind(delete_alpha_numeric_boundary,    KeyCode_Delete, KeyCode_Control);
    Bind(snipe_backward_whitespace_or_token_boundary, KeyCode_Backspace, KeyCode_Alt);
    Bind(snipe_forward_whitespace_or_token_boundary,  KeyCode_Delete, KeyCode_Alt);
    Bind(set_mark,                    KeyCode_Space, KeyCode_Control);
    Bind(replace_in_range,            KeyCode_A, KeyCode_Control);
    Bind(copy,                        KeyCode_C, KeyCode_Control);
    Bind(delete_range,                KeyCode_D, KeyCode_Control);
    Bind(delete_line,                 KeyCode_D, KeyCode_Control, KeyCode_Shift);
    Bind(center_view,                 KeyCode_E, KeyCode_Control);
    Bind(left_adjust_view,            KeyCode_E, KeyCode_Control, KeyCode_Shift);
    Bind(search,                      KeyCode_F, KeyCode_Control);
    Bind(list_all_locations,          KeyCode_F, KeyCode_Control, KeyCode_Shift);
    Bind(list_all_substring_locations_case_insensitive, KeyCode_F, KeyCode_Alt);
    Bind(goto_line,                   KeyCode_G, KeyCode_Control);
    Bind(list_all_locations_of_selection,  KeyCode_G, KeyCode_Control, KeyCode_Shift);
    Bind(kill_buffer,                 KeyCode_K, KeyCode_Control, KeyCode_Shift);
    Bind(duplicate_line,              KeyCode_L, KeyCode_Control);
    Bind(cursor_mark_swap,            KeyCode_M, KeyCode_Control);
    Bind(reopen,                      KeyCode_O, KeyCode_Control, KeyCode_Shift);
    Bind(query_replace,               KeyCode_Q, KeyCode_Control);
    Bind(query_replace_identifier,    KeyCode_Q, KeyCode_Control, KeyCode_Shift);
    Bind(query_replace_selection,     KeyCode_Q, KeyCode_Alt);
    Bind(reverse_search,              KeyCode_R, KeyCode_Control);
    Bind(save,                        KeyCode_S, KeyCode_Control);
    Bind(save_all_dirty_buffers,      KeyCode_S, KeyCode_Control, KeyCode_Shift);
    Bind(search_identifier,           KeyCode_T, KeyCode_Control);
    Bind(list_all_locations_of_identifier, KeyCode_T, KeyCode_Control, KeyCode_Shift);
    Bind(paste_and_indent,            KeyCode_V, KeyCode_Control);
    Bind(paste_next_and_indent,       KeyCode_V, KeyCode_Control, KeyCode_Shift);
    Bind(cut,                         KeyCode_X, KeyCode_Control);
    Bind(redo,                        KeyCode_Y, KeyCode_Control);
    Bind(undo,                        KeyCode_Z, KeyCode_Control);
    Bind(view_buffer_other_panel,     KeyCode_1, KeyCode_Control);
    Bind(swap_panels,                 KeyCode_2, KeyCode_Control);
    Bind(if_read_only_goto_position,  KeyCode_Return);
    Bind(if_read_only_goto_position_same_panel, KeyCode_Return, KeyCode_Shift);
    Bind(view_jump_list_with_lister,  KeyCode_Period, KeyCode_Control, KeyCode_Shift);
    
    // Custom bindings.
    {
        Bind(f4_write_zero_struct,  KeyCode_0, KeyCode_Control);
        Bind(move_right_token_boundary, KeyCode_Right, KeyCode_Shift, KeyCode_Control);
        Bind(move_left_token_boundary, KeyCode_Left, KeyCode_Shift, KeyCode_Control);
    }
    
	// Code files related bindings.
    SelectMap(code_map_id);
    ParentMap(file_map_id);
    BindTextInput(nne__write_text_and_auto_indent);
    Bind(move_left_alpha_numeric_boundary,           KeyCode_Left, KeyCode_Control);
    Bind(move_right_alpha_numeric_boundary,          KeyCode_Right, KeyCode_Control);
    Bind(move_left_alpha_numeric_or_camel_boundary,  KeyCode_Left, KeyCode_Alt);
    Bind(move_right_alpha_numeric_or_camel_boundary, KeyCode_Right, KeyCode_Alt);
    Bind(comment_line_toggle,        KeyCode_Semicolon, KeyCode_Control);
    Bind(word_complete,              KeyCode_Tab);
    Bind(auto_indent_range,          KeyCode_Tab, KeyCode_Control);
    Bind(auto_indent_line_at_cursor, KeyCode_Tab, KeyCode_Shift);
    Bind(word_complete_drop_down,    KeyCode_Tab, KeyCode_Shift, KeyCode_Control);
    Bind(write_block,                KeyCode_R, KeyCode_Alt);
    Bind(write_todo,                 KeyCode_T, KeyCode_Alt);
    Bind(write_note,                 KeyCode_Y, KeyCode_Alt);
    Bind(list_all_locations_of_type_definition,               KeyCode_D, KeyCode_Alt);
    Bind(list_all_locations_of_type_definition_of_identifier, KeyCode_T, KeyCode_Alt, KeyCode_Shift);
    Bind(open_long_braces,           KeyCode_LeftBracket, KeyCode_Control);
    Bind(open_long_braces_semicolon, KeyCode_LeftBracket, KeyCode_Control, KeyCode_Shift);
    Bind(open_long_braces_break,     KeyCode_RightBracket, KeyCode_Control, KeyCode_Shift);
    Bind(select_surrounding_scope,   KeyCode_LeftBracket, KeyCode_Alt);
    Bind(select_surrounding_scope_maximal, KeyCode_LeftBracket, KeyCode_Alt, KeyCode_Shift);
    Bind(select_prev_scope_absolute, KeyCode_RightBracket, KeyCode_Alt);
    Bind(select_prev_top_most_scope, KeyCode_RightBracket, KeyCode_Alt, KeyCode_Shift);
    Bind(select_next_scope_absolute, KeyCode_Quote, KeyCode_Alt);
    Bind(select_next_scope_after_current, KeyCode_Quote, KeyCode_Alt, KeyCode_Shift);
    Bind(place_in_scope,             KeyCode_ForwardSlash, KeyCode_Alt);
    Bind(delete_current_scope,       KeyCode_Minus, KeyCode_Alt);
    Bind(if0_off,                    KeyCode_I, KeyCode_Alt);
    Bind(open_file_in_quotes,        KeyCode_1, KeyCode_Alt);
    Bind(open_matching_file_cpp,     KeyCode_2, KeyCode_Alt);
}

NAMESPACE_END()

#endif // FCODER_CUSTOM_BINDINGS_CPP
