#ifndef FCODER_NICKNEMA_BASIC_CPP
#define FCODER_NICKNEMA_BASIC_CPP

NAMESPACE_BEGIN(nicknema)

global Arena global_frame_arena;

function f32 f32_min_of(f32 a, f32 b) {
	f32 r = a < b ? a : b;
    return r;
}

function f32 f32_max_of(f32 a, f32 b) {
    f32 r = a > b ? a : b;
	return r;
}

NAMESPACE_END()

#endif // FCODER_NICKNEMA_BASIC_CPP
