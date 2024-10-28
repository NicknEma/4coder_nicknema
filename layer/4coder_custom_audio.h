#ifndef FCODER_CUSTOM_AUDIO_H
#define FCODER_CUSTOM_AUDIO_H

NAMESPACE_BEGIN(nne)

function b32 audio_clip_is_valid(Audio_Clip clip);
function b32 audio_clip_is_unloadable(Audio_Clip clip);
function void require_wav(Application_Links *app, Audio_Clip *clip, char *filename);

NAMESPACE_END()

#endif // FCODER_CUSTOM_AUDIO_H
