#ifndef FCODER_CUSTOM_HOOKS_CPP
#define FCODER_CUSTOM_HOOKS_CPP

namespace nne {
	
	//~ Delta Rule.
	
	function Vec2_f32 delta_rule(Vec2_f32 pending, b32 is_new_target, f32 dt, void *data) {
		Vec2_f32 *velocity = cast(Vec2_f32*)data;
		if (velocity->x == 0.f) {
			velocity->x = 1.f;
			velocity->y = 1.f;
		}
		
		Smooth_Step step_x = smooth_camera_step(pending.x, velocity->x, 80.f, 1.f/4.f);
		Smooth_Step step_y = smooth_camera_step(pending.y, velocity->y, 80.f, 1.f/4.f);
		*velocity = V2f32(step_x.v, step_y.v);
		return V2f32(step_x.p, step_y.p);
	}
	
	//~ Buffer Render.
	
	ARGB_Color DEFAULT_FUNCTION_COLOR             = 0xFF769fdf;
	ARGB_Color DEFAULT_TYPE_COLOR                 = 0xFF85b920;
	ARGB_Color DEFAULT_CONSTANT_COLOR             = 0xffeb7b46;
	ARGB_Color DEFAULT_MACRO_COLOR                = 0xffa48391;
	
	ARGB_Color DEFAULT_OCCURRENCE_HIGHLIGHT       = 0x44cb4b16;
	ARGB_Color DEFAULT_OCCURRENCE_HIGHLIGHT_MINOR = 0x33cb4b16;
	
#if 0
	//- Recoloring of strings or identifiers.
	
	struct String_Color_Pair {
		String_Const_u8 needle;
		ARGB_Color      color;
	};
	
	// NOTE(mrmixer): based on draw_comment_highlights.
	// @Doc: Scans for specific identifiers and overwrites their color. Useful for adding custom keywords.
	function void mrmixer_recolor_identifiers(Application_Links *app, Buffer_ID buffer, Text_Layout_ID text_layout_id, Token_Array *tokens, String_Color_Pair *pairs, i32 pair_count) {
		Scratch_Block scratch(app);
		
		Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
		i64 first_index         = token_index_from_pos(tokens, visible_range.first);
		Token_Iterator_Array it = token_iterator_index(buffer, tokens, first_index);
		
		for (;;) {
			Temp_Memory_Block temp(scratch);
			
			Token *token = token_it_read(&it);
			if (token->pos >= visible_range.one_past_last)
				break;
			
			String_Const_u8 tail = {0};
			if (token_it_check_and_get_lexeme(app, scratch, &it, TokenBaseKind_Identifier, &tail)) {
				String_Color_Pair *pair = pairs;
				for (i32 i = 0; i < pair_count; i += 1, pair += 1) {
					if (string_match(tail, pair->needle)) {
						Range_i64 range = Ii64_size(token->pos, token->size);
						paint_text_color(app, text_layout_id, range, pair->color);
						
						break;
					}
				}
			}
			
			if (!token_it_inc_non_whitespace(&it))
				break;
		}
	}
	
	// @Doc: Scans for specific raw text strings and overwrites their color. Useful for non-code files.
	function void mrmixer_recolor_strings(Application_Links *app, Buffer_ID buffer, Text_Layout_ID text_layout_id, String_Color_Pair *pairs, i32 pair_count) {
		Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
		
		String_Color_Pair *pair = pairs;
		for (i32 i = 0; i < pair_count; i += 1, pair += 1) {
			if (pair->needle.size > 0) {
				i64 position = visible_range.min;
				seek_string_insensitive_forward(app, buffer, position - 1, visible_range.max, pair->needle, &position);
				
				while (position < visible_range.max){
					Range_i64 range = Ii64_size(position, pair->needle.size);
					paint_text_color(app, text_layout_id, range, pair->color);
					seek_string_insensitive_forward(app, buffer, position, visible_range.max, pair->needle, &position);
				}
			}
		}
	}
#endif
	
#if 0
	//- Range highlight.
	
	// @Note(ema): From skytrias_custom
	
	enum skytrias_Range_Hightlight_Kind {
		skytrias_Range_Hightlight_Kind_WHOLE,
		skytrias_Range_Hightlight_Kind_UNDERLINE,
	};
	
	// @Doc(ema): Given a range and a color, highlights or underlines the text.
	function void skytrias_render_range_highlight(Application_Links *app, View_ID view_id, Text_Layout_ID text_layout_id, Range_i64 range, skytrias_Range_Hightlight_Kind kind, ARGB_Color color) {
		Rect_f32 range_start_rect = text_layout_character_on_screen(app, text_layout_id, range.start);
		Rect_f32 range_end_rect   = text_layout_character_on_screen(app, text_layout_id, range.end - 1);
		Rect_f32 total_range_rect = {0};
		total_range_rect.x0 = nicknema::f32_min_of(range_start_rect.x0, range_end_rect.x0);
		total_range_rect.y0 = nicknema::f32_min_of(range_start_rect.y0, range_end_rect.y0);
		total_range_rect.x1 = nicknema::f32_max_of(range_start_rect.x1, range_end_rect.x1);
		total_range_rect.y1 = nicknema::f32_max_of(range_start_rect.y1, range_end_rect.y1);
		
		// @Cleanup(ema): Why? Wasn't an if statement better?
		switch (kind) {
			case skytrias_Range_Hightlight_Kind_UNDERLINE: {
				total_range_rect.y0 = total_range_rect.y1 - 1.f;
				total_range_rect.y1 += 1.f;
			} break;
		}
		
		draw_rectangle(app, total_range_rect, 4.f, color);
	}
#endif
	
	//- Hex color preview.
	
	// @Note(ema): Provided by thevaber at
	// https://gist.github.com/thevaber/58bb6a1c03ebe56309545f413e898a95
	
