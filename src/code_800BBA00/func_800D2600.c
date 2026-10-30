/* @header
 * func_800D2600
 * VRAM 0x800D2600 | ROM 0xC5AA0 | size 0x38
 * asm: asm/nonmatchings/code_800BBA00/func_800D2600.s
 */
#include "common.h"

s8 func_800D2758(s32, s32, s32, s32, s32);

/* Boundary/position wrapper taking the mode in arg1: (entity, value, 0, mode, 1). */
s8 func_800D2600(s32 arg0, s8 arg1, s32 arg2) {
    return func_800D2758(arg0, arg2, 0, arg1, 1);
}
