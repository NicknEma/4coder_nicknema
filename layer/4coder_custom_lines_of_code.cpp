#ifndef FCODER_CUSTOM_LINES_OF_CODE_CPP
#define FCODER_CUSTOM_LINES_OF_CODE_CPP

//~ Lines of Code

namespace nne {
	
	function Lines_Of_Code_Info *lines_of_code_from_buffer(Application_Links *app, Arena *arena, Buffer_ID buffer) {
		Lines_Of_Code_Info *first = 0;
		Lines_Of_Code_Info *last  = 0;
		
		Lines_Of_Code_Info *file_info = push_array_zero(arena, Lines_Of_Code_Info, 1);
		sll_queue_push(first, last, file_info);
		file_info->name = str8_lit("all");
		Lines_Of_Code_Info *active_info = 0;
		
		i64 line_count = buffer_get_line_count(app, buffer);
		for (i64 line_idx = 0; line_idx < line_count; line_idx += 1) {
			Scratch_Block scratch(app, arena);
			String_Const_u8 line = push_buffer_line(app, scratch, buffer, line_idx);
			if (line.size != 0 && line.str[line.size - 1] == '\r') {
				line.size -= 1;
			}
			
			// Begin a section if we find a root divider comment here
			char local_strong_divider_comment_signifier = '~'; // @Todo: Use the global one? Why isn't this using the global one?
			if (line.size >= 3 && line.str[0] == '/' && line.str[1] == '/' && line.str[2] == local_strong_divider_comment_signifier) {
				active_info = push_array_zero(arena, Lines_Of_Code_Info, 1);
				active_info->name = push_string_copy(arena, string_substring(line, Ii64(3, line.size)));
				sll_queue_push(first, last, active_info);
			}
			
			// Find out if this is a line with only whitespace
			b32 is_only_whitespace = true;
			{
				for (u64 i = 0; i < line.size; i += 1) {
					if (!character_is_whitespace(line.str[i])) {
						is_only_whitespace = false;
						break;
					}
				}
			}
			
			// Find out if this is a line with only whitespace and an open brace
			b32 is_only_open_brace = false;
			if (is_only_whitespace == false) {
				for (u64 i = 0; i < line.size; i += 1) {
					if (!character_is_whitespace(line.str[i])) {
						is_only_open_brace = line.str[i] == '{';
						if (!is_only_open_brace) {
							break;
						}
					}
				}
			}
			
			// Increment line counts
			{
				file_info->lines += 1;
				if (active_info) {
					active_info->lines += 1;
				}
				
				if (is_only_whitespace) {
					file_info->whitespace_only_lines += 1;
					if (active_info) {
						active_info->whitespace_only_lines += 1;
					}
				}
				
				if (is_only_open_brace) {
					file_info->open_brace_only_lines += 1;
					if (active_info) {
						active_info->open_brace_only_lines += 1;
					}
				}
			}
		}
		
		return first;
	}
	
	function int compare_lines_of_code(const void *a_void, const void *b_void) {
		nne::Lines_Of_Code_Info *a = cast(nne::Lines_Of_Code_Info *)a_void;
		nne::Lines_Of_Code_Info *b = cast(nne::Lines_Of_Code_Info *)b_void;
		
		int result = ((a->lines < b->lines) ? +1 : (a->lines > b->lines) ? -1 : 0);
		return result;
	}
	
}

CUSTOM_COMMAND_SIG(count_lines_of_code)
CUSTOM_DOC("Counts the lines of code in the current buffer, breaks it down by section, and outputs to the *loc* buffer.") {
	Scratch_Block scratch(app);
	using nne::Lines_Of_Code_Info;
	
    View_ID   view   = get_active_view(app, Access_Read);
    Buffer_ID buffer = view_get_buffer(app, view, Access_Read);
    
    // Get all sections and counts from buffer
    Lines_Of_Code_Info *infos_list = nne::lines_of_code_from_buffer(app, scratch, buffer);
    
    // Build unsorted info in array form
    int info_count = 0;
    Lines_Of_Code_Info *info_array = 0;
    {
        for (Lines_Of_Code_Info *info = infos_list; info; info = info->next) {
			info_count += 1;
		}
        info_array = push_array_zero(scratch, Lines_Of_Code_Info, info_count);
		
        int info_index = 0;
        for (Lines_Of_Code_Info *info = infos_list; info; info = info->next) {
            info_array[info_index] = *info;
			info_index += 1;
        }
    }
    
    // Sort array
    qsort(info_array, info_count, sizeof(Lines_Of_Code_Info), nne::compare_lines_of_code);
    
    //- Do the printing
    Buffer_ID loc_buffer = get_buffer_by_name(app, str8_lit("*loc*"), AccessFlag_Write);
    if (loc_buffer) {
        clear_buffer(app, loc_buffer);
        
        for (int info_index = 0; info_index < info_count; info_index += 1) {
            Lines_Of_Code_Info *info = &info_array[info_index];
            
            int padding = 25; // @Cleanup: Magic numbers eyyyy
            int chrs    = cast(int)info->name.size;
            int spaces  = 0;
            if (chrs > padding) {
                chrs = padding;
                spaces = 0;
            } else {
                spaces = padding - chrs;
            }
            
            if (spaces < 0) {
                spaces = 0;
            }
            
			Scratch_Block scratch2(app, scratch);
            String_Const_u8 string = push_stringf(scratch2,
                                                  ">>> %.*s%.*s: %6i lines; %6i whitespace; %6i open braces; %6i significant\n",
                                                  chrs, info->name.str,
                                                  spaces, "                                            ",
                                                  cast(int)info->lines,
                                                  cast(int)info->whitespace_only_lines,
                                                  cast(int)info->open_brace_only_lines,
                                                  cast(int)(info->lines - (info->whitespace_only_lines+info->open_brace_only_lines)));
            b32 write_successful = buffer_replace_range(app, loc_buffer, Ii64(buffer_get_size(app, loc_buffer)), string);
            (void)write_successful;
        }
    }
}

#endif // FCODER_CUSTOM_LINES_OF_CODE_CPP
