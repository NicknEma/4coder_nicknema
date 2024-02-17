#ifndef FCODER_CUSTOM_RENDER_HELPERS_CPP
#define FCODER_CUSTOM_RENDER_HELPERS_CPP

namespace nne {
	
	global Flash global_flashes[64];
	
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
	
	//~ Hex color preview.
	
	// @Note(ema): Provided by thevaber at https://gist.github.com/thevaber/58bb6a1c03ebe56309545f413e898a95
	
	function u32 calculate_color_brightness(u32 color) {
		u32 r = ((color >> 16) & 0xFF);
		u32 g = ((color >>  8) & 0xFF);
		u32 b = ((color >>  0) & 0xFF);
		
		// @Cleanup: Magic numbers!
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
	
	//~ Brace highlight.
	
	// @Note(ema): Based on draw_paren_highlight from 4coder_draw.cpp
	function void draw_brace_highlight(Application_Links *app, Buffer_ID buffer, Text_Layout_ID text_layout_id, i64 pos, ARGB_Color *colors, i32 color_count) {
		ProfileScope(app, "Brace Highlight");
		
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
	
	function void draw_tooltip_rect(Application_Links *app, Rect_f32 rect) {
		ARGB_Color background_color = fcolor_resolve(fcolor_id(defcolor_back));
		ARGB_Color border_color = fcolor_resolve(fcolor_id(defcolor_margin_active));
		
		background_color &= 0x00ffffff;
		background_color |= 0xd0000000;
		
		border_color &= 0x00ffffff;
		border_color |= 0xd0000000;
		
		draw_rectangle(app, rect, 4.f, background_color);
		draw_rectangle_outline(app, rect, 4.f, 3.f, border_color);
	}
	
	function void render_range_highlight(Application_Links *app, View_ID view_id, Text_Layout_ID text_layout_id, Range_i64 range, Range_Highlight_Kind kind, ARGB_Color color) {
		Rect_f32 range_start_rect = text_layout_character_on_screen(app, text_layout_id, range.start);
		Rect_f32 range_end_rect   = text_layout_character_on_screen(app, text_layout_id, range.end-1);
		Rect_f32 total_range_rect = {};
		total_range_rect.x0 = min_of(range_start_rect.x0, range_end_rect.x0);
		total_range_rect.y0 = min_of(range_start_rect.y0, range_end_rect.y0);
		total_range_rect.x1 = max_of(range_start_rect.x1, range_end_rect.x1);
		total_range_rect.y1 = max_of(range_start_rect.y1, range_end_rect.y1);
		
		switch (kind) {
			case Range_Highlight_Kind::Underline: {
				total_range_rect.y0 = total_range_rect.y1 - 1.f;
				total_range_rect.y1 += 1.f;
			} break;
			
			case Range_Highlight_Kind::Minor_Underline: {
				total_range_rect.y0 = total_range_rect.y1 - 1.f;
				total_range_rect.y1 += 1.f;
			}
		}
		
		draw_rectangle(app, total_range_rect, 4.f, color);
	}
	
	function void push_tooltip(String_Const_u8 string, ARGB_Color color) {
		if (global_tooltip_count < ArrayCount(global_tooltips)) {
			String_Const_u8 string_copy = push_string_copy(&global_frame_arena, string);
			global_tooltips[global_tooltip_count].color  = color;
			global_tooltips[global_tooltip_count].string = string_copy;
			global_tooltip_count += 1;
		}
	}
	
	//~ Flashes
	
	function void push_flash(Application_Links *app, Buffer_ID buffer, Range_i64 range, ARGB_Color color, f32 decay_rate) {
		Flash *flash = 0;
		for (int i = 0; i < ArrayCount(global_flashes); i += 1) {
			if (global_flashes[i].active == 0) {
				flash = global_flashes + i;
				break;
			}
		}
		
		if (flash) {
			flash->active = true;
			flash->t = 1;
			flash->buffer = buffer;
			flash->range = range;
			flash->color = color;
			flash->decay_rate = decay_rate;
		}
	}
	
	function void update_flashes(Application_Links *app, Frame_Info frame) {
		for (int i = 0; i < ArrayCount(global_flashes); i += 1) {
			Flash *flash = global_flashes + i;
			if (flash->active) {
				animate_in_n_milliseconds(app, 0);
				flash->t += (0 - flash->t) * flash->decay_rate * frame.animation_dt;
				if (flash->t <= 0.05f) {
					flash->active = false;
				}
			}
		}
	}
	
	function void render_flashes(Application_Links *app, View_ID view, Text_Layout_ID text_layout) {
		Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
		for (int i = 0; i < ArrayCount(global_flashes); i += 1) {
			Flash *flash = global_flashes + i;
			if (flash->active && flash->buffer == buffer) {
				render_range_highlight(app, view, text_layout, flash->range, Range_Highlight_Kind::Whole, argb_color_blend(flash->color, flash->t, 0, 1-flash->t));
			}
		}
	}
	
	//~ Closing-brace Annotation
	
	function void render_close_brace_annotation(Application_Links *app, Buffer_ID buffer, Text_Layout_ID text_layout_id, i64 pos) {
		if (!def_get_config_b32(vars_save_string_lit("f4_disable_close_brace_annotation"))) {
			ProfileScope(app, "Brace Annotation");
			
			Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
			Token_Array token_array = get_token_array_from_buffer(app, buffer);
			Face_ID face_id = global_small_code_face;
			
			if (token_array.tokens != 0) {
				Token_Iterator_Array it = token_iterator_pos(0, &token_array, pos);
				Token *token = token_it_read(&it);
				
				if (token != 0 && token->kind == TokenBaseKind_ScopeOpen) {
					pos = token->pos + token->size;
				} else if (token_it_dec_all(&it)) {
					token = token_it_read(&it);
					if (token->kind == TokenBaseKind_ScopeClose && pos == token->pos + token->size) {
						pos = token->pos;
					}
				}
			}
			
			Scratch_Block scratch(app);
			Range_i64_Array ranges = get_enclosure_ranges(app, scratch, buffer, pos, RangeHighlightKind_CharacterHighlight);
			
			for (i32 i = ranges.count - 1; i >= 0; i -= 1) {
				Range_i64 range = ranges.ranges[i];
				
				// NOTE(rjf): Turn this on to only display end scope annotations where the top is off-screen.
#if 0
				if (range.start >= visible_range.start) {
					continue;
				}
#else
				// NOTE(jack): Prevent brace annotations from printing on single line scopes.
				if (get_line_number_from_pos(app, buffer, range.start) == get_line_number_from_pos(app, buffer, range.end)) {
					continue;
				}
#endif
				
				i64 line = get_line_number_from_pos(app, buffer, range.end);
				i64 last_char = get_line_end_pos(app, buffer, line)-1;
				
				Rect_f32 close_scope_rect = text_layout_character_on_screen(app, text_layout_id, last_char);
				Vec2_f32 close_scope_pos = { close_scope_rect.x0 + 12, close_scope_rect.y0 };
				
				//- Find token set before this scope begins.
				Token *start_token = 0;
				i64 token_count = 0;
				{
					Token_Iterator_Array it = token_iterator_pos(0, &token_array, range.start-1);
					int paren_nest = 0;
					
					for (;;) {
						Token *token = token_it_read(&it);
						
						if (token) {
							token_count += 1;
							
							if (token->kind == TokenBaseKind_ParentheticalClose) {
								++paren_nest;
							} else if (token->kind == TokenBaseKind_ParentheticalOpen) {
								--paren_nest;
							} else if (paren_nest == 0 &&
									   (token->kind == TokenBaseKind_ScopeClose ||
										(token->kind == TokenBaseKind_StatementClose && token->sub_kind != TokenCppKind_Colon))) {
								break;
							} else if ((token->kind == TokenBaseKind_Identifier || token->kind == TokenBaseKind_Keyword ||
										token->kind == TokenBaseKind_Comment) &&
									   !paren_nest) {
								start_token = token;
								break;
							}
							
						} else { break; }
						
						if (!token_it_dec_non_whitespace(&it)) {
							break;
						}
					}
				}
				
				//- Draw the annotation.
				if (start_token) {
					ARGB_Color  color  = finalize_color(defcolor_comment, 0);
					Color_Array colors = finalize_color_array(fleury_color_brace_annotation);
					if (colors.count >= 1 && argb_is_valid(colors.vals[0])) {
						color = colors.vals[(ranges.count - i - 1) % colors.count];
					}
					
					String_Const_u8 start_line = push_buffer_line(app, scratch, buffer, get_line_number_from_pos(app, buffer, start_token->pos));
					
					u64 first_non_whitespace_offset = 0;
					for (u64 c = 0; c < start_line.size; c += 1) {
						if (start_line.str[c] <= 32) {
							first_non_whitespace_offset += 1;
						} else {
							break;
						}
					}
					
					start_line.str  += first_non_whitespace_offset;
					start_line.size -= first_non_whitespace_offset;
					
					if (start_line.str[start_line.size - 1] == 13) {
						// Special case to handle CRLF-newline files.
						
						start_line.size -= 1;
					}
					
					draw_string(app, face_id, start_line, close_scope_pos, color);
				}
			}
		}
		
	}
	
	//~ Brace lines
	
	function void render_brace_vertical_lines(Application_Links *app, Buffer_ID buffer, View_ID view, Text_Layout_ID text_layout_id, i64 pos) {
		if (!def_get_config_b32(vars_save_string_lit("f4_disable_brace_lines"))) { // @Cleanup: Pull out this check
			ProfileScope(app, "Brace Lines");
			
			Face_ID face_id = get_face_id(app, buffer);
			Token_Array token_array = get_token_array_from_buffer(app, buffer);
			Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
			
			if (token_array.tokens != 0) {
				Token_Iterator_Array it = token_iterator_pos(0, &token_array, pos);
				Token *token = token_it_read(&it);
				if (token && token->kind == TokenBaseKind_ScopeOpen) {
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
			
			Face_Metrics metrics = get_face_metrics(app, face_id);
			
			Scratch_Block scratch(app);
			Range_i64_Array ranges = get_enclosure_ranges(app, scratch, buffer, pos, RangeHighlightKind_CharacterHighlight);
			
			Rect_f32 line_number_rect = {};
			b32 show_line_number_margins = def_get_config_b32(vars_save_string_lit("show_line_number_margins"));
			if (show_line_number_margins) {
				Rect_f32 rect = view_get_screen_rect(app, view);
				
				Face_Metrics face_metrics = get_face_metrics(app, face_id);
				f32 digit_advance = face_metrics.decimal_digit_advance;
				
				Rect_f32_Pair pair = layout_line_number_margin(app, buffer, rect, digit_advance);
				line_number_rect = pair.min;
				line_number_rect.x1 += 4;
			}
			
			float x_offset   = view_get_screen_rect(app, view).x0 + 4 - view_get_buffer_scroll(app, view).position.pixel_shift.x + (line_number_rect.x1 - line_number_rect.x0);
			float x_position = 0.f;
			
			u64 vw_indent = def_get_config_u64(app, vars_save_string_lit("virtual_whitespace_regular_indent"));
			
			for (i32 i = ranges.count - 1; i >= 0; i -= 1) {
				Range_i64 range = ranges.ranges[i];
				
				Rect_f32 range_start_rect = text_layout_character_on_screen(app, text_layout_id, range.start);
				Rect_f32 range_end_rect   = text_layout_character_on_screen(app, text_layout_id, range.end);
				
				if (def_enable_virtual_whitespace) {
					x_position = (ranges.count - i - 1) * metrics.space_advance * vw_indent;
				} else {
					String_Const_u8 line = push_buffer_line(app, scratch, buffer, get_line_number_from_pos(app, buffer, range.end));
					for (u64 char_idx = 0; char_idx < line.size; char_idx += 1) {
						if (!character_is_whitespace(line.str[char_idx])) {
							x_position = metrics.space_advance * char_idx;
							break;
						}
					}
				}
				
				float y_start = 0;
				float y_end = 10000;
				if (range.start >= visible_range.start) {
					y_start = range_start_rect.y0 + metrics.line_height;
				}
				if (range.end <= visible_range.end) {
					y_end = range_end_rect.y0;
				}
				
				Rect_f32 line_rect = {0};
				line_rect.x0 = x_position+x_offset;
				line_rect.x1 = x_position+1+x_offset;
				line_rect.y0 = y_start;
				line_rect.y1 = y_end;
				
				Color_Array colors = finalize_color_array(fleury_color_brace_line);
				if (colors.count >= 1 && argb_is_valid(colors.vals[0])) {
					draw_rectangle(app, line_rect, 0.5f, colors.vals[(ranges.count - i - 1) % colors.count]);
				}
			}
		}
	}
}

#endif // FCODER_CUSTOM_RENDER_HELPERS_CPP
