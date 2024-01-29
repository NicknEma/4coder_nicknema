#ifndef FCODER_CUSTOM_UBIQUITOUS_H
#define FCODER_CUSTOM_UBIQUITOUS_H

// NAMESPACE_BEGIN(nne)

enum keybinding_mode {
	KeyBindingMode_0,
	KeyBindingMode_1,
    KeyBindingMode_2,
    KeyBindingMode_3,
    KeyBindingMode_MAX
};

static keybinding_mode GlobalKeybindingMode;
static Face_ID global_styled_title_face = 0;
static Face_ID global_styled_label_face = 0;
static Face_ID global_small_code_face = 0;
static Rect_f32 global_cursor_rect = {};
static Rect_f32 global_last_cursor_rect = {};
static Rect_f32 global_mark_rect = {};
static Rect_f32 global_last_mark_rect = {};
static b32 global_dark_mode = true;
static b32 global_battery_saver = false;
static View_ID global_compilation_view = 0;
static b32 global_compilation_view_expanded = false;
global Arena permanent_arena = {};

// NAMESPACE_END()

#define MemorySet                 memset
#define MemoryCopy                memcpy
#define CalculateCStringLength    strlen
#define S8Lit(s)                  string_u8_litexpr(s)
#define Str_U8(s)                 string_u8_litexpr(s)

NAMESPACE_BEGIN(nne)

internal String_Const_u8 strip_string_border_characters(String_Const_u8 string);
internal f32 random_f32(f32 low, f32 high);
internal f32 min_f32(f32 a, f32 b);
internal f32 max_f32(f32 a, f32 b);
internal b32 char_is_alphabetic(int c);
internal b32 char_is_digit(int c);
internal b32 char_is_symbol(int c);
internal double get_first_double_from_buffer(char *buffer);
internal b32 strings_match_case_sensitive(char *a, int a_length, char *b, int b_length);
internal unsigned int crc32(unsigned char *buf, int len);
internal unsigned int string_crc32(char *string, int string_length);
internal unsigned int cstring_crc32(char *string);
internal u64 get_single_bit_offset(u64 value);

NAMESPACE_END()

#endif // FCODER_CUSTOM_UBIQUITOUS_H
