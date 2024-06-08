#ifndef FCODER_CUSTOM_AUTO_INDENT_CPP
#define FCODER_CUSTOM_AUTO_INDENT_CPP

namespace nne {
	
	// This code is taken directly from 4coder_auto_indent.cpp and modified to handle optional semicolons.
	// @Todo: In addition to the "treat_as_code" field in the config file, we add a second "requires semicolons"
	// field that we read here.
	function b32 indent__unfinished_statement(Token *token, Nest *current_nest, b32 require_statement_closer) {
		b32 result = false;
		
		if (require_statement_closer) {
			if (current_nest && current_nest->kind == TokenBaseKind_ScopeOpen) {
				result = true;
				switch (token->kind) {
					case TokenBaseKind_ScopeOpen:
					case TokenBaseKind_ScopeClose:
					case TokenBaseKind_StatementClose: {
						result = false;
					} break;
				}
				
				if (HasFlag(token->flags, TokenBaseFlag_PreprocessorBody)) {
					result = false;
				}
			}
		}
		
		return result;
	}
	
	// @Note: These Indent_Flag flags are never used in this procedure in the original code. I wonder what their purpose is?
	function i64 *get_indentation_array(Application_Links *app, Arena *arena, Buffer_ID buffer, Range_i64 lines, nne::Indent_Flag flags, i32 tab_width, i32 indent_width) {
		ProfileScope(app, "Get indentation array");
		i64 count = lines.max - lines.min + 1;
		i64 *indentations = push_array(arena, i64, count);
		i64 *shifted_indentations = indentations - lines.first;
		block_fill_u64(indentations, sizeof(*indentations)*count, cast(u64)(-1));
		
		Token_Array token_array = get_token_array_from_buffer(app, buffer);
		Token_Array *tokens = &token_array;
		
		i64 anchor_line = clamp_bot(1, lines.first - 1);
		Token *anchor_token = find_anchor_token(app, buffer, tokens, anchor_line);
		if (anchor_token != 0 && anchor_token >= tokens->tokens && anchor_token < tokens->tokens + tokens->count) {
			i64 line = get_line_number_from_pos(app, buffer, anchor_token->pos);
			line = clamp_top(line, lines.first);
			
			Token_Iterator_Array token_it = token_iterator(0, tokens, anchor_token);
			
			Scratch_Block scratch(app, arena);
			Nest *nest = 0;
			Nest_Alloc nest_alloc = {};
			
			i64 line_last_indented = line - 1;
			i64 last_indent = 0;
			i64 actual_indent = 0;
			b32 in_unfinished_statement = false;
			
			Indent_Line_Cache line_cache = {};
			
			for (;;) {
				Token *token = token_it_read(&token_it);
				
				if (line_cache.where_token_starts == 0 || token->pos >= line_cache.one_past_last_pos) {
					ProfileScope(app, "Get line number");
					line_cache.where_token_starts = get_line_number_from_pos(app, buffer, token->pos);
					line_cache.one_past_last_pos  = get_line_end_pos(app, buffer, line_cache.where_token_starts);
				}
				
				i64 current_indent = 0;
				if (nest) {
					current_indent = nest->indent;
				}
				
				i64 this_indent = current_indent;
				i64 following_indent = current_indent;
				
				b32 shift_by_actual_indent = false;
				b32 ignore_unfinished_statement = false;
				if (HasFlag(token->flags, TokenBaseFlag_PreprocessorBody)) {
					this_indent = 0;
				} else {
					switch (token->kind){
						case TokenBaseKind_ScopeOpen: {
							Nest *new_nest = indent__new_nest(arena, &nest_alloc);
							sll_stack_push(nest, new_nest);
							nest->kind = TokenBaseKind_ScopeOpen;
							nest->indent = current_indent + indent_width;
							following_indent = nest->indent;
							ignore_unfinished_statement = true;
						} break;
						
						case TokenBaseKind_ScopeClose: {
							for (; nest && nest->kind != TokenBaseKind_ScopeOpen; ) {
								Nest *n = nest;
								sll_stack_pop(nest);
								indent__free_nest(&nest_alloc, n);
							}
							
							if (nest && nest->kind == TokenBaseKind_ScopeOpen) {
								Nest *n = nest;
								sll_stack_pop(nest);
								indent__free_nest(&nest_alloc, n);
							}
							
							this_indent = 0;
							if (nest) {
								this_indent = nest->indent;
							}
							following_indent = this_indent;
							ignore_unfinished_statement = true;
						} break;
						
						case TokenBaseKind_ParentheticalOpen: {
							Nest *new_nest = indent__new_nest(arena, &nest_alloc);
							sll_stack_push(nest, new_nest);
							nest->kind = TokenBaseKind_ParentheticalOpen;
							line_indent_cache_update(app, buffer, tab_width, &line_cache);
							nest->indent = (token->pos - line_cache.indent_info.first_char_pos) + 1;
							following_indent = nest->indent;
							shift_by_actual_indent = true;
							ignore_unfinished_statement = true;
						} break;
						
						case TokenBaseKind_ParentheticalClose: {
							if (nest != 0 && nest->kind == TokenBaseKind_ParentheticalOpen) {
								Nest *n = nest;
								sll_stack_pop(nest);
								indent__free_nest(&nest_alloc, n);
							}
							
							following_indent = 0;
							if (nest != 0) {
								following_indent = nest->indent;
							}
							//ignore_unfinished_statement = true;
						} break;
					}
					
					if (token->sub_kind == TokenCppKind_BlockComment || token->sub_kind == TokenCppKind_LiteralStringRaw) {
						ignore_unfinished_statement = true;
					}
					
					if (in_unfinished_statement && !ignore_unfinished_statement) {
						this_indent += indent_width;
					}
				}
				
				// @Cleanup: Can we get rid of this macro?
				//-
#define EMIT(N) \
Stmnt(if (lines.first <= line_it){shifted_indentations[line_it]=N;} \
if (line_it == lines.end){goto finished;} \
actual_indent = N; )
				//-
				
				i64 line_it = line_last_indented;
				if (lines.first <= line_cache.where_token_starts) {
					for (; line_it < line_cache.where_token_starts; ) {
						line_it += 1;
						if (line_it == line_cache.where_token_starts) {
							EMIT(this_indent);
						} else {
							EMIT(last_indent);
						}
					}
				} else {
					actual_indent = this_indent;
					line_it = line_cache.where_token_starts;
				}
				
				i64 line_where_token_ends = get_line_number_from_pos(app, buffer, token->pos + token->size);
				if (lines.first <= line_where_token_ends){
					line_indent_cache_update(app, buffer, tab_width, &line_cache);
					i64 line_where_token_starts_shift = this_indent - line_cache.indent_info.indent_pos;
					for (; line_it < line_where_token_ends; ) {
						line_it += 1;
						i64 line_it_start_pos = get_line_start_pos(app, buffer, line_it);
						Indent_Info line_it_indent_info = get_indent_info_line_number_and_start(app, buffer, line_it, line_it_start_pos, tab_width);
						i64 new_indent = line_it_indent_info.indent_pos + line_where_token_starts_shift;
						new_indent = clamp_bot(0, new_indent);
						EMIT(new_indent);
					}
				} else {
					line_it = line_where_token_ends;
				}
#undef EMIT
				
				if (shift_by_actual_indent) {
					nest->indent += actual_indent;
					following_indent += actual_indent;
				}
				
				if (token->kind != TokenBaseKind_Comment) {
					in_unfinished_statement = nne::indent__unfinished_statement(token, nest, HasFlag(flags, Indent_RequireStatementCloser));
					if (in_unfinished_statement) {
						following_indent += indent_width;
					}
				}
				
				last_indent = following_indent;
				line_last_indented = line_it;
				
				if (!token_it_inc_non_whitespace(&token_it)) {
					break;
				}
			}
		}
		
		finished:;
		return indentations;
	}
	
