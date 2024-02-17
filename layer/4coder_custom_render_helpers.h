#ifndef FCODER_CUSTOM_RENDER_HELPERS_H
#define FCODER_CUSTOM_RENDER_HELPERS_H

namespace nne {
	
	enum class Range_Highlight_Kind {
		Whole,
		Underline,
		Minor_Underline,
	};
	
	struct Flash {
		b32 active;
		f32 t;
		
		Buffer_ID buffer;
		Range_i64 range;
		ARGB_Color color;
		f32 decay_rate;
	};
	
	function u32  calculate_color_brightness(u32 color);
	function void draw_hex_color_preview(Application_Links* app, Buffer_ID buffer, Text_Layout_ID text_layout_id, i64 pos);
	function void draw_brace_highlight(Application_Links *app, Buffer_ID buffer, Text_Layout_ID text_layout_id, i64 pos, ARGB_Color *colors, i32 color_count);
	function void draw_tooltip_rect(Application_Links *app, Rect_f32 rect);
	function void render_range_highlight(Application_Links *app, View_ID view_id, Text_Layout_ID text_layout_id, Range_i64 range, Range_Highlight_Kind kind, ARGB_Color color);
	function void push_tooltip(String_Const_u8 string, ARGB_Color color);
	function void push_flash(Application_Links *app, Buffer_ID buffer, Range_i64 range, ARGB_Color color, f32 decay_rate);
	function void update_flashes(Application_Links *app, Frame_Info frame);
	function void render_flashes(Application_Links *app, View_ID view, Text_Layout_ID text_layout);
	
}

#endif // FCODER_CUSTOM_RENDER_HELPERS_H
