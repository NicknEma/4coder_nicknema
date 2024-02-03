#ifndef FCODER_RFLEURY_LANG_CPP
#define FCODER_RFLEURY_LANG_CPP

NAMESPACE_BEGIN(nicknema)

global Language_System_State language_system_state_ = {}; // @Rename(ema).

function Language *language_from_string(String_Const_u8 name) {
    Language *result = 0;
    
    if (language_system_state_.initialized) {
        u64 hash = table_hash_u8(name.str, name.size);
        u64 slot = hash % ArrayCount(language_system_state_.language_table);
        for (Language *l = language_system_state_.language_table[slot]; l; l = l->next) {
            if (l->hash == hash && string_match(l->name, name)) {
                result = l;
                break;
            }
        }
    }
    
    return result;
}

function Language *language_from_buffer(Application_Links *app, Buffer_ID buffer) {
    Language *language = 0;
    
    Scratch_Block scratch(app);
    String_Const_u8 file_name = push_buffer_file_name(app, scratch, buffer);
    String_Const_u8 extension = string_file_extension(file_name);
    language = language_from_string(extension);
    
    return language;
}

procedure void register_language(String_Const_u8            name,
                                 File_Indexer              *file_indexer,
                                 Lexer_Initter             *lexer_initter,
                                 Lexer                     *lexer,
                                 Positional_Context_Getter *context_getter,
                                 Language_Highlighter      *highlighter,
                                 u64                        lex_state_size) {
    if (!language_system_state_.initialized) {
        language_system_state_.arena = make_arena_system(KB(16));
        language_system_state_.initialized = true;
    }
    
    Language *language = 0;
    u64 hash = table_hash_u8(name.str, name.size);
    u64 slot = hash % ArrayCount(language_system_state_.language_table);
    for (Language *l = language_system_state_.language_table[slot]; l; l = l->next) {
        if (l->hash == hash && string_match(l->name, name)) {
            // @Note(ema): If the language is already in the language table, stop.
            language = l;
            break;
        }
    }
    
    // @Note(ema): If no language was found, make one.
    if (!language) {
        language = push_array(&language_system_state_.arena, Language, 1);
        language->next = language_system_state_.language_table[slot];
        language_system_state_.language_table[slot] = language;
        language->hash = hash;
        
        language->name           = push_string_copy(&language_system_state_.arena, name);
        language->lex_state_size = lex_state_size;
        language->file_indexer   = file_indexer;
        language->lexer_initter  = lexer_initter;
        language->lexer          = lexer;
		language->context_getter = context_getter;
        language->highlighter    = highlighter;
    }
}

procedure Token_List lex_full_input_no_breaks(Application_Links *app, Language *language, Arena *arena, String_Const_u8 text) {
    Token_List list = {};
    
    if (language != 0) {
        Scratch_Block scratch(app, arena);
        void *state = push_array_zero(scratch, u8, language->lex_state_size);
        
		language->lexer_initter(state, text);
        language->lexer(arena, &list, state, max_u64);
    }
    
    return list;
}

// @Note(ema): I think this is for tooltips and stuff like that.
#if 0
internal void Language_PosContext_PushData(Arena *arena, Language_PosContextData **first_ptr, Language_PosContextData **last_ptr, F4_Index_Note *note, Token *query, int arg_index) {
    Language_PosContextData *first = *first_ptr;
    Language_PosContextData *last = *last_ptr;
    Language_PosContextData *func = push_array_zero(arena, Language_PosContextData, 1);
    func->relevant_note = note;
    func->query_token = query;
    func->argument_index = arg_index;
    if (last == 0) {
        first = last = func;
    } else {
        last->next = func;
        last = last->next;
    }
    *first_ptr = first;
    *last_ptr = last;
}

procedure void Language_PosContext_PushData_Call(Arena *arena, Language_PosContextData **first_ptr, Language_PosContextData **last_ptr, String_Const_u8 string, int param_idx) {
    Language_PosContext_PushData(arena, first_ptr, last_ptr, F4_Index_LookupNote(string, 0), 0, param_idx);
}

procedure void Language_PosContext_PushData_Dot(Arena *arena, Language_PosContextData **first_ptr, Language_PosContextData **last_ptr, String_Const_u8 string, Token *query) {
    Language_PosContext_PushData(arena, first_ptr, last_ptr, F4_Index_LookupNote(string, 0), query, 0);
}
#endif

NAMESPACE_END()

#endif // FCODER_RFLEURY_LANG_CPP
