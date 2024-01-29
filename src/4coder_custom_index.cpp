#ifndef FCODER_CUSTOM_INDEX_CPP
#define FCODER_CUSTOM_INDEX_CPP

NAMESPACE_BEGIN(nne)

global Index__State code_index = {};

function void index__initialize(void) {
    code_index.mutex = system_mutex_make();
    code_index.arena = make_arena_system(KB(16));
}

function void index__lock(void) {
    system_mutex_acquire(code_index.mutex);
}

function void index__unlock(void) {
    system_mutex_release(code_index.mutex);
}

//~ Utils

function String_Const_u8 index__string_from_range(Index__Parse_Context *context, Range_i64 range) {
    String_Const_u8 string = string_substring(context->string, range);
    return string;
}

function String_Const_u8 index__string_from_token(Index__Parse_Context *context, Token *token) {
    return index__string_from_range(context, Ii64(token));
}

//~ File Management

function u64 index__get_file_hash_internal(Application_Links *app, Buffer_ID id) {
    Scratch_Block scratch(app);
    String_Const_u8 unique_name = push_buffer_unique_name(app, scratch, id);
	
	u64 hash = table_hash_u8(unique_name.str, unique_name.size);
    return hash;
}

function Index__File *index__lookup_file_internal(Application_Links *app, u64 hash, Buffer_ID buffer) {
    Index__File *result = 0;
    
	u64 slot = hash % ArrayCount(code_index.file_table);
    for (Index__File *file = code_index.file_table[slot]; file; file = file->hash_next) {
        if (file->buffer == buffer) {
            result = file;
            break;
        }
    }
    
	return result;
}

function Index__File *index__lookup_file(Application_Links *app, Buffer_ID buffer) {
	u64          hash = index__get_file_hash_internal(app, buffer);
    Index__File *file = index__lookup_file_internal(app, hash, buffer);
	
	return file;
}

function Index__File *index__lookup_or_make_file(Application_Links *app, Buffer_ID buffer) {
    Index__File *result = 0;
    
	u64 hash = index__get_file_hash_internal(app, buffer);
    u64 slot = hash % ArrayCount(code_index.file_table);
	
	result = index__lookup_file_internal(app, hash, buffer);
	if (!result) {
        if (code_index.free_file) {
            result = code_index.free_file;
            code_index.free_file = code_index.free_file->hash_next;
            memset(result, 0, sizeof(*result));
        } else {
            result = push_array_zero(&code_index.arena, Index__File, 1);
        }
        
        if (result) {
            result->hash_next = code_index.file_table[slot];
            code_index.file_table[slot] = result;
            result->buffer = buffer;
            result->arena = make_arena_system(KB(16));
        }
    }
    
    return result;
}

function void index__erase_file(Application_Links *app, Buffer_ID id) {
    u64          hash = index__get_file_hash_internal(app, id);
    Index__File *file = index__lookup_file_internal(app, hash, id);
    if (file) {
        u64 slot = hash % ArrayCount(code_index.file_table);
        {
            Index__File *prev = 0;
            for (Index__File *hash_file = code_index.file_table[slot]; hash_file; prev = hash_file, hash_file = hash_file->hash_next) {
                if (file == hash_file) {
                    if (prev) {
                        prev->hash_next = file->hash_next;
                    } else {
                        code_index.file_table[slot] = file->hash_next;
                    }
                    break;
                }
            }
        }
        file->hash_next = code_index.free_file;
        code_index.free_file = file;
    }
}

//~ Note Management

function void index__free_note_tree_internal(Index__Note *note) {
    for (Index__Note *child = note->first_child; child; child = child->next_sibling) {
        index__free_note_tree_internal(child);
    }
    
    Index__Note *prev = note->prev;
    Index__Note *next = note->next;
    Index__Note *hash_prev = note->hash_prev;
    Index__Note *hash_next = note->hash_next;
    
    u64 hash = note->hash;
    u64 slot = hash % ArrayCount(code_index.note_table);
    
    if (prev) {
        prev->next = next;
    }
    if (next) {
        next->prev = prev;
    }
    
    if (prev == 0) {
        if (next) {
            next->hash_prev = hash_prev;
            next->hash_next = hash_next;
            if (hash_prev) {
                hash_prev->hash_next = next;
            }
            if (hash_next) {
                hash_next->hash_prev = next;
            }
        } else {
            if (hash_prev) {
                hash_prev->hash_next = hash_next;
            }
            if (hash_next) {
                hash_next->hash_prev = hash_prev;
            }
        }
        
        if (hash_prev == 0) {
            code_index.note_table[slot] = next ? next : hash_next;
        }
    }
}

