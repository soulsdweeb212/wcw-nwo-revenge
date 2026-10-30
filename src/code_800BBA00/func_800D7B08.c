/* @header
 * func_800D7B08
 * VRAM 0x800D7B08 | ROM 0xCAFA8 | size 0x4C
 * asm: asm/nonmatchings/code_800BBA00/func_800D7B08.s
 */
#include "common.h"

s16 func_800D7690(void *, s32, s32);
s32 func_800D4198(s32);

/* Map the 0xF00 field of arg0 to a 0..3 category, or -1. */
s32 func_800D7B08(s32 arg0) {
    s32 t = arg0 & 0xF00;

    if (t == 0x900) {
        return 0;
    }
    if (t == 0x500) {
        return 1;
    }
    if (t == 0x600) {
        return 2;
    }
    return (t == 0xA00) ? 3 : -1;
}
