#include "common.h"

/* Compute a representative point for an entity from its sample ring. Using the
 * record selected by D_800F99A0[*arg0] (stride 0x5C) it walks the point list
 * at D_8007E03C (count D_8007E011[base], 12 bytes/point), tracks the nearest
 * and farthest point by distance from the entity's +0x6C origin, and blends
 * them by D_800E7780 into arg1[0] (x), arg1[2] (z) and arg1[1] (span distance
 * between the two extremes). */
extern vu8 D_800F99A0[];
extern s8 D_8007E011[];
extern u8 D_8007E03C[];
extern f64 D_800E7780;
f32 func_800D3890(void *, void *, s32);

void func_800E2230(s8 *arg0, f32 *arg1) {
    f32 pmin[3];
    f32 pmax[3];
    f32 vec[3];
    s16 base;
    s16 i;
    f32 d;
    f64 c;

    base = (s8)D_800F99A0[*arg0] * 0x5C;
    pmin[1] = 1000.0f;
    pmax[1] = 0.0f;
    for (i = 0; i < D_8007E011[base]; i++) {
        s32 off = i * 12 + base;
        vec[0] = -*(f32 *)((u8 *)D_8007E03C + off);
        vec[2] = *(f32 *)((u8 *)D_8007E03C + off + 8);
        d = func_800D3890(arg0 + 0x6C, vec, 0);
        if (d < pmin[1]) {
            pmin[1] = d;
            pmin[0] = vec[0];
            pmin[2] = vec[2];
        }
        if (pmax[1] < d) {
            pmax[1] = d;
            pmax[0] = vec[0];
            pmax[2] = vec[2];
        }
    }
    c = D_800E7780;
    arg1[0] = (f32)((f64)pmin[0] + (f64)(pmax[0] - pmin[0]) * c);
    arg1[2] = (f32)((f64)pmin[2] + (f64)(pmax[2] - pmin[2]) * c);
    arg1[1] = (f32)((f64)func_800D3890(pmin, pmax, 0) * c);
}
