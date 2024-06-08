#ifndef FCODER_CUSTOM_LANGUAGE_JS_CPP
#define FCODER_CUSTOM_LANGUAGE_JS_CPP

NAMESPACE_BEGIN(nne)

internal b32 js__skip_parse_body(Index__Parse_Context *context) {
    b32 body_found = false;
    int nest = 0;
    
    for (; !context->done; ) {
        Token *name = 0;
        
        if (index__parse_pattern(context, "%k", TokenBaseKind_Comment, &name)) {
            index__parse_comment(context, name);
        } else if (index__parse_pattern(context, "%t", "{")) {
            nest += 1;
            body_found = true;
        } else if (index__parse_pattern(context, "%t", "}")) {
            nest -= 1;
            if (nest == 0) {
                break;
            }
        } else if (!body_found) {
            break;
        } else {
            index__parse_context_inc(context, Index__Token_Skip_Flag_Skip_Whitespace);
        }
    }
    return body_found;
}

function b32 js__parse_decl(Index__Parse_Context *context, Token **name) {
    Token *base_type = 0;
    return (index__parse_pattern(context, "%k%o%k%o%t",
								 TokenBaseKind_Identifier, &base_type,
								 TokenBaseKind_Identifier, name,
								 ";") ||
            index__parse_pattern(context, "%k%o%k%o%t",
								 TokenBaseKind_Keyword, &base_type,
								 TokenBaseKind_Identifier, name,
								 ";") ||
            index__parse_pattern(context, "%k%o%k%t",
								 TokenBaseKind_Identifier, &base_type,
								 TokenBaseKind_Identifier, name,
								 "=") ||
            index__parse_pattern(context, "%k%o%k%t",
								 TokenBaseKind_Keyword, &base_type,
								 TokenBaseKind_Identifier, name,
								 "="));
}

function void js__parse_struct_or_union_body(Index__Parse_Context *context, Index__Note_Flags note_flags) {
    Token *name = 0;
    b32 valid = false;
    b32 need_end_name = false;
    
    if (index__parse_pattern(context, "%k", TokenBaseKind_Identifier, &name)) {
        valid = true;
    } else {
        need_end_name = true;
    }
    
    if (js__skip_parse_body(context)) {
    } else {
        note_flags |= Index__Note_Flag_Prototype;
    }
    
    if (need_end_name) {
        if (index__parse_pattern(context, "%k", TokenBaseKind_Identifier, &name)) {
            valid = true;
        }
    }
    
    if (valid) {
        index__make_note(context, Ii64(name), Index__Note_Kind_Type, note_flags);
    }
}

function b32 js__parse_function_body(Index__Parse_Context *context) {
    b32 valid = false;
    
    for(;!context->done;) {
        Token *token = token_it_read(&context->it);
        if (token == 0) {
			break;
		}
        
		if (token->kind == TokenBaseKind_ScopeOpen) {
            valid = true;
            break;
        }
        index__parse_context_inc(context, 0);
    }
    
    if (valid) {
		js__skip_parse_body(context);
    }
    
    return valid;
}

internal FILE_INDEXER(js__index_file) {
    int scope_nest = 0;
	
    for (b32 handled = false; !context->done; ) {
        handled = false;
        
        Token *name = 0;
        
        if(0){}
        
        //~ NOTE(rjf): Scope Nest Changes
        else if (index__parse_pattern(context, "%t", "{")) {
            handled = true;
            scope_nest += 1;
        } else if (index__parse_pattern(context, "%t", "}")) {
            handled = true;
            scope_nest -= 1;
            if (scope_nest < 0) {
                scope_nest = 0;
            }
        }
        
        //~ NOTE(ema): Classes
        else if (index__parse_pattern(context, "%t", "class")) {
            handled = true;
            js__parse_struct_or_union_body(context, Index__Note_Flag_Product_Type);
        }
        
        //~ NOTE(rjf): Functions
        else if (index__parse_pattern(context, "%t%k%t", "function", TokenBaseKind_Identifier, &name, "(")) {
            handled = true;
            if (js__parse_function_body(context)) {
                index__make_note(context, Ii64(name), Index__Note_Kind_Function, 0);
            }
        }
        
        //~ NOTE(rjf): Declarations
        else if (scope_nest == 0 && js__parse_decl(context, &name)) {
            handled = true;
            index__make_note(context, Ii64(name), Index__Note_Kind_Decl, 0);
        }
        
        //~ NOTE(rjf): Comment Tags
        else if (index__parse_pattern(context, "%k", TokenBaseKind_Comment, &name)) {
            handled = true;
            index__parse_comment(context, name);
        }
        
        
        if (!handled) {
            index__parse_context_inc(context, 0);
        }
    }
}

internal POSITIONAL_CONTEXT_GETTER(js__get_positional_context) {
    int count = 0;
	Positional_Context_Data *first = 0;
	Positional_Context_Data *last = 0;
    
    Token_Array tokens = get_token_array_from_buffer(app, buffer);
    Token_Iterator_Array it = token_iterator_pos(0, &tokens, pos);
    
    // Search for left parentheses (function call or macro invocation).
    {
        int paren_nest = 0;
        int arg_idx = 0;
		
        for (int i = 0; count < 4; i += 1) {
            Token *token = token_it_read(&it);
            if (token) {
                if (paren_nest == 0 &&
					token->sub_kind == TokenCppKind_ParenOp &&
					token_it_dec_non_whitespace(&it)) {
                    Token *name = token_it_read(&it);
                    if (name && name->kind == TokenBaseKind_Identifier) {
                        F4_Language_PosContext_PushData_Call(arena, &first, &last, push_buffer_range(app, arena, buffer, Ii64(name)), arg_idx);
                        count += 1;
                        arg_idx = 0;
                    }
                } else if (token->sub_kind == TokenCppKind_ParenOp) {
                    paren_nest -= 1;
                } else if (token->sub_kind == TokenCppKind_ParenCl && i > 0) {
                    paren_nest += 1;
                } else if (token->sub_kind == TokenCppKind_Comma && i > 0 && paren_nest == 0) {
                    arg_idx += 1;
                }
            } else { break; }
			
            if (!token_it_dec_non_whitespace(&it)) {
                break;
            }
        }
    }
    
    // Search for *.* pattern, or *->* pattern (accessing a type)
    {
#if 1
        Token *last_query_candidate = 0;
        for (;;) {
            Token *token = token_it_read(&it);
            if (token) {
                if (token->kind == TokenBaseKind_Identifier) {
                    last_query_candidate = token;
                } else if ((token->sub_kind == TokenCppKind_Dot ||
							token->sub_kind == TokenCppKind_Arrow) &&
						   token_it_dec_non_whitespace(&it)) {
                    Token *decl_name = token_it_read(&it);
                    if (decl_name && decl_name->kind == TokenBaseKind_Identifier) {
                        
                    }
                }
            } else { break; }
			
            if (!token_it_dec_non_whitespace(&it)) {
                break;
            }
        }
#endif
    }
    
    return first;
}

internal LANGUAGE_HIGHLIGHTER(js__highlight) {
}

NAMESPACE_END()

#endif // FCODER_CUSTOM_LANGUAGE_JS_CPP