/* @header
 * func_800D3590
 * VRAM 0x800D3590 | ROM 0xC6A30 | size 0x20
 * asm: asm/nonmatchings/code_800BBA00/func_800D3590.s
 */
#include "common.h"

f32 func_80003A3C(f32, f32);
f32 nw2Sqrtf(f32);
extern f64 D_800E6B98;
extern f64 D_800E6BA0;

typedef union { f32 f; s32 i; } NwFI;

/* Wrap angle arg0 to [-0x800, 0x800]. */
s32 func_800D3590(s32 arg0) {
    s32 t;

    arg0 &= 0xFFF;
    t = arg0 & 0x800;
    if (t) {
        arg0 |= 0xFFFFF000;
    }
    return arg0;
}
