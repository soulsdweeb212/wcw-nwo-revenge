/* @header
 * guRandom  (originally func_8001C580)
 * VRAM 0x8001C580 | ROM 0x1D180 | size 0x2C
 * asm: asm/nonmatchings/main/guRandom.s
 */
/* SDK: libultra 2.0I, ultralib src/gu/random.c (same code as the SDK source). */
#include "common.h"

extern u32 xseed;

/* Advance the pseudo-random sequence and return the new value. */
u32 guRandom(void) {
    s32 t = xseed * 4;
    return xseed = (u32)((t + 2) * (t + 3)) >> 2;
}
