#ifndef FCODER_CUSTOM_LANG_ODIN_CPP
#define FCODER_CUSTOM_LANG_ODIN_CPP

NAMESPACE_BEGIN(nne)

//~ Index

// Parses a declaration list, such as the formal parameters of a function or the members of a struct.
internal void odin__parse_decl_list(Index__Parse_Context *context, Index__Note *parent) {
    Index__Note *last_parent = index__push_parent_note(context, parent);
    
    for (; !context->done; ) {
        Token *name = 0;
        if (index__require_token_kind(context, TokenBaseKind_Identifier, &name, Index__Token_Skip_Flag_Skip_Whitespace) &&
            index__require_token(context, str8_lit(":"), Index__Token_Skip_Flag_Skip_Whitespace)) {
			// <name> :
            index__make_note(context, Ii64(name), Index__Note_Kind_Decl, 0);
            
            for (; !context->done; ) {
                Token *token = token_it_read(&context->it);
				
                if (token->sub_kind == TokenOdinKind_Comma ||
                    token->sub_kind == TokenOdinKind_Semicolon) {
					// We saw a comma or a semicolon: skip it and resume the outer loop, parsing the next decl.
                    index__parse_context_inc(context, Index__Token_Skip_Flag_Skip_Whitespace);
                    break;
                } else if (token->kind == TokenBaseKind_ScopeClose ||
                           token->sub_kind == TokenOdinKind_ParenCl) {
					// We saw a }. The declaration list is finished.
                    goto end;
                }
                
                index__parse_context_inc(context, Index__Token_Skip_Flag_Skip_Whitespace);
            }
        } else { break; }
    }
    
    end:;
    index__pop_parent_note(context, last_parent);
}

internal void odin__parse_decl_list_in_braces(Index__Parse_Context *context, Index__Note *parent) {
    if (index__require_token(context, str8_lit("{"), Index__Token_Skip_Flag_Skip_Whitespace)) {
        odin__parse_decl_list(context, parent);
        index__require_token(context, str8_lit("}"), Index__Token_Skip_Flag_Skip_Whitespace);
    }
}

internal void odin__parse_decl_list_in_parens(Index__Parse_Context *context, Index__Note *parent) {
    if (index__require_token(context, str8_lit("("), Index__Token_Skip_Flag_Skip_Whitespace)) {
        odin__parse_decl_list(context, parent);
        index__require_token(context, str8_lit(")"), Index__Token_Skip_Flag_Skip_Whitespace);
    }
}

#define S(s) str8_lit(s)

