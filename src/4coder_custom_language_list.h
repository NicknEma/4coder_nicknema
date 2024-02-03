#ifndef FCODER_CUSTOM_LANGUAGE_LIST_H
#define FCODER_CUSTOM_LANGUAGE_LIST_H

// Include language files here.
#include "generated/4coder_custom_lexer_jai.h"
#include "generated/4coder_custom_lexer_jai.cpp"
#include "generated/4coder_custom_lexer_odin.h"
#include "generated/4coder_custom_lexer_odin.cpp"

#include "4coder_custom_lang_cpp.cpp"
#include "4coder_custom_lang_jai.cpp"
#include "4coder_custom_lang_odin.cpp"
#include "4coder_custom_lang_metadesk.cpp"

NAMESPACE_BEGIN(nne)

// This procedure just calls register_language for each implemented language.
procedure void register_languages(void) {
    // C/C++.
    {
        String_Const_u8 extensions[] = {
            S8Lit("cpp"), S8Lit("cc"), S8Lit("c"), S8Lit("cxx"),
            S8Lit("C"), S8Lit("h"), S8Lit("hpp"),
        };
		
        for (int i = 0; i < ArrayCount(extensions); i += 1) {
            register_language(extensions[i],
							  F4_CPP_IndexFile,
							  lex_full_input_cpp_init,
							  lex_full_input_cpp_breaks,
							  F4_CPP_PosContext,
							  F4_CPP_Highlight,
							  Lex_State_Cpp);
        }
    }
    
    // Jai.
    {
        register_language(S8Lit("jai"),
						  F4_Jai_IndexFile,
						  lex_full_input_jai_init,
						  lex_full_input_jai_breaks,
						  F4_Jai_PosContext,
						  F4_Jai_Highlight,
						  Lex_State_Jai);
    }
    
    // Odin.
    {
        register_language(S8Lit("odin"),
						  odin__index_file,
						  lex_full_input_odin_init,
						  lex_full_input_odin_breaks,
						  odin__get_positional_context,
						  odin__highlight,
						  Lex_State_Odin);
    }
    
    // Metadesk.
    {
        String_Const_u8 extensions[] = {
            // TODO(rjf): Maybe find a config-driven way to specify these? "mc" was sort of
            // introduced ad-hoc...
            S8Lit("md"), S8Lit("mc"), S8Lit("metacode"), S8Lit("meta"), S8Lit("metadesk"),
        };
		
        for (int i = 0; i < ArrayCount(extensions); i += 1) {
            register_language(extensions[i],
							  metadesk__index_file,
							  lex_full_input_cpp_init,
							  lex_full_input_cpp_breaks,
							  metadesk__get_positional_context,
							  metadesk__highlight,
							  Lex_State_Cpp);
        }
    }
}

NAMESPACE_END()

#endif // FCODER_CUSTOM_LANGUAGE_LIST_H
