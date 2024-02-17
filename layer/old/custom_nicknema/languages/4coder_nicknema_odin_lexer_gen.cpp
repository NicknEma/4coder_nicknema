/*
4coder_fleury_jai_lexer_gen.cpp - Model definition for an Odin lexer.
*/

// TOP

#define LANG_NAME_LOWER odin
#define LANG_NAME_CAMEL Odin

#include "lexer_generator/4coder_lex_gen_main.cpp"

internal void
build_language_model(void) {
    // @Note(ema): 'sm' means State Machine. 'smh' for State Machine helper.
    // @Note(ema): This fills out a buffer to represent all characters above the ASCII range.
    u8 utf8[129];
    smh_utf8_fill(utf8);
    
    smh_set_base_character_names();
    
    // Odin-specific Names.
    // @Note(ema): I still don't understand what's the point of this.
    sm_char_name('!', "Not");
    sm_char_name('&', "And");
    sm_char_name('|', "Or");
    sm_char_name('%', "Mod");
    sm_char_name('~', "Xor");
    sm_char_name('?', "Ternary");
    sm_char_name('/', "Div");
    
    //
    // Direct Token Kinds.
    //
    
    smh_typical_tokens(); // EOF, Whitespace, LexError
    
    sm_select_base_kind(TokenBaseKind_Comment);
    sm_direct_token_kind("BlockComment");
    sm_direct_token_kind("LineComment");
    
    // @Note(ema): AFAIK, Odin doesn't have identifier backslashes.
    // sm_select_base_kind(TokenBaseKind_Whitespace);
    // sm_direct_token_kind("Backslash");
    
    // @Note(ema): Why do we need to distinguish between all the variations?
    // Just because someone might want to color them differently in the editor?
    sm_select_base_kind(TokenBaseKind_LiteralInteger);
    sm_direct_token_kind("LiteralInteger");
    sm_direct_token_kind("LiteralIntegerBin");
    sm_direct_token_kind("LiteralIntegerOct");
    sm_direct_token_kind("LiteralIntegerHex");
    
    sm_select_base_kind(TokenBaseKind_LiteralFloat);
    sm_direct_token_kind("LiteralFloat32");
    sm_direct_token_kind("LiteralFloat64");
    sm_direct_token_kind("LiteralComplex");
    
    sm_select_base_kind(TokenBaseKind_LiteralString);
    sm_direct_token_kind("LiteralString");
    sm_direct_token_kind("LiteralStringRaw");
    sm_direct_token_kind("LiteralCharacter");
    sm_direct_token_kind("PackageName");
    
    sm_select_base_kind(TokenBaseKind_Keyword);
    sm_direct_token_kind("KeywordGeneric");
    
    //
    // Odin Operators.
    //
    
    Operator_Set *main_ops = sm_begin_op_set();
    
    sm_select_base_kind(TokenBaseKind_ScopeOpen);
    sm_op("{");
    sm_select_base_kind(TokenBaseKind_ScopeClose);
    sm_op("}");
    sm_select_base_kind(TokenBaseKind_ParentheticalOpen);
    sm_op("(");
    sm_op("[");
    sm_select_base_kind(TokenBaseKind_ParentheticalClose);
    sm_op(")");
    sm_op("]");
    sm_select_base_kind(TokenBaseKind_StatementClose);
    sm_op(";");
    
    sm_select_base_kind(TokenBaseKind_Operator);
    
    // Arithmetic operators:
    sm_op("+"); // Addition
    sm_op("-"); // Subtraction, negation
    sm_op("*"); // Multiplication
    sm_op("/"); // Division
    sm_op("%"); // Modulo (truncated)
    sm_op("%%"); // Remainder (floored)
    
    sm_op("|"); // Bitwise or
    sm_op("~"); // Bitwise xor
    sm_op("&"); // Bitwise and
    sm_op("&~"); // Bitwise and-not
    
    sm_char_name('<', "Left");
    sm_char_name('>', "Right");
    sm_op("<<"); // Shift left
    sm_op(">>"); // Shift right
    
    // Comparison operators:
    sm_char_name('<', "Less");
    sm_char_name('>', "Grtr");
    sm_op("<");
    sm_op("<=");
    sm_op(">");
    sm_op(">=");
    sm_op("=="); // Equality
    sm_op("!="); // Inequality
    
    // Logical operators:
    sm_op("&&"); // Short-circuiting logical and
    sm_op("||"); // Short-circuiting logical or
    sm_op("!"); // Not
    
    // Address operators:
    // sm_op("&"); // Address-of operator. @Note(ema): Already declared as bitwise and
    sm_op("^"); // Dereference operator
    sm_op("."); // Namespace/Struct access operator
    
    // Ternary operators:
    sm_op("?");
    
    // Assignment operators:
    // @Note(ema): These aren't listed on the website, I assume that they exist...
    sm_op("=");
    sm_op("+=");
    sm_op("-=");
    sm_op("*=");
    sm_op("/=");
    sm_op("%=");
    
    // Other operators:
    sm_op(":");
    sm_op("::");
    sm_op(":=");
    sm_op("->");
    sm_op("..");
    sm_op("..="); // Inclusive range
    sm_op("..<"); // Half-open range
    sm_op("---"); // Procedure Prototype
    
    sm_char_name('<', "Left");
    sm_char_name('>', "Right");
    sm_op("<<=");
    sm_op(">>=");
    
    sm_op("#");
    sm_op("@");
    sm_op("$");
    
    sm_select_base_kind(TokenBaseKind_StatementClose);
    sm_op(",");
    
    // @Todo(ema): Builtin procedures? Types?
    
    //
    // Odin Keywords.
    //
    
    Keyword_Set *main_keys = sm_begin_key_set("main_keys");
    
    sm_select_base_kind(TokenBaseKind_Keyword);
    sm_key("Asm");
    sm_key("AutoCast", "auto_cast");
    sm_key("BitSet", "bit_set");
    sm_key("Break");
    sm_key("Case");
    sm_key("Cast");
    sm_key("Context");
    sm_key("Continue");
    sm_key("Defer");
    sm_key("Distinct");
    sm_key("Do");
    sm_key("Dynamic");
    sm_key("Else");
    sm_key("Enum");
    sm_key("Fallthrough");
    sm_key("For");
    sm_key("Foreign");
    sm_key("If");
    sm_key("Import");
    sm_key("In");
    sm_key("Map");
    sm_key("NotIn", "not_in");
    sm_key("OrElse", "or_else");
    sm_key("OrReturn", "or_return");
    sm_key("Package");
    sm_key("Proc");
    sm_key("Return");
    sm_key("Struct");
    sm_key("Switch");
    sm_key("Transmute");
    sm_key("Typeid");
    sm_key("union");
    sm_key("Using");
    sm_key("When");
    sm_key("Where");
    
    sm_select_base_kind(TokenBaseKind_LiteralInteger);
    sm_key("LiteralTrue", "true");
    sm_key("LiteralFalse", "false");
    
    sm_select_base_kind(TokenBaseKind_Identifier);
    sm_key_fallback("Identifier");
    
    //
    // Odin Preprocessor Directives.
    //
    
    Keyword_Set *directive_set = sm_begin_key_set("directives");
    
    sm_select_base_kind(TokenBaseKind_Identifier);
    sm_key("PPAssert", "assert");
    sm_key("PPPanic", "panic");
    sm_key("PPBoundsCheck", "bounds_check");
    sm_key("PPNoBoundsCheck", "no_bounds_check");
    sm_key("PPAlign", "align");
    sm_key("PPPacked", "packed");
    sm_key("PPRawUnion", "raw_union");
    sm_key("PPNoNil", "no_nil");
    sm_key("PPSoa", "soa");
    sm_key("PPSimd", "simd");
    sm_key("PPConfig", "config");
    sm_key("PPPartial", "partial");
    sm_key("PPNoAlias", "no_alias");
    sm_key("PPAnyInt", "any_int");
    sm_key("PPCallerLocation", "caller_location");
    sm_key("PPLocation", "location");
    sm_key("PPProcedure", "procedure");
    sm_key("PPFile", "file");
    sm_key("PPLine", "line");
    sm_key("PPCVararg", "c_vararg");
    sm_key("PPByPtr", "by_ptr");
    sm_key("PPOptionalOk", "optional_ok");
    sm_key("PPType", "type");
    sm_key("PPDefined", "defined");
    sm_key("PPLoad", "load");
    sm_key("PPLoadOr", "load_or");
    sm_key("PPLoadHash", "load_hash");
    
    sm_select_base_kind(TokenBaseKind_LexError);
    sm_key_fallback("PPUnknown");
    
    //
    // Odin Preprocess Keywords
    //
    
    // @Note(ema): For things like C++'s '#if defined'. I don't think odin has any.
    /*
    Keyword_Set *pp_keys = sm_begin_key_set("pp_keys");
    
    sm_select_base_kind(TokenBaseKind_Keyword);
    sm_key("PPDefined", "defined");
    */
    
    //
    // Odin Attributes.
    //
    
    Keyword_Set *attribute_set = sm_begin_key_set("attributes");
    
    sm_select_base_kind(TokenBaseKind_Identifier);
    sm_key("AtPrivate", "private");
    sm_key("AtRequire", "require");
    sm_key("AtLinkName", "link_name");
    sm_key("AtLinkPrefix", "link_prefix");
    sm_key("AtExport", "export");
    sm_key("AtLinkage", "linkage");
    sm_key("AtDefaultCallingConvention", "default_calling_convention");
    sm_key("AtLinkSection", "link_section");
    sm_key("AtExtraLinkerFlags", "extra_linker_flags");
    sm_key("AtDeferredIn", "deferred_in");
    sm_key("AtDeferredOut", "deferred_out");
    sm_key("AtDeferredInOut", "deferred_in_out");
    sm_key("AtDeferredNone", "deferred_none");
    sm_key("AtDeprecated", "deprecated");
    sm_key("AtRequireResults", "require_results");
    sm_key("AtWarning", "warning");
    sm_key("AtDisabled", "disabled");
    sm_key("AtInit", "init");
    sm_key("AtCold", "cold");
    sm_key("AtOptimizationMode", "optimization_mode");
    sm_key("AtStatic", "static");
    sm_key("AtThreadLocal", "thread_local");
    sm_key("AtBuiltin", "builtin");
    sm_key("AtObjcName", "objc_name");
    sm_key("AtObjcType", "objc_type");
    sm_key("AtObjcIsClassMethod", "objc_is_class_method");
    sm_key("AtRequireTargetFeature", "require_target_feature");
    sm_key("AtEnableTargetFeature", "enable_target_feature");
    
    //
    // State Machine.
    //
    
    State *root = sm_begin_state_machine();
    
    Flag *is_hex   = sm_add_flag(FlagResetRule_AutoZero);
    Flag *is_oct   = sm_add_flag(FlagResetRule_AutoZero);
    Flag *is_bin   = sm_add_flag(FlagResetRule_AutoZero);
    Flag *is_char  = sm_add_flag(FlagResetRule_AutoZero);
    // Flag *is_wide  = sm_add_flag(FlagResetRule_AutoZero);
    // Flag *is_utf8  = sm_add_flag(FlagResetRule_AutoZero);
    // Flag *is_utf16 = sm_add_flag(FlagResetRule_AutoZero);
    // Flag *is_utf32 = sm_add_flag(FlagResetRule_AutoZero);
    
#define AddState(N) State *N = sm_add_state(#N)
    
    AddState(identifier);
    AddState(whitespace);
    
    AddState(operator_or_fnumber_dot);   // For when we don't know if it's a floating point number or a namespace/struct access
    AddState(operator_or_comment_slash); // For when we don't know if it's a division or the start of a comment
    
    AddState(number);
    AddState(pre_number); // For numbers that start with 0, since they could be 0. 0x 0o or 0b
    
    AddState(fnumber_decimal);
    AddState(fnumber_exponent);
    AddState(fnumber_exponent_sign);
    AddState(fnumber_exponent_digits);
    
    AddState(number_hex_first);
    AddState(number_hex);
    AddState(number_oct_first);
    AddState(number_oct);
    AddState(number_bin_first);
    AddState(number_bin);
    
    AddState(character);
    AddState(string);
    AddState(string_esc);
    AddState(string_esc_oct2);
    AddState(string_esc_oct1);
    AddState(string_esc_hex);
    AddState(string_esc_universal_8);
    AddState(string_esc_universal_7);
    AddState(string_esc_universal_6);
    AddState(string_esc_universal_5);
    AddState(string_esc_universal_4);
    AddState(string_esc_universal_3);
    AddState(string_esc_universal_2);
    AddState(string_esc_universal_1);
    
    AddState(raw_string);
    
    AddState(comment_block);
    AddState(comment_block_try_close);
    AddState(comment_line);
    AddState(comment_line_backslashing);
    
    AddState(directive);
    AddState(attribute);
    AddState(attribute_body);
    
#undef  AddState
    
    Operator_Set *main_ops_without_dot_or_slash = smo_copy_op_set(main_ops);
    smo_remove_ops_with_prefix(main_ops_without_dot_or_slash, ".");
    smo_remove_ops_with_prefix(main_ops_without_dot_or_slash, "/");
    
    Operator_Set *main_ops_with_dot = smo_copy_op_set(main_ops);
    smo_remove_ops_without_prefix(main_ops_with_dot, ".");
    smo_ops_string_skip(main_ops_with_dot, 1);
    
    ////
    
    sm_select_state(root);
    
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("EOF");
        sm_case_eof(emit);
    }
    
    sm_case("abcdefghijklmnopqrstvwxyz"
            "ABCDEFGHIJKLMNOPQRSTVWXYZ"
            "_",
            identifier);
    sm_case(utf8, identifier);
    
    sm_case(" \r\t\f\v\n", whitespace);
    
    sm_case(".", operator_or_fnumber_dot);
    sm_case("/", operator_or_comment_slash);
    
    // @Note(ema): This is for differentiating .</ inside include paths vs operators.
