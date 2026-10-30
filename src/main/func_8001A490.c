/* @header
 * func_8001A490
 * VRAM 0x8001A490 | ROM 0x1B090 | size 0x1CC
 * asm: asm/nonmatchings/main/func_8001A490.s
 */
#include "common.h"

f32 cosf(f32); f32 sinf(f32); f32 sqrtf(f32);
void func_8001B4A0(f32 *, f32 *, f32 *);
extern f32 D_80037200;
#define dtor D_80037200

void func_8001A490(f32 mf[4][4], f32 a, f32 x, f32 y, f32 z)
{
    f32 s, c, h, invh;

    func_8001B4A0(&x, &y, &z);

    a *= dtor;
    s = sinf(a);
    c = cosf(a);

    h = sqrtf(x * x + z * z);

    initIdentityMatrix4x4(mf);

    if (h != 0.0f) {
        invh = 1.0f / h;

        mf[0][0] = (-z * c - s * y * x) * invh;
        mf[1][0] = (z * s - c * y * x) * invh;
        mf[3][0] = 0.0f;
        mf[2][0] = -x;

        mf[0][1] = s * h;
        mf[1][1] = c * h;
        mf[3][1] = 0.0f;
        mf[2][1] = -y;

        mf[0][2] = (c * x - s * y * z) * invh;
        mf[2][2] = -z;
        mf[3][2] = 0.0f;
        mf[1][2] = (-s * x - c * y * z) * invh;

        mf[0][3] = 0.0f;
        mf[1][3] = 0.0f;
        mf[2][3] = 0.0f;
        mf[3][3] = 1.0f;
    }
}
