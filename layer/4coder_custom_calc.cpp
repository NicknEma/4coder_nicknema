#ifndef FCODER_CUSTOM_CALC_CPP
#define FCODER_CUSTOM_CALC_CPP

NAMESPACE_BEGIN(nne)

//~ Tick.
// This is used for animation graphs over time.

global f32 global_calc_time = 0.0f;
internal void calculator__tick(Frame_Info frame_info) {
    global_calc_time += frame_info.literal_dt;
}

//~ Calculator language lexing.

enum Calculator__Token_Type {
    Calculator__Token_Type_Invalid,
    Calculator__Token_Type_Identifier,
    Calculator__Token_Type_Source_Code_Identifier,
    Calculator__Token_Type_Number,
    Calculator__Token_Type_Symbol,
    Calculator__Token_Type_String_Constant,
};

struct Calculator__Token {
    Calculator__Token_Type type;
    char *string; // @Cleanup: Replace these two with a single String8?
    int string_length;
};

internal Calculator__Token calculator__get_token(char *buffer) {
    Calculator__Token token = { Calculator__Token_Type_Invalid };
    
	// These "SingleLineComment" and "MultilineComment" refer to comments inside
	// calc code. They are not source code comments (C++, Jai, etc).
	// This enum only serves to skip comments.
    enum Read_Mode {
        Read_Mode_Normal,
        Read_Mode_SingleLineComment,
        Read_Mode_MultilineComment,
    };
    
    if (buffer) {
		Read_Mode read_mode = Read_Mode_Normal;
		
		// @Rename: j
		for (int char_index = 0; buffer[char_index]; char_index += 1) {
			switch (read_mode) {
				case Read_Mode_SingleLineComment: {
					if (buffer[char_index] == '\n') {
						read_mode = Read_Mode_Normal;
					}
				} break;
				
				case Read_Mode_MultilineComment: {
					if (buffer[char_index] == '#' && buffer[char_index + 1] == '#') {
						read_mode = Read_Mode_Normal;
					} else if (buffer[char_index] == '*' && buffer[char_index + 1] == '/') {
						read_mode = Read_Mode_Normal;
					}
				} break;
				
				default: {
					if (buffer[char_index] == '#') {
						if (buffer[char_index + 1] == '#') {
							read_mode = Read_Mode_MultilineComment;
						} else {
							read_mode = Read_Mode_SingleLineComment;
						}
					} else if (buffer[char_index] == '/' && (buffer[char_index + 1] == '/' || buffer[char_index + 1] == '*')) {
						if (buffer[char_index + 1] == '/') {
							read_mode = Read_Mode_SingleLineComment;
						} else {
							read_mode = Read_Mode_MultilineComment;
						}
					} else if (buffer[char_index] == '@') {
						token.type = Calculator__Token_Type_Source_Code_Identifier;
						token.string = buffer + char_index + 1;
						
						int j;
						for (j = char_index + 1; buffer[j] && (char_is_digit(buffer[j]) || buffer[j] == '_' || char_is_alphabetic(buffer[j])); j += 1);
						
						token.string_length = j - char_index - 1;
						goto end;
					} else if (char_is_alphabetic(buffer[char_index])) {
						token.type = Calculator__Token_Type_Identifier;
						token.string = buffer + char_index;
						
						int j;
						for (j = char_index + 1; buffer[j] && (char_is_digit(buffer[j]) || buffer[j] == '_' || char_is_alphabetic(buffer[j])); j += 1);
						
						token.string_length = j - char_index;
						goto end;
					} else if (char_is_digit(buffer[char_index])) {
						token.type = Calculator__Token_Type_Number;
						token.string = buffer + char_index;
						
						int j;
						for (j = char_index+1; buffer[j] && (char_is_digit(buffer[j]) || buffer[j] == '.' || char_is_alphabetic(buffer[j])); j += 1);
						
						token.string_length = j - char_index;
						goto end;
					} else if (char_is_symbol(buffer[char_index])) {
						token.type = Calculator__Token_Type_Symbol;
						token.string = buffer + char_index;
						
						// Assumes 1-length symbols. Might not always be true.
						int j = char_index + 1;
						// for(j = i+1; buffer[j] && CharIsSymbol(buffer[j]); ++j);
						
						token.string_length = j - char_index;
						goto end;
					} else if (buffer[char_index] == '"' || buffer[char_index] == '\'') {
						int starting_char = buffer[char_index];
						token.type = Calculator__Token_Type_String_Constant;
						token.string = buffer + char_index;
						
						int j;
						for (j = char_index+1; buffer[j] && buffer[j] != starting_char; j += 1);
						
						token.string_length = j - char_index + 1;
						goto end;
					}
				} break;
			}
        }
		
		end:;
    }
    
    return token;
}

internal Calculator__Token calculator__consume_token(char **at) {
    Calculator__Token token = calculator__get_token(*at);
    *at = token.string + token.string_length;
    return token;
}

internal Calculator__Token calculator__peek_token(char **at) {
    Calculator__Token token = calculator__get_token(*at);
    return token;
}

internal b32 calculator__tokens_match(Calculator__Token token, char *str) {
	b32 match = false;
    
    if (token.string && token.string_length > 0 && token.type != Calculator__Token_Type_Invalid) {
        match = true;
        
		for (int i = 0; i < token.string_length; i += 1) {
            if (token.string[i] == str[i]) {
				// @Cleanup: Explain these extra checks.
                if (i == token.string_length - 1) {
                    if (str[i + 1] != 0) {
                        match = false;
                        break;
                    }
                }
            } else {
                match = false;
                break;
            }
        }
    }
	
    return match;
}

internal b32 calculator__require_token(char **at, char *str) {
	b32 result = false;
	
    Calculator__Token token = calculator__get_token(*at);
    if (calculator__tokens_match(token, str)) {
        result = true;
        *at = token.string + token.string_length;
    }
	
    return result;
}

internal b32 calculator__require_token_type(char **at, Calculator__Token_Type type, Calculator__Token *token_ptr) {
	b32 result = false;
	
    Calculator__Token token = calculator__get_token(*at);
    if (token.type == type) {
        result = true;
        *at = token.string + token.string_length;
        if (token_ptr) {
            *token_ptr = token;
        }
    }
	
    return result;
}

internal b32 calculator__require_newline(char **at) {
	b32 result = false;
    
    Calculator__Token next_token = calculator__peek_token(at);
    char *newline = 0;
    for (int i = 0; (*at)[i]; i += 1) {
        if ((*at)[i] == '\n') {
            newline = (*at)+i;
            break;
        }
    }
    
    if (newline) {
        if (next_token.string > newline) {
            result = true;
        }
    }
    
    return result;
}

internal b32 calculator__require_end_of_buffer(char **at) {
    Calculator__Token next_token = calculator__peek_token(at);
    b32 result = (next_token.string == 0);
    return result;
}

//~ Calculator language parsing.

#define Calculator__Node_Type_LIST              \
Calculator__Node_Type(Invalid,                0)\
Calculator__Node_Type(Error,                  0)\
Calculator__Node_Type(Number,                 0)\
Calculator__Node_Type(StringConstant,         0)\
Calculator__Node_Type(Array,                  0)\
Calculator__Node_Type(Identifier,             0)\
Calculator__Node_Type(SourceCodeIdentifier,   0)\
Calculator__Node_Type(FunctionCall,           0)\
Calculator__Node_Type(Add,                    1)\
Calculator__Node_Type(Subtract,               1)\
Calculator__Node_Type(Multiply,               2)\
Calculator__Node_Type(Divide,                 2)\
Calculator__Node_Type(Modulus,                2)\
Calculator__Node_Type(RaiseToPower,           0)\
Calculator__Node_Type(Negate,                 0)\
Calculator__Node_Type(Assignment,             0)\
Calculator__Node_Type(ArrayIndex,             0)\

#define Calculator__Type_LIST                                    \
Calculator__Type(Error,                 "error")                \
Calculator__Type(None,                  "none")                 \
Calculator__Type(Number,                "number")               \
Calculator__Type(Array,                 "array")                \
Calculator__Type(String,                "string")               \
Calculator__Type(SourceCodeReference,   "source code reference")

enum Calculator__Node_Type {
#define Calculator__Node_Type(name, precedence) Calculator__Node_Type_##name,
    Calculator__Node_Type_LIST
#undef Calculator__Node_Type
};

internal int calculator__get_operator_precedence(Calculator__Node_Type type) {
	local_persist int precedence_table[] = {
#define Calculator__Node_Type(name, precedence) precedence,
        Calculator__Node_Type_LIST
#undef Calculator__Node_Type
    };
    return precedence_table[type];
}

enum Calculator__Type {
#define Calculator__Type(name, str) Calculator__Type_##name,
    Calculator__Type_LIST
#undef Calculator__Type
};

internal char *calculator__get_type_name(Calculator__Type type) {
	local_persist char *name_table[] = {
#define Calculator__Type(name, str) str,
        Calculator__Type_LIST
#undef Calculator__Type
    };
    return name_table[type];
}

