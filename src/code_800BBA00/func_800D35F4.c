/* @header
 * func_800D35F4
 * VRAM 0x800D35F4 | ROM 0xC6A94 | size 0x20
 * asm: asm/nonmatchings/code_800BBA00/func_800D35F4.s
 */
#include "common.h"

extern f64 D_800E6B78;

/* Convert radians arg0 to a 4096-unit-turn angle. */
s32 func_800D35F4(f32 arg0) {
    return (s32) ((f64) arg0 * D_800E6B78);
}
