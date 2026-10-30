/* @header
 * func_800D3940
 * VRAM 0x800D3940 | ROM 0xC6DE0 | size 0x84
 * asm: asm/nonmatchings/code_800BBA00/func_800D3940.s
 */
#include "common.h"

f32 func_80003A3C(f32, f32);
f32 nw2Sqrtf(f32);
extern f64 D_800E6B98;
extern f64 D_800E6BA0;

typedef union { f32 f; s32 i; } NwFI;
typedef struct { NwFI e[4]; } NwV4;

/* Same XZ delta but returns only the heading as an s32 (using D_800E6BA0). */
s32 func_800D3940(void *arg0, void *arg1) {
    f32 *p0 = arg0;
    f32 *p1 = arg1;
    NwFI v[4];
    f32 dx;
    f32 dz;
    f32 dist;

    dx = p1[0] - p0[0];
    v[0].f = dx;
    dz = p1[2] - p0[2];
    v[2].f = dz;
    dist = nw2Sqrtf(dx * dx + dz * dz);
    v[1].f = dist;
    v[3].i = (s32)((f64)func_80003A3C(dx, dz) * D_800E6BA0);
    return v[3].i;
}
