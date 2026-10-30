/* @header
 * func_800D3B24
 * VRAM 0x800D3B24 | ROM 0xC6FC4 | size 0xD4
 * asm: asm/nonmatchings/code_800BBA00/func_800D3B24.s
 */
#include "common.h"

typedef union { f32 f; s32 i; } NwFI;
typedef struct { NwFI e[4]; } NwV4;
f32 nw2Sqrtf(f32);
f32 func_80003A3C(f32, f32);
extern f64 D_800E6BB8;

s32 func_800D3B24(void *arg0, void *arg1, f32 arg2, void *arg3) {
    f32 *p0 = arg0, *p1 = arg1;
    NwFI v[4];
    f32 x, z, dist;

    x = p1[0] - p0[0]; v[0].f = x;
    z = p1[2] - p0[2]; v[2].f = z;
    dist = nw2Sqrtf(x * x + z * z); v[1].f = dist;
    v[3].i = (s32)((f64)func_80003A3C(x, z) * D_800E6BB8);
    if (arg3 != NULL) *(NwV4 *)arg3 = *(NwV4 *)v;
    return (v[1].f <= arg2) ? 1 : 0;
}
