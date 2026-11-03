/* @header
 * func_800C3BF8
 * VRAM 0x800C3BF8 | ROM 0x70368 | size 0x548
 * asm: asm/nonmatchings/code_80090000/func_800C3BF8.s
 */
#include "common.h"

typedef struct { f32 x, y, z; s32 a; } Cam;
typedef struct {
    u8 pad0[0x680];
    Cam cam;
    u8 pad690[0x6B4 - 0x690];
    s16 f6B4;
    u8 pad6B6[2];
    s16 f6B8;
    u8 pad6BA[2];
    s16 f6BC;
    s16 f6BE;
    u8 pad6C0[4];
    s32 f6C4;
    u8 pad6C8[0x6D0 - 0x6C8];
} P;
typedef struct { u8 pad0[0x54]; f32 x; u8 pad58[4]; f32 z; u8 pad60[0xB24 - 0x60]; } R;

extern P *D_800E79B8;
extern R D_80070CBC[];
extern s32 D_800EA0A8[];
extern s32 D_800E7CC0[3][2];
extern s32 D_800E74B8[];
s32 func_800B807C(s32, s32);

static inline void setPos(s32 n) {
    P *q = &D_800E79B8[n];
    R *r = &D_80070CBC[n];
    s32 c = q->f6C4 == 4;

    q->cam.x = r->x;
    q->cam.z = r->z;
    if (c && q->cam.x > -300.0f && q->cam.x < 300.0f && q->cam.z > -300.0f && q->cam.z < 300.0f) {
        q->cam.y = 90.0f;
    }
}

void func_800C3BF8(s32 n, P *p) {
    p->f6BE = 2;
    switch (D_800EA0A8[n]) {
    case 9:
        if ((D_800E7CC0[0][n] & 3) == 3) {
            p->f6BC = -5;
            D_800EA0A8[n] = 15;
        } else if (D_800E7CC0[0][n] / 4 == 2) {
            p->f6BC = 0xE7D;
            D_800EA0A8[n] += 2;
        } else {
            p->f6BC = 0x1087;
            D_800EA0A8[n]++;
        }
        break;
    case 10:
        if (p->f6B4 >= p->f6B8) {
            p->f6BC = -7;
            p->f6B4 = 0;
            D_800EA0A8[n]++;
            setPos(n);
        }
        break;
    case 11:
        if (p->f6B4 >= p->f6B8) {
            D_800EA0A8[n]++;
            setPos(n);
            D_800E7CC0[0][n] = D_800E7CC0[1][n];
            D_800E74B8[n] = 1;
            p->f6BC = D_800E7CC0[2][n] ? 0xE6E : -6;
            p->f6B4 = 0;
        }
        break;
    case 12:
        p->f6BC = D_800E7CC0[2][n] ? 0xE6E : -6;
        break;
    case 13:
        if (n == 1 && D_800EA0A8[0] < 15) {
            p->f6BC = -5;
            break;
        }
        if (n != 0 && func_800B807C(-1, -1)) {
            break;
        }
        p->f6BC = 0xBC;
        D_800EA0A8[n]++;
        break;
    case 14:
        if (p->f6B4 >= p->f6B8) {
            setPos(n);
            p->f6BC = -5;
            p->f6B4 = 0;
            D_800EA0A8[n]++;
        }
        break;
    case 15:
        p->f6BC = -5;
        break;
    case 1:
    case 5:
        D_800EA0A8[n] += 3;
        break;
    default:
        if (D_800E7CC0[0][n] / 4 == 2) {
            p->f6BC = 0xE6E;
        } else {
            p->f6BC = -6;
        }
        break;
    }
}
