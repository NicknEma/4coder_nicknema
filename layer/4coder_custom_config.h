#ifndef FCODER_CUSTOM_CONFIG_H
#define FCODER_CUSTOM_CONFIG_H

NAMESPACE_BEGIN(nne)

internal b32 config_load_from_buffer(Application_Links *app, Arena *out_arena, b32 override_font_size, b32 override_hinting, String8 filename, String8 buffer);
internal b32 config_load_from_file(Application_Links *app, Arena *out_arena, i32 override_font_size, b32 override_hinting);

NAMESPACE_END()

#endif // FCODER_CUSTOM_CONFIG_H
