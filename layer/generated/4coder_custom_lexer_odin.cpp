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
u64 odin_main_keys_hash_array[185] = {
0x0000000000000000,0x0000000000000000,0x3256f31ec7519eab,0x0000000000000000,
0x32db764cc0ca4111,0x0000000000000000,0x0000000000000000,0x9b5316f172a4abf7,
0xe32726e517b04403,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0xf193dbfdcd31e2a7,0x04123d40cf282fb1,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x7324352ddeb8f023,
0xf1aa7b3eb8601f61,0x732431eaa22f4fa3,0x9b5316f172a4f38f,0x0000000000000000,
0xacf1190bc5c8350f,0x0000000000000000,0xe32726e4db64923b,0xf193dbf25acd9081,
0x9b5316f172a4f397,0x9b5316f172a49097,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0xe32726e51614cc4b,0x0000000000000000,0x7324347aa3e83e71,
0x1f8646f1ca3e7a13,0xf1aa7b3eb8601e01,0x0000000000000000,0x0000000000000000,
0xe32726e52dc8b8f3,0xf193dbfe5460f64b,0x0000000000000000,0x0000000000000000,
0xe32726e517be74f3,0x312372f6ec8232af,0x9451762c5de8e809,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x9b5316f172a4f691,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0xf193dbfdcda21c05,
0x9451760a05567a0b,0xf193dbfdc1aff0ef,0x0000000000000000,0xe32726e511352073,
0x0000000000000000,0x1f8646f1cafbf395,0x0000000000000000,0xe32726e517be7e6b,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0xacf1190bc5c85a15,
0x94517618c2717851,0x0000000000000000,0x1f8646f1ca30eb4b,0x9b5316f172a50ff1,
0x0000000000000000,0x0000000000000000,0x1f8646f1ca36f511,0x9b5316f172a4ab81,
0x1f8646f1ca0d7495,0x0000000000000000,0x94516d5e43169013,0xf193dbf25acc7851,
0x9b5316f172a3b3a7,0x9451623272097013,0x0000000000000000,0xe32726e51135208b,
0xe32726e4d9f8868b,0x1f8646f1ca3c07b9,0xe32726e4d9f27d83,0xf193dbc2d3136123,
0x0000000000000000,0x9b5316f172b65bbb,0x0000000000000000,0x378844d183ccb0e3,
0x0000000000000000,0x9b5316f172a3741d,0x0000000000000000,0x0000000000000000,
0xe32726e4de6dc4f3,0x3af9f7b5221dbe95,0x0000000000000000,0x0000000000000000,
0x9b5316f172a3b01f,0x1f8646f1caf95e83,0x0000000000000000,0x0000000000000000,
0x312372f6ec820f81,0xe32726e511c339b3,0x9b5316f172a51f41,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x9b5316f172a48a6b,0x0000000000000000,0xf193dbfe5460f523,
0xe32726e511c0cdb3,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x9451762e3f449efd,0xf193dbf0eff3fb15,0x945161fc0e501577,0xe32726e511c3390b,
0x0000000000000000,0xf193dbc2d3136e4b,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0xe32726e511c0c96b,0xf1aa7b3eb8601f17,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x9b5316f172a3b041,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0xf1aa7b3eb8601f1f,0x9b5316f172a50bdf,
0xf1aa7b3eb8601959,0xe32726e4de6dde6b,0x0000000000000000,0x0000000000000000,
0xe32726e4d9f27c4b,0xf193dbfd4ac16b1f,0x94516219f7fb2a13,0x1f8646f1ca3d0e4b,
0x0000000000000000,0x0000000000000000,0x5f3eba459cedc535,0xe32726e517b0454b,
0x1f8646f1caf0e9a1,0x0000000000000000,0x0000000000000000,0x1f8646f1ca36f563,
0xe32726e4c28ba263,0xe32726e52c258411,0x0000000000000000,0x0000000000000000,
0x9b5316f172a38c39,0xe32726e4db4d1b51,0x0000000000000000,0x1f8646f1cafa4c81,
0xe32726e510d6c613,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x32babfc37433f0ef,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x1f8646f1cafbb8c3,0x0000000000000000,0xe32726e4d9f88573,0xe32726e51614cf03,
0x9b5316f172a4c3bf,0xf193dbc9ce888ac1,0xf1aa7b3eb8601dd5,0x0000000000000000,
0x945174e80087884d,0x1f8646f1cac63be7,0x9b5316f172a4a84f,0x7322564a83aa2411,
0x9b5316f172a50fa7,
};
u8 odin_main_keys_key_array_2[] = {0x74,0x72,0x61,0x6e,0x73,0x6d,0x75,0x74,0x65,};
u8 odin_main_keys_key_array_4[] = {0x61,0x75,0x74,0x6f,0x5f,0x63,0x61,0x73,0x74,};
u8 odin_main_keys_key_array_7[] = {0x62,0x31,0x36,};
u8 odin_main_keys_key_array_8[] = {0x69,0x36,0x34,0x62,0x65,};
u8 odin_main_keys_key_array_12[] = {0x72,0x61,0x77,0x70,0x74,0x72,};
u8 odin_main_keys_key_array_13[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x36,0x34,};
u8 odin_main_keys_key_array_19[] = {0x63,0x6f,0x6e,0x74,0x69,0x6e,0x75,0x65,};
u8 odin_main_keys_key_array_20[] = {0x69,0x38,};
u8 odin_main_keys_key_array_21[] = {0x61,0x6c,0x69,0x67,0x6e,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_22[] = {0x66,0x33,0x32,};
u8 odin_main_keys_key_array_24[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x32,0x35,0x36,};
u8 odin_main_keys_key_array_26[] = {0x75,0x6e,0x69,0x6f,0x6e,};
u8 odin_main_keys_key_array_27[] = {0x73,0x74,0x72,0x75,0x63,0x74,};
u8 odin_main_keys_key_array_28[] = {0x66,0x31,0x36,};
u8 odin_main_keys_key_array_29[] = {0x61,0x6e,0x79,};
u8 odin_main_keys_key_array_33[] = {0x66,0x36,0x34,0x6c,0x65,};
u8 odin_main_keys_key_array_35[] = {0x64,0x69,0x73,0x74,0x69,0x6e,0x63,0x74,};
u8 odin_main_keys_key_array_36[] = {0x65,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_37[] = {0x64,0x6f,};
u8 odin_main_keys_key_array_40[] = {0x64,0x65,0x66,0x65,0x72,};
u8 odin_main_keys_key_array_41[] = {0x75,0x31,0x32,0x38,0x6c,0x65,};
u8 odin_main_keys_key_array_44[] = {0x69,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_45[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x33,0x32,};
u8 odin_main_keys_key_array_46[] = {0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,};
u8 odin_main_keys_key_array_50[] = {0x66,0x36,0x34,};
u8 odin_main_keys_key_array_55[] = {0x74,0x79,0x70,0x65,0x69,0x64,};
u8 odin_main_keys_key_array_56[] = {0x66,0x6f,0x72,0x65,0x69,0x67,0x6e,};
u8 odin_main_keys_key_array_57[] = {0x72,0x65,0x74,0x75,0x72,0x6e,};
u8 odin_main_keys_key_array_59[] = {0x69,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_61[] = {0x75,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_63[] = {0x69,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_67[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_68[] = {0x63,0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_70[] = {0x62,0x79,0x74,0x65,};
u8 odin_main_keys_key_array_71[] = {0x69,0x36,0x34,};
u8 odin_main_keys_key_array_74[] = {0x63,0x61,0x73,0x74,};
u8 odin_main_keys_key_array_75[] = {0x62,0x36,0x34,};
u8 odin_main_keys_key_array_76[] = {0x69,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_78[] = {0x6f,0x72,0x5f,0x65,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_79[] = {0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_80[] = {0x75,0x31,0x36,};
u8 odin_main_keys_key_array_81[] = {0x73,0x69,0x7a,0x65,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_83[] = {0x69,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_84[] = {0x75,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_85[] = {0x62,0x6f,0x6f,0x6c,};
u8 odin_main_keys_key_array_86[] = {0x75,0x36,0x34,0x62,0x65,};
u8 odin_main_keys_key_array_87[] = {0x69,0x31,0x32,0x38,0x62,0x65,};
u8 odin_main_keys_key_array_89[] = {0x2d,0x2d,0x2d,};
u8 odin_main_keys_key_array_91[] = {0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_93[] = {0x6e,0x69,0x6c,};
u8 odin_main_keys_key_array_96[] = {0x75,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_97[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_100[] = {0x75,0x33,0x32,};
u8 odin_main_keys_key_array_101[] = {0x72,0x75,0x6e,0x65,};
u8 odin_main_keys_key_array_104[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x36,0x34,};
u8 odin_main_keys_key_array_105[] = {0x66,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_106[] = {0x69,0x6e,0x74,};
u8 odin_main_keys_key_array_113[] = {0x61,0x73,0x6d,};
u8 odin_main_keys_key_array_115[] = {0x75,0x31,0x32,0x38,0x62,0x65,};
u8 odin_main_keys_key_array_116[] = {0x66,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_120[] = {0x63,0x6f,0x6e,0x74,0x65,0x78,0x74,};
u8 odin_main_keys_key_array_121[] = {0x73,0x77,0x69,0x74,0x63,0x68,};
u8 odin_main_keys_key_array_122[] = {0x75,0x69,0x6e,0x74,0x70,0x74,0x72,};
u8 odin_main_keys_key_array_123[] = {0x66,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_125[] = {0x69,0x31,0x32,0x38,0x6c,0x65,};
u8 odin_main_keys_key_array_129[] = {0x66,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_130[] = {0x69,0x66,};
u8 odin_main_keys_key_array_134[] = {0x75,0x36,0x34,};
u8 odin_main_keys_key_array_138[] = {0x69,0x6e,};
u8 odin_main_keys_key_array_139[] = {0x69,0x33,0x32,};
u8 odin_main_keys_key_array_140[] = {0x75,0x38,};
u8 odin_main_keys_key_array_141[] = {0x75,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_144[] = {0x75,0x36,0x34,0x6c,0x65,};
u8 odin_main_keys_key_array_145[] = {0x6e,0x6f,0x74,0x5f,0x69,0x6e,};
u8 odin_main_keys_key_array_146[] = {0x70,0x61,0x63,0x6b,0x61,0x67,0x65,};
u8 odin_main_keys_key_array_147[] = {0x65,0x6e,0x75,0x6d,};
u8 odin_main_keys_key_array_150[] = {0x66,0x61,0x6c,0x6c,0x74,0x68,0x72,0x6f,0x75,0x67,0x68,};
u8 odin_main_keys_key_array_151[] = {0x69,0x36,0x34,0x6c,0x65,};
u8 odin_main_keys_key_array_152[] = {0x70,0x72,0x6f,0x63,};
u8 odin_main_keys_key_array_155[] = {0x63,0x61,0x73,0x65,};
u8 odin_main_keys_key_array_156[] = {0x77,0x68,0x65,0x72,0x65,};
u8 odin_main_keys_key_array_157[] = {0x62,0x72,0x65,0x61,0x6b,};
u8 odin_main_keys_key_array_160[] = {0x6d,0x61,0x70,};
u8 odin_main_keys_key_array_161[] = {0x75,0x73,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_163[] = {0x75,0x69,0x6e,0x74,};
u8 odin_main_keys_key_array_164[] = {0x66,0x61,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_168[] = {0x6f,0x72,0x5f,0x72,0x65,0x74,0x75,0x72,0x6e,};
u8 odin_main_keys_key_array_172[] = {0x74,0x72,0x75,0x65,};
u8 odin_main_keys_key_array_174[] = {0x75,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_175[] = {0x66,0x36,0x34,0x62,0x65,};
u8 odin_main_keys_key_array_176[] = {0x66,0x6f,0x72,};
u8 odin_main_keys_key_array_177[] = {0x69,0x6d,0x70,0x6f,0x72,0x74,};
u8 odin_main_keys_key_array_178[] = {0x62,0x38,};
u8 odin_main_keys_key_array_180[] = {0x62,0x69,0x74,0x5f,0x73,0x65,0x74,};
u8 odin_main_keys_key_array_181[] = {0x77,0x68,0x65,0x6e,};
u8 odin_main_keys_key_array_182[] = {0x62,0x33,0x32,};
u8 odin_main_keys_key_array_183[] = {0x6f,0x72,0x5f,0x62,0x72,0x65,0x61,0x6b,};
u8 odin_main_keys_key_array_184[] = {0x69,0x31,0x36,};
String_Const_u8 odin_main_keys_key_array[185] = {
{0, 0},
{0, 0},
{odin_main_keys_key_array_2, 9},
{0, 0},
{odin_main_keys_key_array_4, 9},
{0, 0},
{0, 0},
{odin_main_keys_key_array_7, 3},
{odin_main_keys_key_array_8, 5},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_12, 6},
{odin_main_keys_key_array_13, 12},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_19, 8},
{odin_main_keys_key_array_20, 2},
{odin_main_keys_key_array_21, 8},
{odin_main_keys_key_array_22, 3},
{0, 0},
{odin_main_keys_key_array_24, 13},
{0, 0},
{odin_main_keys_key_array_26, 5},
{odin_main_keys_key_array_27, 6},
{odin_main_keys_key_array_28, 3},
{odin_main_keys_key_array_29, 3},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_33, 5},
{0, 0},
{odin_main_keys_key_array_35, 8},
{odin_main_keys_key_array_36, 4},
{odin_main_keys_key_array_37, 2},
{0, 0},
{0, 0},
{odin_main_keys_key_array_40, 5},
{odin_main_keys_key_array_41, 6},
{0, 0},
{0, 0},
{odin_main_keys_key_array_44, 5},
{odin_main_keys_key_array_45, 9},
{odin_main_keys_key_array_46, 7},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_50, 3},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_55, 6},
{odin_main_keys_key_array_56, 7},
{odin_main_keys_key_array_57, 6},
{0, 0},
{odin_main_keys_key_array_59, 5},
{0, 0},
{odin_main_keys_key_array_61, 4},
{0, 0},
{odin_main_keys_key_array_63, 5},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_67, 13},
{odin_main_keys_key_array_68, 7},
{0, 0},
{odin_main_keys_key_array_70, 4},
{odin_main_keys_key_array_71, 3},
{0, 0},
{0, 0},
{odin_main_keys_key_array_74, 4},
{odin_main_keys_key_array_75, 3},
{odin_main_keys_key_array_76, 4},
{0, 0},
{odin_main_keys_key_array_78, 7},
{odin_main_keys_key_array_79, 6},
{odin_main_keys_key_array_80, 3},
{odin_main_keys_key_array_81, 7},
{0, 0},
{odin_main_keys_key_array_83, 5},
{odin_main_keys_key_array_84, 5},
{odin_main_keys_key_array_85, 4},
{odin_main_keys_key_array_86, 5},
{odin_main_keys_key_array_87, 6},
{0, 0},
{odin_main_keys_key_array_89, 3},
{0, 0},
{odin_main_keys_key_array_91, 12},
{0, 0},
{odin_main_keys_key_array_93, 3},
{0, 0},
{0, 0},
{odin_main_keys_key_array_96, 5},
{odin_main_keys_key_array_97, 10},
{0, 0},
{0, 0},
{odin_main_keys_key_array_100, 3},
{odin_main_keys_key_array_101, 4},
{0, 0},
{0, 0},
{odin_main_keys_key_array_104, 9},
{odin_main_keys_key_array_105, 5},
{odin_main_keys_key_array_106, 3},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_113, 3},
{0, 0},
{odin_main_keys_key_array_115, 6},
{odin_main_keys_key_array_116, 5},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_120, 7},
{odin_main_keys_key_array_121, 6},
{odin_main_keys_key_array_122, 7},
{odin_main_keys_key_array_123, 5},
{0, 0},
{odin_main_keys_key_array_125, 6},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_129, 5},
{odin_main_keys_key_array_130, 2},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_134, 3},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_138, 2},
{odin_main_keys_key_array_139, 3},
{odin_main_keys_key_array_140, 2},
{odin_main_keys_key_array_141, 5},
{0, 0},
{0, 0},
{odin_main_keys_key_array_144, 5},
{odin_main_keys_key_array_145, 6},
{odin_main_keys_key_array_146, 7},
{odin_main_keys_key_array_147, 4},
{0, 0},
{0, 0},
{odin_main_keys_key_array_150, 11},
{odin_main_keys_key_array_151, 5},
{odin_main_keys_key_array_152, 4},
{0, 0},
{0, 0},
{odin_main_keys_key_array_155, 4},
{odin_main_keys_key_array_156, 5},
{odin_main_keys_key_array_157, 5},
{0, 0},
{0, 0},
{odin_main_keys_key_array_160, 3},
{odin_main_keys_key_array_161, 5},
{0, 0},
{odin_main_keys_key_array_163, 4},
{odin_main_keys_key_array_164, 5},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_168, 9},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_172, 4},
{0, 0},
{odin_main_keys_key_array_174, 5},
{odin_main_keys_key_array_175, 5},
{odin_main_keys_key_array_176, 3},
{odin_main_keys_key_array_177, 6},
{odin_main_keys_key_array_178, 2},
{0, 0},
{odin_main_keys_key_array_180, 7},
{odin_main_keys_key_array_181, 4},
{odin_main_keys_key_array_182, 3},
{odin_main_keys_key_array_183, 8},
{odin_main_keys_key_array_184, 3},
};
Lexeme_Table_Value odin_main_keys_value_array[185] = {
{0, 0},
{0, 0},
{4, TokenOdinKind_Transmute},
{0, 0},
{4, TokenOdinKind_AutoCast},
{0, 0},
{0, 0},
{4, TokenOdinKind_B16},
{4, TokenOdinKind_I64be},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Rawptr},
{4, TokenOdinKind_Quaternion64},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Continue},
{4, TokenOdinKind_I8},
{4, TokenOdinKind_AlignOf},
{4, TokenOdinKind_F32},
{0, 0},
{4, TokenOdinKind_Quaternion256},
{0, 0},
{4, TokenOdinKind_Union},
{4, TokenOdinKind_Struct},
{4, TokenOdinKind_F16},
{4, TokenOdinKind_Any},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_F64le},
{0, 0},
{4, TokenOdinKind_Distinct},
{4, TokenOdinKind_Else},
{4, TokenOdinKind_Do},
{0, 0},
{0, 0},
{4, TokenOdinKind_Defer},
{4, TokenOdinKind_U128le},
{0, 0},
{0, 0},
{4, TokenOdinKind_I16be},
{4, TokenOdinKind_Complex32},
{4, TokenOdinKind_Dynamic},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_F64},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Typeid},
{4, TokenOdinKind_Foreign},
{4, TokenOdinKind_Return},
{0, 0},
{4, TokenOdinKind_I32be},
{0, 0},
{4, TokenOdinKind_U128},
{0, 0},
{4, TokenOdinKind_I16le},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Quaternion128},
{4, TokenOdinKind_Cstring},
{0, 0},
{4, TokenOdinKind_Byte},
{4, TokenOdinKind_I64},
{0, 0},
{0, 0},
{4, TokenOdinKind_Cast},
{4, TokenOdinKind_B64},
{4, TokenOdinKind_I128},
{0, 0},
{4, TokenOdinKind_OrElse},
{4, TokenOdinKind_String},
{4, TokenOdinKind_U16},
{4, TokenOdinKind_SizeOf},
{0, 0},
{4, TokenOdinKind_I32le},
{4, TokenOdinKind_U32le},
{4, TokenOdinKind_Bool},
{4, TokenOdinKind_U64be},
{4, TokenOdinKind_I128be},
{0, 0},
{4, TokenOdinKind_Uninitialized},
{0, 0},
{4, TokenOdinKind_ContainerOf},
{0, 0},
{4, TokenOdinKind_Nil},
{0, 0},
{0, 0},
{4, TokenOdinKind_U16be},
{4, TokenOdinKind_Complex128},
{0, 0},
{0, 0},
{4, TokenOdinKind_U32},
{4, TokenOdinKind_Rune},
{0, 0},
{0, 0},
{4, TokenOdinKind_Complex64},
{4, TokenOdinKind_F32be},
{4, TokenOdinKind_Int},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Asm},
{0, 0},
{4, TokenOdinKind_U128be},
{4, TokenOdinKind_F16be},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Context},
{4, TokenOdinKind_Switch},
{4, TokenOdinKind_Uintptr},
{4, TokenOdinKind_F32le},
{0, 0},
{4, TokenOdinKind_I128le},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_F16le},
{4, TokenOdinKind_If},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_U64},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_In},
{4, TokenOdinKind_I32},
{4, TokenOdinKind_U8},
{4, TokenOdinKind_U16le},
{0, 0},
{0, 0},
{4, TokenOdinKind_U64le},
{4, TokenOdinKind_NotIn},
{4, TokenOdinKind_Package},
{4, TokenOdinKind_Enum},
{0, 0},
{0, 0},
{4, TokenOdinKind_Fallthrough},
{4, TokenOdinKind_I64le},
{4, TokenOdinKind_Proc},
{0, 0},
{0, 0},
{4, TokenOdinKind_Case},
{4, TokenOdinKind_Where},
{4, TokenOdinKind_Break},
{0, 0},
{0, 0},
{4, TokenOdinKind_Map},
{4, TokenOdinKind_Using},
{0, 0},
{4, TokenOdinKind_Uint},
{8, TokenOdinKind_LiteralFalse},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_OrReturn},
{0, 0},
{0, 0},
{0, 0},
{8, TokenOdinKind_LiteralTrue},
{0, 0},
{4, TokenOdinKind_U32be},
{4, TokenOdinKind_F64be},
{4, TokenOdinKind_For},
{4, TokenOdinKind_Import},
{4, TokenOdinKind_B8},
{0, 0},
{4, TokenOdinKind_BitSet},
{4, TokenOdinKind_When},
{4, TokenOdinKind_B32},
{4, TokenOdinKind_OrBreak},
{4, TokenOdinKind_I16},
};
i32 odin_main_keys_slot_count = 185;
u64 odin_main_keys_seed = 0xb8af065b4c9dd40d;
u64 odin_directives_hash_array[47] = {
0x3e586ba3493025bf,0x0000000000000000,0x3e586ba34be9cca7,0x80f2570652f04a97,
0x0000000000000000,0x89818bca8f2a7caf,0x3e586ba349140279,0x61de189d6268000b,
0x866d860bba66210b,0x0000000000000000,0xc111076f2b467b4f,0x0000000000000000,
0x89818bc971cf269b,0xdb508a08320effb1,0x0000000000000000,0x83d5c2bcc5a02c95,
0x29ef6d1d5b32c713,0x4814807207dbda17,0x0000000000000000,0x61dea49cd7ca8913,
0x3869318e24698931,0x0000000000000000,0x83d5c2ff3b917e13,0x0000000000000000,
0x0000000000000000,0x349800acf038240b,0x0000000000000000,0x83d5c2ea364a008d,
0x83d5c2fc4450a7ff,0x83d5c2bc7ea94239,0x0000000000000000,0x3e586ba34914204f,
0x3868c06296aa85c5,0x8610da8af95ddb17,0x0000000000000000,0x0000000000000000,
0x3868c31397c87887,0x0000000000000000,0x3869301d2d4e7e8f,0x0000000000000000,
0x8676a5522fdf7f19,0x57ffdf7d91d9da17,0x0000000000000000,0x0000000000000000,
0x3e586ba3491aa599,0x61f59f2aebb61659,0x0000000000000000,
};
u8 odin_directives_key_array_0[] = {0x74,0x79,0x70,0x65,};
u8 odin_directives_key_array_2[] = {0x66,0x69,0x6c,0x65,};
u8 odin_directives_key_array_3[] = {0x6f,0x70,0x74,0x69,0x6f,0x6e,0x61,0x6c,0x5f,0x6f,0x6b,};
u8 odin_directives_key_array_5[] = {0x70,0x61,0x6e,0x69,0x63,};
u8 odin_directives_key_array_6[] = {0x6c,0x6f,0x61,0x64,};
u8 odin_directives_key_array_7[] = {0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_8[] = {0x72,0x61,0x77,0x5f,0x75,0x6e,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_10[] = {0x66,0x6f,0x72,0x63,0x65,0x5f,0x69,0x6e,0x6c,0x69,0x6e,0x65,};
u8 odin_directives_key_array_12[] = {0x61,0x6c,0x69,0x67,0x6e,};
u8 odin_directives_key_array_13[] = {0x73,0x6f,0x61,};
u8 odin_directives_key_array_15[] = {0x6e,0x6f,0x5f,0x6e,0x69,0x6c,};
u8 odin_directives_key_array_16[] = {0x6f,0x70,0x74,0x69,0x6f,0x6e,0x61,0x6c,0x5f,0x61,0x6c,0x6c,0x6f,0x63,0x61,0x74,0x6f,0x72,0x5f,0x65,0x72,0x72,0x6f,0x72,};
u8 odin_directives_key_array_17[] = {0x6e,0x6f,0x5f,0x62,0x6f,0x75,0x6e,0x64,0x73,0x5f,0x63,0x68,0x65,0x63,0x6b,};
u8 odin_directives_key_array_19[] = {0x6e,0x6f,0x5f,0x61,0x6c,0x69,0x61,0x73,};
u8 odin_directives_key_array_20[] = {0x70,0x61,0x72,0x74,0x69,0x61,0x6c,};
u8 odin_directives_key_array_22[] = {0x63,0x6f,0x6e,0x66,0x69,0x67,};
u8 odin_directives_key_array_25[] = {0x63,0x61,0x6c,0x6c,0x65,0x72,0x5f,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_27[] = {0x62,0x79,0x5f,0x70,0x74,0x72,};
u8 odin_directives_key_array_28[] = {0x61,0x73,0x73,0x65,0x72,0x74,};
u8 odin_directives_key_array_29[] = {0x70,0x61,0x63,0x6b,0x65,0x64,};
u8 odin_directives_key_array_31[] = {0x6c,0x69,0x6e,0x65,};
u8 odin_directives_key_array_32[] = {0x64,0x65,0x66,0x69,0x6e,0x65,0x64,};
u8 odin_directives_key_array_33[] = {0x70,0x72,0x6f,0x63,0x65,0x64,0x75,0x72,0x65,};
u8 odin_directives_key_array_36[] = {0x61,0x6e,0x79,0x5f,0x69,0x6e,0x74,};
u8 odin_directives_key_array_38[] = {0x6c,0x6f,0x61,0x64,0x5f,0x6f,0x72,};
u8 odin_directives_key_array_40[] = {0x6c,0x6f,0x61,0x64,0x5f,0x68,0x61,0x73,0x68,};
u8 odin_directives_key_array_41[] = {0x62,0x6f,0x75,0x6e,0x64,0x73,0x5f,0x63,0x68,0x65,0x63,0x6b,};
u8 odin_directives_key_array_44[] = {0x73,0x69,0x6d,0x64,};
u8 odin_directives_key_array_45[] = {0x63,0x5f,0x76,0x61,0x72,0x61,0x72,0x67,};
String_Const_u8 odin_directives_key_array[47] = {
{odin_directives_key_array_0, 4},
{0, 0},
{odin_directives_key_array_2, 4},
{odin_directives_key_array_3, 11},
{0, 0},
{odin_directives_key_array_5, 5},
{odin_directives_key_array_6, 4},
{odin_directives_key_array_7, 8},
{odin_directives_key_array_8, 9},
{0, 0},
{odin_directives_key_array_10, 12},
{0, 0},
{odin_directives_key_array_12, 5},
{odin_directives_key_array_13, 3},
{0, 0},
{odin_directives_key_array_15, 6},
{odin_directives_key_array_16, 24},
{odin_directives_key_array_17, 15},
{0, 0},
{odin_directives_key_array_19, 8},
{odin_directives_key_array_20, 7},
{0, 0},
{odin_directives_key_array_22, 6},
{0, 0},
{0, 0},
{odin_directives_key_array_25, 15},
{0, 0},
{odin_directives_key_array_27, 6},
{odin_directives_key_array_28, 6},
{odin_directives_key_array_29, 6},
{0, 0},
{odin_directives_key_array_31, 4},
{odin_directives_key_array_32, 7},
{odin_directives_key_array_33, 9},
{0, 0},
{0, 0},
{odin_directives_key_array_36, 7},
{0, 0},
{odin_directives_key_array_38, 7},
{0, 0},
{odin_directives_key_array_40, 9},
{odin_directives_key_array_41, 12},
{0, 0},
{0, 0},
{odin_directives_key_array_44, 4},
{odin_directives_key_array_45, 8},
{0, 0},
};
Lexeme_Table_Value odin_directives_value_array[47] = {
{4, TokenOdinKind_Type},
{0, 0},
{4, TokenOdinKind_File},
{4, TokenOdinKind_OptionalOk},
{0, 0},
{4, TokenOdinKind_Panic},
{4, TokenOdinKind_Load},
{4, TokenOdinKind_Location},
{4, TokenOdinKind_RawUnion},
{0, 0},
{4, TokenOdinKind_ForceInline},
{0, 0},
{4, TokenOdinKind_Align},
{4, TokenOdinKind_Soa},
{0, 0},
{4, TokenOdinKind_NoNil},
{4, TokenOdinKind_OptionalAllocatorError},
{4, TokenOdinKind_NoBoundsCheck},
{0, 0},
{4, TokenOdinKind_NoAlias},
{4, TokenOdinKind_Partial},
{0, 0},
{4, TokenOdinKind_Config},
{0, 0},
{0, 0},
{4, TokenOdinKind_CallerLocation},
{0, 0},
{4, TokenOdinKind_ByPtr},
{4, TokenOdinKind_Assert},
{4, TokenOdinKind_Packed},
{0, 0},
{4, TokenOdinKind_Line},
{4, TokenOdinKind_Defined},
{4, TokenOdinKind_Procedure},
{0, 0},
{0, 0},
{4, TokenOdinKind_AnyInt},
{0, 0},
{4, TokenOdinKind_LoadOr},
{0, 0},
{4, TokenOdinKind_LoadHash},
{4, TokenOdinKind_BoundsCheck},
{0, 0},
{0, 0},
{4, TokenOdinKind_Simd},
{4, TokenOdinKind_CVararg},
{0, 0},
};
i32 odin_directives_slot_count = 47;
u64 odin_directives_seed = 0x597911c7f1a08dba;
u64 odin_attributes_hash_array[49] = {
0x0000000000000000,0x589b4e685d172945,0x356e28e2d484cbb3,0x6eb950f3b0a88ba5,
0x4e3e6f381e725e4b,0x0000000000000000,0x2131075376cf11d9,0x695414a25eab4ba5,
0xd096b62e3429f009,0x0000000000000000,0x4e3e6badf5903a79,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x9c964a69a413e60f,0x0000000000000000,
0x356e364589aa081b,0x4e3e60e21cc131cd,0x0000000000000000,0xd096b62f92f2af4b,
0xb2780ac4722ce1f3,0x5fb33db8ad3f608d,0x0000000000000000,0x0000000000000000,
0xd31498dd3f6a00cb,0x6a387c705970db75,0xedfc2035a692301b,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x4e3e6bdaed585deb,0x585dda764692301b,
0x7d29c8d4a57edad9,0x0000000000000000,0x0000000000000000,0x7c7f753d08036fe9,
0x0000000000000000,0xce2ca3a602ed969b,0x0000000000000000,0xc9132cceb082efaf,
0x0000000000000000,0x4e3d6bec48a61c5f,0x0000000000000000,0xeaec214de4316cc5,
0x0000000000000000,0x0000000000000000,0xa0d606183318b30d,0xf0c52db25306f8bb,
0x6eb950f3b0acdbab,
};
u8 odin_attributes_key_array_1[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x6f,0x75,0x74,};
u8 odin_attributes_key_array_2[] = {0x73,0x74,0x61,0x74,0x69,0x63,};
u8 odin_attributes_key_array_3[] = {0x6f,0x62,0x6a,0x63,0x5f,0x6e,0x61,0x6d,0x65,};
u8 odin_attributes_key_array_4[] = {0x72,0x65,0x71,0x75,0x69,0x72,0x65,};
u8 odin_attributes_key_array_6[] = {0x64,0x65,0x70,0x72,0x65,0x63,0x61,0x74,0x65,0x64,};
u8 odin_attributes_key_array_7[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x6e,0x61,0x6d,0x65,};
u8 odin_attributes_key_array_8[] = {0x69,0x6e,0x69,0x74,};
u8 odin_attributes_key_array_10[] = {0x6c,0x69,0x6e,0x6b,0x61,0x67,0x65,};
u8 odin_attributes_key_array_14[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x73,0x65,0x63,0x74,0x69,0x6f,0x6e,};
u8 odin_attributes_key_array_16[] = {0x65,0x78,0x70,0x6f,0x72,0x74,};
u8 odin_attributes_key_array_17[] = {0x77,0x61,0x72,0x6e,0x69,0x6e,0x67,};
u8 odin_attributes_key_array_19[] = {0x63,0x6f,0x6c,0x64,};
u8 odin_attributes_key_array_20[] = {0x65,0x78,0x74,0x72,0x61,0x5f,0x6c,0x69,0x6e,0x6b,0x65,0x72,0x5f,0x66,0x6c,0x61,0x67,0x73,};
u8 odin_attributes_key_array_21[] = {0x6f,0x62,0x6a,0x63,0x5f,0x69,0x73,0x5f,0x63,0x6c,0x61,0x73,0x73,0x5f,0x6d,0x65,0x74,0x68,0x6f,0x64,};
u8 odin_attributes_key_array_24[] = {0x6f,0x70,0x74,0x69,0x6d,0x69,0x7a,0x61,0x74,0x69,0x6f,0x6e,0x5f,0x6d,0x6f,0x64,0x65,};
u8 odin_attributes_key_array_25[] = {0x74,0x68,0x72,0x65,0x61,0x64,0x5f,0x6c,0x6f,0x63,0x61,0x6c,};
u8 odin_attributes_key_array_26[] = {0x65,0x6e,0x61,0x62,0x6c,0x65,0x5f,0x74,0x61,0x72,0x67,0x65,0x74,0x5f,0x66,0x65,0x61,0x74,0x75,0x72,0x65,};
u8 odin_attributes_key_array_30[] = {0x70,0x72,0x69,0x76,0x61,0x74,0x65,};
u8 odin_attributes_key_array_31[] = {0x72,0x65,0x71,0x75,0x69,0x72,0x65,0x5f,0x74,0x61,0x72,0x67,0x65,0x74,0x5f,0x66,0x65,0x61,0x74,0x75,0x72,0x65,};
u8 odin_attributes_key_array_32[] = {0x64,0x69,0x73,0x61,0x62,0x6c,0x65,0x64,};
u8 odin_attributes_key_array_35[] = {0x72,0x65,0x71,0x75,0x69,0x72,0x65,0x5f,0x72,0x65,0x73,0x75,0x6c,0x74,0x73,};
u8 odin_attributes_key_array_37[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x6e,0x6f,0x6e,0x65,};
u8 odin_attributes_key_array_39[] = {0x64,0x65,0x66,0x61,0x75,0x6c,0x74,0x5f,0x63,0x61,0x6c,0x6c,0x69,0x6e,0x67,0x5f,0x63,0x6f,0x6e,0x76,0x65,0x6e,0x74,0x69,0x6f,0x6e,};
u8 odin_attributes_key_array_41[] = {0x62,0x75,0x69,0x6c,0x74,0x69,0x6e,};
u8 odin_attributes_key_array_43[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x69,0x6e,0x5f,0x6f,0x75,0x74,};
u8 odin_attributes_key_array_46[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x70,0x72,0x65,0x66,0x69,0x78,};
u8 odin_attributes_key_array_47[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x69,0x6e,};
u8 odin_attributes_key_array_48[] = {0x6f,0x62,0x6a,0x63,0x5f,0x74,0x79,0x70,0x65,};
String_Const_u8 odin_attributes_key_array[49] = {
{0, 0},
{odin_attributes_key_array_1, 12},
{odin_attributes_key_array_2, 6},
{odin_attributes_key_array_3, 9},
{odin_attributes_key_array_4, 7},
{0, 0},
{odin_attributes_key_array_6, 10},
{odin_attributes_key_array_7, 9},
{odin_attributes_key_array_8, 4},
{0, 0},
{odin_attributes_key_array_10, 7},
{0, 0},
{0, 0},
{0, 0},
{odin_attributes_key_array_14, 12},
{0, 0},
{odin_attributes_key_array_16, 6},
{odin_attributes_key_array_17, 7},
{0, 0},
{odin_attributes_key_array_19, 4},
{odin_attributes_key_array_20, 18},
{odin_attributes_key_array_21, 20},
{0, 0},
{0, 0},
{odin_attributes_key_array_24, 17},
{odin_attributes_key_array_25, 12},
{odin_attributes_key_array_26, 21},
{0, 0},
{0, 0},
{0, 0},
{odin_attributes_key_array_30, 7},
{odin_attributes_key_array_31, 22},
{odin_attributes_key_array_32, 8},
{0, 0},
{0, 0},
{odin_attributes_key_array_35, 15},
{0, 0},
{odin_attributes_key_array_37, 13},
{0, 0},
{odin_attributes_key_array_39, 26},
{0, 0},
{odin_attributes_key_array_41, 7},
{0, 0},
{odin_attributes_key_array_43, 15},
{0, 0},
{0, 0},
{odin_attributes_key_array_46, 11},
{odin_attributes_key_array_47, 11},
{odin_attributes_key_array_48, 9},
};
Lexeme_Table_Value odin_attributes_value_array[49] = {
{0, 0},
{4, TokenOdinKind_AtDeferredOut},
{4, TokenOdinKind_AtStatic},
{4, TokenOdinKind_AtObjcName},
{4, TokenOdinKind_AtRequire},
{0, 0},
{4, TokenOdinKind_AtDeprecated},
{4, TokenOdinKind_AtLinkName},
{4, TokenOdinKind_AtInit},
{0, 0},
{4, TokenOdinKind_AtLinkage},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtLinkSection},
{0, 0},
{4, TokenOdinKind_AtExport},
{4, TokenOdinKind_AtWarning},
{0, 0},
{4, TokenOdinKind_AtCold},
{4, TokenOdinKind_AtExtraLinkerFlags},
{4, TokenOdinKind_AtObjcIsClassMethod},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtOptimizationMode},
{4, TokenOdinKind_AtThreadLocal},
{4, TokenOdinKind_AtEnableTargetFeature},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtPrivate},
{4, TokenOdinKind_AtRequireTargetFeature},
{4, TokenOdinKind_AtDisabled},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtRequireResults},
{0, 0},
{4, TokenOdinKind_AtDeferredNone},
{0, 0},
{4, TokenOdinKind_AtDefaultCallingConvention},
{0, 0},
{4, TokenOdinKind_AtBuiltin},
{0, 0},
{4, TokenOdinKind_AtDeferredInOut},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtLinkPrefix},
{4, TokenOdinKind_AtDeferredIn},
{4, TokenOdinKind_AtObjcType},
};
i32 odin_attributes_slot_count = 49;
u64 odin_attributes_seed = 0x2aecdbc0eb766466;
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
case 0x1a:case 0x1b:case 0x1c:case 0x1d:case 0x1e:case 0x1f:case 0x5c:
case 0x7f:
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
goto state_label_49; // op stage
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
case 0x3c:
{
state.ptr += 1;
goto state_label_38; // op stage
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
goto state_label_52; // op stage
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
goto state_label_48; // op stage
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
state_label_47: // op stage
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
state_label_48: // op stage
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
state_label_49: // op stage
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
state_label_50: // op stage
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
goto state_label_51; // op stage
}break;
}
}
{
state_label_51: // op stage
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
{
state_label_52: // op stage
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
