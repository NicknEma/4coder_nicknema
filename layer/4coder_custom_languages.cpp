#ifndef FCODER_CUSTOM_LANGUAGES_CPP
#define FCODER_CUSTOM_LANGUAGES_CPP

NAMESPACE_BEGIN(nne)

global F4_Language_State f4_langs = {};

// Given a language name, searches for it in the global language table.
internal F4_Language *language_from_string(String_Const_u8 name) {
    F4_Language *result = 0;
    if (f4_langs.initialized) {
        u64 hash = table_hash_u8(name.str, name.size);
        u64 slot = hash % ArrayCount(f4_langs.language_table);
        for (F4_Language *l = f4_langs.language_table[slot]; l; l = l->next) {
            if (l->hash == hash && string_match(l->name, name)) {
                result = l;
                break;
            }
        }
    }
    return result;
}

// Given a code buffer, returns its language.
internal F4_Language *language_from_buffer(Application_Links *app, Buffer_ID buffer) {
    F4_Language *language = 0;
    Scratch_Block scratch(app);
    String_Const_u8 file_name = push_buffer_file_name(app, scratch, buffer);
    String_Const_u8 extension = string_file_extension(file_name);
    language = language_from_string(extension);
    return language;
}

#define register_language(name, IndexFile, LexInit, LexFullInput, PosContext, Highlight, lex_state_type) register_language_(name, IndexFile, (Lexer_Initter *)LexInit, (Lexer *)LexFullInput, (Positional_Context_Getter *)PosContext, (Language_Highlighter *)Highlight, sizeof(lex_state_type))

// You call this procedure for each language that needs to be recognized by the editor.
internal void register_language_(String_Const_u8 name,
								 File_Indexer              *file_indexer,
								 Lexer_Initter             *lexer_initter,
								 Lexer                     *lexer,
								 Positional_Context_Getter *context_getter,
								 Language_Highlighter      *highlighter,
								 u64 lex_state_size) {
    if (f4_langs.initialized == 0) {
        f4_langs.initialized = 1;
        f4_langs.arena = make_arena_system(KB(16));
    }
    
    F4_Language *language = 0;
    u64 hash = table_hash_u8(name.str, name.size);
    u64 slot = hash % ArrayCount(f4_langs.language_table);
    for (F4_Language *l = f4_langs.language_table[slot]; l; l = l->next) {
        if (l->hash == hash && string_match(l->name, name)) {
            language = l;
            break;
        }
    }
    
    if (language == 0) {
        language = push_array(&f4_langs.arena, F4_Language, 1);
        language->next = f4_langs.language_table[slot];
        f4_langs.language_table[slot] = language;
        language->hash = hash;
        language->name = push_string_copy(&f4_langs.arena, name);
        language->lex_state_size     = lex_state_size;
        language->file_indexer       = file_indexer;
        language->lexer_initter      = lexer_initter;
        language->lexer              = lexer;
		language->context_getter     = context_getter;
        language->highlighter        = highlighter;
    }
}

internal void F4_Language_PosContext_PushData(Arena *arena, Positional_Context_Data **first_ptr, Positional_Context_Data **last_ptr, Index__Note *note, Token *query, int arg_index) {
	Positional_Context_Data *first = *first_ptr;
	Positional_Context_Data *last = *last_ptr;
	Positional_Context_Data *func = push_array_zero(arena, Positional_Context_Data, 1);
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

internal void F4_Language_PosContext_PushData_Call(Arena *arena, Positional_Context_Data **first_ptr, Positional_Context_Data **last_ptr, String_Const_u8 string, int param_idx) {
    Index__Note *note = index__lookup_note(string, 0);
	F4_Language_PosContext_PushData(arena, first_ptr, last_ptr, note, 0, param_idx);
}

internal void F4_Language_PosContext_PushData_Dot(Arena *arena, Positional_Context_Data **first_ptr, Positional_Context_Data **last_ptr, String_Const_u8 string, Token *query) {
	Index__Note *note = index__lookup_note(string, 0);
    F4_Language_PosContext_PushData(arena, first_ptr, last_ptr, note, query, 0);
}

internal Token_List F4_Language_LexFullInput_NoBreaks(Application_Links *app, F4_Language *language, Arena *arena, String_Const_u8 text) {
    Token_List list = {};
    if (language != 0) {
        Scratch_Block scratch(app, arena);
        void *state = push_array_zero(scratch, u8, language->lex_state_size);
		language->lexer_initter(state, text);
        language->lexer(arena, &list, state, max_u64);
    }
    return list;
}

NAMESPACE_END()

#endif // FCODER_CUSTOM_LANGUAGES_CPP

#include "4coder_custom_language_list.h"
