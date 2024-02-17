#ifndef FCODER_NICKNEMA_HOOKS_CPP
#define FCODER_NICKNEMA_HOOKS_CPP

//
// Some constants.
//

ARGB_Color DEFAULT_FUNCTION_COLOR             = 0xFF769fdf;
ARGB_Color DEFAULT_TYPE_COLOR                 = 0xFF85b920;
ARGB_Color DEFAULT_CONSTANT_COLOR             = 0xffeb7b46;
ARGB_Color DEFAULT_MACRO_COLOR                = 0xffa48391;

ARGB_Color DEFAULT_OCCURRENCE_HIGHLIGHT       = 0x44cb4b16;
ARGB_Color DEFAULT_OCCURRENCE_HIGHLIGHT_MINOR = 0x33cb4b16;

//
// Brace highlight.
//

// @Note(ema): Based on draw_paren_highlight from 4coder_draw.cpp
procedure void draw_brace_highlight(Application_Links *app, Buffer_ID buffer, Text_Layout_ID text_layout_id, i64 pos, ARGB_Color *colors, i32 color_count) {
    Token_Array token_array = get_token_array_from_buffer(app, buffer);
    if (token_array.tokens != 0) {
        Token_Iterator_Array it = token_iterator_pos(0, &token_array, pos);
        Token *token = token_it_read(&it);
        if (token != 0 && token->kind == TokenBaseKind_ScopeOpen) {
            pos = token->pos + token->size;
        } else {
            if (token_it_dec_all(&it)) {
                token = token_it_read(&it);
                if (token->kind == TokenBaseKind_ScopeClose && pos == token->pos + token->size) {
                    pos = token->pos;
                }
            }
        }
    }
    
    draw_enclosures(app, text_layout_id, buffer, pos, FindNest_Scope, RangeHighlightKind_CharacterHighlight, 0, 0, colors, color_count);
}

//
// Hex color preview.
//

// @Note(ema): Provided by thevaber at
// https://gist.github.com/thevaber/58bb6a1c03ebe56309545f413e898a95

function u32 ryanb_calculate_color_brightness(u32 color) {
    u32 r = ((color >> 16) & 0xFF);
    u32 g = ((color >>  8) & 0xFF);
    u32 b = ((color >>  0) & 0xFF);
    
    // @Cleanup: What are these magic numbers?
    f32 brightness = sqrtf((r * r * 0.241f) + (g * g * 0.691f) + (b * b * 0.068f));
    
    return (u32)brightness;
}

