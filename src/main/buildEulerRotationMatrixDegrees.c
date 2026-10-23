#include "common.h"

/*
 * Build a 4x4 rotation matrix `matrix` from Euler angles x/y/z given in
 * degrees (scaled by D_800307B0 = pi/180), applying Z*Y*X in that order.
 */
f32 cosf(f32);
f32 sinf(f32);
extern f32 D_800307B0;
void buildEulerRotationMatrixDegrees(f32 matrix[4][4], f32 x, f32 y, f32 z) {
 f32 sx, cx, sy, cy, sz, cz;
 x *= D_800307B0; y *= D_800307B0; z *= D_800307B0;
 sx = sinf(x); cx = cosf(x); sy = sinf(y); cy = cosf(y); sz = sinf(z); cz = cosf(z);
 matrix[0][0] = cz * cy;
 matrix[0][1] = sz * cx + cz * sy * sx;
 matrix[0][2] = sz * sx - cz * sy * cx;
 matrix[0][3] = 0;
 matrix[1][0] = -sz * cy;
 matrix[1][1] = cz * cx - sz * sy * sx;
 matrix[1][2] = cz * sx + sz * sy * cx;
 matrix[1][3] = 0;
 matrix[2][0] = sy; matrix[2][1] = -cy * sx; matrix[2][2] = cy * cx; matrix[2][3] = 0;
 matrix[3][0] = 0; matrix[3][1] = 0; matrix[3][2] = 0; matrix[3][3] = 1;
}
