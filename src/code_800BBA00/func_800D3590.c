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

/* XZ-plane distance and heading between arg0 and arg1; optionally write
 * {dx,dist,dz,angle} to arg2 and return the distance. */
f32 func_800D3890(void *arg0, void *arg1, void *arg2) {
    f32 *p0 = arg0;
    f32 *p1 = arg1;
    NwFI v[4];
    f32 dx;
    f32 dz;
    f32 dist;

    dx = p1[0] - p0[0];
    dz = p1[2] - p0[2];
    v[0].f = dx;
    v[2].f = dz;
    dist = nw2Sqrtf(dx * dx + dz * dz);
    v[1].f = dist;
    v[3].i = (s32)((f64)func_80003A3C(dx, dz) * D_800E6B98);
    if (arg2 != NULL) {
        ((s32 *)arg2)[0] = v[0].i;
        ((s32 *)arg2)[1] = v[1].i;
        ((s32 *)arg2)[2] = v[2].i;
        ((s32 *)arg2)[3] = v[3].i;
    }
    return dist;
}

/* As func_800D3890, returning only the heading angle. */
s32 func_800D3940(void *arg0, void *arg1) {
    f32 *p0 = arg0;
    f32 *p1 = arg1;
    NwFI v[4];
    f32 dx;
    f32 dz;
    f32 dist;

    dx = p1[0] - p0[0];
    dz = p1[2] - p0[2];
    v[0].f = dx;
    v[2].f = dz;
    dist = nw2Sqrtf(dx * dx + dz * dz);
    v[1].f = dist;
    v[3].i = (s32)((f64)func_80003A3C(dx, dz) * D_800E6BA0);
    return v[3].i;
}
