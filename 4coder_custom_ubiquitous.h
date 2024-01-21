#ifndef FCODER_CUSTOM_UBIQUITOUS_H
#define FCODER_CUSTOM_UBIQUITOUS_H

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

#define MemorySet                 memset
#define MemoryCopy                memcpy
#define CalculateCStringLength    strlen
#define S8Lit(s)                  string_u8_litexpr(s)
#define Str_U8(s)                 string_u8_litexpr(s)

#endif // FCODER_CUSTOM_UBIQUITOUS_H
