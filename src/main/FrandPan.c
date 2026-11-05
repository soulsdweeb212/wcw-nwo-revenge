/* @header
 * FrandPan  (originally func_800168A4)
 * VRAM 0x800168A4 | ROM 0x174A4 | size 0x50
 * asm: asm/nonmatchings/main/FrandPan.s
 */
/* SDK: libmus, libmus/src/playerinc/player_commands.inc.c (same code as the SDK source). */
#include "common.h"

s8 __MusIntRandom(u8);

/* Parses an envelope level: seeds +0xDD from a random byte and adds the next. */
u8 *FrandPan(u8 *arg0, u8 *arg1) {
    s8 v = __MusIntRandom(*arg1++);
    *(s8 *)(arg0 + 0xDD) = v;
    v += *arg1++;
    *(s8 *)(arg0 + 0xDD) = v;
    return arg1;
}

extern f64 D_8003B3F0;
