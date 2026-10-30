/* @header
 * func_800D3E40
 * VRAM 0x800D3E40 | ROM 0xC72E0 | size 0xAC
 * asm: asm/nonmatchings/code_800BBA00/func_800D3E40.s
 */
#include "common.h"

f32 cosf(f32); f32 sinf(f32); extern f64 D_800E6BD0;
/* Rotates the XZ point arg1 around arg0 by arg2 (scaled by D_800E6BD0) into arg3. */
void func_800D3E40(f32 *arg0, f32 *arg1, s32 arg2, f32 *arg3) {
    f32 angle, c, s, x, z;
    angle = (f32)((f64)arg2 * D_800E6BD0);
    c = cosf(angle);
    s = sinf(angle);
    x = arg1[0];
    z = arg1[2];
    arg3[0] = arg0[0] + (x * c + z * s);
    x = x * s;
    arg3[2] = arg0[2] + (z * c - x);
}
