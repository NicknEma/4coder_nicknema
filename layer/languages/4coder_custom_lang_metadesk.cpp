#ifndef FCODER_CUSTOM_LANG_METADESK_CPP
#define FCODER_CUSTOM_LANG_METADESK_CPP

NAMESPACE_BEGIN(nne)

struct Metadesk_Lexer_State {
    String_Const_u8 string;
    u8 *at;
    u8 *one_past_last;
};

enum Metadesk_Token_SubKind {
    Metadesk_Token_SubKind_Null,
    Metadesk_Token_SubKind_Tag,
};

internal FILE_INDEXER(metadesk__index_file) {
    for(; !context->done; ) {
        Token *name = 0;
        if (index__require_token_kind(context, TokenBaseKind_Identifier, &name, Index__Token_Skip_Flag_Skip_Whitespace)) {
            if (index__require_token(context, S8Lit(":"), Index__Token_Skip_Flag_Skip_Whitespace)) {
                index__make_note(context, Ii64(name), Index__Note_Kind_Constant, 0);
            }
        } else if(index__require_token_kind(context, TokenBaseKind_Comment, &name, Index__Token_Skip_Flag_Skip_Whitespace)) {
            index__parse_comment(context, name);
        } else {
            index__parse_context_inc(context, Index__Token_Skip_Flag_Skip_Whitespace);
        }
    }
}

internal LEXER_INITTER(metadesk__lexer_initter) {
    Metadesk_Lexer_State *state = cast(Metadesk_Lexer_State *)state_ptr;
    state->string = contents;
    state->at = contents.str;
    state->one_past_last = contents.str + contents.size;
}

internal b32 metadesk__char_is_symbol(u8 c) {
    return (c == '~' || c == '!' || c == '@' || c == '#' || c == '$' ||
            c == '%' || c == '^' || c == '&' || c == '*' || c == '(' ||
            c == ')' || c == '-' || c == '=' || c == '+' || c == '[' ||
            c == ']' || c == '{' || c == '}' || c == ':' || c == ';' ||
            c == ',' || c == '<' || c == '.' || c == '>' || c == '/' ||
            c == '?' || c == '|' || c == '\\');
}

