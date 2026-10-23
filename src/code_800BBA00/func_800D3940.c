#include "common.h"

f32 func_80003A3C(f32, f32);
f32 nw2Sqrtf(f32);
extern f64 D_800E6B98;
extern f64 D_800E6BA0;

typedef union { f32 f; s32 i; } NwFI;
typedef struct { NwFI e[4]; } NwV4;

/* Computes the XZ delta between arg0 and arg1: stores dx, the distance and dz
 * into a 4-word result, converts the heading to 16.16 fixed point and copies the
 * result to arg2 when given. Returns the distance. */
f32 func_800D3890(void *arg0, void *arg1, void *arg2) {
    f32 *p0 = arg0;
    f32 *p1 = arg1;
    NwFI v[4];
    f32 dz;
    f32 dx;
    f32 dist;

    dx = p1[0] - p0[0];
    v[0].f = dx;
    dz = p1[2] - p0[2];
    v[2].f = dz;
    dist = nw2Sqrtf(dx * dx + dz * dz);
    v[1].f = dist;
    v[3].i = (s32)((f64)func_80003A3C(dx, dz) * D_800E6B98);
    if (arg2 != NULL) {
        *(NwV4 *)arg2 = *(NwV4 *)v;
    }
    return v[1].f;
}

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
