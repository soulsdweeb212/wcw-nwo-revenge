/* @header
 * func_800D37C0
 * VRAM 0x800D37C0 | ROM 0xC6C60 | size 0x78
 * asm: asm/nonmatchings/code_800BBA00/func_800D37C0.s
 */
#include "common.h"

f32 cosf(f32);
f32 sinf(f32);
extern f64 D_800E6B90;

/* Writes the XZ direction vector of length arg1 at angle arg0 (scaled by
 * D_800E6B90) into arg2. */
void func_800D37C0(s32 arg0, f32 arg1, void *arg2) {
    f32 temp_fs0;

    temp_fs0 = (f32) ((f64) arg0 * D_800E6B90);
    *(f32 *)((u8 *)arg2 + 0) = (f32) (arg1 * sinf(temp_fs0));
    *(f32 *)((u8 *)arg2 + 8) = (f32) (arg1 * cosf(temp_fs0));
}
