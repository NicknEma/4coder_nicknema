#ifndef FCODER_FLEURY_LEGO_H
#define FCODER_FLEURY_LEGO_H

NAMESPACE_BEGIN(nne)

enum F4_LegoKind
{
    F4_LegoKind_Null,
    F4_LegoKind_String,
    F4_LegoKind_Macro,
    F4_LegoKind_File,
    F4_LegoKind_COUNT
};

struct F4_Lego
{
    b32 initialized;
    F4_LegoKind kind;
    Arena arena;
    String8 string;
};

function void F4_Lego_Store(F4_Lego *lego, F4_LegoKind kind, String8 string);

NAMESPACE_END()

#endif // FCODER_FLEURY_LEGO_H
