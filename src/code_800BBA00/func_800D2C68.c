/* @header
 * func_800D2C68
 * VRAM 0x800D2C68 | ROM 0xC6108 | size 0x44
 * asm: asm/nonmatchings/code_800BBA00/func_800D2C68.s
 */
#include "common.h"

s32 func_800D2CAC(void *, void *, void *, f32, void *, void *, void *, u16, s32, u16);
/* Boundary-correction wrapper (entity, linked entity, divisor, optional position
 * and attachment) with the apply flag set. */
s32 func_800D2C68(void *arg0, void *arg1, f32 arg2, void *arg3, s32 arg4) {
    return func_800D2CAC(arg0, arg1, NULL, arg2, NULL, arg3, NULL, 0, arg4, 1);
}
