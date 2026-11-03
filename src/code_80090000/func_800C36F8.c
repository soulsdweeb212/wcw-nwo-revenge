/* @header
 * func_800C36F8
 * VRAM 0x800C36F8 | ROM 0x6FE68 | size 0x500
 * asm: asm/nonmatchings/code_80090000/func_800C36F8.s
 */
#include "common.h"

typedef struct { f32 x, y, z; s32 a; } Cam;
typedef struct {
    u8 pad0[0x680];
    Cam cam;
    u8 pad690[0x6BA - 0x690];
    s16 f6BA;
    u8 pad6BC[0x6D0 - 0x6BC];
} P;

extern P *D_800E79B8;
extern s32 D_800E74D8, D_800E6B7C, D_800E74F0, D_800E8204;
extern s8 D_800EA0C6, D_800EA0C7;
extern f64 D_800D6CA0;
f32 nw2Sqrtf(f32);
void func_800C2704(s32);

void func_800C36F8(s32 n) {
    Cam t;
    P *p;
    s32 sx = 0, sy = 0, off = 0, a;
    f32 dx, dy, dz, d;
    s32 z;

    p = &D_800E79B8[n];
    switch (D_800E74D8) {
    case -7:
    case -3:
    case -2:
        if (n == D_800E6B7C) {
            if (D_800EA0C6 < -4 || D_800EA0C6 > 4) {
                sx = D_800EA0C6;
            }
            if (D_800EA0C7 < -4 || D_800EA0C7 > 4) {
                sy = D_800EA0C7;
            }
            D_800E74F0 = D_800E74F0 - sy * D_800D6CA0;
            if (D_800E74F0 < 0) {
                D_800E74F0 = 0;
            }
            if (D_800E74F0 > 0x80) {
                D_800E74F0 = 0x80;
            }
            off -= sx;
        }
        t.a = p->cam.a + off;
        z = D_800E74F0;
        if (D_800E74D8 == -3) {
            t.x = (z * -22) / 128 + 0x39;
            t.y = (z * -40) / 128 + 0x71;
            t.z = (z * -151) / 128 - 0x379;
        } else if (D_800E74D8 == -7) {
            if (n != 0) {
                t.x = 118.0f;
            } else if (D_800E8204 < 0) {
                t.x = 68.0f;
            } else {
                t.x = 18.0f;
            }
            t.y = 64.0f;
            t.z = -717.0f;
            t.a = 0x800;
        } else if (n == D_800E6B7C) {
            t.x = (z * -63) / 128 + 0x6C;
            t.y = (z * -16) / 128 + 0x40;
            t.z = (z * -343) / 128 - 0x2C4;
        } else {
            t.x = 48.0f;
            t.y = 80.0f;
            t.z = -512.0f;
            t.a = 0x800;
        }
        if (p->f6BA != 0) {
            p->cam.x = t.x;
            p->cam.y = t.y;
            p->cam.z = t.z;
            p->cam.a = t.a;
            break;
        }
        dx = t.x - p->cam.x;
        dy = t.y - p->cam.y;
        dz = t.z - p->cam.z;
        d = nw2Sqrtf(dx * dx + dy * dy + dz * dz);
        if (d != 0.0f) {
            if (d < 30.0f) {
                p->cam.x = t.x;
                p->cam.y = t.y;
                p->cam.z = t.z;
            } else {
                p->cam.x += dx * 30.0f / d;
                p->cam.y += dy * 30.0f / d;
                p->cam.z += dz * 30.0f / d;
            }
        }
        a = p->cam.a;
        if (a != t.a) {
            if ((a - t.a) & 0x800) {
                a += 0x80;
                if (!((a - t.a) & 0x800)) {
                    a = t.a;
                }
            } else {
                a -= 0x80;
                if ((a - t.a) & 0x800) {
                    a = t.a;
                }
            }
        }
        p->cam.a = a & 0xFFF;
        break;
    case -9:
    case -5:
    case -4:
        func_800C2704(n);
        break;
    case -10:
    case -8:
        if (n != 0) {
            p->cam.x = 50.0f;
        } else if (D_800E8204 < 0) {
            p->cam.x = 0.0f;
        } else {
            p->cam.x = -50.0f;
        }
        p->cam.y = 90.0f;
        p->cam.z = 0.0f;
        p->cam.a = 0x800;
        break;
    case -6:
        break;
    }
}
