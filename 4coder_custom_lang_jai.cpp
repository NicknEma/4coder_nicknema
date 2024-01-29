#ifndef FCODER_CUSTOM_LANG_JAI_CPP
#define FCODER_CUSTOM_LANG_JAI_CPP

NAMESPACE_BEGIN(nne)

internal void F4_Jai_ParseDeclSet(Index__Parse_Context *context, Index__Note *parent) {
    Index__Note *last_parent = index__push_parent_note(context, parent);
    for (;!context->done;) {
        Token *name = 0;
        if (index__require_token_kind(context, TokenBaseKind_Identifier, &name, Index__Token_Skip_Flag_Skip_Whitespace) &&
			index__require_token(context, S8Lit(":"), Index__Token_Skip_Flag_Skip_Whitespace)) {
            index__make_note(context, Ii64(name), Index__Note_Kind_Decl, 0);
            
            for (;!context->done;) {
                Token *token = token_it_read(&context->it);
                if (token->sub_kind == TokenJaiKind_Comma || token->sub_kind == TokenJaiKind_Semicolon) {
                    index__parse_context_inc(context, Index__Token_Skip_Flag_Skip_Whitespace);
                    break;
                } else if (token->kind == TokenBaseKind_ScopeClose || token->sub_kind == TokenJaiKind_ParenCl) {
                    goto end;
                }
				
                index__parse_context_inc(context, Index__Token_Skip_Flag_Skip_Whitespace);
            }
            
        } else { break; }
    }
    
    end:;
    index__pop_parent_note(context, last_parent);
}

internal void F4_Jai_ParseDeclSet_Braces(Index__Parse_Context *context, Index__Note *parent) {
    if (index__require_token(context, S8Lit("{"), Index__Token_Skip_Flag_Skip_Whitespace)) {
        F4_Jai_ParseDeclSet(context, parent);
        index__require_token(context, S8Lit("}"), Index__Token_Skip_Flag_Skip_Whitespace);
    }
}

internal void F4_Jai_ParseDeclSet_Parens(Index__Parse_Context *context, Index__Note *parent) {
    if (index__require_token(context, S8Lit("("), Index__Token_Skip_Flag_Skip_Whitespace)) {
        F4_Jai_ParseDeclSet(context, parent);
        index__require_token(context, S8Lit(")"), Index__Token_Skip_Flag_Skip_Whitespace);
    }
}

internal FILE_INDEXER(F4_Jai_IndexFile) {
    int scope_nest = 0;
    
	for (; !context->done; ) {
        Token *name = 0;
        Index__Token_Skip_Flags flags = Index__Token_Skip_Flag_Skip_Whitespace;
        
        // NOTE(rjf): Handle nests.
        {
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
            
            // NOTE(rjf): Definitions
            if (index__require_token(context, S8Lit("::"), flags)){
                
				// NOTE(rjf): Procedures
                if (index__peek_token(context, S8Lit("(")) ||
					(index__require_token(context, S8Lit("inline"), flags) &&
					 index__peek_token(context, S8Lit("(")))) {
                    Index__Note *parent = index__make_note(context, Ii64(name), Index__Note_Kind_Function, 0);
                    F4_Jai_ParseDeclSet_Parens(context, parent);
                }
				
                // NOTE(rjf): Structs
                else if (index__require_token(context, S8Lit("struct"), flags)) {
                    Index__Note *parent = index__make_note(context, Ii64(name), Index__Note_Kind_Type, Index__Note_Flag_Product_Type);
                    F4_Jai_ParseDeclSet_Braces(context, parent);
                }
				
                // NOTE(rjf): Unions
                else if (index__require_token(context, S8Lit("union"), flags)) {
                    Index__Note *parent = index__make_note(context, Ii64(name), Index__Note_Kind_Type, Index__Note_Flag_Sum_Type);
                    F4_Jai_ParseDeclSet_Braces(context, parent);
                }
				
                // NOTE(rjf): Enums
                else if (index__require_token(context, S8Lit("enum"), flags)) {
                    index__make_note(context, Ii64(name), Index__Note_Kind_Type, 0);
                }
				
                // NOTE(rjf): Constants
                else if (index__require_token_kind(context, TokenBaseKind_Identifier, 0, flags) ||
						 index__require_token_kind(context, TokenBaseKind_LiteralInteger, 0, flags) ||
						 index__require_token_kind(context, TokenBaseKind_LiteralFloat, 0, flags) ||
						 index__require_token_kind(context, TokenBaseKind_LiteralString, 0, flags)) {
                    index__make_note(context, Ii64(name), Index__Note_Kind_Constant, 0);
                }
            }
        }
        
        //~ NOTE(rjf): Comment Tags
        else if (index__require_token_kind(context, TokenBaseKind_Comment, &name, Index__Token_Skip_Flag_Skip_Whitespace)) {
            index__parse_comment(context, name);
        }
        
        else {
            index__parse_context_inc(context, flags);
        }
    }
}

