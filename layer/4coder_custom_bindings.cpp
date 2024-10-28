#ifndef FCODER_CUSTOM_BINDINGS_CPP
#define FCODER_CUSTOM_BINDINGS_CPP

//~ Global keybinding modes
// NOTE(ema): global_keybinding_mode is defined in ubiquitous.h
// TODO(ema): 0, 1, 2 and 3 aren't really helpful names... at least explain here what they are. @Rename.

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
	Command_Map_ID from;
	Command_Map_ID to;
};
global Command_Map_ID_Pair global_command_map_reroute[4] = {};

function Implicit_Map_Result
implicit_map_function(Application_Links *app, String_ID lang, String_ID mode, Input_Event *event) {
	Implicit_Map_Result result = {};
	
	View_ID view = get_this_ctx_view(app, Access_Always);
	
	Command_Map_ID orig_id = default_get_map_id(app, view);
	Command_Map_ID map_id = orig_id;
	if (global_keybinding_mode == Keybinding_Mode_1) {
		for (int pair_index = 0; pair_index < ArrayCount(global_command_map_reroute); pair_index += 1) {
			if (global_command_map_reroute[pair_index].from == map_id) {
				map_id = global_command_map_reroute[pair_index].to;
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


//~ Bindings

// In 4coder, literally every event can be custom-controlled. Things like exiting the program when
// clicking the X button, scrolling the contents when moving the mouse wheel, inputting text
// when typing on the keyboard.
// This functions sets the bindings that are necessary for 4coder to be usable as a text editor.
function void
set_absolutely_necessary_bindings(Mapping *mapping) {
	::implicit_map_function = nne::implicit_map_function;
	
	MappingScope();
	SelectMapping(mapping);
	
	//- Global bindings (affecting the whole editor)
	String_ID global_map_id = vars_save_string_lit("keys_global");
	SelectMap(global_map_id);
	BindCore(custom_startup,   CoreCode_Startup); // When the program is launched, call the custom startup command
	BindCore(default_try_exit, CoreCode_TryExit); // When the user wants to exit, do exit
	Bind(exit_4coder, KeyCode_F4, KeyCode_Alt);   // Respond to Alt+F4
	BindMouseWheel(mouse_wheel_scroll);           // Scroll contents when the mouse wheel is moved
	BindMouseWheel(mouse_wheel_change_face_size, KeyCode_Control); // Change text size when the mouse wheel is moved and Ctrl is held
	
	//- Text files related bindings
	String_ID file_map_id   = vars_save_string_lit("keys_file");
	SelectMap(file_map_id);
	ParentMap(global_map_id);           // Every global binding also affects files
	BindTextInput(write_text_input);    // Every time there's text input, call this command. TODO(ema): If power mode is removed, the only thing making this necessary is the custom indentation rule @Cleanup.
	BindMouse(click_set_cursor_and_mark, MouseCode_Left);             // Mouse left pressed           => set cursor and mark
	BindMouseRelease(click_set_cursor,   MouseCode_Left);             // Mouse left released          => set cursor
	BindCore(click_set_cursor_and_mark,  CoreCode_ClickActivateView); // View activated               => set cursor and mark
	BindMouseMove(click_set_cursor_if_lbutton);                       // Mouse left helf + mouse move => set cursor
	
	//- Code files related bindings (what counts as a code file is specified in the config.4coder file)
	String_ID code_map_id   = vars_save_string_lit("keys_code");
	SelectMap(code_map_id);
	ParentMap(file_map_id);
	BindTextInput(custom__write_text_and_auto_indent); // Every time there's text input in a code file, call this command. TODO(ema): This doesn't work? What? If I step through the code in VS studio, writing text breaks on the default write_text_input.
	BindMouse(f4_lego_click_store_token_1, MouseCode_Right); // TODO(ema): Figure out what these 2 do (lego isn't a terribly good name...)
	BindMouse(f4_lego_click_store_token_2, MouseCode_Middle);
	
	// TODO(ema): Figure out what all this is.
	String_ID global_command_map_id = vars_save_string_lit("keys_global_1");
	String_ID file_command_map_id   = vars_save_string_lit("keys_file_1");
	String_ID code_command_map_id   = vars_save_string_lit("keys_code_1");
	
	SelectMap(global_command_map_id);
	ParentMap(global_map_id);
	global_command_map_reroute[0].from = global_map_id;
	global_command_map_reroute[0].to   = global_command_map_id;
	
	SelectMap(file_command_map_id);
	ParentMap(global_command_map_id);
	global_command_map_reroute[1].from = file_map_id;
	global_command_map_reroute[1].to   = file_command_map_id;
	
	SelectMap(code_command_map_id);
	ParentMap(file_command_map_id);
	global_command_map_reroute[2].from = code_map_id;
	global_command_map_reroute[2].to   = code_command_map_id;
}

// This function is only called when we fail to load the bindings.4coder file. When that happens, we hardcode in some default bindings.
function void
set_default_bindings(Mapping *mapping) {
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
	Bind(f4_home,                KeyCode_Home);
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
		Bind(move_right_token_boundary, KeyCode_Right, KeyCode_Shift, KeyCode_Control);
		Bind(move_left_token_boundary, KeyCode_Left, KeyCode_Shift, KeyCode_Control);
	}
	
	// Code files related bindings.
	SelectMap(code_map_id);
	ParentMap(file_map_id);
	BindTextInput(custom__write_text_and_auto_indent);
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

//~ Dynamic bindings.

CUSTOM_COMMAND_SIG(load_bindings_default_directories)
CUSTOM_DOC("Load and apply the bindings.4coder file from 4coder's default directories (user and image).") {
	if (!nne::dynamic_binding_load_from_file(app, &framework_mapping, Str_U8("bindings.4coder"))) {
		nne::set_default_bindings(&framework_mapping);
		print_message(app, Str_U8("Bindings not loaded\n"));
	}
	nne::set_absolutely_necessary_bindings(&framework_mapping);
}

CUSTOM_COMMAND_SIG(load_bindings_current_buffer)
CUSTOM_DOC("Load and apply the bindings.4coder file from the current buffer.") {
	Scratch_Block scratch(app);
	
	View_ID   view   = get_active_view(app, AccessFlag_Read);
	Buffer_ID buffer = view_get_buffer(app, view, AccessFlag_Read);
	String8   buffer_data = push_whole_buffer(app, scratch, buffer);
	String8   buffer_name = push_buffer_base_name(app, scratch, buffer);
	
	if (!nne::dynamic_binding_load_from_buffer(app, &framework_mapping, buffer_name, buffer_data)) {
		nne::set_default_bindings(&framework_mapping);
		print_message(app, Str_U8("Bindings not loaded\n"));
	}
	nne::set_absolutely_necessary_bindings(&framework_mapping);
}

// NOTE(ema): @Copypaste From 4coder_config.cpp. The only (meaningful) difference is the type of the last parameter.
// TODO(ema): Maybe this overload could be pushed to the community fork.
function Config_Error *
def_config_push_error(Arena *arena, Config_Error_List *list, String_Const_u8 file_name, u8 *pos,
					  String_Const_u8 error_text) {
    Config_Error *error = push_array(arena, Config_Error, 1);
    zdll_push_back(list->first, list->last, error);
    list->count += 1;
    error->file_name = file_name;
    error->pos  = pos;
    error->text = push_string_copy(arena, error_text); // NOTE(ema): Only different line from original procedure.
    return(error);
}

// NOTE(ema): Same as above.
function Config_Error *
def_config_push_error(Arena *arena, Config *config, u8 *pos, String_Const_u8 error_text) {
    return def_config_push_error(arena, &config->errors, config->file_name, pos, error_text);
}

NAMESPACE_BEGIN(nne)

// NOTE(ema): @Copypaste From 4coder_search.cpp's def_search_get_full_path. The only (meaningful)
// difference is that we check if the string already ends in a slash instead of blindly appending it.
// TODO(ema): Maybe this change could be pushed to the community fork.
internal String_Const_u8
search_get_full_path(Arena *arena, List_String_Const_u8 *list, String_Const_u8 relative_name) {
	String_Const_u8 result = {};
	
	Temp_Memory temp = begin_temp(arena);
	for (Node_String_Const_u8 *node = list->first; node != 0; node = node->next) {
		String_Const_u8 full_path = {};
		
		u8  slash = '/';
		b32 should_append_slash = !(node->string.str[node->string.size-1] == slash ||
									node->string.str[node->string.size-1] == '\\');
		
		u64 path_back_size = node->string.size + (should_append_slash ? 1 : 0);
		
		full_path.size = path_back_size + relative_name.size;
		full_path.str = push_array(arena, u8, full_path.size + 1); // Include the null terminator.
		block_copy(full_path.str, node->string.str, path_back_size);
		if (should_append_slash) {
			full_path.str[node->string.size] = slash;
		}
		
		block_copy(full_path.str + path_back_size, relative_name.str, relative_name.size);
		full_path.str[full_path.size] = 0;
		
		File_Attributes attribs = system_quick_file_attributes(arena, full_path);
		if (attribs.last_write_time > 0) {
			result = full_path;
			break;
		}
		
		end_temp(temp);
	}
	
	return result;
}

function b32
dynamic_binding_load_from_buffer(Application_Links *app, Mapping *mapping, String_Const_u8 filename,
								 String_Const_u8 buffer) {
	b32     success = false;
	String8 error_message = {};
	
	Scratch_Block scratch(app);
	
	// NOTE(ema): 'filename' is used to report parsing errors.
	Config *parsed = def_config_from_text(app, scratch, filename, buffer);
	if (parsed != 0) {
		success = true;
	} else {
		error_message = Str_U8("can't parse bindings\n");
	}
	
	if (error_message.str == 0) {
		Thread_Context* tctx = get_thread_context(app);
		mapping_release(tctx, mapping);
		mapping_init(tctx, mapping);
		
		MappingScope();
		SelectMapping(mapping);
		
		for (Config_Assignment *assignment = parsed->first; assignment; assignment = assignment->next) {
			Config_LValue *lvalue = assignment->l;
			
			if (lvalue != 0 && lvalue->index == 0) {
				Config_Get_Result map_rvalue = config_evaluate_rvalue(parsed, assignment, assignment->r);
				
				// NOTE(ema): At global scope, we only care about compounds.
				if (map_rvalue.type == ConfigRValueType_Compound) {
					String_Const_u8 map_name    = lvalue->identifier;
					String_ID       map_name_id = vars_save_string(map_name);
					
					SelectMap(map_name_id);
					
					Config_Compound *compound = map_rvalue.compound;
					
					Config_Get_Result_List list = typed_compound_array_reference_list(scratch, parsed, compound);
					for (Config_Get_Result_Node *node = list.first; node; node = node->next) {
						String_Const_u8 cmd_string    = {};
						String_Const_u8 key_string    = {};
						String_Const_u8 mod_string[9] = {};
						
						// Gather declaration parts:
						{
							Config_Compound *src = node->result.compound;
							if (!config_compound_string_member(parsed, src, "cmd", 0, &cmd_string)) {
								def_config_push_error(scratch, parsed, node->result.pos, "Command string is required in binding");
								goto finish_map;
							}
							if (!config_compound_string_member(parsed, src, "key", 1, &key_string)) {
								def_config_push_error(scratch, parsed, node->result.pos, "Key string is required in binding");
								goto finish_map;
							}
							for (i32 mod_idx = 0; mod_idx < ArrayCount(mod_string); mod_idx += 1) {
								String_Const_u8 str = push_stringf(scratch, "mod_%i", mod_idx);
								if (config_compound_string_member(parsed, src, str, 2 + mod_idx, &mod_string[mod_idx])) {
									Allow_Break();
								}
							}
						}
						
						// Declaration read in successfully: bind it.
						{
							Command_Metadata *command = get_command_metadata_from_name(cmd_string);
							Key_Code keycode = dynamic_binding_key_code_from_string(key_string);
							
							if (command != 0 && keycode != 0) {
								i32 mod_count = 0;
								Key_Code mods[ArrayCount(mod_string)] = {0};
								for (i32 i = 0; i < ArrayCount(mod_string); i += 1) {
									if (mod_string[i].str != 0) {
										mods[mod_count] = dynamic_binding_key_code_from_string(mod_string[i]);
										mod_count += 1;
									}
								}
								
								Input_Modifier_Set mods_set = { mods, mod_count };
								map_set_binding(mapping, map, command->proc, InputEventKind_KeyStroke, keycode, &mods_set);
							} else {
								String8 cmd_message = {};
								String8 key_message = {};
								
								if (command == 0) { cmd_message = push_stringf(scratch, "Command %.*s does not exist", string_expand(cmd_string)); }
								if (keycode == 0) { key_message = push_stringf(scratch, "Invalid key %.*s",            string_expand(key_string)); }
								
								if (cmd_message.str != 0) { def_config_push_error(scratch, parsed, node->result.pos, cmd_message); }
								if (key_message.str != 0) { def_config_push_error(scratch, parsed, node->result.pos, key_message); }
							}
						}
						
						finish_map:;
					}
					
					if (parsed->errors.first != 0) {
						String_Const_u8 error_text = config_stringize_errors(app, scratch, parsed);
						print_message(app, error_text);
					}
				} else {
					// NOTE(ema): Non-compound rvalue at global scope, ignore.
				}
			}
		}
	}
	
	if (error_message.str != 0) {
		print_message(app, error_message);
	}
	
	return success;
}

function b32
dynamic_binding_load_from_file(Application_Links *app, Mapping *mapping, String_Const_u8 filename) {
	b32     success = false;
	String8 error_message = {};
	
	Scratch_Block scratch(app);
	
	// Get full file path.
	String_Const_u8 full_path = {};
	{
		// TODO(ema): Give the ability to specify the
		// desired priority for the folders (executable dir, project dir, user dir).
		
		String8List search_list = {};
		def_search_normal_load_list(scratch, &search_list);
		full_path = nne::search_get_full_path(scratch, &search_list, push_string_copy(scratch, filename));
		// NOTE(ema): The filename is copied so that it's going to have a null-terminator.
		
		{
			String8 message = push_stringf(scratch, "loading bindings: %.*s\n", string_expand(full_path));
			print_message(app, message);
		}
	}
	
	// Read file.
	String_Const_u8 data = {};
	{
		if (full_path.size > 0) {
			File_Name_Data name_and_data = dump_file(scratch, full_path);
			if (name_and_data.data.str != 0) {
				data = name_and_data.data;
			} else {
				error_message = push_stringf(scratch, "can't open file: %.*s\n", string_expand(full_path));
			}
		}
	}
	
	if (error_message.str == 0) {
		success = dynamic_binding_load_from_buffer(app, mapping, filename, data);
	} else {
		print_message(app, error_message);
	}
	
	return success;
}

NAMESPACE_END()

#endif // FCODER_CUSTOM_BINDINGS_CPP
