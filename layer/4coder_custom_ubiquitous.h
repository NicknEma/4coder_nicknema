#ifndef FCODER_CUSTOM_UBIQUITOUS_H
#define FCODER_CUSTOM_UBIQUITOUS_H

#define NAMESPACE_BEGIN(name) namespace name {
#define NAMESPACE_END() }

#define Allow_Break() Assert(1)
#define Force_Break() Assert(0)

#define cast(t) (t)

enum Keybinding_Mode {
	Keybinding_Mode_0,
	Keybinding_Mode_1,
    Keybinding_Mode_2,
    Keybinding_Mode_3,
    Keybinding_Mode_MAX
};

global Keybinding_Mode global_keybinding_mode;
global Face_ID         global_styled_title_face = 0;
global Face_ID         global_styled_label_face = 0;
global Face_ID         global_small_code_face = 0;
global Rect_f32        global_cursor_rect = {};
global Rect_f32        global_last_cursor_rect = {};
global Rect_f32        global_mark_rect = {};
global Rect_f32        global_last_mark_rect = {};
global b32             global_dark_mode = true;
global b32             global_battery_saver = false;
global View_ID         global_compilation_view = 0;
global b32             global_compilation_view_expanded = false;
global Arena           global_custom_permanent_arena = {};

#define MemorySet                 memset
#define MemoryCopy                memcpy
#define CalculateCStringLength    strlen
#define S8Lit(s)                  string_u8_litexpr(s)
#define Str_U8(s)                 string_u8_litexpr(s)

function String_Const_u8 strip_string_border_characters(String_Const_u8 string);
function f32 random_f32(f32 low, f32 high);
function f32 min_of(f32 a, f32 b);
function f32 max_of(f32 a, f32 b);
function b32 char_is_alphabetic(int c);
function b32 char_is_digit(int c);
function b32 char_is_symbol(int c);
function double get_first_double_from_buffer(char *buffer);
function b32 strings_match_case_sensitive(char *a, int a_length, char *b, int b_length);
function u32  crc32(unsigned char *buf, int len);
function u32 string_crc32(char *string, int string_length);
function u32 cstring_crc32(char *string);
function u64 get_single_bit_offset(u64 value);
function b32 is_file_readable(String_Const_u8 path);

#endif // FCODER_CUSTOM_UBIQUITOUS_H
