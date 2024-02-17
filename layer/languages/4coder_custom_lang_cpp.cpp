#ifndef FCODER_CUSTOM_LANGUAGE_CPP_CPP
#define FCODER_CUSTOM_LANGUAGE_CPP_CPP

NAMESPACE_BEGIN(nne)

// Parses the rest of a macro definition after the # character.
internal void F4_CPP_ParseMacroDefinition(Index__Parse_Context *context) {
    Token *name = 0;
    if (index__parse_pattern(context, "%k", TokenBaseKind_Identifier, &name)) {
        Index__Note *last_parent = index__push_parent_note(context, 0);
        index__make_note(context, Ii64(name), Index__Note_Kind_Macro, 0);
        index__pop_parent_note(context, last_parent);
        index__skip_soft_tokens(context, 1);
    }
}

internal b32 F4_CPP_SkipParseBody(Index__Parse_Context *context) {
    b32 body_found = false;
    int nest = 0;
    
    for (; !context->done; ) {
        Token *name = 0;
        
        if (index__parse_pattern(context, "%k", TokenBaseKind_Comment, &name)) {
            index__parse_comment(context, name);
        } else if (index__parse_pattern(context, "%b", TokenCppKind_PPDefine, &name)) {
            F4_CPP_ParseMacroDefinition(context);
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

procedure b32 F4_CPP_ParseDecl(Index__Parse_Context *context, Token **name) {
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

procedure void F4_CPP_ParseStructOrUnionBody(Index__Parse_Context *context, Index__Note_Flags note_flags) {
    Token *name = 0;
    b32 valid = false;
    b32 need_end_name = false;
    
    if (index__parse_pattern(context, "%k", TokenBaseKind_Identifier, &name)) {
        valid = true;
    } else {
        need_end_name = true;
    }
    
    if (F4_CPP_SkipParseBody(context)) {
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

function b32 F4_CPP_ParseFunctionBody(Index__Parse_Context *context, b32 *prototype_ptr) {
    b32 valid = false;
    b32 prototype = false;
    
    for(;!context->done;) {
        Token *token = token_it_read(&context->it);
        if (token == 0) {
			break;
		}
        
		if (token->sub_kind == TokenCppKind_Semicolon) {
            valid = true;
            prototype = true;
            break;
        } else if (token->sub_kind == TokenCppKind_ParenCl) {
        } else if (token->kind == TokenBaseKind_ScopeOpen) {
            valid = true;
            break;
        }
        index__parse_context_inc(context, 0);
    }
    
    if (valid) {
        if (!prototype) {
            F4_CPP_SkipParseBody(context);
        }
    }
    
    *prototype_ptr = prototype;
    
    return valid;
}

procedure void F4_CPP_ParseEnumBody(Index__Parse_Context *context) {
    if (index__parse_pattern(context, "%t", "{")) {
        for (; !context->done; ) {
            Token *constant = 0;
            if (index__parse_pattern(context, "%k%t", TokenBaseKind_Identifier, &constant, ",")) {
                index__make_note(context, Ii64(constant), Index__Note_Kind_Constant, 0);
            } else if (index__parse_pattern(context, "%k%t", TokenBaseKind_Identifier, &constant, "=")) {
                index__make_note(context, Ii64(constant), Index__Note_Kind_Constant, 0);
                
                for (; !context->done; ) {
                    Token *token = token_it_read(&context->it);
                    if (token->kind == TokenBaseKind_StatementClose) {
                        index__parse_context_inc(context, 0);
                        break;
                    } else if (token->kind == TokenBaseKind_ScopeClose ||
							   token->kind == TokenBaseKind_ScopeOpen) {
                        break;
                    }
                    index__parse_context_inc(context, 0);
                }
            } else if (index__parse_pattern(context, "%k", TokenBaseKind_Identifier, &constant)) {
                index__make_note(context, Ii64(constant), Index__Note_Kind_Constant, 0);
            } else if (index__parse_pattern(context, "%t", "}")) {
                break;
            } else {
                index__parse_context_inc(context, 0);
            }
        }
    }
}

internal FILE_INDEXER(F4_CPP_IndexFile) {
    int scope_nest = 0;
	
    for (b32 handled = false; !context->done; ) {
        handled = false;
        
        Token *name = 0;
        Token *base_type = 0;
        Index__Note *containing_struct = 0;
        Index__Note *note = 0;
        
        if(0){}
        
        //~ Extern "C" scope changes (ignore). NOTE(rjf): ((dude C++ syntax is so fucked up))
        // CORRECTION: NOTE(rjf): Text files in general are so fucked up, fuck all of this
        // parsing bullshit.
        else if (index__parse_pattern(context, "%t%t%t", "extern", "C", "{")) {
            handled = true;
        }
        
		// Namespace scope changes. @Note(ema): I agree with the above statement.
		// %k -> token kind,    requires Token_Base_Kind and Token ** for output token
		else if (index__parse_pattern(context, "%t%k%t", "namespace", TokenBaseKind_Identifier, 0, "{")) {
			handled = true;
			
			b32 indent_namespaces = def_get_config_b32(vars_save_string_lit("cpp_indent_namespaces"));
			if (indent_namespaces) {
				scope_nest += 1;
			}
		}
		
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
        
        //~ NOTE(rjf): Structs
        else if (index__parse_pattern(context, "%t", "struct")) {
            handled = true;
            F4_CPP_ParseStructOrUnionBody(context, Index__Note_Flag_Product_Type);
        } else if (index__parse_pattern(context, "%t%t", "typedef", "struct")) {
            handled = true;
            F4_CPP_ParseStructOrUnionBody(context, 0);
            if (index__parse_pattern(context, "%k", TokenBaseKind_Identifier, &name)) {
                index__make_note(context, Ii64(name), Index__Note_Kind_Type, Index__Note_Flag_Product_Type);
            }
        }
        
        //~ NOTE(rjf): Unions
        else if (index__parse_pattern(context, "%t", "union")) {
            handled = true;
            F4_CPP_ParseStructOrUnionBody(context, Index__Note_Flag_Sum_Type);
        } else if (index__parse_pattern(context, "%t%t", "typedef", "union")) {
            handled = true;
            F4_CPP_ParseStructOrUnionBody(context, Index__Note_Flag_Sum_Type);
            if (index__parse_pattern(context, "%k", TokenBaseKind_Identifier, &name)) {
                index__make_note(context, Ii64(name), Index__Note_Kind_Type, Index__Note_Flag_Sum_Type);
            }
        }
        
        //~ NOTE(rjf): Typedef'd Enums
        else if (index__parse_pattern(context, "%t%t%k", "typedef", "enum", TokenBaseKind_Identifier, &name) ||
				 index__parse_pattern(context, "%t%t", "typedef", "enum")) {
            handled = true;
            b32 prototype = false;
            b32 possible_name_at_end = (name == 0);
            
			if (index__parse_pattern(context, "%t", ";")) {
                prototype = true;
            }
			
            if (!prototype) {
                F4_CPP_ParseEnumBody(context);
            }
			
            if (possible_name_at_end) {
                if (index__parse_pattern(context, "%k", TokenBaseKind_Identifier, &name)) {
				}
            }
			
            if (name != 0) {
                index__make_note(context, Ii64(name), Index__Note_Kind_Type, prototype ? Index__Note_Flag_Prototype : 0);
            }
        }
        
        //~ NOTE(rjf): Enums
        else if(index__parse_pattern(context, "%t%k", "enum", TokenBaseKind_Identifier, &name) ||
                index__parse_pattern(context, "%t", "enum")) {
            handled = true;
            b32 prototype = false;
			
            if (index__parse_pattern(context, "%t", ";")) {
                prototype = true;
            }
			
            if (!prototype) {
                F4_CPP_ParseEnumBody(context);
            }
			
            if (name != 0) {
                index__make_note(context, Ii64(name), Index__Note_Kind_Type, prototype ? Index__Note_Flag_Prototype : 0);
            }
        }
        
        //~ NOTE(rjf): Pure Typedefs
        else if (index__parse_pattern(context, "%t", "typedef")) {
            handled = true;
            int nest = 0;
            b32 sum_type = false;
			
            for (; !context->done; ) {
                if (index__parse_pattern(context, "%t", "(")) {
                    nest += 1;
                } else if (index__parse_pattern(context, "%t", "(")) {
                    nest -= 1;
                } else if (nest == 0 && index__parse_pattern(context, "%k", TokenBaseKind_Identifier, &name)) {
                    String8 namestr = index__string_from_token(context, name);
                    Index__Note *namenote = index__lookup_note(namestr, 0);
                    if (namenote != 0 && namenote->kind == Index__Note_Kind_Type &&
						namenote->flags & Index__Note_Flag_Sum_Type) {
                        sum_type = true;
                    }
                } else if (index__parse_pattern(context, "%t", ";")) {
                    break;
                } else  {
                    index__parse_context_inc(context, 0);
                }
            }
			
            if (name != 0) {
                Index__Note_Flags note_flags = 0;
                if (sum_type) {
                    note_flags |= Index__Note_Flag_Sum_Type;
                }
                index__make_note(context, Ii64(name), Index__Note_Kind_Type, note_flags);
            }
        }
        
        //~ NOTE(rjf): Functions
        else if (scope_nest == 0 &&
				 (index__parse_pattern(context, "%k%o%k%t", TokenBaseKind_Identifier, &base_type, TokenBaseKind_Identifier, &name, "(") ||
				  index__parse_pattern(context, "%k%o%k%t", TokenBaseKind_Keyword,    &base_type, TokenBaseKind_Identifier, &name, "("))) {
            handled = true;
            b32 prototype = false;
            if (F4_CPP_ParseFunctionBody(context, &prototype)) {
                index__make_note(context, Ii64(name), Index__Note_Kind_Function, prototype ? Index__Note_Flag_Prototype : 0);
            }
        }
        
        //~ NOTE(rjf): Member Functions
        else if (scope_nest == 0 &&
				 (index__parse_pattern(context, "%k%o%n%t%k%t",
									   TokenBaseKind_Identifier, &base_type,
									   Index__Note_Kind_Type, &containing_struct, "::", TokenBaseKind_Identifier, &name, "(") ||
				  index__parse_pattern(context, "%k%o%n%t%k%t",
									   TokenBaseKind_Keyword, &base_type,
									   Index__Note_Kind_Type, &containing_struct, "::", TokenBaseKind_Identifier, &name, "("))) {
            handled = true;
            b32 prototype = false;
            if (F4_CPP_ParseFunctionBody(context, &prototype)) {
                index__make_note(context, Ii64(name), Index__Note_Kind_Function, prototype ? Index__Note_Flag_Product_Type : 0);
            }
        }
        
        //~ NOTE(rjf): Declarations
        else if (scope_nest == 0 && F4_CPP_ParseDecl(context, &name)) {
            handled = true;
            index__make_note(context, Ii64(name), Index__Note_Kind_Decl, 0);
        }
        
        //~ NOTE(rjf): Macro Functions
        else if (0 && index__parse_pattern(context, "%n%t%k", Index__Note_Kind_Macro, &note, "(", TokenBaseKind_Identifier, &name)) {
            b32 valid = false;
            b32 prototype = false;
            
            for (; !context->done; ) {
                Token *token = token_it_read(&context->it);
                if (token == 0) {
					break;
				}
				
                if (token->sub_kind == TokenCppKind_Semicolon) {
                    prototype = true;
                    valid = true;
                    break;
                } else if (token->sub_kind == TokenCppKind_ParenCl) {
                } else if (token->kind == TokenBaseKind_ScopeOpen) {
                    valid = true;
                    break;
                }
				
                index__parse_context_inc(context, 0);
            }
            
            if (valid) {
                handled = true;
                index__make_note(context, Ii64(name), Index__Note_Kind_Function, prototype ? Index__Note_Flag_Product_Type : 0);
                F4_CPP_SkipParseBody(context);
            }
        }
        
        //~ NOTE(rjf): Comment Tags
        else if (index__parse_pattern(context, "%k", TokenBaseKind_Comment, &name)) {
            handled = true;
            index__parse_comment(context, name);
        }
        
        //~ NOTE(rjf): Macros
        else if (index__parse_pattern(context, "%b", TokenCppKind_PPDefine, &name)) {
            handled = true;
            F4_CPP_ParseMacroDefinition(context);
        }
        
        
        if (!handled) {
            index__parse_context_inc(context, 0);
        }
    }
}

internal POSITIONAL_CONTEXT_GETTER(cpp__get_positional_context) {
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

internal LANGUAGE_HIGHLIGHTER(cpp__highlight) {
}

NAMESPACE_END()

#endif // FCODER_CUSTOM_LANGUAGE_CPP_CPP