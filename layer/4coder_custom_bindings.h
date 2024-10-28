#ifndef FCODER_CUSTOM_BINDINGS_H
#define FCODER_CUSTOM_BINDINGS_H

NAMESPACE_BEGIN(nne)

function void set_absolutely_necessary_bindings(Mapping *mapping);
function void set_default_bindings(Mapping *mapping);
function b32  dynamic_binding_load_from_file(Application_Links *app, Mapping *mapping, String_Const_u8 filename);
function b32  dynamic_binding_load_from_buffer(Application_Links *app, Mapping *mapping, String_Const_u8 filename, String_Const_u8 buffer);

NAMESPACE_END()

#endif // FCODER_CUSTOM_BINDINGS_H