	function b32 auto_indent_buffer(Application_Links *app, Buffer_ID buffer, Range_i64 pos, nne::Indent_Flag flags, i32 tab_width, i32 indent_width){
		ProfileScope(app, "Auto indent buffer");
		
		Token_Array  token_array = get_token_array_from_buffer(app, buffer);
		Token_Array *tokens = &token_array;
		
		b32 result = false;
		if (tokens->tokens) {
			result = true;
			
			Scratch_Block scratch(app);
			
#define SAFETY_COUNTER_MAX 20
			
			Range_i64 line_numbers = {};
			if (HasFlag(flags, Indent_FullTokens)) {
				i32 safety_counter = 0;
				for (;;) {
					Range_i64 expanded = enclose_tokens(app, buffer, pos);
					expanded = enclose_whole_lines(app, buffer, expanded);
					if (expanded == pos) {
						break;
					}
					pos = expanded;
					safety_counter += 1;
					if (safety_counter == SAFETY_COUNTER_MAX) {
						pos = buffer_range(app, buffer);
						break;
					}
				}
			}
			
#undef SAFETY_COUNTER_MAX
			
			line_numbers = get_line_range_from_pos_range(app, buffer, pos);
			
			i64 *indentations = nne::get_indentation_array(app, scratch, buffer, line_numbers, flags, tab_width, indent_width);
			set_line_indents(app, scratch, buffer, line_numbers, indentations, flags, tab_width);
		}
		
		return result;
	}
	
