/* @header
 * func_8009A714
 * VRAM 0x8009A714 | ROM 0x8DBB4 | size 0x48
 * asm: asm/nonmatchings/ovl2_80090000/func_8009A714.s
 */
#include "common.h"

extern f32 D_800EB37C;
extern f32 D_800EB380;
extern f32 D_800EB384;
extern s32 D_800EB388;
extern f32 D_800EB38C;
extern f32 D_800EB390;

void func_8009A714(f32 arg0, f32 arg1, f32 arg2, s32 arg3, f32 arg4, f32 arg5) {
    D_800EB37C = arg0;
    D_800EB380 = arg1;
    D_800EB388 = arg3;
    D_800EB384 = -arg2;
    D_800EB38C = arg4;
    D_800EB390 = -arg5;
}
