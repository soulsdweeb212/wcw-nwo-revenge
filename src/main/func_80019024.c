/* @header
 * func_80019024
 * VRAM 0x80019024 | ROM 0x19C24 | size 0x48
 * asm: asm/nonmatchings/main/func_80019024.s
 */
#include "common.h"

/* Interpolate arg0 toward a target: arg1 is a 1/8-unit step, arg2 a signed offset
 * and arg3 a 16.16 fraction; returns the result truncated to s16. */
s32 func_80019024(s32 arg0, s32 arg1, s16 arg2, s32 arg3) {
    s32 step;
    s32 r;

    step = arg1 >> 3;
    if (step != 0) {
        r = (arg0 + (((s32) ((arg3 & 0xFFFF) * step) >> 0x10) + (arg2 * step))) << 0x10;
    } else {
        r = arg0 << 0x10;
    }
    return r >> 0x10;
}
