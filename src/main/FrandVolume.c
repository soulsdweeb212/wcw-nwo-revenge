/* @header
 * FrandVolume  (originally func_80016854)
 * VRAM 0x80016854 | ROM 0x17454 | size 0x50
 * asm: asm/nonmatchings/main/FrandVolume.s
 */
/* SDK: libmus, libmus/src/playerinc/player_commands.inc.c (same code as the SDK source). */
#include "common.h"

s8 __MusIntRandom(u8);

/* Decode a signed byte into arg0+0xDC, then add the next byte to it. */
u8 *FrandVolume(u8 *arg0, u8 *arg1) {
    s8 v = __MusIntRandom(*arg1++);
    *(s8 *)(arg0 + 0xDC) = v;
    v += *arg1++;
    *(s8 *)(arg0 + 0xDC) = v;
    return arg1;
}

extern f64 D_8003B3F0;
