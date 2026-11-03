/* @header
 * func_800B83D0
 * VRAM 0x800B83D0 | ROM 0x64B40 | size 0x510
 * asm: asm/nonmatchings/code_80090000/func_800B83D0.s
 */
#include "common.h"

extern f32 D_800DC890[6];
extern f32 D_800DC8A8[6];
extern f32 D_800DC8C0[6];
extern s32 D_800E79CC, D_800D28F0;
extern f64 D_800D6790, D_800D6798, D_800D67A0;
void buildScaledRotationTranslationMatrix(void *, f32, f32, f32, f32, f32, f32, f32);
void func_8001B3EC(void *, f32, f32, f32, f32 *, f32 *, f32 *);
f32 nw2Sqrtf(f32);
s32 func_800B5E18(s32, s32);
void setupTiltedPerspectiveCamera(s32, f32, f32, f32, f32, f32, f32, f32);
void setCameraView(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32);

void func_800B83D0(s32 id) {
    f32 m[16];
    f32 px, py, pz, qx, qy, qz;
    f32 x, y, z, a, b, f;

    buildScaledRotationTranslationMatrix(m, D_800DC890[3], D_800DC890[4], D_800DC890[5], 1.0f, D_800DC890[0], D_800DC890[1], D_800DC890[2]);
    func_8001B3EC(m, 0.0f, 0.0f, 0.0f, &D_800DC8A8[0], &D_800DC8A8[1], &D_800DC8A8[2]);
    if (D_800E79CC != 0) {
        func_8001B3EC(m, 0.0f, 0.0f, 500.0f, &px, &py, &pz);
        x = D_800DC8C0[3] - D_800DC890[0];
        z = D_800DC8C0[5] - D_800DC890[2];
        y = D_800DC8C0[4] - D_800DC890[1];
        a = func_800B5E18(y, nw2Sqrtf(x * x + z * z)) * D_800D6790;
        b = func_800B5E18(x, z) * D_800D6798;
        x = D_800DC8C0[0] - a;
        y = D_800DC8C0[1] - b;
        if (x < -180.0f) {
            x += 360.0f;
        }
        if (x > 180.0f) {
            x -= 360.0f;
        }
        if (y < -180.0f) {
            y += 360.0f;
        }
        if (y > 180.0f) {
            y -= 360.0f;
        }
        if (x < -1.0f) {
            D_800DC8C0[0] = a - 1.0f;
        }
        if (x > 1.0f) {
            D_800DC8C0[0] = a + 1.0f;
        }
        if (y < -1.0f) {
            D_800DC8C0[1] = b - 1.0f;
        }
        if (y > 1.0f) {
            D_800DC8C0[1] = b + 1.0f;
        }
        D_800DC8C0[2] = 0.0f;
        buildScaledRotationTranslationMatrix(m, D_800DC8C0[0], D_800DC8C0[1], D_800DC8C0[2], 1.0f, D_800DC8A8[0], D_800DC8A8[1], D_800DC8A8[2]);
        func_8001B3EC(m, 0.0f, 0.0f, 500.0f, &qx, &qy, &qz);
        f = D_800E79CC;
        D_800DC8A8[3] = px + (qx - px) * f * (1.0f / 256.0f);
        D_800DC8A8[4] = py + (qy - py) * f * (1.0f / 256.0f);
        D_800DC8A8[5] = pz + (qz - pz) * f * (1.0f / 256.0f);
    } else {
        func_8001B3EC(m, 0.0f, 0.0f, 500.0f, &D_800DC8A8[3], &D_800DC8A8[4], &D_800DC8A8[5]);
    }
    if (D_800D28F0 == 0x21) {
        setupTiltedPerspectiveCamera(id, D_800DC890[5] * D_800D67A0, D_800DC8A8[0], D_800DC8A8[1], D_800DC8A8[2], D_800DC8A8[3], D_800DC8A8[4], D_800DC8A8[5]);
    } else {
        setCameraView(id, D_800D28F0, 4.0f / 3.0f, 100.0f, 4000.0f, 1.0f, D_800DC8A8[0], D_800DC8A8[1], D_800DC8A8[2], D_800DC8A8[3], D_800DC8A8[4], D_800DC8A8[5]);
    }
}