	function b32 auto_indent_buffer(Application_Links *app, Buffer_ID buffer, Range_i64 pos, nne::Indent_Flag flags) {
		i32 indent_width = cast(i32)def_get_config_u64(app, vars_save_string_lit("indent_width"));
		i32 tab_width    = cast(i32)def_get_config_u64(app, vars_save_string_lit("default_tab_width"));
		tab_width = clamp_bot(1, tab_width);
		
		AddFlag(flags, Indent_FullTokens);
		b32 indent_with_tabs = def_get_config_b32(vars_save_string_lit("indent_with_tabs"));
		if (indent_with_tabs) {
			AddFlag(flags, Indent_UseTab);
		}
		
#if 1
		AddFlag(flags, Indent_RequireStatementCloser); // @Temporary.
#endif
		
		return nne::auto_indent_buffer(app, buffer, pos, flags, indent_width, tab_width);
	}
	
	function b32 auto_indent_buffer(Application_Links *app, Buffer_ID buffer, Range_i64 pos) {
		return nne::auto_indent_buffer(app, buffer, pos, 0);
	}
	
	function void auto_indent_whole_file(Application_Links *app) {
		View_ID   view   = get_active_view(app, Access_ReadWriteVisible);
		Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
		i64  buffer_size = buffer_get_size(app, buffer);
		
		nne::auto_indent_buffer(app, buffer, Ii64(0, buffer_size));
	}
	
	function void auto_indent_line_at_cursor(Application_Links *app) {
		View_ID   view   = get_active_view(app, Access_ReadWriteVisible);
		Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
		i64       pos    = view_get_cursor_pos(app, view);
		
		nne::auto_indent_buffer(app, buffer, Ii64(pos));
		move_past_lead_whitespace(app, view, buffer);
	}
	
	function void auto_indent_range(Application_Links *app) {
		View_ID   view   = get_active_view(app, Access_ReadWriteVisible);
		Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
		Range_i64 range  = get_view_range(app, view);
		
		nne::auto_indent_buffer(app, buffer, range);
		move_past_lead_whitespace(app, view, buffer);
	}
	
	function void write_text_and_auto_indent(Application_Links *app) {
		ProfileScope(app, "Write text and auto indent");
		
		User_Input      in     = get_current_input(app);
		String_Const_u8 insert = to_writable(&in);
		
		if (insert.str && insert.size > 0) {
			b32 do_auto_indent = false;
			{
				for (u64 i = 0; !do_auto_indent && i < insert.size; i += 1) {
					switch (insert.str[i]) {
						case ';':
						case ':':
						case '{':
						case '}':
						case '(':
						case ')':
						case '[':
						case ']':
						case '#':
						case '\n':
						case '\t': { do_auto_indent = true; } break;
					}
				}
			}
			
			if (do_auto_indent) {
				View_ID   view   = get_active_view(app, Access_ReadWriteVisible);
				Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
				
				Range_i64 pos = {};
				if (view_has_highlighted_range(app, view)) {
					pos = get_view_range(app, view);
				} else {
					pos.min = pos.max = view_get_cursor_pos(app, view);
				}
				
				write_text_input(app);
				
				i64 end_pos = view_get_cursor_pos(app, view);
				pos.min = Min(pos.min, end_pos);
				pos.max = Max(pos.max, end_pos);
				
				nne::auto_indent_buffer(app, buffer, pos);
				move_past_lead_whitespace(app, view, buffer);
			} else {
				write_text_input(app);
			}
		}
	}
	
}

//~ Commands
// Since commands can't be put in a namespace (because the metaprogram gets confused) we prefix
// the commands' name instead.

#if 1
CUSTOM_COMMAND_SIG(custom__auto_indent_whole_file)
CUSTOM_DOC("Audo-indents the entire current buffer.") {
    nne::auto_indent_whole_file(app);
}

CUSTOM_COMMAND_SIG(custom__auto_indent_line_at_cursor)
CUSTOM_DOC("Auto-indents the line on which the cursor sits.") {
    nne::auto_indent_line_at_cursor(app);
}

CUSTOM_COMMAND_SIG(custom__auto_indent_range)
CUSTOM_DOC("Auto-indents the range between the cursor and the mark.") {
    nne::auto_indent_range(app);
}
#endif

CUSTOM_COMMAND_SIG(custom__write_text_and_auto_indent)
CUSTOM_DOC("Inserts text and auto-indents the line on which the cursor sits if any of the text contains 'layout punctuation' such as ;:{}()[]# and new lines.") {
    nne::write_text_and_auto_indent(app);
}

#endif // FCODER_CUSTOM_AUTO_INDENT_CPP
