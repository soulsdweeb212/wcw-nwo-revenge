/* @header
 * func_8000335C
 * VRAM 0x8000335C | ROM 0x3F5C | size 0x20
 * asm: asm/nonmatchings/main/func_8000335C.s
 */
#include "common.h"

s32 countAudioVoicesByKey();

/* Report whether any voice with key 0 is active. */
s32 func_8000335C(void) {
    return countAudioVoicesByKey() != 0;
}
