/* @header
 * func_800D2670
 * VRAM 0x800D2670 | ROM 0xC5B10 | size 0x30
 * asm: asm/nonmatchings/code_800BBA00/func_800D2670.s
 */
#include "common.h"

s8 func_800D2758(s32, s32, s32, s32, s32);

/* Boundary correction with no records and a two-pass direction mask. */
s8 func_800D2670(s32 arg0, s32 arg1) {
    return func_800D2758(arg0, arg1, 0, -1, 2);
}