function void ryanb_draw_hex_color_preview(Application_Links* app, Buffer_ID buffer, Text_Layout_ID text_layout_id, i64 pos) {
    ProfileScope(app, "ryanb draw hex color preview");
    
    Scratch_Block scratch(app);
    
    // @Cleanup: Remove magic numbers and characters.
    Range_i64 range = enclose_pos_alpha_numeric(app, buffer, pos);
    String_Const_u8 token = push_buffer_range(app, scratch, buffer, range);
    if (token.size == 10) {
        if (token.str[0] == '0' && (token.str[1] == 'x' || token.str[1] == 'X')) {
            b32 is_hex = true;
            for (u32 i = 0; (i < 8) && is_hex; i += 1) {
                char c = token.str[i + 2];
                is_hex = ((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || (c >= '0' && c <= '9'));
            }
            
            if (is_hex) {
                String_Const_u8 hex = string_substring(token, Ii64_size(2, 8));
                
                ARGB_Color hex_color = (u32)string_to_integer(hex, 16);
                draw_character_block(app, text_layout_id, Ii64_size(range.min, 10), 2.0f, hex_color);
                
                ARGB_Color text_color = ryanb_calculate_color_brightness(hex_color) < 128 ? 0xFFFFFFFF : 0xFF000000;
                paint_text_color(app, text_layout_id, range, text_color);
            }
        }
    }
}

#if 0
function void nicknema_preview_hex_colors(Application_Links *app, Buffer_ID buffer, Text_Layout_ID text_layout_id) {
    Scratch_Block scratch(app);
    Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
    String_Const_u8 text = push_buffer_range(app, scratch, buffer, visible_range);
    
    for (i64 index = visible_range.min; text.size > 0; ) {
        if (text.size >= 2+8 && text.str[0] == '0' && (text.str[1] == 'x' || text.str[1] == 'X')) {
            text = string_skip(text, 2);
            index += 2;
            
            b32 looks_like_hex_number = true;
            for (i32 i = 0; i < 8; i++) {
                char c = text.str[i];
                if (!((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || (c >= '0' && c <= '9'))) {
                    looks_like_hex_number = false;
                    break;
                }
            }
            
            if (!looks_like_hex_number) { // @Note(ema): Skip non-hex-numbers.
                continue;
            }
            
            String_Const_u8 hex_text = string_prefix(text, 8);
            u32 color = (u32)string_to_integer(hex_text, 16);
            
            u8 alpha = (u8) ((color >> 24) & 0xFF);
            u8 alpha_threshold = 0x7F;
            
            // @Incomplete(ema): Include suffixes like L, LL, ULL.
            
            if (alpha >= alpha_threshold) {
                paint_text_color(app, text_layout_id, Ii64_size(index - 2, 10), color);
            } else {
                u32 full_alpha_color = color | (0xFF << 24);
                paint_text_color(app, text_layout_id, Ii64_size(index - 2, 10), full_alpha_color);
                
                draw_character_block(app, text_layout_id, Ii64_size(index - 2, 10), 2.0f, color);
                
                // @Incomplete(ema): Rectangle at the end of line. (Problem: multiple hex colors on the same line.
                /*
                Rect_f32 rect = text_layout_character_on_screen(app, text_layout_id, index + 8);
                draw_rectangle(app, rect, 2.0f, color);
*/
            }
            
            text = string_skip(text, 8);
            index += 8;
        } else {
            text = string_skip(text, 1);
            index += 1;
        }
    }
}
#endif

//
// Range highlight.
//

// @Note(ema): From skytrias_custom

enum skytrias_Range_Hightlight_Kind {
	skytrias_Range_Hightlight_Kind_WHOLE,
	skytrias_Range_Hightlight_Kind_UNDERLINE,
};

// @Doc(ema): Given a range and a color, highlights or underlines the text.
procedure void skytrias_render_range_highlight(Application_Links *app, View_ID view_id, Text_Layout_ID text_layout_id, Range_i64 range, skytrias_Range_Hightlight_Kind kind, ARGB_Color color) {
	Rect_f32 range_start_rect = text_layout_character_on_screen(app, text_layout_id, range.start);
	Rect_f32 range_end_rect   = text_layout_character_on_screen(app, text_layout_id, range.end - 1);
	Rect_f32 total_range_rect = {0};
    total_range_rect.x0 = nicknema::f32_min_of(range_start_rect.x0, range_end_rect.x0);
	total_range_rect.y0 = nicknema::f32_min_of(range_start_rect.y0, range_end_rect.y0);
	total_range_rect.x1 = nicknema::f32_max_of(range_start_rect.x1, range_end_rect.x1);
	total_range_rect.y1 = nicknema::f32_max_of(range_start_rect.y1, range_end_rect.y1);
	
    // @Cleanup(ema): Why? Wasn't an if statement better?
	switch (kind) {
		case skytrias_Range_Hightlight_Kind_UNDERLINE: {
			total_range_rect.y0 = total_range_rect.y1 - 1.f;
			total_range_rect.y1 += 1.f;
		} break;
	}
	
    draw_rectangle(app, total_range_rect, 4.f, color);
}

//
// CPP-Specific Token coloring.
//

// @Doc: Returns the color of an individual cpp token.
function FColor ryanb_get_token_color_cpp(Token token) {
    FColor result = fcolor_id(defcolor_text_default);
    
    switch (token.kind) {
        case TokenBaseKind_Preprocessor:   result = fcolor_id(defcolor_preproc);        break;
        case TokenBaseKind_Keyword:        result = fcolor_id(defcolor_keyword);        break;
        case TokenBaseKind_Comment:        result = fcolor_id(defcolor_comment);        break;
        case TokenBaseKind_LiteralString:  result = fcolor_id(defcolor_str_constant);   break;
        case TokenBaseKind_LiteralInteger: result = fcolor_id(defcolor_int_constant);   break;
        case TokenBaseKind_LiteralFloat:   result = fcolor_id(defcolor_float_constant); break;
        
        default: switch (token.sub_kind) {
            // case TokenCppKind_BraceOp:
            // case TokenCppKind_BraceCl:
            // case TokenCppKind_ParenOp:
            // case TokenCppKind_ParenCl:
            // case TokenCppKind_BrackOp:
            // case TokenCppKind_BrackCl:
            case TokenCppKind_And:
            case TokenCppKind_AndAnd:
            case TokenCppKind_Or:
            case TokenCppKind_OrOr:
            // case TokenCppKind_Colon:
            // case TokenCppKind_ColonColon:
            // case TokenCppKind_Semicolon:
            // case TokenCppKind_Comma:
            case TokenCppKind_Dot:
            // case TokenCppKind_DotDotDot:
            case TokenCppKind_Arrow:
            case TokenCppKind_Plus:
            case TokenCppKind_PlusPlus:
            case TokenCppKind_Minus:
            case TokenCppKind_MinusMinus:
            case TokenCppKind_Star:
            case TokenCppKind_Div:
            case TokenCppKind_Mod:
            case TokenCppKind_Ternary:
            case TokenCppKind_Eq:
            case TokenCppKind_PlusEq:
            case TokenCppKind_MinusEq:
            case TokenCppKind_StarEq:
            case TokenCppKind_DivEq:
            case TokenCppKind_ModEq:
            case TokenCppKind_Less:
            case TokenCppKind_LessEq:
            case TokenCppKind_Grtr:
            case TokenCppKind_GrtrEq:
            case TokenCppKind_EqEq:
            case TokenCppKind_NotEq:                 result = fcolor_id(defcolor_keyword, 2); break;
            
            case TokenCppKind_LiteralCharacter:
            case TokenCppKind_LiteralCharacterWide:
            case TokenCppKind_LiteralCharacterUTF8:
            case TokenCppKind_LiteralCharacterUTF16:
            case TokenCppKind_LiteralCharacterUTF32: result = fcolor_id(defcolor_char_constant); break;
            
            case TokenCppKind_LiteralTrue:
            case TokenCppKind_LiteralFalse:          result = fcolor_id(defcolor_bool_constant); break;
            
            case TokenCppKind_PPIncludeFile:         result = fcolor_id(defcolor_include); break;
            
            default: break;
        }
    }
    
    return result;
}

// @Doc: Colors individual cpp tokens, without knowing their contexts (i.e. keywords, but not custom types).
procedure void ryanb_draw_cpp_token_colors(Application_Links *app, Text_Layout_ID text_layout_id, Token_Array *array) {
    ProfileScope(app, "ryanb draw cpp token colors");
    
    auto visible_range = text_layout_get_visible_range(app, text_layout_id);
    i64  first_index   = token_index_from_pos(array, visible_range.first);
    auto it            = token_iterator_index(0, array, first_index);
    
    for (;;) {
        Token *token = token_it_read(&it);
        if (token->pos >= visible_range.one_past_last)
            break;
        
        auto color = ryanb_get_token_color_cpp(*token);
        auto argb  = fcolor_resolve(color);
        paint_text_color(app, text_layout_id, Ii64_size(token->pos, token->size), argb);
        
        if (!token_it_inc_all(&it))
            break;
    }
}

#if 0
function void
nicknema_draw_token_colors(Application_Links *app, Text_Layout_ID text_layout_id, Token_Array *array) {
    
}

enum class Language_ID {
    NONE,
    
    C,
    CPP,
    ODIN,
    BAT,
};

struct Language_Match {
    Language_ID     id;
    String_Const_u8 extension;
};

global Language_Match languages[] = {
    { Language_ID::C,    string_u8_litexpr(".c") },
    { Language_ID::C,    string_u8_litexpr(".cc") },
    { Language_ID::C,    string_u8_litexpr(".h") },
    { Language_ID::CPP,  string_u8_litexpr(".cpp") },
    { Language_ID::CPP,  string_u8_litexpr(".hpp") },
    { Language_ID::ODIN, string_u8_litexpr(".odin") },
    { Language_ID::BAT,  string_u8_litexpr(".bat") },
};

function Language_ID
get_language_id(String_Const_u8 buffer_name) {
    Language_ID result = Language_ID::NONE;
    
    for (int i = 0; i < sizeof(languages) / sizeof(*languages); i += 1) {
        if (string_match_insensitive(string_postfix(buffer_name, languages[i].extension.size), languages[i].extension)) {
            result = languages[i].id;
        }
    }
    
    return result;
}

function Language_ID
get_language_id(Application_Links *app, Buffer_ID buffer) {
    Language_ID result;
    
    {
        Scratch_Block scratch(app);
        String_Const_u8 buffer_name = push_buffer_base_name(app, scratch, buffer);
        
        result = get_language_id(buffer_name);
    }
    
    return result;
}
#endif

//
// Recoloring of strings or identifiers.
//

struct String_Color_Pair {
    String_Const_u8 needle;
    ARGB_Color      color;
};

// NOTE(mrmixer): based on draw_comment_highlights.
// @Doc: Scans for specific identifiers and overwrites their color. Useful for adding custom keywords.
procedure void mrmixer_recolor_identifiers(Application_Links *app, Buffer_ID buffer, Text_Layout_ID text_layout_id, Token_Array *tokens, String_Color_Pair *pairs, i32 pair_count) {
    Scratch_Block scratch(app);
    
    Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
    i64 first_index         = token_index_from_pos(tokens, visible_range.first);
    Token_Iterator_Array it = token_iterator_index(buffer, tokens, first_index);
    
    for (;;) {
        Temp_Memory_Block temp(scratch);
        
        Token *token = token_it_read(&it);
        if (token->pos >= visible_range.one_past_last)
            break;
        
        String_Const_u8 tail = {0};
        if (token_it_check_and_get_lexeme(app, scratch, &it, TokenBaseKind_Identifier, &tail)) {
            String_Color_Pair *pair = pairs;
            for (i32 i = 0; i < pair_count; i += 1, pair += 1) {
                if (string_match(tail, pair->needle)) {
                    Range_i64 range = Ii64_size(token->pos, token->size);
                    paint_text_color(app, text_layout_id, range, pair->color);
                    
                    break;
                }
            }
        }
        
        if (!token_it_inc_non_whitespace(&it))
            break;
    }
}

// @Doc: Scans for specific raw text strings and overwrites their color. Useful for non-code files.
procedure void mrmixer_recolor_strings(Application_Links *app, Buffer_ID buffer, Text_Layout_ID text_layout_id, String_Color_Pair *pairs, i32 pair_count) {
    Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
    
    String_Color_Pair *pair = pairs;
    for (i32 i = 0; i < pair_count; i += 1, pair += 1) {
        if (pair->needle.size > 0) {
            i64 position = visible_range.min;
            seek_string_insensitive_forward(app, buffer, position - 1, visible_range.max, pair->needle, &position);
            
            while (position < visible_range.max){
                Range_i64 range = Ii64_size(position, pair->needle.size);
                paint_text_color(app, text_layout_id, range, pair->color);
                seek_string_insensitive_forward(app, buffer, position, visible_range.max, pair->needle, &position);
            }
        }
    }
}

//
// Main rendering loops.
//

procedure void render_buffer(Application_Links *app, View_ID view_id, Face_ID face_id, Buffer_ID buffer, Text_Layout_ID text_layout_id, Rect_f32 rect) {
    ProfileScope(app, "nicknema render buffer");
    
    Rect_f32 prev_clip  = draw_set_clip(app, rect);
    
    View_ID active_view = get_active_view(app, Access_Always);
    b32  is_active_view = (active_view == view_id);
    
    Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
    
    //
    // Draw visible text.
    //
    
    Token_Array tokens = get_token_array_from_buffer(app, buffer);
    if (tokens.tokens != 0) {
        // There are tokens: This is a code file. @Note(ema): This code assumes a cpp file.
        
        // Draw base cpp colors.
        ryanb_draw_cpp_token_colors(app, text_layout_id, &tokens);
        
        {
            // Overwrite colors for TODOs, NOTEs and such.
            // @Hardcoded, @Incomplete: Read this list from a file?
            
            Comment_Highlight_Pair pairs[] = {
                {string_u8_litexpr("NOTE"),           finalize_color(defcolor_comment_pop, 0)},
                {string_u8_litexpr("TODO"),           finalize_color(defcolor_comment_pop, 1)},
                
                // @Note(ema): Additional comment keywords.
                {string_u8_litexpr("@Note"),          finalize_color(defcolor_comment_pop, 0)},
                {string_u8_litexpr("@Hardcoded"),     finalize_color(defcolor_comment_pop, 0)},
                {string_u8_litexpr("@Doc"),           finalize_color(defcolor_comment_pop, 0)},
                
                {string_u8_litexpr("@Todo"),          finalize_color(defcolor_comment_pop, 1)},
                {string_u8_litexpr("@Incomplete"),    finalize_color(defcolor_comment_pop, 1)},
                {string_u8_litexpr("@Speed"),         finalize_color(defcolor_comment_pop, 1)},
                {string_u8_litexpr("@Rename"),        finalize_color(defcolor_comment_pop, 1)},
                {string_u8_litexpr("@Robustness"),    finalize_color(defcolor_comment_pop, 1)},
                {string_u8_litexpr("@Cleanup"),       finalize_color(defcolor_comment_pop, 1)},
                {string_u8_litexpr("@Hack"),          finalize_color(defcolor_comment_pop, 1)},
                {string_u8_litexpr("@Temporary"),     finalize_color(defcolor_comment_pop, 1)},
                {string_u8_litexpr("@Unimplemented"), finalize_color(defcolor_comment_pop, 1)},
            };
            
            b32 use_comment_keyword = def_get_config_b32(vars_save_string_lit("use_comment_keywords"));
            if (use_comment_keyword)
                draw_comment_highlights(app, buffer, text_layout_id, &tokens, pairs, ArrayCount(pairs));
        }
        
        {
            // Overwrite colors for cpp keywords not recognized by default 4coder, or for other identifiers that are useful if seen as keywords.
            // @Hardcoded, @Incomplete: Read this list from a file?
            
            String_Color_Pair pairs[] = {
                string_u8_litexpr("u8"),  finalize_color(defcolor_keyword, 0),
                string_u8_litexpr("u16"), finalize_color(defcolor_keyword, 0),
                string_u8_litexpr("u32"), finalize_color(defcolor_keyword, 0),
                string_u8_litexpr("u64"), finalize_color(defcolor_keyword, 0),
                
                string_u8_litexpr("i8"),  finalize_color(defcolor_keyword, 0),
                string_u8_litexpr("i16"), finalize_color(defcolor_keyword, 0),
                string_u8_litexpr("i32"), finalize_color(defcolor_keyword, 0),
                string_u8_litexpr("i64"), finalize_color(defcolor_keyword, 0),
                
                string_u8_litexpr("b8"),  finalize_color(defcolor_keyword, 0),
                string_u8_litexpr("b16"), finalize_color(defcolor_keyword, 0),
                string_u8_litexpr("b32"), finalize_color(defcolor_keyword, 0),
                string_u8_litexpr("b64"), finalize_color(defcolor_keyword, 0),
                
                string_u8_litexpr("f32"), finalize_color(defcolor_keyword, 0),
                string_u8_litexpr("f64"), finalize_color(defcolor_keyword, 0),
                
                string_u8_litexpr("auto"),      finalize_color(defcolor_keyword, 0),
                string_u8_litexpr("constexpr"), finalize_color(defcolor_keyword, 0),
                string_u8_litexpr("consteval"), finalize_color(defcolor_keyword, 0),
                string_u8_litexpr("restrict"),  finalize_color(defcolor_keyword, 0),
                
                string_u8_litexpr("__debugbreak"), 0xffa46391,
            };
            
            mrmixer_recolor_identifiers(app, buffer, text_layout_id, &tokens, pairs, ArrayCount(pairs));
        }
        
        {
            // Overwrite color of functions, types, constants and macros.
            // @Incomplete(ema): Constants. Is it possible to expand the CodeIndexNote enum?
            Scratch_Block scratch(app);
            
            ARGB_Color function_color = DEFAULT_FUNCTION_COLOR;
            ARGB_Color type_color     = DEFAULT_TYPE_COLOR;
            ARGB_Color constant_color = DEFAULT_CONSTANT_COLOR; cast(void)constant_color;
            ARGB_Color macro_color    = DEFAULT_MACRO_COLOR;    cast(void)macro_color;
            
            auto it = token_iterator_pos(0, &tokens, visible_range.first);
            for (;;) {
                if (!token_it_inc_non_whitespace(&it))
                    break;
                
                Token           *token = token_it_read(&it);
                String_Const_u8 lexeme = push_token_lexeme(app, scratch, buffer, token);
                Code_Index_Note *note  = code_index_note_from_string(lexeme);
                
                if (note != 0) switch (note->note_kind) {
                    case CodeIndexNote_Function:
                    paint_text_color(app, text_layout_id, Ii64_size(token->pos, token->size), function_color);
                    break;
                    
                    case CodeIndexNote_Type:
                    paint_text_color(app, text_layout_id, Ii64_size(token->pos, token->size), type_color);
                    break;
                    
                    case CodeIndexNote_Macro:
                    paint_text_color(app, text_layout_id, Ii64_size(token->pos, token->size), macro_color);
                    break;
                    
#if 0
                    case CodeIndexNote_Constant:
                    paint_text_color(app, text_layout_id, Ii64_size(token->pos, token->size), constant_color);
                    break;
#endif
                    
                    default: break;
                }
            }
        }
        
    } else {
        // There are no tokens: this is a raw text file.
        paint_text_color_fcolor(app, text_layout_id, visible_range, fcolor_id(defcolor_text_default));
    }
    
    //
    // Draw cursor and things that depend on it.
    //
    
    // NOTE(allen): Define cursor shape.
    // @Todo(ema): Thin cursor.
    Face_Metrics metrics     = get_face_metrics(app, face_id);
    u64 cursor_roundness_100 = def_get_config_u64(app, vars_save_string_lit("cursor_roundness"));
    f32 cursor_roundness     = metrics.normal_advance * cursor_roundness_100 * 0.01f;
    f32 mark_thickness       = cast(f32)def_get_config_u64(app, vars_save_string_lit("mark_thickness"));
    
    i64 cursor_pos = view_correct_cursor(app, view_id);
    view_correct_mark(app, view_id);
    
    {
        // Do brace and paren helper.
        b32 use_paren_helper = def_get_config_b32(vars_save_string_lit("use_paren_helper"));
        if (use_paren_helper){
            Color_Array colors = finalize_color_array(defcolor_text_cycle);
            draw_paren_highlight(app, buffer, text_layout_id, cursor_pos, colors.vals, colors.count);
        }
        
        // @Incomplete: read variable from config file.
        b32 use_brace_helper = true;
        if (use_brace_helper) {
            Color_Array colors = finalize_color_array(defcolor_text_cycle);
            draw_brace_highlight(app, buffer, text_layout_id, cursor_pos, colors.vals, colors.count);
        }
    }
    
    {
        // Use scope highlight.
        // @Rename(ema): Is it a good idea to rename the variable in the config file? Idk. But 'use' is a weird word for what it does. Try "highlight_nested_scopes"?
        b32 use_scope_highlight = def_get_config_b32(vars_save_string_lit("use_scope_highlight"));
        if (use_scope_highlight) {
            Color_Array colors = finalize_color_array(defcolor_back_cycle);
            draw_scope_highlight(app, buffer, text_layout_id, cursor_pos, colors.vals, colors.count);
        }
    }
    
    {
        // Highlight errors, jumps (together because they're basically the same thing).
        b32 use_error_highlight = def_get_config_b32(vars_save_string_lit("use_error_highlight"));
        b32 use_jump_highlight  = def_get_config_b32(vars_save_string_lit("use_jump_highlight"));
        
        if (use_error_highlight || use_jump_highlight) {
            auto compilation_buffer_name = string_u8_litexpr("*compilation*");
            auto compilation_buffer      = get_buffer_by_name(app, compilation_buffer_name, Access_Always);
            
            // Error highlight.
            if (use_error_highlight)
                draw_jump_highlights(app, buffer, text_layout_id, compilation_buffer, fcolor_id(defcolor_highlight_junk));
            
            // Jump highlight.
            if (use_jump_highlight) {
                auto jump_buffer = get_locked_jump_buffer(app);
                if (jump_buffer != compilation_buffer)
                    draw_jump_highlights(app, buffer, text_layout_id, jump_buffer, fcolor_id(defcolor_highlight_white));
            }
        }
    }
    
    {
        // Preview hex colors.
        // @Incomplete(ema): read variable from config file.
        b32 should_preview_hex_colors = true;
        if (should_preview_hex_colors)
            ryanb_draw_hex_color_preview(app, buffer, text_layout_id, cursor_pos);
    }
    
    {
#if 0
        // Highlight token occurrences.
        // @Incomplete(ema): read variable from config file.
        b32 should_highlight_token_occurrences = true;
        if (should_highlight_token_occurrences) {
            Buffer_ID            active_cursor_buffer        = view_get_buffer(app, active_view, Access_Always);
            i64                  active_cursor_pos           = view_get_cursor_pos(app, active_view);
            Token_Array          active_cursor_buffer_tokens = get_token_array_from_buffer(app, active_cursor_buffer);
            Token_Iterator_Array active_cursor_it            = token_iterator_pos(0, &active_cursor_buffer_tokens, active_cursor_pos);
            Token               *active_cursor_token         = token_it_read(&active_cursor_it);
            
            if (active_cursor_token) {
                Scratch_Block   scratch(app);
                String_Const_u8 active_cursor_string = push_buffer_range(app, scratch, active_cursor_buffer, Ii64(active_cursor_token));
                
                // auto visible_range = text_layout_get_visible_range(app, text_layout_id);
                i64  first_index   = token_index_from_pos(&tokens, visible_range.first);
                auto it            = token_iterator_index(0, &tokens, first_index);
                
                for (;;) {
                    Token *token = token_it_read(&it);
                    if (!token || token->pos >= visible_range.one_past_last)
                        break;
                    
                    if (token->kind == TokenBaseKind_Identifier) {
                        Range_i64 token_range = Ii64(token);
                        String_Const_u8 token_string = push_buffer_range(app, scratch, buffer, token_range);
                        
                        auto occurrence_highlight       = DEFAULT_OCCURRENCE_HIGHLIGHT;
                        auto occurrence_highlight_minor = DEFAULT_OCCURRENCE_HIGHLIGHT_MINOR;
                        
                        if (range_contains(token_range, view_get_cursor_pos(app, view_id)))
                            skytrias_render_range_highlight(app, view_id, text_layout_id, token_range, skytrias_Range_Hightlight_Kind_WHOLE, occurrence_highlight);
                        else if(active_cursor_token->kind == TokenBaseKind_Identifier && string_match(token_string, active_cursor_string))
                            skytrias_render_range_highlight(app, view_id, text_layout_id, token_range, skytrias_Range_Hightlight_Kind_WHOLE, occurrence_highlight_minor);
                    }
                    
                    if (!token_it_inc_non_whitespace(&it))
                        break;
                }
            }
        }
#endif
    }
    
    {
        // Highlight line at cursor.
        b32 highlight_line_at_cursor = def_get_config_b32(vars_save_string_lit("highlight_line_at_cursor"));
        if (highlight_line_at_cursor && is_active_view) {
            i64 line_number = get_line_number_from_pos(app, buffer, cursor_pos);
            draw_line_highlight(app, text_layout_id, line_number, fcolor_id(defcolor_highlight_cursor_line));
        }
    }
    
    {
        // Draw whitespace.
        b64 show_whitespace = false;
        view_get_setting(app, view_id, ViewSetting_ShowWhitespace, &show_whitespace);
        
        if (show_whitespace) {
            if (tokens.tokens == 0)
                draw_whitespace_highlight(app, buffer, text_layout_id, cursor_roundness);
            else
                draw_whitespace_highlight(app, text_layout_id, &tokens, cursor_roundness);
        }
    }
    
    {
        // Draw cursor.
        switch (fcoder_mode) {
            case FCoderMode_Original:
            draw_original_4coder_style_cursor_mark_highlight(app, view_id, is_active_view, buffer, text_layout_id, cursor_roundness, mark_thickness);
            break;
            
            case FCoderMode_NotepadLike:
            draw_notepad_style_cursor_highlight(app, view_id, buffer, text_layout_id, cursor_roundness);
            break;
        }
    }
    
    //
    // Finalize drawing.
    //
    
    paint_fade_ranges(app, text_layout_id, buffer);
    
    // NOTE(allen): Put the actual text on the actual screen.
    draw_text_layout_default(app, text_layout_id);
    
    draw_set_clip(app, prev_clip);
}

procedure void render_caller(Application_Links *app, Frame_Info frame_info, View_ID view_id) {
    ProfileScope(app, "nicknema render caller");
    
    View_ID active_view = get_active_view(app, Access_Always);
    b32  is_active_view = (active_view == view_id);
    
    Rect_f32 region = draw_background_and_margin(app, view_id, is_active_view);
    Rect_f32 prev_clip = draw_set_clip(app, region);
    
    Buffer_ID buffer = view_get_buffer(app, view_id, Access_Always);
    Face_ID face_id = get_face_id(app, buffer);
    Face_Metrics face_metrics = get_face_metrics(app, face_id);
    f32 line_height = face_metrics.line_height;
    f32 digit_advance = face_metrics.decimal_digit_advance;
    
    {
        // NOTE(allen): file bar.
        b64 showing_file_bar = false;
        if (view_get_setting(app, view_id, ViewSetting_ShowFileBar, &showing_file_bar) && showing_file_bar) {
            Rect_f32_Pair pair = layout_file_bar_on_top(region, line_height);
            draw_file_bar(app, view_id, buffer, face_id, pair.min);
            region = pair.max;
        }
    }
    
    Buffer_Scroll scroll = {};
    {
        // @Note(ema): Animate scrolling.
        scroll = view_get_buffer_scroll(app, view_id);
        Buffer_Point_Delta_Result delta = delta_apply(app, view_id, frame_info.animation_dt, scroll);
        if (!block_match_struct(&scroll.position, &delta.point)){
            block_copy_struct(&scroll.position, &delta.point);
            view_set_buffer_scroll(app, view_id, scroll, SetBufferScroll_NoCursorChange);
        }
        
        if (delta.still_animating)
            animate_in_n_milliseconds(app, 0);
    }
    
    {
        // NOTE(allen): query bars.
        Query_Bar *space[32];
        Query_Bar_Ptr_Array query_bars = {};
        query_bars.ptrs = space;
        
        if (get_active_query_bars(app, view_id, ArrayCount(space), &query_bars)) {
            for (i32 i = 0; i < query_bars.count; i += 1) {
                Rect_f32_Pair pair = layout_query_bar_on_top(region, line_height, 1);
                draw_query_bar(app, query_bars.ptrs[i], face_id, pair.min);
                region = pair.max;
            }
        }
    }
    
    // NOTE(allen): FPS hud.
    if (show_fps_hud) {
        Rect_f32_Pair pair = layout_fps_hud_on_bottom(region, line_height);
        draw_fps_hud(app, frame_info, face_id, pair.max);
        region = pair.min;
        animate_in_n_milliseconds(app, 1000);
    }
    
    // NOTE(allen): layout line numbers.
    Rect_f32 line_number_rect = {};
    b32 show_line_number_margins = def_get_config_b32(vars_save_string_lit("show_line_number_margins"));
    if (show_line_number_margins) {
        Rect_f32_Pair pair = layout_line_number_margin(app, buffer, region, digit_advance);
        line_number_rect = pair.min;
        region = pair.max;
    }
    
    // NOTE(allen): begin buffer render.
    Buffer_Point buffer_point = scroll.position;
    Text_Layout_ID text_layout_id = text_layout_create(app, buffer, region, buffer_point);
    
    // NOTE(allen): draw line numbers.
    if (show_line_number_margins)
        draw_line_number_margin(app, view_id, buffer, face_id, text_layout_id, line_number_rect);
    
    // NOTE(allen): draw the buffer.
    render_buffer(app, view_id, face_id, buffer, text_layout_id, region);
    
    text_layout_free(app, text_layout_id);
    draw_set_clip(app, prev_clip);
}

//
// Tick hook.
//

procedure void fleury_tick(Application_Links *app, Frame_Info frame_info) {
    linalloc_clear(&nicknema::global_frame_arena);
    // global_tooltip_count = 0;
    
    F4_Index_Tick(app);
    
    // NOTE(rjf): Default tick stuff from the 4th dimension:
    default_tick(app, frame_info);
}

//
// Begin buffer hook.
//

function void F4_DoFullLex_ASYNC_Inner(Async_Context *actx, Buffer_ID buffer_id) {
    Application_Links *app = actx->app;
    ProfileScope(app, "[F4] Async Lex");
    Scratch_Block scratch(app);
    
    String_Const_u8 contents = {};
    {
        ProfileBlock(app, "[F4] Async Lex Contents (before mutex)");
        acquire_global_frame_mutex(app);
        ProfileBlock(app, "[F4] Async Lex Contents (after mutex)");
        contents = push_whole_buffer(app, scratch, buffer_id);
        release_global_frame_mutex(app);
    }
    
    i32 limit_factor = 10000;
    
    Token_List list = {};
    b32 canceled = false;
    
    using namespace nicknema;
    Language *language = language_from_buffer(app, buffer_id);
    
    // NOTE(rjf): Fall back to C++ if we don't have a proper language.
    if(language == 0)
    {
        language = language_from_string(Str_U8("cpp"));
    }
    
    if(language != 0)
    {
        void *lexing_state = push_array_zero(scratch, u8, language->lex_state_size);
        language->lexer_initter(lexing_state, contents);
        for(;;)
        {
            ProfileBlock(app, "[F4] Async Lex Block");
            if(language->lexer(scratch, &list, lexing_state, limit_factor))
            {
                break;
            }
            if(async_check_canceled(actx))
            {
                canceled = true;
                break;
            }
        }
    }
    
    if(!canceled)
    {
        ProfileBlock(app, "[F4] Async Lex Save Results (before mutex)");
        acquire_global_frame_mutex(app);
        ProfileBlock(app, "[F4] Async Lex Save Results (after mutex)");
        Managed_Scope scope = buffer_get_managed_scope(app, buffer_id);
        if(scope != 0)
        {
            Base_Allocator *allocator = managed_scope_allocator(app, scope);
            Token_Array *tokens_ptr = scope_attachment(app, scope, attachment_tokens, Token_Array);
            base_free(allocator, tokens_ptr->tokens);
            Token_Array tokens = {};
            tokens.tokens = base_array(allocator, Token, list.total_count);
            tokens.count = list.total_count;
            tokens.max = list.total_count;
            token_fill_memory_from_list(tokens.tokens, &list);
            block_copy_struct(tokens_ptr, &tokens);
        }
        buffer_mark_as_modified(buffer_id);
        release_global_frame_mutex(app);
    }
}

function void F4_DoFullLex_ASYNC(Async_Context *actx, String_Const_u8 data) {
    if (data.size == sizeof(Buffer_ID)) {
        Buffer_ID buffer = *(Buffer_ID*)data.str;
        F4_DoFullLex_ASYNC_Inner(actx, buffer);
    }
}

function BUFFER_HOOK_SIG(F4_BeginBuffer)
{
    ProfileScope(app, "[Fleury] Begin Buffer");
    
    Scratch_Block scratch(app);
    b32 treat_as_code = false;
    String_Const_u8 file_name = push_buffer_file_name(app, scratch, buffer_id);
    String_Const_u8 buffer_name = push_buffer_base_name(app, scratch, buffer_id);
    
    // NOTE(rjf): Treat as code if the config tells us to.
    if(treat_as_code == false)
    {
        if(file_name.size > 0)
        {
            String_Const_u8 treat_as_code_string = def_get_config_string(scratch, vars_save_string_lit("treat_as_code"));
            String_Const_u8_Array extensions = parse_extension_line_to_extension_list(app, scratch, treat_as_code_string);
            String_Const_u8 ext = string_file_extension(file_name);
            for(i32 i = 0; i < extensions.count; ++i)
            {
                if(string_match(ext, extensions.strings[i]))
                {
                    treat_as_code = true;
                    break;
                }
            }
        }
    }
    
    // NOTE(rjf): Treat as code for *calc* and *peek* buffers.
    if(treat_as_code == false)
    {
        if(buffer_name.size > 0)
        {
            if(string_match(buffer_name, string_u8_litexpr("*calc*")))
            {
                treat_as_code = true;
            }
            else if(string_match(buffer_name, string_u8_litexpr("*peek*")))
            {
                treat_as_code = true;
            }
        }
    }
    
    // NOTE(rjf): Treat as code if we've identified the language of a file.
    if(treat_as_code == false)
    {
        using namespace nicknema;
        Language *language = language_from_buffer(app, buffer_id);
        if (language) {
            treat_as_code = true;
        }
    }
    
    String_ID file_map_id = vars_save_string_lit("keys_file");
    String_ID code_map_id = vars_save_string_lit("keys_code");
    
    Command_Map_ID map_id = (treat_as_code) ? (code_map_id) : (file_map_id);
    Managed_Scope scope = buffer_get_managed_scope(app, buffer_id);
    Command_Map_ID *map_id_ptr = scope_attachment(app, scope, buffer_map_id, Command_Map_ID);
    *map_id_ptr = map_id;
    
    Line_Ending_Kind setting = guess_line_ending_kind_from_buffer(app, buffer_id);
    Line_Ending_Kind *eol_setting = scope_attachment(app, scope, buffer_eol_setting, Line_Ending_Kind);
    *eol_setting = setting;
    
    // NOTE(allen): Decide buffer settings
    b32 wrap_lines = true;
    b32 use_lexer = false;
    if(treat_as_code)
    {
        wrap_lines = def_get_config_b32(vars_save_string_lit("enable_code_wrapping"));
        use_lexer = true;
    }
    
    if(string_match(buffer_name, string_u8_litexpr("*compilation*")))
    {
        wrap_lines = false;
    }
    
    if (use_lexer)
    {
        ProfileBlock(app, "begin buffer kick off lexer");
        Async_Task *lex_task_ptr = scope_attachment(app, scope, buffer_lex_task, Async_Task);
        *lex_task_ptr = async_task_no_dep(&global_async_system, F4_DoFullLex_ASYNC, make_data_struct(&buffer_id));
    }
    
    {
        b32 *wrap_lines_ptr = scope_attachment(app, scope, buffer_wrap_lines, b32);
        *wrap_lines_ptr = wrap_lines;
    }
    
    if (use_lexer)
    {
        buffer_set_layout(app, buffer_id, layout_virt_indent_index_generic);
    }
    else
    {
        if (treat_as_code)
        {
            buffer_set_layout(app, buffer_id, layout_virt_indent_literal_generic);
        }
        else{
            buffer_set_layout(app, buffer_id, layout_generic);
        }
    }
    
    
    // no meaning for return
    return(0);
}

#endif // FCODER_NICKNEMA_HOOKS_CPP
