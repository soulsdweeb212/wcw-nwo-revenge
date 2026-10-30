/* @header
 * func_800D36B4
 * VRAM 0x800D36B4 | ROM 0xC6B54 | size 0x34
 * asm: asm/nonmatchings/code_800BBA00/func_800D36B4.s
 */
#include "common.h"

/* Writes the XYZ delta (arg1 - arg0) into arg2. */
void func_800D36B4(void *arg0, void *arg1, void *arg2) {
    *(f32 *)((u8 *)arg2 + 0) = (f32) (*(f32 *)((u8 *)arg1 + 0) - *(f32 *)((u8 *)arg0 + 0));
    *(f32 *)((u8 *)arg2 + 8) = (f32) (*(f32 *)((u8 *)arg1 + 8) - *(f32 *)((u8 *)arg0 + 8));
    *(f32 *)((u8 *)arg2 + 4) = (f32) (*(f32 *)((u8 *)arg1 + 4) - *(f32 *)((u8 *)arg0 + 4));
}
