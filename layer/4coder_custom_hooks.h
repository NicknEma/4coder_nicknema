#ifndef FCODER_CUSTOM_HOOKS_H
#define FCODER_CUSTOM_HOOKS_H

//~ The hooks that 4coder's core will call back, that are implemented by the custom layer.

namespace nne {
	//- Hooks
	function void             tick(Application_Links *app, Frame_Info frame_info);
	function i32              begin_buffer(Application_Links *app, Buffer_ID buffer_id);
	function void             render(Application_Links *app, Frame_Info frame_info, View_ID view_id);
	function Layout_Item_List layout(Application_Links *app, Arena *arena, Buffer_ID buffer, Range_i64 range, Face_ID face, f32 width);
	function void             whole_screen_render(Application_Links *app, Frame_Info frame_info);
	function i32              buffer_edit_range(Application_Links *app, Buffer_ID buffer_id, Range_i64 new_range, Range_Cursor old_cursor_range);
	function Vec2_f32         delta_rule(Vec2_f32 pending, b32 is_new_target, f32 dt, void *data);
	
	//- Helpers:
	// function void render_buffer(Application_Links *app, View_ID view_id, Face_ID face_id, Buffer_ID buffer, Text_Layout_ID text_layout_id, Rect_f32 rect, Frame_Info frame_info);
}

#endif // 4CODER_CUSTOM_HOOKS_H
