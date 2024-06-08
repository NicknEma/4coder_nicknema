// TOP

#define LANG_NAME_LOWER js
#define LANG_NAME_CAMEL JS

#include "lexer_generator/4coder_lex_gen_main.cpp"

internal void build_language_model(void) {
    // 'sm' means State Machine. 'smh' means State Machine helper.
    
#define Associate_Name_To_Character(c, s) sm_char_name(c, s)
	
	// Associate names to characters. Set the language agnostic ones with smh_set_base_character_names
	// and then overwrite odin-specific ones.
    smh_set_base_character_names();
    Associate_Name_To_Character('!', "Not");
    Associate_Name_To_Character('&', "And");
    Associate_Name_To_Character('|', "Or");
    Associate_Name_To_Character('%', "Mod");
    Associate_Name_To_Character('~', "Xor");
    Associate_Name_To_Character('?', "Ternary");
    Associate_Name_To_Character('/', "Div");
    
	// Now we define the tokens that will be emitted by the lexer.
	// Each token has a lexeme and a kind. Some also have a subkind.
	// We define a token by SELECTING its base kind (choosing one
	// from those already defined by 4coder) and then ADDING a possible
	// lexeme for it, and a subkind (a "specialization", if you will).
	
    //~ Direct Token Kinds (comments, literals, keywords) Declarations.
	
	// "Direct Tokens" are the ones without a subkind. (I think? @Todo )
    
    smh_typical_tokens(); // EOF, Whitespace, LexError
    
#define Add_Direct_Token(s) sm_direct_token_kind(s)
	
    sm_select_base_kind(TokenBaseKind_Comment);
    Add_Direct_Token("BlockComment");
    Add_Direct_Token("LineComment");
    
	sm_select_base_kind(TokenBaseKind_Whitespace);
	Add_Direct_Token("Backslash");
    
    // sm_select_base_kind(TokenBaseKind_LiteralInteger);
    
    sm_select_base_kind(TokenBaseKind_LiteralFloat);
    Add_Direct_Token("LiteralNumber");
    
    sm_select_base_kind(TokenBaseKind_LiteralString);
    Add_Direct_Token("LiteralString");
    // Add_Direct_Token("LiteralCharacter");
    
    sm_select_base_kind(TokenBaseKind_Keyword);
    Add_Direct_Token("KeywordGeneric"); // @Note(ema): This is never used. What's the point?
    
#undef Add_Direct_Token
	
    //~ Odin Operators.
    
    Operator_Set *main_ops = sm_begin_op_set();
    
	// What we're saying is: select a base kind, then add a token with the
	// supplied string as a lexeme, and the associated name as a subkind?
	
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
    sm_op(",");
	// sm_op("\n");
	// @Todo(ema): Add optional semicolons. Will sm_op("\n") work?
	
    sm_select_base_kind(TokenBaseKind_Operator);
    {
		// Arithmetic operators:
		sm_op("+");  // Addition
		sm_op("-");  // Subtraction, negation
		sm_op("*");  // Multiplication
		sm_op("/");  // Division
		sm_op("%");  // Modulo (truncated)
		
		sm_op("|");  // Bitwise or
		sm_op("~");  // Bitwise xor
		sm_op("&");  // Bitwise and
		sm_op("&~"); // Bitwise and-not
		
		Associate_Name_To_Character('<', "Left");
		Associate_Name_To_Character('>', "Right");
		sm_op("<<"); // Shift left
		sm_op(">>"); // Shift right
		
		// Comparison operators:
		Associate_Name_To_Character('<', "Less");
		Associate_Name_To_Character('>', "Grtr");
		sm_op("<");
		sm_op("<=");
		sm_op(">");
		sm_op(">=");
		sm_op("==");  // Equality
		sm_op("!=");  // Inequality
		
		// Logical operators:
		sm_op("&&");  // Short-circuiting logical and
		sm_op("||");  // Short-circuiting logical or
		sm_op("!");   // Logical not
		
		// Address operators:
		sm_op("^");   // Dereference operator
		sm_op(".");   // Namespace/Struct access operator
		
		// Ternary operators:
		sm_op("?");
		sm_op(":");   // Ternary, declaration
		
		// Assignment operators:
		sm_op("=");
		sm_op("+=");
		sm_op("-=");
		sm_op("*=");
		sm_op("/=");
		sm_op("%=");
		
		Associate_Name_To_Character('<', "Left");
		Associate_Name_To_Character('>', "Right");
		
		// Other operators:
		
		// sm_op("->");  // Member function shorthand
		// sm_op("..");  // @Cleanup: Does this exist?
		// sm_op("..="); // Inclusive range
		// sm_op("..<"); // Half-open range
		// sm_op("---"); // Procedure Prototype/uninitialized variable
		
		// sm_op("#"); // Directive start
		// sm_op("@"); // Attribute start
		// sm_op("$"); // Compile-time parameter start
    }
	
    // @Todo(ema): Builtin procedures?
    
    //~ Odin Keywords.
    
    Keyword_Set *main_keywords = sm_begin_key_set("main_keys");
    
    sm_select_base_kind(TokenBaseKind_Keyword);
    {
		sm_key("Await");
		sm_key("Break");
		sm_key("Case");
		sm_key("Catch");
		sm_key("Class");
		sm_key("Const");
		sm_key("Continue");
		sm_key("Debugger");
		sm_key("Default");
		sm_key("Delete");
		sm_key("Do");
		sm_key("Else");
		sm_key("Export");
		sm_key("Extends");
		sm_key("Finally");
		sm_key("For");
		sm_key("Function");
		sm_key("If");
		sm_key("Import");
		sm_key("In");
		sm_key("Instanceof");
		sm_key("Let");
		sm_key("New");
		sm_key("Return");
		sm_key("Super");
		sm_key("Switch");
		sm_key("This");
		sm_key("Throw");
		sm_key("Try");
		sm_key("Typeof");
		sm_key("Var");
		sm_key("While");
		sm_key("With");
		sm_key("Yield");
		sm_key("Static");
		
		// For future use
		sm_key("Enum");
		sm_key("Implements");
		sm_key("Interface");
		sm_key("Package");
		sm_key("Private");
		sm_key("Protected");
		sm_key("Public");
		
		// Types
		sm_key("Null");
		sm_key("Void");
		sm_key("Undefined");
    }
	
    sm_select_base_kind(TokenBaseKind_LiteralInteger);
    {
		sm_key("LiteralTrue",  "true");
		sm_key("LiteralFalse", "false");
    }
	
    sm_select_base_kind(TokenBaseKind_Identifier);
    sm_key_fallback("Identifier");
    
    //~ State Definitions.
    
    State *root = sm_begin_state_machine();
    
    Flag *is_hex  = sm_add_flag(FlagResetRule_AutoZero);
    Flag *is_oct  = sm_add_flag(FlagResetRule_AutoZero);
    Flag *is_bin  = sm_add_flag(FlagResetRule_AutoZero);
    Flag *is_char = sm_add_flag(FlagResetRule_AutoZero);
    
#define AddState(N) State *N = sm_add_state(#N)
    
    AddState(identifier);
    AddState(whitespace);
    
    AddState(operator_or_fnumber_dot);   // @Note(ema): For when we don't know if it's a floating point number or a namespace/struct access
    AddState(operator_or_comment_slash); // @Note(ema): For when we don't know if it's a division or the start of a comment
    
    AddState(number);
    AddState(pre_number); // @Note(ema): For numbers that start with 0, since they could be 0. 0x 0o or 0b
    
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
    
    AddState(template_string);
    
    AddState(comment_block);
    AddState(comment_block_try_close);
    AddState(comment_line);
    AddState(comment_line_backslashing);
    
#undef  AddState
    
    Operator_Set *main_ops_without_dot_or_slash = smo_copy_op_set(main_ops);
    smo_remove_ops_with_prefix(main_ops_without_dot_or_slash, ".");
    smo_remove_ops_with_prefix(main_ops_without_dot_or_slash, "/");
    
    Operator_Set *main_ops_with_dot = smo_copy_op_set(main_ops);
    smo_remove_ops_without_prefix(main_ops_with_dot, ".");
    smo_ops_string_skip(main_ops_with_dot, 1);
    
#define Create_Emit_Rule() sm_emit_rule()
	
	// This fills out a buffer to represent all characters above the ASCII range.
	u8 utf8[129];
	smh_utf8_fill(utf8);
	
	//~ Root state
	
    sm_select_state(root);
    {
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("EOF");
			sm_case_eof(emit); // At the end of file, emit "direct" token EOF.
		}
		
		sm_case("abcdefghijklmnopqrstuvwxyz"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"_",           identifier); // Go to state identifier
		sm_case(utf8,          identifier); // Go to state identifier
		
		sm_case(" \r\t\f\v\n", whitespace); // Go to state whitespace
		
		sm_case(".", operator_or_fnumber_dot);   // It could be an access operator or the start of a float.
		sm_case("/", operator_or_comment_slash); // It could be a division operator or the start of a comment.
		
#if 1
		{
			// This is the code that emits operators. It's what makes automatic
			// indentation work, since braces are what describes indentation (and
			// braces are operators).
			Character_Set *char_set = smo_new_char_set();
#if 0
			smo_char_set_union_ops_firsts(char_set, main_ops_without_dot_or_slash);
			smo_char_set_remove(char_set, ".</");
#else
			smo_char_set_union_ops_firsts(char_set, main_ops);
#endif
			char *char_set_array = smo_char_set_get_array(char_set);
			State *operator_state = smo_op_set_lexer_root(main_ops, root, "LexError");
			sm_case_peek(char_set_array, operator_state);
		}
#endif
		
		sm_case("123456789", number); // See a number, go to state number
		sm_case("0",     pre_number); // Could be a hex, oct or bin literal, or a regular number
		
		sm_case("\'",    string);          // Go to state string
		sm_case("\"",    string);          // Go to state string
		sm_case("`",     template_string); // Go to state template_string
		
		// For anything else, emit a lexer error.
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LexError");
			sm_fallback(emit); // For anything else, emit a LexError
		}
    }
	
	//~ Identifiers and keywords
	
    sm_select_state(identifier); // See an identifier:
	{
		sm_case("abcdefghijklmnopqrstuvwxyz"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"_$"
				"0123456789",
				identifier);       // Stay in state identifier
		sm_case(utf8, identifier); // Stay in state identifier
		{
			// If it can't continue the identifier...
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_keys(main_keywords); // Select the token from the keyword set (which also contains the identifier case)
			sm_fallback_peek(emit); // ...then emit the token, without consuming the current character.
		}
    }
    
	//~ Whitespace
	
    sm_select_state(whitespace);
    {
		sm_case(" \t\r\f\v\n", whitespace);
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("Whitespace");
			sm_fallback_peek(emit);
		}
    }
	
	//~ Indecision states
	
    sm_select_state(operator_or_comment_slash);
    {
		sm_case("*", comment_block); // Go to state comment_block
		sm_case("/", comment_line);  // Go to state comment_line
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("DivEq");
			sm_case("=", emit);      // Emit token DivEq
		}
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("Div");
			sm_fallback_peek(emit);  // Emit token Div
		}
    }
    sm_select_state(operator_or_fnumber_dot);   // See '.'
    {
		sm_case("0123456789", fnumber_decimal); // Go to state fnumber_decimal
		{
			Character_Set *char_set = smo_new_char_set();
			smo_char_set_union_ops_firsts(char_set, main_ops_with_dot);
			char *char_set_array = smo_char_set_get_array(char_set);
			State *operator_state = smo_op_set_lexer_root(main_ops_with_dot, root, "LexError");
			sm_case_peek(char_set_array, operator_state); // If followed by another operator, emit a LexError and go back to root?
		}
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("Dot");
			sm_fallback_peek(emit); // Emit token Dot (the operator)
		}
    }
	
	//~ Numbers
	
    sm_select_state(number); // See a number except '0'
    {
		sm_case("0123456789", number); // Stay in state number
		sm_case(".", fnumber_decimal); // Go to state fnumber_decimal
		// sm_case("i", znumber);
		sm_case("Ee", fnumber_exponent); // Go to state fnumber_exponent
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LiteralNumber");
			sm_fallback_peek(emit); // Emit a LiteralNumber token
		}
    }
    sm_select_state(pre_number); // See a '0'
    {
		sm_case(".",  fnumber_decimal);
		sm_case("Ee", fnumber_exponent);
		sm_case("Xx", number_hex_first);
		sm_case("Oo", number_oct_first);
		sm_case("Bb", number_bin_first);
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LiteralNumber");
			sm_fallback_peek(emit);
		}
    }
	
	//~ Floating point numbers
	
    sm_select_state(fnumber_decimal);
    {
		sm_case("0123456789", fnumber_decimal);
		sm_case("Ee", fnumber_exponent);
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LiteralNumber");
			sm_fallback_peek(emit);
		}
    }
    sm_select_state(fnumber_exponent);
    {
		sm_case("+-", fnumber_exponent_sign);
		sm_case("0123456789", fnumber_exponent_digits);
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LiteralNumber");
			sm_fallback_peek(emit);
		}
    }
    sm_select_state(fnumber_exponent_sign);
    {
		sm_case("0123456789", fnumber_exponent_digits);
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LiteralNumber");
			sm_fallback_peek(emit);
		}
    }
    sm_select_state(fnumber_exponent_digits);
    {
		sm_case("0123456789", fnumber_exponent_digits);
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LiteralNumber");
			sm_fallback_peek(emit);
		}
    }
	
	//~ Hex numbers
	
    sm_select_state(number_hex_first); // First character of hex literal after 0x:
    {
		sm_set_flag(is_hex, true);
		sm_case("0123456789abcdefABCDEF", number_hex); // Go to state number_hex
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LexError");
			sm_fallback_peek(emit); // If not actually a hex number, emit a LexError
		}
    }
    sm_select_state(number_hex);
    {
		sm_case("0123456789abcdefABCDEF", number_hex);
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LiteralNumber");
			sm_fallback_peek(emit);
		}
    }
	
	//~ Oct numbers
	
    sm_select_state(number_oct_first);
    {
		sm_set_flag(is_oct, true);
		sm_case("01234567", number_oct);
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LexError");
			sm_fallback_peek(emit);
		}
    }
    sm_select_state(number_oct);
    {
		sm_case("01234567", number_oct);
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LiteralNumber");
			sm_fallback_peek(emit);
		}
    }
	
	//~ Bin numbers
	
    sm_select_state(number_bin_first);
    {
		sm_set_flag(is_bin, true);
		sm_case("01", number_bin);
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LexError");
			sm_fallback_peek(emit);
		}
    }
    sm_select_state(number_bin);
	{
		sm_case("01", number_bin);
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LiteralNumber");
			sm_fallback_peek(emit);
		}
    }
	
	//~ Strings
	
    sm_select_state(character); // See a character literal:
    {
		sm_set_flag(is_char, true);
		sm_fallback_peek(string);
    }
    sm_select_state(string); // See a string literal:
    {
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LiteralString");
			sm_case_flagged(is_char, false, "\"'", emit); // If you see a " and you aren't in a character, emit a LiteralString
		}
		sm_case("\\", string_esc); // Go to string_esc state, next character is escaped
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LexError");
			sm_case_peek("\n", emit); // If the line terminates, it's a LexError
		}
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LexError");
			sm_case_eof_peek(emit); // If the file terminates, it's a LexError
		}
		sm_case_flagged(is_char, true, "\"", string);  // The " character doesn't terminate the "string" if we're flagged as characters.
		sm_case_flagged(is_char, false, "\'", string); // The ' character doesn't terminate the "string" if we're not flagged as characters.
		sm_fallback(string); // Stay in state string
    }
    sm_select_state(string_esc);
    {
		{
			sm_case("\n'\"?\\abfnrtv", string);
			sm_case("01234567", string_esc_oct2);
			sm_case("x", string_esc_hex);
			sm_case("u", string_esc_universal_4);
			sm_case("U", string_esc_universal_8);
			{
				Emit_Rule *emit = Create_Emit_Rule();
				sm_emit_handler_direct("LexError");
				sm_case_peek("\n", emit);
			}
			{
				Emit_Rule *emit = Create_Emit_Rule();
				sm_emit_handler_direct("LexError");
				sm_case_eof_peek(emit);
			}
			sm_fallback(string);
		}
	}
    sm_select_state(template_string); // See a template string:
    {
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LiteralString");
			sm_case("`", emit); // See a backtick, emit a LiteralString
		}
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LexError");
			sm_case_eof_peek(emit); // If the file terminates, it's a LexError
		}
		sm_fallback(template_string); // Stay in state raw_string
    }
	
    sm_select_state(string_esc_oct2);
    sm_case("01234567", string_esc_oct1);
    sm_fallback_peek(string);
    
    sm_select_state(string_esc_oct1);
    sm_case("01234567", string);
    sm_fallback_peek(string);
    
    sm_select_state(string_esc_hex);
    sm_case("0123456789abcdefABCDEF", string_esc_hex);
    sm_fallback_peek(string);
    
    sm_select_state(string_esc_universal_8);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_7);
    sm_fallback_peek(string);
    
    sm_select_state(string_esc_universal_7);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_6);
    sm_fallback_peek(string);
    
    sm_select_state(string_esc_universal_6);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_5);
    sm_fallback_peek(string);
    
    sm_select_state(string_esc_universal_5);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_4);
    sm_fallback_peek(string);
    
    sm_select_state(string_esc_universal_4);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_3);
    sm_fallback_peek(string);
    
    sm_select_state(string_esc_universal_3);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_2);
    sm_fallback_peek(string);
    
    sm_select_state(string_esc_universal_2);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_1);
    sm_fallback_peek(string);
    
    sm_select_state(string_esc_universal_1);
    sm_case("0123456789abcdefABCDEF", string);
    sm_fallback_peek(string);
    
	//~ Comments
	
    sm_select_state(comment_block); // When inside a comment block...
    {
		sm_case("*", comment_block_try_close); // See a *, the block could be about to be closed.
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("BlockComment");
			sm_case_eof_peek(emit); // In case of EOF, it's a block comment token.
		}
		sm_fallback(comment_block); // Stay in state comment_block
    }
    sm_select_state(comment_block_try_close);
    {
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("BlockComment");
			sm_case("/", emit);
		}
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("BlockComment");
			sm_case_eof_peek(emit);
		}
		sm_case("*", comment_block_try_close);
		sm_fallback(comment_block);
    }
    sm_select_state(comment_line);
    {
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LineComment");
			sm_case_peek("\n", emit);
		}
		{
			Emit_Rule *emit = Create_Emit_Rule();
			sm_emit_handler_direct("LineComment");
			sm_case_eof_peek(emit);
		}
		sm_case("\\", comment_line_backslashing);
		sm_fallback(comment_line);
    }
    sm_select_state(comment_line_backslashing);
    {
		sm_case("\r", comment_line_backslashing);
		sm_fallback(comment_line);
    }
}

#undef Create_Emit_Rule
#undef Associate_Name_To_Character

// BOTTOM

