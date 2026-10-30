/* @header
 * func_800D7A2C
 * VRAM 0x800D7A2C | ROM 0xCAECC | size 0x3C
 * asm: asm/nonmatchings/code_800BBA00/func_800D7A2C.s
 */
#include "common.h"

/* Map a reaction bitmask to a 0..3 category, or -1. */
s32 func_800D7A2C(s32 arg0) {
    if (arg0 & 0x800) {
        return 0;
    }
    if (arg0 & 0x100) {
        return 1;
    }
    if (arg0 & 0x400) {
        return 2;
    }
    return (arg0 & 0x200) ? 3 : -1;
}

s16 func_800D7690(void *, s32, s32);
s32 func_800D4198(s32);