// Removes and frees all the notes in a file.
function void index__clear_file(Index__File *file) {
    if (file) {
        file->generation += 1;
        for (Index__Note *note = file->first_note; note; note = note->next_sibling) {
            index__free_note_tree_internal(note);
        }
		
        linalloc_clear(&file->arena);
        file->first_note = 0;
		file->last_note  = 0;
    }
}

function Index__Note *index__lookup_note(String_Const_u8 string, Index__Note *parent) {
    Index__Note *result = 0;
    
	u64 hash = table_hash_u8(string.str, string.size);
    u64 slot = hash % ArrayCount(code_index.note_table);
    for (Index__Note *note = code_index.note_table[slot]; note; note = note->hash_next) {
        if (note->hash == hash && note->parent == parent) {
            if (string_match(string, note->string)) {
                result = note;
                break;
            }
        }
    }
	
    return result;
}

function Index__Note *index__lookup_note(String_Const_u8 string) {
    return index__lookup_note(string, 0);
}

function Index__Note *index__allocate_note(void) {
    Index__Note *result = 0;
	
    if (code_index.free_note) {
        result = code_index.free_note;
        code_index.free_note = code_index.free_note->hash_next;
        memset(result, 0, sizeof(*result));
    } else {
        result = push_array_zero(&code_index.arena, Index__Note, 1);
    }
	
    return result;
}

function void index__insert_note(Index__Parse_Context *context, Index__Note *note, Range_i64 name_range, Index__Note_Kind note_kind, Index__Note_Flags note_flags) {
    Index__File    *file   = context->file;
    Index__Note    *parent = context->active_parent;
    String_Const_u8 string = index__string_from_range(context, name_range);
    Range_i64       range  = name_range;
    
    if (file) {
        u64 hash = table_hash_u8(string.str, string.size);
        u64 slot = hash % ArrayCount(code_index.note_table);
        
        // NOTE(rjf): Push to duplicate chain.
        {
            Index__Note *list_head = index__lookup_note(string);
            Index__Note *list_tail = list_head;
            for (Index__Note *note = list_tail; note; list_tail = note, note = note->next)
			{ }
            
			if (list_tail != 0) {
                list_tail->next = note;
                note->prev = list_tail;
                note->hash_next = 0;
                note->hash_prev = 0;
            } else {
                note->hash_next = code_index.note_table[slot];
                if (code_index.note_table[slot]) {
                    code_index.note_table[slot]->hash_prev = note;
                }
                code_index.note_table[slot] = note;
                note->hash_prev = 0;
                note->prev = 0;
            }
        }
        note->next = 0;
        
        // NOTE(rjf): Push to tree.
        {
            note->parent = parent;
            if (parent) {
                note->prev_sibling = parent->last_child;
                note->next_sibling = 0;
                if (parent->last_child == 0) {
                    parent->first_child = parent->last_child = note;
                } else {
                    parent->last_child->next_sibling = note;
                    parent->last_child = parent->last_child->next_sibling;
                }
            } else {
                note->prev_sibling = file->last_note;
                note->next_sibling = 0;
                if (file->last_note == 0) {
                    file->first_note = file->last_note = note;
                } else {
                    file->last_note->next_sibling = note;
                    file->last_note = file->last_note->next_sibling;
                }
            }
        }
        
        // NOTE(rjf): Fill out data.
        {
            note->hash   = hash;
            note->string = push_string_copy(&file->arena, string);
            note->kind   = note_kind;
            note->flags  = note_flags;
            note->range  = range;
            note->file   = file;
            note->file_generation = file->generation;
        }
    }
}

// Allocates, inserts and returns a note.
function Index__Note *index__make_note(Index__Parse_Context *context, Range_i64 name_range, Index__Note_Kind note_kind, Index__Note_Flags note_flags) {
    Index__Note *result = index__allocate_note();
    index__insert_note(context, result, name_range, note_kind, note_flags);
    return result;
}

function Index__Note *index__push_parent_note(Index__Parse_Context *context, Index__Note *new_parent) {
    Index__Note *prev_parent = context->active_parent;
    context->active_parent = new_parent;
	
    return prev_parent;
}

function void index__pop_parent_note(Index__Parse_Context *context, Index__Note *last_parent) {
    context->active_parent = last_parent;
}

//~ Parsing

function void index__parse_file_internal(Application_Links *app, Index__File *file, String_Const_u8 string, Token_Array tokens, F4_Language *language) {
    if (language != 0) {
        Index__Parse_Context context = {
			false,
			app,
			file,
			string,
			tokens,
			token_iterator_pos(0, &context.tokens, 0),
		};
		
		language->file_indexer(&context);
    }
}