	function u32 calculate_color_brightness(u32 color) {
		u32 r = ((color >> 16) & 0xFF);
		u32 g = ((color >>  8) & 0xFF);
		u32 b = ((color >>  0) & 0xFF);
		
		// @Cleanup: What are these magic numbers?
		f32 brightness = sqrtf((r * r * 0.241f) + (g * g * 0.691f) + (b * b * 0.068f));
		
		return cast(u32)brightness;
	}
	
	function void draw_hex_color_preview(Application_Links* app, Buffer_ID buffer, Text_Layout_ID text_layout_id, i64 pos) {
		ProfileScope(app, "Draw hex color preview");
		Scratch_Block scratch(app);
		
		// @Cleanup: Remove magic numbers and characters.
		Range_i64 range = enclose_pos_alpha_numeric(app, buffer, pos);
		String_Const_u8 token = push_buffer_range(app, scratch, buffer, range);
		if (token.size == 10) {
			if (token.str[0] == '0' && (token.str[1] == 'x' || token.str[1] == 'X')) {
				b32 is_hex = true;
				for (u32 i = 0; (i < 8) && is_hex; i += 1) {
					char c = token.str[i + 2];
					is_hex = ((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || (c >= '0' && c <= '9'));
				}
				
				if (is_hex) {
					String_Const_u8 hex = string_substring(token, Ii64_size(2, 8));
					
					ARGB_Color hex_color = (u32)string_to_integer(hex, 16);
					draw_character_block(app, text_layout_id, Ii64_size(range.min, 10), 2.0f, hex_color);
					
					ARGB_Color text_color = calculate_color_brightness(hex_color) < 128 ? 0xFFFFFFFF : 0xFF000000;
					paint_text_color(app, text_layout_id, range, text_color);
				}
			}
		}
	}
	
	//- Brace highlight.
	
	// @Note(ema): Based on draw_paren_highlight from 4coder_draw.cpp
	function void draw_brace_highlight(Application_Links *app, Buffer_ID buffer, Text_Layout_ID text_layout_id, i64 pos, ARGB_Color *colors, i32 color_count) {
		Token_Array token_array = get_token_array_from_buffer(app, buffer);
		if (token_array.tokens != 0) {
			Token_Iterator_Array it = token_iterator_pos(0, &token_array, pos);
			Token *token = token_it_read(&it);
			if (token != 0 && token->kind == TokenBaseKind_ScopeOpen) {
				pos = token->pos + token->size;
			} else {
				if (token_it_dec_all(&it)) {
					token = token_it_read(&it);
					if (token->kind == TokenBaseKind_ScopeClose && pos == token->pos + token->size) {
						pos = token->pos;
					}
				}
			}
		}
		
		draw_enclosures(app, text_layout_id, buffer, pos, FindNest_Scope, RangeHighlightKind_CharacterHighlight, 0, 0, colors, color_count);
	}
	
	function void render_buffer(Application_Links *app, View_ID view_id, Face_ID face_id, Buffer_ID buffer, Text_Layout_ID text_layout_id, Rect_f32 rect, Frame_Info frame_info) {
		ProfileScope(app, "Render Buffer");
		Scratch_Block scratch(app);
		
		Rect_f32 prev_clip  = draw_set_clip(app, rect);
		
		View_ID active_view = get_active_view(app, Access_Always);
		b32 is_active_view  = (active_view == view_id);
		
		//- Token colorizing
		Token_Array token_array = get_token_array_from_buffer(app, buffer);
		if (token_array.tokens != 0) {
			do_syntax_highlight(app, text_layout_id, &token_array);
			
			//- Scan for TODOs and NOTEs
			b32 use_comment_keywords = def_get_config_b32(vars_save_string_lit("use_comment_keywords"));
			if (use_comment_keywords) {
				Comment_Highlight_Pair pairs[] = {
					{str8_lit("NOTE"), finalize_color(defcolor_comment_pop, 0)},
					{str8_lit("TODO"), finalize_color(defcolor_comment_pop, 1)},
					{def_get_config_string(scratch, vars_save_string_lit("user_name")), finalize_color(fleury_color_comment_user_name, 0)},
				};
				
				draw_comment_highlights(app, buffer, text_layout_id, &token_array, pairs, ArrayCount(pairs));
			}
		} else {
			Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
			paint_text_color_fcolor(app, text_layout_id, visible_range, fcolor_id(defcolor_text_default));
		}
		
		i64 cursor_pos = view_correct_cursor(app, view_id);
		view_correct_mark(app, view_id);
		
		{
			//- Scope highlight.
			b32 use_scope_highlight = def_get_config_b32(vars_save_string_lit("use_scope_highlight"));
			if (use_scope_highlight) {
				Color_Array colors = finalize_color_array(defcolor_back_cycle);
				draw_scope_highlight(app, buffer, text_layout_id, cursor_pos, colors.vals, colors.count);
			}
		}
		
		//- Paren and brace highlight.
		{
			// @Cleanup: Render brace highlight doesn't read from config?
			// It's probabily checked inside F4_Brace_RenderHighlight...
			
			if (def_get_config_b32(vars_save_string_lit("use_paren_helper"))) {
				Color_Array colors = finalize_color_array(defcolor_text_cycle);
				draw_paren_highlight(app, buffer, text_layout_id, cursor_pos, colors.vals, colors.count);
			}
			
			Color_Array colors = finalize_color_array(fleury_color_brace_highlight);
			if (colors.count >= 1 && argb_is_valid(colors.vals[0])) {
				F4_Brace_RenderHighlight(app, buffer, text_layout_id, cursor_pos, colors.vals, colors.count);
			}
		}
		
		{
			//- Highlight line at cursor.
			b32 highlight_line_at_cursor = def_get_config_b32(vars_save_string_lit("highlight_line_at_cursor"));
			Buffer_ID compilation_buffer = get_buffer_by_name(app, string_u8_litexpr("*compilation*"), Access_Always);
			if (highlight_line_at_cursor && (is_active_view || buffer == compilation_buffer)) {
				i64 line_number = get_line_number_from_pos(app, buffer, cursor_pos);
				draw_line_highlight(app, text_layout_id, line_number, fcolor_id(defcolor_highlight_cursor_line));
			}
		}
		
		{
			//- Highlight errors, jumps (together because they're basically the same thing).
			b32 use_error_highlight = def_get_config_b32(vars_save_string_lit("use_error_highlight"));
			b32 use_jump_highlight  = def_get_config_b32(vars_save_string_lit("use_jump_highlight"));
			
			if (use_error_highlight || use_jump_highlight) {
				Buffer_ID compilation_buffer = get_buffer_by_name(app, string_u8_litexpr("*compilation*"), Access_Always);
				
				// Error highlight.
				if (use_error_highlight)
					draw_jump_highlights(app, buffer, text_layout_id, compilation_buffer, fcolor_id(defcolor_highlight_junk));
				
				// Jump highlight.
				if (use_jump_highlight) {
					Buffer_ID jump_buffer = get_locked_jump_buffer(app);
					if (jump_buffer != compilation_buffer)
						draw_jump_highlights(app, buffer, text_layout_id, jump_buffer, fcolor_id(defcolor_highlight_white));
				}
			}
		}
		
		//- Error annotations
		{
			Buffer_ID compilation_buffer = get_buffer_by_name(app, string_u8_litexpr("*compilation*"), Access_Always);
			F4_RenderErrorAnnotations(app, buffer, text_layout_id, compilation_buffer);
		}
		
		{
			//- Preview hex colors
			// @Incomplete(ema): read variable from config file.
			b32 should_preview_hex_colors = def_get_config_b32(vars_save_string_lit("preview_hex_colors"));
			if (should_preview_hex_colors) {
				draw_hex_color_preview(app, buffer, text_layout_id, cursor_pos);
			}
		}
		
		{
			//- Highlight token occurrences.
			b32 should_highlight_token_occurrences = !def_get_config_b32(vars_save_string_lit("f4_disable_cursor_token_occurance"));
			if (should_highlight_token_occurrences) {
				ProfileScope(app, "Token Occurance Highlight");
				
				// Get the active cursor's token string.
				Buffer_ID            active_cursor_buffer        = view_get_buffer(app, active_view, Access_Always);
				i64                  active_cursor_pos           = view_get_cursor_pos(app, active_view);
				Token_Array          active_cursor_buffer_tokens = get_token_array_from_buffer(app, active_cursor_buffer);
				Token_Iterator_Array active_cursor_it            = token_iterator_pos(0, &active_cursor_buffer_tokens, active_cursor_pos);
				Token               *active_cursor_token         = token_it_read(&active_cursor_it);
				
				if (active_cursor_token) {
					Scratch_Block   local_scratch(app);
					String_Const_u8 active_cursor_string = push_buffer_range(app, local_scratch, active_cursor_buffer, Ii64(active_cursor_token));
					
					// Loop the visible tokens
					Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
					i64  first_index = token_index_from_pos(&token_array, visible_range.first);
					auto it          = token_iterator_index(0, &token_array, first_index);
					
					for (;;) {
						Token *token = token_it_read(&it);
						if (!token || token->pos >= visible_range.one_past_last) {
							break;
						}
						
						if (token->kind == TokenBaseKind_Identifier) {
							Range_i64 token_range = Ii64(token);
							String_Const_u8 token_string = push_buffer_range(app, local_scratch, buffer, token_range);
							
							if (range_contains(token_range, view_get_cursor_pos(app, view_id))) {
								// If this is the buffers cursor token, highlight it with an Underline
								F4_RenderRangeHighlight(app, view_id, text_layout_id, token_range, F4_RangeHighlightKind_Underline, fcolor_resolve(fcolor_id(fleury_color_token_highlight)));
							} else if (active_cursor_token->kind == TokenBaseKind_Identifier && string_match(token_string, active_cursor_string)) {
								// If the token matches the active buffer token. highlight it with a Minor Underline
								F4_RenderRangeHighlight(app, view_id, text_layout_id, token_range, F4_RangeHighlightKind_MinorUnderline, fcolor_resolve(fcolor_id(fleury_color_token_minor_highlight)));
								
							} 
						}
						
						if (!token_it_inc_non_whitespace(&it)) {
							break;
						}
					}
				}
			} else {
				// NOTE(jack): if "f4_disable_cursor_token_occurance" is set, just highlight the cusror 
				ProfileScope(app, "Token Highlight");
				
				Token_Iterator_Array it = token_iterator_pos(0, &token_array, cursor_pos);
				Token *token = token_it_read(&it);
				if (token && token->kind == TokenBaseKind_Identifier) {
					F4_RenderRangeHighlight(app, view_id, text_layout_id, Ii64(token->pos, token->pos + token->size), F4_RangeHighlightKind_Underline, fcolor_resolve(fcolor_id(fleury_color_token_highlight)));
				}
			}
		}
		
		//- Render flashes.
		{
			F4_RenderFlashes(app, view_id, text_layout_id);
		}
		
		//- Divider comments.
		{
			render_divider_comments(app, buffer, view_id, text_layout_id);
		}
		
		//- Cursor Mark Range.
		if (is_active_view && fcoder_mode == FCoderMode_Original) {
			F4_HighlightCursorMarkRange(app, view_id);
		}
		
		//- Get cursor shape.
		Face_Metrics metrics     = get_face_metrics(app, face_id);
		u64 cursor_roundness_100 = def_get_config_u64(app, vars_save_string_lit("cursor_roundness"));
		f32 cursor_roundness     = metrics.normal_advance * cursor_roundness_100 * 0.01f;
		f32 mark_thickness       = cast(f32)def_get_config_u64(app, vars_save_string_lit("mark_thickness"));
		
		//- Draw cursor.
		switch (fcoder_mode) {
			case FCoderMode_Original: {
				F4_Cursor_RenderEmacsStyle(app, view_id, is_active_view, buffer, text_layout_id, cursor_roundness, mark_thickness, frame_info);
			} break;
			
			case FCoderMode_NotepadLike: {
				F4_Cursor_RenderNotepadStyle(app, view_id, is_active_view, buffer, text_layout_id, cursor_roundness,
											 mark_thickness, frame_info);
			} break;
		}
		
		{
			//- Draw whitespace.
			b64 show_whitespace = false;
			view_get_setting(app, view_id, ViewSetting_ShowWhitespace, &show_whitespace);
			
			if (show_whitespace) {
				if (token_array.tokens == 0) {
					draw_whitespace_highlight(app, buffer, text_layout_id, cursor_roundness);
				} else {
					draw_whitespace_highlight(app, text_layout_id, &token_array, cursor_roundness);
				}
			}
		}
		
		//- Render helper annotations after closing braces.
		{
			F4_Brace_RenderCloseBraceAnnotation(app, buffer, text_layout_id, cursor_pos);
		}
		
		//- Draw vertical brace lines, as an additional scope helper.
		{
			F4_Brace_RenderLines(app, buffer, view_id, text_layout_id, cursor_pos);
		}
		
		//- @Note(ema): New. It didn't happen in the raw fleury layer.
		paint_fade_ranges(app, text_layout_id, buffer);
		
		//- Put the actual text on the actual screen.
		draw_text_layout_default(app, text_layout_id);
		
		//- Interpret buffer as calc code, if it's the calc buffer.
		{
			// @Todo: Why doesn't this work with virtual whitespace, and why even without it it works only until the file is saved?
			Buffer_ID calc_buffer_id = get_buffer_by_name(app, string_u8_litexpr("*calc*"), AccessFlag_Read);
			if (calc_buffer_id == buffer) {
				calculator__render_buffer(app, buffer, view_id, text_layout_id, frame_info);
			}
		}
		
		//- Draw calc comments.
		{
			// @Todo: Why doesn't this work with virtual whitespace, and why even without it it works only until the file is saved?
			calculator__render_comments(app, buffer, view_id, text_layout_id, frame_info);
		}
		
		draw_set_clip(app, prev_clip);
		
		//- Draw tooltips and stuff.
		if (active_view == view_id) {
			//- Position context helper.
			{
				F4_PosContext_Render(app, view_id, buffer, text_layout_id, cursor_pos);
			}
			
			//- Draw tooltip list.
			{
				Mouse_State mouse = get_mouse_state(app);
				
				Rect_f32 view_rect = view_get_screen_rect(app, view_id);
				
				Face_ID tooltip_face_id = global_small_code_face;
				Face_Metrics tooltip_face_metrics = get_face_metrics(app, tooltip_face_id);
				
				Rect_f32 tooltip_rect = {
					cast(f32)mouse.x + 16,
					cast(f32)mouse.y + 16,
					cast(f32)mouse.x + 16,
					cast(f32)mouse.y + 16 + tooltip_face_metrics.line_height + 8,
				};
				
				for (int i = 0; i < global_tooltip_count; i += 1) {
					String_Const_u8 string = global_tooltips[i].string;
					tooltip_rect.x1 = tooltip_rect.x0;
					tooltip_rect.x1 += get_string_advance(app, tooltip_face_id, string) + 4;
					
					if (tooltip_rect.x1 > view_rect.x1) {
						f32 difference = tooltip_rect.x1 - view_rect.x1;
						tooltip_rect.x1 = cast(float)cast(int)(tooltip_rect.x1 - difference);
						tooltip_rect.x0 = cast(float)cast(int)(tooltip_rect.x0 - difference);
					}
					
					F4_DrawTooltipRect(app, tooltip_rect);
					
					draw_string(app, tooltip_face_id, string, V2f32(tooltip_rect.x0 + 4, tooltip_rect.y0 + 4), global_tooltips[i].color);
				}
			}
		}
		
		//- Draw inactive rectangle.
		if (is_active_view == 0) {
			Rect_f32 view_rect = view_get_screen_rect(app, view_id);
			ARGB_Color color = fcolor_resolve(fcolor_id(fleury_color_inactive_pane_overlay));
			if (argb_is_valid(color)) {
				draw_rectangle(app, view_rect, 0.f, color);
			}
		}
		
		//- Render code peek.
		{
			if(!view_get_is_passive(app, view_id) && !is_active_view) {
				F4_CodePeek_Render(app, view_id, face_id, buffer, frame_info);
			}
		}
		
		//- Draw power mode.
		{
			F4_PowerMode_RenderBuffer(app, view_id, face_id, frame_info);
		}
	}
	
	//~ Render.
	
	function void draw_file_bar(Application_Links *app, View_ID view_id, Buffer_ID buffer, Face_ID face_id, Rect_f32 bar) {
		Scratch_Block scratch(app);
		
		draw_rectangle_fcolor(app, bar, 0.f, fcolor_id(defcolor_bar));
		
		FColor base_color = fcolor_id(defcolor_base);
		FColor pop2_color = fcolor_id(defcolor_pop2);
		
		i64 cursor_position = view_get_cursor_pos(app, view_id);
		Buffer_Cursor cursor = view_compute_cursor(app, view_id, seek_pos(cursor_position));
		
		Fancy_Line list = {};
		String_Const_u8 unique_name = push_buffer_unique_name(app, scratch, buffer);
		push_fancy_string(scratch, &list, base_color, unique_name);
		push_fancy_stringf(scratch, &list, base_color, " - Row: %3.lld Col: %3.lld -", cursor.line, cursor.col);
		
		Managed_Scope scope = buffer_get_managed_scope(app, buffer);
		Line_Ending_Kind *eol_setting = scope_attachment(app, scope, buffer_eol_setting,
														 Line_Ending_Kind);
		switch (*eol_setting){
			case LineEndingKind_Binary:
			{
				push_fancy_string(scratch, &list, base_color, string_u8_litexpr(" bin"));
			}break;
			
			case LineEndingKind_LF:
			{
				push_fancy_string(scratch, &list, base_color, string_u8_litexpr(" lf"));
			}break;
			
			case LineEndingKind_CRLF:
			{
				push_fancy_string(scratch, &list, base_color, string_u8_litexpr(" crlf"));
			}break;
		}
		
		u8 space[3];
		{
			Dirty_State dirty = buffer_get_dirty_state(app, buffer);
			String_u8 str = Su8(space, 0, 3);
			if (dirty != 0){
				string_append(&str, string_u8_litexpr(" "));
			}
			if (HasFlag(dirty, DirtyState_UnsavedChanges)){
				string_append(&str, string_u8_litexpr("*"));
			}
			if (HasFlag(dirty, DirtyState_UnloadedChanges)){
				string_append(&str, string_u8_litexpr("!"));
			}
			push_fancy_string(scratch, &list, pop2_color, str.string);
		}
		
		push_fancy_string(scratch, &list, base_color, S8Lit(" Syntax Mode: "));
		push_fancy_string(scratch, &list, base_color, read_syntax_options_string());
		
		Vec2_f32 p = bar.p0 + V2f32(2.f, 2.f);
		draw_fancy_line(app, face_id, fcolor_zero(), &list, p);
		
		if(!def_get_config_b32(vars_save_string_lit("f4_disable_progress_bar")))
		{
			f32 progress = (f32)cursor.line / (f32)buffer_get_line_count(app, buffer);
			Rect_f32 progress_bar_rect =
			{
				bar.x0 + (bar.x1 - bar.x0) * progress,
				bar.y0,
				bar.x1,
				bar.y1,
			};
			ARGB_Color progress_bar_color = fcolor_resolve(fcolor_id(fleury_color_file_progress_bar));
			if(argb_is_valid(progress_bar_color))
			{
				draw_rectangle(app, progress_bar_rect, 0, progress_bar_color);
			}
		}
	}
	
	function void render(Application_Links *app, Frame_Info frame_info, View_ID view_id) {
		F4_RecentFiles_RefreshView(app, view_id);
		
		ProfileScope(app, "[Fleury] Render");
		Scratch_Block scratch(app);
		
		View_ID active_view = get_active_view(app, Access_Always);
		b32 is_active_view = (active_view == view_id);
		
		f32 margin_size = cast(f32)def_get_config_u64(app, vars_save_string_lit("f4_margin_size"));
		Rect_f32 view_rect = view_get_screen_rect(app, view_id);
		Rect_f32 region = rect_inner(view_rect, margin_size);
		
		Buffer_ID buffer = view_get_buffer(app, view_id, Access_Always);
		String_Const_u8 buffer_name = push_buffer_base_name(app, scratch, buffer);
		
		//~ NOTE(rjf): Draw background.
		{
			ARGB_Color color = fcolor_resolve(fcolor_id(defcolor_back));
			if(string_match(buffer_name, string_u8_litexpr("*compilation*")))
			{
				color = color_blend(color, 0.5f, 0xff000000);
			}
			// NOTE(rjf): Inactive background color.
			else if(is_active_view == 0)
			{
				ARGB_Color inactive_bg_color = fcolor_resolve(fcolor_id(fleury_color_inactive_pane_background));
				if(argb_is_valid(inactive_bg_color))
				{
					color = inactive_bg_color;
				}
			}
			draw_rectangle(app, region, 0.f, color);
			draw_margin(app, view_rect, region, color);
		}
		
		//~ NOTE(rjf): Draw margin.
		{
			ARGB_Color color = fcolor_resolve(fcolor_id(defcolor_margin));
			if(def_get_config_b32(vars_save_string_lit("f4_margin_use_mode_color")) &&
			   is_active_view)
			{
				color = get_color(app, make_cursor_color_context(power_mode.enabled ? Color_Flag_PowerMode : 0,
																 global_keybinding_mode));
			}
			draw_margin(app, view_rect, region, color);
		}
		
		Rect_f32 prev_clip = draw_set_clip(app, region);
		
		Face_ID face_id = get_face_id(app, buffer);
		Face_Metrics face_metrics = get_face_metrics(app, face_id);
		f32 line_height = face_metrics.line_height;
		f32 digit_advance = face_metrics.decimal_digit_advance;
		
		// NOTE(allen): file bar
		b64 showing_file_bar = false;
		if(view_get_setting(app, view_id, ViewSetting_ShowFileBar, &showing_file_bar) && showing_file_bar)
		{
			Rect_f32_Pair pair = layout_file_bar_on_top(region, line_height);
			nne::draw_file_bar(app, view_id, buffer, face_id, pair.min);
			region = pair.max;
		}
		
		Buffer_Scroll scroll = view_get_buffer_scroll(app, view_id);
		Buffer_Point_Delta_Result delta = delta_apply(app, view_id, frame_info.animation_dt, scroll);
		
		if(!block_match_struct(&scroll.position, &delta.point))
		{
			block_copy_struct(&scroll.position, &delta.point);
			view_set_buffer_scroll(app, view_id, scroll, SetBufferScroll_NoCursorChange);
		}
		
		if(delta.still_animating)
		{
			animate_in_n_milliseconds(app, 0);
		}
		
		// NOTE(allen): query bars
		{
			Query_Bar *space[32];
			Query_Bar_Ptr_Array query_bars = {};
			query_bars.ptrs = space;
			if (get_active_query_bars(app, view_id, ArrayCount(space), &query_bars))
			{
				for (i32 i = 0; i < query_bars.count; i += 1)
				{
					Rect_f32_Pair pair = layout_query_bar_on_top(region, line_height, 1);
					draw_query_bar(app, query_bars.ptrs[i], face_id, pair.min);
					region = pair.max;
				}
			}
		}
		
		// NOTE(allen): FPS hud
		if(show_fps_hud)
		{
			Rect_f32_Pair pair = layout_fps_hud_on_bottom(region, line_height);
			draw_fps_hud(app, frame_info, face_id, pair.max);
			region = pair.min;
			animate_in_n_milliseconds(app, 1000);
		}
		
		// NOTE(allen): layout line numbers
		Rect_f32 line_number_rect = {};
		if(def_get_config_b32(vars_save_string_lit("show_line_number_margins")))
		{
			Rect_f32_Pair pair = layout_line_number_margin(app, buffer, region, digit_advance);
			line_number_rect = pair.min;
			line_number_rect.x1 += 4;
			region = pair.max;
		}
		
		// NOTE(allen): begin buffer render
		Buffer_Point buffer_point = scroll.position;
		if(is_active_view)
		{
			buffer_point.pixel_shift.y += F4_PowerMode_ScreenShake()*1.f;
		}
		Text_Layout_ID text_layout_id = text_layout_create(app, buffer, region, buffer_point);
		
		// NOTE(allen): draw line numbers
		if(def_get_config_b32(vars_save_string_lit("show_line_number_margins")))
		{
			draw_line_number_margin(app, view_id, buffer, face_id, text_layout_id, line_number_rect);
		}
		
		// draw the buffer
		render_buffer(app, view_id, face_id, buffer, text_layout_id, region, frame_info);
		
		text_layout_free(app, text_layout_id);
		draw_set_clip(app, prev_clip);
	}
	
	//~ NOTE(rjf): Begin buffer hook
	
	function void do_full_lex_async_internal(Async_Context *actx, Buffer_ID buffer_id) {
		Application_Links *app = actx->app;
		ProfileScope(app, "[F4] Async Lex");
		Scratch_Block scratch(app);
		
		String_Const_u8 contents = {};
		{
			ProfileBlock(app, "[F4] Async Lex Contents (before mutex)");
			acquire_global_frame_mutex(app);
			ProfileBlock(app, "[F4] Async Lex Contents (after mutex)");
			contents = push_whole_buffer(app, scratch, buffer_id);
			release_global_frame_mutex(app);
		}
		
		i32 limit_factor = 10000;
		
		Token_List list = {};
		b32 canceled = false;
		
		F4_Language *language = language_from_buffer(app, buffer_id);
		
		// NOTE(rjf): Fall back to C++ if we don't have a proper language.
		if(language == 0)
		{
			language = language_from_string(S8Lit("cpp"));
		}
		
		if(language != 0)
		{
			void *lexing_state = push_array_zero(scratch, u8, language->lex_state_size);
			language->lexer_initter(lexing_state, contents);
			for(;;)
			{
				ProfileBlock(app, "[F4] Async Lex Block");
				if(language->lexer(scratch, &list, lexing_state, limit_factor))
				{
					break;
				}
				if(async_check_canceled(actx))
				{
					canceled = true;
					break;
				}
			}
		}
		
		if(!canceled)
		{
			ProfileBlock(app, "[F4] Async Lex Save Results (before mutex)");
			acquire_global_frame_mutex(app);
			ProfileBlock(app, "[F4] Async Lex Save Results (after mutex)");
			Managed_Scope scope = buffer_get_managed_scope(app, buffer_id);
			if(scope != 0)
			{
				Base_Allocator *allocator = managed_scope_allocator(app, scope);
				Token_Array *tokens_ptr = scope_attachment(app, scope, attachment_tokens, Token_Array);
				base_free(allocator, tokens_ptr->tokens);
				Token_Array tokens = {};
				tokens.tokens = base_array(allocator, Token, list.total_count);
				tokens.count = list.total_count;
				tokens.max = list.total_count;
				token_fill_memory_from_list(tokens.tokens, &list);
				block_copy_struct(tokens_ptr, &tokens);
			}
			buffer_mark_as_modified(buffer_id);
			release_global_frame_mutex(app);
		}
	}
	
	function void do_full_lex_async(Async_Context *actx, String_Const_u8 data) {
		if(data.size == sizeof(Buffer_ID))
		{
			Buffer_ID buffer = *(Buffer_ID*)data.str;
			do_full_lex_async_internal(actx, buffer);
		}
	}
	
	function i32 begin_buffer(Application_Links *app, Buffer_ID buffer_id) {
		ProfileScope(app, "[Fleury] Begin Buffer");
		
		Scratch_Block scratch(app);
		b32 treat_as_code = false;
		String_Const_u8 file_name = push_buffer_file_name(app, scratch, buffer_id);
		String_Const_u8 buffer_name = push_buffer_base_name(app, scratch, buffer_id);
		
		// NOTE(rjf): Treat as code if the config tells us to.
		if(treat_as_code == false)
		{
			if(file_name.size > 0)
			{
				String_Const_u8 treat_as_code_string = def_get_config_string(scratch, vars_save_string_lit("treat_as_code"));
				String_Const_u8_Array extensions = parse_extension_line_to_extension_list(app, scratch, treat_as_code_string);
				String_Const_u8 ext = string_file_extension(file_name);
				for(i32 i = 0; i < extensions.count; ++i)
				{
					if(string_match(ext, extensions.strings[i]))
					{
						treat_as_code = true;
						break;
					}
				}
			}
		}
		
		// NOTE(rjf): Treat as code for *calc* and *peek* buffers.
		if(treat_as_code == false)
		{
			if(buffer_name.size > 0)
			{
				if(string_match(buffer_name, string_u8_litexpr("*calc*")))
				{
					treat_as_code = true;
				}
				else if(string_match(buffer_name, string_u8_litexpr("*peek*")))
				{
					treat_as_code = true;
				}
			}
		}
		
		// NOTE(rjf): Treat as code if we've identified the language of a file.
		if(treat_as_code == false)
		{
			F4_Language *language = language_from_buffer(app, buffer_id);
			if(language)
			{
				treat_as_code = true;
			}
		}
		
		String_ID file_map_id = vars_save_string_lit("keys_file");
		String_ID code_map_id = vars_save_string_lit("keys_code");
		
		Command_Map_ID map_id = (treat_as_code) ? (code_map_id) : (file_map_id);
		Managed_Scope scope = buffer_get_managed_scope(app, buffer_id);
		Command_Map_ID *map_id_ptr = scope_attachment(app, scope, buffer_map_id, Command_Map_ID);
		*map_id_ptr = map_id;
		
		Line_Ending_Kind setting = guess_line_ending_kind_from_buffer(app, buffer_id);
		Line_Ending_Kind *eol_setting = scope_attachment(app, scope, buffer_eol_setting, Line_Ending_Kind);
		*eol_setting = setting;
		
		// NOTE(allen): Decide buffer settings
		b32 wrap_lines = true;
		b32 use_lexer = false;
		if(treat_as_code)
		{
			wrap_lines = def_get_config_b32(vars_save_string_lit("enable_code_wrapping"));
			use_lexer = true;
		}
		
		if(string_match(buffer_name, string_u8_litexpr("*compilation*")))
		{
			wrap_lines = false;
		}
		
		if (use_lexer)
		{
			ProfileBlock(app, "begin buffer kick off lexer");
			Async_Task *lex_task_ptr = scope_attachment(app, scope, buffer_lex_task, Async_Task);
			*lex_task_ptr = async_task_no_dep(&global_async_system, do_full_lex_async, make_data_struct(&buffer_id));
		}
		
		{
			b32 *wrap_lines_ptr = scope_attachment(app, scope, buffer_wrap_lines, b32);
			*wrap_lines_ptr = wrap_lines;
		}
		
		if (use_lexer)
		{
			buffer_set_layout(app, buffer_id, layout_virt_indent_index_generic);
		}
		else
		{
			if (treat_as_code)
			{
				buffer_set_layout(app, buffer_id, layout_virt_indent_literal_generic);
			}
			else{
				buffer_set_layout(app, buffer_id, layout_generic);
			}
		}
		
		
		// no meaning for return
		return(0);
	}
	
	
	//~ Layout.
	
	function Layout_Item_List layout_internal(Application_Links *app, Arena *arena, Buffer_ID buffer, Range_i64 range, Face_ID face, f32 width, Layout_Virtual_Indent virt_indent) {
		Layout_Item_List list = get_empty_item_list(range);
		
		Scratch_Block scratch(app);
		String_Const_u8 text = push_buffer_range(app, scratch, buffer, range);
		
		Face_Advance_Map advance_map = get_face_advance_map(app, face);
		Face_Metrics metrics = get_face_metrics(app, face);
		f32 tab_width = (f32)def_get_config_u64(app, vars_save_string_lit("default_tab_width"));
		tab_width = clamp_bot(1, tab_width);
		LefRig_TopBot_Layout_Vars pos_vars = get_lr_tb_layout_vars(&advance_map, &metrics, tab_width, width);
		
		if (text.size == 0){
			lr_tb_write_blank(&pos_vars, face, arena, &list, range.first);
		}
		else{
			b32 skipping_leading_whitespace = (virt_indent == LayoutVirtualIndent_On);
			Newline_Layout_Vars newline_vars = get_newline_layout_vars();
			
			u8 *ptr = text.str;
			u8 *end_ptr = ptr + text.size;
			for (;ptr < end_ptr;){
				Character_Consume_Result consume = utf8_consume(ptr, (u64)(end_ptr - ptr));
				
				i64 index = layout_index_from_ptr(ptr, text.str, range.first);
				switch (consume.codepoint){
					case '\t':
					case ' ':
					{
						newline_layout_consume_default(&newline_vars);
						f32 advance = lr_tb_advance(&pos_vars, face, consume.codepoint);
						if (!skipping_leading_whitespace){
							lr_tb_write_with_advance(&pos_vars, face, advance, arena, &list, index, consume.codepoint);
						}
						else{
							lr_tb_advance_x_without_item(&pos_vars, advance);
						}
					}break;
					
					default:
					{
						newline_layout_consume_default(&newline_vars);
						lr_tb_write(&pos_vars, face, arena, &list, index, consume.codepoint);
					}break;
					
					case '\r':
					{
						newline_layout_consume_CR(&newline_vars, index);
					}break;
					
					case '\n':
					{
						i64 newline_index = newline_layout_consume_LF(&newline_vars, index);
						lr_tb_write_blank(&pos_vars, face, arena, &list, newline_index);
						lr_tb_next_line(&pos_vars);
					}break;
					
					case max_u32:
					{
						newline_layout_consume_default(&newline_vars);
						lr_tb_write_byte(&pos_vars, face, arena, &list, index, *ptr);
					}break;
				}
				
				ptr += consume.inc;
			}
			
			if (newline_layout_consume_finish(&newline_vars)){
				i64 index = layout_index_from_ptr(ptr, text.str, range.first);
				lr_tb_write_blank(&pos_vars, face, arena, &list, index);
			}
		}
		
		layout_item_list_finish(&list, -pos_vars.line_to_text_shift);
		
		return(list);
	}
	
	function Layout_Item_List layout(Application_Links *app, Arena *arena, Buffer_ID buffer, Range_i64 range, Face_ID face, f32 width) {
		return layout_internal(app, arena, buffer, range, face, width, LayoutVirtualIndent_Off);
	}
	
	//~ Tick.
	
	function void tick(Application_Links *app, Frame_Info frame_info) {
		linalloc_clear(&global_frame_arena);
		global_tooltip_count = 0;
		
		tick_colors(app, frame_info);
		index__tick(app);
		calculator__tick(frame_info);
		F4_PowerMode_Tick(app, frame_info);
		F4_UpdateFlashes(app, frame_info);
		
		// Default tick stuff from the 4th dimension:
		default_tick(app, frame_info);
	}
	
	//~ Whole Screen Render.
	
	function void whole_screen_render(Application_Links *app, Frame_Info frame_info) {
		F4_PowerMode_RenderWholeScreen(app, frame_info);
	}
	
	//~ Buffer Edit Range.
	
	function i32 buffer_edit_range(Application_Links *app, Buffer_ID buffer_id, Range_i64 new_range, Range_Cursor old_cursor_range) {
		// buffer_id, new_range, original_size
		ProfileScope(app, "[F4] Buffer Edit Range");
		
		Range_i64 old_range = Ii64(old_cursor_range.min.pos, old_cursor_range.max.pos);
		
		buffer_shift_fade_ranges(buffer_id, old_range.max, (new_range.max - old_range.max));
		
		{
			code_index_lock();
			Code_Index_File *file = code_index_get_file(buffer_id);
			if (file != 0){
				code_index_shift(file, old_range, range_size(new_range));
			}
			code_index_unlock();
		}
		
		i64 insert_size = range_size(new_range);
		i64 text_shift = replace_range_shift(old_range, insert_size);
		
		Scratch_Block scratch(app);
		
		Managed_Scope scope = buffer_get_managed_scope(app, buffer_id);
		Async_Task *lex_task_ptr = scope_attachment(app, scope, buffer_lex_task, Async_Task);
		
		Base_Allocator *allocator = managed_scope_allocator(app, scope);
		b32 do_full_relex = false;
		
		if (async_task_is_running_or_pending(&global_async_system, *lex_task_ptr)){
			async_task_cancel(app, &global_async_system, *lex_task_ptr);
			buffer_unmark_as_modified(buffer_id);
			do_full_relex = true;
			*lex_task_ptr = 0;
		}
		
		Token_Array *ptr = scope_attachment(app, scope, attachment_tokens, Token_Array);
		if (ptr != 0 && ptr->tokens != 0){
			ProfileBlockNamed(app, "attempt resync", profile_attempt_resync);
			
			i64 token_index_first = token_relex_first(ptr, old_range.first, 1);
			i64 token_index_resync_guess =
				token_relex_resync(ptr, old_range.one_past_last, 16);
			
			if (token_index_resync_guess - token_index_first >= 4000){
				do_full_relex = true;
			}
			else{
				Token *token_first = ptr->tokens + token_index_first;
				Token *token_resync = ptr->tokens + token_index_resync_guess;
				
				Range_i64 relex_range = Ii64(token_first->pos, token_resync->pos + token_resync->size + text_shift);
				String_Const_u8 partial_text = push_buffer_range(app, scratch, buffer_id, relex_range);
				
				//~ NOTE(rjf): Lex
				F4_Language *language = language_from_buffer(app, buffer_id);
				// NOTE(rjf): Fall back to C++ if we don't have a proper language.
				if(language == 0)
				{
					language = language_from_string(S8Lit("cpp"));
				}
				Token_List relex_list = F4_Language_LexFullInput_NoBreaks(app, language, scratch, partial_text);
				//~
				
				if (relex_range.one_past_last < buffer_get_size(app, buffer_id)){
					token_drop_eof(&relex_list);
				}
				
				Token_Relex relex = token_relex(relex_list, relex_range.first - text_shift, ptr->tokens, token_index_first, token_index_resync_guess);
				
				ProfileCloseNow(profile_attempt_resync);
				
				if (!relex.successful_resync){
					do_full_relex = true;
				}
				else{
					ProfileBlock(app, "apply resync");
					
					i64 token_index_resync = relex.first_resync_index;
					
					Range_i64 head = Ii64(0, token_index_first);
					Range_i64 replaced = Ii64(token_index_first, token_index_resync);
					Range_i64 tail = Ii64(token_index_resync, ptr->count);
					i64 resynced_count = (token_index_resync_guess + 1) - token_index_resync;
					i64 relexed_count = relex_list.total_count - resynced_count;
					i64 tail_shift = relexed_count - (token_index_resync - token_index_first);
					
					i64 new_tokens_count = ptr->count + tail_shift;
					Token *new_tokens = base_array(allocator, Token, new_tokens_count);
					
					Token *old_tokens = ptr->tokens;
					block_copy_array_shift(new_tokens, old_tokens, head, 0);
					token_fill_memory_from_list(new_tokens + replaced.first, &relex_list, relexed_count);
					for (i64 i = 0, index = replaced.first; i < relexed_count; i += 1, index += 1){
						new_tokens[index].pos += relex_range.first;
					}
					for (i64 i = tail.first; i < tail.one_past_last; i += 1){
						old_tokens[i].pos += text_shift;
					}
					block_copy_array_shift(new_tokens, ptr->tokens, tail, tail_shift);
					
					base_free(allocator, ptr->tokens);
					
					ptr->tokens = new_tokens;
					ptr->count = new_tokens_count;
					ptr->max = new_tokens_count;
					
					buffer_mark_as_modified(buffer_id);
				}
			}
		}
		
		if (do_full_relex) {
			*lex_task_ptr = async_task_no_dep(&global_async_system, do_full_lex_async, make_data_struct(&buffer_id));
		}
		
		// no meaning for return
		return(0);
	}
	
}

#endif // FCODER_CUSTOM_HOOKS_CPP