internal Token *
_F4_Jai_FindDecl(Application_Links *app, Buffer_ID buffer, i64 pos, Token *decl_name)
{
    Token *result = 0;
    Scratch_Block scratch(app);
    
    int scope_nest = 0;
    String_Const_u8 decl_name_str = push_buffer_range(app, scratch, buffer, Ii64(decl_name));
    Token_Array tokens = get_token_array_from_buffer(app, buffer);
    Token_Iterator_Array it = token_iterator_pos(0, &tokens, pos);
    for(;;)
    {
        Token *token = token_it_read(&it);
        if(token)
        {
            if(scope_nest == 0 &&
               token->sub_kind == TokenJaiKind_Colon &&
               token_it_dec_non_whitespace(&it))
            {
                Token *name_candidate = token_it_read(&it);
                if(name_candidate && name_candidate->kind == TokenBaseKind_Identifier)
                {
                    String_Const_u8 name_candidate_string = push_buffer_range(app, scratch, buffer, Ii64(name_candidate));
                    if(string_match(name_candidate_string, decl_name_str))
                    {
                        result = name_candidate;
                        break;
                    }
                }
            }
            else if(token->sub_kind == TokenJaiKind_BraceCl)
            {
                scope_nest += 1;
            }
            else if(token->sub_kind == TokenJaiKind_BraceOp)
            {
                scope_nest -= 1;
            }
        }
        else { break; }
        if(!token_it_dec_non_whitespace(&it))
        {
            break;
        }
    }
    return result;
}

internal POSITIONAL_CONTEXT_GETTER(F4_Jai_PosContext)
{
    int count = 0;
	Positional_Context_Data *first = 0;
	Positional_Context_Data *last = 0;
    
    Token_Array tokens = get_token_array_from_buffer(app, buffer);
    
    // NOTE(rjf): Search for left parentheses (function call or macro invocation).
    {
        Token_Iterator_Array it = token_iterator_pos(0, &tokens, pos);
        
        int paren_nest = 0;
        int arg_idx = 0;
        for(int i = 0; count < 4; i += 1)
        {
            Token *token = token_it_read(&it);
            if(token)
            {
                if(paren_nest == 0 &&
                   token->sub_kind == TokenJaiKind_ParenOp &&
                   token_it_dec_non_whitespace(&it))
                {
                    Token *name = token_it_read(&it);
                    if(name && name->kind == TokenBaseKind_Identifier)
                    {
                        F4_Language_PosContext_PushData_Call(arena, &first, &last, push_buffer_range(app, arena, buffer, Ii64(name)), arg_idx);
						count += 1;
                        arg_idx = 0;
                    }
                }
                else if(token->sub_kind == TokenJaiKind_ParenOp)
                {
                    paren_nest -= 1;
                }
                else if(token->sub_kind == TokenJaiKind_ParenCl && i > 0)
                {
                    paren_nest += 1;
                }
                else if(token->sub_kind == TokenJaiKind_Comma && i > 0 && paren_nest == 0)
                {
                    arg_idx += 1;
                }
            }
            else { break; }
            if(!token_it_dec_non_whitespace(&it))
            {
                break;
            }
        }
    }
    
    // NOTE(rjf): Search for *.* pattern (accessing a type)
    {
        Token_Iterator_Array it = token_iterator_pos(0, &tokens, pos);
        
        Token *last_query_candidate = 0;
        for(int i = 0; i < 3; i += 1)
        {
            Token *token = token_it_read(&it);
            if(token)
            {
                if(i == 0 && token->kind == TokenBaseKind_Identifier)
                {
                    last_query_candidate = token;
                }
                else if((i == 0 || i == 1) &&
					    token->sub_kind == TokenJaiKind_Dot &&
                        token_it_dec_non_whitespace(&it))
                {
                    Token *decl_name = token_it_read(&it);
                    if(decl_name && decl_name->kind == TokenBaseKind_Identifier)
                    {
                        Token *decl_start = _F4_Jai_FindDecl(app, buffer, decl_name->pos, decl_name);
                        if(decl_start)
                        {
                            Token_Iterator_Array it2 = token_iterator_pos(0, &tokens, decl_start->pos);
                            b32 found_colon = 0;
                            Token *base_type = 0;
                            for(;;)
                            {
                                Token *token2 = token_it_read(&it2);
                                if(token2)
                                {
                                    if(token2->sub_kind == TokenJaiKind_Colon)
                                    {
                                        found_colon = 1;
                                    }
                                    else if(found_colon && token2->kind == TokenBaseKind_Identifier)
                                    {
                                        base_type = token2;
                                    }
                                    else if(found_colon && token2->kind == TokenBaseKind_StatementClose)
                                    {
                                        break;
                                    }
                                }
                                else { break; }
                                if(!token_it_inc_non_whitespace(&it2)) { break; }
                            }
                            
                            if(base_type != 0)
                            {
                                F4_Language_PosContext_PushData_Dot(arena, &first, &last,
                                                                    push_buffer_range(app, arena, buffer, Ii64(base_type)), last_query_candidate);
                            }
                        }
                    }
                }
            }
            else { break; }
            if(!token_it_dec_non_whitespace(&it))
            {
                break;
            }
        }
    }
    
    return first;
}

internal LANGUAGE_HIGHLIGHTER(F4_Jai_Highlight) {
}

NAMESPACE_END()

#endif // FCODER_CUSTOM_LANG_JAI_CPP