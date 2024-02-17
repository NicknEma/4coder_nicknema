
// TOP

/*
* @TODO(ema):

* FEATURES:
* Cursor as a line
* c++ and odin syntax highlighting
  *  recursively walk imports/includes, record types, macros, constants, procedures, global variables.
* Multiline editing
* Peek definition
* Don't auto-indent comments

* COMMANDS:
* build/run command in opposite panel binding
* Numpad ascii codes

* BINDINGS:
* vsplit and hsplit

Tutorial:
https://4coder.handmade.network/forums/articles/t/7319-customization_layer_-_getting_started__4coder_4.1_
*/

#ifndef FCODER_NICKNEMA_CPP
#define FCODER_NICKNEMA_CPP

#include <stdlib.h>
#include <string.h>
#include "4coder_default_include.cpp"

#include "4coder_nicknema_basic.h"
#include "4coder_nicknema_languages.h"
#include "4coder_fleury_index.h"

#include "4coder_nicknema_basic.cpp"
#include "4coder_nicknema_languages.cpp"
#include "4coder_fleury_index.cpp"

// #include "4coder_fleury_lang_cpp.cpp"
// #include "4coder_fleury_lang_jai.cpp"

#include "4coder_nicknema_odin.cpp"

#include "4coder_nicknema_hooks.cpp"
#include "4coder_nicknema_bindings.cpp"

#if !defined(META_PASS)
# include "generated/managed_id_metadata.cpp"
#endif

#if OS_MAC
# define Setup_Default_Mapping(mapping, global_map_id, file_map_id, code_map_id)     setup_mac_mapping(mapping, global_map_id, file_map_id, code_map_id);
#else
# define Setup_Default_Mapping(mapping, global_map_id, file_map_id, code_map_id) setup_default_mapping(mapping, global_map_id, file_map_id, code_map_id);
#endif

// @Doc(ema): The custom layer entry point.
void custom_layer_init(Application_Links *app) {
    default_framework_init(app);
    
    {
        // Setup Hooks. Hooks are the links that the editor has to custom functionality implementation. For example, the rendering loop. They have default values but they can be overwritten.
        
        set_all_default_hooks(app);
        
        // @Note(ema): Now overwrite the hooks we want to change.
        set_custom_hook(app, HookID_RenderCaller, render_caller);
        set_custom_hook(app, HookID_Tick, fleury_tick);
        set_custom_hook(app, HookID_BeginBuffer, F4_BeginBuffer);
    }
    
    {
        // Setup Mappings.
        
        Thread_Context *thread_context = get_thread_context(app);
        mapping_init(thread_context, &framework_mapping);
        
        String_ID global_map_id = vars_save_string_lit("keys_global");
        String_ID file_map_id   = vars_save_string_lit("keys_file");
        String_ID code_map_id   = vars_save_string_lit("keys_code");
        
        Setup_Default_Mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
        setup_essential_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
        
        // Custom mapping.
        MappingScope();
        SelectMapping(&framework_mapping);
        
        SelectMap(global_map_id);
        
        BindCore(nicknema_startup, CoreCode_Startup);
    }
    
    {
        F4_Index_Initialize();
    }
    
    {
        // Register languages to the language system. This allows them to access the index.
        using namespace nicknema;
        
        {
            // C/C++.
            String_Const_u8 extensions[] = {
                str8_lit("cpp"), str8_lit("cc"), str8_lit("c"), str8_lit("cxx"),
                str8_lit("C"), str8_lit("h"), str8_lit("hpp"),
            };
            
            for (int i = 0; i < ArrayCount(extensions); i += 1) {
#if 0
                register_language(extensions[i],
                                  F4_CPP_IndexFile,
                                  lex_full_input_cpp_init,
                                  lex_full_input_cpp_breaks,
                                  F4_CPP_GetPositionalContext,
                                  F4_CPP_Highlight,
                                  sizeof(Lex_State_Cpp));
#endif
            }
        }
        
        {
            // Odin.
            String_Const_u8            name           = Str_U8("odin");
            File_Indexer              *file_indexer   = odin__index_file;
            Lexer_Initter             *lexer_initter  = cast(Lexer_Initter *)lex_full_input_odin_init;
            Lexer                     *lexer          = cast(Lexer *)lex_full_input_odin_breaks;
            Positional_Context_Getter *context_getter = odin__get_positional_context;
            Language_Highlighter      *highlighter    = odin__highlight;
            u64                        lex_state_size = sizeof(Lex_State_Odin);
            
            register_language(name, file_indexer, lexer_initter, lexer, context_getter, highlighter, lex_state_size);
        }
    }
}

#endif // FCODER_NICKNEMA_CPP

// BOTTOM
