#ifndef FCODER_CUSTOM_DYNAMIC_BINDINGS
#define FCODER_CUSTOM_DYNAMIC_BINDINGS

NAMESPACE_BEGIN(nne)

// @Copypaste(ema): From 4coder_search.cpp's def_search_get_full_path
// The only (meaningful) difference is that we check if the string already ends in a slash instead of blindly appending it.
// @Note(ema): I don't know what the def_ prefix stands for.
internal String_Const_u8 search_get_full_path(Arena *arena, List_String_Const_u8 *list, String_Const_u8 relative_name) {
    String_Const_u8 result = {};
    
    Temp_Memory temp = begin_temp(arena);
    
    u8 slash = '/';
    
    for (Node_String_Const_u8 *node = list->first; node; node = node->next) {
        String_Const_u8 full_path = {};
        
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
        if (attribs.last_write_time > 0){
            result = full_path;
            break;
        }
        
        end_temp(temp);
    }
    
    return result;
}

// @Copypaste(ema): From 4coder_dynamic_bindings.cpp
// The only (meaningful) difference is the call to a different version def_search_get_full_path() that checks for a backslash before inserting one. This fix might not be necessary if we switch to a community-maintained fork of 4coder that solves it. If it still isn't solved, we could push the change ourselves.
internal b32 dynamic_binding_load_from_file(Application_Links *app, Mapping *mapping, String_Const_u8 filename) {
    b32 result = false;
    
    Scratch_Block scratch(app);
    
    String_Const_u8 filename_copied = push_string_copy(scratch, filename);
    String8List search_list = {};
    def_search_normal_load_list(scratch, &search_list);
    String_Const_u8 full_path = nne::search_get_full_path(scratch, &search_list, filename_copied);
    
    {
        String8 message = push_stringf(scratch, "loading bindings: %.*s\n", string_expand(full_path));
        print_message(app, message);
    }
    
    FILE *file = 0;
    if (full_path.size > 0){
        file = fopen((char*)full_path.str, "rb");
    }
    
    if (file) {
        String_Const_u8 data = dump_file_handle(scratch, file);
        Config *parsed = def_config_from_text(app, scratch, filename, data);
		fclose(file);
        // @Cleanup(ema): Decouple the two: make one that takes just the contents string, and a wrapper that takes the filename and then call the other. Also give the ability to specify the desired priority for the folders (executable dir, project dir, user dir).
		
        if (parsed) {
            result = true;
            
			Thread_Context* tctx = get_thread_context(app);
			mapping_release(tctx, mapping);
			mapping_init(tctx, mapping);
			
			MappingScope();
			SelectMapping(mapping);
            
            for (Config_Assignment *assignment = parsed->first; assignment; assignment = assignment->next) {
                Config_LValue *l = assignment->l;
                if (l != 0 && l->index == 0) {
                    Config_Get_Result rvalue = config_evaluate_rvalue(parsed, assignment, assignment->r);
                    if (rvalue.type == ConfigRValueType_Compound) {
                        String_Const_u8 map_name = l->identifier;
                        String_ID map_name_id = vars_save_string(map_name);
                        
                        SelectMap(map_name_id);
                        
                        Config_Compound *compound = rvalue.compound;
                        
                        Config_Get_Result_List list = typed_compound_array_reference_list(scratch, parsed, compound);
                        for (Config_Get_Result_Node *node = list.first; node; node = node->next) {
                            Config_Compound *src = node->result.compound;
                            String_Const_u8 cmd_string = {0};
                            String_Const_u8 key_string = {0};
                            String_Const_u8 mod_string[9] = {0};
                            
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
                                    // NOTE(rjf): No-Op
                                }
                            }
                            
                            // NOTE(rjf): Map read in successfully.
                            {
                                // NOTE(rjf): Find command.
                                Command_Metadata *command = get_command_metadata_from_name(cmd_string);
                                
                                // NOTE(rjf): Find keycode.
                                Key_Code keycode = dynamic_binding_key_code_from_string(key_string);
                                
                                // NOTE(rjf): Find mods.
                                i32 mod_count = 0;
                                Key_Code mods[ArrayCount(mod_string)] = {0};
                                for (i32 i = 0; i < ArrayCount(mod_string); i += 1) {
                                    if (mod_string[i].str) {
                                        mods[mod_count] = dynamic_binding_key_code_from_string(mod_string[i]);
                                        mod_count += 1;
                                    }
                                }
                                
                                if (keycode != 0 && command != 0) {
                                    Input_Modifier_Set mods_set = { mods, mod_count, };
                                    map_set_binding(mapping, map, command->proc, InputEventKind_KeyStroke, keycode, &mods_set);
                                } else {
                                    def_config_push_error(scratch, parsed, node->result.pos,
                                                          (keycode != 0) ? (char*)"Invalid command" :
                                                          (command != 0) ? (char*)"Invalid key":
                                                          (char*)"Invalid command and key");
                                }
                            }
                            
                            finish_map:;
                        }
                        
                        
                        if (parsed->errors.first != 0) {
                            String_Const_u8 error_text = config_stringize_errors(app, scratch, parsed);
                            print_message(app, error_text);
                        }
                    }
                }
            }
        }
    }
    
    return result;
}

NAMESPACE_END()

#endif // FCODER_CUSTOM_DYNAMIC_BINDINGS
