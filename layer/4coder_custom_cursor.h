#ifndef FCODER_FLEURY_CURSOR_H
#define FCODER_FLEURY_CURSOR_H

namespace nne {
	
	function void render_cursor_emacs_style(Application_Links *app, View_ID view_id, b32 is_active_view, Buffer_ID buffer, Text_Layout_ID text_layout_id, f32 roundness, f32 outline_thickness, Frame_Info frame_info);
	function void render_cursor_notepad_style(Application_Links *app, View_ID view_id, b32 is_active_view, Buffer_ID buffer, Text_Layout_ID text_layout_id, f32 roundness, f32 outline_thickness, Frame_Info frame_info);
	function void highlight_cursor_mark_range(Application_Links *app, View_ID view_id);
}

#endif // FCODER_FLEURY_CURSOR_H
