#ifndef FCODER_CUSTOM_COLORS_H
#define FCODER_CUSTOM_COLORS_H

CUSTOM_ID(colors, fleury_color_syntax_crap);
CUSTOM_ID(colors, fleury_color_operators);
CUSTOM_ID(colors, fleury_color_inactive_pane_overlay);
CUSTOM_ID(colors, fleury_color_inactive_pane_background);
CUSTOM_ID(colors, fleury_color_file_progress_bar);
CUSTOM_ID(colors, fleury_color_brace_highlight);
CUSTOM_ID(colors, fleury_color_brace_line);
CUSTOM_ID(colors, fleury_color_brace_annotation);
CUSTOM_ID(colors, fleury_color_index_sum_type);
CUSTOM_ID(colors, fleury_color_index_product_type);
CUSTOM_ID(colors, fleury_color_index_function);
CUSTOM_ID(colors, fleury_color_index_macro);
CUSTOM_ID(colors, fleury_color_index_constant);
CUSTOM_ID(colors, fleury_color_index_comment_tag);
CUSTOM_ID(colors, fleury_color_index_decl);
CUSTOM_ID(colors, fleury_color_cursor_macro);
CUSTOM_ID(colors, fleury_color_cursor_power_mode);
CUSTOM_ID(colors, fleury_color_cursor_inactive);
CUSTOM_ID(colors, fleury_color_plot_cycle);
CUSTOM_ID(colors, fleury_color_token_highlight);
CUSTOM_ID(colors, fleury_color_token_minor_highlight);
CUSTOM_ID(colors, fleury_color_comment_user_name);
CUSTOM_ID(colors, fleury_color_lego_grab);
CUSTOM_ID(colors, fleury_color_lego_splat);
CUSTOM_ID(colors, fleury_color_error_annotation);

NAMESPACE_BEGIN(nne)

typedef u32 Color_Flags;
enum {
    Color_Flag_Macro     = (1<<0),
    Color_Flag_PowerMode = (1<<1),
};

struct Color_Context {
    Token token;
    Buffer_ID buffer;
    Color_Flags flags;
    keybinding_mode mode;
};

internal void tick_colors(Application_Links *app, Frame_Info frame_info);
internal ARGB_Color argb_from_id(Color_Table table, Managed_ID id, int subindex);
internal ARGB_Color argb_from_id(Color_Table table, Managed_ID id);
internal Color_Context make_token_color_context(Token token, Buffer_ID buffer);
internal Color_Context make_cursor_color_context(Color_Flags flags, keybinding_mode mode);
internal ARGB_Color get_color(Application_Links *app, Color_Context ctx);
internal void do_syntax_highlight(Application_Links *app, Text_Layout_ID text_layout_id, Token_Array *array);

NAMESPACE_END()

#endif // 4CODER_CUSTOM_COLORS_H
