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
u64 odin_main_keys_hash_array[114] = {
0x0000000000000000,0xadced753e46f88c7,0x98d82d855441a349,0xdacda28a8024303d,
0x0000000000000000,0x98d82d855ba327ff,0xbb2066fa85d7e745,0x98d82d855ba36b3f,
0x0000000000000000,0xaf6a25b5ddd84455,0xe7fb1ef393b835bb,0x98d82d855ba34b33,
0x98d82d85544193bd,0x0000000000000000,0x98d82d855442617d,0x0000000000000000,
0x0000000000000000,0x98d82d85544192df,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x98d82d855ba480bf,0xdacda28a80815179,0xdad3e7f7eca83e8b,
0x0000000000000000,0xadca60871fa3d095,0x0000000000000000,0xf6f88270e2c7b197,
0x0000000000000000,0xdad3e7f5e551f7ad,0x0000000000000000,0xaf6a25fc02b628b1,
0x0000000000000000,0x0000000000000000,0xaf6a25b5dae481f9,0x98d82d8554419cc1,
0x0000000000000000,0xbb2072149e420b9b,0xdacda28a809df67f,0xdacda28b73d62c23,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x98d82d855ba36849,
0x0000000000000000,0xdad3e7f4f2188497,0xe7fb1ef393b8cbf5,0xaf6a25fc1c568133,
0xc58dc2fc10c96eb9,0xe7fb1ef393b835e7,0x0000000000000000,0xc631ceb2e145f7ad,
0x0000000000000000,0x98d82d855ba33601,0x0000000000000000,0xe7fb1ef393b8cb8d,
0x0000000000000000,0x0000000000000000,0x98d82d8554419ea1,0x0000000000000000,
0xadca891d0ee70a49,0xdacda28a80bbee6d,0x9383e7a57ac4040b,0xdad3e7f4f1f7dd41,
0x0000000000000000,0xdad3e788b75c482d,0xadced5def550a4a3,0x0000000000000000,
0xadced710e39f098b,0xaf6a25b5de92d375,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0xdad3e7f5e6b43c31,0xdacda28a80891755,0x0000000000000000,
0x98d82d8554419e41,0x0000000000000000,0xdad3e7f7ecad56a3,0xdad3e7f7ebe92047,
0xdacda28a80915375,0x98d82d855ba336ff,0x0000000000000000,0xdad3e7880fbe578b,
0x98d82d855ba32689,0xadca8a4c4bb4dd41,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0xadced782951ee27b,0xdacda28b73ea288b,0xaf6a25b5e6a7b953,
0xe7fb1ef393b8ca5f,0x0000000000000000,0x0000000000000000,0xadced7ec1b0e1f95,
0xadca8bda788e23f9,0xe7fb1ef393b8c90f,0x0000000000000000,0x98d82d855ba3269d,
0x0000000000000000,0x98d82d855ba48917,0x98d82d855ba369dd,0xdacda28b73ea2899,
0x0000000000000000,0x0000000000000000,
};
u8 odin_main_keys_key_array_1[] = {0x63,0x6f,0x6e,0x74,0x65,0x78,0x74,};
u8 odin_main_keys_key_array_2[] = {0x66,0x6f,0x72,};
u8 odin_main_keys_key_array_3[] = {0x65,0x6e,0x75,0x6d,};
u8 odin_main_keys_key_array_5[] = {0x69,0x36,0x34,};
u8 odin_main_keys_key_array_6[] = {0x63,0x6f,0x6e,0x74,0x69,0x6e,0x75,0x65,};
u8 odin_main_keys_key_array_7[] = {0x75,0x36,0x34,};
u8 odin_main_keys_key_array_9[] = {0x75,0x6e,0x69,0x6f,0x6e,};
u8 odin_main_keys_key_array_10[] = {0x62,0x38,};
u8 odin_main_keys_key_array_11[] = {0x6e,0x69,0x6c,};
u8 odin_main_keys_key_array_12[] = {0x62,0x31,0x36,};
u8 odin_main_keys_key_array_14[] = {0x2d,0x2d,0x2d,};
u8 odin_main_keys_key_array_17[] = {0x62,0x36,0x34,};
u8 odin_main_keys_key_array_25[] = {0x69,0x6e,0x74,};
u8 odin_main_keys_key_array_26[] = {0x65,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_27[] = {0x73,0x74,0x72,0x75,0x63,0x74,};
u8 odin_main_keys_key_array_29[] = {0x73,0x69,0x7a,0x65,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_31[] = {0x66,0x61,0x6c,0x6c,0x74,0x68,0x72,0x6f,0x75,0x67,0x68,};
u8 odin_main_keys_key_array_33[] = {0x72,0x65,0x74,0x75,0x72,0x6e,};
u8 odin_main_keys_key_array_35[] = {0x64,0x65,0x66,0x65,0x72,};
u8 odin_main_keys_key_array_38[] = {0x66,0x61,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_39[] = {0x62,0x33,0x32,};
u8 odin_main_keys_key_array_41[] = {0x64,0x69,0x73,0x74,0x69,0x6e,0x63,0x74,};
u8 odin_main_keys_key_array_42[] = {0x70,0x72,0x6f,0x63,};
u8 odin_main_keys_key_array_43[] = {0x62,0x6f,0x6f,0x6c,};
u8 odin_main_keys_key_array_47[] = {0x75,0x33,0x32,};
u8 odin_main_keys_key_array_49[] = {0x69,0x6d,0x70,0x6f,0x72,0x74,};
u8 odin_main_keys_key_array_50[] = {0x69,0x6e,};
u8 odin_main_keys_key_array_51[] = {0x62,0x72,0x65,0x61,0x6b,};
u8 odin_main_keys_key_array_52[] = {0x74,0x72,0x61,0x6e,0x73,0x6d,0x75,0x74,0x65,};
u8 odin_main_keys_key_array_53[] = {0x64,0x6f,};
u8 odin_main_keys_key_array_55[] = {0x6f,0x72,0x5f,0x72,0x65,0x74,0x75,0x72,0x6e,};
u8 odin_main_keys_key_array_57[] = {0x66,0x33,0x32,};
u8 odin_main_keys_key_array_59[] = {0x69,0x66,};
u8 odin_main_keys_key_array_62[] = {0x61,0x6e,0x79,};
u8 odin_main_keys_key_array_64[] = {0x70,0x61,0x63,0x6b,0x61,0x67,0x65,};
u8 odin_main_keys_key_array_65[] = {0x72,0x75,0x6e,0x65,};
u8 odin_main_keys_key_array_66[] = {0x61,0x75,0x74,0x6f,0x5f,0x63,0x61,0x73,0x74,};
u8 odin_main_keys_key_array_67[] = {0x69,0x6e,0x74,0x70,0x74,0x72,};
u8 odin_main_keys_key_array_69[] = {0x6e,0x6f,0x74,0x5f,0x69,0x6e,};
u8 odin_main_keys_key_array_70[] = {0x63,0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_72[] = {0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,};
u8 odin_main_keys_key_array_73[] = {0x77,0x68,0x65,0x72,0x65,};
u8 odin_main_keys_key_array_77[] = {0x72,0x61,0x77,0x70,0x74,0x72,};
u8 odin_main_keys_key_array_78[] = {0x74,0x72,0x75,0x65,};
u8 odin_main_keys_key_array_80[] = {0x61,0x73,0x6d,};
u8 odin_main_keys_key_array_82[] = {0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_83[] = {0x73,0x77,0x69,0x74,0x63,0x68,};
u8 odin_main_keys_key_array_84[] = {0x77,0x68,0x65,0x6e,};
u8 odin_main_keys_key_array_85[] = {0x66,0x36,0x34,};
u8 odin_main_keys_key_array_87[] = {0x74,0x79,0x70,0x65,0x69,0x64,};
u8 odin_main_keys_key_array_88[] = {0x69,0x33,0x32,};
u8 odin_main_keys_key_array_89[] = {0x75,0x69,0x6e,0x74,0x70,0x74,0x72,};
u8 odin_main_keys_key_array_97[] = {0x62,0x69,0x74,0x5f,0x73,0x65,0x74,};
u8 odin_main_keys_key_array_98[] = {0x63,0x61,0x73,0x74,};
u8 odin_main_keys_key_array_99[] = {0x75,0x73,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_100[] = {0x69,0x38,};
u8 odin_main_keys_key_array_103[] = {0x66,0x6f,0x72,0x65,0x69,0x67,0x6e,};
u8 odin_main_keys_key_array_104[] = {0x6f,0x72,0x5f,0x65,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_105[] = {0x75,0x38,};
u8 odin_main_keys_key_array_107[] = {0x69,0x31,0x36,};
u8 odin_main_keys_key_array_109[] = {0x6d,0x61,0x70,};
u8 odin_main_keys_key_array_110[] = {0x75,0x31,0x36,};
u8 odin_main_keys_key_array_111[] = {0x63,0x61,0x73,0x65,};
String_Const_u8 odin_main_keys_key_array[114] = {
{0, 0},
{odin_main_keys_key_array_1, 7},
{odin_main_keys_key_array_2, 3},
{odin_main_keys_key_array_3, 4},
{0, 0},
{odin_main_keys_key_array_5, 3},
{odin_main_keys_key_array_6, 8},
{odin_main_keys_key_array_7, 3},
{0, 0},
{odin_main_keys_key_array_9, 5},
{odin_main_keys_key_array_10, 2},
{odin_main_keys_key_array_11, 3},
{odin_main_keys_key_array_12, 3},
{0, 0},
{odin_main_keys_key_array_14, 3},
{0, 0},
{0, 0},
{odin_main_keys_key_array_17, 3},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_25, 3},
{odin_main_keys_key_array_26, 4},
{odin_main_keys_key_array_27, 6},
{0, 0},
{odin_main_keys_key_array_29, 7},
{0, 0},
{odin_main_keys_key_array_31, 11},
{0, 0},
{odin_main_keys_key_array_33, 6},
{0, 0},
{odin_main_keys_key_array_35, 5},
{0, 0},
{0, 0},
{odin_main_keys_key_array_38, 5},
{odin_main_keys_key_array_39, 3},
{0, 0},
{odin_main_keys_key_array_41, 8},
{odin_main_keys_key_array_42, 4},
{odin_main_keys_key_array_43, 4},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_47, 3},
{0, 0},
{odin_main_keys_key_array_49, 6},
{odin_main_keys_key_array_50, 2},
{odin_main_keys_key_array_51, 5},
{odin_main_keys_key_array_52, 9},
{odin_main_keys_key_array_53, 2},
{0, 0},
{odin_main_keys_key_array_55, 9},
{0, 0},
{odin_main_keys_key_array_57, 3},
{0, 0},
{odin_main_keys_key_array_59, 2},
{0, 0},
{0, 0},
{odin_main_keys_key_array_62, 3},
{0, 0},
{odin_main_keys_key_array_64, 7},
{odin_main_keys_key_array_65, 4},
{odin_main_keys_key_array_66, 9},
{odin_main_keys_key_array_67, 6},
{0, 0},
{odin_main_keys_key_array_69, 6},
{odin_main_keys_key_array_70, 7},
{0, 0},
{odin_main_keys_key_array_72, 7},
{odin_main_keys_key_array_73, 5},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_77, 6},
{odin_main_keys_key_array_78, 4},
{0, 0},
{odin_main_keys_key_array_80, 3},
{0, 0},
{odin_main_keys_key_array_82, 6},
{odin_main_keys_key_array_83, 6},
{odin_main_keys_key_array_84, 4},
{odin_main_keys_key_array_85, 3},
{0, 0},
{odin_main_keys_key_array_87, 6},
{odin_main_keys_key_array_88, 3},
{odin_main_keys_key_array_89, 7},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_97, 7},
{odin_main_keys_key_array_98, 4},
{odin_main_keys_key_array_99, 5},
{odin_main_keys_key_array_100, 2},
{0, 0},
{0, 0},
{odin_main_keys_key_array_103, 7},
{odin_main_keys_key_array_104, 7},
{odin_main_keys_key_array_105, 2},
{0, 0},
{odin_main_keys_key_array_107, 3},
{0, 0},
{odin_main_keys_key_array_109, 3},
{odin_main_keys_key_array_110, 3},
{odin_main_keys_key_array_111, 4},
{0, 0},
{0, 0},
};
Lexeme_Table_Value odin_main_keys_value_array[114] = {
{0, 0},
{4, TokenOdinKind_Context},
{4, TokenOdinKind_For},
{4, TokenOdinKind_Enum},
{0, 0},
{4, TokenOdinKind_I64},
{4, TokenOdinKind_Continue},
{4, TokenOdinKind_U64},
{0, 0},
{4, TokenOdinKind_Union},
{4, TokenOdinKind_B8},
{4, TokenOdinKind_Nil},
{4, TokenOdinKind_B16},
{0, 0},
{4, TokenOdinKind_Uninitialized},
{0, 0},
{0, 0},
{4, TokenOdinKind_B64},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Int},
{4, TokenOdinKind_Else},
{4, TokenOdinKind_Struct},
{0, 0},
{4, TokenOdinKind_SizeOf},
{0, 0},
{4, TokenOdinKind_Fallthrough},
{0, 0},
{4, TokenOdinKind_Return},
{0, 0},
{4, TokenOdinKind_Defer},
{0, 0},
{0, 0},
{8, TokenOdinKind_LiteralFalse},
{4, TokenOdinKind_B32},
{0, 0},
{4, TokenOdinKind_Distinct},
{4, TokenOdinKind_Proc},
{4, TokenOdinKind_Bool},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_U32},
{0, 0},
{4, TokenOdinKind_Import},
{4, TokenOdinKind_In},
{4, TokenOdinKind_Break},
{4, TokenOdinKind_Transmute},
{4, TokenOdinKind_Do},
{0, 0},
{4, TokenOdinKind_OrReturn},
{0, 0},
{4, TokenOdinKind_F32},
{0, 0},
{4, TokenOdinKind_If},
{0, 0},
{0, 0},
{4, TokenOdinKind_Any},
{0, 0},
{4, TokenOdinKind_Package},
{4, TokenOdinKind_Rune},
{4, TokenOdinKind_AutoCast},
{4, TokenOdinKind_Intptr},
{0, 0},
{4, TokenOdinKind_NotIn},
{4, TokenOdinKind_Cstring},
{0, 0},
{4, TokenOdinKind_Dynamic},
{4, TokenOdinKind_Where},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Rawptr},
{8, TokenOdinKind_LiteralTrue},
{0, 0},
{4, TokenOdinKind_Asm},
{0, 0},
{4, TokenOdinKind_String},
{4, TokenOdinKind_Switch},
{4, TokenOdinKind_When},
{4, TokenOdinKind_F64},
{0, 0},
{4, TokenOdinKind_Typeid},
{4, TokenOdinKind_I32},
{4, TokenOdinKind_Uintptr},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_BitSet},
{4, TokenOdinKind_Cast},
{4, TokenOdinKind_Using},
{4, TokenOdinKind_I8},
{0, 0},
{0, 0},
{4, TokenOdinKind_Foreign},
{4, TokenOdinKind_OrElse},
{4, TokenOdinKind_U8},
{0, 0},
{4, TokenOdinKind_I16},
{0, 0},
{4, TokenOdinKind_Map},
{4, TokenOdinKind_U16},
{4, TokenOdinKind_Case},
{0, 0},
{0, 0},
};
i32 odin_main_keys_slot_count = 114;
u64 odin_main_keys_seed = 0x08431153bc854a47;
u64 odin_directives_hash_array[50] = {
0x0000000000000000,0x72cdee74989667c1,0x0000000000000000,0xeaa8eb20be71c30b,
0xd9bb1b4aa94762a5,0x0000000000000000,0x0000000000000000,0x72cdee752bb8b8ed,
0xee2c2d5d42a37d69,0x5880b101fda7527b,0x0000000000000000,0x0000000000000000,
0x5880b101f36ab71b,0x0000000000000000,0x4e76791d6aa37d69,0x72cdee7b61a4b6ed,
0x0000000000000000,0x72cdee761298e8d7,0x0000000000000000,0x0000000000000000,
0xdb4fa92131ac3b79,0xdb4fa9213e8113fb,0x0000000000000000,0x0000000000000000,
0xd9bce83488f71093,0x5880b101f3657a23,0x0cd8f084077ba4a1,0x0000000000000000,
0xf2fbc63789f9e823,0x0000000000000000,0x0000000000000000,0xd9a13d4ab098676b,
0xeaa8ee26e4b98b49,0x0000000000000000,0x0000000000000000,0x5880b101f362732d,
0x856b7ba056c358af,0x0000000000000000,0x0000000000000000,0xe151af8b6b8d37f1,
0xe151ad092670c60d,0xe151ad71068f70bf,0x0000000000000000,0x6deedd81c168030b,
0x4cf5a1b0d49b256f,0x72cdee7c8fe11825,0xeaa8cc1f187b9261,0x5880b101f365be95,
0x0000000000000000,0xe151afd8cbf188ed,
};
u8 odin_directives_key_array_1[] = {0x61,0x73,0x73,0x65,0x72,0x74,};
u8 odin_directives_key_array_3[] = {0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_4[] = {0x6c,0x6f,0x61,0x64,0x5f,0x68,0x61,0x73,0x68,};
u8 odin_directives_key_array_7[] = {0x70,0x61,0x63,0x6b,0x65,0x64,};
u8 odin_directives_key_array_8[] = {0x62,0x6f,0x75,0x6e,0x64,0x73,0x5f,0x63,0x68,0x65,0x63,0x6b,};
u8 odin_directives_key_array_9[] = {0x74,0x79,0x70,0x65,};
u8 odin_directives_key_array_12[] = {0x66,0x69,0x6c,0x65,};
u8 odin_directives_key_array_14[] = {0x6e,0x6f,0x5f,0x62,0x6f,0x75,0x6e,0x64,0x73,0x5f,0x63,0x68,0x65,0x63,0x6b,};
u8 odin_directives_key_array_15[] = {0x6e,0x6f,0x5f,0x6e,0x69,0x6c,};
u8 odin_directives_key_array_17[] = {0x62,0x79,0x5f,0x70,0x74,0x72,};
u8 odin_directives_key_array_20[] = {0x70,0x61,0x6e,0x69,0x63,};
u8 odin_directives_key_array_21[] = {0x61,0x6c,0x69,0x67,0x6e,};
u8 odin_directives_key_array_24[] = {0x70,0x72,0x6f,0x63,0x65,0x64,0x75,0x72,0x65,};
u8 odin_directives_key_array_25[] = {0x6c,0x69,0x6e,0x65,};
u8 odin_directives_key_array_26[] = {0x6f,0x70,0x74,0x69,0x6f,0x6e,0x61,0x6c,0x5f,0x6f,0x6b,};
u8 odin_directives_key_array_28[] = {0x66,0x6f,0x72,0x63,0x65,0x5f,0x69,0x6e,0x6c,0x69,0x6e,0x65,};
u8 odin_directives_key_array_31[] = {0x72,0x61,0x77,0x5f,0x75,0x6e,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_32[] = {0x6e,0x6f,0x5f,0x61,0x6c,0x69,0x61,0x73,};
u8 odin_directives_key_array_35[] = {0x73,0x69,0x6d,0x64,};
u8 odin_directives_key_array_36[] = {0x73,0x6f,0x61,};
u8 odin_directives_key_array_39[] = {0x61,0x6e,0x79,0x5f,0x69,0x6e,0x74,};
u8 odin_directives_key_array_40[] = {0x64,0x65,0x66,0x69,0x6e,0x65,0x64,};
u8 odin_directives_key_array_41[] = {0x6c,0x6f,0x61,0x64,0x5f,0x6f,0x72,};
u8 odin_directives_key_array_43[] = {0x63,0x61,0x6c,0x6c,0x65,0x72,0x5f,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_44[] = {0x6f,0x70,0x74,0x69,0x6f,0x6e,0x61,0x6c,0x5f,0x61,0x6c,0x6c,0x6f,0x63,0x61,0x74,0x6f,0x72,0x5f,0x65,0x72,0x72,0x6f,0x72,};
u8 odin_directives_key_array_45[] = {0x63,0x6f,0x6e,0x66,0x69,0x67,};
u8 odin_directives_key_array_46[] = {0x63,0x5f,0x76,0x61,0x72,0x61,0x72,0x67,};
u8 odin_directives_key_array_47[] = {0x6c,0x6f,0x61,0x64,};
u8 odin_directives_key_array_49[] = {0x70,0x61,0x72,0x74,0x69,0x61,0x6c,};
String_Const_u8 odin_directives_key_array[50] = {
{0, 0},
{odin_directives_key_array_1, 6},
{0, 0},
{odin_directives_key_array_3, 8},
{odin_directives_key_array_4, 9},
{0, 0},
{0, 0},
{odin_directives_key_array_7, 6},
{odin_directives_key_array_8, 12},
{odin_directives_key_array_9, 4},
{0, 0},
{0, 0},
{odin_directives_key_array_12, 4},
{0, 0},
{odin_directives_key_array_14, 15},
{odin_directives_key_array_15, 6},
{0, 0},
{odin_directives_key_array_17, 6},
{0, 0},
{0, 0},
{odin_directives_key_array_20, 5},
{odin_directives_key_array_21, 5},
{0, 0},
{0, 0},
{odin_directives_key_array_24, 9},
{odin_directives_key_array_25, 4},
{odin_directives_key_array_26, 11},
{0, 0},
{odin_directives_key_array_28, 12},
{0, 0},
{0, 0},
{odin_directives_key_array_31, 9},
{odin_directives_key_array_32, 8},
{0, 0},
{0, 0},
{odin_directives_key_array_35, 4},
{odin_directives_key_array_36, 3},
{0, 0},
{0, 0},
{odin_directives_key_array_39, 7},
{odin_directives_key_array_40, 7},
{odin_directives_key_array_41, 7},
{0, 0},
{odin_directives_key_array_43, 15},
{odin_directives_key_array_44, 24},
{odin_directives_key_array_45, 6},
{odin_directives_key_array_46, 8},
{odin_directives_key_array_47, 4},
{0, 0},
{odin_directives_key_array_49, 7},
};
Lexeme_Table_Value odin_directives_value_array[50] = {
{0, 0},
{4, TokenOdinKind_Assert},
{0, 0},
{4, TokenOdinKind_Location},
{4, TokenOdinKind_LoadHash},
{0, 0},
{0, 0},
{4, TokenOdinKind_Packed},
{4, TokenOdinKind_BoundsCheck},
{4, TokenOdinKind_Type},
{0, 0},
{0, 0},
{4, TokenOdinKind_File},
{0, 0},
{4, TokenOdinKind_NoBoundsCheck},
{4, TokenOdinKind_NoNil},
{0, 0},
{4, TokenOdinKind_ByPtr},
{0, 0},
{0, 0},
{4, TokenOdinKind_Panic},
{4, TokenOdinKind_Align},
{0, 0},
{0, 0},
{4, TokenOdinKind_Procedure},
{4, TokenOdinKind_Line},
{4, TokenOdinKind_OptionalOk},
{0, 0},
{4, TokenOdinKind_ForceInline},
{0, 0},
{0, 0},
{4, TokenOdinKind_RawUnion},
{4, TokenOdinKind_NoAlias},
{0, 0},
{0, 0},
{4, TokenOdinKind_Simd},
{4, TokenOdinKind_Soa},
{0, 0},
{0, 0},
{4, TokenOdinKind_AnyInt},
{4, TokenOdinKind_Defined},
{4, TokenOdinKind_LoadOr},
{0, 0},
{4, TokenOdinKind_CallerLocation},
{4, TokenOdinKind_OptionalAllocatorError},
{4, TokenOdinKind_Config},
{4, TokenOdinKind_CVararg},
{4, TokenOdinKind_Load},
{0, 0},
{4, TokenOdinKind_Partial},
};
i32 odin_directives_slot_count = 50;
u64 odin_directives_seed = 0x1e264cada69a80fd;
u64 odin_attributes_hash_array[49] = {
0x0000000000000000,0xe0a54cd0e44893a1,0x1507f75d764cd093,0x489bdd427f7d8795,
0x0000000000000000,0xe7dbc35f5bf4494d,0x0000000000000000,0xcb9dffa42d4ae4cd,
0x0000000000000000,0x0000000000000000,0x527eea4383426e47,0xe437947c252564a3,
0xb1d51d8a76c842a3,0xc41ddd5798af11dd,0x27e8f04ce0954c83,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0xe7d9299ca8f0e94d,0xa3e2be6e9bebb3dd,
0x0000000000000000,0x0000000000000000,0x527eed3d91a106b3,0x0000000000000000,
0xd3366a5c252564a3,0x0000000000000000,0xd33721f6559e73b1,0xdb2deb69ad349725,
0x0000000000000000,0x27e8f041facc69cb,0x583a08d4fca62cbb,0x1459322b622b41a1,
0x0000000000000000,0x6df78fccd682eb61,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0xedfd02d6d509fea7,0xe0a54cd0e54cb263,0x0000000000000000,
0x527eedcd642a7b11,0xe7dbc35f5861dea3,0x0000000000000000,0xb6489a7451542ea7,
0x0000000000000000,0x0000000000000000,0xf70db90fe8fd4423,0x527eeda4f4c7ea93,
0x527eed929b61d4b5,
};
u8 odin_attributes_key_array_1[] = {0x69,0x6e,0x69,0x74,};
u8 odin_attributes_key_array_2[] = {0x6f,0x70,0x74,0x69,0x6d,0x69,0x7a,0x61,0x74,0x69,0x6f,0x6e,0x5f,0x6d,0x6f,0x64,0x65,};
u8 odin_attributes_key_array_3[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x70,0x72,0x65,0x66,0x69,0x78,};
u8 odin_attributes_key_array_5[] = {0x6f,0x62,0x6a,0x63,0x5f,0x6e,0x61,0x6d,0x65,};
u8 odin_attributes_key_array_7[] = {0x74,0x68,0x72,0x65,0x61,0x64,0x5f,0x6c,0x6f,0x63,0x61,0x6c,};
u8 odin_attributes_key_array_10[] = {0x62,0x75,0x69,0x6c,0x74,0x69,0x6e,};
u8 odin_attributes_key_array_11[] = {0x65,0x6e,0x61,0x62,0x6c,0x65,0x5f,0x74,0x61,0x72,0x67,0x65,0x74,0x5f,0x66,0x65,0x61,0x74,0x75,0x72,0x65,};
u8 odin_attributes_key_array_12[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x6e,0x6f,0x6e,0x65,};
u8 odin_attributes_key_array_13[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x6f,0x75,0x74,};
u8 odin_attributes_key_array_14[] = {0x65,0x78,0x70,0x6f,0x72,0x74,};
u8 odin_attributes_key_array_18[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x6e,0x61,0x6d,0x65,};
u8 odin_attributes_key_array_19[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x69,0x6e,0x5f,0x6f,0x75,0x74,};
u8 odin_attributes_key_array_22[] = {0x72,0x65,0x71,0x75,0x69,0x72,0x65,};
u8 odin_attributes_key_array_24[] = {0x72,0x65,0x71,0x75,0x69,0x72,0x65,0x5f,0x74,0x61,0x72,0x67,0x65,0x74,0x5f,0x66,0x65,0x61,0x74,0x75,0x72,0x65,};
u8 odin_attributes_key_array_26[] = {0x72,0x65,0x71,0x75,0x69,0x72,0x65,0x5f,0x72,0x65,0x73,0x75,0x6c,0x74,0x73,};
u8 odin_attributes_key_array_27[] = {0x6f,0x62,0x6a,0x63,0x5f,0x69,0x73,0x5f,0x63,0x6c,0x61,0x73,0x73,0x5f,0x6d,0x65,0x74,0x68,0x6f,0x64,};
u8 odin_attributes_key_array_29[] = {0x73,0x74,0x61,0x74,0x69,0x63,};
u8 odin_attributes_key_array_30[] = {0x65,0x78,0x74,0x72,0x61,0x5f,0x6c,0x69,0x6e,0x6b,0x65,0x72,0x5f,0x66,0x6c,0x61,0x67,0x73,};
u8 odin_attributes_key_array_31[] = {0x64,0x69,0x73,0x61,0x62,0x6c,0x65,0x64,};
u8 odin_attributes_key_array_33[] = {0x64,0x65,0x70,0x72,0x65,0x63,0x61,0x74,0x65,0x64,};
u8 odin_attributes_key_array_37[] = {0x64,0x65,0x66,0x61,0x75,0x6c,0x74,0x5f,0x63,0x61,0x6c,0x6c,0x69,0x6e,0x67,0x5f,0x63,0x6f,0x6e,0x76,0x65,0x6e,0x74,0x69,0x6f,0x6e,};
u8 odin_attributes_key_array_38[] = {0x63,0x6f,0x6c,0x64,};
u8 odin_attributes_key_array_40[] = {0x6c,0x69,0x6e,0x6b,0x61,0x67,0x65,};
u8 odin_attributes_key_array_41[] = {0x6f,0x62,0x6a,0x63,0x5f,0x74,0x79,0x70,0x65,};
u8 odin_attributes_key_array_43[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x73,0x65,0x63,0x74,0x69,0x6f,0x6e,};
u8 odin_attributes_key_array_46[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x69,0x6e,};
u8 odin_attributes_key_array_47[] = {0x70,0x72,0x69,0x76,0x61,0x74,0x65,};
u8 odin_attributes_key_array_48[] = {0x77,0x61,0x72,0x6e,0x69,0x6e,0x67,};
String_Const_u8 odin_attributes_key_array[49] = {
{0, 0},
{odin_attributes_key_array_1, 4},
{odin_attributes_key_array_2, 17},
{odin_attributes_key_array_3, 11},
{0, 0},
{odin_attributes_key_array_5, 9},
{0, 0},
{odin_attributes_key_array_7, 12},
{0, 0},
{0, 0},
{odin_attributes_key_array_10, 7},
{odin_attributes_key_array_11, 21},
{odin_attributes_key_array_12, 13},
{odin_attributes_key_array_13, 12},
{odin_attributes_key_array_14, 6},
{0, 0},
{0, 0},
{0, 0},
{odin_attributes_key_array_18, 9},
{odin_attributes_key_array_19, 15},
{0, 0},
{0, 0},
{odin_attributes_key_array_22, 7},
{0, 0},
{odin_attributes_key_array_24, 22},
{0, 0},
{odin_attributes_key_array_26, 15},
{odin_attributes_key_array_27, 20},
{0, 0},
{odin_attributes_key_array_29, 6},
{odin_attributes_key_array_30, 18},
{odin_attributes_key_array_31, 8},
{0, 0},
{odin_attributes_key_array_33, 10},
{0, 0},
{0, 0},
{0, 0},
{odin_attributes_key_array_37, 26},
{odin_attributes_key_array_38, 4},
{0, 0},
{odin_attributes_key_array_40, 7},
{odin_attributes_key_array_41, 9},
{0, 0},
{odin_attributes_key_array_43, 12},
{0, 0},
{0, 0},
{odin_attributes_key_array_46, 11},
{odin_attributes_key_array_47, 7},
{odin_attributes_key_array_48, 7},
};
Lexeme_Table_Value odin_attributes_value_array[49] = {
{0, 0},
{4, TokenOdinKind_AtInit},
{4, TokenOdinKind_AtOptimizationMode},
{4, TokenOdinKind_AtLinkPrefix},
{0, 0},
{4, TokenOdinKind_AtObjcName},
{0, 0},
{4, TokenOdinKind_AtThreadLocal},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtBuiltin},
{4, TokenOdinKind_AtEnableTargetFeature},
{4, TokenOdinKind_AtDeferredNone},
{4, TokenOdinKind_AtDeferredOut},
{4, TokenOdinKind_AtExport},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtLinkName},
{4, TokenOdinKind_AtDeferredInOut},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtRequire},
{0, 0},
{4, TokenOdinKind_AtRequireTargetFeature},
{0, 0},
{4, TokenOdinKind_AtRequireResults},
{4, TokenOdinKind_AtObjcIsClassMethod},
{0, 0},
{4, TokenOdinKind_AtStatic},
{4, TokenOdinKind_AtExtraLinkerFlags},
{4, TokenOdinKind_AtDisabled},
{0, 0},
{4, TokenOdinKind_AtDeprecated},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtDefaultCallingConvention},
{4, TokenOdinKind_AtCold},
{0, 0},
{4, TokenOdinKind_AtLinkage},
{4, TokenOdinKind_AtObjcType},
{0, 0},
{4, TokenOdinKind_AtLinkSection},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtDeferredIn},
{4, TokenOdinKind_AtPrivate},
{4, TokenOdinKind_AtWarning},
};
i32 odin_attributes_slot_count = 49;
u64 odin_attributes_seed = 0x42e6bdadbdf546ae;
struct Lex_State_Odin{
u32 flags_ZF0;
u8 *base;
u8 *delim_first;
u8 *delim_one_past_last;
u8 *emit_ptr;
u8 *ptr;
u8 *opl_ptr;
};
internal void
lex_full_input_odin_init(Lex_State_Odin *state_ptr, String_Const_u8 input){
state_ptr->flags_ZF0 = 0;
state_ptr->base = input.str;
state_ptr->delim_first = input.str;
state_ptr->delim_one_past_last = input.str;
state_ptr->emit_ptr = input.str;
state_ptr->ptr = input.str;
state_ptr->opl_ptr = input.str + input.size;
}
internal b32
lex_full_input_odin_breaks(Arena *arena, Token_List *list, Lex_State_Odin *state_ptr, u64 max){
b32 result = false;
u64 emit_counter = 0;
Lex_State_Odin state;
block_copy_struct(&state, state_ptr);
{
state_label_1: // root
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_EOF;
token.kind = 0;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
result = true;
goto end;
}
}
switch (*state.ptr){
case 0x00:case 0x01:case 0x02:case 0x03:case 0x04:case 0x05:case 0x06:
case 0x07:case 0x08:case 0x0e:case 0x0f:case 0x10:case 0x11:case 0x12:
case 0x13:case 0x14:case 0x15:case 0x16:case 0x17:case 0x18:case 0x19:
case 0x1a:case 0x1b:case 0x1c:case 0x1d:case 0x1e:case 0x1f:case 0x3c:
case 0x55:case 0x5c:case 0x75:case 0x7f:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LexError;
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
goto state_label_1; // root
}break;
case 0x09:case 0x0a:case 0x0b:case 0x0c:case 0x0d:case 0x20:
{
state.ptr += 1;
goto state_label_3; // whitespace
}break;
case 0x21:
{
state.ptr += 1;
goto state_label_41; // op stage
}break;
case 0x22:
{
state.ptr += 1;
goto state_label_18; // string
}break;
case 0x23:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Pound;
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
goto state_label_1; // root
}break;
case 0x24:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Dollar;
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
goto state_label_1; // root
}break;
case 0x25:
{
state.ptr += 1;
goto state_label_36; // op stage
}break;
case 0x26:
{
state.ptr += 1;
goto state_label_37; // op stage
}break;
case 0x27:
{
state.ptr += 1;
state.flags_ZF0 |= 0x8;
goto state_label_18; // string
}break;
case 0x28:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_ParenOp;
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
goto state_label_1; // root
}break;
case 0x29:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_ParenCl;
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
goto state_label_1; // root
}break;
case 0x2a:
{
state.ptr += 1;
goto state_label_45; // op stage
}break;
case 0x2b:
{
state.ptr += 1;
goto state_label_43; // op stage
}break;
case 0x2c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Comma;
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
goto state_label_1; // root
}break;
case 0x2d:
{
state.ptr += 1;
goto state_label_44; // op stage
}break;
case 0x2e:
{
state.ptr += 1;
goto state_label_4; // operator_or_fnumber_dot
}break;
case 0x2f:
{
state.ptr += 1;
goto state_label_5; // operator_or_comment_slash
}break;
case 0x30:
{
state.ptr += 1;
goto state_label_7; // pre_number
}break;
case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:case 0x37:
case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_6; // number
}break;
case 0x3a:
{
state.ptr += 1;
goto state_label_46; // op stage
}break;
case 0x3b:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Semicolon;
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
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
goto state_label_40; // op stage
}break;
case 0x3e:
{
state.ptr += 1;
goto state_label_39; // op stage
}break;
case 0x3f:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Ternary;
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
goto state_label_1; // root
}break;
case 0x40:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_At;
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
goto state_label_1; // root
}break;
default:
{
state.ptr += 1;
goto state_label_2; // identifier
}break;
case 0x5b:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_BrackOp;
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
goto state_label_1; // root
}break;
case 0x5d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_BrackCl;
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
goto state_label_1; // root
}break;
case 0x5e:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Carrot;
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
goto state_label_1; // root
}break;
case 0x60:
{
state.ptr += 1;
goto state_label_31; // raw_string
}break;
case 0x7b:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_BraceOp;
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
goto state_label_1; // root
}break;
case 0x7c:
{
state.ptr += 1;
goto state_label_42; // op stage
}break;
case 0x7d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_BraceCl;
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
goto state_label_1; // root
}break;
case 0x7e:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Xor;
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
do{
Lexeme_Table_Lookup lookup = lexeme_table_lookup(odin_main_keys_hash_array, odin_main_keys_key_array, odin_main_keys_value_array, odin_main_keys_slot_count, odin_main_keys_seed, state.emit_ptr, token.size);
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
token.sub_kind = TokenOdinKind_Identifier;
token.kind = 6;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
Lexeme_Table_Lookup lookup = lexeme_table_lookup(odin_main_keys_hash_array, odin_main_keys_key_array, odin_main_keys_value_array, odin_main_keys_slot_count, odin_main_keys_seed, state.emit_ptr, token.size);
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
token.sub_kind = TokenOdinKind_Identifier;
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
do{
token.sub_kind = TokenOdinKind_Whitespace;
token.kind = 1;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_Whitespace;
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
goto state_label_1; // root
}break;
case 0x09:case 0x0a:case 0x0b:case 0x0c:case 0x0d:case 0x20:
{
state.ptr += 1;
goto state_label_3; // whitespace
}break;
}
}
{
state_label_4: // operator_or_fnumber_dot
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Dot;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_Dot;
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
goto state_label_1; // root
}break;
case 0x2e:
{
state.ptr += 1;
goto state_label_50; // op stage
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_8; // fnumber_decimal
}break;
}
}
{
state_label_5: // operator_or_comment_slash
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Div;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_Div;
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
goto state_label_1; // root
}break;
case 0x2a:
{
state.ptr += 1;
goto state_label_32; // comment_block
}break;
case 0x2f:
{
state.ptr += 1;
goto state_label_34; // comment_line
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_DivEq;
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
goto state_label_1; // root
}break;
}
}
{
state_label_6: // number
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralInteger;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_LiteralInteger;
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
goto state_label_1; // root
}break;
case 0x2e:
{
state.ptr += 1;
goto state_label_8; // fnumber_decimal
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_6; // number
}break;
case 0x45:case 0x65:
{
state.ptr += 1;
goto state_label_9; // fnumber_exponent
}break;
}
}
{
state_label_7: // pre_number
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralInteger;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_LiteralInteger;
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
goto state_label_1; // root
}break;
case 0x2e:
{
state.ptr += 1;
goto state_label_8; // fnumber_decimal
}break;
case 0x42:case 0x62:
{
state.ptr += 1;
state.flags_ZF0 |= 0x4;
goto state_label_16; // number_bin_first
}break;
case 0x45:case 0x65:
{
state.ptr += 1;
goto state_label_9; // fnumber_exponent
}break;
case 0x4f:case 0x6f:
{
state.ptr += 1;
state.flags_ZF0 |= 0x2;
goto state_label_14; // number_oct_first
}break;
case 0x58:case 0x78:
{
state.ptr += 1;
state.flags_ZF0 |= 0x1;
goto state_label_12; // number_hex_first
}break;
}
}
{
state_label_8: // fnumber_decimal
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralFloat64;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_LiteralFloat64;
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
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_8; // fnumber_decimal
}break;
case 0x45:case 0x65:
{
state.ptr += 1;
goto state_label_9; // fnumber_exponent
}break;
case 0x46:case 0x66:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralFloat32;
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
goto state_label_1; // root
}break;
case 0x4c:case 0x6c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralFloat64;
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
goto state_label_1; // root
}break;
}
}
{
state_label_9: // fnumber_exponent
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralFloat64;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_LiteralFloat64;
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
goto state_label_1; // root
}break;
case 0x2b:case 0x2d:
{
state.ptr += 1;
goto state_label_10; // fnumber_exponent_sign
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_11; // fnumber_exponent_digits
}break;
case 0x46:case 0x66:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralFloat32;
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
goto state_label_1; // root
}break;
case 0x4c:case 0x6c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralFloat64;
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
goto state_label_1; // root
}break;
}
}
{
state_label_10: // fnumber_exponent_sign
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralFloat64;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_LiteralFloat64;
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
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_11; // fnumber_exponent_digits
}break;
case 0x46:case 0x66:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralFloat32;
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
goto state_label_1; // root
}break;
case 0x4c:case 0x6c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralFloat64;
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
goto state_label_1; // root
}break;
}
}
{
state_label_11: // fnumber_exponent_digits
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralFloat64;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_LiteralFloat64;
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
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_11; // fnumber_exponent_digits
}break;
case 0x46:case 0x66:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralFloat32;
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
goto state_label_1; // root
}break;
case 0x4c:case 0x6c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralFloat64;
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
goto state_label_1; // root
}break;
}
}
{
state_label_12: // number_hex_first
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_LexError;
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
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x5f:case 0x61:case 0x62:case 0x63:case 0x64:
case 0x65:case 0x66:
{
state.ptr += 1;
goto state_label_13; // number_hex
}break;
}
}
{
state_label_13: // number_hex
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralIntegerHex;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_LiteralIntegerHex;
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
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x5f:case 0x61:case 0x62:case 0x63:case 0x64:
case 0x65:case 0x66:
{
state.ptr += 1;
goto state_label_13; // number_hex
}break;
}
}
{
state_label_14: // number_oct_first
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_LexError;
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
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x5f:
{
state.ptr += 1;
goto state_label_15; // number_oct
}break;
}
}
{
state_label_15: // number_oct
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralIntegerOct;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_LiteralIntegerOct;
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
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x5f:
{
state.ptr += 1;
goto state_label_15; // number_oct
}break;
}
}
{
state_label_16: // number_bin_first
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_LexError;
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
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x5f:
{
state.ptr += 1;
goto state_label_17; // number_bin
}break;
}
}
{
state_label_17: // number_bin
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralIntegerBin;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_LiteralIntegerBin;
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
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x5f:
{
state.ptr += 1;
goto state_label_17; // number_bin
}break;
}
}
{
state_label_18: // string
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_18; // string
}break;
case 0x0a:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LexError;
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
goto state_label_1; // root
}break;
case 0x22:
{
if ((!HasFlag(state.flags_ZF0, 0x8))){
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralString;
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
goto state_label_1; // root
}
state.ptr += 1;
goto state_label_18; // string
}break;
case 0x27:
{
if ((HasFlag(state.flags_ZF0, 0x8))){
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralCharacter;
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
goto state_label_1; // root
}
state.ptr += 1;
goto state_label_18; // string
}break;
case 0x5c:
{
state.ptr += 1;
goto state_label_19; // string_esc
}break;
}
}
{
state_label_19: // string_esc
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_EOF;
token.kind = 0;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
result = true;
goto end;
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_18; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:
{
state.ptr += 1;
goto state_label_20; // string_esc_oct2
}break;
case 0x55:
{
state.ptr += 1;
goto state_label_23; // string_esc_universal_8
}break;
case 0x75:
{
state.ptr += 1;
goto state_label_27; // string_esc_universal_4
}break;
case 0x78:
{
state.ptr += 1;
goto state_label_22; // string_esc_hex
}break;
}
}
{
state_label_20: // string_esc_oct2
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_18; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_18; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:
{
state.ptr += 1;
goto state_label_21; // string_esc_oct1
}break;
}
}
{
state_label_21: // string_esc_oct1
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_18; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_18; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:
{
state.ptr += 1;
goto state_label_18; // string
}break;
}
}
{
state_label_22: // string_esc_hex
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_18; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_18; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_22; // string_esc_hex
}break;
}
}
{
state_label_23: // string_esc_universal_8
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_18; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_18; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_24; // string_esc_universal_7
}break;
}
}
{
state_label_24: // string_esc_universal_7
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_18; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_18; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_25; // string_esc_universal_6
}break;
}
}
{
state_label_25: // string_esc_universal_6
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_18; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_18; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_26; // string_esc_universal_5
}break;
}
}
{
state_label_26: // string_esc_universal_5
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_18; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_18; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_27; // string_esc_universal_4
}break;
}
}
{
state_label_27: // string_esc_universal_4
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_18; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_18; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_28; // string_esc_universal_3
}break;
}
}
{
state_label_28: // string_esc_universal_3
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_18; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_18; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_29; // string_esc_universal_2
}break;
}
}
{
state_label_29: // string_esc_universal_2
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_18; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_18; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_30; // string_esc_universal_1
}break;
}
}
{
state_label_30: // string_esc_universal_1
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_18; // string
}
}
switch (*state.ptr){
default:
{
goto state_label_18; // string
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_18; // string
}break;
}
}
{
state_label_31: // raw_string
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
goto state_label_31; // raw_string
}break;
case 0x60:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LiteralString;
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
goto state_label_1; // root
}break;
}
}
{
state_label_32: // comment_block
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_BlockComment;
token.kind = 3;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_EOF;
token.kind = 0;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
result = true;
goto end;
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_32; // comment_block
}break;
case 0x2a:
{
state.ptr += 1;
goto state_label_33; // comment_block_try_close
}break;
}
}
{
state_label_33: // comment_block_try_close
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_BlockComment;
token.kind = 3;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_EOF;
token.kind = 0;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
result = true;
goto end;
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_32; // comment_block
}break;
case 0x2a:
{
state.ptr += 1;
goto state_label_33; // comment_block_try_close
}break;
case 0x2f:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_BlockComment;
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
goto state_label_1; // root
}break;
}
}
{
state_label_34: // comment_line
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LineComment;
token.kind = 3;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_34; // comment_line
}break;
case 0x0a:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LineComment;
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
goto state_label_1; // root
}break;
case 0x5c:
{
state.ptr += 1;
goto state_label_35; // comment_line_backslashing
}break;
}
}
{
state_label_35: // comment_line_backslashing
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
goto state_label_34; // comment_line
}break;
case 0x0d:
{
state.ptr += 1;
goto state_label_35; // comment_line_backslashing
}break;
}
}
{
state_label_36: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Mod;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_Mod;
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
goto state_label_1; // root
}break;
case 0x25:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_ModMod;
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
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_ModEq;
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
goto state_label_1; // root
}break;
}
}
{
state_label_37: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_And;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_And;
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
goto state_label_1; // root
}break;
case 0x26:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_AndAnd;
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
goto state_label_1; // root
}break;
case 0x7e:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_AndXor;
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
goto state_label_1; // root
}break;
}
}
{
state_label_38: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Less;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_Less;
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
goto state_label_1; // root
}break;
case 0x3c:
{
state.ptr += 1;
goto state_label_48; // op stage
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LessEq;
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
goto state_label_1; // root
}break;
}
}
{
state_label_39: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Grtr;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_Grtr;
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
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_GrtrEq;
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
goto state_label_1; // root
}break;
case 0x3e:
{
state.ptr += 1;
goto state_label_49; // op stage
}break;
}
}
{
state_label_40: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Eq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_Eq;
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
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_EqEq;
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
goto state_label_1; // root
}break;
}
}
{
state_label_41: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Not;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_Not;
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
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_NotEq;
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
goto state_label_1; // root
}break;
}
}
{
state_label_42: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Or;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_Or;
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
goto state_label_1; // root
}break;
case 0x7c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_OrOr;
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
goto state_label_1; // root
}break;
}
}
{
state_label_43: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Plus;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_Plus;
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
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_PlusEq;
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
goto state_label_1; // root
}break;
}
}
{
state_label_44: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Minus;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_Minus;
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
goto state_label_1; // root
}break;
case 0x2d:
{
state.ptr += 1;
goto state_label_47; // op stage
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_MinusEq;
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
goto state_label_1; // root
}break;
case 0x3e:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_MinusGrtr;
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
goto state_label_1; // root
}break;
}
}
{
state_label_45: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Star;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_Star;
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
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_StarEq;
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
goto state_label_1; // root
}break;
}
}
{
state_label_46: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_Colon;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_Colon;
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
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_ColonEq;
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
goto state_label_1; // root
}break;
}
}
{
state_label_47: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_LexError;
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
goto state_label_1; // root
}break;
case 0x2d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_MinusMinusMinus;
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
goto state_label_1; // root
}break;
}
}
{
state_label_48: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LeftLeft;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_LeftLeft;
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
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_LeftLeftEq;
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
goto state_label_1; // root
}break;
}
}
{
state_label_49: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_RightRight;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_RightRight;
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
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_RightRightEq;
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
goto state_label_1; // root
}break;
}
}
{
state_label_50: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_DotDot;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_ZF0 = 0;
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
do{
token.sub_kind = TokenOdinKind_DotDot;
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
goto state_label_1; // root
}break;
case 0x3c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_DotDotLess;
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
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenOdinKind_DotDotEq;
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
goto state_label_1; // root
}break;
}
}
end:;
block_copy_struct(state_ptr, &state);
return(result);
}
internal Token_List
lex_full_input_odin(Arena *arena, String_Const_u8 input){
Lex_State_Odin state = {};
lex_full_input_odin_init(&state, input);
Token_List list = {};
lex_full_input_odin_breaks(arena, &list, &state, max_u64);
return(list);
}