// Uses the file's language-specific callbacks to parse the file.
function void index__parse_file(Application_Links *app, Index__File *file, String_Const_u8 string, Token_Array tokens) {
    index__lock();
	
    F4_Language *lang = language_from_buffer(app, file->buffer);
    index__parse_file_internal(app, file, string, tokens, lang);
    
	index__unlock();
}

// @Rename(ema): "inc" == "increment" ??
// Better name: "advance", maybe.
function b32 index__parse_context_inc(Index__Parse_Context *context, Index__Token_Skip_Flags flags) {
    if (flags & Index__Token_Skip_Flag_Skip_Whitespace) {
        context->done = !token_it_inc_non_whitespace(&context->it);
    } else {
        context->done = !token_it_inc_all(&context->it);
    }
	
    return context->done;
}

function b32 index__require_token(Index__Parse_Context *context, String_Const_u8 string, Index__Token_Skip_Flags flags) {
    b32    found = false;
    Token *token = token_it_read(&context->it);
    if (token) {
        String_Const_u8 token_string = string_substring(context->string, Ii64(token->pos, token->pos+token->size));
        if (string_match(string, token_string)) {
			found = true;
        }
    } else {
        context->done = true;
    }
	
    if (found) {
        index__parse_context_inc(context, flags);
    }
	
    return found;
}

function b32 index__require_token_kind(Index__Parse_Context *context, Token_Base_Kind kind, Token **token_out, Index__Token_Skip_Flags flags) {
    b32    found = false;
    Token *token = token_it_read(&context->it);
    if (token) {
        if (token->kind == kind) {
			found = true;
            if (token_out) {
                *token_out = token;
            }
        }
    } else {
        context->done = true;
    }
	
	if (found) {
        index__parse_context_inc(context, flags);
    }
	
    return found;
}

function b32 index__require_token_subkind(Index__Parse_Context *context, int sub_kind, Token **token_out, Index__Token_Skip_Flags flags) {
    b32    found = false;
    Token *token = token_it_read(&context->it);
    if (token) {
        if (token->sub_kind == sub_kind) {
			found = true;
            if (token_out) {
                *token_out = token;
            }
        }
    } else {
        context->done = true;
    }
	
	if (found) {
        index__parse_context_inc(context, flags);
    }
	
    return found;
}

function b32 index__peek_token(Index__Parse_Context *context, String_Const_u8 string) {
    b32    found = false;
    Token *token = token_it_read(&context->it);
    if (token) {
        String_Const_u8 token_string =
            string_substring(context->string, Ii64(token->pos, token->pos + token->size));
        if (string_match(string, token_string)) {
			found = true;
        }
    } else {
        context->done = true;
    }
	
    return found;
}

function b32 index__peek_token_kind(Index__Parse_Context *context, Token_Base_Kind kind, Token **token_out) {
    b32    found = false;
    Token *token = token_it_read(&context->it);
    if (token) {
        if (token->kind == kind) {
			found = true;
			if (token_out) {
				*token_out = token;
			}
		}
    } else {
        context->done = true;
    }
	
    return found;
}

function void index__parse_comment(Index__Parse_Context *context, Token *token) {
    String_Const_u8 string = index__string_from_token(context, token);
    
    for (u64 i = 0; i < string.size; i += 1) {
        if (string.str[i] == '@') {
            Range_i64 range = Ii64(token);
            range.min += i;
            index__make_note(context, range, Index__Note_Kind_Comment_Tag, 0);
            break;
        } else if (i+4 < string.size && string_match(S8Lit("TODO"), string_substring(string, Ii64(i, i + 4)))) {
            Range_i64 range = Ii64(token);
            range.min += i;
            index__make_note(context, range, Index__Note_Kind_Comment_ToDo, 0);
        }
    }
}

function void index__skip_soft_tokens(Index__Parse_Context *context, b32 preproc) {
    for (; !context->done; ) {
        Token *token = token_it_read(&context->it);
        if (preproc) {
            if (!(token->flags & TokenBaseFlag_PreprocessorBody) ||
				token->kind == TokenBaseKind_Preprocessor) {
                break;
            }
        } else {
            if (token->kind == TokenBaseKind_StatementClose ||
				token->kind == TokenBaseKind_ScopeOpen ||
				token->kind == TokenBaseKind_ParentheticalOpen) {
                break;
            }
        }
		
        if (!token_it_inc_non_whitespace(&context->it)) {
            break;
        }
    }
}

