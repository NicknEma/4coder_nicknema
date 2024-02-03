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
u64 odin_main_keys_hash_array[173] = {
0xb67393a72673702f,0xbed89de0dc85f873,0x86cbcab1ee1d2cc1,0x0000000000000000,
0x0000000000000000,0xbfef5e9e4e751557,0x0000000000000000,0x98bb0ec528dc1cb1,
0x8b3ab60475183873,0x3a6e1bfca806bae3,0x98bb0ec5715c94d5,0x86cbcab1eefe80cd,
0x0000000000000000,0x0000000000000000,0xbfef5e9e4e75efa7,0xbfef5e9e4e754b71,
0x0000000000000000,0x86cbcab1eef84349,0xb67393a726737247,0x86cbcab1eefb59f3,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x86cbcab1ee5b8163,
0x8b3ab604864c50f3,0x0000000000000000,0x98bb0eba0057a583,0x86cbcab1ee0cf42f,
0x463eb56682ce820f,0x8b3ab604866b1bf3,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x8b3ab6049a389e9d,0x0000000000000000,0xb67393a726737305,
0x98bb0eba0057a433,0x0000000000000000,0xa8ad25d1b988cb67,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0xbfef5e9e418f1865,0x0000000000000000,
0x0000000000000000,0xa8ad246084336231,0xbec710a21e82fbd3,0x0000000000000000,
0x86cbcab1ee1d2cf1,0x744c3c2be70392e1,0x98bb0ec761e99b33,0x0000000000000000,
0xbfef5e9e4e75ee73,0x0000000000000000,0x0000000000000000,0xb67393a7267377d5,
0x8b3ab6048668b673,0x0000000000000000,0xbfef5e9e4e75ed1f,0x8b3ab60481b16073,
0x0000000000000000,0xa8ad25f184e1811d,0xbfef5e9e4e7565fb,0xa8ad241c45d29723,
0x98bb0eba641c61e3,0x0000000000000000,0x0000000000000000,0x469b378459dc0b65,
0xbec40ee52fddae85,0x0000000000000000,0x0000000000000000,0x8b3ab6049a063ac7,
0x86cbcab1ee2dcf21,0x744c40ee27d374bd,0xa8ad25c1d0a71ad5,0x0000000000000000,
0xbfef5e9e4e755b39,0x0000000000000000,0xa8ad2374d786e851,0x8b3ab60472f3a5f3,
0x0000000000000000,0xbfef5e9e4e7515a3,0x8b3ab604864c5333,0x8b3ab60475183403,
0x0000000000000000,0x0000000000000000,0x8b3ab60472e86473,0x0000000000000000,
0xbfef5e9e4e75f8b9,0xa8ad23f44af8bb4d,0x8b3ab604774b63f3,0x0000000000000000,
0x0000000000000000,0x8b3ab60481ef2483,0x86cbcab1ee4094b3,0x0000000000000000,
0xbfef5e9e4e74d833,0x8b3ab60481d3c6b3,0x98bb0ec555207b61,0x0000000000000000,
0x0000000000000000,0x8b3ab60472f3a403,0x0000000000000000,0x4e342312ecf1c6b7,
0x0000000000000000,0x86cbcab1eeff4f49,0x86cbcab1ee58c9a7,0xbfef5e9e4e751c7f,
0x0000000000000000,0x8b3ab60483135573,0xbfef5e9e4e74d99b,0x0000000000000000,
0x0000000000000000,0x8b3ab60471ab360f,0x0000000000000000,0x0000000000000000,
0x8b3ab60481b162b3,0xbfef5e9e4e74c763,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x8b3ab6044ef4e4cd,0xa8ad23e8a8fbf04f,0x8b3ab60481d3c573,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x86cbcab1ee2dee6f,
0xbed89de0dc85fba7,0x8b3ab60483135633,0x98bb0ec761e99b83,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0xbfef5e9e4e756443,0x98bb0eb18cbf01a3,0x8b3ab604866b19b3,
0x0000000000000000,0xbfef5e9e4e769b23,0xbfef5e9e4e75b767,0xbfef5e9e4e75132f,
0x86cbcab1ee2ce4ef,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x4e342312ecfe838f,0x0000000000000000,
0xa8ad25d3d213603f,0x98bb0ec5715cad11,0x8b3ab60472e862b3,0x98bb0eb92cdebb15,
0x98bb0ec6e974ce85,0x0000000000000000,0x0000000000000000,0xbfef5e9e4e7565b3,
0x0000000000000000,0xb67393a726737027,0xbede8f4b0c099711,0xb67393a7267370d5,
0x8b3ab6048668a8b3,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,
};
u8 odin_main_keys_key_array_0[] = {0x69,0x66,};
u8 odin_main_keys_key_array_1[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x36,0x34,};
u8 odin_main_keys_key_array_2[] = {0x63,0x61,0x73,0x65,};
u8 odin_main_keys_key_array_5[] = {0x62,0x33,0x32,};
u8 odin_main_keys_key_array_7[] = {0x72,0x61,0x77,0x70,0x74,0x72,};
u8 odin_main_keys_key_array_8[] = {0x66,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_9[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x36,0x34,};
u8 odin_main_keys_key_array_10[] = {0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_11[] = {0x65,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_14[] = {0x66,0x33,0x32,};
u8 odin_main_keys_key_array_15[] = {0x6d,0x61,0x70,};
u8 odin_main_keys_key_array_17[] = {0x62,0x6f,0x6f,0x6c,};
u8 odin_main_keys_key_array_18[] = {0x62,0x38,};
u8 odin_main_keys_key_array_19[] = {0x62,0x79,0x74,0x65,};
u8 odin_main_keys_key_array_23[] = {0x72,0x75,0x6e,0x65,};
u8 odin_main_keys_key_array_24[] = {0x69,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_26[] = {0x69,0x31,0x32,0x38,0x62,0x65,};
u8 odin_main_keys_key_array_27[] = {0x69,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_28[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_29[] = {0x69,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_33[] = {0x75,0x73,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_35[] = {0x64,0x6f,};
u8 odin_main_keys_key_array_36[] = {0x69,0x31,0x32,0x38,0x6c,0x65,};
u8 odin_main_keys_key_array_38[] = {0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,};
u8 odin_main_keys_key_array_42[] = {0x2d,0x2d,0x2d,};
u8 odin_main_keys_key_array_45[] = {0x70,0x61,0x63,0x6b,0x61,0x67,0x65,};
u8 odin_main_keys_key_array_46[] = {0x74,0x72,0x61,0x6e,0x73,0x6d,0x75,0x74,0x65,};
u8 odin_main_keys_key_array_48[] = {0x63,0x61,0x73,0x74,};
u8 odin_main_keys_key_array_49[] = {0x63,0x6f,0x6e,0x74,0x69,0x6e,0x75,0x65,};
u8 odin_main_keys_key_array_50[] = {0x75,0x31,0x32,0x38,0x6c,0x65,};
u8 odin_main_keys_key_array_52[] = {0x66,0x36,0x34,};
u8 odin_main_keys_key_array_55[] = {0x75,0x38,};
u8 odin_main_keys_key_array_56[] = {0x69,0x36,0x34,0x6c,0x65,};
u8 odin_main_keys_key_array_58[] = {0x66,0x31,0x36,};
u8 odin_main_keys_key_array_59[] = {0x75,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_61[] = {0x62,0x69,0x74,0x5f,0x73,0x65,0x74,};
u8 odin_main_keys_key_array_62[] = {0x69,0x31,0x36,};
u8 odin_main_keys_key_array_63[] = {0x63,0x6f,0x6e,0x74,0x65,0x78,0x74,};
u8 odin_main_keys_key_array_64[] = {0x6e,0x6f,0x74,0x5f,0x69,0x6e,};
u8 odin_main_keys_key_array_67[] = {0x66,0x61,0x6c,0x6c,0x74,0x68,0x72,0x6f,0x75,0x67,0x68,};
u8 odin_main_keys_key_array_68[] = {0x6f,0x72,0x5f,0x72,0x65,0x74,0x75,0x72,0x6e,};
u8 odin_main_keys_key_array_71[] = {0x75,0x6e,0x69,0x6f,0x6e,};
u8 odin_main_keys_key_array_72[] = {0x74,0x72,0x75,0x65,};
u8 odin_main_keys_key_array_73[] = {0x64,0x69,0x73,0x74,0x69,0x6e,0x63,0x74,};
u8 odin_main_keys_key_array_74[] = {0x63,0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_76[] = {0x6e,0x69,0x6c,};
u8 odin_main_keys_key_array_78[] = {0x75,0x69,0x6e,0x74,0x70,0x74,0x72,};
u8 odin_main_keys_key_array_79[] = {0x66,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_81[] = {0x62,0x36,0x34,};
u8 odin_main_keys_key_array_82[] = {0x69,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_83[] = {0x66,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_86[] = {0x66,0x36,0x34,0x6c,0x65,};
u8 odin_main_keys_key_array_88[] = {0x61,0x73,0x6d,};
u8 odin_main_keys_key_array_89[] = {0x6f,0x72,0x5f,0x65,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_90[] = {0x64,0x65,0x66,0x65,0x72,};
u8 odin_main_keys_key_array_93[] = {0x77,0x68,0x65,0x72,0x65,};
u8 odin_main_keys_key_array_94[] = {0x75,0x69,0x6e,0x74,};
u8 odin_main_keys_key_array_96[] = {0x75,0x33,0x32,};
u8 odin_main_keys_key_array_97[] = {0x75,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_98[] = {0x73,0x77,0x69,0x74,0x63,0x68,};
u8 odin_main_keys_key_array_101[] = {0x66,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_103[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x32,0x35,0x36,};
u8 odin_main_keys_key_array_105[] = {0x65,0x6e,0x75,0x6d,};
u8 odin_main_keys_key_array_106[] = {0x70,0x72,0x6f,0x63,};
u8 odin_main_keys_key_array_107[] = {0x62,0x31,0x36,};
u8 odin_main_keys_key_array_109[] = {0x75,0x36,0x34,0x62,0x65,};
u8 odin_main_keys_key_array_110[] = {0x75,0x31,0x36,};
u8 odin_main_keys_key_array_113[] = {0x62,0x72,0x65,0x61,0x6b,};
u8 odin_main_keys_key_array_116[] = {0x75,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_117[] = {0x75,0x36,0x34,};
u8 odin_main_keys_key_array_121[] = {0x66,0x61,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_122[] = {0x73,0x69,0x7a,0x65,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_123[] = {0x75,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_127[] = {0x75,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_128[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x33,0x32,};
u8 odin_main_keys_key_array_129[] = {0x75,0x36,0x34,0x6c,0x65,};
u8 odin_main_keys_key_array_130[] = {0x75,0x31,0x32,0x38,0x62,0x65,};
u8 odin_main_keys_key_array_141[] = {0x69,0x33,0x32,};
u8 odin_main_keys_key_array_142[] = {0x69,0x6d,0x70,0x6f,0x72,0x74,};
u8 odin_main_keys_key_array_143[] = {0x69,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_145[] = {0x69,0x6e,0x74,};
u8 odin_main_keys_key_array_146[] = {0x66,0x6f,0x72,};
u8 odin_main_keys_key_array_147[] = {0x61,0x6e,0x79,};
u8 odin_main_keys_key_array_148[] = {0x77,0x68,0x65,0x6e,};
u8 odin_main_keys_key_array_154[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_156[] = {0x66,0x6f,0x72,0x65,0x69,0x67,0x6e,};
u8 odin_main_keys_key_array_157[] = {0x73,0x74,0x72,0x75,0x63,0x74,};
u8 odin_main_keys_key_array_158[] = {0x66,0x36,0x34,0x62,0x65,};
u8 odin_main_keys_key_array_159[] = {0x74,0x79,0x70,0x65,0x69,0x64,};
u8 odin_main_keys_key_array_160[] = {0x72,0x65,0x74,0x75,0x72,0x6e,};
u8 odin_main_keys_key_array_163[] = {0x69,0x36,0x34,};
u8 odin_main_keys_key_array_165[] = {0x69,0x6e,};
u8 odin_main_keys_key_array_166[] = {0x61,0x75,0x74,0x6f,0x5f,0x63,0x61,0x73,0x74,};
u8 odin_main_keys_key_array_167[] = {0x69,0x38,};
u8 odin_main_keys_key_array_168[] = {0x69,0x36,0x34,0x62,0x65,};
String_Const_u8 odin_main_keys_key_array[173] = {
{odin_main_keys_key_array_0, 2},
{odin_main_keys_key_array_1, 9},
{odin_main_keys_key_array_2, 4},
{0, 0},
{0, 0},
{odin_main_keys_key_array_5, 3},
{0, 0},
{odin_main_keys_key_array_7, 6},
{odin_main_keys_key_array_8, 5},
{odin_main_keys_key_array_9, 12},
{odin_main_keys_key_array_10, 6},
{odin_main_keys_key_array_11, 4},
{0, 0},
{0, 0},
{odin_main_keys_key_array_14, 3},
{odin_main_keys_key_array_15, 3},
{0, 0},
{odin_main_keys_key_array_17, 4},
{odin_main_keys_key_array_18, 2},
{odin_main_keys_key_array_19, 4},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_23, 4},
{odin_main_keys_key_array_24, 5},
{0, 0},
{odin_main_keys_key_array_26, 6},
{odin_main_keys_key_array_27, 4},
{odin_main_keys_key_array_28, 10},
{odin_main_keys_key_array_29, 5},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_33, 5},
{0, 0},
{odin_main_keys_key_array_35, 2},
{odin_main_keys_key_array_36, 6},
{0, 0},
{odin_main_keys_key_array_38, 7},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_42, 3},
{0, 0},
{0, 0},
{odin_main_keys_key_array_45, 7},
{odin_main_keys_key_array_46, 9},
{0, 0},
{odin_main_keys_key_array_48, 4},
{odin_main_keys_key_array_49, 8},
{odin_main_keys_key_array_50, 6},
{0, 0},
{odin_main_keys_key_array_52, 3},
{0, 0},
{0, 0},
{odin_main_keys_key_array_55, 2},
{odin_main_keys_key_array_56, 5},
{0, 0},
{odin_main_keys_key_array_58, 3},
{odin_main_keys_key_array_59, 5},
{0, 0},
{odin_main_keys_key_array_61, 7},
{odin_main_keys_key_array_62, 3},
{odin_main_keys_key_array_63, 7},
{odin_main_keys_key_array_64, 6},
{0, 0},
{0, 0},
{odin_main_keys_key_array_67, 11},
{odin_main_keys_key_array_68, 9},
{0, 0},
{0, 0},
{odin_main_keys_key_array_71, 5},
{odin_main_keys_key_array_72, 4},
{odin_main_keys_key_array_73, 8},
{odin_main_keys_key_array_74, 7},
{0, 0},
{odin_main_keys_key_array_76, 3},
{0, 0},
{odin_main_keys_key_array_78, 7},
{odin_main_keys_key_array_79, 5},
{0, 0},
{odin_main_keys_key_array_81, 3},
{odin_main_keys_key_array_82, 5},
{odin_main_keys_key_array_83, 5},
{0, 0},
{0, 0},
{odin_main_keys_key_array_86, 5},
{0, 0},
{odin_main_keys_key_array_88, 3},
{odin_main_keys_key_array_89, 7},
{odin_main_keys_key_array_90, 5},
{0, 0},
{0, 0},
{odin_main_keys_key_array_93, 5},
{odin_main_keys_key_array_94, 4},
{0, 0},
{odin_main_keys_key_array_96, 3},
{odin_main_keys_key_array_97, 5},
{odin_main_keys_key_array_98, 6},
{0, 0},
{0, 0},
{odin_main_keys_key_array_101, 5},
{0, 0},
{odin_main_keys_key_array_103, 13},
{0, 0},
{odin_main_keys_key_array_105, 4},
{odin_main_keys_key_array_106, 4},
{odin_main_keys_key_array_107, 3},
{0, 0},
{odin_main_keys_key_array_109, 5},
{odin_main_keys_key_array_110, 3},
{0, 0},
{0, 0},
{odin_main_keys_key_array_113, 5},
{0, 0},
{0, 0},
{odin_main_keys_key_array_116, 5},
{odin_main_keys_key_array_117, 3},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_121, 5},
{odin_main_keys_key_array_122, 7},
{odin_main_keys_key_array_123, 5},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_127, 4},
{odin_main_keys_key_array_128, 9},
{odin_main_keys_key_array_129, 5},
{odin_main_keys_key_array_130, 6},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_141, 3},
{odin_main_keys_key_array_142, 6},
{odin_main_keys_key_array_143, 5},
{0, 0},
{odin_main_keys_key_array_145, 3},
{odin_main_keys_key_array_146, 3},
{odin_main_keys_key_array_147, 3},
{odin_main_keys_key_array_148, 4},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_154, 13},
{0, 0},
{odin_main_keys_key_array_156, 7},
{odin_main_keys_key_array_157, 6},
{odin_main_keys_key_array_158, 5},
{odin_main_keys_key_array_159, 6},
{odin_main_keys_key_array_160, 6},
{0, 0},
{0, 0},
{odin_main_keys_key_array_163, 3},
{0, 0},
{odin_main_keys_key_array_165, 2},
{odin_main_keys_key_array_166, 9},
{odin_main_keys_key_array_167, 2},
{odin_main_keys_key_array_168, 5},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
};
Lexeme_Table_Value odin_main_keys_value_array[173] = {
{4, TokenOdinKind_If},
{4, TokenOdinKind_Complex64},
{4, TokenOdinKind_Case},
{0, 0},
{0, 0},
{4, TokenOdinKind_B32},
{0, 0},
{4, TokenOdinKind_Rawptr},
{4, TokenOdinKind_F32le},
{4, TokenOdinKind_Quaternion64},
{4, TokenOdinKind_String},
{4, TokenOdinKind_Else},
{0, 0},
{0, 0},
{4, TokenOdinKind_F32},
{4, TokenOdinKind_Map},
{0, 0},
{4, TokenOdinKind_Bool},
{4, TokenOdinKind_B8},
{4, TokenOdinKind_Byte},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Rune},
{4, TokenOdinKind_I32be},
{0, 0},
{4, TokenOdinKind_I128be},
{4, TokenOdinKind_I128},
{4, TokenOdinKind_Complex128},
{4, TokenOdinKind_I16be},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Using},
{0, 0},
{4, TokenOdinKind_Do},
{4, TokenOdinKind_I128le},
{0, 0},
{4, TokenOdinKind_Dynamic},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Uninitialized},
{0, 0},
{0, 0},
{4, TokenOdinKind_Package},
{4, TokenOdinKind_Transmute},
{0, 0},
{4, TokenOdinKind_Cast},
{4, TokenOdinKind_Continue},
{4, TokenOdinKind_U128le},
{0, 0},
{4, TokenOdinKind_F64},
{0, 0},
{0, 0},
{4, TokenOdinKind_U8},
{4, TokenOdinKind_I64le},
{0, 0},
{4, TokenOdinKind_F16},
{4, TokenOdinKind_U32le},
{0, 0},
{4, TokenOdinKind_BitSet},
{4, TokenOdinKind_I16},
{4, TokenOdinKind_Context},
{4, TokenOdinKind_NotIn},
{0, 0},
{0, 0},
{4, TokenOdinKind_Fallthrough},
{4, TokenOdinKind_OrReturn},
{0, 0},
{0, 0},
{4, TokenOdinKind_Union},
{8, TokenOdinKind_LiteralTrue},
{4, TokenOdinKind_Distinct},
{4, TokenOdinKind_Cstring},
{0, 0},
{4, TokenOdinKind_Nil},
{0, 0},
{4, TokenOdinKind_Uintptr},
{4, TokenOdinKind_F16le},
{0, 0},
{4, TokenOdinKind_B64},
{4, TokenOdinKind_I32le},
{4, TokenOdinKind_F32be},
{0, 0},
{0, 0},
{4, TokenOdinKind_F64le},
{0, 0},
{4, TokenOdinKind_Asm},
{4, TokenOdinKind_OrElse},
{4, TokenOdinKind_Defer},
{0, 0},
{0, 0},
{4, TokenOdinKind_Where},
{4, TokenOdinKind_Uint},
{0, 0},
{4, TokenOdinKind_U32},
{4, TokenOdinKind_U16le},
{4, TokenOdinKind_Switch},
{0, 0},
{0, 0},
{4, TokenOdinKind_F16be},
{0, 0},
{4, TokenOdinKind_Quaternion256},
{0, 0},
{4, TokenOdinKind_Enum},
{4, TokenOdinKind_Proc},
{4, TokenOdinKind_B16},
{0, 0},
{4, TokenOdinKind_U64be},
{4, TokenOdinKind_U16},
{0, 0},
{0, 0},
{4, TokenOdinKind_Break},
{0, 0},
{0, 0},
{4, TokenOdinKind_U32be},
{4, TokenOdinKind_U64},
{0, 0},
{0, 0},
{0, 0},
{8, TokenOdinKind_LiteralFalse},
{4, TokenOdinKind_SizeOf},
{4, TokenOdinKind_U16be},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_U128},
{4, TokenOdinKind_Complex32},
{4, TokenOdinKind_U64le},
{4, TokenOdinKind_U128be},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_I32},
{4, TokenOdinKind_Import},
{4, TokenOdinKind_I16le},
{0, 0},
{4, TokenOdinKind_Int},
{4, TokenOdinKind_For},
{4, TokenOdinKind_Any},
{4, TokenOdinKind_When},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Quaternion128},
{0, 0},
{4, TokenOdinKind_Foreign},
{4, TokenOdinKind_Struct},
{4, TokenOdinKind_F64be},
{4, TokenOdinKind_Typeid},
{4, TokenOdinKind_Return},
{0, 0},
{0, 0},
{4, TokenOdinKind_I64},
{0, 0},
{4, TokenOdinKind_In},
{4, TokenOdinKind_AutoCast},
{4, TokenOdinKind_I8},
{4, TokenOdinKind_I64be},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
};
i32 odin_main_keys_slot_count = 173;
u64 odin_main_keys_seed = 0xfcf9c5b38b6b124e;
u64 odin_directives_hash_array[51] = {
0xb690f9ed2bea2d59,0x0000000000000000,0xc93afa60a23735f9,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0xdc32c7e07e8edcfd,0xe62660b38455abc7,
0x0000000000000000,0x631fff9160b84c5d,0x0000000000000000,0xed67f168fc35eb3d,
0xed67f168fc441935,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0xc74fd79ffadd5025,0x31df74fbde792215,0x0000000000000000,0xe62663f24d3b16ab,
0x0000000000000000,0x0000000000000000,0xb6911b04a11c91c5,0x0000000000000000,
0x97e83bea8271b199,0x0000000000000000,0x631fc19f42c8bba3,0x0000000000000000,
0xc93f659a69a96799,0x57deca6f7a03bf6f,0x0000000000000000,0xe4f8ecaac8bc91c5,
0xe62663f3ecbd9f0b,0xed67f168fc0defab,0xe62660b0cde05369,0x0000000000000000,
0x0000000000000000,0xe626641ae9d8cb71,0x0000000000000000,0x0000000000000000,
0xdc32c7eec7ebd909,0x0000000000000000,0x316b54566c4ec5fb,0x631fff78502d23c3,
0x631ebcbd35677189,0x31df864ff4378199,0x0000000000000000,0xd32080c82df46505,
0xed67f168fc49ad59,0xed67f168fc1ade8b,0xc93b03ee474ef647,
};
u8 odin_directives_key_array_0[] = {0x66,0x6f,0x72,0x63,0x65,0x5f,0x69,0x6e,0x6c,0x69,0x6e,0x65,};
u8 odin_directives_key_array_2[] = {0x70,0x72,0x6f,0x63,0x65,0x64,0x75,0x72,0x65,};
u8 odin_directives_key_array_6[] = {0x70,0x61,0x6e,0x69,0x63,};
u8 odin_directives_key_array_7[] = {0x62,0x79,0x5f,0x70,0x74,0x72,};
u8 odin_directives_key_array_9[] = {0x6c,0x6f,0x61,0x64,0x5f,0x6f,0x72,};
u8 odin_directives_key_array_11[] = {0x74,0x79,0x70,0x65,};
u8 odin_directives_key_array_12[] = {0x66,0x69,0x6c,0x65,};
u8 odin_directives_key_array_16[] = {0x6f,0x70,0x74,0x69,0x6f,0x6e,0x61,0x6c,0x5f,0x6f,0x6b,};
u8 odin_directives_key_array_17[] = {0x6e,0x6f,0x5f,0x61,0x6c,0x69,0x61,0x73,};
u8 odin_directives_key_array_19[] = {0x6e,0x6f,0x5f,0x6e,0x69,0x6c,};
u8 odin_directives_key_array_22[] = {0x6e,0x6f,0x5f,0x62,0x6f,0x75,0x6e,0x64,0x73,0x5f,0x63,0x68,0x65,0x63,0x6b,};
u8 odin_directives_key_array_24[] = {0x63,0x61,0x6c,0x6c,0x65,0x72,0x5f,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_26[] = {0x64,0x65,0x66,0x69,0x6e,0x65,0x64,};
u8 odin_directives_key_array_28[] = {0x72,0x61,0x77,0x5f,0x75,0x6e,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_29[] = {0x73,0x6f,0x61,};
u8 odin_directives_key_array_31[] = {0x62,0x6f,0x75,0x6e,0x64,0x73,0x5f,0x63,0x68,0x65,0x63,0x6b,};
u8 odin_directives_key_array_32[] = {0x70,0x61,0x63,0x6b,0x65,0x64,};
u8 odin_directives_key_array_33[] = {0x73,0x69,0x6d,0x64,};
u8 odin_directives_key_array_34[] = {0x61,0x73,0x73,0x65,0x72,0x74,};
u8 odin_directives_key_array_37[] = {0x63,0x6f,0x6e,0x66,0x69,0x67,};
u8 odin_directives_key_array_40[] = {0x61,0x6c,0x69,0x67,0x6e,};
u8 odin_directives_key_array_42[] = {0x63,0x5f,0x76,0x61,0x72,0x61,0x72,0x67,};
u8 odin_directives_key_array_43[] = {0x70,0x61,0x72,0x74,0x69,0x61,0x6c,};
u8 odin_directives_key_array_44[] = {0x61,0x6e,0x79,0x5f,0x69,0x6e,0x74,};
u8 odin_directives_key_array_45[] = {0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_47[] = {0x6f,0x70,0x74,0x69,0x6f,0x6e,0x61,0x6c,0x5f,0x61,0x6c,0x6c,0x6f,0x63,0x61,0x74,0x6f,0x72,0x5f,0x65,0x72,0x72,0x6f,0x72,};
u8 odin_directives_key_array_48[] = {0x6c,0x69,0x6e,0x65,};
u8 odin_directives_key_array_49[] = {0x6c,0x6f,0x61,0x64,};
u8 odin_directives_key_array_50[] = {0x6c,0x6f,0x61,0x64,0x5f,0x68,0x61,0x73,0x68,};
String_Const_u8 odin_directives_key_array[51] = {
{odin_directives_key_array_0, 12},
{0, 0},
{odin_directives_key_array_2, 9},
{0, 0},
{0, 0},
{0, 0},
{odin_directives_key_array_6, 5},
{odin_directives_key_array_7, 6},
{0, 0},
{odin_directives_key_array_9, 7},
{0, 0},
{odin_directives_key_array_11, 4},
{odin_directives_key_array_12, 4},
{0, 0},
{0, 0},
{0, 0},
{odin_directives_key_array_16, 11},
{odin_directives_key_array_17, 8},
{0, 0},
{odin_directives_key_array_19, 6},
{0, 0},
{0, 0},
{odin_directives_key_array_22, 15},
{0, 0},
{odin_directives_key_array_24, 15},
{0, 0},
{odin_directives_key_array_26, 7},
{0, 0},
{odin_directives_key_array_28, 9},
{odin_directives_key_array_29, 3},
{0, 0},
{odin_directives_key_array_31, 12},
{odin_directives_key_array_32, 6},
{odin_directives_key_array_33, 4},
{odin_directives_key_array_34, 6},
{0, 0},
{0, 0},
{odin_directives_key_array_37, 6},
{0, 0},
{0, 0},
{odin_directives_key_array_40, 5},
{0, 0},
{odin_directives_key_array_42, 8},
{odin_directives_key_array_43, 7},
{odin_directives_key_array_44, 7},
{odin_directives_key_array_45, 8},
{0, 0},
{odin_directives_key_array_47, 24},
{odin_directives_key_array_48, 4},
{odin_directives_key_array_49, 4},
{odin_directives_key_array_50, 9},
};
Lexeme_Table_Value odin_directives_value_array[51] = {
{4, TokenOdinKind_ForceInline},
{0, 0},
{4, TokenOdinKind_Procedure},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Panic},
{4, TokenOdinKind_ByPtr},
{0, 0},
{4, TokenOdinKind_LoadOr},
{0, 0},
{4, TokenOdinKind_Type},
{4, TokenOdinKind_File},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_OptionalOk},
{4, TokenOdinKind_NoAlias},
{0, 0},
{4, TokenOdinKind_NoNil},
{0, 0},
{0, 0},
{4, TokenOdinKind_NoBoundsCheck},
{0, 0},
{4, TokenOdinKind_CallerLocation},
{0, 0},
{4, TokenOdinKind_Defined},
{0, 0},
{4, TokenOdinKind_RawUnion},
{4, TokenOdinKind_Soa},
{0, 0},
{4, TokenOdinKind_BoundsCheck},
{4, TokenOdinKind_Packed},
{4, TokenOdinKind_Simd},
{4, TokenOdinKind_Assert},
{0, 0},
{0, 0},
{4, TokenOdinKind_Config},
{0, 0},
{0, 0},
{4, TokenOdinKind_Align},
{0, 0},
{4, TokenOdinKind_CVararg},
{4, TokenOdinKind_Partial},
{4, TokenOdinKind_AnyInt},
{4, TokenOdinKind_Location},
{0, 0},
{4, TokenOdinKind_OptionalAllocatorError},
{4, TokenOdinKind_Line},
{4, TokenOdinKind_Load},
{4, TokenOdinKind_LoadHash},
};
i32 odin_directives_slot_count = 51;
u64 odin_directives_seed = 0x7a60935667326f14;
u64 odin_attributes_hash_array[49] = {
0x0000000000000000,0x4c37b30f62265bbf,0x03ffbf13d3e907fd,0x0000000000000000,
0xe9dc863fb9446f57,0x0000000000000000,0x0000000000000000,0x6b09f87a926134b5,
0x03ffbf13d2123c17,0x278426fe61d09987,0x0000000000000000,0xa3afea3260446f57,
0x0000000000000000,0xac79ef12021fa821,0x876b5f3e90d26567,0xf6fa9ae8ae6382d7,
0x0000000000000000,0xe08d7f582405debf,0x0000000000000000,0xe157621867d58cb9,
0x3d661eb4b2f0fe99,0x0000000000000000,0xe08d7f582479acb9,0x3c34264cc00f89cd,
0x0000000000000000,0x7ebc43fba34f925b,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x7953dafadf2459f1,
0x0c1347c657868dab,0x7ebc438f4754952f,0x0000000000000000,0x0000000000000000,
0x7ebc4de02b719965,0x7ebc4dd9faf3ab89,0xfd05652c0eaea9cb,0x7ebc4d93f9f9d517,
0x0000000000000000,0x0f7b79dd5e1970ff,0x4effb279618c6e09,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x7518e6a911de9be5,0x0f7b79c275fe39ef,
0x917a48620eb67689,
};
u8 odin_attributes_key_array_1[] = {0x65,0x78,0x74,0x72,0x61,0x5f,0x6c,0x69,0x6e,0x6b,0x65,0x72,0x5f,0x66,0x6c,0x61,0x67,0x73,};
u8 odin_attributes_key_array_2[] = {0x69,0x6e,0x69,0x74,};
u8 odin_attributes_key_array_4[] = {0x65,0x6e,0x61,0x62,0x6c,0x65,0x5f,0x74,0x61,0x72,0x67,0x65,0x74,0x5f,0x66,0x65,0x61,0x74,0x75,0x72,0x65,};
u8 odin_attributes_key_array_7[] = {0x64,0x69,0x73,0x61,0x62,0x6c,0x65,0x64,};
u8 odin_attributes_key_array_8[] = {0x63,0x6f,0x6c,0x64,};
u8 odin_attributes_key_array_9[] = {0x6f,0x70,0x74,0x69,0x6d,0x69,0x7a,0x61,0x74,0x69,0x6f,0x6e,0x5f,0x6d,0x6f,0x64,0x65,};
u8 odin_attributes_key_array_11[] = {0x72,0x65,0x71,0x75,0x69,0x72,0x65,0x5f,0x74,0x61,0x72,0x67,0x65,0x74,0x5f,0x66,0x65,0x61,0x74,0x75,0x72,0x65,};
u8 odin_attributes_key_array_13[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x70,0x72,0x65,0x66,0x69,0x78,};
u8 odin_attributes_key_array_14[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x69,0x6e,};
u8 odin_attributes_key_array_15[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x6e,0x6f,0x6e,0x65,};
u8 odin_attributes_key_array_17[] = {0x6f,0x62,0x6a,0x63,0x5f,0x74,0x79,0x70,0x65,};
u8 odin_attributes_key_array_19[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x6e,0x61,0x6d,0x65,};
u8 odin_attributes_key_array_20[] = {0x6f,0x62,0x6a,0x63,0x5f,0x69,0x73,0x5f,0x63,0x6c,0x61,0x73,0x73,0x5f,0x6d,0x65,0x74,0x68,0x6f,0x64,};
u8 odin_attributes_key_array_22[] = {0x6f,0x62,0x6a,0x63,0x5f,0x6e,0x61,0x6d,0x65,};
u8 odin_attributes_key_array_23[] = {0x72,0x65,0x71,0x75,0x69,0x72,0x65,0x5f,0x72,0x65,0x73,0x75,0x6c,0x74,0x73,};
u8 odin_attributes_key_array_25[] = {0x62,0x75,0x69,0x6c,0x74,0x69,0x6e,};
u8 odin_attributes_key_array_31[] = {0x74,0x68,0x72,0x65,0x61,0x64,0x5f,0x6c,0x6f,0x63,0x61,0x6c,};
u8 odin_attributes_key_array_32[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x73,0x65,0x63,0x74,0x69,0x6f,0x6e,};
u8 odin_attributes_key_array_33[] = {0x72,0x65,0x71,0x75,0x69,0x72,0x65,};
u8 odin_attributes_key_array_36[] = {0x6c,0x69,0x6e,0x6b,0x61,0x67,0x65,};
u8 odin_attributes_key_array_37[] = {0x77,0x61,0x72,0x6e,0x69,0x6e,0x67,};
u8 odin_attributes_key_array_38[] = {0x64,0x65,0x66,0x61,0x75,0x6c,0x74,0x5f,0x63,0x61,0x6c,0x6c,0x69,0x6e,0x67,0x5f,0x63,0x6f,0x6e,0x76,0x65,0x6e,0x74,0x69,0x6f,0x6e,};
u8 odin_attributes_key_array_39[] = {0x70,0x72,0x69,0x76,0x61,0x74,0x65,};
u8 odin_attributes_key_array_41[] = {0x65,0x78,0x70,0x6f,0x72,0x74,};
u8 odin_attributes_key_array_42[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x69,0x6e,0x5f,0x6f,0x75,0x74,};
u8 odin_attributes_key_array_46[] = {0x64,0x65,0x70,0x72,0x65,0x63,0x61,0x74,0x65,0x64,};
u8 odin_attributes_key_array_47[] = {0x73,0x74,0x61,0x74,0x69,0x63,};
u8 odin_attributes_key_array_48[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x6f,0x75,0x74,};
String_Const_u8 odin_attributes_key_array[49] = {
{0, 0},
{odin_attributes_key_array_1, 18},
{odin_attributes_key_array_2, 4},
{0, 0},
{odin_attributes_key_array_4, 21},
{0, 0},
{0, 0},
{odin_attributes_key_array_7, 8},
{odin_attributes_key_array_8, 4},
{odin_attributes_key_array_9, 17},
{0, 0},
{odin_attributes_key_array_11, 22},
{0, 0},
{odin_attributes_key_array_13, 11},
{odin_attributes_key_array_14, 11},
{odin_attributes_key_array_15, 13},
{0, 0},
{odin_attributes_key_array_17, 9},
{0, 0},
{odin_attributes_key_array_19, 9},
{odin_attributes_key_array_20, 20},
{0, 0},
{odin_attributes_key_array_22, 9},
{odin_attributes_key_array_23, 15},
{0, 0},
{odin_attributes_key_array_25, 7},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_attributes_key_array_31, 12},
{odin_attributes_key_array_32, 12},
{odin_attributes_key_array_33, 7},
{0, 0},
{0, 0},
{odin_attributes_key_array_36, 7},
{odin_attributes_key_array_37, 7},
{odin_attributes_key_array_38, 26},
{odin_attributes_key_array_39, 7},
{0, 0},
{odin_attributes_key_array_41, 6},
{odin_attributes_key_array_42, 15},
{0, 0},
{0, 0},
{0, 0},
{odin_attributes_key_array_46, 10},
{odin_attributes_key_array_47, 6},
{odin_attributes_key_array_48, 12},
};
Lexeme_Table_Value odin_attributes_value_array[49] = {
{0, 0},
{4, TokenOdinKind_AtExtraLinkerFlags},
{4, TokenOdinKind_AtInit},
{0, 0},
{4, TokenOdinKind_AtEnableTargetFeature},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtDisabled},
{4, TokenOdinKind_AtCold},
{4, TokenOdinKind_AtOptimizationMode},
{0, 0},
{4, TokenOdinKind_AtRequireTargetFeature},
{0, 0},
{4, TokenOdinKind_AtLinkPrefix},
{4, TokenOdinKind_AtDeferredIn},
{4, TokenOdinKind_AtDeferredNone},
{0, 0},
{4, TokenOdinKind_AtObjcType},
{0, 0},
{4, TokenOdinKind_AtLinkName},
{4, TokenOdinKind_AtObjcIsClassMethod},
{0, 0},
{4, TokenOdinKind_AtObjcName},
{4, TokenOdinKind_AtRequireResults},
{0, 0},
{4, TokenOdinKind_AtBuiltin},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtThreadLocal},
{4, TokenOdinKind_AtLinkSection},
{4, TokenOdinKind_AtRequire},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtLinkage},
{4, TokenOdinKind_AtWarning},
{4, TokenOdinKind_AtDefaultCallingConvention},
{4, TokenOdinKind_AtPrivate},
{0, 0},
{4, TokenOdinKind_AtExport},
{4, TokenOdinKind_AtDeferredInOut},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtDeprecated},
{4, TokenOdinKind_AtStatic},
{4, TokenOdinKind_AtDeferredOut},
};
i32 odin_attributes_slot_count = 49;
u64 odin_attributes_seed = 0xe05223f13de69afa;
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
case 0x5c:case 0x7f:
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
goto state_label_48; // op stage
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
goto state_label_49; // op stage
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
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
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
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
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
case 0x37:
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
case 0x37:
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
case 0x30:case 0x31:
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
case 0x30:case 0x31:
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
goto state_label_46; // op stage
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
goto state_label_47; // op stage
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
token.sub_kind = TokenOdinKind_MinusRight;
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
state_label_47: // op stage
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
state_label_48: // op stage
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
state_label_49: // op stage
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
token.sub_kind = TokenOdinKind_DotDotLeft;
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
