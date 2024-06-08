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
0x337ed98401275711,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x337ed98401388983,0x0a84f39145481b93,0x0a84f390a1c6e753,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x80e6124bc7827b4f,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0a84f390a1bdcaa3,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x337ed9840138fbc3,
0x80e6124bc79fa181,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0a84f391454866d3,0x0000000000000000,0xc353078fe0a737fd,
0x0000000000000000,0x1b18ae6b9a43c9b3,0x1b25143271b94b2f,0xc7b369a74f9ddd71,
0x0a84f391ba43df53,0x0000000000000000,0xc3537ee35ded23ed,0x0a84f390a1bdce53,
0x0000000000000000,0x337ed984013883df,0x0000000000000000,0xc3537648fb70cf6f,
0x337ed98401236385,0x48843f68ba33ec43,0x0a84f390a7c5e4d3,0x0000000000000000,
0x337ed984012733d9,0x48843f4f337206e3,0x337ed984013888f7,0x0000000000000000,
0x0000000000000000,0xc353078466fa6d87,0x0000000000000000,0x0a84f391452ca453,
0xd4eb45311ca8ea65,0xc3537e9c8afb2591,0x0000000000000000,0x0a84f39145589f53,
0x337ed9840138d87f,0x80e6124bcb89d369,0x0000000000000000,0x48843f4fbee7d711,
0x0000000000000000,0x0000000000000000,0x80e6124bc79355c7,0x0000000000000000,
0x0000000000000000,0x48843f35c23c1203,0x80e6124bc7e84513,0x0000000000000000,
0x0a84f391ba367113,0x0000000000000000,0x0000000000000000,0x337ed9840138d947,
0x48843f4f0147f225,0x0000000000000000,0x337ed98401278d93,0x0a84f39152f3fb27,
0x0a84f390a1c00453,0x337ed9840138d893,0x80e6124bcb9712e9,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x80e6124bc7ea8d0f,0x0a84f391525b8823,0xd53950b7d62fd405,
0x48843f4f33720653,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x407fe38a3a7b1b17,0x0000000000000000,0xc7b724fd7bcb1e93,0x0a84f391ba43d913,
0x80e6124bc7881283,0x0000000000000000,0x0000000000000000,0x1a2c73be98aa3701,
0x337ed98401278c3b,0x0000000000000000,0x0a84f3904e6c71ad,0x0000000000000000,
0x48843f70157fc3b1,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0xc35307c3b061aa83,0x48843f4f67db1d75,0x80e6124bc798134f,
0x0000000000000000,0x0000000000000000,0x1a2c14a8d929c21d,0x0000000000000000,
0x0000000000000000,0xd4eb45311ca8eaa7,0x0000000000000000,0x60bc528da0f28403,
0x337ed98401271b93,0x0a84f39145589913,0x0000000000000000,0x48843f68d777e6e3,
0x0000000000000000,0x80e6124bcb916d11,0x0000000000000000,0x0000000000000000,
0x337ed98401386d19,0x337ed98401271ae3,0x0000000000000000,0x0000000000000000,
0xc7b724fd7bcb1d47,0x0000000000000000,0x0000000000000000,0xd4eb45311ca8e947,
0x0a84f390a59fedaf,0x48843f70157c8635,0x0000000000000000,0x0000000000000000,
0x337ed9840138e747,0x0000000000000000,0x80e6124bcb916d21,0xd4eb45311ca8e94f,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0a84f391ba3e8d93,
0xc35307c1515bc735,0x0000000000000000,0x80e6124bcb8aa9ad,0x337ed98401278a43,
0x80e6124bcb95e013,0xd4eb45311ca8e675,0x0000000000000000,0x337ed984013863cf,
0x0a84f390a1c004a3,0x0a84f391452ca913,0x0000000000000000,0x407fe38a3a7469ef,
0x0a84f391ba367453,0x0000000000000000,0x0000000000000000,0x48843f7014729141,
0x48843f68d777e653,0x0000000000000000,0x0000000000000000,0x0a84f390a1c6e513,
0x0000000000000000,0x0000000000000000,0xc35376114e4a4c31,0x0a84f391ba3e82d3,
0x0a84f3915fac8f3d,0x0000000000000000,0xd4eb45311ca8e8b5,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0xc35307b7aea52a9f,0x337ed98401271a5b,
0x1b1bd012b74df225,
};
u8 odin_main_keys_key_array_0[] = {0x6d,0x61,0x70,};
u8 odin_main_keys_key_array_5[] = {0x62,0x36,0x34,};
u8 odin_main_keys_key_array_6[] = {0x75,0x36,0x34,0x62,0x65,};
u8 odin_main_keys_key_array_7[] = {0x66,0x36,0x34,0x6c,0x65,};
u8 odin_main_keys_key_array_11[] = {0x69,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_19[] = {0x66,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_23[] = {0x69,0x6e,0x74,};
u8 odin_main_keys_key_array_24[] = {0x74,0x72,0x75,0x65,};
u8 odin_main_keys_key_array_29[] = {0x75,0x36,0x34,0x6c,0x65,};
u8 odin_main_keys_key_array_31[] = {0x62,0x69,0x74,0x5f,0x73,0x65,0x74,};
u8 odin_main_keys_key_array_33[] = {0x74,0x72,0x61,0x6e,0x73,0x6d,0x75,0x74,0x65,};
u8 odin_main_keys_key_array_34[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_35[] = {0x61,0x75,0x74,0x6f,0x5f,0x63,0x61,0x73,0x74,};
u8 odin_main_keys_key_array_36[] = {0x69,0x36,0x34,0x6c,0x65,};
u8 odin_main_keys_key_array_38[] = {0x6f,0x72,0x5f,0x65,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_39[] = {0x66,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_41[] = {0x62,0x31,0x36,};
u8 odin_main_keys_key_array_43[] = {0x73,0x69,0x7a,0x65,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_44[] = {0x2d,0x2d,0x2d,};
u8 odin_main_keys_key_array_45[] = {0x6e,0x6f,0x74,0x5f,0x69,0x6e,};
u8 odin_main_keys_key_array_46[] = {0x64,0x65,0x66,0x65,0x72,};
u8 odin_main_keys_key_array_48[] = {0x6e,0x69,0x6c,};
u8 odin_main_keys_key_array_49[] = {0x75,0x31,0x32,0x38,0x62,0x65,};
u8 odin_main_keys_key_array_50[] = {0x62,0x33,0x32,};
u8 odin_main_keys_key_array_53[] = {0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,};
u8 odin_main_keys_key_array_55[] = {0x75,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_56[] = {0x64,0x6f,};
u8 odin_main_keys_key_array_57[] = {0x70,0x61,0x63,0x6b,0x61,0x67,0x65,};
u8 odin_main_keys_key_array_59[] = {0x75,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_60[] = {0x66,0x31,0x36,};
u8 odin_main_keys_key_array_61[] = {0x62,0x6f,0x6f,0x6c,};
u8 odin_main_keys_key_array_63[] = {0x72,0x61,0x77,0x70,0x74,0x72,};
u8 odin_main_keys_key_array_66[] = {0x70,0x72,0x6f,0x63,};
u8 odin_main_keys_key_array_69[] = {0x69,0x6d,0x70,0x6f,0x72,0x74,};
u8 odin_main_keys_key_array_70[] = {0x75,0x69,0x6e,0x74,};
u8 odin_main_keys_key_array_72[] = {0x69,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_75[] = {0x66,0x33,0x32,};
u8 odin_main_keys_key_array_76[] = {0x72,0x65,0x74,0x75,0x72,0x6e,};
u8 odin_main_keys_key_array_78[] = {0x75,0x33,0x32,};
u8 odin_main_keys_key_array_79[] = {0x75,0x6e,0x69,0x6f,0x6e,};
u8 odin_main_keys_key_array_80[] = {0x66,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_81[] = {0x66,0x36,0x34,};
u8 odin_main_keys_key_array_82[] = {0x65,0x6e,0x75,0x6d,};
u8 odin_main_keys_key_array_89[] = {0x77,0x68,0x65,0x6e,};
u8 odin_main_keys_key_array_90[] = {0x77,0x68,0x65,0x72,0x65,};
u8 odin_main_keys_key_array_91[] = {0x66,0x61,0x6c,0x6c,0x74,0x68,0x72,0x6f,0x75,0x67,0x68,};
u8 odin_main_keys_key_array_92[] = {0x75,0x31,0x32,0x38,0x6c,0x65,};
u8 odin_main_keys_key_array_96[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x32,0x35,0x36,};
u8 odin_main_keys_key_array_98[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x36,0x34,};
u8 odin_main_keys_key_array_99[] = {0x69,0x36,0x34,0x62,0x65,};
u8 odin_main_keys_key_array_100[] = {0x72,0x75,0x6e,0x65,};
u8 odin_main_keys_key_array_103[] = {0x63,0x6f,0x6e,0x74,0x69,0x6e,0x75,0x65,};
u8 odin_main_keys_key_array_104[] = {0x75,0x31,0x36,};
u8 odin_main_keys_key_array_106[] = {0x66,0x61,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_108[] = {0x73,0x74,0x72,0x75,0x63,0x74,};
u8 odin_main_keys_key_array_113[] = {0x63,0x6f,0x6e,0x74,0x65,0x78,0x74,};
u8 odin_main_keys_key_array_114[] = {0x74,0x79,0x70,0x65,0x69,0x64,};
u8 odin_main_keys_key_array_115[] = {0x75,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_118[] = {0x64,0x69,0x73,0x74,0x69,0x6e,0x63,0x74,};
u8 odin_main_keys_key_array_121[] = {0x62,0x38,};
u8 odin_main_keys_key_array_123[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x36,0x34,};
u8 odin_main_keys_key_array_124[] = {0x69,0x36,0x34,};
u8 odin_main_keys_key_array_125[] = {0x75,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_127[] = {0x69,0x31,0x32,0x38,0x62,0x65,};
u8 odin_main_keys_key_array_129[] = {0x63,0x61,0x73,0x74,};
u8 odin_main_keys_key_array_132[] = {0x61,0x73,0x6d,};
u8 odin_main_keys_key_array_133[] = {0x69,0x33,0x32,};
u8 odin_main_keys_key_array_136[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x33,0x32,};
u8 odin_main_keys_key_array_139[] = {0x69,0x6e,};
u8 odin_main_keys_key_array_140[] = {0x62,0x72,0x65,0x61,0x6b,};
u8 odin_main_keys_key_array_141[] = {0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_144[] = {0x66,0x6f,0x72,};
u8 odin_main_keys_key_array_146[] = {0x63,0x61,0x73,0x65,};
u8 odin_main_keys_key_array_147[] = {0x69,0x66,};
u8 odin_main_keys_key_array_151[] = {0x69,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_152[] = {0x63,0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_154[] = {0x65,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_155[] = {0x75,0x36,0x34,};
u8 odin_main_keys_key_array_156[] = {0x62,0x79,0x74,0x65,};
u8 odin_main_keys_key_array_157[] = {0x75,0x38,};
u8 odin_main_keys_key_array_159[] = {0x61,0x6e,0x79,};
u8 odin_main_keys_key_array_160[] = {0x66,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_161[] = {0x75,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_163[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_164[] = {0x69,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_167[] = {0x73,0x77,0x69,0x74,0x63,0x68,};
u8 odin_main_keys_key_array_168[] = {0x69,0x31,0x32,0x38,0x6c,0x65,};
u8 odin_main_keys_key_array_171[] = {0x66,0x36,0x34,0x62,0x65,};
u8 odin_main_keys_key_array_174[] = {0x75,0x69,0x6e,0x74,0x70,0x74,0x72,};
u8 odin_main_keys_key_array_175[] = {0x69,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_176[] = {0x75,0x73,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_178[] = {0x69,0x38,};
u8 odin_main_keys_key_array_182[] = {0x66,0x6f,0x72,0x65,0x69,0x67,0x6e,};
u8 odin_main_keys_key_array_183[] = {0x69,0x31,0x36,};
u8 odin_main_keys_key_array_184[] = {0x6f,0x72,0x5f,0x72,0x65,0x74,0x75,0x72,0x6e,};
String_Const_u8 odin_main_keys_key_array[185] = {
{odin_main_keys_key_array_0, 3},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_5, 3},
{odin_main_keys_key_array_6, 5},
{odin_main_keys_key_array_7, 5},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_11, 4},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_19, 5},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_23, 3},
{odin_main_keys_key_array_24, 4},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_29, 5},
{0, 0},
{odin_main_keys_key_array_31, 7},
{0, 0},
{odin_main_keys_key_array_33, 9},
{odin_main_keys_key_array_34, 10},
{odin_main_keys_key_array_35, 9},
{odin_main_keys_key_array_36, 5},
{0, 0},
{odin_main_keys_key_array_38, 7},
{odin_main_keys_key_array_39, 5},
{0, 0},
{odin_main_keys_key_array_41, 3},
{0, 0},
{odin_main_keys_key_array_43, 7},
{odin_main_keys_key_array_44, 3},
{odin_main_keys_key_array_45, 6},
{odin_main_keys_key_array_46, 5},
{0, 0},
{odin_main_keys_key_array_48, 3},
{odin_main_keys_key_array_49, 6},
{odin_main_keys_key_array_50, 3},
{0, 0},
{0, 0},
{odin_main_keys_key_array_53, 7},
{0, 0},
{odin_main_keys_key_array_55, 5},
{odin_main_keys_key_array_56, 2},
{odin_main_keys_key_array_57, 7},
{0, 0},
{odin_main_keys_key_array_59, 5},
{odin_main_keys_key_array_60, 3},
{odin_main_keys_key_array_61, 4},
{0, 0},
{odin_main_keys_key_array_63, 6},
{0, 0},
{0, 0},
{odin_main_keys_key_array_66, 4},
{0, 0},
{0, 0},
{odin_main_keys_key_array_69, 6},
{odin_main_keys_key_array_70, 4},
{0, 0},
{odin_main_keys_key_array_72, 5},
{0, 0},
{0, 0},
{odin_main_keys_key_array_75, 3},
{odin_main_keys_key_array_76, 6},
{0, 0},
{odin_main_keys_key_array_78, 3},
{odin_main_keys_key_array_79, 5},
{odin_main_keys_key_array_80, 5},
{odin_main_keys_key_array_81, 3},
{odin_main_keys_key_array_82, 4},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_89, 4},
{odin_main_keys_key_array_90, 5},
{odin_main_keys_key_array_91, 11},
{odin_main_keys_key_array_92, 6},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_96, 13},
{0, 0},
{odin_main_keys_key_array_98, 9},
{odin_main_keys_key_array_99, 5},
{odin_main_keys_key_array_100, 4},
{0, 0},
{0, 0},
{odin_main_keys_key_array_103, 8},
{odin_main_keys_key_array_104, 3},
{0, 0},
{odin_main_keys_key_array_106, 5},
{0, 0},
{odin_main_keys_key_array_108, 6},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_113, 7},
{odin_main_keys_key_array_114, 6},
{odin_main_keys_key_array_115, 4},
{0, 0},
{0, 0},
{odin_main_keys_key_array_118, 8},
{0, 0},
{0, 0},
{odin_main_keys_key_array_121, 2},
{0, 0},
{odin_main_keys_key_array_123, 12},
{odin_main_keys_key_array_124, 3},
{odin_main_keys_key_array_125, 5},
{0, 0},
{odin_main_keys_key_array_127, 6},
{0, 0},
{odin_main_keys_key_array_129, 4},
{0, 0},
{0, 0},
{odin_main_keys_key_array_132, 3},
{odin_main_keys_key_array_133, 3},
{0, 0},
{0, 0},
{odin_main_keys_key_array_136, 9},
{0, 0},
{0, 0},
{odin_main_keys_key_array_139, 2},
{odin_main_keys_key_array_140, 5},
{odin_main_keys_key_array_141, 6},
{0, 0},
{0, 0},
{odin_main_keys_key_array_144, 3},
{0, 0},
{odin_main_keys_key_array_146, 4},
{odin_main_keys_key_array_147, 2},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_151, 5},
{odin_main_keys_key_array_152, 7},
{0, 0},
{odin_main_keys_key_array_154, 4},
{odin_main_keys_key_array_155, 3},
{odin_main_keys_key_array_156, 4},
{odin_main_keys_key_array_157, 2},
{0, 0},
{odin_main_keys_key_array_159, 3},
{odin_main_keys_key_array_160, 5},
{odin_main_keys_key_array_161, 5},
{0, 0},
{odin_main_keys_key_array_163, 13},
{odin_main_keys_key_array_164, 5},
{0, 0},
{0, 0},
{odin_main_keys_key_array_167, 6},
{odin_main_keys_key_array_168, 6},
{0, 0},
{0, 0},
{odin_main_keys_key_array_171, 5},
{0, 0},
{0, 0},
{odin_main_keys_key_array_174, 7},
{odin_main_keys_key_array_175, 5},
{odin_main_keys_key_array_176, 5},
{0, 0},
{odin_main_keys_key_array_178, 2},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_182, 7},
{odin_main_keys_key_array_183, 3},
{odin_main_keys_key_array_184, 9},
};
Lexeme_Table_Value odin_main_keys_value_array[185] = {
{4, TokenOdinKind_Map},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_B64},
{4, TokenOdinKind_U64be},
{4, TokenOdinKind_F64le},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_I128},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_F32be},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Int},
{8, TokenOdinKind_LiteralTrue},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_U64le},
{0, 0},
{4, TokenOdinKind_BitSet},
{0, 0},
{4, TokenOdinKind_Transmute},
{4, TokenOdinKind_Complex128},
{4, TokenOdinKind_AutoCast},
{4, TokenOdinKind_I64le},
{0, 0},
{4, TokenOdinKind_OrElse},
{4, TokenOdinKind_F32le},
{0, 0},
{4, TokenOdinKind_B16},
{0, 0},
{4, TokenOdinKind_SizeOf},
{4, TokenOdinKind_Uninitialized},
{4, TokenOdinKind_NotIn},
{4, TokenOdinKind_Defer},
{0, 0},
{4, TokenOdinKind_Nil},
{4, TokenOdinKind_U128be},
{4, TokenOdinKind_B32},
{0, 0},
{0, 0},
{4, TokenOdinKind_Dynamic},
{0, 0},
{4, TokenOdinKind_U16le},
{4, TokenOdinKind_Do},
{4, TokenOdinKind_Package},
{0, 0},
{4, TokenOdinKind_U32le},
{4, TokenOdinKind_F16},
{4, TokenOdinKind_Bool},
{0, 0},
{4, TokenOdinKind_Rawptr},
{0, 0},
{0, 0},
{4, TokenOdinKind_Proc},
{0, 0},
{0, 0},
{4, TokenOdinKind_Import},
{4, TokenOdinKind_Uint},
{0, 0},
{4, TokenOdinKind_I16be},
{0, 0},
{0, 0},
{4, TokenOdinKind_F32},
{4, TokenOdinKind_Return},
{0, 0},
{4, TokenOdinKind_U32},
{4, TokenOdinKind_Union},
{4, TokenOdinKind_F16le},
{4, TokenOdinKind_F64},
{4, TokenOdinKind_Enum},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_When},
{4, TokenOdinKind_Where},
{4, TokenOdinKind_Fallthrough},
{4, TokenOdinKind_U128le},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Quaternion256},
{0, 0},
{4, TokenOdinKind_Complex64},
{4, TokenOdinKind_I64be},
{4, TokenOdinKind_Rune},
{0, 0},
{0, 0},
{4, TokenOdinKind_Continue},
{4, TokenOdinKind_U16},
{0, 0},
{8, TokenOdinKind_LiteralFalse},
{0, 0},
{4, TokenOdinKind_Struct},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Context},
{4, TokenOdinKind_Typeid},
{4, TokenOdinKind_U128},
{0, 0},
{0, 0},
{4, TokenOdinKind_Distinct},
{0, 0},
{0, 0},
{4, TokenOdinKind_B8},
{0, 0},
{4, TokenOdinKind_Quaternion64},
{4, TokenOdinKind_I64},
{4, TokenOdinKind_U32be},
{0, 0},
{4, TokenOdinKind_I128be},
{0, 0},
{4, TokenOdinKind_Cast},
{0, 0},
{0, 0},
{4, TokenOdinKind_Asm},
{4, TokenOdinKind_I32},
{0, 0},
{0, 0},
{4, TokenOdinKind_Complex32},
{0, 0},
{0, 0},
{4, TokenOdinKind_In},
{4, TokenOdinKind_Break},
{4, TokenOdinKind_String},
{0, 0},
{0, 0},
{4, TokenOdinKind_For},
{0, 0},
{4, TokenOdinKind_Case},
{4, TokenOdinKind_If},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_I32be},
{4, TokenOdinKind_Cstring},
{0, 0},
{4, TokenOdinKind_Else},
{4, TokenOdinKind_U64},
{4, TokenOdinKind_Byte},
{4, TokenOdinKind_U8},
{0, 0},
{4, TokenOdinKind_Any},
{4, TokenOdinKind_F16be},
{4, TokenOdinKind_U16be},
{0, 0},
{4, TokenOdinKind_Quaternion128},
{4, TokenOdinKind_I16le},
{0, 0},
{0, 0},
{4, TokenOdinKind_Switch},
{4, TokenOdinKind_I128le},
{0, 0},
{0, 0},
{4, TokenOdinKind_F64be},
{0, 0},
{0, 0},
{4, TokenOdinKind_Uintptr},
{4, TokenOdinKind_I32le},
{4, TokenOdinKind_Using},
{0, 0},
{4, TokenOdinKind_I8},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_Foreign},
{4, TokenOdinKind_I16},
{4, TokenOdinKind_OrReturn},
};
i32 odin_main_keys_slot_count = 185;
u64 odin_main_keys_seed = 0xd55caa6382a24f2e;
u64 odin_directives_hash_array[51] = {
0x2a65f84c777f00cd,0x0000000000000000,0xcc2628beed19938d,0xe033ac458377f441,
0x0000000000000000,0x0000000000000000,0x66beffdd32964fb7,0x0000000000000000,
0x0000000000000000,0x2a65f84c777da49b,0x2a65f84c77ae9943,0x0000000000000000,
0x0000000000000000,0xe871d157f5854299,0xc57964dd728dafa9,0x2a65f84c7751683b,
0x0000000000000000,0x0000000000000000,0x97f1b53634fc8f0f,0x66beff967684f4cd,
0x0000000000000000,0xbae92029827b114b,0x66beffdeb256b421,0x0000000000000000,
0xe871d1570361ae1b,0x0000000000000000,0x0000000000000000,0x4b774d1da8fef74f,
0xbaea5f4d0b9f9fb3,0xcc26186a176bb76d,0xcc2628b68f8820df,0x2a65f84c77ad7c75,
0x0000000000000000,0x66beff95f0aaa38d,0x964059027ae5896b,0xc45ad356c8d4e589,
0x66beffd9f807b905,0x0000000000000000,0x0000000000000000,0x4424c09d3dc0b943,
0xc57d887e99096e01,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0xcc26180e772d9011,0xbaeba68643d42e45,0xc57979213d21896b,0x0000000000000000,
0x0000000000000000,0xc06c3c9e4cd4e589,0x0000000000000000,
};
u8 odin_directives_key_array_0[] = {0x73,0x69,0x6d,0x64,};
u8 odin_directives_key_array_2[] = {0x70,0x61,0x72,0x74,0x69,0x61,0x6c,};
u8 odin_directives_key_array_3[] = {0x6f,0x70,0x74,0x69,0x6f,0x6e,0x61,0x6c,0x5f,0x6f,0x6b,};
u8 odin_directives_key_array_6[] = {0x62,0x79,0x5f,0x70,0x74,0x72,};
u8 odin_directives_key_array_9[] = {0x74,0x79,0x70,0x65,};
u8 odin_directives_key_array_10[] = {0x6c,0x69,0x6e,0x65,};
u8 odin_directives_key_array_13[] = {0x70,0x61,0x6e,0x69,0x63,};
u8 odin_directives_key_array_14[] = {0x6e,0x6f,0x5f,0x61,0x6c,0x69,0x61,0x73,};
u8 odin_directives_key_array_15[] = {0x66,0x69,0x6c,0x65,};
u8 odin_directives_key_array_18[] = {0x6f,0x70,0x74,0x69,0x6f,0x6e,0x61,0x6c,0x5f,0x61,0x6c,0x6c,0x6f,0x63,0x61,0x74,0x6f,0x72,0x5f,0x65,0x72,0x72,0x6f,0x72,};
u8 odin_directives_key_array_19[] = {0x70,0x61,0x63,0x6b,0x65,0x64,};
u8 odin_directives_key_array_21[] = {0x72,0x61,0x77,0x5f,0x75,0x6e,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_22[] = {0x61,0x73,0x73,0x65,0x72,0x74,};
u8 odin_directives_key_array_24[] = {0x61,0x6c,0x69,0x67,0x6e,};
u8 odin_directives_key_array_27[] = {0x73,0x6f,0x61,};
u8 odin_directives_key_array_28[] = {0x70,0x72,0x6f,0x63,0x65,0x64,0x75,0x72,0x65,};
u8 odin_directives_key_array_29[] = {0x64,0x65,0x66,0x69,0x6e,0x65,0x64,};
u8 odin_directives_key_array_30[] = {0x6c,0x6f,0x61,0x64,0x5f,0x6f,0x72,};
u8 odin_directives_key_array_31[] = {0x6c,0x6f,0x61,0x64,};
u8 odin_directives_key_array_33[] = {0x6e,0x6f,0x5f,0x6e,0x69,0x6c,};
u8 odin_directives_key_array_34[] = {0x63,0x61,0x6c,0x6c,0x65,0x72,0x5f,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_35[] = {0x6e,0x6f,0x5f,0x62,0x6f,0x75,0x6e,0x64,0x73,0x5f,0x63,0x68,0x65,0x63,0x6b,};
u8 odin_directives_key_array_36[] = {0x63,0x6f,0x6e,0x66,0x69,0x67,};
u8 odin_directives_key_array_39[] = {0x66,0x6f,0x72,0x63,0x65,0x5f,0x69,0x6e,0x6c,0x69,0x6e,0x65,};
u8 odin_directives_key_array_40[] = {0x63,0x5f,0x76,0x61,0x72,0x61,0x72,0x67,};
u8 odin_directives_key_array_44[] = {0x61,0x6e,0x79,0x5f,0x69,0x6e,0x74,};
u8 odin_directives_key_array_45[] = {0x6c,0x6f,0x61,0x64,0x5f,0x68,0x61,0x73,0x68,};
u8 odin_directives_key_array_46[] = {0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_49[] = {0x62,0x6f,0x75,0x6e,0x64,0x73,0x5f,0x63,0x68,0x65,0x63,0x6b,};
String_Const_u8 odin_directives_key_array[51] = {
{odin_directives_key_array_0, 4},
{0, 0},
{odin_directives_key_array_2, 7},
{odin_directives_key_array_3, 11},
{0, 0},
{0, 0},
{odin_directives_key_array_6, 6},
{0, 0},
{0, 0},
{odin_directives_key_array_9, 4},
{odin_directives_key_array_10, 4},
{0, 0},
{0, 0},
{odin_directives_key_array_13, 5},
{odin_directives_key_array_14, 8},
{odin_directives_key_array_15, 4},
{0, 0},
{0, 0},
{odin_directives_key_array_18, 24},
{odin_directives_key_array_19, 6},
{0, 0},
{odin_directives_key_array_21, 9},
{odin_directives_key_array_22, 6},
{0, 0},
{odin_directives_key_array_24, 5},
{0, 0},
{0, 0},
{odin_directives_key_array_27, 3},
{odin_directives_key_array_28, 9},
{odin_directives_key_array_29, 7},
{odin_directives_key_array_30, 7},
{odin_directives_key_array_31, 4},
{0, 0},
{odin_directives_key_array_33, 6},
{odin_directives_key_array_34, 15},
{odin_directives_key_array_35, 15},
{odin_directives_key_array_36, 6},
{0, 0},
{0, 0},
{odin_directives_key_array_39, 12},
{odin_directives_key_array_40, 8},
{0, 0},
{0, 0},
{0, 0},
{odin_directives_key_array_44, 7},
{odin_directives_key_array_45, 9},
{odin_directives_key_array_46, 8},
{0, 0},
{0, 0},
{odin_directives_key_array_49, 12},
{0, 0},
};
Lexeme_Table_Value odin_directives_value_array[51] = {
{4, TokenOdinKind_Simd},
{0, 0},
{4, TokenOdinKind_Partial},
{4, TokenOdinKind_OptionalOk},
{0, 0},
{0, 0},
{4, TokenOdinKind_ByPtr},
{0, 0},
{0, 0},
{4, TokenOdinKind_Type},
{4, TokenOdinKind_Line},
{0, 0},
{0, 0},
{4, TokenOdinKind_Panic},
{4, TokenOdinKind_NoAlias},
{4, TokenOdinKind_File},
{0, 0},
{0, 0},
{4, TokenOdinKind_OptionalAllocatorError},
{4, TokenOdinKind_Packed},
{0, 0},
{4, TokenOdinKind_RawUnion},
{4, TokenOdinKind_Assert},
{0, 0},
{4, TokenOdinKind_Align},
{0, 0},
{0, 0},
{4, TokenOdinKind_Soa},
{4, TokenOdinKind_Procedure},
{4, TokenOdinKind_Defined},
{4, TokenOdinKind_LoadOr},
{4, TokenOdinKind_Load},
{0, 0},
{4, TokenOdinKind_NoNil},
{4, TokenOdinKind_CallerLocation},
{4, TokenOdinKind_NoBoundsCheck},
{4, TokenOdinKind_Config},
{0, 0},
{0, 0},
{4, TokenOdinKind_ForceInline},
{4, TokenOdinKind_CVararg},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_AnyInt},
{4, TokenOdinKind_LoadHash},
{4, TokenOdinKind_Location},
{0, 0},
{0, 0},
{4, TokenOdinKind_BoundsCheck},
{0, 0},
};
i32 odin_directives_slot_count = 51;
u64 odin_directives_seed = 0xfc93ef7becbf0e9d;
u64 odin_attributes_hash_array[49] = {
0x0000000000000000,0x0000000000000000,0x9cef68c852add2cb,0x553d1983116aaf9d,
0xef0e8ad711df003b,0x890b5e0984a4e2f5,0x0000000000000000,0xdff5334c9eab914f,
0x44244fe96dbf4783,0x0000000000000000,0x259897b5eec587a5,0x8590bf5382689bfd,
0x0000000000000000,0x0000000000000000,0x442f5359cb069c15,0xaa397ae0ee428291,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x2facae0f024d2a3d,
0x0000000000000000,0x2facb186018cb801,0x11712521d0f98339,0x553d1983115d457b,
0x0000000000000000,0xc00cc8c0439d4821,0x0000000000000000,0x5aeda2278a8401ef,
0x2fa3590984f4d90b,0x442f5359caa1f783,0x0000000000000000,0x076df740b9503f43,
0xc6fdf628eaed3cf3,0x890b5e09a45d2a31,0x0000000000000000,0x5f20007c776563a1,
0x240e9e2665f6c5ab,0x2fa356c2b4713fb3,0x2fa354c6d1dca9d1,0x0000000000000000,
0x0000000000000000,0x4d1b5f0046428291,0x0000000000000000,0x0000000000000000,
0xb5c0aa921c80b401,0x0000000000000000,0xb8ffce7328f3d743,0x0000000000000000,
0x0000000000000000,
};
u8 odin_attributes_key_array_2[] = {0x64,0x65,0x70,0x72,0x65,0x63,0x61,0x74,0x65,0x64,};
u8 odin_attributes_key_array_3[] = {0x63,0x6f,0x6c,0x64,};
u8 odin_attributes_key_array_4[] = {0x74,0x68,0x72,0x65,0x61,0x64,0x5f,0x6c,0x6f,0x63,0x61,0x6c,};
u8 odin_attributes_key_array_5[] = {0x73,0x74,0x61,0x74,0x69,0x63,};
u8 odin_attributes_key_array_7[] = {0x72,0x65,0x71,0x75,0x69,0x72,0x65,0x5f,0x72,0x65,0x73,0x75,0x6c,0x74,0x73,};
u8 odin_attributes_key_array_8[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x6e,0x61,0x6d,0x65,};
u8 odin_attributes_key_array_10[] = {0x65,0x78,0x74,0x72,0x61,0x5f,0x6c,0x69,0x6e,0x6b,0x65,0x72,0x5f,0x66,0x6c,0x61,0x67,0x73,};
u8 odin_attributes_key_array_11[] = {0x6f,0x70,0x74,0x69,0x6d,0x69,0x7a,0x61,0x74,0x69,0x6f,0x6e,0x5f,0x6d,0x6f,0x64,0x65,};
u8 odin_attributes_key_array_14[] = {0x6f,0x62,0x6a,0x63,0x5f,0x74,0x79,0x70,0x65,};
u8 odin_attributes_key_array_15[] = {0x72,0x65,0x71,0x75,0x69,0x72,0x65,0x5f,0x74,0x61,0x72,0x67,0x65,0x74,0x5f,0x66,0x65,0x61,0x74,0x75,0x72,0x65,};
u8 odin_attributes_key_array_19[] = {0x70,0x72,0x69,0x76,0x61,0x74,0x65,};
u8 odin_attributes_key_array_21[] = {0x72,0x65,0x71,0x75,0x69,0x72,0x65,};
u8 odin_attributes_key_array_22[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x69,0x6e,};
u8 odin_attributes_key_array_23[] = {0x69,0x6e,0x69,0x74,};
u8 odin_attributes_key_array_25[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x6e,0x6f,0x6e,0x65,};
u8 odin_attributes_key_array_27[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x70,0x72,0x65,0x66,0x69,0x78,};
u8 odin_attributes_key_array_28[] = {0x6c,0x69,0x6e,0x6b,0x61,0x67,0x65,};
u8 odin_attributes_key_array_29[] = {0x6f,0x62,0x6a,0x63,0x5f,0x6e,0x61,0x6d,0x65,};
u8 odin_attributes_key_array_31[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x6f,0x75,0x74,};
u8 odin_attributes_key_array_32[] = {0x6f,0x62,0x6a,0x63,0x5f,0x69,0x73,0x5f,0x63,0x6c,0x61,0x73,0x73,0x5f,0x6d,0x65,0x74,0x68,0x6f,0x64,};
u8 odin_attributes_key_array_33[] = {0x65,0x78,0x70,0x6f,0x72,0x74,};
u8 odin_attributes_key_array_35[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x73,0x65,0x63,0x74,0x69,0x6f,0x6e,};
u8 odin_attributes_key_array_36[] = {0x64,0x69,0x73,0x61,0x62,0x6c,0x65,0x64,};
u8 odin_attributes_key_array_37[] = {0x77,0x61,0x72,0x6e,0x69,0x6e,0x67,};
u8 odin_attributes_key_array_38[] = {0x62,0x75,0x69,0x6c,0x74,0x69,0x6e,};
u8 odin_attributes_key_array_41[] = {0x65,0x6e,0x61,0x62,0x6c,0x65,0x5f,0x74,0x61,0x72,0x67,0x65,0x74,0x5f,0x66,0x65,0x61,0x74,0x75,0x72,0x65,};
u8 odin_attributes_key_array_44[] = {0x64,0x65,0x66,0x61,0x75,0x6c,0x74,0x5f,0x63,0x61,0x6c,0x6c,0x69,0x6e,0x67,0x5f,0x63,0x6f,0x6e,0x76,0x65,0x6e,0x74,0x69,0x6f,0x6e,};
u8 odin_attributes_key_array_46[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x69,0x6e,0x5f,0x6f,0x75,0x74,};
String_Const_u8 odin_attributes_key_array[49] = {
{0, 0},
{0, 0},
{odin_attributes_key_array_2, 10},
{odin_attributes_key_array_3, 4},
{odin_attributes_key_array_4, 12},
{odin_attributes_key_array_5, 6},
{0, 0},
{odin_attributes_key_array_7, 15},
{odin_attributes_key_array_8, 9},
{0, 0},
{odin_attributes_key_array_10, 18},
{odin_attributes_key_array_11, 17},
{0, 0},
{0, 0},
{odin_attributes_key_array_14, 9},
{odin_attributes_key_array_15, 22},
{0, 0},
{0, 0},
{0, 0},
{odin_attributes_key_array_19, 7},
{0, 0},
{odin_attributes_key_array_21, 7},
{odin_attributes_key_array_22, 11},
{odin_attributes_key_array_23, 4},
{0, 0},
{odin_attributes_key_array_25, 13},
{0, 0},
{odin_attributes_key_array_27, 11},
{odin_attributes_key_array_28, 7},
{odin_attributes_key_array_29, 9},
{0, 0},
{odin_attributes_key_array_31, 12},
{odin_attributes_key_array_32, 20},
{odin_attributes_key_array_33, 6},
{0, 0},
{odin_attributes_key_array_35, 12},
{odin_attributes_key_array_36, 8},
{odin_attributes_key_array_37, 7},
{odin_attributes_key_array_38, 7},
{0, 0},
{0, 0},
{odin_attributes_key_array_41, 21},
{0, 0},
{0, 0},
{odin_attributes_key_array_44, 26},
{0, 0},
{odin_attributes_key_array_46, 15},
{0, 0},
{0, 0},
};
Lexeme_Table_Value odin_attributes_value_array[49] = {
{0, 0},
{0, 0},
{4, TokenOdinKind_AtDeprecated},
{4, TokenOdinKind_AtCold},
{4, TokenOdinKind_AtThreadLocal},
{4, TokenOdinKind_AtStatic},
{0, 0},
{4, TokenOdinKind_AtRequireResults},
{4, TokenOdinKind_AtLinkName},
{0, 0},
{4, TokenOdinKind_AtExtraLinkerFlags},
{4, TokenOdinKind_AtOptimizationMode},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtObjcType},
{4, TokenOdinKind_AtRequireTargetFeature},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtPrivate},
{0, 0},
{4, TokenOdinKind_AtRequire},
{4, TokenOdinKind_AtDeferredIn},
{4, TokenOdinKind_AtInit},
{0, 0},
{4, TokenOdinKind_AtDeferredNone},
{0, 0},
{4, TokenOdinKind_AtLinkPrefix},
{4, TokenOdinKind_AtLinkage},
{4, TokenOdinKind_AtObjcName},
{0, 0},
{4, TokenOdinKind_AtDeferredOut},
{4, TokenOdinKind_AtObjcIsClassMethod},
{4, TokenOdinKind_AtExport},
{0, 0},
{4, TokenOdinKind_AtLinkSection},
{4, TokenOdinKind_AtDisabled},
{4, TokenOdinKind_AtWarning},
{4, TokenOdinKind_AtBuiltin},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtEnableTargetFeature},
{0, 0},
{0, 0},
{4, TokenOdinKind_AtDefaultCallingConvention},
{0, 0},
{4, TokenOdinKind_AtDeferredInOut},
{0, 0},
{0, 0},
};
i32 odin_attributes_slot_count = 49;
u64 odin_attributes_seed = 0x11094396401bed8c;
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
