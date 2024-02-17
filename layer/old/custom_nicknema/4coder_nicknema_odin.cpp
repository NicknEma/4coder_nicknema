#ifndef FCODER_NICKNEMA_ODIN_CPP
#define FCODER_NICKNEMA_ODIN_CPP

// This file implements the procedures declared in 4coder_nicknema_languages.h for the odin language.

NAMESPACE_BEGIN(nicknema)

#include "generated/4coder_nicknema_lexer_odin.h"
#include "generated/4coder_nicknema_lexer_odin.cpp"

//
// Index file:
//

internal void odin__parse_decl_set(F4_Index_ParseCtx *ctx, F4_Index_Note *parent) {
    F4_Index_Note *last_parent = F4_Index_PushParent(ctx, parent);
    
    for (; !ctx->done; ) {
        Token *name = 0;
        if (F4_Index_RequireTokenKind(ctx, TokenBaseKind_Identifier, &name, F4_Index_TokenSkipFlag_SkipWhitespace) &&
            F4_Index_RequireToken(ctx, str8_lit(":"), F4_Index_TokenSkipFlag_SkipWhitespace)) {
            F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_Decl, 0);
            
            for (; !ctx->done; ) {
                Token *token = token_it_read(&ctx->it);
                if (token->sub_kind == TokenOdinKind_Comma ||
                    token->sub_kind == TokenOdinKind_Semicolon) {
                    F4_Index_ParseCtx_Inc(ctx, F4_Index_TokenSkipFlag_SkipWhitespace);
                    break;
                } else if (token->kind == TokenBaseKind_ScopeClose ||
                           token->sub_kind == TokenOdinKind_ParenCl) {
                    goto end;
                }
                
                F4_Index_ParseCtx_Inc(ctx, F4_Index_TokenSkipFlag_SkipWhitespace);
            }
            
        } else {
            break;
        }
    }
    
    end:;
    F4_Index_PopParent(ctx, last_parent);
}

internal void odin__parse_decl_set_braces(F4_Index_ParseCtx *ctx, F4_Index_Note *parent) {
    if (F4_Index_RequireToken(ctx, str8_lit("{"), F4_Index_TokenSkipFlag_SkipWhitespace)) {
        odin__parse_decl_set(ctx, parent);
        F4_Index_RequireToken(ctx, str8_lit("}"), F4_Index_TokenSkipFlag_SkipWhitespace);
    }
}

internal void odin__parse_decl_set_parens(F4_Index_ParseCtx *ctx, F4_Index_Note *parent) {
    if (F4_Index_RequireToken(ctx, str8_lit("("), F4_Index_TokenSkipFlag_SkipWhitespace)) {
        odin__parse_decl_set(ctx, parent);
        F4_Index_RequireToken(ctx, str8_lit(")"), F4_Index_TokenSkipFlag_SkipWhitespace);
    }
}

// Indexes an entire file of a language and adds stuff to the code index.
procedure FILE_INDEXER(odin__index_file) {
    int scope_nest = 0;
    
    for (; !ctx->done; ) {
        Token *name = 0;
        F4_Index_TokenSkipFlags flags = F4_Index_TokenSkipFlag_SkipWhitespace;
        
        {
            // NOTE(rjf): Handle nests.
            Token *token = token_it_read(&ctx->it);
            if (token) {
                if (token->kind == TokenBaseKind_ScopeOpen) {
                    scope_nest += 1;
                } else if (token->kind == TokenBaseKind_ScopeClose) {
                    scope_nest -= 1;
                }
                
                if (scope_nest < 0)
                    scope_nest = 0;
            }
        }
        
        if (F4_Index_RequireTokenKind(ctx, TokenBaseKind_Identifier, &name, flags)) {
            // NOTE(rjf): Definitions
            if (F4_Index_RequireToken(ctx, str8_lit("::"), flags)) {
                
                // Procedures
                // @Note(ema): This only looks for the prototype of the procedure, it does not
                // walk through the whole body.
#if 0
                
                if (F4_Index_PeekToken(ctx, str8_lit("(")) || (F4_Index_RequireToken(ctx, str8_lit("inline"), flags) && F4_Index_PeekToken(ctx, str8_lit("(")))) {
                    F4_Index_Note *parent = F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_Function, 0);
                    odin__parse_decl_set_parens(ctx, parent);
                }
                
#else
                
                // @Incomplete(ema): attributes and directives
                if ((F4_Index_RequireToken(ctx, str8_lit("proc"), flags) && F4_Index_PeekToken(ctx, str8_lit("("))) || (F4_Index_RequireToken(ctx, str8_lit("proc"), flags) &&
                                                                                                                        F4_Index_RequireToken(ctx, str8_lit("LiteralString"), flags) &&
                                                                                                                        F4_Index_PeekToken(ctx, str8_lit("(")))) {
                    F4_Index_Note *parent = F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_Function, 0);
                    odin__parse_decl_set_parens(ctx, parent);
                }
                
#endif
                
                // Structs.
                else if (F4_Index_RequireToken(ctx, str8_lit("struct"), flags)) {
                    F4_Index_Note *parent = F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_Type, F4_Index_NoteFlag_ProductType);
                    odin__parse_decl_set_braces(ctx, parent);
                }
                
                // Unions.
                else if (F4_Index_RequireToken(ctx, str8_lit("union"), flags)) {
                    F4_Index_Note *parent = F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_Type, F4_Index_NoteFlag_SumType);
                    odin__parse_decl_set_braces(ctx, parent);
                }
                
                // Enums.
                else if (F4_Index_RequireToken(ctx, str8_lit("enum"), flags)) {
                    F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_Type, 0);
                }
                
                // Constants.
                else if (F4_Index_RequireTokenKind(ctx, TokenBaseKind_Identifier,     0, flags) || F4_Index_RequireTokenKind(ctx, TokenBaseKind_LiteralInteger, 0, flags) || F4_Index_RequireTokenKind(ctx, TokenBaseKind_LiteralFloat,   0, flags) || F4_Index_RequireTokenKind(ctx, TokenBaseKind_LiteralString,  0, flags)) {
                    F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_Constant, 0);
                }
            }
        }
        
