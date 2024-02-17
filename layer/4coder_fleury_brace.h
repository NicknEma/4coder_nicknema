#ifndef FCODER_CUSTOM_BRACE_H
#define FCODER_CUSTOM_BRACE_H

NAMESPACE_BEGIN(nne)

function void F4_Brace_RenderHighlight(Application_Links *app, Buffer_ID buffer, Text_Layout_ID text_layout_id, i64 pos, ARGB_Color *colors, i32 color_count);
function void F4_Brace_RenderCloseBraceAnnotation(Application_Links *app, Buffer_ID buffer, Text_Layout_ID text_layout_id, i64 pos);
function void F4_Brace_RenderLines(Application_Links *app, Buffer_ID buffer, View_ID view, Text_Layout_ID text_layout_id, i64 pos);

NAMESPACE_END()

#endif // 4CODER_CUSTOM_BRACE_H