struct Calculator__Node {
    Calculator__Node_Type type;
	f64 value;
    union { Calculator__Node *operand; Calculator__Node *left; };
    Calculator__Node *right;
    union { Calculator__Node *first_parameter; Calculator__Node *first_member; };
    Calculator__Node *next;
    Calculator__Token token;
    int num_params;
    String_Const_u8 error_string;
    char *at_source; // @Cleanup: Isn't this already a part of the token?
};

internal Calculator__Node *calculator__allocate_node(Arena *arena, Calculator__Node_Type type, char *at_source) {
    Calculator__Node *node = push_array(arena, Calculator__Node, 1);
    
	MemorySet(node, 0, sizeof(*node));
    node->type = type;
    node->at_source = at_source;
	
    return node;
}

internal Calculator__Node *calculator__make_error_node(Arena *arena, char *format, ...) {
    Calculator__Node *node = push_array(arena, Calculator__Node, 1);
    
	MemorySet(node, 0, sizeof(*node));
    node->type = Calculator__Node_Type_Error;
    va_list args;
    va_start(args, format);
    node->error_string = push_stringfv(arena, format, args);
    va_end(args);
    
	return node;
}

internal Calculator__Node *calculator__parse_expression(Arena *arena, char **at_ptr);
internal Calculator__Node *calculator__parse_unary_expression(Arena *arena, char **at_ptr) {
    Calculator__Node *expression = 0;
    Calculator__Token token = calculator__peek_token(at_ptr);
    char *at_source = token.string;
    
    if (calculator__tokens_match(token, "-")) {
		// Unary minus.
        calculator__consume_token(at_ptr);
        expression = calculator__allocate_node(arena, Calculator__Node_Type_Negate, at_source);
        expression->operand = calculator__parse_unary_expression(arena, at_ptr);
    } else if (token.type == Calculator__Token_Type_Source_Code_Identifier) {
		// @Todo(ema): What's a source code identifier in this context?
        calculator__consume_token(at_ptr);
        expression = calculator__allocate_node(arena, Calculator__Node_Type_SourceCodeIdentifier, at_source);
        expression->token = token;
    } else if (token.type == Calculator__Token_Type_Identifier) {
        calculator__consume_token(at_ptr);
        if (calculator__require_token(at_ptr, "(")) {
            // Function call.
			
			expression = calculator__allocate_node(arena, Calculator__Node_Type_FunctionCall, at_source);
            expression->token = token;
            
            Calculator__Node **target_param = &expression->first_parameter;
            for (;;) {
                Calculator__Token next_token = calculator__peek_token(at_ptr);
                if (next_token.type == Calculator__Token_Type_Invalid || calculator__tokens_match(next_token, ")")) {
                    break;
                }
                
                Calculator__Node *param = calculator__parse_expression(arena, at_ptr);
                
                if (param) {
                    *target_param = param;
                    target_param = &(*target_param)->next;
                    calculator__require_token(at_ptr, ",");
                } else {
                    expression = calculator__make_error_node(arena, "Invalid parameter.");
                    goto end_parse;
                }
            }
            
            if (!calculator__require_token(at_ptr, ")")) {
                expression = calculator__make_error_node(arena, "Missing ')'.");
                goto end_parse;
            }
        } else {
            // Constant or variable.
			expression = calculator__allocate_node(arena, Calculator__Node_Type_Identifier, at_source);
            expression->token = token;
        }
    } else if (calculator__tokens_match(token, "(")) {
		// Expression in parentheses.
        calculator__consume_token(at_ptr);
        expression = calculator__parse_expression(arena, at_ptr);
        calculator__require_token(at_ptr, ")");
    } else if (token.type == Calculator__Token_Type_Number) {
        calculator__consume_token(at_ptr);
        expression = calculator__allocate_node(arena, Calculator__Node_Type_Number, at_source);
        expression->value = get_first_double_from_buffer(token.string);
    } else if (token.type == Calculator__Token_Type_String_Constant) {
        calculator__consume_token(at_ptr);
        expression = calculator__allocate_node(arena, Calculator__Node_Type_StringConstant, at_source);
        expression->token = token;
    } else if (calculator__tokens_match(token, "[")) {
        calculator__consume_token(at_ptr);
        
        expression = calculator__allocate_node(arena, Calculator__Node_Type_Array, at_source);
        Calculator__Node **target_member = &expression->first_member;
        for (;;) {
            token = calculator__peek_token(at_ptr);
            if (calculator__tokens_match(token, "]") || token.type == Calculator__Token_Type_Invalid) {
                break;
            }
            
            Calculator__Node *member_expression = calculator__parse_expression(arena, at_ptr);
            if (!calculator__require_token(at_ptr, ",")) {
                expression = calculator__make_error_node(arena, "Missing ','.");
                goto end_parse;
            }
			
            if (member_expression) {
                *target_member = member_expression;
                target_member = &(*target_member)->next;
            } else {
                break;
            }
        }
        
        calculator__require_token(at_ptr, "]");
    }
    
    if (calculator__require_token(at_ptr, "^")) {
        Calculator__Node *old_expr = expression;
        expression = calculator__allocate_node(arena, Calculator__Node_Type_RaiseToPower, at_source);
        expression->left = old_expr;
        expression->right = calculator__parse_unary_expression(arena, at_ptr);
    }
    
    // Array index.
    if (expression) {
        while (calculator__require_token(at_ptr, "[")) {
            Calculator__Node *old_expr = expression;
            expression = calculator__allocate_node(arena, Calculator__Node_Type_ArrayIndex, at_source);
            expression->token = token;
            expression->left = old_expr;
            expression->right = calculator__parse_expression(arena, at_ptr);
            
            if (!expression->right) {
                expression = calculator__make_error_node(arena, "Missing array index inside of '[' and ']'.");
                goto end_parse;
            }
            
            if (!calculator__require_token(at_ptr, "]")) {
                expression = calculator__make_error_node(arena, "Missing ']'.");
                goto end_parse;
            }
        }
    }
    
    end_parse:;
    return expression;
}

internal Calculator__Node_Type calculator__get_binary_operator_type_from_token(Calculator__Token token) {
    Calculator__Node_Type type = Calculator__Node_Type_Invalid;
	
	if (token.type == Calculator__Token_Type_Symbol) {
        switch (token.string[0]) {
			case '+': { type = Calculator__Node_Type_Add;      } break;
			case '-': { type = Calculator__Node_Type_Subtract; } break;
			case '*': { type = Calculator__Node_Type_Multiply; } break;
			case '/': { type = Calculator__Node_Type_Divide;   } break;
			case '%': { type = Calculator__Node_Type_Modulus;  } break;
			default: break;
        }
    }
	
    return type;
}

internal Calculator__Node *calculator__parse_expression_internal(Arena *arena, char **at_ptr, int precedence_in) {
    Calculator__Node *expression = calculator__parse_unary_expression(arena, at_ptr);
    
    if (expression) {
        Calculator__Token token = calculator__peek_token(at_ptr);
        Calculator__Node_Type operator_type = calculator__get_binary_operator_type_from_token(token);
        
        char *at_source = token.string;
        
        if (token.string && operator_type != Calculator__Node_Type_Invalid && operator_type != Calculator__Node_Type_Number) {
            for (int precedence = calculator__get_operator_precedence(operator_type); precedence >= precedence_in; precedence -= 1) {
                for (;;) {
                    token = calculator__peek_token(at_ptr);
                    
                    operator_type = calculator__get_binary_operator_type_from_token(token);
                    int operator_precedence = calculator__get_operator_precedence(operator_type);
                    
                    if (operator_precedence != precedence) {
                        break;
                    }
                    
                    if (operator_type == Calculator__Node_Type_Invalid) {
                        break;
                    }
                    
                    calculator__consume_token(at_ptr);
                    
                    Calculator__Node *right = calculator__parse_expression_internal(arena, at_ptr, precedence+1);
                    Calculator__Node *existing_expression = expression;
                    expression = calculator__allocate_node(arena, operator_type, at_source);
                    expression->type = operator_type;
                    expression->left = existing_expression;
                    expression->right = right;
                    
                    if (!right) {
                        goto end_parse;
                    }
                }
            }
            
            end_parse:;
        }
    }
    
    
    return expression;
}

internal Calculator__Node *calculator__parse_expression(Arena *arena, char **at_ptr) {
    return calculator__parse_expression_internal(arena, at_ptr, 1);
}

