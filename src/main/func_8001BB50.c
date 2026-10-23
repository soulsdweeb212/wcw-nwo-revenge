#include "common.h"

/* Builds a 4x4 X/Y/Z Euler rotation matrix in the caller's buffer. The angles
 * are converted from degrees to radians using D_80037210, and the identity is
 * written before the upper-left 3x3 rotation. */
f32 cosf(f32);
f32 sinf(f32);
void initIdentityMatrix4x4(void *);
extern f32 D_80037210;

void func_8001BB50(f32 m[4][4], f32 x, f32 y, f32 z) {
    f32 sx, cx, sy, cy, sz, cz;
    x *= D_80037210;
    y *= D_80037210;
    z *= D_80037210;
    sx = sinf(x);
    cx = cosf(x);
    sy = sinf(y);
    cy = cosf(y);
    sz = sinf(z);
    cz = cosf(z);
    initIdentityMatrix4x4(m);
    m[0][0] = cy * cz;
    m[0][1] = cy * sz;
    m[0][2] = -sy;
    m[1][0] = sx * sy * cz - cx * sz;
    m[1][1] = sx * sy * sz + cx * cz;
    m[1][2] = sx * cy;
    m[2][0] = cx * sy * cz + sx * sz;
    m[2][1] = cx * sy * sz - sx * cz;
    m[2][2] = cx * cy;
}