// Indexes an entire file of a language and adds stuff to the code index.
function FILE_INDEXER(odin__index_file) {
    int scope_nest = 0;
    
    for (; !context->done; ) {
        Token *name = 0;
        Index__Token_Skip_Flags flags = Index__Token_Skip_Flag_Skip_Whitespace;
        
        {
            // Handle nests.
            Token *token = token_it_read(&context->it);
            if (token) {
                if (token->kind == TokenBaseKind_ScopeOpen) {
                    scope_nest += 1;
                } else if (token->kind == TokenBaseKind_ScopeClose) {
                    scope_nest -= 1;
                }
                
                if (scope_nest < 0) {
                    scope_nest = 0;
				}
            }
        }
        
        if (index__require_token_kind(context, TokenBaseKind_Identifier, &name, flags)) {
            // <name>
			
            if (index__require_token(context, S(":"), flags)) {
				// <name> :
				
				// Skip the possible explicit type annotation.
				if (index__peek_token_kind(context, TokenBaseKind_Identifier, 0)) {
					// <name> : <ident>
					
					index__parse_context_inc(context, flags);
				}
				
				Token *rhs_name = 0;
                if (index__require_token(context, S(":"), flags)) {
					// <name> ::
					
					// Procedures.
					// @Note(ema): This only looks for the prototype of the procedure, it does not
					// walk through the whole body.
					if ((index__require_token(context, S("proc"), flags)) ||
						(index__require_token(context, S("#force_inline"), flags) &&
						 index__require_token(context, S("proc"), flags))) {
						// <name> :: proc
						// <name> :: #force_inline proc
						
						Index__Note *parent = index__make_note(context, Ii64(name), Index__Note_Kind_Function, 0);
						odin__parse_decl_list_in_parens(context, parent);
					}
					
					// Structs.
					else if (index__require_token(context, S("struct"), flags)) {
						// <name> :: struct
						Index__Note *parent = index__make_note(context, Ii64(name), Index__Note_Kind_Type, Index__Note_Flag_Product_Type);
						odin__parse_decl_list_in_braces(context, parent);
					}
					
					// Unions.
					else if (index__require_token(context, S("union"), flags)) {
						// <name> :: union
						Index__Note *parent = index__make_note(context, Ii64(name), Index__Note_Kind_Type, Index__Note_Flag_Sum_Type);
						odin__parse_decl_list_in_braces(context, parent);
					}
					
					// Enums.
					else if (index__require_token(context, S("enum"), flags)) {
						// <name> :: enum
						index__make_note(context, Ii64(name), Index__Note_Kind_Type, 0);
					}
					
					// Distinct types.
					else if (index__require_token(context, S("distinct"), flags) &&
							 index__require_token_kind(context, TokenBaseKind_Identifier, &rhs_name, flags)) {
						// <name> :: distinct <ident>
						
						Index__Note_Flags note_flags = 0;
						Index__Note *rhs_note = index__lookup_note(index__string_from_token(context, rhs_name));
						if (rhs_note) {
							note_flags = rhs_note->flags;
						}
						
						index__make_note(context, Ii64(name), Index__Note_Kind_Type, note_flags);
					}
					
					// Type directives.
					else if (index__require_token(context, S("#type"), flags)) {
						// <name> :: #type
						
						// @Incomplete: what kind of type?
						index__make_note(context, Ii64(name), Index__Note_Kind_Type, 0);
					}
					
					// Literal constants.
					else if (index__require_token_kind(context, TokenBaseKind_LiteralInteger, 0, flags) || index__require_token_kind(context, TokenBaseKind_LiteralFloat, 0, flags) || index__require_token_kind(context, TokenBaseKind_LiteralString,  0, flags)) {
						// <name> :: <literal>
						index__make_note(context, Ii64(name), Index__Note_Kind_Constant, 0);
					}
					
					// Aliases.
					else if (index__require_token_kind(context, TokenBaseKind_Identifier, &rhs_name, flags)) {
						// <name> :: <ident>
						
						Index__Note *rhs_note = index__lookup_note(index__string_from_token(context, rhs_name));
						if (rhs_note) {
							if (rhs_note->kind == Index__Note_Kind_Type) {
								index__make_note(context, Ii64(name), Index__Note_Kind_Type, rhs_note->flags);
							} else {
								index__make_note(context, Ii64(name), Index__Note_Kind_Constant, 0);
							}
						} else {
							index__make_note(context, Ii64(name), Index__Note_Kind_Constant, 0);
						}
					}
				} else if (index__require_token(context, str8_lit("="), flags)) {
					// <name> :=
					
					index__make_note(context, Ii64(name), Index__Note_Kind_Decl, 0);
				}
			}
		}
		
#undef S
		
		//~ Comment Tags.
		// @Note(ema): When we come across a comment, we call index::parse_comment that figures out if the comment contains annotations, notes or todos.
		else if (index__require_token_kind(context, TokenBaseKind_Comment, &name, Index__Token_Skip_Flag_Skip_Whitespace)) {
			index__parse_comment(context, name);
		}
		
		// Nothing meaningful, just advance by one.
		else {
			index__parse_context_inc(context, flags);
		}
	}
}

//~ Positional context:

internal Token *_F4_Odin_FindDecl(Application_Links *app, Buffer_ID buffer, i64 pos, Token *decl_name) {
    Scratch_Block scratch(app);
	Token *result = 0;
    
    int scope_nest = 0;
    String_Const_u8 decl_name_str = push_buffer_range(app, scratch, buffer, Ii64(decl_name));
    Token_Array tokens = get_token_array_from_buffer(app, buffer);
    Token_Iterator_Array it = token_iterator_pos(0, &tokens, pos);
    for (;;) {
        Token *token = token_it_read(&it);
        if (token) {
            if (scope_nest == 0 &&
				token->sub_kind == TokenOdinKind_Colon &&
				token_it_dec_non_whitespace(&it)) {
                Token *name_candidate = token_it_read(&it);
                if (name_candidate && name_candidate->kind == TokenBaseKind_Identifier) {
                    String_Const_u8 name_candidate_string = push_buffer_range(app, scratch, buffer, Ii64(name_candidate));
                    if (string_match(name_candidate_string, decl_name_str)) {
                        result = name_candidate;
                        break;
                    }
                }
            } else if (token->sub_kind == TokenOdinKind_BraceCl) {
                scope_nest += 1;
            } else if (token->sub_kind == TokenOdinKind_BraceOp) {
                scope_nest -= 1;
            }
        } else { break; }
		
        if (!token_it_dec_non_whitespace(&it)) {
            break;
        }
    }
	
    return result;
}