#if 0
    {
        Character_Set *char_set = smo_new_char_set();
        smo_char_set_union_ops_firsts(char_set, main_ops_without_dot_or_slash);
        smo_char_set_remove(char_set, ".</");
        char *char_set_array = smo_char_set_get_array(char_set);
        State *operator_state = smo_op_set_lexer_root(main_ops_without_dot_or_slash, root, "LexError");
        sm_case_peek(char_set_array, operator_state);
        sm_case_peek_flagged(is_include_body, false, "<", operator_state);
    }
#endif
    
    sm_case("123456789", number);
    sm_case("0",     pre_number);
    
    sm_case("\'", character);
    sm_case("\"", string);
    sm_case("`",  raw_string);
    sm_case("#",  directive);
    sm_case("@",  attribute);
    
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_fallback(emit);
    }
    
    ////
    
    sm_select_state(identifier);
    sm_case("abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "_$"
            "0123456789",
            identifier);
    sm_case(utf8, identifier);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_keys(main_keys);
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(whitespace);
    sm_case(" \t\r\f\v\n", whitespace);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Whitespace");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(operator_or_comment_slash);
    sm_case("*", comment_block);
    sm_case("/", comment_line);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("DivEq");
        sm_case("=", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Div");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(operator_or_fnumber_dot);
    sm_case("0123456789", fnumber_decimal);
    {
        Character_Set *char_set = smo_new_char_set();
        smo_char_set_union_ops_firsts(char_set, main_ops_with_dot);
        char *char_set_array = smo_char_set_get_array(char_set);
        State *operator_state = smo_op_set_lexer_root(main_ops_with_dot, root, "LexError");
        sm_case_peek(char_set_array, operator_state);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Dot");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(number);
    sm_case("0123456789", number);
    sm_case(".", fnumber_decimal);
    // sm_case("i", znumber);
    sm_case("Ee", fnumber_exponent);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralInteger");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(pre_number);
    sm_case(".", fnumber_decimal);
    sm_case("Ee", fnumber_exponent);
    sm_case("Xx", number_hex_first);
    sm_case("Oo", number_oct_first);
    sm_case("Bb", number_bin_first);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralInteger");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(fnumber_decimal);
    sm_case("0123456789", fnumber_decimal);
    sm_case("Ee", fnumber_exponent);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat32");
        sm_case("Ff", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_case("Ll", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(fnumber_exponent);
    sm_case("+-", fnumber_exponent_sign);
    sm_case("0123456789", fnumber_exponent_digits);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat32");
        sm_case("Ff", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_case("Ll", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(fnumber_exponent_sign);
    sm_case("0123456789", fnumber_exponent_digits);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat32");
        sm_case("Ff", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_case("Ll", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(fnumber_exponent_digits);
    sm_case("0123456789", fnumber_exponent_digits);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat32");
        sm_case("Ff", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_case("Ll", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(number_hex_first);
    sm_set_flag(is_hex, true);
    sm_case("0123456789abcdefABCDEF_", number_hex);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(number_hex);
    sm_case("0123456789abcdefABCDEF_", number_hex);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralIntegerHex");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(number_oct_first);
    sm_set_flag(is_oct, true);
    sm_case("01234567_", number_oct);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(number_oct);
    sm_case("01234567_", number_oct);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralIntegerOct");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(number_bin_first);
    sm_set_flag(is_bin, true);
    sm_case("01_", number_bin);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(number_bin);
    sm_case("01_", number_bin);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralIntegerBin");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(character);
    sm_set_flag(is_char, true);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralString");
        sm_case_flagged(is_char, false, "\"", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralCharacter");
        sm_case_flagged(is_char, true, "\'", emit);
    }
    sm_case("\\", string_esc);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_case_peek("\n", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_case_eof_peek(emit);
    }
    sm_case_flagged(is_char, true, "\"", string);
    sm_case_flagged(is_char, false, "\'", string);
    sm_fallback(string);
    
    ////
    
    sm_select_state(string_esc);
    sm_case("\n'\"?\\abfnrtv", string);
    sm_case("01234567", string_esc_oct2);
    sm_case("x", string_esc_hex);
    sm_case("u", string_esc_universal_4);
    sm_case("U", string_esc_universal_8);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_case_peek("\n", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_case_eof_peek(emit);
    }
    sm_fallback(string);
    
    ////
    
    sm_select_state(string_esc_oct2);
    sm_case("01234567", string_esc_oct1);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_oct1);
    sm_case("01234567", string);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_hex);
    sm_case("0123456789abcdefABCDEF", string_esc_hex);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_8);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_7);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_7);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_6);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_6);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_5);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_5);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_4);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_4);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_3);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_3);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_2);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_2);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_1);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_1);
    sm_case("0123456789abcdefABCDEF", string);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(raw_string);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralString");
        sm_case("`", emit);
    }
    sm_fallback(raw_string);
    
    ////
    
    sm_select_state(comment_block);
    sm_case("*", comment_block_try_close);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("BlockComment");
        sm_case_eof_peek(emit);
    }
    sm_fallback(comment_block);
    
    ////
    
    sm_select_state(comment_block_try_close);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("BlockComment");
        sm_case("/", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("BlockComment");
        sm_case_eof_peek(emit);
    }
    sm_case("*", comment_block_try_close);
    sm_fallback(comment_block);
    
    ////
    
    sm_select_state(comment_line);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LineComment");
        sm_case_peek("\n", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LineComment");
        sm_case_eof_peek(emit);
    }
    sm_case("\\", comment_line_backslashing);
    sm_fallback(comment_line);
    
    sm_select_state(comment_line_backslashing);
    sm_case("\r", comment_line_backslashing);
    sm_fallback(comment_line);
    
    ////
    
    sm_select_state(directive);
    sm_case("abcdefghijklmnopqrstuvwyz"
            "ABCDEFGHIJKLMNOPQRSTUVWYZ"
            "_"
            "0123456789",
            directive);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_keys(directive_set);
        sm_fallback(emit);
    }
    
    ////
    
    sm_select_state(attribute);
    sm_case("(", attribute_body);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_fallback(emit);
    }
    
    ////
    
    sm_select_state(attribute_body);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_keys(attribute_set);
        sm_case(")", emit);
    }
    sm_fallback(attribute_body);
}

// BOTTOM