// Skips operators, also handling opening and closing parentheses
function void index__skip_operators(Index__Parse_Context *context) {
    int paren_nest = 0;
    for (; !context->done; ) {
        Token *token = token_it_read(&context->it);
        if (token->kind == TokenBaseKind_ParentheticalOpen) {
            paren_nest += 1;
        } else if (token->kind == TokenBaseKind_ParentheticalClose) {
            paren_nest -= 1;
            if (paren_nest < 0) {
                paren_nest = 0;
            }
        } else if (token->kind != TokenBaseKind_Operator && paren_nest == 0) {
            break;
        }
		
        index__parse_context_inc(context, Index__Token_Skip_Flag_Skip_Whitespace);
    }
}

function b32 index__parse_pattern(Index__Parse_Context *context, char *fmt, ...) {
    b32 parsed = true;
    
    Index__Parse_Context context_restore = *context;
    Index__Token_Skip_Flags flags = Index__Token_Skip_Flag_Skip_Whitespace;
    
    va_list args;
    va_start(args, fmt);
    for (int i = 0; fmt[i]; ) {
        if (fmt[i] == '%') {
            switch (fmt[i + 1]) {
                // %t -> token, requires char * specifying token string
				case 't': {
                    char *cstring = va_arg(args, char *);
                    String8 string = SCu8((u8 *)cstring, cstring_length(cstring));
					
                    parsed = parsed && index__require_token(context, string, flags);
                } break;
                
				// %k -> token kind, requires Token_Base_Kind and Token ** for output token
                case 'k': {
                    Token_Base_Kind kind = (Token_Base_Kind)va_arg(args, int);
                    Token **output_token = va_arg(args, Token **);
					
                    parsed = parsed && index__require_token_kind(context, kind, output_token, flags);
                } break;
                
				// %b -> token subkind, requires token subkind and Token ** for output token
                case 'b': {
                    i16 kind = (i16)va_arg(args, int);
                    Token **output_token = va_arg(args, Token **);
					
                    parsed = parsed && index__require_token_subkind(context, kind, output_token, flags);
                } break;
                
				// %n -> note, requires Index__Note_Kind and Index__Note ** for output note
                case 'n': {
                    Index__Note_Kind kind = (Index__Note_Kind)va_arg(args, int);
                    Index__Note **output_note = va_arg(args, Index__Note **);
					
                    Token *token = 0;
                    parsed = parsed && index__require_token_kind(context, TokenBaseKind_Identifier, &token, flags);
                    parsed = parsed && !!token;
					
                    if (parsed) {
                        String8 token_string = index__string_from_token(context, token);
                        Index__Note *note = index__lookup_note(token_string, 0);
                        b32 kind_match = false;
                        for (Index__Note *n = note; n; n = n->next) {
                            if (n->kind == kind) {
                                kind_match = true;
                                note = n;
                                break;
                            }
                        }
						
                        if (note && kind_match) {
                            *output_note = note;
                            parsed = true;
                        } else {
                            parsed = false;
                        }
                    }
                } break;
                
				// %s -> soft group, requires no arguments
                case 's': { index__skip_soft_tokens(context, 0); } break;
                
				// %o -> operator group, requires no arguments
                case 'o': { index__skip_operators(context); } break;
                
                default: break;
            }
			
            i += 1;
        } else {
            i += 1;
        }
    }
    
    va_end(args);
    
    if (!parsed) {
        *context = context_restore;
    }
    return parsed;
}

//~ Tick

function void index__tick(Application_Links *app) {
    Scratch_Block scratch(app);
	
    for (Buffer_Modified_Node *node = global_buffer_modified_set.first; node != 0;node = node->next) {
        Temp_Memory_Block temp(scratch); // @Unused(ema) ??
        
        Buffer_ID buffer_id = node->buffer;
        String_Const_u8 contents = push_whole_buffer(app, scratch, buffer_id);
        Token_Array tokens = get_token_array_from_buffer(app, buffer_id);
        if (tokens.count == 0) {
			continue;
		}
        
		{
			// Reparse file.
			// @Note(ema): Doesn't parse_file already lock and unlock the index?
			
			index__lock();
			Index__File *file = index__lookup_or_make_file(app, buffer_id);
			if (file) {
				ProfileScope(app, "[f] reparse");
				index__clear_file(file);
				index__parse_file(app, file, contents, tokens);
			}
			index__unlock();
		}
		
        buffer_clear_layout_cache(app, buffer_id);
    }
}

NAMESPACE_END() // nne

#endif // FCODER_CUSTOM_INDEX_CPP
