#ifndef FCODER_NICKNEMA_BASIC_H
#define FCODER_NICKNEMA_BASIC_H

//
// Macros
//

#define cast(t) (t)
#define procedure function

#define Allow_Break() do {int __x__ = 0; (void)__x__;} while (0)

#ifndef NAMESPACE_BEGIN
#define NAMESPACE_BEGIN(name) namespace name {
#endif

#ifndef NAMESPACE_END
#define NAMESPACE_END() }
#endif

#define Str_U8(s) str8_lit(s)

//
// Helpers.
//

NAMESPACE_BEGIN(nicknema)

function f32 f32_min_of(f32 a, f32 b);
function f32 f32_max_of(f32 a, f32 b);

NAMESPACE_END()

#endif // FCODER_NICKNEMA_BASIC_H