internal Calculator__Node *calculator__parse_code(Arena *arena, char **at_ptr) {
    Calculator__Node *root = 0;
    Calculator__Node **target = &root;
    
    for (;;) {
        Calculator__Token token = calculator__peek_token(at_ptr);
        
        // Parse assignment.
        if (token.type == Calculator__Token_Type_Identifier) {
            char *at_source = token.string;
            
            char *at_reset = *at_ptr;
            calculator__consume_token(at_ptr);
            
            // Variable assignment.
            if (calculator__require_token(at_ptr, "=")) {
                Calculator__Node *identifier = calculator__allocate_node(arena, Calculator__Node_Type_Identifier, at_source);
                identifier->token = token;
                
                Calculator__Node *assignment = calculator__allocate_node(arena, Calculator__Node_Type_Assignment, at_source);
                assignment->left = identifier;
                assignment->right = calculator__parse_expression(arena, at_ptr);
                
                if (assignment == 0) {
                    break;
                }
                
                if (assignment->right == 0) {
                    assignment = calculator__make_error_node(arena, "Syntax error.");
                    *target = assignment;
                    break;
                } else if (assignment->right->type == Calculator__Node_Type_Error) {
                    assignment = assignment->right;
                    *target = assignment;
                    break;
                }
                
                *target = assignment;
                target = &(*target)->next;
                goto end_parse;
            } else {
                *at_ptr = at_reset;
            }
        }
        
        // Parse expression.
        {
            Calculator__Node *expression = calculator__parse_expression(arena, at_ptr);
            if (expression) {
                *target = expression;
				target  = &(*target)->next;
            } else { break; }
        }
        
        end_parse:;
        if (!calculator__require_token(at_ptr, ";") && !calculator__require_newline(at_ptr) && !calculator__require_end_of_buffer(at_ptr)) {
            *target = calculator__make_error_node(arena, "Expected end-of-statement (semicolon or newline).");
            target = &(*target)->next;
            break;
        }
    }
    
    return root;
}

//~ End of parser.

//~ Values and constructors.

struct Calculator__Value {
    union {
        struct { f64 as_f64; };
        struct { String_Const_u8 as_error; };
        struct { String_Const_u8 as_string; };
        struct { i64 as_token_offset; };
        struct { int array_count; Calculator__Value *as_array; };
    };
    
    Calculator__Type type;
};

// @Cleanup(ema): Make them as actual constructors?
internal Calculator__Value Calculator__ValueNone(void) {
    Calculator__Value calc_value = {};
	calc_value.type = Calculator__Type_None;
    return calc_value;
}

internal Calculator__Value Calculator__ValueF64(double num) {
    Calculator__Value val = {};
    val.type = Calculator__Type_Number;
    val.as_f64 = num;
    return val;
}

internal Calculator__Value Calculator__ValueError(String_Const_u8 string) {
    Calculator__Value val = {};
    val.type = Calculator__Type_Error;
    val.as_error = string;
    return val;
}

internal Calculator__Value Calculator__ValueString(String_Const_u8 string) {
    Calculator__Value val = {};
    val.type = Calculator__Type_String;
    val.as_string = string;
    return val;
}

internal Calculator__Value Calculator__ValueSourceCodeReference(i64 token_position) {
    Calculator__Value val = {};
    val.type = Calculator__Type_SourceCodeReference;
    val.as_token_offset = token_position;
    return val;
}

internal Calculator__Value Calculator__ValueArray(struct CalcInterpretContext *context, Calculator__Node *first_member);

struct Calculator__Graph {
    Calculator__Graph *next;
    
	Calculator__Node *parent_call;
    Plot2DMode mode;
    String_Const_u8 plot_title;
    String_Const_u8 x_axis;
    String_Const_u8 y_axis;
    int num_function_samples;
    Rect_f32 plot_view;
    int num_bins;
    Range_f32 bin_data_range;
    union {
        float *x_data;
        float *data;
    };
    float *y_data;
    int data_count;
    i32 style_flags;
};

struct Calculator__Result {
    Calculator__Value value;
    Calculator__Graph *first_graph;
};

struct Calculator__Symbol_Table;
struct Calculator__Interpreter_Context {
    Application_Links *app;
    Buffer_ID buffer;
    Text_Layout_ID text_layout_id;
    Arena *arena;
    Calculator__Symbol_Table *symbol_table;
    f32 current_time;
    
    // Plot data.
    struct {
        String_Const_u8 plot_title;
        String_Const_u8 x_axis;
        String_Const_u8 y_axis;
        Rect_f32 plot_view;
        int num_function_samples;
        int num_bins;
        f32 bin_range_low;
        f32 bin_range_high;
    };
};

// We need to call this function inside the value_array constructor because we need to infer the type of the array.
// The type is inferred from the first member of the array, and the subsequent ones are checked to make sure
// they are of the same type.
internal Calculator__Result calculator__interpret_expression(Calculator__Interpreter_Context *context, Calculator__Node *root);

internal Calculator__Value calculator__make_value_array(Calculator__Interpreter_Context *context, Calculator__Node *first_member) {
    Calculator__Value val = {};
    val.type = Calculator__Type_Array;
    
	// First get the length of the array so that you can allocate enough memory.
    int count = 0;
    for (Calculator__Node *member = first_member; member; member = member->next) {
        count += 1;
    }
    
	Calculator__Value *array = push_array(context->arena, Calculator__Value, count);
    
    int write_pos = 0;
    Calculator__Type array_type = Calculator__Type_None;
    for (Calculator__Node *member = first_member; member; member = member->next) {
        Calculator__Result result = calculator__interpret_expression(context, member);
        
        if (member == first_member) {
            // The first member of the array decides the type of the array.
			array_type = result.value.type;
			
            if (array_type == Calculator__Type_Error) {
                val = result.value;
                goto end_create;
            } else if (array_type == Calculator__Type_None) {
                val = Calculator__ValueError(string_u8_litexpr("Cannot make arrays of 'none' type."));
                goto end_create;
            }
        } else {
            if (result.value.type != array_type) {
                val = Calculator__ValueError(string_u8_litexpr("Cannot have multiple types in an array."));
                goto end_create;
            }
        }
        
        array[write_pos] = result.value;
		write_pos += 1;
    }
    
    if (array && count != 0) {
        val.as_array    = array;
        val.array_count = count;
    }
    
    end_create:;
    return val;
}

//~ End of Values and their constructors.

//~ Calculator Symbol Table.

// typedef struct CalcSymbolKey CalcSymbolKey;
struct CalcSymbolKey { // @Cleanup(ema): Why not as a String_Const_u8?
    char *string;
    i32 string_length;
    b32 deleted;
};

// typedef struct CalcSymbolValue CalcSymbolValue;
struct CalcSymbolValue {
    Calculator__Value value;
};

// typedef struct Calculator__Symbol_Table Calculator__Symbol_Table;
struct Calculator__Symbol_Table {
	u32 size;
    CalcSymbolKey   *keys;
    CalcSymbolValue *values;
};

internal Calculator__Symbol_Table calculator__init_symbol_table(Arena *arena, u32 size) {
    Calculator__Symbol_Table table = {};
    
	table.size   = size;
    table.keys   = push_array(arena, CalcSymbolKey,   size);
    table.values = push_array(arena, CalcSymbolValue, size);
    MemorySet(table.keys,   0, sizeof(*table.keys)  * size);
    MemorySet(table.values, 0, sizeof(*table.values)* size);
    
	return table;
}

// @Cleanup: Unify string and string_length.
internal CalcSymbolValue *Calculator__Symbol_TableLookup_(Calculator__Symbol_Table *table, char *string, int length) {
    CalcSymbolValue *result = 0;
    
	u32 hash = string_crc32(string, length) % table->size;
	u32 original_hash = hash;
    
#if 1
    
	// @Cleanup: Veryfy that the other version works and delete this. So much code!
	CalcSymbolValue *value = 0;
    
	for (;;) {
        if (table->keys[hash].string || table->keys[hash].deleted) {
            if (!table->keys[hash].deleted && strings_match_case_sensitive(table->keys[hash].string, table->keys[hash].string_length, string, length)) {
                value = table->values + hash;
                break;
            } else {
                if (++hash >= table->size) {
                    hash = 0;
                }
                if (hash == original_hash) {
                    break;
                }
            }
        } else {
            break;
        }
    }
	
    if (value) {
        result = value;
    }
    
#else
	
	while ((table->keys[hash].string || table->keys[hash].deleted) && !result) {
		if (!table->keys[hash].deleted && strings_match_case_sensitive(table->keys[hash].string, table->keys[hash].string_length, string, length)) {
			result = &table->values[hash];
		} else {
			hash += 1;
			if (hash >= table->size) { hash = 0; } // We overflew the table, wrap back to the beginning.
			if (hash == original_hash) { break; } // We went back to the place we started at, we didn't find anything.
		}
    }
	
#endif
	
    return result;
}

// @Cleanup: Unify string and string_length.
internal Calculator__Value Calculator__Symbol_TableLookup(Calculator__Symbol_Table *table, char *string, int string_length) {
    Calculator__Value value = {};
    
	CalcSymbolValue *table_value = Calculator__Symbol_TableLookup_(table, string, string_length);
    if (table_value) { value = table_value->value; }
	else             { value.type = Calculator__Type_Error; }
	
    return value;
}

