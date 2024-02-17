#ifndef FCODER_CUSTOM_COLORS_CPP
#define FCODER_CUSTOM_COLORS_CPP

namespace nne {
	
	typedef u32 Syntax_Flags;
	enum {
		Syntax_Flag_Functions    = (1<<0),
		Syntax_Flag_Macros       = (1<<1),
		Syntax_Flag_Types        = (1<<2),
		Syntax_Flag_Operators    = (1<<3),
		Syntax_Flag_Constants    = (1<<4),
		Syntax_Flag_Literals     = (1<<5),
		Syntax_Flag_Preprocessor = (1<<6),
		Syntax_Flag_Keywords     = (1<<7),
		Syntax_Flag_HighlightAll = (1<<15),
	};
#define Syntax_Flag_All 0xffffffff
	
	global f32 syntax_flag_transitions[32] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,};
	
	//~ Syntax highlighting options.
	
	struct Syntax_Options {
		String8 name;
		Syntax_Flags flags;
	};
	
	global Syntax_Options syntax_options_table[] = {
		{ S8Lit("All"),            Syntax_Flag_All },
		{ S8Lit("None"),           0 },
		{ S8Lit("Functions Only"), Syntax_Flag_Functions },
		{ S8Lit("Macros Only"),    Syntax_Flag_Macros },
		{ S8Lit("Function-Likes Only"), Syntax_Flag_Functions | Syntax_Flag_Macros },
		{ S8Lit("Types Only"),     Syntax_Flag_Types },
		{ S8Lit("Externals Only"), Syntax_Flag_Functions | Syntax_Flag_Macros | Syntax_Flag_Types | Syntax_Flag_Constants },
	};
	global i32 active_syntax_option_idx = 0;
	
	function String8 read_syntax_options_string(void) {
		return syntax_options_table[active_syntax_option_idx].name;
	}
	
	//~ Tick.
	
	function void tick_colors(Application_Links *app, Frame_Info frame_info) {
		Syntax_Options options = syntax_options_table[active_syntax_option_idx];
		for (int flag_idx = 0; flag_idx < sizeof(Syntax_Flags)*8; flag_idx += 1) {
			f32 delta = (cast(f32)!!(options.flags & (1<<flag_idx)) - syntax_flag_transitions[flag_idx]) * frame_info.animation_dt * 8.f;
			syntax_flag_transitions[flag_idx] += delta;
			if (fabsf(delta) > 0.001f) {
				animate_in_n_milliseconds(app, 0);
			}
		}
	}
	
	//~ ARGB.
	
	function b32 argb_is_valid(ARGB_Color color) {
		return color != 0xFF990099; // @Cleanup(ema): What? Explain...
	}
	
	function ARGB_Color argb_from_id(Color_Table table, Managed_ID id, int subindex) {
		ARGB_Color result = 0;
		FColor color = fcolor_id(id);
		if (color.a_byte == 0){
			if (color.id != 0){
				result = finalize_color(table, color.id, subindex);
			}
		} else {
			result = color.argb;
		}
		return result;
	}
	
	function ARGB_Color argb_from_id(Color_Table table, Managed_ID id) {
		return argb_from_id(table, id, 0);
	}
	
	//~ Color context.
	
	function Color_Context make_token_color_context(Token token, Buffer_ID buffer) {
		Color_Context ctx = {};
		ctx.token    = token;
		ctx.buffer   = buffer;
		return ctx;
	}
	
	function Color_Context make_cursor_color_context(Color_Flags flags, Keybinding_Mode mode) {
		Color_Context ctx = {};
		ctx.flags    = flags;
		ctx.mode     = mode;
		return ctx;
	}
	
	function ARGB_Color get_color(Application_Links *app, Color_Context context) {
		Color_Table table = active_color_table;
		ARGB_Color  default_color = argb_from_id(table, defcolor_text_default);
		ARGB_Color  color = default_color;
		f32 t = 1;
		
#define Fill_From_Flag(flag) do{ t = syntax_flag_transitions[get_single_bit_offset(flag)]; }while(0)
		
		//- Token Color
		if (context.token.size != 0) {
			Scratch_Block scratch(app);
			
			switch (context.token.kind) {
				case TokenBaseKind_Identifier: {
					String_Const_u8 string = push_buffer_range(app, scratch, context.buffer, Ii64(context.token.pos, context.token.pos + context.token.size));
					Index__Note *note = index__lookup_note(string);
					if (note) {
						color = 0xffff0000; // @Cleanup: Magic number
						switch (note->kind) {
							case Index__Note_Kind_Type: {
								Fill_From_Flag(Syntax_Flag_Types);
								color = argb_from_id(table,
													 note->flags & Index__Note_Flag_Sum_Type
													 ? fleury_color_index_sum_type
													 : fleury_color_index_product_type);
							} break;
							
							case Index__Note_Kind_Macro: {
								Fill_From_Flag(Syntax_Flag_Macros);
								color = argb_from_id(table, fleury_color_index_macro);
							} break;
							
							case Index__Note_Kind_Function: {
								Fill_From_Flag(Syntax_Flag_Functions);
								color = argb_from_id(table, fleury_color_index_function);
							} break;
							
							case Index__Note_Kind_Constant: {
								Fill_From_Flag(Syntax_Flag_Constants);
								color = argb_from_id(table, fleury_color_index_constant);
							} break;
							
							case Index__Note_Kind_Decl: {
								Fill_From_Flag(Syntax_Flag_Constants);
								color = argb_from_id(table, fleury_color_index_decl);
							} break;
							
							default: { color = 0xffff00ff; } break; // @Cleanup: Magic number
						}
						
						if (!argb_is_valid(color)) {
							color = default_color;
						}
					}
					
				} break;
				
				case TokenBaseKind_Preprocessor:     { Fill_From_Flag(Syntax_Flag_Preprocessor); color = argb_from_id(table, defcolor_preproc); } break;
				case TokenBaseKind_Keyword:          { Fill_From_Flag(Syntax_Flag_Keywords); color = argb_from_id(table, defcolor_keyword); } break;
				case TokenBaseKind_Comment:          { color = argb_from_id(table, defcolor_comment); } break;
				case TokenBaseKind_LiteralString:    { Fill_From_Flag(Syntax_Flag_Literals); color = argb_from_id(table, defcolor_str_constant); } break;
				case TokenBaseKind_LiteralInteger:   { Fill_From_Flag(Syntax_Flag_Literals); color = argb_from_id(table, defcolor_int_constant); } break;
				case TokenBaseKind_LiteralFloat:     { Fill_From_Flag(Syntax_Flag_Literals); color = argb_from_id(table, defcolor_float_constant); } break;
				case TokenBaseKind_Operator:         { Fill_From_Flag(Syntax_Flag_Operators); color = argb_from_id(table, fleury_color_operators); if (!argb_is_valid(color)) { color = default_color; } } break;
				
				case TokenBaseKind_ScopeOpen:
				case TokenBaseKind_ScopeClose:
				case TokenBaseKind_ParentheticalOpen:
				case TokenBaseKind_ParentheticalClose:
				case TokenBaseKind_StatementClose: {
					color = argb_from_id(table, fleury_color_syntax_crap);
					if (!argb_is_valid(color)) {
						color = default_color;
					}
					break;
				}
				
				default: {
					switch(context.token.sub_kind) {
						case TokenCppKind_LiteralTrue:
						case TokenCppKind_LiteralFalse: {
							color = argb_from_id(table, defcolor_bool_constant);
							Fill_From_Flag(Syntax_Flag_Literals); 
							break;
						}
						
						case TokenCppKind_LiteralCharacter:
						case TokenCppKind_LiteralCharacterWide:
						case TokenCppKind_LiteralCharacterUTF8:
						case TokenCppKind_LiteralCharacterUTF16:
						case TokenCppKind_LiteralCharacterUTF32: {
							color = argb_from_id(table, defcolor_char_constant);
							Fill_From_Flag(Syntax_Flag_Literals); 
							break;
						}
						
						case TokenCppKind_PPIncludeFile: {
							color = argb_from_id(table, defcolor_include);
							Fill_From_Flag(Syntax_Flag_Literals); 
							break;
						}
					}
				} break;
			}
		}
		
		//- Cursor Color
		else {
			if (context.flags & Color_Flag_Macro) {
				color = argb_from_id(table, fleury_color_cursor_macro);
			} else if (context.flags & Color_Flag_PowerMode) {
				color = argb_from_id(table, fleury_color_cursor_power_mode);
			} else {
				color = argb_from_id(table, defcolor_cursor, context.mode);
			}
		}
		
#undef Fill_From_Flag
		
		return color_blend(default_color, t, color);
	}
	
	function void do_syntax_highlight(Application_Links *app, Text_Layout_ID text_layout_id, Token_Array *array) {
		Color_Table table = active_color_table;
		Buffer_ID buffer = text_layout_get_buffer(app, text_layout_id);
		Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
		i64 first_index = token_index_from_pos(array, visible_range.first);
		Token_Iterator_Array it = token_iterator_index(0, array, first_index);
		ARGB_Color comment_tag_color = argb_from_id(table, fleury_color_index_comment_tag, 0);
		
		for (;;) {
			Token *token = token_it_read(&it);
			if (!token || token->pos >= visible_range.one_past_last) {
				break;
			}
			
			ARGB_Color argb = get_color(app, make_token_color_context(*token, buffer));
			paint_text_color(app, text_layout_id, Ii64_size(token->pos, token->size), argb);
			
			// Substrings from comments, for annotations
			if (argb_is_valid(comment_tag_color)) {
				if (token->kind == TokenBaseKind_Comment) {
					Scratch_Block scratch(app);
					String_Const_u8 string = push_buffer_range(app, scratch, buffer, Ii64(token->pos, token->pos + token->size));
					for (u64 i = 0; i < string.size; i += 1) {
						if (string.str[i] == '@') {
							u64 j = i+1;
							for (; j < string.size; j += 1) {
								if (character_is_whitespace(string.str[j])) {
									break;
								}
							}
							paint_text_color(app, text_layout_id, Ii64(token->pos + cast(i64)i, token->pos + cast(i64)j), comment_tag_color);
						}
					}
				}
			}
			
			if (!token_it_inc_all(&it)) {
				break;
			}
		}
		
		F4_Language *lang = language_from_buffer(app, buffer);
		if (lang && lang->highlighter) {
			lang->highlighter(app, text_layout_id, array, table);
		}
	}
	
}

CUSTOM_COMMAND_SIG(f4_switch_syntax_option)
CUSTOM_DOC("Switches the syntax highlighting mode.") {
	nne::active_syntax_option_idx = (nne::active_syntax_option_idx + 1) % ArrayCount(nne::syntax_options_table);
}

#endif // FCODER_CUSTOM_COLORS_CPP
