#ifndef FCODER_CUSTOM_AUDIO_CPP
#define FCODER_CUSTOM_AUDIO_CPP

NAMESPACE_BEGIN(nne)

function b32 audio_clip_is_valid(Audio_Clip clip) {
    return clip.samples != 0 && clip.samples != (i16 *)0x00000001;
}

function b32 audio_clip_is_unloadable(Audio_Clip clip) {
    return clip.samples == (i16 *)0x00000001;
}

function void require_wav(Application_Links *app, Audio_Clip *clip, char *filename) {
    if (!audio_clip_is_valid(*clip) && !audio_clip_is_unloadable(*clip)) {
        FILE *file = def_search_normal_fopen(&global_custom_permanent_arena, filename, "rb");
        if (file != 0) {
            *clip = audio_clip_from_wav_FILE(&global_custom_permanent_arena, file);
            fclose(file);
        } else {
            clip->samples = (i16 *)0x00000001;
        }
    }
}

NAMESPACE_END()

#endif // FCODER_CUSTOM_AUDIO_CPP
