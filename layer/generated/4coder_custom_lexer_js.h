#if !defined(FCODER_LEX_GEN_HAND_WRITTEN_TYPES)
#define FCODER_LEX_GEN_HAND_WRITTEN_TYPES

struct Lexeme_Table_Value{
    Token_Base_Kind base_kind;
    u16 sub_kind;
};

struct Lexeme_Table_Lookup{
    b32 found_match;
    Token_Base_Kind base_kind;
    u16 sub_kind;
};

#endif
typedef u16 Token_JS_Kind;
enum{
TokenJSKind_EOF = 0,
TokenJSKind_Whitespace = 1,
TokenJSKind_LexError = 2,
TokenJSKind_BlockComment = 3,
TokenJSKind_LineComment = 4,
TokenJSKind_Backslash = 5,
TokenJSKind_LiteralNumber = 6,
TokenJSKind_LiteralString = 7,
TokenJSKind_KeywordGeneric = 8,
TokenJSKind_BraceOp = 9,
TokenJSKind_BraceCl = 10,
TokenJSKind_ParenOp = 11,
TokenJSKind_BrackOp = 12,
TokenJSKind_ParenCl = 13,
TokenJSKind_BrackCl = 14,
TokenJSKind_Semicolon = 15,
TokenJSKind_Comma = 16,
TokenJSKind_Plus = 17,
TokenJSKind_Minus = 18,
TokenJSKind_Star = 19,
TokenJSKind_Div = 20,
TokenJSKind_Mod = 21,
TokenJSKind_Or = 22,
TokenJSKind_Xor = 23,
TokenJSKind_And = 24,
TokenJSKind_AndXor = 25,
TokenJSKind_LeftLeft = 26,
TokenJSKind_RightRight = 27,
TokenJSKind_Less = 28,
TokenJSKind_LessEq = 29,
TokenJSKind_Grtr = 30,
TokenJSKind_GrtrEq = 31,
TokenJSKind_EqEq = 32,
TokenJSKind_NotEq = 33,
TokenJSKind_AndAnd = 34,
TokenJSKind_OrOr = 35,
TokenJSKind_Not = 36,
TokenJSKind_Carrot = 37,
TokenJSKind_Dot = 38,
TokenJSKind_Ternary = 39,
TokenJSKind_Colon = 40,
TokenJSKind_Eq = 41,
TokenJSKind_PlusEq = 42,
TokenJSKind_MinusEq = 43,
TokenJSKind_StarEq = 44,
TokenJSKind_DivEq = 45,
TokenJSKind_ModEq = 46,
TokenJSKind_Await = 47,
TokenJSKind_Break = 48,
TokenJSKind_Case = 49,
TokenJSKind_Catch = 50,
TokenJSKind_Class = 51,
TokenJSKind_Const = 52,
TokenJSKind_Continue = 53,
TokenJSKind_Debugger = 54,
TokenJSKind_Default = 55,
TokenJSKind_Delete = 56,
TokenJSKind_Do = 57,
TokenJSKind_Else = 58,
TokenJSKind_Export = 59,
TokenJSKind_Extends = 60,
TokenJSKind_Finally = 61,
TokenJSKind_For = 62,
TokenJSKind_Function = 63,
TokenJSKind_If = 64,
TokenJSKind_Import = 65,
TokenJSKind_In = 66,
TokenJSKind_Instanceof = 67,
TokenJSKind_Let = 68,
TokenJSKind_New = 69,
TokenJSKind_Return = 70,
TokenJSKind_Super = 71,
TokenJSKind_Switch = 72,
TokenJSKind_This = 73,
TokenJSKind_Throw = 74,
TokenJSKind_Try = 75,
TokenJSKind_Typeof = 76,
TokenJSKind_Var = 77,
TokenJSKind_While = 78,
TokenJSKind_With = 79,
TokenJSKind_Yield = 80,
TokenJSKind_Static = 81,
TokenJSKind_Enum = 82,
TokenJSKind_Implements = 83,
TokenJSKind_Interface = 84,
TokenJSKind_Package = 85,
TokenJSKind_Private = 86,
TokenJSKind_Protected = 87,
TokenJSKind_Public = 88,
TokenJSKind_Null = 89,
TokenJSKind_Void = 90,
TokenJSKind_Undefined = 91,
TokenJSKind_LiteralTrue = 92,
TokenJSKind_LiteralFalse = 93,
TokenJSKind_Identifier = 94,
TokenJSKind_COUNT = 95,
};
char *token_js_kind_names[] = {
"EOF",
"Whitespace",
"LexError",
"BlockComment",
"LineComment",
"Backslash",
"LiteralNumber",
"LiteralString",
"KeywordGeneric",
"BraceOp",
"BraceCl",
"ParenOp",
"BrackOp",
"ParenCl",
"BrackCl",
"Semicolon",
"Comma",
"Plus",
"Minus",
"Star",
"Div",
"Mod",
"Or",
"Xor",
"And",
"AndXor",
"LeftLeft",
"RightRight",
"Less",
"LessEq",
"Grtr",
"GrtrEq",
"EqEq",
"NotEq",
"AndAnd",
"OrOr",
"Not",
"Carrot",
"Dot",
"Ternary",
"Colon",
"Eq",
"PlusEq",
"MinusEq",
"StarEq",
"DivEq",
"ModEq",
"Await",
"Break",
"Case",
"Catch",
"Class",
"Const",
"Continue",
"Debugger",
"Default",
"Delete",
"Do",
"Else",
"Export",
"Extends",
"Finally",
"For",
"Function",
"If",
"Import",
"In",
"Instanceof",
"Let",
"New",
"Return",
"Super",
"Switch",
"This",
"Throw",
"Try",
"Typeof",
"Var",
"While",
"With",
"Yield",
"Static",
"Enum",
"Implements",
"Interface",
"Package",
"Private",
"Protected",
"Public",
"Null",
"Void",
"Undefined",
"LiteralTrue",
"LiteralFalse",
"Identifier",
};
