#ifndef FCODER_CUSTOM_LOAD_H
#define FCODER_CUSTOM_LOAD_H

NAMESPACE_BEGIN(nne)

internal void apply_parsed_config();
internal void parse_config_and_apply();
internal void load_config_and_apply(Application_Links *app, Arena *out_arena, i32 override_font_size, b32 override_hinting);

NAMESPACE_END()

#endif // FCODER_CUSTOM_LOAD_H
