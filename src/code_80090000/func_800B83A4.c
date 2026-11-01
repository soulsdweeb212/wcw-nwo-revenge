/* @header
 * func_800B83A4
 * VRAM 0x800B83A4 | ROM 0x64B14 | size 0x2C
 * asm: asm/nonmatchings/code_80090000/func_800B83A4.s
 */
#include "common.h"

extern f32 D_800DC8CC;
extern f32 D_800DC8D0;
extern s32 D_800DC8D4;
extern s32 D_800DC8E4;

void func_800B83A4(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
    D_800DC8CC = arg0;
    D_800DC8D0 = arg1;
    D_800DC8D4 = arg2;
    if (arg3 != 0) {
        D_800DC8E4 = 0;
    }
}
