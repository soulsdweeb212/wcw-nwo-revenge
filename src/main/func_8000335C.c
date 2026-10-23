#include "common.h"

s32 countAudioVoicesByKey();

/* Report whether any voice with key 0 is active. */
s32 func_8000335C(void) {
    return countAudioVoicesByKey() != 0;
}
