/* @header
 * func_800D36E8
 * VRAM 0x800D36E8 | ROM 0xC6B88 | size 0x34
 * asm: asm/nonmatchings/code_800BBA00/func_800D36E8.s
 */
/* @header
 * func_800D371C
 * VRAM 0x800D371C | ROM 0xC6BBC | size 0x28
 * asm: asm/nonmatchings/code_800BBA00/func_800D371C.s
 */
/* @header
 * func_800D3744
 * VRAM 0x800D3744 | ROM 0xC6BE4 | size 0x7C
 * asm: asm/nonmatchings/code_800BBA00/func_800D3744.s
 */
#include "common.h"

/* func_800D36E8, func_800D371C and func_800D3744 are one translation unit: compiled apart, the assembler cannot see
 * the instruction before func_800D371C and pads its first mul.s with a nop that the ROM does not have. A source that
 * holds several consecutive functions is placed once, at the address of the first (build.json names the same "c"
 * for each). */
f32 func_80003A3C(f32, f32);
f32 nw2Sqrtf(f32);
extern f64 D_800E6B80;
extern f64 D_800E6B88;

/* Convert the atan2-style result of func_80003A3C into a 4096-unit heading. */
s32 func_800D36E8(void) {
    return (s32) ((f64) ((f32 (*)(void)) func_80003A3C)() * D_800E6B80);
}

/* Evaluate sqrt(x*x + y*y); the result is not consumed here. */
f32 func_800D371C(f32 x, f32 y) {
    return nw2Sqrtf(x * x + y * y);
}

/* Computes the length of the 2D vector (arg0,arg1) into *arg2 and its heading
 * (16.16 fixed point) into *arg3. */
void func_800D3744(f32 arg0, f32 arg1, f32 *arg2, s32 *arg3) {
    *arg2 = nw2Sqrtf((arg0 * arg0) + (arg1 * arg1));
    *arg3 = (s32) ((f64) func_80003A3C(arg0, arg1) * D_800E6B88);
}
