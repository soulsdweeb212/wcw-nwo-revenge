#include "common.h"

extern f32 D_80048288[4][4];
static inline f32 proj_80001CA0(f32 *v) {
    f32 x, z;
    x = D_80048288[0][0]*v[0] + D_80048288[1][0]*v[1] + D_80048288[2][0]*v[2] + D_80048288[3][0];
    z = D_80048288[0][2]*v[0] + D_80048288[1][2]*v[1] + D_80048288[2][2]*v[2] + D_80048288[3][2];
    z += 1000.0f;
    return x / z;
}
s32 func_80001CA0(f32 *a, f32 *b) {
    if (proj_80001CA0(a) < proj_80001CA0(b)) return 1;
    return 0;
}
