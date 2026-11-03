/* @header
 * func_800BB6E8
 * VRAM 0x800BB6E8 | ROM 0x67E58 | size 0x2AC
 * asm: asm/nonmatchings/code_80090000/func_800BB6E8.s
 */
#include "common.h"

extern f32 D_800DF1F0, D_800DF1F4, D_800DF1F8;
extern s32 D_800DF200, D_800E79CC;
void buildScaledRotationTranslationMatrix(void *, f32, f32, f32, f32, f32, f32, f32);
void func_8001B3EC(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_800B82B8(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
void func_800B83A4(f32, f32, f32, s32);
void func_800C2CDC_ovl1(s32, f32 *);

void func_800BB6E8(s32 a) {
    f32 p[4], q[4];
    f32 m[16];
    f32 x, y, z, rx, ry, rz;
    f32 t;
    if (a & 1) {
        func_800B82B8(&x, &y, &z, &rx, &ry, &rz);
        buildScaledRotationTranslationMatrix(m, x, y, z, 1.0f, rx, ry, rz);
        func_8001B3EC(m, 0.0f, 0.0f, 500.0f, &x, &y, &z);
        D_800DF200 = 0;
    } else {
        if (a & 4) {
            func_800C2CDC_ovl1(4, p);
            func_800C2CDC_ovl1(5, q);
        } else {
            func_800C2CDC_ovl1(0, p);
            func_800C2CDC_ovl1(1, q);
        }
        if (a & 2) {
            z = (p[2] + q[2]) * 0.5f;
            y = (p[1] + q[1]) * 0.5f;
            x = -(p[0] + q[0]) * 0.5f;
        } else if (a & 8) {
            z = q[2];
            y = q[1];
            x = -q[0];
        } else {
            z = p[2];
            y = p[1];
            x = -p[0];
        }
    }
    if (D_800DF200 == 0) {
        D_800DF1F0 = x;
        D_800DF1F4 = y;
        D_800DF1F8 = z;
    } else {
        t = D_800DF200;
        rx = x + (D_800DF1F0 - x) * t * 0.015625f;
        ry = y + (D_800DF1F4 - y) * t * 0.015625f;
        rz = z + (D_800DF1F8 - z) * t * 0.015625f;
        D_800DF200--;
        x = rx;
        y = ry;
        z = rz;
    }
    func_800B83A4(x, y, z, a & 1);
    if (D_800E79CC < 0x100) {
        D_800E79CC++;
    }
}
