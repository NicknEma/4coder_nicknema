#ifndef FCODER_CUSTOM_AUDIO_H
#define FCODER_CUSTOM_AUDIO_H

function b32 F4_AudioClipIsValid(Audio_Clip clip);
function b32 F4_AudioClipIsUnloadable(Audio_Clip clip);
function void F4_RequireWAV(Application_Links *app, Audio_Clip *clip, char *filename);

#endif // FCODER_CUSTOM_AUDIO_H
