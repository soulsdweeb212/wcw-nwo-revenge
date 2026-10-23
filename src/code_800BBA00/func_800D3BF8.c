#include "common.h"

typedef union { f32 f; s32 i; } NwFI;
typedef struct { NwFI e[4]; } NwV4;

f32 nw2Sqrtf(f32);
f32 func_80003A3C(f32, f32);
extern f64 D_800E6BC0;

s32 func_800D3BF8(void *arg0, void *arg1, f32 arg2, void *arg3) {
    f32 *p0 = arg0, *p1 = arg1;
    NwFI v[4];
    f32 dx, dy, dist;

    dx = p1[0] - p0[0]; v[0].f = dx;
    dy = p1[1] - p0[1]; v[1].f = dy;
    dist = nw2Sqrtf(dx * dx + dy * dy); v[2].f = dist;
    v[3].i = (s32)((f64)func_80003A3C(dx, dy) * D_800E6BC0);
    if (arg3 != NULL) *(NwV4 *)arg3 = *(NwV4 *)v;
    return v[2].f <= arg2;
}
