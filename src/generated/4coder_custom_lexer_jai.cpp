#if !defined(FCODER_LEX_GEN_HAND_WRITTEN)
#define FCODER_LEX_GEN_HAND_WRITTEN

internal u64
lexeme_hash(u64 seed, u8 *ptr, u64 size){
    u64 result = 0;
    for (u64 i = 0; i < size; i += 1, ptr += 1){
        result ^= ((*ptr) ^ result*59) + seed;
    }
    return(result);
}

internal Lexeme_Table_Lookup
lexeme_table_lookup(u64 *hash_array, String_Const_u8 *key_array, 
                    Lexeme_Table_Value *value_array, i32 slot_count, u64 seed,
                    u8 *ptr, u64 size){
    Lexeme_Table_Lookup result = {};
    u64 hash = lexeme_hash(seed, ptr, size);
    u64 comparison_hash = hash | 1;
    i32 first_index = (hash % slot_count);
    i32 index = first_index;
    for (;;){
        if (hash_array[index] == comparison_hash){
            if (string_match(SCu8(ptr, size), key_array[index])){
                result.found_match = true;
                result.base_kind = value_array[index].base_kind;
                result.sub_kind = value_array[index].sub_kind;
                break;
            }
        }
        else if (hash_array[index] == 0){
            break;
        }
        index += 1;
        if (index == slot_count){
            index = 0;
        }
        if (index == first_index){
            break;
        }
    }
    return(result);
}

