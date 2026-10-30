/* @header
 * func_800D39C4
 * VRAM 0x800D39C4 | ROM 0xC6E64 | size 0xB0
 * asm: asm/nonmatchings/code_800BBA00/func_800D39C4.s
 */
#include "common.h"

typedef union { f32 f; s32 i; } NwFI;
typedef struct { NwFI e[4]; } NwV4;

f32 nw2Sqrtf(f32);
f32 func_80003A3C(f32, f32);

extern f64 D_800E6BA8;

/* Compute the 2D offset between arg0 and arg1, then pack dx, dy, the distance
 * and the heading (func_80003A3C scaled by D_800E6BA8) into a 4-element vector,
 * storing it via arg2 when non-NULL. Returns the distance. */
f32 func_800D39C4(void *arg0, void *arg1, void *arg2) {
    f32 *p0 = arg0, *p1 = arg1;
    NwFI v[4];
    f32 dx, dy, dist;

    dx = p1[0] - p0[0]; v[0].f = dx;
    dy = p1[1] - p0[1]; v[1].f = dy;
    dist = nw2Sqrtf(dx * dx + dy * dy); v[2].f = dist;
    v[3].i = (s32)((f64)func_80003A3C(dx, dy) * D_800E6BA8);
    if (arg2 != NULL) *(NwV4 *)arg2 = *(NwV4 *)v;
    return v[2].f;
}
