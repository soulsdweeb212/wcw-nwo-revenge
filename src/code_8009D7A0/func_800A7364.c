/* @header
 * func_800A7364
 * VRAM 0x800A7364 | ROM 0x9A804 | size 0xB4
 * asm: asm/nonmatchings/code_8009D7A0/func_800A7364.s
 */
#include "common.h"

/* Copies the entity's X/Z (from +0x6C/+0x74) to +0x4C/+0x54, then clamps the
 * facing-quadrant (+0x3C) axis to the ring edge (+/-265). */
void func_800A7364(u8 *arg0) {
    f32 a = *(f32 *)(arg0 + 0x6C);
    f32 b = *(f32 *)(arg0 + 0x74);
    s32 t = *(s16 *)(arg0 + 0x3C);

    *(f32 *)(arg0 + 0x4C) = a;
    *(f32 *)(arg0 + 0x54) = b;
    switch (t) {
    case 0:
        *(f32 *)(arg0 + 0x54) = 265.0f;
        break;
    case 1:
        *(f32 *)(arg0 + 0x4C) = 265.0f;
        break;
    case 2:
        *(f32 *)(arg0 + 0x54) = -265.0f;
        break;
    case 3:
        *(f32 *)(arg0 + 0x4C) = -265.0f;
        break;
    }
}

s32 func_800D3550(s32);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