#endif
u64 jai_main_keys_hash_array[89] = {
0x0000000000000000,0x54bd563d3b398c9f,0x0f34e9edf49cc329,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x413526a9721c37e7,
0x0000000000000000,0x413526a9721e4cdf,0xa32127d50d7a05a9,0x0000000000000000,
0x0000000000000000,0x9361a260fd3bb6f9,0x0000000000000000,0xd059615c40125d37,
0x0000000000000000,0x9361a260fd3bb6fd,0xa32127d50d7fa661,0xa32127d50d248915,
0x413526a9722005bd,0x0000000000000000,0x413526a9721e9d3b,0x2ef6c88e0df6dfbb,
0x9361a260fd3bb069,0x0000000000000000,0xd059615c3e2c9e2f,0xa32127d50d7a05b9,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x5332eb8389a3b81b,0x0000000000000000,
0xd059615c39a9806b,0x0000000000000000,0x9361a260fd3bb077,0x0000000000000000,
0x0f34e9ed08426a4b,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0f34e9ef2a7d1deb,0xa32127d50d7cd095,
0x0000000000000000,0x5332e8ce7e933e03,0x54a281e63c075d59,0xd059615c3e22e725,
0x0000000000000000,0x0f34e9ee94fdf1eb,0x0000000000000000,0x0000000000000000,
0x0f34e9edf49c994d,0x413526a9721d0ef3,0x413526a9721ec76f,0x0000000000000000,
0xa32127d50d339a25,0x0f34e9edf3c00279,0x54bd761ef0fd6d3d,0x5332ebabb3815e37,
0x0000000000000000,0xa32127d50d79fac1,0xd059615c4d33f745,0x5332e8e76bba403b,
0x5332ebb1802af7bb,0x5332e8e76bba40ef,0x0000000000000000,0xa32127d50d6570d3,
0x0000000000000000,0x413526a9721d0eab,0x9361a260fd3bb7e7,0x0000000000000000,
0x413526a9721d0da3,0xd059615c43e56aab,0xd059615c4d140e15,0x9361a260fd3bb30d,
0x0000000000000000,0x413526a9721d72d3,0x0f34e9ed08f13b8d,0x413526a9721d74eb,
0x0000000000000000,0x413526a9721d743b,0xa32127d50d30a459,0x0000000000000000,
0x0000000000000000,
};
u8 jai_main_keys_key_array_1[] = {0x6f,0x70,0x65,0x72,0x61,0x74,0x6f,0x72,};
u8 jai_main_keys_key_array_2[] = {0x73,0x74,0x72,0x75,0x63,0x74,};
u8 jai_main_keys_key_array_7[] = {0x41,0x6e,0x79,};
u8 jai_main_keys_key_array_9[] = {0x66,0x6f,0x72,};
u8 jai_main_keys_key_array_10[] = {0x63,0x61,0x73,0x74,};
u8 jai_main_keys_key_array_13[] = {0x73,0x38,};
u8 jai_main_keys_key_array_15[] = {0x62,0x72,0x65,0x61,0x6b,};
u8 jai_main_keys_key_array_17[] = {0x75,0x38,};
u8 jai_main_keys_key_array_18[] = {0x65,0x6e,0x75,0x6d,};
u8 jai_main_keys_key_array_19[] = {0x67,0x6f,0x74,0x6f,};
u8 jai_main_keys_key_array_20[] = {0x2d,0x2d,0x2d,};
u8 jai_main_keys_key_array_22[] = {0x69,0x6e,0x74,};
u8 jai_main_keys_key_array_23[] = {0x70,0x75,0x73,0x68,0x5f,0x63,0x6f,0x6e,0x74,0x65,0x78,0x74,};
u8 jai_main_keys_key_array_24[] = {0x69,0x74,};
u8 jai_main_keys_key_array_26[] = {0x75,0x6e,0x69,0x6f,0x6e,};
u8 jai_main_keys_key_array_27[] = {0x63,0x61,0x73,0x65,};
u8 jai_main_keys_key_array_34[] = {0x64,0x65,0x66,0x61,0x75,0x6c,0x74,};
u8 jai_main_keys_key_array_36[] = {0x77,0x68,0x69,0x6c,0x65,};
u8 jai_main_keys_key_array_38[] = {0x69,0x66,};
u8 jai_main_keys_key_array_40[] = {0x72,0x65,0x6d,0x6f,0x76,0x65,};
u8 jai_main_keys_key_array_46[] = {0x69,0x6e,0x6c,0x69,0x6e,0x65,};
u8 jai_main_keys_key_array_47[] = {0x65,0x6c,0x73,0x65,};
u8 jai_main_keys_key_array_49[] = {0x61,0x6c,0x69,0x67,0x6e,0x6f,0x66,};
u8 jai_main_keys_key_array_50[] = {0x63,0x6f,0x6e,0x74,0x69,0x6e,0x75,0x65,};
u8 jai_main_keys_key_array_51[] = {0x75,0x73,0x69,0x6e,0x67,};
u8 jai_main_keys_key_array_53[] = {0x64,0x65,0x6c,0x65,0x74,0x65,};
u8 jai_main_keys_key_array_56[] = {0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 jai_main_keys_key_array_57[] = {0x73,0x31,0x36,};
u8 jai_main_keys_key_array_58[] = {0x6e,0x65,0x77,};
u8 jai_main_keys_key_array_60[] = {0x76,0x6f,0x69,0x64,};
u8 jai_main_keys_key_array_61[] = {0x73,0x77,0x69,0x74,0x63,0x68,};
u8 jai_main_keys_key_array_62[] = {0x69,0x74,0x5f,0x69,0x6e,0x64,0x65,0x78,};
u8 jai_main_keys_key_array_63[] = {0x73,0x69,0x7a,0x65,0x5f,0x6f,0x66,};
u8 jai_main_keys_key_array_65[] = {0x62,0x6f,0x6f,0x6c,};
u8 jai_main_keys_key_array_66[] = {0x66,0x6c,0x6f,0x61,0x74,};
u8 jai_main_keys_key_array_67[] = {0x66,0x6c,0x6f,0x61,0x74,0x36,0x34,};
u8 jai_main_keys_key_array_68[] = {0x63,0x6f,0x6e,0x74,0x65,0x78,0x74,};
u8 jai_main_keys_key_array_69[] = {0x66,0x6c,0x6f,0x61,0x74,0x33,0x32,};
u8 jai_main_keys_key_array_71[] = {0x6e,0x75,0x6c,0x6c,};
u8 jai_main_keys_key_array_73[] = {0x73,0x36,0x34,};
u8 jai_main_keys_key_array_74[] = {0x78,0x78,};
u8 jai_main_keys_key_array_76[] = {0x73,0x33,0x32,};
u8 jai_main_keys_key_array_77[] = {0x64,0x65,0x66,0x65,0x72,};
u8 jai_main_keys_key_array_78[] = {0x66,0x61,0x6c,0x73,0x65,};
u8 jai_main_keys_key_array_79[] = {0x64,0x6f,};
u8 jai_main_keys_key_array_81[] = {0x75,0x31,0x36,};
u8 jai_main_keys_key_array_82[] = {0x72,0x65,0x74,0x75,0x72,0x6e,};
u8 jai_main_keys_key_array_83[] = {0x75,0x33,0x32,};
u8 jai_main_keys_key_array_85[] = {0x75,0x36,0x34,};
u8 jai_main_keys_key_array_86[] = {0x74,0x72,0x75,0x65,};
String_Const_u8 jai_main_keys_key_array[89] = {
{0, 0},
{jai_main_keys_key_array_1, 8},
{jai_main_keys_key_array_2, 6},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{jai_main_keys_key_array_7, 3},
{0, 0},
{jai_main_keys_key_array_9, 3},
{jai_main_keys_key_array_10, 4},
{0, 0},
{0, 0},
{jai_main_keys_key_array_13, 2},
{0, 0},
{jai_main_keys_key_array_15, 5},
{0, 0},
{jai_main_keys_key_array_17, 2},
{jai_main_keys_key_array_18, 4},
{jai_main_keys_key_array_19, 4},
{jai_main_keys_key_array_20, 3},
{0, 0},
{jai_main_keys_key_array_22, 3},
{jai_main_keys_key_array_23, 12},
{jai_main_keys_key_array_24, 2},
{0, 0},
{jai_main_keys_key_array_26, 5},
{jai_main_keys_key_array_27, 4},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{jai_main_keys_key_array_34, 7},
{0, 0},
{jai_main_keys_key_array_36, 5},
{0, 0},
{jai_main_keys_key_array_38, 2},
{0, 0},
{jai_main_keys_key_array_40, 6},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{jai_main_keys_key_array_46, 6},
{jai_main_keys_key_array_47, 4},
{0, 0},
{jai_main_keys_key_array_49, 7},
{jai_main_keys_key_array_50, 8},
{jai_main_keys_key_array_51, 5},
{0, 0},
{jai_main_keys_key_array_53, 6},
{0, 0},
{0, 0},
{jai_main_keys_key_array_56, 6},
{jai_main_keys_key_array_57, 3},
{jai_main_keys_key_array_58, 3},
{0, 0},
{jai_main_keys_key_array_60, 4},
{jai_main_keys_key_array_61, 6},
{jai_main_keys_key_array_62, 8},
{jai_main_keys_key_array_63, 7},
{0, 0},
{jai_main_keys_key_array_65, 4},
{jai_main_keys_key_array_66, 5},
{jai_main_keys_key_array_67, 7},
{jai_main_keys_key_array_68, 7},
{jai_main_keys_key_array_69, 7},
{0, 0},
{jai_main_keys_key_array_71, 4},
{0, 0},
{jai_main_keys_key_array_73, 3},
{jai_main_keys_key_array_74, 2},
{0, 0},
{jai_main_keys_key_array_76, 3},
{jai_main_keys_key_array_77, 5},
{jai_main_keys_key_array_78, 5},
{jai_main_keys_key_array_79, 2},
{0, 0},
{jai_main_keys_key_array_81, 3},
{jai_main_keys_key_array_82, 6},
{jai_main_keys_key_array_83, 3},
{0, 0},
{jai_main_keys_key_array_85, 3},
{jai_main_keys_key_array_86, 4},
{0, 0},
{0, 0},
};
Lexeme_Table_Value jai_main_keys_value_array[89] = {
{0, 0},
{4, TokenJaiKind_Operator},
{4, TokenJaiKind_Struct},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenJaiKind_Any},
{0, 0},
{4, TokenJaiKind_For},
{4, TokenJaiKind_Cast},
{0, 0},
{0, 0},
{4, TokenJaiKind_S8},
{0, 0},
{4, TokenJaiKind_Break},
{0, 0},
{4, TokenJaiKind_U8},
{4, TokenJaiKind_Enum},
{4, TokenJaiKind_Goto},
{4, TokenJaiKind_Uninitialized},
{0, 0},
{4, TokenJaiKind_Int},
{4, TokenJaiKind_PushContext},
{4, TokenJaiKind_It},
{0, 0},
{4, TokenJaiKind_Union},
{4, TokenJaiKind_Case},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenJaiKind_Default},
{0, 0},
{4, TokenJaiKind_While},
{0, 0},
{4, TokenJaiKind_If},
{0, 0},
{4, TokenJaiKind_Remove},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenJaiKind_Inline},
{4, TokenJaiKind_Else},
{0, 0},
{4, TokenJaiKind_AlignOf},
{4, TokenJaiKind_Continue},
{4, TokenJaiKind_Using},
{0, 0},
{4, TokenJaiKind_Delete},
{0, 0},
{0, 0},
{4, TokenJaiKind_String},
{4, TokenJaiKind_S16},
{4, TokenJaiKind_New},
{0, 0},
{4, TokenJaiKind_Void},
{4, TokenJaiKind_Switch},
{4, TokenJaiKind_ItIndex},
{4, TokenJaiKind_SizeOf},
{0, 0},
{4, TokenJaiKind_Bool},
{4, TokenJaiKind_Float},
{4, TokenJaiKind_Float64},
{4, TokenJaiKind_Context},
{4, TokenJaiKind_Float32},
{0, 0},
{4, TokenJaiKind_Null},
{0, 0},
{4, TokenJaiKind_S64},
{4, TokenJaiKind_Autocast},
{0, 0},
{4, TokenJaiKind_S32},
{4, TokenJaiKind_Defer},
{8, TokenJaiKind_LiteralFalse},
{4, TokenJaiKind_Do},
{0, 0},
{4, TokenJaiKind_U16},
{4, TokenJaiKind_Return},
{4, TokenJaiKind_U32},
{0, 0},
{4, TokenJaiKind_U64},
{8, TokenJaiKind_LiteralTrue},
{0, 0},
{0, 0},
};
i32 jai_main_keys_slot_count = 89;
u64 jai_main_keys_seed = 0xdad4186f326399e6;
u64 jai_pp_directives_hash_array[26] = {
0x0000000000000000,0x755125dd846c4e37,0x0000000000000000,0xeef7a5902079b62b,
0x17cded2cf5df481f,0x0000000000000000,0x75512717f42c1637,0x0000000000000000,
0xeef7a59010e91d9d,0xeef7a590178bdd2b,0xa68c48e5b395c40f,0x0000000000000000,
0x17cded2a35a9716b,0x17cded2c8bce182b,0xeef7a59020a0d01b,0xa68c48e5b3e4ca19,
0x0000000000000000,0x170cbfb20460869b,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0xeef7a59012951273,0x17cded2e7168c40d,0x0000000000000000,
0xa68c48e5b3e53d9f,0xa68c48e5b395c1fb,
};
u8 jai_pp_directives_key_array_1[] = {0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,};
u8 jai_pp_directives_key_array_3[] = {0x69,0x66,0x64,0x65,0x66,};
u8 jai_pp_directives_key_array_4[] = {0x64,0x65,0x66,0x69,0x6e,0x65,};
u8 jai_pp_directives_key_array_6[] = {0x69,0x6e,0x63,0x6c,0x75,0x64,0x65,};
u8 jai_pp_directives_key_array_8[] = {0x75,0x73,0x69,0x6e,0x67,};
u8 jai_pp_directives_key_array_9[] = {0x75,0x6e,0x64,0x65,0x66,};
u8 jai_pp_directives_key_array_10[] = {0x65,0x6c,0x73,0x65,};
u8 jai_pp_directives_key_array_12[] = {0x70,0x72,0x61,0x67,0x6d,0x61,};
u8 jai_pp_directives_key_array_13[] = {0x69,0x66,0x6e,0x64,0x65,0x66,};
u8 jai_pp_directives_key_array_14[] = {0x65,0x6e,0x64,0x69,0x66,};
u8 jai_pp_directives_key_array_15[] = {0x6c,0x6f,0x61,0x64,};
u8 jai_pp_directives_key_array_17[] = {0x69,0x66,};
u8 jai_pp_directives_key_array_21[] = {0x65,0x72,0x72,0x6f,0x72,};
u8 jai_pp_directives_key_array_22[] = {0x69,0x6d,0x70,0x6f,0x72,0x74,};
u8 jai_pp_directives_key_array_24[] = {0x6c,0x69,0x6e,0x65,};
u8 jai_pp_directives_key_array_25[] = {0x65,0x6c,0x69,0x66,};
String_Const_u8 jai_pp_directives_key_array[26] = {
{0, 0},
{jai_pp_directives_key_array_1, 7},
{0, 0},
{jai_pp_directives_key_array_3, 5},
{jai_pp_directives_key_array_4, 6},
{0, 0},
{jai_pp_directives_key_array_6, 7},
{0, 0},
{jai_pp_directives_key_array_8, 5},
{jai_pp_directives_key_array_9, 5},
{jai_pp_directives_key_array_10, 4},
{0, 0},
{jai_pp_directives_key_array_12, 6},
{jai_pp_directives_key_array_13, 6},
{jai_pp_directives_key_array_14, 5},
{jai_pp_directives_key_array_15, 4},
{0, 0},
{jai_pp_directives_key_array_17, 2},
{0, 0},
{0, 0},
{0, 0},
{jai_pp_directives_key_array_21, 5},
{jai_pp_directives_key_array_22, 6},
{0, 0},
{jai_pp_directives_key_array_24, 4},
{jai_pp_directives_key_array_25, 4},
};
Lexeme_Table_Value jai_pp_directives_value_array[26] = {
{0, 0},
{6, TokenJaiKind_PPVersion},
{0, 0},
{6, TokenJaiKind_PPIfDef},
{6, TokenJaiKind_PPDefine},
{0, 0},
{6, TokenJaiKind_PPInclude},
{0, 0},
{6, TokenJaiKind_PPUsing},
{6, TokenJaiKind_PPUndef},
{6, TokenJaiKind_PPElse},
{0, 0},
{6, TokenJaiKind_PPPragma},
{6, TokenJaiKind_PPIfNDef},
{6, TokenJaiKind_PPEndIf},
{6, TokenJaiKind_PPLoad},
{0, 0},
{6, TokenJaiKind_PPIf},
{0, 0},
{0, 0},
{0, 0},
{6, TokenJaiKind_PPError},
{6, TokenJaiKind_PPImport},
{0, 0},
{6, TokenJaiKind_PPLine},
{6, TokenJaiKind_PPElIf},
};
i32 jai_pp_directives_slot_count = 26;
u64 jai_pp_directives_seed = 0xe62720852fa9c0c9;
u64 jai_pp_keys_hash_array[2] = {
0x6ff694a29d906569,0x0000000000000000,
};
u8 jai_pp_keys_key_array_0[] = {0x64,0x65,0x66,0x69,0x6e,0x65,0x64,};
String_Const_u8 jai_pp_keys_key_array[2] = {
{jai_pp_keys_key_array_0, 7},
{0, 0},
};
Lexeme_Table_Value jai_pp_keys_value_array[2] = {
{4, TokenJaiKind_PPDefined},
{0, 0},
};
i32 jai_pp_keys_slot_count = 2;
u64 jai_pp_keys_seed = 0x78c15ebe872f0e56;
struct Lex_State_Jai{
u32 flags_ZF0;
u32 flags_KF0;
u16 flags_ZB0;
u8 *base;
u8 *delim_first;
u8 *delim_one_past_last;
u8 *emit_ptr;
u8 *ptr;
u8 *opl_ptr;
};
internal void
lex_full_input_jai_init(Lex_State_Jai *state_ptr, String_Const_u8 input){
state_ptr->flags_ZF0 = 0;
state_ptr->flags_KF0 = 0;
state_ptr->flags_ZB0 = 0;
state_ptr->base = input.str;
state_ptr->delim_first = input.str;
state_ptr->delim_one_past_last = input.str;
state_ptr->emit_ptr = input.str;
state_ptr->ptr = input.str;
state_ptr->opl_ptr = input.str + input.size;
}
internal b32
lex_full_input_jai_breaks(Arena *arena, Token_List *list, Lex_State_Jai *state_ptr, u64 max){
b32 result = false;
u64 emit_counter = 0;
Lex_State_Jai state;
block_copy_struct(&state, state_ptr);
{
state_label_1: // root
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_EOF;
token.kind = 0;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
result = true;
goto end;
}
}
switch (*state.ptr){
case 0x00:case 0x01:case 0x02:case 0x03:case 0x04:case 0x05:case 0x06:
case 0x07:case 0x08:case 0x0e:case 0x0f:case 0x10:case 0x11:case 0x12:
case 0x13:case 0x14:case 0x15:case 0x16:case 0x17:case 0x18:case 0x19:
case 0x1a:case 0x1b:case 0x1c:case 0x1d:case 0x1e:case 0x1f:case 0x40:
case 0x60:case 0x7f:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x09:case 0x0b:case 0x0c:case 0x0d:case 0x20:
{
if ((HasFlag(state.flags_KF0, 0x2))){
state.ptr += 1;
goto state_label_4; // error_body
}
state.ptr += 1;
goto state_label_3; // whitespace
}break;
case 0x0a:
{
state.ptr += 1;
state.flags_ZB0 &= ~(0x1);
state.flags_KF0 &= ~(0x1);
state.flags_KF0 &= ~(0x2);
goto state_label_3; // whitespace
}break;
case 0x21:
{
state.ptr += 1;
goto state_label_58; // op stage
}break;
case 0x22:
{
if ((HasFlag(state.flags_KF0, 0x1))){
state.ptr += 1;
goto state_label_26; // include_quotes
}
state.ptr += 1;
goto state_label_32; // string
}break;
case 0x23:
{
if ((!HasFlag(state.flags_ZB0, 0x1))){
state.ptr += 1;
goto state_label_23; // pp_directive_whitespace
}
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
default:
{
state.ptr += 1;
goto state_label_2; // identifier
}break;
case 0x25:
{
state.ptr += 1;
goto state_label_63; // op stage
}break;
case 0x26:
{
state.ptr += 1;
goto state_label_59; // op stage
}break;
case 0x27:
{
state.ptr += 1;
state.flags_ZF0 |= 0x40;
goto state_label_32; // string
}break;
case 0x28:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_ParenOp;
token.kind = 13;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x29:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_ParenCl;
token.kind = 14;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x2a:
{
state.ptr += 1;
goto state_label_62; // op stage
}break;
case 0x2b:
{
state.ptr += 1;
goto state_label_61; // op stage
}break;
case 0x2c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Comma;
token.kind = 15;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x2d:
{
state.ptr += 1;
goto state_label_54; // op stage
}break;
case 0x2e:
{
state.ptr += 1;
goto state_label_6; // operator_or_fnumber_dot
}break;
case 0x2f:
{
state.ptr += 1;
goto state_label_7; // operator_or_comment_slash
}break;
case 0x30:
{
state.ptr += 1;
goto state_label_9; // znumber
}break;
case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:case 0x37:
case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_8; // number
}break;
case 0x3a:
{
state.ptr += 1;
goto state_label_53; // op stage
}break;
case 0x3b:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Semicolon;
token.kind = 15;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x3c:
{
if ((!HasFlag(state.flags_KF0, 0x1))){
state.ptr += 1;
goto state_label_56; // op stage
}
state.ptr += 1;
goto state_label_25; // include_pointy
}break;
case 0x3d:
{
state.ptr += 1;
goto state_label_55; // op stage
}break;
case 0x3e:
{
state.ptr += 1;
goto state_label_57; // op stage
}break;
case 0x3f:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Ternary;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x4c:
{
state.ptr += 1;
state.flags_ZF0 |= 0x4;
goto state_label_27; // pre_L
}break;
case 0x52:
{
state.ptr += 1;
goto state_label_31; // pre_R
}break;
case 0x55:
{
state.ptr += 1;
state.flags_ZF0 |= 0x20;
goto state_label_29; // pre_U
}break;
case 0x5b:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_BrackOp;
token.kind = 13;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x5c:
{
state.ptr += 1;
goto state_label_5; // backslash
}break;
case 0x5d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_BrackCl;
token.kind = 14;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x5e:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Xor;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x75:
{
state.ptr += 1;
state.flags_ZF0 |= 0x10;
goto state_label_28; // pre_u
}break;
case 0x7b:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_BraceOp;
token.kind = 11;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x7c:
{
state.ptr += 1;
goto state_label_60; // op stage
}break;
case 0x7d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_BraceCl;
token.kind = 12;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x7e:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Tilde;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_2: // identifier
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZB0, 0x1)){
Lexeme_Table_Lookup lookup = lexeme_table_lookup(jai_pp_keys_hash_array, jai_pp_keys_key_array, jai_pp_keys_value_array, jai_pp_keys_slot_count, jai_pp_keys_seed, state.emit_ptr, token.size);
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
}
Lexeme_Table_Lookup lookup = lexeme_table_lookup(jai_main_keys_hash_array, jai_main_keys_key_array, jai_main_keys_value_array, jai_main_keys_slot_count, jai_main_keys_seed, state.emit_ptr, token.size);
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
token.sub_kind = TokenJaiKind_Identifier;
token.kind = 6;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
case 0x00:case 0x01:case 0x02:case 0x03:case 0x04:case 0x05:case 0x06:
case 0x07:case 0x08:case 0x09:case 0x0a:case 0x0b:case 0x0c:case 0x0d:
case 0x0e:case 0x0f:case 0x10:case 0x11:case 0x12:case 0x13:case 0x14:
case 0x15:case 0x16:case 0x17:case 0x18:case 0x19:case 0x1a:case 0x1b:
case 0x1c:case 0x1d:case 0x1e:case 0x1f:case 0x20:case 0x21:case 0x22:
case 0x23:case 0x25:case 0x26:case 0x27:case 0x28:case 0x29:case 0x2a:
case 0x2b:case 0x2c:case 0x2d:case 0x2e:case 0x2f:case 0x3a:case 0x3b:
case 0x3c:case 0x3d:case 0x3e:case 0x3f:case 0x40:case 0x5b:case 0x5c:
case 0x5d:case 0x5e:case 0x60:case 0x7b:case 0x7c:case 0x7d:case 0x7e:
case 0x7f:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZB0, 0x1)){
Lexeme_Table_Lookup lookup = lexeme_table_lookup(jai_pp_keys_hash_array, jai_pp_keys_key_array, jai_pp_keys_value_array, jai_pp_keys_slot_count, jai_pp_keys_seed, state.emit_ptr, token.size);
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
}
Lexeme_Table_Lookup lookup = lexeme_table_lookup(jai_main_keys_hash_array, jai_main_keys_key_array, jai_main_keys_value_array, jai_main_keys_slot_count, jai_main_keys_seed, state.emit_ptr, token.size);
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
token.sub_kind = TokenJaiKind_Identifier;
token.kind = 6;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
default:
{
state.ptr += 1;
goto state_label_2; // identifier
}break;
}
}
{
state_label_3: // whitespace
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Whitespace;
token.kind = 1;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Whitespace;
token.kind = 1;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x09:case 0x0b:case 0x0c:case 0x0d:case 0x20:
{
state.ptr += 1;
goto state_label_3; // whitespace
}break;
case 0x0a:
{
state.ptr += 1;
state.flags_ZB0 &= ~(0x1);
state.flags_KF0 &= ~(0x1);
state.flags_KF0 &= ~(0x2);
goto state_label_3; // whitespace
}break;
}
}
{
state_label_4: // error_body
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_PPErrorMessage;
token.kind = 10;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_4; // error_body
}break;
case 0x0a:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_PPErrorMessage;
token.kind = 10;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_5: // backslash
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Backslash;
token.kind = 1;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Backslash;
token.kind = 1;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x0a:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Backslash;
token.kind = 1;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x0d:
{
state.ptr += 1;
goto state_label_5; // backslash
}break;
}
}
{
state_label_6: // operator_or_fnumber_dot
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Dot;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Dot;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x2a:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_DotStar;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x2e:
{
state.ptr += 1;
goto state_label_66; // op stage
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_10; // fnumber_decimal
}break;
}
}
{
state_label_7: // operator_or_comment_slash
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Div;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Div;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x2a:
{
state.ptr += 1;
goto state_label_49; // comment_block
}break;
case 0x2f:
{
state.ptr += 1;
goto state_label_51; // comment_line
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_DivEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_8: // number
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralInteger;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralInteger;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x2e:
{
state.ptr += 1;
goto state_label_10; // fnumber_decimal
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_8; // number
}break;
case 0x45:case 0x65:
{
state.ptr += 1;
goto state_label_11; // fnumber_exponent
}break;
case 0x4c:
{
state.ptr += 1;
goto state_label_18; // L_number
}break;
case 0x55:case 0x75:
{
state.ptr += 1;
goto state_label_17; // U_number
}break;
case 0x6c:
{
state.ptr += 1;
goto state_label_20; // l_number
}break;
}
}
{
state_label_9: // znumber
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralInteger;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralInteger;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x2e:
{
state.ptr += 1;
goto state_label_10; // fnumber_decimal
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:
{
state.ptr += 1;
state.flags_ZF0 |= 0x2;
goto state_label_16; // number_oct
}break;
case 0x45:case 0x65:
{
state.ptr += 1;
goto state_label_11; // fnumber_exponent
}break;
case 0x4c:
{
state.ptr += 1;
goto state_label_18; // L_number
}break;
case 0x55:case 0x75:
{
state.ptr += 1;
goto state_label_17; // U_number
}break;
case 0x58:case 0x78:
{
state.ptr += 1;
state.flags_ZF0 |= 0x1;
goto state_label_14; // number_hex_first
}break;
case 0x6c:
{
state.ptr += 1;
goto state_label_20; // l_number
}break;
}
}
{
state_label_10: // fnumber_decimal
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralFloat64;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralFloat64;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_10; // fnumber_decimal
}break;
case 0x45:case 0x65:
{
state.ptr += 1;
goto state_label_11; // fnumber_exponent
}break;
case 0x46:case 0x66:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralFloat32;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x4c:case 0x6c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralFloat64;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_11: // fnumber_exponent
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralFloat64;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralFloat64;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x2b:case 0x2d:
{
state.ptr += 1;
goto state_label_12; // fnumber_exponent_sign
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_13; // fnumber_exponent_digits
}break;
case 0x46:case 0x66:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralFloat32;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x4c:case 0x6c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralFloat64;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_12: // fnumber_exponent_sign
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralFloat64;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralFloat64;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_13; // fnumber_exponent_digits
}break;
case 0x46:case 0x66:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralFloat32;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x4c:case 0x6c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralFloat64;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_13: // fnumber_exponent_digits
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralFloat64;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralFloat64;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_13; // fnumber_exponent_digits
}break;
case 0x46:case 0x66:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralFloat32;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x4c:case 0x6c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralFloat64;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_14: // number_hex_first
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_15; // number_hex
}break;
}
}
{
state_label_15: // number_hex
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralIntegerHex;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralIntegerHex;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_15; // number_hex
}break;
case 0x4c:
{
state.ptr += 1;
goto state_label_18; // L_number
}break;
case 0x55:case 0x75:
{
state.ptr += 1;
goto state_label_17; // U_number
}break;
case 0x6c:
{
state.ptr += 1;
goto state_label_20; // l_number
}break;
}
}
{
state_label_16: // number_oct
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralIntegerOct;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LiteralIntegerOct;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:
{
state.ptr += 1;
state.flags_ZF0 |= 0x2;
goto state_label_16; // number_oct
}break;
case 0x4c:
{
state.ptr += 1;
goto state_label_18; // L_number
}break;
case 0x55:case 0x75:
{
state.ptr += 1;
goto state_label_17; // U_number
}break;
case 0x6c:
{
state.ptr += 1;
goto state_label_20; // l_number
}break;
}
}
{
state_label_17: // U_number
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexU;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctU;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerU;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexU;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctU;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerU;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x4c:
{
state.ptr += 1;
goto state_label_19; // UL_number
}break;
case 0x6c:
{
state.ptr += 1;
goto state_label_21; // Ul_number
}break;
}
}
{
state_label_18: // L_number
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexL;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctL;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerL;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexL;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctL;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerL;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x4c:
{
state.ptr += 1;
goto state_label_22; // LL_number
}break;
case 0x55:case 0x75:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexUL;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctUL;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerUL;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_19: // UL_number
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexUL;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctUL;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerUL;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexUL;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctUL;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerUL;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x4c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexULL;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctULL;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerULL;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_20: // l_number
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexL;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctL;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerL;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexL;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctL;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerL;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x55:case 0x75:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexUL;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctUL;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerUL;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x6c:
{
state.ptr += 1;
goto state_label_22; // LL_number
}break;
}
}
{
state_label_21: // Ul_number
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexUL;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctUL;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerUL;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexUL;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctUL;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerUL;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x6c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexULL;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctULL;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerULL;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_22: // LL_number
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexLL;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctLL;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerLL;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexLL;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctLL;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerLL;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x55:case 0x75:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x1)){
token.sub_kind = TokenJaiKind_LiteralIntegerHexULL;
token.kind = 8;
break;
}
if (HasFlag(state.flags_ZF0, 0x2)){
token.sub_kind = TokenJaiKind_LiteralIntegerOctULL;
token.kind = 8;
break;
}
token.sub_kind = TokenJaiKind_LiteralIntegerULL;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_23: // pp_directive_whitespace
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x09:case 0x0b:case 0x0c:case 0x20:
{
state.ptr += 1;
goto state_label_23; // pp_directive_whitespace
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x47:case 0x48:case 0x49:case 0x4a:case 0x4b:
case 0x4c:case 0x4d:case 0x4e:case 0x4f:case 0x50:case 0x51:case 0x52:
case 0x53:case 0x54:case 0x55:case 0x56:case 0x57:case 0x58:case 0x59:
case 0x5a:case 0x5f:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:case 0x67:case 0x68:case 0x69:case 0x6a:case 0x6b:case 0x6c:
case 0x6d:case 0x6e:case 0x6f:case 0x70:case 0x71:case 0x72:case 0x73:
case 0x74:case 0x75:case 0x76:case 0x77:case 0x78:case 0x79:case 0x7a:
{
state.delim_first = state.ptr;
state.flags_ZB0 |= 0x1;
state.ptr += 1;
goto state_label_24; // pp_directive
}break;
}
}
{
state_label_24: // pp_directive
if (state.ptr == state.opl_ptr){
if ((true)){
state.delim_one_past_last = state.ptr;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
Lexeme_Table_Lookup lookup = lexeme_table_lookup(jai_pp_directives_hash_array, jai_pp_directives_key_array, jai_pp_directives_value_array, jai_pp_directives_slot_count, jai_pp_directives_seed, state.delim_first, (state.delim_one_past_last - state.delim_first));
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
token.sub_kind = TokenJaiKind_PPUnknown;
token.kind = 2;
}while(0);
switch (token.sub_kind){
case TokenJaiKind_PPInclude:
{
state.flags_KF0 |= 0x1;
}break;
case TokenJaiKind_PPError:
{
state.flags_KF0 |= 0x2;
}break;
}
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
state.delim_one_past_last = state.ptr;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
Lexeme_Table_Lookup lookup = lexeme_table_lookup(jai_pp_directives_hash_array, jai_pp_directives_key_array, jai_pp_directives_value_array, jai_pp_directives_slot_count, jai_pp_directives_seed, state.delim_first, (state.delim_one_past_last - state.delim_first));
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
token.sub_kind = TokenJaiKind_PPUnknown;
token.kind = 2;
}while(0);
switch (token.sub_kind){
case TokenJaiKind_PPInclude:
{
state.flags_KF0 |= 0x1;
}break;
case TokenJaiKind_PPError:
{
state.flags_KF0 |= 0x2;
}break;
}
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x47:case 0x48:case 0x49:case 0x4a:case 0x4b:
case 0x4c:case 0x4d:case 0x4e:case 0x4f:case 0x50:case 0x51:case 0x52:
case 0x53:case 0x54:case 0x55:case 0x56:case 0x57:case 0x58:case 0x59:
case 0x5a:case 0x5f:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:case 0x67:case 0x68:case 0x69:case 0x6a:case 0x6b:case 0x6c:
case 0x6d:case 0x6e:case 0x6f:case 0x70:case 0x71:case 0x72:case 0x73:
case 0x74:case 0x75:case 0x76:case 0x77:case 0x78:case 0x79:case 0x7a:
{
state.ptr += 1;
goto state_label_24; // pp_directive
}break;
}
}
{
state_label_25: // include_pointy
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x20:case 0x2e:case 0x2f:case 0x30:case 0x31:case 0x32:case 0x33:
case 0x34:case 0x35:case 0x36:case 0x37:case 0x38:case 0x39:case 0x41:
case 0x42:case 0x43:case 0x44:case 0x45:case 0x46:case 0x47:case 0x48:
case 0x49:case 0x4a:case 0x4b:case 0x4c:case 0x4d:case 0x4e:case 0x4f:
case 0x50:case 0x51:case 0x52:case 0x53:case 0x54:case 0x55:case 0x56:
case 0x57:case 0x58:case 0x59:case 0x5a:case 0x5c:case 0x5f:case 0x61:
case 0x62:case 0x63:case 0x64:case 0x65:case 0x66:case 0x67:case 0x68:
case 0x69:case 0x6a:case 0x6b:case 0x6c:case 0x6d:case 0x6e:case 0x6f:
case 0x70:case 0x71:case 0x72:case 0x73:case 0x74:case 0x75:case 0x76:
case 0x77:case 0x78:case 0x79:case 0x7a:
{
state.ptr += 1;
goto state_label_25; // include_pointy
}break;
case 0x3e:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_PPIncludeFile;
token.kind = 10;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_26: // include_quotes
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x20:case 0x2e:case 0x2f:case 0x30:case 0x31:case 0x32:case 0x33:
case 0x34:case 0x35:case 0x36:case 0x37:case 0x38:case 0x39:case 0x41:
case 0x42:case 0x43:case 0x44:case 0x45:case 0x46:case 0x47:case 0x48:
case 0x49:case 0x4a:case 0x4b:case 0x4c:case 0x4d:case 0x4e:case 0x4f:
case 0x50:case 0x51:case 0x52:case 0x53:case 0x54:case 0x55:case 0x56:
case 0x57:case 0x58:case 0x59:case 0x5a:case 0x5c:case 0x5f:case 0x61:
case 0x62:case 0x63:case 0x64:case 0x65:case 0x66:case 0x67:case 0x68:
case 0x69:case 0x6a:case 0x6b:case 0x6c:case 0x6d:case 0x6e:case 0x6f:
case 0x70:case 0x71:case 0x72:case 0x73:case 0x74:case 0x75:case 0x76:
case 0x77:case 0x78:case 0x79:case 0x7a:
{
state.ptr += 1;
goto state_label_26; // include_quotes
}break;
case 0x22:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_PPIncludeFile;
token.kind = 10;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_27: // pre_L
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_2; // identifier
}
}
switch (*state.ptr){
default:
{
goto state_label_2; // identifier
}break;
case 0x22:
{
state.ptr += 1;
goto state_label_32; // string
}break;
case 0x52:
{
state.ptr += 1;
goto state_label_31; // pre_R
}break;
}
}
{
state_label_28: // pre_u
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_2; // identifier
}
}
switch (*state.ptr){
default:
{
goto state_label_2; // identifier
}break;
case 0x22:
{
state.ptr += 1;
goto state_label_32; // string
}break;
case 0x38:
{
state.ptr += 1;
state.flags_ZF0 |= 0x8;
goto state_label_30; // pre_u8
}break;
case 0x52:
{
state.ptr += 1;
goto state_label_31; // pre_R
}break;
}
}
{
state_label_29: // pre_U
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_2; // identifier
}
}
switch (*state.ptr){
default:
{
goto state_label_2; // identifier
}break;
case 0x22:
{
state.ptr += 1;
goto state_label_32; // string
}break;
case 0x52:
{
state.ptr += 1;
goto state_label_31; // pre_R
}break;
}
}
{
state_label_30: // pre_u8
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_2; // identifier
}
}
switch (*state.ptr){
default:
{
goto state_label_2; // identifier
}break;
case 0x22:
{
state.ptr += 1;
goto state_label_32; // string
}break;
case 0x52:
{
state.ptr += 1;
goto state_label_31; // pre_R
}break;
}
}
{
state_label_31: // pre_R
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_2; // identifier
}
}
switch (*state.ptr){
default:
{
goto state_label_2; // identifier
}break;
case 0x22:
{
state.ptr += 1;
state.delim_first = state.ptr;
goto state_label_45; // raw_string_get_delim
}break;
}
}
{
state_label_32: // string
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_32; // string
}break;
case 0x0a:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x22:
{
if ((!HasFlag(state.flags_ZF0, 0x40))){
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x4)){
token.sub_kind = TokenJaiKind_LiteralStringWide;
token.kind = 10;
break;
}
if (HasFlag(state.flags_ZF0, 0x8)){
token.sub_kind = TokenJaiKind_LiteralStringUTF8;
token.kind = 10;
break;
}
if (HasFlag(state.flags_ZF0, 0x10)){
token.sub_kind = TokenJaiKind_LiteralStringUTF16;
token.kind = 10;
break;
}
if (HasFlag(state.flags_ZF0, 0x20)){
token.sub_kind = TokenJaiKind_LiteralStringUTF32;
token.kind = 10;
break;
}
token.sub_kind = TokenJaiKind_LiteralString;
token.kind = 10;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
state.ptr += 1;
goto state_label_32; // string
}break;
case 0x27:
{
if ((HasFlag(state.flags_ZF0, 0x40))){
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x4)){
token.sub_kind = TokenJaiKind_LiteralCharacterWide;
token.kind = 10;
break;
}
if (HasFlag(state.flags_ZF0, 0x8)){
token.sub_kind = TokenJaiKind_LiteralCharacterUTF8;
token.kind = 10;
break;
}
if (HasFlag(state.flags_ZF0, 0x10)){
token.sub_kind = TokenJaiKind_LiteralCharacterUTF16;
token.kind = 10;
break;
}
if (HasFlag(state.flags_ZF0, 0x20)){
token.sub_kind = TokenJaiKind_LiteralCharacterUTF32;
token.kind = 10;
break;
}
token.sub_kind = TokenJaiKind_LiteralCharacter;
token.kind = 10;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
state.ptr += 1;
goto state_label_32; // string
}break;
case 0x5c:
{
state.ptr += 1;
goto state_label_33; // string_esc
}break;
}
}
{
state_label_33: // string_esc
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_EOF;
token.kind = 0;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
result = true;
goto end;
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_32; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:
{
state.ptr += 1;
goto state_label_34; // string_esc_oct2
}break;
case 0x55:
{
state.ptr += 1;
goto state_label_37; // string_esc_universal_8
}break;
case 0x75:
{
state.ptr += 1;
goto state_label_41; // string_esc_universal_4
}break;
case 0x78:
{
state.ptr += 1;
goto state_label_36; // string_esc_hex
}break;
}
}
{
state_label_34: // string_esc_oct2
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_32; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_32; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:
{
state.ptr += 1;
goto state_label_35; // string_esc_oct1
}break;
}
}
{
state_label_35: // string_esc_oct1
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_32; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_32; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:
{
state.ptr += 1;
goto state_label_32; // string
}break;
}
}
{
state_label_36: // string_esc_hex
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_32; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_32; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_36; // string_esc_hex
}break;
}
}
{
state_label_37: // string_esc_universal_8
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_32; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_32; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_38; // string_esc_universal_7
}break;
}
}
{
state_label_38: // string_esc_universal_7
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_32; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_32; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_39; // string_esc_universal_6
}break;
}
}
{
state_label_39: // string_esc_universal_6
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_32; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_32; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_40; // string_esc_universal_5
}break;
}
}
{
state_label_40: // string_esc_universal_5
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_32; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_32; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_41; // string_esc_universal_4
}break;
}
}
{
state_label_41: // string_esc_universal_4
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_32; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_32; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_42; // string_esc_universal_3
}break;
}
}
{
state_label_42: // string_esc_universal_3
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_32; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_32; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_43; // string_esc_universal_2
}break;
}
}
{
state_label_43: // string_esc_universal_2
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_32; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_32; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_44; // string_esc_universal_1
}break;
}
}
{
state_label_44: // string_esc_universal_1
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_32; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_32; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_32; // string
}break;
}
}
{
state_label_45: // raw_string_get_delim
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_EOF;
token.kind = 0;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
result = true;
goto end;
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_45; // raw_string_get_delim
}break;
case 0x20:case 0x29:case 0x5c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x28:
{
state.delim_one_past_last = state.ptr;
state.ptr += 1;
goto state_label_46; // raw_string_find_close
}break;
}
}
{
state_label_46: // raw_string_find_close
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_EOF;
token.kind = 0;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
result = true;
goto end;
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_46; // raw_string_find_close
}break;
case 0x29:
{
state.ptr += 1;
goto state_label_47; // raw_string_try_delim
}break;
}
}
{
state_label_47: // raw_string_try_delim
u64 delim_length = state.delim_one_past_last - state.delim_first;
u64 parse_length = 0;
for (;;){
if (parse_length == delim_length){
goto state_label_48; // raw_string_try_quote
}
if (state.ptr == state.opl_ptr){
goto state_label_48; // raw_string_try_quote
}
if (*state.ptr == state.delim_first[parse_length]){
state.ptr += 1;
parse_length += 1;
}
else{
goto state_label_46; // raw_string_find_close
}
}
}
{
state_label_48: // raw_string_try_quote
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_46; // raw_string_find_close
}
}
switch (*state.ptr){
default:
{
goto state_label_46; // raw_string_find_close
}break;
case 0x22:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
if (HasFlag(state.flags_ZF0, 0x4)){
token.sub_kind = TokenJaiKind_LiteralStringWideRaw;
token.kind = 10;
break;
}
if (HasFlag(state.flags_ZF0, 0x8)){
token.sub_kind = TokenJaiKind_LiteralStringUTF8Raw;
token.kind = 10;
break;
}
if (HasFlag(state.flags_ZF0, 0x10)){
token.sub_kind = TokenJaiKind_LiteralStringUTF16Raw;
token.kind = 10;
break;
}
if (HasFlag(state.flags_ZF0, 0x20)){
token.sub_kind = TokenJaiKind_LiteralStringUTF32Raw;
token.kind = 10;
break;
}
token.sub_kind = TokenJaiKind_LiteralStringRaw;
token.kind = 10;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_49: // comment_block
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_BlockComment;
token.kind = 3;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_EOF;
token.kind = 0;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
result = true;
goto end;
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_49; // comment_block
}break;
case 0x0a:
{
state.ptr += 1;
state.flags_ZB0 &= ~(0x1);
state.flags_KF0 &= ~(0x1);
goto state_label_49; // comment_block
}break;
case 0x2a:
{
state.ptr += 1;
goto state_label_50; // comment_block_try_close
}break;
}
}
{
state_label_50: // comment_block_try_close
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_BlockComment;
token.kind = 3;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_EOF;
token.kind = 0;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
result = true;
goto end;
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_49; // comment_block
}break;
case 0x2a:
{
state.ptr += 1;
goto state_label_50; // comment_block_try_close
}break;
case 0x2f:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_BlockComment;
token.kind = 3;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_51: // comment_line
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LineComment;
token.kind = 3;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_51; // comment_line
}break;
case 0x0a:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LineComment;
token.kind = 3;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x5c:
{
state.ptr += 1;
goto state_label_52; // comment_line_backslashing
}break;
}
}
{
state_label_52: // comment_line_backslashing
if (state.ptr == state.opl_ptr){
if ((true)){
result = true;
goto end;
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_51; // comment_line
}break;
case 0x0d:
{
state.ptr += 1;
goto state_label_52; // comment_line_backslashing
}break;
}
}
{
state_label_53: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Colon;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Colon;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x3a:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_ColonColon;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_ColonEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_54: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Minus;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Minus;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_MinusEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x3e:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_MinusGrtr;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_55: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Eq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Eq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_EqEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x3e:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_EqGrtr;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_56: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Less;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Less;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x3c:
{
state.ptr += 1;
goto state_label_64; // op stage
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LessEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_57: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Grtr;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Grtr;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_GrtrEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x3e:
{
state.ptr += 1;
goto state_label_65; // op stage
}break;
}
}
{
state_label_58: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Not;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Not;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_NotEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_59: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_And;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_And;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x26:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_AndAnd;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_60: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Or;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Or;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x7c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_OrOr;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_61: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Plus;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Plus;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_PlusEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_62: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Star;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Star;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_StarEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_63: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Mod;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_Mod;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_ModEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_64: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LeftLeft;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LeftLeft;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_LeftLeftEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_65: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_RightRight;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_RightRight;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_RightRightEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_66: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_DotDot;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_DotDot;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
case 0x2e:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_ZB0;
do{
token.sub_kind = TokenJaiKind_DotDotDot;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_ZF0 = 0;
state.flags_ZB0 = 0;
goto state_label_1; // root
}break;
}
}
end:;
block_copy_struct(state_ptr, &state);
return(result);
}
internal Token_List
lex_full_input_jai(Arena *arena, String_Const_u8 input){
Lex_State_Jai state = {};
lex_full_input_jai_init(&state, input);
Token_List list = {};
lex_full_input_jai_breaks(arena, &list, &state, max_u64);
return(list);
}
