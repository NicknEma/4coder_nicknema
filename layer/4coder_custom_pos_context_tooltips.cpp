#ifndef FCODER_CUSTOM_POS_CONTEXT_TOOLTIPS_CPP
#define FCODER_CUSTOM_POS_CONTEXT_TOOLTIPS_CPP

namespace nne {
	
	function Vec2_f32 render_positional_context_definition_tokens(Application_Links *app, Face_ID face, String_Const_u8 backing_string, Token_Array tokens, b32 do_render, int highlight_arg, Vec2_f32 text_position, f32 max_x) {
		Scratch_Block scratch(app);
		
		Vec2_f32 starting_text_pos = text_position;
		Face_Metrics metrics = get_face_metrics(app, face);
		
		Token_Iterator_Array it = token_iterator_pos(0, &tokens, 0);
		b32 found_first_open_paren = false;
		for (int arg_idx = 0;; ) {
			Token *token = token_it_read(&it);
			if (!token) {
				break;
			}
			
			if (token->kind == TokenBaseKind_Whitespace) {
				text_position.x += get_string_advance(app, face, string_u8_litexpr(" "));
			} else {
				ARGB_Color color = finalize_color(defcolor_text_default, 0);
				if (token->kind == TokenBaseKind_StatementClose) {
					String_Const_u8 str = string_substring(backing_string, Ii64(token));
					if (string_match(str, S8Lit(","))) {
						arg_idx += 1;
					}
				} else if (token->kind == TokenBaseKind_ParentheticalOpen) {
					found_first_open_paren = true;
				}
				
				// Highlight
				b32 highlight = false;
				if(found_first_open_paren && arg_idx == highlight_arg &&
				   (token->kind == TokenBaseKind_Identifier ||
					token->kind == TokenBaseKind_Operator ||
					token->kind == TokenBaseKind_Keyword)) {
					color = finalize_color(fleury_color_token_highlight, 0);
					highlight = true;
				}
				
				Vec2_f32 start_pos = text_position;
				String_Const_u8 token_string = string_substring(backing_string, Ii64(token->pos, token->pos+token->size));
				f32 string_advance = get_string_advance(app, face, token_string);
				if (text_position.x + string_advance >= max_x) {
					text_position.x = starting_text_pos.x;
					text_position.y += metrics.line_height;
				}
				if (do_render) {
					draw_string(app, face, token_string, text_position, color);
				}
				text_position.x += string_advance;
				
				if (highlight) {
					if (do_render) {
						draw_rectangle(app, Rf32(start_pos.x, start_pos.y + metrics.line_height, text_position.x, start_pos.y + metrics.line_height + 2.f), 1.f, color);
					}
				}
			}
			
			if (token_it_inc_all(&it) == 0) {
				break;
			}
		}
		
		return text_position;
	}
	
