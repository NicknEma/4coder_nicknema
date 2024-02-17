#ifndef FCODER_CUSTOM_RECENT_FILES_CPP
#define FCODER_CUSTOM_RECENT_FILES_CPP

CUSTOM_ID(attachment, f4_recentfiles_viewstate);

namespace nne {
	
	struct Recent_Files_View_State {
		int recent_buffer_count;
		Buffer_ID recent_buffers[16];
	};
	
	function void refresh_recent_files_view(Application_Links *app, View_ID view) {
		Buffer_ID buffer = view_get_buffer(app, view, AccessFlag_Read);
		if (buffer) {
			Managed_Scope scope = view_get_managed_scope(app, view);
			Recent_Files_View_State *state = scope_attachment(app, scope, f4_recentfiles_viewstate, Recent_Files_View_State);
			if (state) {
				b32 need_push = true;
				
				if (state->recent_buffer_count > 0 && state->recent_buffers[0] == buffer) {
					need_push = false;
				}
				
				if (need_push) {
					if (state->recent_buffer_count >= 16) {
						state->recent_buffer_count -= 1;
					}
					
					memmove(state->recent_buffers + 1, state->recent_buffers + 0, sizeof(state->recent_buffers[0])*state->recent_buffer_count);
					state->recent_buffers[0] = buffer;
					state->recent_buffer_count += 1;
					
					// Remove any old instances of this buffer in the list.
					{
						for (int i = 1; i < state->recent_buffer_count; i += 1) {
							if (state->recent_buffers[i] == buffer) {
								memmove(state->recent_buffers + i, state->recent_buffers + i + 1, sizeof(state->recent_buffers[0])*(state->recent_buffer_count-i-1));
								state->recent_buffer_count -= 1;
							}
						}
					}
				}
			}
		}
	}
	
	// @Rename: What does it render? The list? The names?
	// @Unused, so maybe it doesn't matter
	internal void render_recent_files(Application_Links *app, View_ID view, Face_ID face) {
		Scratch_Block scratch(app);
		
		Rect_f32 view_rect = view_get_screen_rect(app, view);
		Face_Metrics metrics = get_face_metrics(app, face);
		
		Managed_Scope scope = view_get_managed_scope(app, view);
		Recent_Files_View_State *state = scope_attachment(app, scope, f4_recentfiles_viewstate, Recent_Files_View_State);
		
		if (state) {
			Vec2_f32 p = view_rect.p0;
			for (int i = 0; i < state->recent_buffer_count; i += 1) {
				Buffer_ID buffer = state->recent_buffers[i];
				String_Const_u8 string = push_buffer_unique_name(app, scratch, buffer);
				draw_string(app, face, string, p, 0xffffffff);
				p.y += metrics.line_height;
			}
		}
	}
	
}

CUSTOM_UI_COMMAND_SIG(list_recent_files)
CUSTOM_DOC("Lists the recent files used in the current panel.") {
	View_ID view = get_active_view(app, Access_Read);
	Managed_Scope scope = view_get_managed_scope(app, view);
	nne::Recent_Files_View_State *state = scope_attachment(app, scope, f4_recentfiles_viewstate, nne::Recent_Files_View_State);
	
	if (state) {
		Scratch_Block scratch(app);
		Lister_Block  lister(app, scratch);
		lister_set_query(lister, "Recent Buffers:");
		lister_set_default_handlers(lister);
		
		for (int i = 1; i < state->recent_buffer_count; i += 1) {
			Buffer_ID buffer = state->recent_buffers[i];
			String_Const_u8 buffer_name = push_buffer_unique_name(app, scratch, buffer);
			Buffer_ID *buf = push_array(scratch, Buffer_ID, 1);
			*buf = buffer;
			lister_add_item(lister, buffer_name, S8Lit(""), buf, 0);
		}
		
		Lister_Result l_result = run_lister(app, lister);
		if (!l_result.canceled && l_result.user_data) {
			Buffer_ID buffer = *cast(Buffer_ID *)l_result.user_data;
			if (buffer) {
				view_set_buffer(app, view, buffer, 0);
			}
		}
	}
}

#endif // FCODER_CUSTOM_RECENT_FILES_CPP