#if 1
        //~ NOTE(rjf): Comment Tags
        // @Note(ema): Comment tags? They look like regular comments...
        else if (F4_Index_RequireTokenKind(ctx, TokenBaseKind_Comment, &name, F4_Index_TokenSkipFlag_SkipWhitespace)) {
            F4_Index_ParseComment(ctx, name);
        }
#endif
        
        else {
            F4_Index_ParseCtx_Inc(ctx, flags);
        }
    }
}

//
// Positional context:
//

internal Token *_F4_Jai_FindDecl(Application_Links *app, Buffer_ID buffer, i64 pos, Token *decl_name) {
    Token *result = 0; cast(void)result;
#if 0
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
#endif
    return result;
}

//
// Figures out some language-specific contextual information given some
// position in a buffer. For example, what type I am accessing, what function I am
// calling, which parameter am I accessing, etc.
function POSITIONAL_CONTEXT_GETTER(odin__get_positional_context) {
    int count = 0; cast(void)count;
    Positional_Context_Data *first = 0;
    Positional_Context_Data *last = 0; cast(void)last;
    
#if 0
    Token_Array tokens = get_token_array_from_buffer(app, buffer);
    
    // NOTE(rjf): Search for left parentheses (function call or macro invocation).
    // @Note(ema): Why?
    {
        Token_Iterator_Array it = token_iterator_pos(0, &tokens, pos);
        
        int paren_nest = 0;
        int arg_idx = 0;
        for (int i = 0; count < 4; i += 1) {
            Token *token = token_it_read(&it);
            if (token) {
                if (paren_nest == 0 && token->sub_kind == TokenJaiKind_ParenOp && token_it_dec_non_whitespace(&it)) {
                    Token *name = token_it_read(&it);
                    if (name && name->kind == TokenBaseKind_Identifier) {
                        F4_Language_PosContext_PushData_Call(arena, &first, &last, push_buffer_range(app, arena, buffer, Ii64(name)), arg_idx);
						count  += 1;
                        arg_idx = 0;
                    }
                } else if (token->sub_kind == TokenJaiKind_ParenOp) {
                    paren_nest -= 1;
                } else if (token->sub_kind == TokenJaiKind_ParenCl && i > 0) {
                    paren_nest += 1;
                } else if (token->sub_kind == TokenJaiKind_Comma && i > 0 && paren_nest == 0) {
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
    
    // NOTE(rjf): Search for *.* pattern (accessing a type)
    // @Note(ema): Again, why?
    {
        Token_Iterator_Array it = token_iterator_pos(0, &tokens, pos);
        
        Token *last_query_candidate = 0;
        for (int i = 0; i < 3; i += 1) {
            Token *token = token_it_read(&it);
            if (token) {
                if (i == 0 && token->kind == TokenBaseKind_Identifier) {
                    last_query_candidate = token;
                } else if ((i == 0 || i == 1) && token->sub_kind == TokenJaiKind_Dot && token_it_dec_non_whitespace(&it)) {
                    Token *decl_name = token_it_read(&it);
                    if (decl_name && decl_name->kind == TokenBaseKind_Identifier) {
                        Token *decl_start = _F4_Jai_FindDecl(app, buffer, decl_name->pos, decl_name);
                        if (decl_start) {
                            Token_Iterator_Array it2 = token_iterator_pos(0, &tokens, decl_start->pos);
                            b32 found_colon = 0;
                            Token *base_type = 0;
                            for (;;) {
                                Token *token2 = token_it_read(&it2);
                                if (token2) {
                                    if (token2->sub_kind == TokenJaiKind_Colon) {
                                        found_colon = 1;
                                    } else if (found_colon && token2->kind == TokenBaseKind_Identifier) {
                                        base_type = token2;
                                    } else if (found_colon && token2->kind == TokenBaseKind_StatementClose) {
                                        break;
                                    }
                                } else {
                                    break;
                                }
                                
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
            } else {
                break;
            }
            
            if (!token_it_dec_non_whitespace(&it)) {
                break;
            }
        }
    }
#endif
    
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

#endif // FCODER_NICKNEMA_ODIN_CPP