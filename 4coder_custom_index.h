#ifndef FCODER_CUSTOM_INDEX_H
#define FCODER_CUSTOM_INDEX_H

NAMESPACE_BEGIN(nne)

enum Index__Note_Kind {
    Index__Note_Kind_Null,
    Index__Note_Kind_Scope,
    Index__Note_Kind_Type,
    Index__Note_Kind_Constant,
    Index__Note_Kind_Function,
    Index__Note_Kind_Decl,
    Index__Note_Kind_Macro,
    Index__Note_Kind_Comment_Tag,
    Index__Note_Kind_Comment_ToDo,
    Index__Note_Kind_COUNT
};

typedef u32 Index__Note_Flags;
enum {
    Index__Note_Flag_Prototype    = (1<<0),
    Index__Note_Flag_Product_Type = (1<<1),
    Index__Note_Flag_Sum_Type     = (1<<2),
};

struct Index__File;

struct Index__Note {
    Index__Note *next;
    Index__Note *prev;
    Index__Note *hash_next;
	Index__Note *hash_prev;
    Index__Note *parent;
    Index__Note *next_sibling;
    Index__Note *prev_sibling;
    Index__Note *first_child;
    Index__Note *last_child;
    
    u64               hash;
    String_Const_u8   string;
    Index__Note_Kind  kind;
    Index__Note_Flags flags;
    Range_i64         range;
    Index__File      *file;
	int file_generation;
};

struct Index__File {
    Index__File *hash_next;
    Arena        arena;
    Buffer_ID    buffer;
    Index__Note *first_note;
    Index__Note *last_note;
	int generation;
};

struct Index__State {
    System_Mutex mutex;
    Arena        arena;
    Index__Note *note_table[16384];
	Index__Note *free_note;
    Index__File *file_table[16384];
    Index__File *free_file;
};

struct Index__Parse_Context {
    b32                  done;
    Application_Links   *app;
    Index__File         *file;
    String_Const_u8      string;
    Token_Array          tokens;
    Token_Iterator_Array it;
    Index__Note         *active_parent;
};

typedef u32 Index__Token_Skip_Flags;
enum {
    Index__Token_Skip_Flag_Skip_Whitespace = (1<<0),
};

function void index__initialize(void);
function void index__lock(void);
function void index__unlock(void);

function String_Const_u8 index__string_from_range(Index__Parse_Context *context, Range_i64 range);
function String_Const_u8 index__string_from_token(Index__Parse_Context *context, Token *token);

function Index__File *index__lookup_file(Application_Links *app, Buffer_ID buffer);
function Index__File *index__lookup_or_make_file(Application_Links *app, Buffer_ID buffer);
function void index__erase_file(Application_Links *app, Buffer_ID id);
function void index__clear_file(Index__File *file);

function Index__Note *index__lookup_note(String_Const_u8 string, Index__Note *parent);
function Index__Note *index__lookup_note(String_Const_u8 string);
function Index__Note *index__allocate_note(void);
function void index__insert_note(Index__Parse_Context *context, Index__Note *note, Range_i64 name_range, Index__Note_Kind note_kind, Index__Note_Flags note_flags);
function Index__Note *index__make_note(Index__Parse_Context *context, Range_i64 name_range, Index__Note_Kind note_kind, Index__Note_Flags note_flags);
function Index__Note *index__push_parent_note(Index__Parse_Context *context, Index__Note *new_parent);
function void index__pop_parent_note(Index__Parse_Context *context, Index__Note *last_parent);

function void index__parse_file(Application_Links *app, Index__File *file, String_Const_u8 string, Token_Array tokens);
function b32 index__parse_context_inc(Index__Parse_Context *context, Index__Token_Skip_Flags flags);
function b32 index__require_token(Index__Parse_Context *context, String_Const_u8 string, Index__Token_Skip_Flags flags);
function b32 index__require_token_kind(Index__Parse_Context *context, Token_Base_Kind kind, Token **token_out, Index__Token_Skip_Flags flags);
function b32 index__require_token_subkind(Index__Parse_Context *context, int sub_kind, Token **token_out, Index__Token_Skip_Flags flags);
function b32 index__peek_token(Index__Parse_Context *context, String_Const_u8 string);
function b32 index__peek_token_kind(Index__Parse_Context *context, Token_Base_Kind kind, Token **token_out);
function void index__parse_comment(Index__Parse_Context *context, Token *token);
function void index__skip_soft_tokens(Index__Parse_Context *context, b32 preproc);
function void index__skip_operators(Index__Parse_Context *context);

function void index__tick(Application_Links *app);

// Format:
// %t -> token,         requires char * specifying token string
// %k -> token kind,    requires Token_Base_Kind and Token ** for output token
// %b -> token subkind, requires token subkind and Token ** for output token
// %n -> note,          requires Index__Note_Kind and Index__Note ** for output note
// %s -> soft group,    requires no arguments
// %o -> operator group,requires no arguments
function b32 index__parse_pattern(Index__Parse_Context *context, char *fmt, ...);

NAMESPACE_END() // nne

#endif // FCODER_CUSTOM_INDEX_H
