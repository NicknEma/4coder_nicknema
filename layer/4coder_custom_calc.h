
//- @f4_calc_intro Built-In Calculator/Plotting
//
// This custom layer includes a tiny little calculator language, which has
// plotting capabilities. It has a few features that comprise it all:
//
// - Calculator Comments: Any comments starting with a 'c', e.g. //c or /*c,
//   will be interpreted as calculator code, including inline plots. This
//   can be useful to do quick calculations, see a math function represented
//   visually, or plot data. You can check out examples/demos in the
//   4coder_fleury_plots_demo.cpp file. Turn it off with "f4_disable_calc_comments"
//   in your config file.
//
// - *calc* Buffer: On startup, a *calc* buffer is opened that you can switch
//   to. The entire buffer is interpreted as calculator code, and it will
//   do all the same things that calc comments do.

#ifndef FCODER_CUSTOM_CALC_H
#define FCODER_CUSTOM_CALC_H

NAMESPACE_BEGIN(nne)

internal void calculator__tick(Frame_Info frame_info);
internal void calculator__render_code(Application_Links *app, Buffer_ID buffer, View_ID view, Text_Layout_ID text_layout_id, Frame_Info frame_info, Arena *arena, char *code_buffer, i64 start_char_offset);
internal void calculator__render_buffer(Application_Links *app, Buffer_ID buffer, View_ID view, Text_Layout_ID text_layout_id, Frame_Info frame_info);
internal void calculator__render_comments(Application_Links *app, Buffer_ID buffer, View_ID view, Text_Layout_ID text_layout_id, Frame_Info frame_info);

NAMESPACE_END()

#endif // FCODER_CUSTOM_CALC_H
