#include "common.h"

f32 func_80003A3C(f32, f32);
f32 nw2Sqrtf(f32);
extern f64 D_800E6B98;
extern f64 D_800E6BA0;

s32 func_800D3590(s32 arg0) {
    s32 v = arg0 & 0xFFF;
    s32 t = v & 0x800;

    if (t) {
        v |= 0xFFFFF000;
    }
    return v;
}

/* Evaluate sqrt(x*x + y*y); the result is not consumed here. */
void func_800D371C(f32 x, f32 y) {
    nw2Sqrtf(x * x + y * y);
}

f32 func_800D3890(void *arg0, void *arg1, void *arg2) {
    f32 *p0 = arg0;
    f32 *p1 = arg1;
    f32 dx;
    f32 dist;
    f32 dz;
    s32 ang;

    dx = p1[0] - p0[0];
    dz = p1[2] - p0[2];
    dist = nw2Sqrtf(dx * dx + dz * dz);
    ang = (s32)((f64)func_80003A3C(dx, dz) * D_800E6B98);
    if (arg2 != NULL) {
        ((s32 *)arg2)[0] = *(s32 *)&dx;
        ((s32 *)arg2)[1] = *(s32 *)&dist;
        ((s32 *)arg2)[2] = *(s32 *)&dz;
        ((s32 *)arg2)[3] = ang;
    }
    return dist;
}

void func_800D3940(void *arg0, void *arg1) {
    f32 *p0 = arg0;
    f32 *p1 = arg1;
    f32 dx;
    f32 dist;
    f32 dz;
    s32 ang;

    dx = p1[0] - p0[0];
    dz = p1[2] - p0[2];
    dist = nw2Sqrtf(dx * dx + dz * dz);
    ang = (s32)((f64)func_80003A3C(dx, dz) * D_800E6BA0);
}
