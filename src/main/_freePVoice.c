/* @header
 * _freePVoice  (originally func_80020854)
 * VRAM 0x80020854 | ROM 0x21454 | size 0x40
 * asm: asm/nonmatchings/main/_freePVoice.s
 */
/* SDK: libultra 2.0I, ultralib src/audio/synthesizer.c (same code as the SDK source). */
#include "common.h"

s32 alLink(s32, s32);
s32 alUnlink(s32);

/* Detach node arg1 and append it to the list at arg0+0x14. */
void _freePVoice(s32 arg0, s32 arg1) {
    alUnlink(arg1);
    alLink(arg1, arg0 + 0x14);
}