//
// Figures out some language-specific contextual information given some
// position in a buffer. For example, what type I am accessing, what function I am
// calling, which parameter am I accessing, etc.
function POSITIONAL_CONTEXT_GETTER(odin__get_positional_context) {
    int count = 0;
	Positional_Context_Data *first = 0;
	Positional_Context_Data *last  = 0;
    
    Token_Array tokens = get_token_array_from_buffer(app, buffer);
    
    // Search for left parentheses (function call or macro invocation).
    // The corresponding line will be used to display the tooltip.
    {
        Token_Iterator_Array it = token_iterator_pos(0, &tokens, pos);
        
        int paren_nest = 0;
        int arg_idx = 0;
        for (int i = 0; count < 4; i += 1) {
            Token *token = token_it_read(&it);
            if (token) {
                if (paren_nest == 0 && token->sub_kind == TokenOdinKind_ParenOp && token_it_dec_non_whitespace(&it)) {
                    Token *name = token_it_read(&it);
                    if (name && name->kind == TokenBaseKind_Identifier) {
                        F4_Language_PosContext_PushData_Call(arena, &first, &last, push_buffer_range(app, arena, buffer, Ii64(name)), arg_idx);
						count  += 1;
                        arg_idx = 0;
                    }
                } else if (token->sub_kind == TokenOdinKind_ParenOp) {
                    paren_nest -= 1;
                } else if (token->sub_kind == TokenOdinKind_ParenCl && i > 0) {
                    paren_nest += 1;
                } else if (token->sub_kind == TokenOdinKind_Comma && i > 0 && paren_nest == 0) {
                    arg_idx += 1;
                }
            } else {
                break;
            }
            
            if (!token_it_dec_non_whitespace(&it)) {
                break;
            }
        }
    }
    
    // Search for *.* pattern (accessing a type)
    // The corresponding line will be used to display the tooltip.
    {
        Token_Iterator_Array it = token_iterator_pos(0, &tokens, pos);
        
        Token *last_query_candidate = 0;
        for (int i = 0; i < 3; i += 1) {
            Token *token = token_it_read(&it);
            if (token) {
                if (i == 0 && token->kind == TokenBaseKind_Identifier) {
                    last_query_candidate = token;
                } else if ((i == 0 || i == 1) && token->sub_kind == TokenOdinKind_Dot && token_it_dec_non_whitespace(&it)) {
                    Token *decl_name = token_it_read(&it);
                    if (decl_name && decl_name->kind == TokenBaseKind_Identifier) {
                        Token *decl_start = _F4_Odin_FindDecl(app, buffer, decl_name->pos, decl_name);
                        if (decl_start) {
                            Token_Iterator_Array it2 = token_iterator_pos(0, &tokens, decl_start->pos);
                            b32    found_colon = false;
                            Token *base_type = 0;
                            for (;;) {
                                Token *token2 = token_it_read(&it2);
                                if (token2) {
                                    if (token2->sub_kind == TokenOdinKind_Colon) {
                                        found_colon = true;
                                    } else if (found_colon && token2->kind == TokenBaseKind_Identifier) {
                                        base_type = token2;
                                    } else if (found_colon && token2->kind == TokenBaseKind_StatementClose) {
                                        break;
                                    }
                                } else { break; }
                                
                                if (!token_it_inc_non_whitespace(&it2)) {
                                    break;
                                }
                            }
                            
                            if (base_type != 0) {
                                F4_Language_PosContext_PushData_Dot(arena, &first, &last,
                                                                    push_buffer_range(app, arena, buffer, Ii64(base_type)), last_query_candidate);
                            }
                        }
                    }
                }
            } else { break; }
            
            if (!token_it_dec_non_whitespace(&it)) {
                break;
            }
        }
    }
    
    return first;
}


//
// Does language-specific coloring for a buffer, for special-case syntax
// highlighting and stuff. Most syntax highlighting is handled through token-base-kinds
// and index lookups, but sometimes it's useful to be able to override colors by
// language-specific token sub-kinds and flags, so that's what this hook is for.
internal LANGUAGE_HIGHLIGHTER(odin__highlight) {
}

NAMESPACE_END()

#endif // FCODER_CUSTOM_LANG_ODIN_CPP