// @Cleanup(ema): Why not as a String_Const_u8?
internal CalcSymbolValue *calculator__add_to_symbol_table(Calculator__Symbol_Table *table, char *string, int string_length, Calculator__Value value) {
    CalcSymbolValue *result = 0;
    
	u32 hash = string_crc32(string, string_length) % table->size;
	u32 original_hash = hash;
	u32 found_hash = 0;
	b32 found = false;
    
    for (;;) {
        if (table->keys[hash].string || table->keys[hash].deleted) {
            if (!table->keys[hash].deleted && strings_match_case_sensitive(table->keys[hash].string, table->keys[hash].string_length, string, string_length)) {
                found = true;
                found_hash = hash;
                break;
            } else if (table->keys[hash].deleted) {
                found = true;
                found_hash = hash;
            }
            
            if (++hash >= table->size) {
                hash = 0;
            }
			
            if (hash == original_hash) {
                break;
            }
        } else {
            found = true;
            found_hash = hash;
            break;
        }
    }
    
    if (found) {
        table->keys[found_hash].string = string;
        table->keys[found_hash].string_length = string_length;
        table->values[found_hash].value = value;
        result = table->values + found_hash;
    }
    
    return result;
}

// @Cleanup: String_Const_u8 param
internal void Calculator__Symbol_TableRemove(Calculator__Symbol_Table *table, char *string, int length) {
	u32 hash = string_crc32(string, length) % table->size;
	u32 original_hash = hash;
    
#if 1
	
    for(;;)
    {
        if(table->keys[hash].string || table->keys[hash].deleted)
        {
            if(!table->keys[hash].deleted &&
               strings_match_case_sensitive(table->keys[hash].string, table->keys[hash].string_length,
											string, length))
            {
                table->keys[hash].deleted = 1;
                break;
            }
            
            if(++hash >= table->size)
            {
                hash = 0;
            }
            if(hash == original_hash)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
	
#else
	
    while (table->keys[hash].string || table->keys[hash].deleted) {
		if(!table->keys[hash].deleted && strings_match_case_sensitive(table->keys[hash].string, table->keys[hash].string_length, string, length)) {
			table->keys[hash].deleted = true;
			break;
		}
		
		hash += 1;
		if (hash >= table->size) { hash = 0; }
		if(hash == original_hash) { break; }
    }
	
#endif
}

internal void GetDataFromSourceCode(Application_Links *app, Buffer_ID buffer, Text_Layout_ID text_layout_id, i64 start_pos, Arena *arena, float **data_ptr, int *data_count_ptr) {
    Token_Array token_array = get_token_array_from_buffer(app, buffer);
    Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
    
    if(token_array.tokens != 0)
    {
        Token_Iterator_Array it = token_iterator_pos(0, &token_array, start_pos);
        Token *token = 0;
        
        b32 found = 0;
        
        // NOTE(rjf): Find scope open (opening brace of initializer).
        for(;;)
        {
            token = token_it_read(&it);
            if(token->pos >= start_pos + 30 || !token ||
               !token_it_inc_non_whitespace(&it))
            {
                found = 0;
                break;
            }
            
            if(token->kind == TokenBaseKind_ScopeOpen)
            {
                found = 1;
                break;
            }
        }
        
        // NOTE(rjf): Read data.
        if(found)
        {
            struct DataChunk
            {
                DataChunk *next;
                u64 value_count;
                float values[1024];
            };
            
            u64 total_value_count = 0;
            DataChunk *data_chunk = push_array_zero(arena, DataChunk, 1);
            DataChunk *first_data_chunk = data_chunk;
            DataChunk *last_data_chunk = data_chunk;
            
            b32 is_negative = 0;
            int data_count;
            float *data;
            for(;;)
            {
                token = token_it_read(&it);
                if(!token || !token_it_inc_non_whitespace(&it))
                {
                    goto end_read_data;
                }
                
                if(token->kind == TokenBaseKind_Operator &&
                   token->sub_kind == TokenCppKind_Minus)
                {
                    is_negative = 1;
                }
                
                if(token->kind == TokenBaseKind_LiteralFloat ||
                   token->kind == TokenBaseKind_LiteralInteger)
                {
                    Range_i64 token_range =
                    {
                        token->pos,
                        token->pos + (token->size > 256 ? 256 : token->size),
                    };
                    
                    u8 token_buffer[256];
                    buffer_read_range(app, buffer, token_range, token_buffer);
                    
                    float sign = is_negative ? -1.f : 1.f;
                    is_negative = 0;
                    
                    float value = sign * (float)get_first_double_from_buffer((char *)token_buffer);
                    if(last_data_chunk->value_count >= ArrayCount(last_data_chunk->values))
                    {
                        DataChunk *new_chunk = push_array_zero(arena, DataChunk, 1);
                        last_data_chunk->next = new_chunk;
                        last_data_chunk = new_chunk;
                    }
                    last_data_chunk->values[last_data_chunk->value_count++] = value;
                    total_value_count += 1;
                }
                else if(token->kind == TokenBaseKind_ScopeClose)
                {
                    break;
                }
            }
            
            data_count = 0;
            data = push_array_zero(arena, float, total_value_count);
            for(DataChunk *chunk = first_data_chunk; chunk; chunk = chunk->next)
            {
                for(int i = 0; i < ArrayCount(chunk->values); i += 1)
                {
                    data[data_count] = chunk->values[i];
                    data_count += 1;
                }
            }
            
            *data_ptr = data;
            *data_count_ptr = data_count;
            
            end_read_data:;
        }
        
    }
}

//~ Plotting

internal void calculator__graph_expression(Application_Links *app, Face_ID face_id, Rect_f32 screen_rect, Calculator__Graph *graph_list, Calculator__Interpreter_Context *context) {
    Calculator__Node *parent_call = graph_list->parent_call;
    Rect_f32 plot_view = graph_list->plot_view;
    
	// Count graphs.
    int plot_count = 0;
    for (Calculator__Graph *graph = graph_list; graph && graph->parent_call == parent_call; graph = graph->next) {
        plot_count += 1;
    }
    
    Plot2DInfo plot_data = {};
	{
        plot_data.mode           = graph_list->mode;
        plot_data.title          = graph_list->plot_title;
        plot_data.x_axis         = graph_list->x_axis;
        plot_data.y_axis         = graph_list->y_axis;
        plot_data.screen_rect    = screen_rect;
        plot_data.app            = app;
        plot_data.title_face_id  = global_styled_title_face;
        plot_data.label_face_id  = global_styled_label_face;
        plot_data.plot_view      = plot_view;
        plot_data.num_bins       = graph_list->num_bins;
        plot_data.bin_data_range = graph_list->bin_data_range;
        
        if (graph_list->num_bins > 0) {
            plot_data.bin_group_count = plot_count;
            plot_data.bins = push_array_zero(context->arena, int, plot_data.num_bins*plot_data.bin_group_count);
        }
    }
    Plot2DBegin(&plot_data);
    
	// Do plotting.
    for (Calculator__Graph *graph = graph_list; graph && graph->parent_call == parent_call; graph = graph->next) {
        switch (plot_data.mode) {
            case Plot2DMode_Line:      { Plot2DPoints   (&plot_data, graph->style_flags, graph->x_data, graph->y_data, graph->data_count); } break;
            case Plot2DMode_Histogram: { Plot2DHistogram(&plot_data, graph->data, graph->data_count); } break;
            default: break;
        }
    }
    
    Plot2DEnd(&plot_data);
}

// @Rename a bunch of stuff here.
// typedef struct CalcFindInputResult CalcFindInputResult;
struct CalcFindInputResult {
    Calculator__Node *unknown;
    int number_unknowns;
};

internal CalcFindInputResult FindUnknownForGraph(Calculator__Symbol_Table *table, Calculator__Node *expression) {
    CalcFindInputResult result = {};
    
    if (expression && expression->type != Calculator__Node_Type_Invalid) {
        if (expression->type == Calculator__Node_Type_Identifier) {
            CalcSymbolValue *symbol_value = Calculator__Symbol_TableLookup_(table, expression->token.string, expression->token.string_length);
            
            if (!symbol_value) {
                result.unknown = expression;
                result.number_unknowns += 1;
            }
        } else {
            CalcFindInputResult results[] = {
                FindUnknownForGraph(table, expression->left),
                FindUnknownForGraph(table, expression->right),
                FindUnknownForGraph(table, expression->first_parameter),
                FindUnknownForGraph(table, expression->next),
            };
            
            for (int i = 0; i < ArrayCount(results); i += 1) {
                if (results[i].unknown) {
                    if (!result.unknown) {
                        result.unknown = results[i].unknown;
                        result.number_unknowns += 1;
                    } else {
                        if (!strings_match_case_sensitive(results[i].unknown->token.string, results[i].unknown->token.string_length, result.unknown->token.string, result.unknown->token.string_length)) {
                            result.number_unknowns += 1;
                        }
                    }
                }
            }
        }
    }
    
    return result;
}

internal void GenerateLinePlotData(Calculator__Interpreter_Context *context, Calculator__Node *expression, Calculator__Node *input_variable, float **x_data, float **y_data, int *data_count, i32 *style_flags_ptr) {
    Calculator__Result expression_result = calculator__interpret_expression(context, expression);
    
    *x_data = 0;
    *y_data = 0;
    *data_count = 0;
    *style_flags_ptr = 0;
    
    i32 style_flags = 0;
    
    //~ NOTE(rjf): Plotting scripting arrays.
    if(expression_result.value.type == Calculator__Type_Array)
    {
        style_flags |= Plot2DStyleFlags_Points;
        
        // NOTE(rjf): X/Y data arrays.
        if(expression_result.value.array_count == 2 &&
           expression_result.value.as_array[0].type == Calculator__Type_Array &&
           expression_result.value.as_array[1].type == Calculator__Type_Array &&
           expression_result.value.as_array[0].array_count > 0 &&
           expression_result.value.as_array[0].array_count ==
           expression_result.value.as_array[1].array_count &&
           expression_result.value.as_array[0].as_array[0].type ==
           expression_result.value.as_array[1].as_array[0].type &&
           expression_result.value.as_array[0].as_array[0].type == Calculator__Type_Number)
        {
            int values_to_plot = expression_result.value.as_array[0].array_count;
            float *x_values = push_array(context->arena, float, values_to_plot);
            float *y_values = push_array(context->arena, float, values_to_plot);
            
            for(int i = 0; i < values_to_plot; ++i)
            {
                x_values[i] = (float)expression_result.value.as_array[0].as_array[i].as_f64;
                y_values[i] = (float)expression_result.value.as_array[1].as_array[i].as_f64;
            }
            
            *x_data = x_values;
            *y_data = y_values;
            *data_count = values_to_plot;
        }
        
        // NOTE(rjf): Just Y data.
        else if(expression_result.value.array_count > 0 &&
                expression_result.value.as_array[0].type == Calculator__Type_Number)
        {
            int values_to_plot = expression_result.value.array_count;
            float *x_values = push_array(context->arena, float, values_to_plot);
            float *y_values = push_array(context->arena, float, values_to_plot);
            
            for(int i = 0; i < values_to_plot; ++i)
            {
                x_values[i] = (float)i;
                y_values[i] = (float)expression_result.value.as_array[i].as_f64;
            }
            
            *x_data = x_values;
            *y_data = y_values;
            *data_count = values_to_plot;
        }
        
    }
    
    
    //~ NOTE(rjf): Graphing data from source code.
    else if(expression_result.value.type == Calculator__Type_SourceCodeReference)
    {
        style_flags |= Plot2DStyleFlags_Points;
        
        float *y_values = 0;
        int values_to_plot = 0;
        GetDataFromSourceCode(context->app, context->buffer, context->text_layout_id,
                              expression_result.value.as_token_offset, context->arena,
                              &y_values, &values_to_plot);
        
        // NOTE(rjf): Plot data.
        if(y_values && values_to_plot)
        {
            float *x_values = push_array(context->arena, float, values_to_plot);
            for(int i = 0; i < values_to_plot; ++i)
            {
                x_values[i] = (float)i;
            }
            *x_data = x_values;
            *y_data = y_values;
            *data_count = values_to_plot;
        }
    }
    
    
    //~ NOTE(rjf): Graphing scripting functions.
    else
    {
        style_flags |= Plot2DStyleFlags_Lines;
        
        Calculator__Node *input_node = input_variable;
        CalcSymbolValue *symbol_value_ptr = 0;
        if(input_node)
        {
            Calculator__Value value = Calculator__ValueF64(0);
            symbol_value_ptr =
                calculator__add_to_symbol_table(context->symbol_table, input_node->token.string,
												input_node->token.string_length, value);
        }
        
        // NOTE(rjf): Find function sample points.
        int values_to_plot = context->num_function_samples;
        float *x_values = push_array(context->arena, float, values_to_plot);
        float *y_values = push_array(context->arena, float, values_to_plot);
        {
            for(int i = 0; i < values_to_plot; ++i)
            {
                double new_x_value = (context->plot_view.x0 + (i / (float)values_to_plot) *
                                      (context->plot_view.x1 - context->plot_view.x0));
                if(symbol_value_ptr)
                {
                    symbol_value_ptr->value.as_f64 = new_x_value;
                }
                
                Calculator__Result result = calculator__interpret_expression(context, expression);
                if(result.value.type != Calculator__Type_Number)
                {
                    break;
                }
                else
                {
                    x_values[i] = (float)new_x_value;
                    y_values[i] = (float)result.value.as_f64;
                }
            }
        }
        
        if(input_node)
        {
            Calculator__Symbol_TableRemove(context->symbol_table, input_node->token.string,
										   input_node->token.string_length);
        }
        
        *x_data = x_values;
        *y_data = y_values;
        *data_count = values_to_plot;
    }
    
    *style_flags_ptr = style_flags;
}

internal void GenerateHistogramPlotData(Calculator__Interpreter_Context *context, Calculator__Node *expression, Calculator__Node *input_variable, float **data, int *data_count) {
    Calculator__Result expression_result = calculator__interpret_expression(context, expression);
    
    *data = 0;
    *data_count = 0;
    
    // NOTE(rjf): Graphing scripting arrays.
    if(expression_result.value.type == Calculator__Type_Array)
    {
        
        if(expression_result.value.array_count > 0 &&
           expression_result.value.as_array[0].type == Calculator__Type_Number)
        {
            int values_to_plot = expression_result.value.array_count;
            float *values = push_array(context->arena, float, values_to_plot);
            
            for(int i = 0; i < values_to_plot; ++i)
            {
                values[i] = (float)expression_result.value.as_array[i].as_f64;
            }
            
            *data = values;
            *data_count = values_to_plot;
        }
        
    }
    
    // NOTE(rjf): Graphing data from source code.
    else if(expression_result.value.type == Calculator__Type_SourceCodeReference)
    {
        float *values = 0;
        int values_to_plot = 0;
        GetDataFromSourceCode(context->app, context->buffer, context->text_layout_id,
                              expression_result.value.as_token_offset, context->arena,
                              &values, &values_to_plot);
        
        // NOTE(rjf): Plot data.
        if(values && values_to_plot)
        {
            *data = values;
            *data_count = values_to_plot;
        }
    }
    
    // NOTE(rjf): Graphing scripting functions.
    else
    {
        
    }
    
}

//~ End of graphing.

//~ Build-in functions.

#define CALC_BUILT_IN_FUNCTION(name) Calculator__Result name(Calculator__Interpreter_Context *context, int param_count, Calculator__Result *params)
typedef CALC_BUILT_IN_FUNCTION(CalcBuiltInFunction);

internal CALC_BUILT_IN_FUNCTION(CalcSin) {
    Calculator__Result result = {};
    result.value = Calculator__ValueF64(sin(params[0].value.as_f64));
    return result;
}

internal CALC_BUILT_IN_FUNCTION(CalcCos) {
    Calculator__Result result = {};
    result.value = Calculator__ValueF64(cos(params[0].value.as_f64));
    return result;
}

internal CALC_BUILT_IN_FUNCTION(CalcTan) {
    Calculator__Result result = {};
    result.value = Calculator__ValueF64(tan(params[0].value.as_f64));
    return result;
}

internal CALC_BUILT_IN_FUNCTION(CalcAbs) {
    Calculator__Result result = {};
    result.value = Calculator__ValueF64(fabs(params[0].value.as_f64));
    return result;
}

internal CALC_BUILT_IN_FUNCTION(CalcPlotTitle) {
    context->plot_title = params[0].value.as_string;
    context->plot_title.str += 1;
    context->plot_title.size -= 2;
    Calculator__Result result = {};
    result.value = Calculator__ValueNone();
    return result;
}

internal CALC_BUILT_IN_FUNCTION(CalcPlotFunctionSamples) {
    context->num_function_samples = (int)params[0].value.as_f64;
    Calculator__Result result = {};
    result.value = Calculator__ValueNone();
    return result;
}

internal CALC_BUILT_IN_FUNCTION(CalcPlotBinCount) {
    context->num_bins = (int)params[0].value.as_f64;
    Calculator__Result result = {};
    result.value = Calculator__ValueNone();
    return result;
}

internal CALC_BUILT_IN_FUNCTION(CalcPlotBinRange) {
    context->bin_range_low = (f32)params[0].value.as_f64;
    context->bin_range_high = (f32)params[1].value.as_f64;
    Calculator__Result result = {};
    result.value = Calculator__ValueNone();
    return result;
}

internal CALC_BUILT_IN_FUNCTION(CalcTime) {
    Calculator__Result result = {};
    result.value = Calculator__ValueF64((f64)context->current_time);
    animate_in_n_milliseconds(context->app, 0);
    return result;
}

internal Calculator__Result calculator__call_builtin_function(Calculator__Interpreter_Context *context, Calculator__Node *root) {
    
#define MAX_BUILTIN_PARAM 4
    
    Calculator__Result result = {};
    b32 function_valid = 0;
    
    if (!root || root->type != Calculator__Node_Type_FunctionCall) {
        result.value = Calculator__ValueError(string_u8_litexpr("Internal parsing error, function call expected."));
        goto end_func_call;
    }
    
	// @Cleanup: Why is this local here?
	local_persist struct {
        char *name;
        CalcBuiltInFunction *proc;
        Calculator__Type return_type;
        int required_parameter_count;
        Calculator__Type parameter_types[MAX_BUILTIN_PARAM];
    } functions[] = {
        { "sin", CalcSin, Calculator__Type_Number, 1, { Calculator__Type_Number }, },
        { "cos", CalcCos, Calculator__Type_Number, 1, { Calculator__Type_Number }, },
        { "tan", CalcTan, Calculator__Type_Number, 1, { Calculator__Type_Number }, },
        { "abs", CalcAbs, Calculator__Type_Number, 1, { Calculator__Type_Number }, },
        
        {
            "plot_title",
            CalcPlotTitle,
            Calculator__Type_None,
            1, { Calculator__Type_String },
        },
        
        {
            "plot_function_samples",
            CalcPlotFunctionSamples,
            Calculator__Type_None,
            1, { Calculator__Type_Number },
        },
        
        {
            "plot_bin_count",
            CalcPlotBinCount,
            Calculator__Type_None,
            1, { Calculator__Type_Number },
        },
        
        {
            "plot_bin_range",
            CalcPlotBinRange,
            Calculator__Type_None,
            2, { Calculator__Type_Number, Calculator__Type_Number },
        },
        
        { "time", CalcTime, Calculator__Type_Number, },
    };
    
    for (int function_index = 0; function_index < ArrayCount(functions); function_index += 1) {
        if (calculator__tokens_match(root->token, functions[function_index].name)) {
            // The requested function is a builtin function.
			// Check if the passed parameters match both in count and type, then
			// maybe call the function.
			
			function_valid = true;
            
            int param_count = 0;
            Calculator__Result param_results[MAX_BUILTIN_PARAM] = {0};
            for (Calculator__Node *param = root->first_parameter; param; param = param->next) {
                param_results[param_count++] = calculator__interpret_expression(context, param);
                if (param_count >= ArrayCount(param_results)) {
                    break;
                }
            }
            
			b32 correct_call = true; // There was no argument mismatch.
            
			// Check parameter count.
            if (param_count < functions[function_index].required_parameter_count) {
                String_Const_u8 error_string = push_stringf(context->arena, "%s expects at least %i parameters.", functions[function_index].name, functions[function_index].required_parameter_count);
                result.value = Calculator__ValueError(error_string);
                correct_call = false;
            }
            
			// Check parameter types.
            if (correct_call) {
                for (int param_index = 0; param_index < param_count; param_index += 1) {
                    if (param_results[param_index].value.type != functions[function_index].parameter_types[param_index]) {
                        correct_call = false;
                        String_Const_u8 error_string = push_stringf(context->arena, "'%s' expects a '%s' for parameter %i.",
																	functions[function_index].name, calculator__get_type_name(functions[function_index].parameter_types[param_index]), param_index + 1);
                        result.value = Calculator__ValueError(error_string);
                        break;
                    }
                }
            }
            
			// Actually evaluate function.
            if (correct_call) {
                result = functions[function_index].proc(context, param_count, param_results);
            }
        } else if (function_index == ArrayCount(functions) - 1) {
            if (calculator__tokens_match(root->token, "plot_xaxis") ||
				calculator__tokens_match(root->token, "plot_yaxis")) {
                function_valid = true;
                int is_y_axis = calculator__tokens_match(root->token, "plot_yaxis");
                
                result.value = Calculator__ValueNone();
                
                Calculator__Node *title_param = 0;
                Calculator__Node *low_param   = 0;
                Calculator__Node *high_param  = 0;
                
                Calculator__Result title_result = {};
                Calculator__Result low_result   = {};
                Calculator__Result high_result  = {};
                
                for (Calculator__Node *param = root->first_parameter; param; param = param->next) {
                    Calculator__Result interpret = calculator__interpret_expression(context, param);
                    
                    if (interpret.value.type == Calculator__Type_String) {
                        if (title_param) {
                            result.value = Calculator__ValueError(is_y_axis
																  ? string_u8_litexpr("plot_yaxis only accepts one string.")
																  : string_u8_litexpr("plot_xaxis only accepts one string."));
                            goto end_func_call;
                        } else {
                            title_param  = param;
                            title_result = interpret;
                        }
                    } else if (interpret.value.type == Calculator__Type_Number) {
                        if (low_param) {
                            if (high_param) {
                                result.value = Calculator__ValueError(is_y_axis
																	  ? string_u8_litexpr("plot_yaxis only accepts two numbers.")
																	  : string_u8_litexpr("plot_xaxis only accepts two numbers."));
                                
                                goto end_func_call;
                            } else {
                                high_param  = param;
                                high_result = interpret;
                            }
                        } else {
                            low_param  = param;
                            low_result = interpret;
                        }
                    } else {
                        result = interpret;
                        break;
                    }
                }
                
                if(low_param && high_param)
                {
                    if(is_y_axis)
                    {
                        if(title_result.value.as_string.size)
                        {
                            context->y_axis = strip_string_border_characters(title_result.value.as_string);
                        }
                        else
                        {
                            context->y_axis = {};
                        }
                        
                        context->plot_view.y0 = (f32)low_result.value.as_f64;
                        context->plot_view.y1 = (f32)high_result.value.as_f64;
                    }
                    else
                    {
                        if(title_result.value.as_string.size)
                        {
                            context->x_axis = strip_string_border_characters(title_result.value.as_string);
                        }
                        else
                        {
                            context->x_axis = {};
                        }
                        
                        context->plot_view.x0 = (f32)low_result.value.as_f64;
                        context->plot_view.x1 = (f32)high_result.value.as_f64;
                    }
                }
                else
                {
                    result.value = Calculator__ValueError(is_y_axis
														  ? string_u8_litexpr("plot_yaxis needs two bounds (title optional).")
														  : string_u8_litexpr("plot_xaxis needs two bounds (title optional)."));
                }
            } else if (calculator__tokens_match(root->token, "plot") ||
					   calculator__tokens_match(root->token, "plot_histogram")) {
                function_valid = true;
                
				// Select the desired plot mode (line or histogram).
                struct { char *name; Plot2DMode mode; } plot_functions[] = {
                    { "plot",           Plot2DMode_Line,       },
                    { "plot_histogram", Plot2DMode_Histogram,  },
                };
                Plot2DMode mode = Plot2DMode_Line;
                for (int plot_function_index = 0; plot_function_index < ArrayCount(plot_functions); plot_function_index += 1) {
                    if (calculator__tokens_match(root->token, plot_functions[plot_function_index].name)) {
                        mode = plot_functions[plot_function_index].mode;
                    }
                }
                
                result.value = Calculator__ValueNone();
                
                Calculator__Graph **target = &result.first_graph;
                for (Calculator__Node *graph_expression = root->first_parameter; graph_expression; graph_expression = graph_expression->next) {
                    CalcFindInputResult input_find = FindUnknownForGraph(context->symbol_table, graph_expression);
                    if (input_find.number_unknowns <= 1) {
                        Calculator__Node *input_variable = input_find.unknown;
                        Calculator__Graph *new_graph = push_array_zero(context->arena, Calculator__Graph, 1);
                        
                        new_graph->next = 0;
                        new_graph->parent_call = root;
                        
                        new_graph->mode = mode;
                        new_graph->plot_title = context->plot_title;
                        new_graph->x_axis = context->x_axis;
                        new_graph->y_axis = context->y_axis;
                        
                        new_graph->num_function_samples = context->num_function_samples;
                        new_graph->plot_view = context->plot_view;
                        new_graph->num_bins = context->num_bins;
                        new_graph->bin_data_range.min = context->bin_range_low;
                        new_graph->bin_data_range.max = context->bin_range_high;
                        
                        // Generate the plotting data.
                        {
                            if (mode == Plot2DMode_Line) {
                                GenerateLinePlotData(context, graph_expression, input_variable, &new_graph->x_data, &new_graph->y_data, &new_graph->data_count, &new_graph->style_flags);
                            } else if (mode == Plot2DMode_Histogram) {
                                GenerateHistogramPlotData(context, graph_expression, input_variable, &new_graph->data, &new_graph->data_count);
                            }
                        }
                        
                        *target = new_graph;
                        target = &(*target)->next;
                    } else {
                        result.value = Calculator__ValueError(string_u8_litexpr("Too many unknowns in graphing expression."));
                        break;
                    }
                }
            }
        }
    }
    
    end_func_call:;
    if (!function_valid) {
        result.value = Calculator__ValueError(string_u8_litexpr("Unknown function."));
    }
    
    return result;
}

//~ End of builtin functions.

//~ Expression interpreter.

internal Calculator__Result calculator__interpret_expression(Calculator__Interpreter_Context *context, Calculator__Node *root) {
    Calculator__Result result = {};
    
	if (!root) {
		result.value = Calculator__ValueError(string_u8_litexpr("Syntax error."));
    } else {
        switch (root->type) {
            case Calculator__Node_Type_Error: { result.value = Calculator__ValueError(root->error_string); } break;
            case Calculator__Node_Type_Number: { result.value = Calculator__ValueF64(root->value); } break;
            case Calculator__Node_Type_Array: { result.value = calculator__make_value_array(context, root->first_member); } break;
            
            case Calculator__Node_Type_ArrayIndex: {
                result = calculator__interpret_expression(context, root->left);
                if (result.value.type == Calculator__Type_Array) {
                    Calculator__Result index = calculator__interpret_expression(context, root->right);
                    
                    if (index.value.type == Calculator__Type_Number) {
                        int array_index = cast(int)index.value.as_f64;
                        if (array_index >= 0 && array_index < result.value.array_count) {
                            result.value = result.value.as_array[array_index];
                        } else {
                            result.value = Calculator__ValueError(string_u8_litexpr("Array index out of bounds."));
                        }
                    } else {
                        result.value = Calculator__ValueError(string_u8_litexpr("Cannot use non-numbers to index arrays."));
                        goto end_interpret;
                    }
                } else {
                    result.value = Calculator__ValueError(string_u8_litexpr("Cannot index a non-array."));
                    goto end_interpret;
                }
            } break;
            
            case Calculator__Node_Type_StringConstant: {
                result.value = Calculator__ValueString({ cast(u8 *)root->token.string, cast(u64)root->token.string_length });
            } break;
            
			// Binary operator evaluation.
            case Calculator__Node_Type_Add:
            case Calculator__Node_Type_Subtract:
            case Calculator__Node_Type_Multiply:
            case Calculator__Node_Type_Divide:
            case Calculator__Node_Type_Modulus:
            case Calculator__Node_Type_RaiseToPower: {
                if (root->left && root->right) {
                    Calculator__Result left_result  = calculator__interpret_expression(context, root->left);
                    Calculator__Result right_result = calculator__interpret_expression(context, root->right);
                    
                    if (left_result.value.type == Calculator__Type_Error) {
                        result = left_result;
                        goto end_interpret;
                    } else if (right_result.value.type == Calculator__Type_Error) {
                        result = right_result;
                        goto end_interpret;
                    } else if (left_result.value.type != Calculator__Type_Number || right_result.value.type != Calculator__Type_Number) {
                        result.value = Calculator__ValueError(string_u8_litexpr("Cannot use non-numbers in expressions."));
                        goto end_interpret;
                    }
                    
					// At this point, both operands have been evaluated successfully, and both are numbers.
					// We can actually compute the result of the operation.
					
                    switch (root->type) {
                        case Calculator__Node_Type_Add:            result.value = Calculator__ValueF64(left_result.value.as_f64 + right_result.value.as_f64);     break;
                        case Calculator__Node_Type_Subtract:       result.value = Calculator__ValueF64(left_result.value.as_f64 - right_result.value.as_f64);     break;
                        case Calculator__Node_Type_Multiply:       result.value = Calculator__ValueF64(left_result.value.as_f64 * right_result.value.as_f64);     break;
                        case Calculator__Node_Type_RaiseToPower:   result.value = Calculator__ValueF64(pow(left_result.value.as_f64, right_result.value.as_f64)); break;
                        
						case Calculator__Node_Type_Divide: {
                            if (right_result.value.as_f64 == 0) {
                                result.value = Calculator__ValueF64(NAN);
                            } else {
                                result.value = Calculator__ValueF64(left_result.value.as_f64 / right_result.value.as_f64);
                            }
                        } break;
                        
						case Calculator__Node_Type_Modulus: {
                            if(right_result.value.as_f64 == 0) {
                                result.value = Calculator__ValueF64(NAN);
                            } else {
                                result.value = Calculator__ValueF64(fmod(left_result.value.as_f64, right_result.value.as_f64));
                            }
                        } break;
						
						default: break;
                    }
                } else {
                    result.value = Calculator__ValueError(string_u8_litexpr("Binary operators require two operands."));
                }
            } break;
            
            case Calculator__Node_Type_Negate: {
                result = calculator__interpret_expression(context, root->operand);
                if (result.value.type == Calculator__Type_Number) {
                    result.value = Calculator__ValueF64(-result.value.as_f64);
                }
            } break;
            
            case Calculator__Node_Type_FunctionCall: {
                result = calculator__call_builtin_function(context, root);
            } break;
            
            case Calculator__Node_Type_Identifier: {
                result.value = Calculator__Symbol_TableLookup(context->symbol_table, root->token.string, root->token.string_length);
                if (result.value.type == Calculator__Type_Error) {
                    result.value = Calculator__ValueError(push_stringf(context->arena, "'%.*s' is not declared.", root->token.string_length, root->token.string));
                }
            } break;
            
            case Calculator__Node_Type_SourceCodeIdentifier: {
                Token_Array token_array = get_token_array_from_buffer(context->app, context->buffer);
                Range_i64 visible_range = text_layout_get_visible_range(context->app, context->text_layout_id);
                i64 first_index         = token_index_from_pos(&token_array, visible_range.first);
                Token_Iterator_Array it = token_iterator_index(0, &token_array, first_index);
                Token *token = 0;
                
                for (;;) {
                    token = token_it_read(&it);
                    
                    if (token->pos >= visible_range.one_past_last + 4096 || !token || !token_it_inc_non_whitespace(&it)) {
                        break;
                    }
                    
                    if (token->kind == TokenBaseKind_Identifier) {
                        String_Const_u8 token_string;
                        {
                            // @Cleanup(ema): Magic numbers.
							Range_i64 token_range = {
                                token->pos,
                                token->pos + (token->size > cast(i64)256
                                              ? cast(i64)256
                                              : token->size),
                            };
                            
                            u8 token_buffer[256] = {};
                            buffer_read_range(context->app, context->buffer, token_range, token_buffer);
                            token_string = { token_buffer, cast(u64)(token_range.end - token_range.start) };
                        }
                        
                        if (strings_match_case_sensitive(cast(char *)token_string.str, cast(int)token_string.size, root->token.string, root->token.string_length)) {
                            result.value = Calculator__ValueSourceCodeReference(token->pos);
                            break;
                        }
                    }
                }
                
				
            } break;
            
            default: break;
        }
    }
    
    end_interpret:;
    return result;
}

// @Cleanup(ema): Use a String_Const_u8 parameter?
internal b32 calculator__identifier_exists_in_expression(Calculator__Node *root, char *string, int string_length) {
    b32 result = false;
    
    if (root && root->type != Calculator__Node_Type_Invalid) {
        if (strings_match_case_sensitive(root->token.string, root->token.string_length, string, string_length)) {
			// Base case.
            result = true;
        } else {
			// Recursive case.
            result |= calculator__identifier_exists_in_expression(root->left,            string, string_length);
            result |= calculator__identifier_exists_in_expression(root->right,           string, string_length);
            result |= calculator__identifier_exists_in_expression(root->first_parameter, string, string_length);
            result |= calculator__identifier_exists_in_expression(root->next,            string, string_length);
        }
    }
    
    return result;
}

internal Calculator__Result calculator__interpret_code(Calculator__Interpreter_Context *context, Calculator__Node *root) {
    Calculator__Result result = {0};
    Calculator__Result last_result = result;
    
    if (root) {
        last_result = result;
        
        if (root->type == Calculator__Node_Type_Error) {
            result.value = Calculator__ValueError(root->error_string);
            goto end_interpret;
        } else if (root->type == Calculator__Node_Type_Assignment) {
            if (root->left->type == Calculator__Node_Type_Identifier) {
                if (!calculator__identifier_exists_in_expression(root->right, root->left->token.string, root->left->token.string_length)) {
                    Calculator__Result right_result = calculator__interpret_expression(context, root->right);
                    calculator__add_to_symbol_table(context->symbol_table, root->left->token.string, root->left->token.string_length, right_result.value);
                    result = calculator__interpret_expression(context, root->right);
                    result.first_graph = last_result.first_graph;
                } else {
                    result.value = Calculator__ValueError(string_u8_litexpr("Recursive definition."));
                    result.first_graph = last_result.first_graph;
                }
            } else {
                result.value = Calculator__ValueError(string_u8_litexpr("Assignment to non-identifier."));
                result.first_graph = last_result.first_graph;
            }
        } else {
            result = calculator__interpret_expression(context, root);
            if (last_result.first_graph) {
				// Copy all graphs from last_result to result.
                for (Calculator__Graph *graph = last_result.first_graph; graph; graph = graph->next) {
                    if (graph->next == 0) {
                        graph->next = result.first_graph;
                        break;
                    }
                }
                
                result.first_graph = last_result.first_graph;
            } else if (result.value.type == Calculator__Type_Error) {
                goto end_interpret;
            }
        }
    }
    
    end_interpret:;
    return result;
}

internal Calculator__Interpreter_Context calculator__init_interpreter_context(Application_Links *app, Buffer_ID buffer, Text_Layout_ID text_layout_id, Arena *arena, Calculator__Symbol_Table *symbol_table, f32 current_time) {
    Calculator__Interpreter_Context context = {0};
    context.app            = app;
    context.buffer         = buffer;
    context.text_layout_id = text_layout_id;
    context.arena          = arena;
    context.symbol_table   = symbol_table;
    context.current_time   = current_time;
    
    // Default plot settings.
    {
        context.plot_title           = string_u8_litexpr("");
        context.x_axis               = string_u8_litexpr("x");
        context.y_axis               = string_u8_litexpr("y");
        context.plot_view            = Rf32(-1, -1, +1, +1);
        context.num_function_samples = 128;
        context.num_bins             = 10;
        context.bin_range_low        = -1;
        context.bin_range_high       =  1;
    }
    
    return context;
}

//~ Rendering code.

// Renders a portion of calculator code into a view. The code could either come from a *calc* buffer or from a calc comment (a comment starting with 'c').
// @Cleanup: Why aren't you passing a String_Const_u8 for the code buffer?
internal void calculator__render_code(Application_Links *app, Buffer_ID buffer, View_ID view, Text_Layout_ID text_layout_id, Frame_Info frame_info, Arena *arena, char *code_buffer, i64 start_char_offset) {
    ProfileScope(app, "[Custom] Render Calculator Code");
    
	// Make an interpret context.
	Calculator__Interpreter_Context *context = 0;
	{
		f32 current_time = global_calc_time;
		Calculator__Symbol_Table symbol_table = calculator__init_symbol_table(arena, 1024); // @Cleanup: Magic numbers
		
		// Add default symbols.
		{
			// Pi
			{
				Calculator__Value value = Calculator__ValueF64(3.1415926535897);
				calculator__add_to_symbol_table(&symbol_table, "pi", 2, value);
			}
			
			// e
			{
				Calculator__Value value = Calculator__ValueF64(2.71828);
				calculator__add_to_symbol_table(&symbol_table, "e", 1, value);
			}
			
#define Expand_String_Lit(s) (s), (sizeof(s) - 1)
			
			calculator__add_to_symbol_table(&symbol_table, Expand_String_Lit("e"), Calculator__ValueF64(44.0 / 7.0));
			
#undef Expand_String_Lit
		}
		
		// @Rename: make_interpret_context.
		Calculator__Interpreter_Context context_ = calculator__init_interpreter_context(app, buffer, text_layout_id, arena, &symbol_table, current_time);
		context = &context_;
    }
	
    char *at = code_buffer;
    Calculator__Node *expr = calculator__parse_code(arena, &at);
    
    Rect_f32 last_graph_rect = {};
    
    for (Calculator__Node *interpret_expression = expr; interpret_expression; interpret_expression = interpret_expression->next) {
        char *at_source = interpret_expression->at_source;
        
        // Find starting result layout position.
        Vec2_f32 result_layout_position = {};
        if (at_source) {
            i64 offset = cast(i64)(at_source - code_buffer);
            for (int i = 0; at_source[i] && at_source[i] != '\n'; i += 1) {
                offset += 1;
            }
            i64 buffer_offset = start_char_offset + offset;
            Rect_f32 last_character_rect = text_layout_character_on_screen(app, text_layout_id, buffer_offset);
            result_layout_position.x = last_character_rect.x0;
            result_layout_position.y = last_character_rect.y0;
            result_layout_position.x += 20;
        }
        
        Calculator__Result result = calculator__interpret_code(context, interpret_expression);
        
        if (result_layout_position.x > 0 && result_layout_position.y > 0) {
            // Draw result, if there's one.
            {
                String_Const_u8 result_string = {0};
                
                switch (result.value.type) {
                    case Calculator__Type_Error: {
                        if (expr == 0 || !result.value.as_error.size) {
                            result_string = push_stringf(arena, "(error: Parse failure.)");
                        } else {
                            result_string = push_stringf(arena, "(error: %.*s)", string_expand(result.value.as_error));
                        }
                    } break;
					
                    case Calculator__Type_Number: {
                        result_string = push_stringf(arena, "= %f", result.value.as_f64);
                    } break;
					
                    case Calculator__Type_String: {
                        result_string = push_stringf(arena, "= %.*s", string_expand(result.value.as_string));
                    } break;
					
                    default: break;
                }
                
                Vec2_f32 point = result_layout_position;
                
                u32 color = finalize_color(defcolor_comment, 0);
                color &= 0x00ffffff;
                color |= 0x80000000; // @Cleanup: Magic numbers.
                draw_string(app, get_face_id(app, buffer), result_string, point, color);
            }
            
            // Draw graphs.
            {
                Rect_f32 view_rect = view_get_screen_rect(app, view);
                
                Rect_f32 graph_rect = {};
                {
                    graph_rect.x0 = view_rect.x1 - 30 - 300;
                    graph_rect.y0 = result_layout_position.y + 30 - 100;
                    graph_rect.x1 = graph_rect.x0 + 300;
                    graph_rect.y1 = graph_rect.y0 + 200;
                }
                
                Calculator__Node *last_parent_call = 0;
                for (Calculator__Graph *graph = result.first_graph; graph; graph = graph->next) {
                    if (last_parent_call == 0 || graph->parent_call != last_parent_call) {
                        if (last_graph_rect.x0 != 0 && rect_overlap(graph_rect, last_graph_rect)) {
                            graph_rect.y0 = last_graph_rect.y1 + 50;
                            graph_rect.y1 = graph_rect.y0 + 200;
                        }
                        
                        last_graph_rect = graph_rect;
                        
                        calculator__graph_expression(app, get_face_id(app, buffer), graph_rect, graph, context);
                        
                        // Bump graph rect forward.
                        {
                            f32 rect_height = graph_rect.y1 - graph_rect.y0;
                            graph_rect.y0 += rect_height + 50;
                            graph_rect.y1 += rect_height + 50;
                            result_layout_position.y += rect_height + 50;
                        }
                        
                        last_parent_call = graph->parent_call;
                    }
                }
            }
        }
    }
}

// Wrapper around render_code. Renders the whole *calc* buffer.
internal void calculator__render_buffer(Application_Links *app, Buffer_ID buffer, View_ID view, Text_Layout_ID text_layout_id, Frame_Info frame_info) {
    Scratch_Block scratch(app);
	
    Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
    String_Const_u8 code_string = push_whole_buffer(app, scratch, buffer);
    calculator__render_code(app, buffer, view, text_layout_id, frame_info, scratch, cast(char *)code_string.str, visible_range.start);
}

// Wrapper around render_code. Renders each individual calc comment.
internal void calculator__render_comments(Application_Links *app, Buffer_ID buffer, View_ID view, Text_Layout_ID text_layout_id, Frame_Info frame_info) {
    if (def_get_config_b32(vars_save_string_lit("f4_disable_calc_comments"))) {
        return;
    }
    
    ProfileScope(app, "[Custom] Calculator Comments");
    
    Scratch_Block scratch(app);
    Token_Array token_array = get_token_array_from_buffer(app, buffer);
    Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
    
    if (token_array.tokens) {
        i64 first_index = token_index_from_pos(&token_array, visible_range.first);
        Token_Iterator_Array it = token_iterator_index(0, &token_array, first_index);
        
        Token *token = 0;
        for (;;) {
            token = token_it_read(&it);
            
            if (token->pos >= visible_range.one_past_last || !token || !token_it_inc_non_whitespace(&it)) {
                break;
            }
            
            if (token->kind == TokenBaseKind_Comment) {
                Range_i64 token_range = {
                    token->pos,
                    token->pos + (token->size > 1024 // @Cleanup: this is just a clamp_top
                                  ? 1024
                                  : token->size),
                };
                
                u32 token_buffer_size = cast(u32)(token_range.end - token_range.start);
                if (token_buffer_size < 4) { // @Cleanup: This is a clamp_bottom
                    token_buffer_size = 4;
                }
				
                u8 *token_buffer = push_array(scratch, u8, token_buffer_size + 1);
                buffer_read_range(app, buffer, token_range, token_buffer);
                token_buffer[token_buffer_size] = 0;
                
                if ((token_buffer[0] == '/' && token_buffer[1] == '/' && token_buffer[2] == 'c' && character_is_whitespace(token_buffer[3])) ||
					(token_buffer[0] == '/' && token_buffer[1] == '*' && token_buffer[2] == 'c')) {
					b32 is_multiline_comment = (token_buffer[1] == '*');
                    if (is_multiline_comment) {
                        if (token_buffer[token_buffer_size - 2] == '*' && token_buffer[token_buffer_size - 1] == '/') {
                            token_buffer[token_buffer_size - 2] = 0;
                        }
                    }
                    char *at = cast(char *)token_buffer + 3;
                    calculator__render_code(app, buffer, view, text_layout_id, frame_info, scratch, at, token_range.start + 3);
                }
            }
        }
    }
}

NAMESPACE_END()

#endif // FCODER_CUSTOM_CALC_CPP