internal LEXER(metadesk__lexer) {
    b32 result = false;
    Metadesk_Lexer_State state_ = *cast(Metadesk_Lexer_State *)state_ptr;
    Metadesk_Lexer_State *state = &state_;
    u64 emit_counter = 0;
    i64 strmax = cast(i64)state->string.size;
    
	for (i64 i = cast(i64)(state->at - state->string.str); i < strmax && state->at + i < state->one_past_last; ) {
        i64 start_i = i;
        u8 chr = state->string.str[i];
        
        if (i+1 < strmax && state->string.str[i] == '/' && state->string.str[i+1] == '/') {
			// Line Comments.
			
            Token token = { i, 1, TokenBaseKind_Comment, 0 };
            token.size += 1;
            for (i64 j = i+2; j < strmax && state->string.str[j] != '\n'; j += 1) {
				token.size += 1;
			}
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (i+1 < strmax && state->string.str[i] == '/' && state->string.str[i+1] == '*') {
            // Block Comments.
			
			Token token = { i, 1, TokenBaseKind_Comment, 0 };
            token.size += 1;
            for (i64 j = i+2; j+1 < strmax && !(state->string.str[j] == '*' && state->string.str[j+1] == '/'); j += 1) {
				token.size += 1;
			}
            token.size += 2;
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (character_is_alpha(chr)) {
            // Identifier.
			
			Token token = { i, 1, TokenBaseKind_Identifier, 0 };
            for (i64 j = i+1; j < cast(i64)state->string.size && (character_is_alpha_numeric(state->string.str[j]) || state->string.str[j] == '_'); j += 1) {
				token.size += 1;
			}
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (character_is_whitespace(chr)) {
            // Whitespace.
			
			Token token = { i, 1, TokenBaseKind_Whitespace, 0 };
            for (i64 j = i+1; j < cast(i64)state->string.size &&  character_is_whitespace(state->string.str[j]); j += 1) {
				token.size += 1;
			}
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (chr >= '0' && chr <= '9') {
            // Numeric Literal.
			
			Token token = { i, 1, TokenBaseKind_LiteralFloat, 0 };
            for (i64 j = i+1; j < cast(i64)state->string.size && (character_is_alpha_numeric(state->string.str[j]) ||
																  state->string.str[j] == '_' ||
																  state->string.str[j] == '.'); j += 1) {
				token.size += 1;
			}
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (chr == '"') {
			// Single-Line String Literal.
			
			Token token = { i, 1, TokenBaseKind_LiteralString, 0 };
            for (i64 j = i+1; j < cast(i64)state->string.size && state->string.str[j] != '"'; j += 1) {
				token.size += 1;
			}
            token.size += 1;
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (chr == '`') {
            // Single-Line String Literal Marker (Bundle-Of-Tokens).
			
			Token token = { i, 1, TokenBaseKind_LiteralString, 0 };
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (chr == '\'') {
            // Single-Line Char Literal.
			
			Token token = { i, 1, TokenBaseKind_LiteralString, 0 };
            for (i64 j = i+1; j < cast(i64)state->string.size && state->string.str[j] != '\'';
				 j += 1) {
				token.size += 1;
			}
            token.size += 1;
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (i+2 < strmax &&
				   state->string.str[i]   == '"' &&
				   state->string.str[i+1] == '"' &&
				   state->string.str[i+2] == '"') {
            // Multi-line String Literal.
			
			Token token = { i, 1, TokenBaseKind_LiteralString, 0 };
            for (i64 j = i+1; j+2 < cast(i64)state->string.size && !(state->string.str[j]   == '"' &&
																	 state->string.str[j+1] == '"' &&
																	 state->string.str[j+2] == '"'); j += 1) {
				token.size += 1;
			}
            token.size += 3;
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (i+2 < strmax &&
				   state->string.str[i]   == '`' &&
				   state->string.str[i+1] == '`' &&
				   state->string.str[i+2] == '`') {
            // Multi-Line String Literal Marker (Bundle-Of-Tokens).
			
			Token token = { i, 3, TokenBaseKind_LiteralString, 0 };
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (i+2 < strmax &&
				   state->string.str[i]   == '\'' &&
				   state->string.str[i+1] == '\'' &&
				   state->string.str[i+2] == '\'') {
            // Multi-line Char Literal.
			
			Token token = { i, 1, TokenBaseKind_LiteralString, 0 };
            for (i64 j = i+1; j+2 < cast(i64)state->string.size && !(state->string.str[j]   == '\'' &&
																	 state->string.str[j+1] == '\'' &&
																	 state->string.str[j+2] == '\''); j += 1) {
				token.size += 1;
			}
            token.size += 3;
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (chr == '@') {
            // Tags.
			
			Token token = { i, 1, TokenBaseKind_Identifier, 0 };
            token.sub_kind = Metadesk_Token_SubKind_Tag;
            for (i64 j = i+1; j < cast(i64)state->string.size && (character_is_alpha_numeric(state->string.str[j]) || state->string.str[j] == '_'); j += 1) {
				token.size += 1;
			}
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (chr == '{') {
            // Scope-Open.
			
			Token token = { i, 1, TokenBaseKind_ScopeOpen, 0 };
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (chr == '}') {
            // Scope-Close.
			
			Token token = { i, 1, TokenBaseKind_ScopeClose, 0 };
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (chr == '(' || chr == '[') {
            // Paren-Open.
			
			Token token = { i, 1, TokenBaseKind_ParentheticalOpen, 0 };
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (chr == ')' || chr == ']') {
            // Paren-Close.
			
			Token token = { i, 1, TokenBaseKind_ParentheticalClose, 0 };
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (chr == ',' || chr == ';' || (chr == '-' && i+1 < strmax && state->string.str[i+1] == '>')) {
            // Statement closes.
			
			Token token = { i, 1, TokenBaseKind_StatementClose, 0 };
            token_list_push(arena, list, &token);
            i += token.size;
        } else if (metadesk__char_is_symbol(chr)) {
            // Operators.
			
			Token token = { i, 1, TokenBaseKind_Operator, 0 };
            token_list_push(arena, list, &token);
            i += token.size;
        } else {
            // Catch-All.
			
			Token token = {i, 1, TokenBaseKind_LexError, 0 };
            token_list_push(arena, list, &token);
            i += token.size;
        }
        
        if (state->at >= state->one_past_last) {
            goto eof;
        } else if (start_i == i) {
            i += 1;
            state->at = state->string.str + i;
        } else {
            state->at = state->string.str + i;
            emit_counter += 1;
            if (emit_counter >= max) {
                goto end;
            }
        }
    }
    
    // Add EOF Token.
    eof:;
    {
        result = true;
        Token token = { (i64)state->string.size, 1, TokenBaseKind_EOF, 0 };
        token_list_push(arena, list, &token);
    }
    
    end:;
    *cast(Metadesk_Lexer_State *)state_ptr = *state;
    return result;
}

internal POSITIONAL_CONTEXT_GETTER(metadesk__get_positional_context) {
    return 0;
}

internal LANGUAGE_HIGHLIGHTER(metadesk__highlight) {
    Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
    i64 first_index = token_index_from_pos(array, visible_range.first);
    Token_Iterator_Array it = token_iterator_index(0, array, first_index);
    
    for (;;) {
        Token *token = token_it_read(&it);
        if (!token || token->pos >= visible_range.one_past_last) {
            break;
        }
		
        if (token->sub_kind == Metadesk_Token_SubKind_Tag) {
            paint_text_color(app, text_layout_id, Ii64(token), argb_from_id(color_table, fleury_color_index_comment_tag, 0));
        }
		
        if (!token_it_inc_all(&it)) {
            break;
        }
    }
}

NAMESPACE_END()

#endif // FCODER_CUSTOM_LANG_METADESK_CPP
