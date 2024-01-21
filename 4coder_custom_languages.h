#ifndef FCODER_CUSTOM_LANGUAGES_H
#define FCODER_CUSTOM_LANGUAGES_H

NAMESPACE_BEGIN(nne)

struct F4_Index_ParseCtx;

//~ NOTE(rjf): Indexes an entire file of a language and adds stuff to the code index.
#define FILE_INDEXER(name) void name(F4_Index_ParseCtx *ctx)
typedef FILE_INDEXER(File_Indexer);

//~ NOTE(rjf): Initializes lexer state.
// Only used for hand-written lexers.
#define LEXER_INITTER(name) void name(void *state_ptr, String_Const_u8 contents)
typedef LEXER_INITTER(Lexer_Initter);

//~ NOTE(rjf): Lexes an entire file to produce tokens for the language (with breaks).
// Only used for hand-written lexers.
#define LEXER(name) b32 name(Arena *arena, Token_List *list, void *state_ptr, u64 max)
typedef LEXER(Lexer);

//~ NOTE(rjf): Figures out some language-specific contextual information given some
// position in a buffer. For example, what type I am accessing, what function I am
// calling which parameter am I accessing, etc.

struct F4_Index_Note;
struct Positional_Context_Data {
    Positional_Context_Data *next;
    F4_Index_Note *relevant_note;
    Token *query_token;
    int argument_index;
};
#define POSITIONAL_CONTEXT_GETTER(name) Positional_Context_Data *name(Application_Links *app, Arena *arena, Buffer_ID buffer, i64 pos)
typedef POSITIONAL_CONTEXT_GETTER(Positional_Context_Getter);

//~ NOTE(rjf): Does language-specific coloring for a buffer, for special-case syntax
// highlighting and stuff. Most syntax highlighting is handled through token-base-kinds
// and index lookups, but sometimes it's useful to be able to override colors by
// language-specific token sub-kinds and flags, so that's what this hook is for.
#define LANGUAGE_HIGHLIGHTER(name) void name(Application_Links *app, Text_Layout_ID text_layout_id, Token_Array *array, Color_Table color_table)
typedef LANGUAGE_HIGHLIGHTER(Language_Highlighter);

//~

struct F4_Language {
    F4_Language *next;
    u64 hash;
    String_Const_u8 name;
    u64 lex_state_size;
	
    File_Indexer              *file_indexer;
    Lexer_Initter             *lexer_initter;
    Lexer                     *lexer;
    Positional_Context_Getter *context_getter;
    Language_Highlighter      *highlighter;
};

// @Note(ema): Only ONE of these stores the state for all the languages.
struct F4_Language_State {
    b32 initialized;
    Arena arena;
    F4_Language *language_table[4096];
};

NAMESPACE_END()

#endif // FCODER_CUSTOM_LANGUAGES_H
