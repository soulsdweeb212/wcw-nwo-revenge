/* @header
 * __MusIntFlushPending  (originally func_80014D78)
 * VRAM 0x80014D78 | ROM 0x15978 | size 0x7C
 * asm: asm/nonmatchings/main/__MusIntFlushPending.s
 */
/* SDK: libmus, libmus/src/player.c (same code as the SDK source). */
#include "common.h"

void n_alSynStartVoice(s32, s32);
void n_alSynStopVoice(s32);
extern s32 mus_voices;

/* Resets the audio voice's link: if it was already linked, sends command 15,
 * then sends command 14 with the voice's +8 value and clears that value. */
void __MusIntFlushPending(void *arg0, s32 arg1) {
    if (*(u8 *)((u8 *)arg0 + 0xE9) != 0) {
        n_alSynStopVoice(mus_voices + (arg1 * 0x1C));
    }
    *(u8 *)((u8 *)arg0 + 0xE9) = 1U;
    n_alSynStartVoice(mus_voices + (arg1 * 0x1C), *(s32 *)((u8 *)arg0 + 8));
    *(s32 *)((u8 *)arg0 + 8) = 0;
}
