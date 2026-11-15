/* @header
 * func_800B8368
 * VRAM 0x800B8368 | ROM 0x64AD8 | size 0x3C
 * asm: asm/nonmatchings/code_80090000/func_800B8368.s
 */
#include "common.h"

extern f32 D_800DC890;
extern f32 D_800DC894;
#ifdef TARGET_PC
/* PC: D_800DC898 and D_800DC89C are elements 2 and 3 of the camera's six floats D_800DC890 (func_800B82B8 and
 * func_800B83D0 read them as f32). */
extern f32 D_800DC898;
extern f32 D_800DC89C;
#else
extern s32 D_800DC898;
extern s32 D_800DC89C;
#endif
extern f32 D_800DC8A0;
extern f32 D_800DC8A4;

#ifdef TARGET_PC
/* PC: all six arguments are floats: the callers (func_800B7C9C, func_800B7F3C) pass six f32. On the N64 the third and
 * fourth travel as their bits in a2 and a3, which this function stores as they are; on PC floats travel in registers
 * of their own, so the PC definition takes them as f32. */
void func_800B8368(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
#else
void func_800B8368(f32 arg0, f32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5) {
#endif
    D_800DC890 = arg0;
    D_800DC894 = arg1;
    D_800DC898 = arg2;
    D_800DC89C = arg3;
    D_800DC8A0 = arg4;
    D_800DC8A4 = arg5;
}
