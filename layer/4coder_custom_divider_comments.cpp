#ifndef FCODER_CUSTOM_DIVIDER_COMMENTS_CPP
#define FCODER_CUSTOM_DIVIDER_COMMENTS_CPP

NAMESPACE_BEGIN(nne)

global String_Const_u8 strong_divider_comment_signifier = string_u8_litexpr("//~");
global String_Const_u8   weak_divider_comment_signifier = string_u8_litexpr("//-");

//~ Rendering divider comments

internal void
render_divider_comments(Application_Links *app, Buffer_ID buffer, View_ID view, Text_Layout_ID text_layout_id) {
	if (!def_get_config_b32(vars_save_string_lit("f4_disable_divider_comments"))) {
		ProfileScope(app, "[F4] Divider Comments");
		Scratch_Block scratch(app);
		
		Token_Array token_array = get_token_array_from_buffer(app, buffer);
		Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
		
		if (token_array.tokens != 0) {
			i64 first_index = token_index_from_pos(&token_array, visible_range.first);
			Token_Iterator_Array it = token_iterator_index(0, &token_array, first_index);
			
			// If the feature is enabled, if it was possible to get the tokens, for all tokens in range:
			for (Token *token = token_it_read(&it); ; token = token_it_read(&it)) {
				
				// token_it_inc_non_whitespace = increase (advance) until non-whitespace. Return true if one was found.
				if (token->pos >= visible_range.one_past_last || token == 0 || !token_it_inc_non_whitespace(&it)) {
					break;
				}
				
				if (token->kind == TokenBaseKind_Comment) {
					Rect_f32 comment_first_char_rect = text_layout_character_on_screen(app, text_layout_id, token->pos);
					Rect_f32 comment_last_char_rect  = text_layout_character_on_screen(app, text_layout_id, token->pos+token->size-1);
					String_Const_u8 token_string        = push_buffer_range(app, scratch, buffer, Ii64(token));
					String_Const_u8 signifier_substring = string_substring(token_string, Ii64(0, 3));
					ARGB_Color comment_color = fcolor_resolve(fcolor_id(defcolor_comment));
					f32        roundness     = 4.0f;
					
					if (string_match(signifier_substring, strong_divider_comment_signifier)) {
						// Strong dividers.
						
						f32 divider_width = 10000; // NOTE(ema): Arbitrary amount that is larger than the screen width. @Hardcoded
						Rect_f32 rect = {
							comment_first_char_rect.x0, comment_first_char_rect.y0 - 2,
							divider_width,              comment_first_char_rect.y0,
						};
						
						draw_rectangle(app, rect, roundness, comment_color);
					} else if (string_match(signifier_substring, weak_divider_comment_signifier)) {
						// Weak dividers.
						
						f32 dash_size = 8;
						f32 dash_gap  = dash_size * 0.5f;
						Rect_f32 rect = {
							(comment_last_char_rect.x1),
							(comment_last_char_rect.y0 + comment_last_char_rect.y1)/2 - 1,
							(comment_last_char_rect.x1 + dash_size),
							(comment_last_char_rect.y0 + comment_last_char_rect.y1)/2 + 1,
						};
						
						int num_dashes = 1000;  // NOTE(ema): Enough to fill the whole screen. @Hardcoded
						for (int i = 0; i < num_dashes; i += 1) {
							draw_rectangle(app, rect, roundness, comment_color);
							rect.x0 += dash_size + dash_gap;
							rect.x1 += dash_size + dash_gap;
						}
					}
				}
			}
		}
	}
}

//~ Jumping between divider comments

internal i64
seek_any_divider_comment(Application_Links *app, Buffer_ID buffer, Scan_Direction direction,
						 i64 pos, String_Const_u8 signifier) {
	i64 result = pos;
	
	Scratch_Block scratch(app);
	Token_Array tokens = get_token_array_from_buffer(app, buffer);
	if (tokens.tokens != 0) {
		Token_Iterator_Array it = token_iterator_pos(0, &tokens, pos);
		
		// NOTE(ema): I think the two cases are just the same code, except for the use of
		// 'inc_non_whitespace' vs 'dec_non_whitespace'.
		switch (direction) {
			case Scan_Forward: {
				for (Token *token = token_it_read(&it);
					 token != 0 && token_it_inc_non_whitespace(&it);
					 token = token_it_read(&it)) {
					
					if (token->kind == TokenBaseKind_Comment) {
						String_Const_u8 str = push_buffer_range(app, scratch, buffer, Ii64(token));
						if (str.size >= signifier.size && string_match(string_substring(str, Ii64(0, signifier.size)), signifier)) {
							result = token->pos;
							break;
						}
					}
				}
			} break;
			
			case Scan_Backward: {
				for (Token *token = token_it_read(&it);
					 token != 0 && token_it_dec_non_whitespace(&it);
					 token = token_it_read(&it)) {
					
					if (token->kind == TokenBaseKind_Comment) {
						String_Const_u8 str = push_buffer_range(app, scratch, buffer, Ii64(token));
						if (str.size >= signifier.size && string_match(string_substring(str, Ii64(0, signifier.size)), signifier)) {
							result = token->pos;
							break;
						}
					}
				}
			} break;
		}
	}
	
	return result;
}

// Makes the caret jump to the next/previous "strong" divider comment.
// **Returns** the byte offset of the start of the comment.
internal i64
seek_strong_divider_comment(Application_Links *app, Buffer_ID buffer, Side side,
							Scan_Direction direction, i64 pos) {
	(void)side;
	return seek_any_divider_comment(app, buffer, direction, pos, strong_divider_comment_signifier);
}

// Makes the caret jump to the next/previous "weak" divider comment.
// **Returns** the byte offset of the start of the comment.
internal i64
seek_weak_divider_comment(Application_Links *app, Buffer_ID buffer, Side side,
						  Scan_Direction direction, i64 pos) {
	(void)side;
	return seek_any_divider_comment(app, buffer, direction, pos, weak_divider_comment_signifier);
}

NAMESPACE_END()

//- Commands

CUSTOM_COMMAND_SIG(seek_next_strong_divider_comment)
CUSTOM_DOC("Seek the next strong divider comment in the buffer.") {
	Scratch_Block scratch(app);
	current_view_scan_move(app, Scan_Forward,  push_boundary_list(scratch, nne::seek_strong_divider_comment));
}

CUSTOM_COMMAND_SIG(seek_prev_strong_divider_comment)
CUSTOM_DOC("Seek the previous strong divider comment in the buffer.") {
	Scratch_Block scratch(app);
	current_view_scan_move(app, Scan_Backward, push_boundary_list(scratch, nne::seek_strong_divider_comment));
}

CUSTOM_COMMAND_SIG(seek_next_weak_divider_comment)
CUSTOM_DOC("Seek the next weak divider comment in the buffer.") {
	Scratch_Block scratch(app);
	current_view_scan_move(app, Scan_Forward,  push_boundary_list(scratch, nne::seek_weak_divider_comment));
}

CUSTOM_COMMAND_SIG(seek_prev_weak_divider_comment)
CUSTOM_DOC("Seek the previous weak divider comment in the buffer.") {
	Scratch_Block scratch(app);
	current_view_scan_move(app, Scan_Backward, push_boundary_list(scratch, nne::seek_weak_divider_comment));
}

#endif // FCODER_CUSTOM_DIVIDER_COMMENTS_CPP
