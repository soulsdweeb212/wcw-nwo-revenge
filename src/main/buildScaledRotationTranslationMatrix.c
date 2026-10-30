/* @header
 * buildScaledRotationTranslationMatrix  (originally func_8001C1C0)
 * VRAM 0x8001C1C0 | ROM 0x1CDC0 | size 0x1D8
 * asm: asm/nonmatchings/main/buildScaledRotationTranslationMatrix.s
 */
#include "common.h"

/* Build a 4x4 row-major matrix: rotate by X/Y/Z Euler angles (in degrees,
 * scaled to radians by D_80037220), scale uniformly, and translate by
 * (tx,ty,tz). The three rotation sines/cosines are computed once and reused. */
f32 cosf(f32);
f32 sinf(f32);
extern f32 D_80037220;

void buildScaledRotationTranslationMatrix(f32 m[4][4], f32 x, f32 y, f32 z, f32 scale, f32 tx, f32 ty, f32 tz) {
    f32 sx, cx, sy, cy, sz, cz;
    x *= D_80037220;
    y *= D_80037220;
    z *= D_80037220;
    sx = sinf(x);
    cx = cosf(x);
    sy = sinf(y);
    cy = cosf(y);
    sz = sinf(z);
    cz = cosf(z);
    m[0][0] = cy * cz * scale;
    m[0][1] = cy * sz * scale;
    m[0][2] = -sy * scale;
    m[0][3] = 0.0f;
    m[1][0] = (sx * sy * cz - cx * sz) * scale;
    m[1][1] = (sx * sy * sz + cx * cz) * scale;
    m[1][2] = sx * cy * scale;
    m[1][3] = 0.0f;
    m[2][0] = (cx * sy * cz + sx * sz) * scale;
    m[2][1] = (cx * sy * sz - sx * cz) * scale;
    m[2][2] = cx * cy * scale;
    m[2][3] = 0.0f;
    m[3][0] = tx;
    m[3][1] = ty;
    m[3][2] = tz;
    m[3][3] = 1.0f;
}
