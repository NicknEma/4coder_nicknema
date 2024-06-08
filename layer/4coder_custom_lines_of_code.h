#ifndef FCODER_CUSTOM_LINES_OF_CODE_H
#define FCODER_CUSTOM_LINES_OF_CODE_H

namespace nne {
	
	struct Lines_Of_Code_Info {
		Lines_Of_Code_Info *next;
		String_Const_u8 name;
		i64 lines;
		i64 whitespace_only_lines;
		i64 open_brace_only_lines;
	};
	
	function Lines_Of_Code_Info *lines_of_code_from_buffer(Application_Links *app, Arena *arena, Buffer_ID buffer);
	function int compare_lines_of_code(const void *a_void, const void *b_void); // For qsort
}

CUSTOM_COMMAND_SIG(count_lines_of_code);

#endif // FCODER_CUSTOM_LINES_OF_CODE_H
