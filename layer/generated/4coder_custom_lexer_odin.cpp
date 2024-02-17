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
u64 odin_main_keys_hash_array[182] = {
0x7cc63b016fd1d14f,0xe64d5799d78b0643,0x0b5e50af5c3d2219,0x0000000000000000,
0x0ae254213505a073,0x7cc63b016fd1481f,0x0000000000000000,0x4d6e98daf2606c51,
0x7cc63b016fd1d157,0x7cc63b016fd14c67,0x0000000000000000,0x0000000000000000,
0xe64d5799d8fe1e0b,0x0000000000000000,0x0ae2542133cec391,0xe64d5799d8e4b4f9,
0x0000000000000000,0x7cc63b016fd15b5d,0x7cc63b016fd19937,0x7cc63b016fd6ed81,
0x0b1e08389cd9044f,0x51e762dd38264b91,0x0000000000000000,0x51e762dd387588c1,
0x0000000000000000,0xe8c8f429cc32bf4b,0x0000000000000000,0x7cc63b016fd19941,
0x4d5501585a21056b,0x0000000000000000,0x0000000000000000,0xe64d5799d900e951,
0x7cc63b016fd1988f,0x0000000000000000,0x51e762ce8011dd0b,0x0ae254213e42d8cb,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0xe64d5799d8d7c141,
0xe8c8f5973630eb91,0x0000000000000000,0x0ae254212c68e351,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0xe8c8fb5497551753,0x0000000000000000,
0x7cc63b016fd1f457,0xe64d5799d789e0d5,0x0000000000000000,0x0000000000000000,
0x0ae25421342ebf23,0x0000000000000000,0x51e762cc64e9710b,0x4d7a834317be31ef,
0x0000000000000000,0x0ae2542133e511fb,0x7cc63b016fd029d1,0x7cc63b016fd02f81,
0x0000000000000000,0x0000000000000000,0xe8c8fad4e971fdd3,0x0000000000000000,
0x0ae254213e42d833,0x0ae25421361882b3,0x0000000000000000,0xe8c8fa3e179e85d3,
0x0ae2542135055c73,0x0b5e50af5c3d2757,0x0000000000000000,0x7cc63b016fd6f367,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0ae254214978980b,0x0b5e50af5c3d275f,0x0ae25421497898c3,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0ae254213e88e5ab,0xe8c8fa8e94f23137,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x51e762ce8011df63,0x51e762dd5d209b55,0x0000000000000000,0x0000000000000000,
0x0ae254213505a0cb,0x7cc63b016fd18379,0x0ae25421496db8cb,0x4d7a834317be3cc1,
0x51e762cea9957267,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0xe64d5799d7809a83,0x0ae2542120ae7dd3,
0x0b5e50af5c3d24a1,0x0000000000000000,0x0ae254213e8390c3,0x0000000000000000,
0x51e762cc64e97363,0x0000000000000000,0x0000000000000000,0x0b5e50af5c3d2615,
0x7cc63b016fd6eddf,0x7cc63b016fd1982b,0x0000000000000000,0x7cc63b016fd0067f,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0xf96290f97d145555,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0xe64d5799d8d9e2e1,0x0ae254213e83918b,0x0ae25421496db833,0x51e762d127d6a645,
0x0ae2542122f926c3,0x0000000000000000,0x7cc63b016fd284fb,0x0000000000000000,
0x0000000000000000,0x51e762c6a66c4b01,0x51e762c9db48ca5f,0x31622cc66c7478f1,
0x0000000000000000,0x7cc63b016fd14c31,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0xe64d5799d8c0cc55,0xe8c8facce2901449,0x0000000000000000,
0x0000000000000000,0xe8c8f528824ee70d,0x0000000000000000,0x4d526190fd91852f,
0x51e762ceb8af852f,0x0b1e08389cd89755,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0b5e50af5c3d2641,0xe64d5799d8e16f53,
0x0ae254213e88ef33,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0xe64d5799d8ddce27,0x97e4ecf5226353e3,0x0000000000000000,
0x0ae2542135055fab,0x97e4a0f942cf7cb1,0xe64d5799d900e923,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0xca9d7ecd42207975,
0xe64d5799d8e1ba0b,0x0000000000000000,0x0ae25421492bd9ab,0x0000000000000000,
0x0000000000000000,0xe8c8f429a2f6a2bd,0x0000000000000000,0x0000000000000000,
0x0ae25421492be733,0x0ae2542122f9258b,
};
u8 odin_main_keys_key_array_0[] = {0x66,0x33,0x32,};
u8 odin_main_keys_key_array_1[] = {0x72,0x75,0x6e,0x65,};
u8 odin_main_keys_key_array_2[] = {0x75,0x38,};
u8 odin_main_keys_key_array_4[] = {0x66,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_5[] = {0x69,0x33,0x32,};
u8 odin_main_keys_key_array_7[] = {0x61,0x75,0x74,0x6f,0x5f,0x63,0x61,0x73,0x74,};
u8 odin_main_keys_key_array_8[] = {0x66,0x31,0x36,};
u8 odin_main_keys_key_array_9[] = {0x69,0x31,0x36,};
u8 odin_main_keys_key_array_12[] = {0x62,0x79,0x74,0x65,};
u8 odin_main_keys_key_array_14[] = {0x75,0x73,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_15[] = {0x62,0x6f,0x6f,0x6c,};
u8 odin_main_keys_key_array_17[] = {0x6e,0x69,0x6c,};
u8 odin_main_keys_key_array_18[] = {0x62,0x31,0x36,};
u8 odin_main_keys_key_array_19[] = {0x75,0x36,0x34,};
u8 odin_main_keys_key_array_20[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x32,0x35,0x36,};
u8 odin_main_keys_key_array_21[] = {0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_23[] = {0x73,0x74,0x72,0x75,0x63,0x74,};
u8 odin_main_keys_key_array_25[] = {0x66,0x6f,0x72,0x65,0x69,0x67,0x6e,};
u8 odin_main_keys_key_array_27[] = {0x62,0x36,0x34,};
u8 odin_main_keys_key_array_28[] = {0x74,0x72,0x61,0x6e,0x73,0x6d,0x75,0x74,0x65,};
u8 odin_main_keys_key_array_31[] = {0x63,0x61,0x73,0x74,};
u8 odin_main_keys_key_array_32[] = {0x62,0x33,0x32,};
u8 odin_main_keys_key_array_34[] = {0x75,0x31,0x32,0x38,0x6c,0x65,};
u8 odin_main_keys_key_array_35[] = {0x69,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_39[] = {0x75,0x69,0x6e,0x74,};
u8 odin_main_keys_key_array_40[] = {0x63,0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_42[] = {0x62,0x72,0x65,0x61,0x6b,};
u8 odin_main_keys_key_array_46[] = {0x70,0x61,0x63,0x6b,0x61,0x67,0x65,};
u8 odin_main_keys_key_array_48[] = {0x61,0x6e,0x79,};
u8 odin_main_keys_key_array_49[] = {0x75,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_52[] = {0x77,0x68,0x65,0x72,0x65,};
u8 odin_main_keys_key_array_54[] = {0x69,0x31,0x32,0x38,0x6c,0x65,};
u8 odin_main_keys_key_array_55[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x33,0x32,};
u8 odin_main_keys_key_array_57[] = {0x75,0x6e,0x69,0x6f,0x6e,};
u8 odin_main_keys_key_array_58[] = {0x66,0x36,0x34,};
u8 odin_main_keys_key_array_59[] = {0x69,0x6e,0x74,};
u8 odin_main_keys_key_array_62[] = {0x6f,0x72,0x5f,0x65,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_64[] = {0x69,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_65[] = {0x64,0x65,0x66,0x65,0x72,};
u8 odin_main_keys_key_array_67[] = {0x73,0x69,0x7a,0x65,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_68[] = {0x66,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_69[] = {0x69,0x66,};
u8 odin_main_keys_key_array_71[] = {0x75,0x31,0x36,};
u8 odin_main_keys_key_array_76[] = {0x75,0x36,0x34,0x6c,0x65,};
u8 odin_main_keys_key_array_77[] = {0x69,0x6e,};
u8 odin_main_keys_key_array_78[] = {0x75,0x36,0x34,0x62,0x65,};
u8 odin_main_keys_key_array_82[] = {0x69,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_83[] = {0x75,0x69,0x6e,0x74,0x70,0x74,0x72,};
u8 odin_main_keys_key_array_88[] = {0x75,0x31,0x32,0x38,0x62,0x65,};
u8 odin_main_keys_key_array_89[] = {0x73,0x77,0x69,0x74,0x63,0x68,};
u8 odin_main_keys_key_array_92[] = {0x66,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_93[] = {0x6d,0x61,0x70,};
u8 odin_main_keys_key_array_94[] = {0x75,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_95[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x36,0x34,};
u8 odin_main_keys_key_array_96[] = {0x72,0x61,0x77,0x70,0x74,0x72,};
u8 odin_main_keys_key_array_102[] = {0x74,0x72,0x75,0x65,};
u8 odin_main_keys_key_array_103[] = {0x66,0x61,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_104[] = {0x69,0x38,};
u8 odin_main_keys_key_array_106[] = {0x69,0x36,0x34,0x62,0x65,};
u8 odin_main_keys_key_array_108[] = {0x69,0x31,0x32,0x38,0x62,0x65,};
u8 odin_main_keys_key_array_111[] = {0x62,0x38,};
u8 odin_main_keys_key_array_112[] = {0x75,0x33,0x32,};
u8 odin_main_keys_key_array_113[] = {0x61,0x73,0x6d,};
u8 odin_main_keys_key_array_115[] = {0x66,0x6f,0x72,};
u8 odin_main_keys_key_array_119[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_124[] = {0x70,0x72,0x6f,0x63,};
u8 odin_main_keys_key_array_125[] = {0x69,0x36,0x34,0x6c,0x65,};
u8 odin_main_keys_key_array_126[] = {0x75,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_127[] = {0x74,0x79,0x70,0x65,0x69,0x64,};
u8 odin_main_keys_key_array_128[] = {0x66,0x36,0x34,0x62,0x65,};
u8 odin_main_keys_key_array_130[] = {0x2d,0x2d,0x2d,};
u8 odin_main_keys_key_array_133[] = {0x69,0x6d,0x70,0x6f,0x72,0x74,};
u8 odin_main_keys_key_array_134[] = {0x6e,0x6f,0x74,0x5f,0x69,0x6e,};
u8 odin_main_keys_key_array_135[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x36,0x34,};
u8 odin_main_keys_key_array_137[] = {0x69,0x36,0x34,};
u8 odin_main_keys_key_array_141[] = {0x69,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_142[] = {0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,};
u8 odin_main_keys_key_array_145[] = {0x62,0x69,0x74,0x5f,0x73,0x65,0x74,};
u8 odin_main_keys_key_array_147[] = {0x6f,0x72,0x5f,0x72,0x65,0x74,0x75,0x72,0x6e,};
u8 odin_main_keys_key_array_148[] = {0x72,0x65,0x74,0x75,0x72,0x6e,};
u8 odin_main_keys_key_array_149[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_154[] = {0x64,0x6f,};
u8 odin_main_keys_key_array_155[] = {0x65,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_156[] = {0x69,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_161[] = {0x77,0x68,0x65,0x6e,};
u8 odin_main_keys_key_array_162[] = {0x63,0x6f,0x6e,0x74,0x69,0x6e,0x75,0x65,};
u8 odin_main_keys_key_array_164[] = {0x66,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_165[] = {0x64,0x69,0x73,0x74,0x69,0x6e,0x63,0x74,};
u8 odin_main_keys_key_array_166[] = {0x63,0x61,0x73,0x65,};
u8 odin_main_keys_key_array_171[] = {0x66,0x61,0x6c,0x6c,0x74,0x68,0x72,0x6f,0x75,0x67,0x68,};
u8 odin_main_keys_key_array_172[] = {0x65,0x6e,0x75,0x6d,};
u8 odin_main_keys_key_array_174[] = {0x75,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_177[] = {0x63,0x6f,0x6e,0x74,0x65,0x78,0x74,};
u8 odin_main_keys_key_array_180[] = {0x75,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_181[] = {0x66,0x36,0x34,0x6c,0x65,};
String_Const_u8 odin_main_keys_key_array[182] = {
{odin_main_keys_key_array_0, 3},
{odin_main_keys_key_array_1, 4},
{odin_main_keys_key_array_2, 2},
{0, 0},
{odin_main_keys_key_array_4, 5},
{odin_main_keys_key_array_5, 3},
{0, 0},
{odin_main_keys_key_array_7, 9},
{odin_main_keys_key_array_8, 3},
{odin_main_keys_key_array_9, 3},
{0, 0},
{0, 0},
{odin_main_keys_key_array_12, 4},
{0, 0},
{odin_main_keys_key_array_14, 5},
{odin_main_keys_key_array_15, 4},
{0, 0},
{odin_main_keys_key_array_17, 3},
{odin_main_keys_key_array_18, 3},
{odin_main_keys_key_array_19, 3},
{odin_main_keys_key_array_20, 13},
{odin_main_keys_key_array_21, 6},
{0, 0},
{odin_main_keys_key_array_23, 6},
{0, 0},
{odin_main_keys_key_array_25, 7},
{0, 0},
{odin_main_keys_key_array_27, 3},
{odin_main_keys_key_array_28, 9},
{0, 0},
{0, 0},
{odin_main_keys_key_array_31, 4},
{odin_main_keys_key_array_32, 3},
{0, 0},
{odin_main_keys_key_array_34, 6},
{odin_main_keys_key_array_35, 5},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_39, 4},
{odin_main_keys_key_array_40, 7},
{0, 0},
{odin_main_keys_key_array_42, 5},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_46, 7},
{0, 0},
{odin_main_keys_key_array_48, 3},
{odin_main_keys_key_array_49, 4},
{0, 0},
{0, 0},
{odin_main_keys_key_array_52, 5},
{0, 0},
{odin_main_keys_key_array_54, 6},
{odin_main_keys_key_array_55, 9},
{0, 0},
{odin_main_keys_key_array_57, 5},
{odin_main_keys_key_array_58, 3},
{odin_main_keys_key_array_59, 3},
{0, 0},
{0, 0},
{odin_main_keys_key_array_62, 7},
{0, 0},
{odin_main_keys_key_array_64, 5},
{odin_main_keys_key_array_65, 5},
{0, 0},
{odin_main_keys_key_array_67, 7},
{odin_main_keys_key_array_68, 5},
{odin_main_keys_key_array_69, 2},
{0, 0},
{odin_main_keys_key_array_71, 3},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_76, 5},
{odin_main_keys_key_array_77, 2},
{odin_main_keys_key_array_78, 5},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_82, 5},
{odin_main_keys_key_array_83, 7},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_88, 6},
{odin_main_keys_key_array_89, 6},
{0, 0},
{0, 0},
{odin_main_keys_key_array_92, 5},
{odin_main_keys_key_array_93, 3},
{odin_main_keys_key_array_94, 5},
{odin_main_keys_key_array_95, 9},
{odin_main_keys_key_array_96, 6},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_102, 4},
{odin_main_keys_key_array_103, 5},
{odin_main_keys_key_array_104, 2},
{0, 0},
{odin_main_keys_key_array_106, 5},
{0, 0},
{odin_main_keys_key_array_108, 6},
{0, 0},
{0, 0},
{odin_main_keys_key_array_111, 2},
{odin_main_keys_key_array_112, 3},
{odin_main_keys_key_array_113, 3},
{0, 0},
{odin_main_keys_key_array_115, 3},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_119, 10},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_124, 4},
{odin_main_keys_key_array_125, 5},
{odin_main_keys_key_array_126, 5},
{odin_main_keys_key_array_127, 6},
{odin_main_keys_key_array_128, 5},
{0, 0},
{odin_main_keys_key_array_130, 3},
{0, 0},
{0, 0},
{odin_main_keys_key_array_133, 6},
{odin_main_keys_key_array_134, 6},
{odin_main_keys_key_array_135, 12},
{0, 0},
{odin_main_keys_key_array_137, 3},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_141, 4},
{odin_main_keys_key_array_142, 7},
{0, 0},
{0, 0},
{odin_main_keys_key_array_145, 7},
{0, 0},
{odin_main_keys_key_array_147, 9},
{odin_main_keys_key_array_148, 6},
{odin_main_keys_key_array_149, 13},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_154, 2},
{odin_main_keys_key_array_155, 4},
{odin_main_keys_key_array_156, 5},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_161, 4},
{odin_main_keys_key_array_162, 8},
{0, 0},
{odin_main_keys_key_array_164, 5},
{odin_main_keys_key_array_165, 8},
{odin_main_keys_key_array_166, 4},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_171, 11},
{odin_main_keys_key_array_172, 4},
{0, 0},
{odin_main_keys_key_array_174, 5},
{0, 0},
{0, 0},
{odin_main_keys_key_array_177, 7},
{0, 0},
{0, 0},
{odin_main_keys_key_array_180, 5},
{odin_main_keys_key_array_181, 5},
};
Lexeme_Table_Value odin_main_keys_value_array[182] = {
{4, TokenOdinKind_F32},
{4, TokenOdinKind_Rune},
{4, TokenOdinKind_U8},
{0, 0},
{4, TokenOdinKind_F32be},
{4, TokenOdinKind_I32},
{0, 0},
{4, TokenOdinKind_AutoCast},
{4, TokenOdinKind_F16},
{4, TokenOdinKind_I16},
{0, 0},
{0, 0},
{4, TokenOdinKind_Byte},
{0, 0},
{4, TokenOdinKind_Using},
{4, TokenOdinKind_Bool},
{0, 0},
{4, TokenOdinKind_Nil},
{4, TokenOdinKind_B16},
{4, TokenOdinKind_U64},
{4, TokenOdinKind_Quaternion256},
{4, TokenOdinKind_String},
{0, 0},
{4, TokenOdinKind_Struct},
{0, 0},
{4, TokenOdinKind_Foreign},
{0, 0},
{4, TokenOdinKind_B64},
{4, TokenOdinKind_Transmute},
{0, 0},
{0, 0},
{4, TokenOdinKind_Cast},
{4, TokenOdinKind_B32},
{0, 0},
{4, TokenOdinKind_U128le},
{4, TokenOdinKind_I32le},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Uint},
{4, TokenOdinKind_Cstring},
{0, 0},
{4, TokenOdinKind_Break},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Package},
{0, 0},
{4, TokenOdinKind_Any},
{4, TokenOdinKind_U128},
{0, 0},
{0, 0},
{4, TokenOdinKind_Where},
{0, 0},
{4, TokenOdinKind_I128le},
{4, TokenOdinKind_Complex32},
{0, 0},
{4, TokenOdinKind_Union},
{4, TokenOdinKind_F64},
{4, TokenOdinKind_Int},
{0, 0},
{0, 0},
{4, TokenOdinKind_OrElse},
{0, 0},
{4, TokenOdinKind_I32be},
{4, TokenOdinKind_Defer},
{0, 0},
{4, TokenOdinKind_SizeOf},
{4, TokenOdinKind_F16be},
{4, TokenOdinKind_If},
{0, 0},
{4, TokenOdinKind_U16},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_U64le},
{4, TokenOdinKind_In},
{4, TokenOdinKind_U64be},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_I16le},
{4, TokenOdinKind_Uintptr},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_U128be},
{4, TokenOdinKind_Switch},
{0, 0},
{0, 0},
{4, TokenOdinKind_F32le},
{4, TokenOdinKind_Map},
{4, TokenOdinKind_U32le},
{4, TokenOdinKind_Complex64},
{4, TokenOdinKind_Rawptr},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{8, TokenOdinKind_LiteralTrue},
{8, TokenOdinKind_LiteralFalse},
{4, TokenOdinKind_I8},
{0, 0},
{4, TokenOdinKind_I64be},
{0, 0},
{4, TokenOdinKind_I128be},
{0, 0},
{0, 0},
{4, TokenOdinKind_B8},
{4, TokenOdinKind_U32},
{4, TokenOdinKind_Asm},
{0, 0},
{4, TokenOdinKind_For},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Complex128},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Proc},
{4, TokenOdinKind_I64le},
{4, TokenOdinKind_U32be},
{4, TokenOdinKind_Typeid},
{4, TokenOdinKind_F64be},
{0, 0},
{4, TokenOdinKind_Uninitialized},
{0, 0},
{0, 0},
{4, TokenOdinKind_Import},
{4, TokenOdinKind_NotIn},
{4, TokenOdinKind_Quaternion64},
{0, 0},
{4, TokenOdinKind_I64},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_I128},
{4, TokenOdinKind_Dynamic},
{0, 0},
{0, 0},
{4, TokenOdinKind_BitSet},
{0, 0},
{4, TokenOdinKind_OrReturn},
{4, TokenOdinKind_Return},
{4, TokenOdinKind_Quaternion128},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Do},
{4, TokenOdinKind_Else},
{4, TokenOdinKind_I16be},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_When},
{4, TokenOdinKind_Continue},
{0, 0},
{4, TokenOdinKind_F16le},
{4, TokenOdinKind_Distinct},
{4, TokenOdinKind_Case},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Fallthrough},
{4, TokenOdinKind_Enum},
{0, 0},
{4, TokenOdinKind_U16le},
{0, 0},
{0, 0},
{4, TokenOdinKind_Context},
{0, 0},
{0, 0},
{4, TokenOdinKind_U16be},
{4, TokenOdinKind_F64le},
};
i32 odin_main_keys_slot_count = 182;
u64 odin_main_keys_seed = 0xd8dbd343f1d4f64d;
u64 odin_directives_hash_array[50] = {
0x1be8afa90c20f273,0x0000000000000000,0xc65b2f65f25a3cef,0x0000000000000000,
0xf22fa360f500108d,0xf22e551dab6323d5,0x0000000000000000,0xbb7ca87bcf5ce2e1,
0x0000000000000000,0x159af78375e57c79,0x0cd03c53a1db7d5d,0x0b55325ebc7e5fd9,
0x0000000000000000,0x0000000000000000,0xf68770e0077ede35,0xc65b2f65f2a63219,
0x72504221537ede35,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x15943367741f8017,0x16bf1e8ce6cb9777,0x0000000000000000,0x0b55325bf8613fc1,
0xbb7c89f5f1652f8d,0x0b553259a3ef1b63,0xc65b2f65f1a0c6e7,0xbb7cf0d500627f49,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0xf23d4c49e7475377,
0xbb7ca81851d29c5b,0x1d6b00250b32026b,0x0000000000000000,0x0cd03c53fef416f7,
0xd1139668f71d7575,0x0000000000000000,0x0000000000000000,0x0b5531ae13f73529,
0x0000000000000000,0xc65b2f65f2b59449,0xc65b2f65f2a1e59f,0x0000000000000000,
0x0000000000000000,0xe72caa2855175377,0x516fec591372999f,0x0000000000000000,
0x0000000000000000,0x0b553259ba019305,
};
u8 odin_directives_key_array_0[] = {0x6f,0x70,0x74,0x69,0x6f,0x6e,0x61,0x6c,0x5f,0x61,0x6c,0x6c,0x6f,0x63,0x61,0x74,0x6f,0x72,0x5f,0x65,0x72,0x72,0x6f,0x72,};
u8 odin_directives_key_array_2[] = {0x74,0x79,0x70,0x65,};
u8 odin_directives_key_array_4[] = {0x6e,0x6f,0x5f,0x61,0x6c,0x69,0x61,0x73,};
u8 odin_directives_key_array_5[] = {0x63,0x5f,0x76,0x61,0x72,0x61,0x72,0x67,};
u8 odin_directives_key_array_7[] = {0x70,0x61,0x72,0x74,0x69,0x61,0x6c,};
u8 odin_directives_key_array_9[] = {0x6c,0x6f,0x61,0x64,0x5f,0x68,0x61,0x73,0x68,};
u8 odin_directives_key_array_10[] = {0x70,0x61,0x6e,0x69,0x63,};
u8 odin_directives_key_array_11[] = {0x63,0x6f,0x6e,0x66,0x69,0x67,};
u8 odin_directives_key_array_14[] = {0x62,0x6f,0x75,0x6e,0x64,0x73,0x5f,0x63,0x68,0x65,0x63,0x6b,};
u8 odin_directives_key_array_15[] = {0x6c,0x6f,0x61,0x64,};
u8 odin_directives_key_array_16[] = {0x6e,0x6f,0x5f,0x62,0x6f,0x75,0x6e,0x64,0x73,0x5f,0x63,0x68,0x65,0x63,0x6b,};
u8 odin_directives_key_array_20[] = {0x70,0x72,0x6f,0x63,0x65,0x64,0x75,0x72,0x65,};
u8 odin_directives_key_array_21[] = {0x72,0x61,0x77,0x5f,0x75,0x6e,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_23[] = {0x6e,0x6f,0x5f,0x6e,0x69,0x6c,};
u8 odin_directives_key_array_24[] = {0x61,0x6e,0x79,0x5f,0x69,0x6e,0x74,};
u8 odin_directives_key_array_25[] = {0x62,0x79,0x5f,0x70,0x74,0x72,};
u8 odin_directives_key_array_26[] = {0x66,0x69,0x6c,0x65,};
u8 odin_directives_key_array_27[] = {0x64,0x65,0x66,0x69,0x6e,0x65,0x64,};
u8 odin_directives_key_array_31[] = {0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_32[] = {0x6c,0x6f,0x61,0x64,0x5f,0x6f,0x72,};
u8 odin_directives_key_array_33[] = {0x73,0x6f,0x61,};
u8 odin_directives_key_array_35[] = {0x61,0x6c,0x69,0x67,0x6e,};
u8 odin_directives_key_array_36[] = {0x6f,0x70,0x74,0x69,0x6f,0x6e,0x61,0x6c,0x5f,0x6f,0x6b,};
u8 odin_directives_key_array_39[] = {0x70,0x61,0x63,0x6b,0x65,0x64,};
u8 odin_directives_key_array_41[] = {0x73,0x69,0x6d,0x64,};
u8 odin_directives_key_array_42[] = {0x6c,0x69,0x6e,0x65,};
u8 odin_directives_key_array_45[] = {0x63,0x61,0x6c,0x6c,0x65,0x72,0x5f,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_46[] = {0x66,0x6f,0x72,0x63,0x65,0x5f,0x69,0x6e,0x6c,0x69,0x6e,0x65,};
u8 odin_directives_key_array_49[] = {0x61,0x73,0x73,0x65,0x72,0x74,};
String_Const_u8 odin_directives_key_array[50] = {
{odin_directives_key_array_0, 24},
{0, 0},
{odin_directives_key_array_2, 4},
{0, 0},
{odin_directives_key_array_4, 8},
{odin_directives_key_array_5, 8},
{0, 0},
{odin_directives_key_array_7, 7},
{0, 0},
{odin_directives_key_array_9, 9},
{odin_directives_key_array_10, 5},
{odin_directives_key_array_11, 6},
{0, 0},
{0, 0},
{odin_directives_key_array_14, 12},
{odin_directives_key_array_15, 4},
{odin_directives_key_array_16, 15},
{0, 0},
{0, 0},
{0, 0},
{odin_directives_key_array_20, 9},
{odin_directives_key_array_21, 9},
{0, 0},
{odin_directives_key_array_23, 6},
{odin_directives_key_array_24, 7},
{odin_directives_key_array_25, 6},
{odin_directives_key_array_26, 4},
{odin_directives_key_array_27, 7},
{0, 0},
{0, 0},
{0, 0},
{odin_directives_key_array_31, 8},
{odin_directives_key_array_32, 7},
{odin_directives_key_array_33, 3},
{0, 0},
{odin_directives_key_array_35, 5},
{odin_directives_key_array_36, 11},
{0, 0},
{0, 0},
{odin_directives_key_array_39, 6},
{0, 0},
{odin_directives_key_array_41, 4},
{odin_directives_key_array_42, 4},
{0, 0},
{0, 0},
{odin_directives_key_array_45, 15},
{odin_directives_key_array_46, 12},
{0, 0},
{0, 0},
{odin_directives_key_array_49, 6},
};
Lexeme_Table_Value odin_directives_value_array[50] = {
{4, TokenOdinKind_OptionalAllocatorError},
{0, 0},
{4, TokenOdinKind_Type},
{0, 0},
{4, TokenOdinKind_NoAlias},
{4, TokenOdinKind_CVararg},
{0, 0},
{4, TokenOdinKind_Partial},
{0, 0},
{4, TokenOdinKind_LoadHash},
{4, TokenOdinKind_Panic},
{4, TokenOdinKind_Config},
{0, 0},
{0, 0},
{4, TokenOdinKind_BoundsCheck},
{4, TokenOdinKind_Load},
{4, TokenOdinKind_NoBoundsCheck},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Procedure},
{4, TokenOdinKind_RawUnion},
{0, 0},
{4, TokenOdinKind_NoNil},
{4, TokenOdinKind_AnyInt},
{4, TokenOdinKind_ByPtr},
{4, TokenOdinKind_File},
{4, TokenOdinKind_Defined},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Location},
{4, TokenOdinKind_LoadOr},
{4, TokenOdinKind_Soa},
{0, 0},
{4, TokenOdinKind_Align},
{4, TokenOdinKind_OptionalOk},
{0, 0},
{0, 0},
{4, TokenOdinKind_Packed},
{0, 0},
{4, TokenOdinKind_Simd},
{4, TokenOdinKind_Line},
{0, 0},
{0, 0},
{4, TokenOdinKind_CallerLocation},
{4, TokenOdinKind_ForceInline},
{0, 0},
{0, 0},
{4, TokenOdinKind_Assert},
};
i32 odin_directives_slot_count = 50;
u64 odin_directives_seed = 0x138726b76500b8c9;
u64 odin_attributes_hash_array[49] = {
0x4e22e6019f179afd,0x94924ed3e49e8ae9,0xa52b72ccd16364b9,0x0000000000000000,
0x3683b9d6bd24053d,0x0000000000000000,0x3683b95545d70e7b,0x0000000000000000,
0x0000000000000000,0x91f6f07ca2f76335,0xa52b72ccd17c487b,0xaabbbed0552642c3,
0x0000000000000000,0x91f6f07cbd6a565b,0xae0006329e5befbf,0x0000000000000000,
0x0000000000000000,0xd1bf0deb8e750d0b,0x725bfe6861060015,0x7b6c5dbf2c7e89eb,
0x049e8982b480bbff,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x3683bb66f0228849,0x0000000000000000,0xb5b8b51cffb1e925,0xc19df7972c7e89eb,
0x7de050a50eb7a4a3,0x0000000000000000,0x0000000000000000,0x3683b65cd7dc05af,
0x7de050d8da3ab66b,0x0000000000000000,0x22d82d99f762d22b,0x0000000000000000,
0x0000000000000000,0xef8ba81f54668bc9,0xb1bcaefd30e3239d,0x3683b7271238575b,
0x0000000000000000,0x552d8c8be5452919,0x0000000000000000,0x0000000000000000,
0x8ba0c475131a8e1b,0x0000000000000000,0x0a35e5723ac18795,0x91f6bc5bd2ec2335,
0x0000000000000000,
};
u8 odin_attributes_key_array_0[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x70,0x72,0x65,0x66,0x69,0x78,};
u8 odin_attributes_key_array_1[] = {0x64,0x65,0x70,0x72,0x65,0x63,0x61,0x74,0x65,0x64,};
u8 odin_attributes_key_array_2[] = {0x69,0x6e,0x69,0x74,};
u8 odin_attributes_key_array_4[] = {0x77,0x61,0x72,0x6e,0x69,0x6e,0x67,};
u8 odin_attributes_key_array_6[] = {0x72,0x65,0x71,0x75,0x69,0x72,0x65,};
u8 odin_attributes_key_array_9[] = {0x6f,0x62,0x6a,0x63,0x5f,0x6e,0x61,0x6d,0x65,};
u8 odin_attributes_key_array_10[] = {0x63,0x6f,0x6c,0x64,};
u8 odin_attributes_key_array_11[] = {0x65,0x78,0x74,0x72,0x61,0x5f,0x6c,0x69,0x6e,0x6b,0x65,0x72,0x5f,0x66,0x6c,0x61,0x67,0x73,};
u8 odin_attributes_key_array_13[] = {0x6f,0x62,0x6a,0x63,0x5f,0x74,0x79,0x70,0x65,};
u8 odin_attributes_key_array_14[] = {0x64,0x65,0x66,0x61,0x75,0x6c,0x74,0x5f,0x63,0x61,0x6c,0x6c,0x69,0x6e,0x67,0x5f,0x63,0x6f,0x6e,0x76,0x65,0x6e,0x74,0x69,0x6f,0x6e,};
u8 odin_attributes_key_array_17[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x6e,0x6f,0x6e,0x65,};
u8 odin_attributes_key_array_18[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x6f,0x75,0x74,};
u8 odin_attributes_key_array_19[] = {0x72,0x65,0x71,0x75,0x69,0x72,0x65,0x5f,0x74,0x61,0x72,0x67,0x65,0x74,0x5f,0x66,0x65,0x61,0x74,0x75,0x72,0x65,};
u8 odin_attributes_key_array_20[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x73,0x65,0x63,0x74,0x69,0x6f,0x6e,};
u8 odin_attributes_key_array_24[] = {0x6c,0x69,0x6e,0x6b,0x61,0x67,0x65,};
u8 odin_attributes_key_array_26[] = {0x74,0x68,0x72,0x65,0x61,0x64,0x5f,0x6c,0x6f,0x63,0x61,0x6c,};
u8 odin_attributes_key_array_27[] = {0x65,0x6e,0x61,0x62,0x6c,0x65,0x5f,0x74,0x61,0x72,0x67,0x65,0x74,0x5f,0x66,0x65,0x61,0x74,0x75,0x72,0x65,};
u8 odin_attributes_key_array_28[] = {0x73,0x74,0x61,0x74,0x69,0x63,};
u8 odin_attributes_key_array_31[] = {0x62,0x75,0x69,0x6c,0x74,0x69,0x6e,};
u8 odin_attributes_key_array_32[] = {0x65,0x78,0x70,0x6f,0x72,0x74,};
u8 odin_attributes_key_array_34[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x69,0x6e,};
u8 odin_attributes_key_array_37[] = {0x64,0x69,0x73,0x61,0x62,0x6c,0x65,0x64,};
u8 odin_attributes_key_array_38[] = {0x6f,0x62,0x6a,0x63,0x5f,0x69,0x73,0x5f,0x63,0x6c,0x61,0x73,0x73,0x5f,0x6d,0x65,0x74,0x68,0x6f,0x64,};
u8 odin_attributes_key_array_39[] = {0x70,0x72,0x69,0x76,0x61,0x74,0x65,};
u8 odin_attributes_key_array_41[] = {0x72,0x65,0x71,0x75,0x69,0x72,0x65,0x5f,0x72,0x65,0x73,0x75,0x6c,0x74,0x73,};
u8 odin_attributes_key_array_44[] = {0x6f,0x70,0x74,0x69,0x6d,0x69,0x7a,0x61,0x74,0x69,0x6f,0x6e,0x5f,0x6d,0x6f,0x64,0x65,};
u8 odin_attributes_key_array_46[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x69,0x6e,0x5f,0x6f,0x75,0x74,};
u8 odin_attributes_key_array_47[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x6e,0x61,0x6d,0x65,};
String_Const_u8 odin_attributes_key_array[49] = {
{odin_attributes_key_array_0, 11},
{odin_attributes_key_array_1, 10},
{odin_attributes_key_array_2, 4},
{0, 0},
{odin_attributes_key_array_4, 7},
{0, 0},
{odin_attributes_key_array_6, 7},
{0, 0},
{0, 0},
{odin_attributes_key_array_9, 9},
{odin_attributes_key_array_10, 4},
{odin_attributes_key_array_11, 18},
{0, 0},
{odin_attributes_key_array_13, 9},
{odin_attributes_key_array_14, 26},
{0, 0},
{0, 0},
{odin_attributes_key_array_17, 13},
{odin_attributes_key_array_18, 12},
{odin_attributes_key_array_19, 22},
{odin_attributes_key_array_20, 12},
{0, 0},
{0, 0},
{0, 0},
{odin_attributes_key_array_24, 7},
{0, 0},
{odin_attributes_key_array_26, 12},
{odin_attributes_key_array_27, 21},
{odin_attributes_key_array_28, 6},
{0, 0},
{0, 0},
{odin_attributes_key_array_31, 7},
{odin_attributes_key_array_32, 6},
{0, 0},
{odin_attributes_key_array_34, 11},
{0, 0},
{0, 0},
{odin_attributes_key_array_37, 8},
{odin_attributes_key_array_38, 20},
{odin_attributes_key_array_39, 7},
{0, 0},
{odin_attributes_key_array_41, 15},
{0, 0},
{0, 0},
{odin_attributes_key_array_44, 17},
{0, 0},
{odin_attributes_key_array_46, 15},
{odin_attributes_key_array_47, 9},
{0, 0},
};
Lexeme_Table_Value odin_attributes_value_array[49] = {
{4, TokenOdinKind_AtLinkPrefix},
{4, TokenOdinKind_AtDeprecated},
{4, TokenOdinKind_AtInit},
{0, 0},
{4, TokenOdinKind_AtWarning},
{0, 0},
{4, TokenOdinKind_AtRequire},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtObjcName},
{4, TokenOdinKind_AtCold},
{4, TokenOdinKind_AtExtraLinkerFlags},
{0, 0},
{4, TokenOdinKind_AtObjcType},
{4, TokenOdinKind_AtDefaultCallingConvention},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtDeferredNone},
{4, TokenOdinKind_AtDeferredOut},
{4, TokenOdinKind_AtRequireTargetFeature},
{4, TokenOdinKind_AtLinkSection},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtLinkage},
{0, 0},
{4, TokenOdinKind_AtThreadLocal},
{4, TokenOdinKind_AtEnableTargetFeature},
{4, TokenOdinKind_AtStatic},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtBuiltin},
{4, TokenOdinKind_AtExport},
{0, 0},
{4, TokenOdinKind_AtDeferredIn},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtDisabled},
{4, TokenOdinKind_AtObjcIsClassMethod},
{4, TokenOdinKind_AtPrivate},
{0, 0},
{4, TokenOdinKind_AtRequireResults},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtOptimizationMode},
{0, 0},
{4, TokenOdinKind_AtDeferredInOut},
{4, TokenOdinKind_AtLinkName},
{0, 0},
};
i32 odin_attributes_slot_count = 49;
u64 odin_attributes_seed = 0x48b15175929c1ad6;
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
