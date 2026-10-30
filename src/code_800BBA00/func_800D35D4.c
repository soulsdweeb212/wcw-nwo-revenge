/* @header
 * func_800D35D4
 * VRAM 0x800D35D4 | ROM 0xC6A74 | size 0x20
 * asm: asm/nonmatchings/code_800BBA00/func_800D35D4.s
 */
#include "common.h"

extern f64 D_800E6B70;

/* Convert an angle in 4096-unit turns to radians. */
f32 func_800D35D4(s32 arg0) {
    return (f32) ((f64) arg0 * D_800E6B70);
}