	internal void render_positional_context_tooltips(Application_Links *app, View_ID view, Buffer_ID buffer, Text_Layout_ID text_layout_id, i64 pos) {
		if (def_get_config_b32(vars_save_string_lit("f4_disable_poscontext"))) {
			return; // @Cleanup: Decide for one consistent thing: either all checks are inside their respective functions, or they are all outside...
		}
		
		ProfileScope(app, "Pos Context Rendering");
		Scratch_Block scratch(app);
		
		Rect_f32 cursor_rect = text_layout_character_on_screen(app, text_layout_id, pos);
		Rect_f32 view_rect = view_get_screen_rect(app, view);
		Face_ID face = global_small_code_face;
		Face_Metrics metrics = get_face_metrics(app, face);
		F4_Language *language = language_from_buffer(app, buffer);
		f32 padding = 4.f;
		
		if (language) {
			
#if 1
			b32 render_at_cursor = true;
			if (def_get_config_b32(vars_save_string_lit("f4_poscontext_draw_at_bottom_of_buffer"))) {
				render_at_cursor = false;
			}
#else
			b32 render_at_cursor = def_get_config_b32(vars_save_string_lit("f4_poscontext_draw_at_bottom_of_buffer"));
#endif
			
			Vec2_f32 tooltip_position = {
				global_cursor_rect.x0,
				global_cursor_rect.y1,
			};
			
			Positional_Context_Data *ctx_list = language->context_getter(app, scratch, buffer, pos);
			if (!render_at_cursor) {
				f32 height = 0;
				for (Positional_Context_Data *ctx = ctx_list; ctx; ctx = ctx->next) {
					height += metrics.line_height + 2*padding;
				}
				tooltip_position = V2f32(view_rect.x0, view_rect.y1 - height);
			}
			
			for (Positional_Context_Data *ctx = ctx_list; ctx; ctx = ctx->next) {
				Index__Note *note = ctx->relevant_note;
				if (note && note->file) {
					
					if (note->kind == Index__Note_Kind_Function || note->kind == Index__Note_Kind_Macro) {
						//~ Render function tooltip.
						
						//- Find range of definition + params
						Range_i64 definition_range = note->range;
						{
							Token_Array defbuffer_tokens = get_token_array_from_buffer(app, note->file->buffer);
							Token_Iterator_Array it = token_iterator_pos(0, &defbuffer_tokens, note->range.min);
							int paren_nest = 0;
							for (; token_it_inc_all(&it); ) {
								Token *token = token_it_read(&it);
								if (token) {
									if (token->kind == TokenBaseKind_ParentheticalOpen) {
										paren_nest += 1;
									}
									if (token->kind == TokenBaseKind_ParentheticalClose) {
										paren_nest -= 1;
										if (paren_nest == 0) {
											definition_range.max = token->pos + token->size;
											break;
										}
									}
								}
							}
						}
						
						String_Const_u8 definition_string = push_buffer_range(app, scratch, note->file->buffer, definition_range);
						Token_Array definition_tokens = token_array_from_text(app, scratch, definition_string);
						
						//- Calculate needed size for this tooltip.
						f32 max_x = view_rect.x1-view_rect.x0;
						Vec2_f32 end_draw_position = render_positional_context_definition_tokens(app, face, definition_string, definition_tokens, false, 0, V2f32(0, 0), max_x);
						Vec2_f32 needed_size = {
							(end_draw_position.y > 0) ? max_x : end_draw_position.x,
							end_draw_position.y,
						};
						
						Rect_f32 draw_rect = {
							tooltip_position.x,
							tooltip_position.y,
							tooltip_position.x + needed_size.x + 2*padding,
							tooltip_position.y + needed_size.y + metrics.line_height + 2*padding,
						};
						if (draw_rect.x1 > view_rect.x1) {
							f32 width = rect_width(draw_rect);
							draw_rect.x0 = cast(f32)cast(int)(view_rect.x1 - width);
							draw_rect.x1 = view_rect.x1;
						}
						if (draw_rect.y1 > view_rect.y1) {
							f32 height = rect_height(draw_rect);
							draw_rect.y0 = cast(f32)cast(int)(view_rect.y1 - height);
							draw_rect.y1 = view_rect.y1;
						}
						
						draw_tooltip_rect(app, draw_rect);
						
						//- Render tokens of definition
						{
							Vec2_f32 text_position = {
								draw_rect.x0 + padding,
								draw_rect.y0 + padding,
							};
							
							render_positional_context_definition_tokens(app, face, definition_string, definition_tokens, true, ctx->argument_index, text_position, view_rect.x1);
						}
						
						f32 advance = draw_rect.y1 - draw_rect.y0;
						tooltip_position.y += advance;
					} else if (note->kind == Index__Note_Kind_Type) {
						//~ Render type tooltip.
						
						Token_Array defbuffer_tokens = get_token_array_from_buffer(app, note->file->buffer);
						for (Index__Note *member = note->first_child; member; member = member->next_sibling) {
							Range_i64 member_range = member->range;
							Token_Iterator_Array it = token_iterator_pos(0, &defbuffer_tokens, member->range.min);
							for (;;) {
								Token *token = token_it_read(&it);
								if (token) {
									if (token->kind == TokenBaseKind_StatementClose) {
										member_range.max = token->pos;
										break;
									}
								} else { break; }
								
								if (!token_it_inc_non_whitespace(&it)) {
									break;
								}
							}
							
							String_Const_u8 member_string = push_buffer_range(app, scratch, note->file->buffer, member_range);
							
							Vec2_f32 needed_size = { get_string_advance(app, face, member_string), 0, };
							Rect_f32 draw_rect = {
								tooltip_position.x,
								tooltip_position.y,
								tooltip_position.x + needed_size.x + 2*padding,
								tooltip_position.y + needed_size.y + metrics.line_height + 2*padding,
							};
							
							draw_tooltip_rect(app, draw_rect);
							draw_string(app, face, member_string, V2f32(draw_rect.x0 + padding, draw_rect.y0 + padding), finalize_color(defcolor_text_default, 0));
							
							f32 advance = draw_rect.y1 - draw_rect.y0;
							tooltip_position.y += advance;
						}
					}
				}
			}
		}
	}
	
}

#endif // FCODER_CUSTOM_POS_CONTEXT_TOOLTIPS_CPP
