#ifndef FCODER_NICKNEMA_LANGUAGES_H
#define FCODER_NICKNEMA_LANGUAGES_H

// @Note(ema): Defined in "index.h"
struct F4_Index_ParseCtx;
struct F4_Index_Note;

NAMESPACE_BEGIN(nicknema)

//
// @Doc(ema): Indexes an entire file of a language and adds stuff to the code index.
#define FILE_INDEXER(name) void name(F4_Index_ParseCtx *ctx)
typedef FILE_INDEXER(File_Indexer);

//
// @Doc(ema): Initializes lexer state. Only used for hand-written lexers.
#define LEXER_INITTER(name) void name(void *state_ptr, String_Const_u8 contents)
typedef LEXER_INITTER(Lexer_Initter);

//
// Lexes an entire file to produce tokens for the language (with breaks). Only used for hand-written lexers.
#define LEXER(name) b32 name(Arena *arena, Token_List *list, void *state_ptr, u64 max)
typedef LEXER(Lexer);

//
// @Doc(ema): Figures out some language-specific contextual information given some position in a buffer. For example, what type I am accessing, what function I am calling, which parameter am I accessing, etc.
struct Positional_Context_Data {
    Positional_Context_Data *next;
    F4_Index_Note *relevant_note;
    Token *query_token;
    int argument_index;
};
#define POSITIONAL_CONTEXT_GETTER(name) Positional_Context_Data *name(Application_Links *app, Arena *arena, Buffer_ID buffer, i64 pos)
typedef POSITIONAL_CONTEXT_GETTER(Positional_Context_Getter);

//
// @Doc(ema): Does language-specific coloring for a buffer, for special-case syntax highlighting and stuff. Most syntax highlighting is handled through token-base-kinds and index lookups, but sometimes it's useful to be able to override colors by language-specific token sub-kinds and flags, so that's what this hook is for.
#define LANGUAGE_HIGHLIGHTER(name) void name(Application_Links *app, Text_Layout_ID text_layout_id, Token_Array *array, Color_Table color_table)
typedef LANGUAGE_HIGHLIGHTER(Language_Highlighter);

//~

struct Language {
    Language *next;
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
struct Language_System_State {
    b32       initialized;
    Arena     arena;
    Language *language_table[4096];
};

// @Doc(ema): Given a language name, searches for it in the global language table.
function Language *language_from_string(String_Const_u8 name);

// @Doc(ema): Given a code buffer, returns its language.
function Language *language_from_buffer(Application_Links *app, Buffer_ID buffer);

// @Doc(ema): You call this procedure for each language that needs to be recognized by the editor.
procedure void register_language(String_Const_u8            name,
                                 File_Indexer              *file_indexer,
                                 Lexer_Initter             *lexer_initter,
                                 Lexer                     *lexer,
                                 Positional_Context_Getter *context_getter,
                                 Language_Highlighter      *highlighter,
                                 u64                        lex_state_size);

procedure Token_List lex_full_input_no_breaks(Application_Links *app, Language *language, Arena *arena, String_Const_u8 text);

NAMESPACE_END()

#endif // FCODER_NICKNEMA_LANGUAGES_H
