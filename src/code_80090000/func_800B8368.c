/* @header
 * func_800B8368
 * VRAM 0x800B8368 | ROM 0x64AD8 | size 0x3C
 * asm: asm/nonmatchings/code_80090000/func_800B8368.s
 */
#include "common.h"

extern f32 D_800DC890;
extern f32 D_800DC894;
extern s32 D_800DC898;
extern s32 D_800DC89C;
extern f32 D_800DC8A0;
extern f32 D_800DC8A4;

void func_800B8368(f32 arg0, f32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5) {
    D_800DC890 = arg0;
    D_800DC894 = arg1;
    D_800DC898 = arg2;
    D_800DC89C = arg3;
    D_800DC8A0 = arg4;
    D_800DC8A4 = arg5;
}
