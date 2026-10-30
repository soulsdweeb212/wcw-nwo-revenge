/* @header
 * func_8001BCD8
 * VRAM 0x8001BCD8 | ROM 0x1C8D8 | size 0x18C
 * asm: asm/nonmatchings/main/func_8001BCD8.s
 */
#include "common.h"

/* Builds a 4x4 rotation matrix for X/Y/Z Euler angles. The angles are scaled by
 * D_80037210 (degrees -> radians), the identity is written first, then the
 * upper-left 3x3 rotation, and the result is converted to the caller's buffer. */
f32 cosf(f32);
f32 sinf(f32);
extern f32 D_80037210;
void func_8001B090(void *, void *);
void initIdentityMatrix4x4(void *);

void func_8001BCD8(void *out, f32 angleX, f32 angleY, f32 angleZ) {
    f32 sx, cx, sy, cy, sz, cz;
    f32 m[4][4];
    void *mp = m;
    f32 rx = angleX * D_80037210;
    f32 ry = angleY * D_80037210;
    f32 rz = angleZ * D_80037210;

    sx = sinf(rx); cx = cosf(rx);
    sy = sinf(ry); cy = cosf(ry);
    sz = sinf(rz); cz = cosf(rz);
    initIdentityMatrix4x4(mp);
    m[0][0] = cy * cz;                m[0][1] = cy * sz;                m[0][2] = -sy;
    m[1][0] = sx * sy * cz - cx * sz; m[1][1] = sx * sy * sz + cx * cz; m[1][2] = sx * cy;
    m[2][0] = cx * sy * cz + sx * sz; m[2][1] = cx * sy * sz - sx * cz; m[2][2] = cx * cy;
    func_8001B090(mp, out);
}
