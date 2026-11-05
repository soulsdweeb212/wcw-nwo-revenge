/* @header
 * func_800C1F50
 * VRAM 0x800C1F50 | ROM 0x6E6C0 | size 0x420
 * asm: asm/nonmatchings/code_80090000/func_800C1F50.s
 */
#include "common.h"

typedef struct { u8 pad0[4]; u16 held; u16 pressed; u8 pad8[2]; s8 sx; s8 sy; } Pad;
typedef struct { f32 x, y, z; s32 r; } Cam;
typedef struct { u8 pad0[0x6C4]; s32 f6C4; u8 pad6C8[8]; } Wr;

extern Pad D_8006E178[];
extern Wr *D_800E79B8;
extern f64 D_800D6C60;
s32 func_800B5E18(s32, s32);
f32 nw2Sqrtf(f32);
void guPositionF(void *, f32, f32, f32, f32, f32, f32, f32);
void guMtxXFMF(void *, f32, f32, f32, f32 *, f32 *, f32 *);

void func_800C1F50(Cam *a, s32 wi, s32 pi) {
    s32 sx = 0;
    s32 sy = 0;
    Wr *w = &D_800E79B8[wi];
    Pad *c = &D_8006E178[pi];
    f32 spd = 0.0f;
    s32 k;
    f32 m[16];

    if (c->pressed & 0x1000) {
        a->z = 0.0f;
        a->y = 0.0f;
        a->x = 0.0f;
        a->r = 0x800;
    } else {
        if (c->sx < -4 || c->sx > 4) {
            sx = c->sx;
        }
        if (c->sy < -4 || c->sy > 4) {
            sy = c->sy;
        }
    }
    if (!(c->held & 0x2000)) {
        if (c->held & 0x800) {
            a->y += 8.0f;
        }
        if (c->held & 0x400) {
            a->y -= 8.0f;
        }
        if (c->held & 0x200) {
            a->r -= 0x20;
        }
        if (c->held & 0x100) {
            a->r += 0x20;
        }
        a->x += sx / 4;
        a->z += sy / 4;
    } else {
        if (c->held & 0x8000) {
            spd = -16.0f;
        }
        if (c->held & 0x4000) {
            spd = 32.0f;
        }
        if (c->held & 0x800) {
            a->y -= 8.0f;
        }
        if (c->held & 0x400) {
            a->y += 8.0f;
        }
        k = func_800B5E18(sx, sy);
        if (k >= 0) {
            if (a->r != k) {
                if ((a->r - k) & 0x800) {
                    a->r += 0x100;
                    if (!((a->r - k) & 0x800)) {
                        a->r = k;
                    }
                } else {
                    a->r -= 0x100;
                    if ((a->r - k) & 0x800) {
                        a->r = k;
                    }
                }
            }
            a->r &= 0xFFF;
            spd = nw2Sqrtf(sx * sx + sy * sy) * 0.2f;
        }
    }
    guPositionF(m, 0.0f, a->r * 360 * D_800D6C60, 0.0f, 1.0f, a->x, a->y, a->z);
    guMtxXFMF(m, 0.0f, 0.0f, spd, &a->x, &a->y, &a->z);
    if (w->f6C4 == 4) {
        if (-280.0f < a->x && a->x < 280.0f && -280.0f < a->z && a->z < 280.0f) {
            a->y = 90.0f;
        } else {
            a->y = 0.0f;
        }
    }
}
