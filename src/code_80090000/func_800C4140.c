/* @header
 * func_800C4140
 * VRAM 0x800C4140 | ROM 0x708B0 | size 0x7DC
 * asm: asm/nonmatchings/code_80090000/func_800C4140.s
 */
#include "common.h"

typedef struct { f32 x, y, z; s32 a; } Cam;
typedef struct {
    u8 pad0[0x680];
    Cam cam;
    u8 pad690[2];
    s16 f692;
    s16 f694;
    u16 f696;
    u8 pad698[2];
    s16 f69A;
    u16 f69C;
    u16 f69E;
    u16 f6A0;
    s16 f6A2;
    s16 f6A4;
    s16 f6A6;
    s16 f6A8;
    s16 f6AA;
    s16 f6AC;
    s16 f6AE;
    s16 f6B0;
    s16 f6B2;
    s16 f6B4;
    s16 f6B6;
    s16 f6B8;
    s16 f6BA;
    s16 f6BC;
    s16 f6BE;
    u8 pad6C0[4];
    s32 f6C4;
    u8 pad6C8[8];
} P;
typedef struct { u8 pad0[0x54]; f32 x; u8 pad58[4]; f32 z; u8 pad60[0xB24 - 0x60]; } R;

extern P *D_800E79B8;
extern R D_80070CBC[];
extern s32 D_800EA0A8[];
extern s32 D_800E8200[];
extern s32 D_800E74D8, D_800E74D4, D_800EA348;
extern s32 D_800E73A4[3];
extern s32 D_800D5E80, D_800D5E84, D_800E6B7C, D_800EA320, D_800E7920;
extern s16 D_800E7C84[2];

void func_800C36F8(s32);
void func_800C33F4(s32);
void func_800C3BF8(s32, P *);
u16 func_8000B46C(s16);
u16 func_8000B550(s16, s32);
void func_80012B38(s16, s32, s32);
s32 func_800C2E50(P *);
s16 func_80008574(s16);
void func_8000946C(s16, s16, s16);

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

void func_800C4140(s32 n, s32 a, s32 b) {
    P *p = &D_800E79B8[n];
    s16 m;
    s32 x;

    if (D_800E8200[n] >= 0) {
        func_800C36F8(n);
    }
    p->f694 = a;
    p->f69A = b;
    if (D_800E74D8 == -3) {
        p->f6AA = D_800E74D4;
        p->f6AE = D_800EA348;
        p->f6A2 = D_800E73A4[0];
        p->f6A4 = D_800E73A4[1];
        p->f6A6 = D_800E73A4[2];
    }
    if (p->f6B0 != p->f6BC) {
        p->f6B0 = p->f6BC;
        p->f6B4 = 0;
    }
    if (D_800D5E80 != 0) {
        for (;;) {
            D_800D5E84 = 0;
            func_800C33F4(n);
            if (p->f6BA == 0) {
                break;
            }
        }
    } else {
        func_800C33F4(n);
    }
    switch (D_800E74D8) {
    case -2:
        if (n == D_800E6B7C) {
            if (p->f6BA == 0 && !(p->f6C4 & 0x80)) {
                if (p->f6B4 < p->f6B8) {
                    p->f6BE = 2;
                    break;
                }
                if (++D_800EA0A8[n] >= 9) {
                    D_800EA0A8[n] = 0;
                }
                setPos(n);
                x = D_800EA0A8[n];
                if (x == 2) {
                    p->f6BC = 0xBD;
                } else if (x == 5) {
                    p->f6BC = 0xBB;
                } else if (x == 8) {
                    p->f6BC = 0xBE;
                } else {
                    p->f6BC = -1;
                }
            } else {
                D_800EA0A8[n] = 0;
                p->f6BC = -1;
            }
        } else {
            p->f6BC = -1;
        }
        p->f6BE = 2;
        break;
    case -7:
        if (p->f6BA == 0 && !(p->f6C4 & 0x80)) {
            if (p->f6B4 >= p->f6B8) {
                if (++D_800EA0A8[n] >= 2) {
                    D_800EA0A8[n] = 0;
                }
                setPos(n);
            }
        } else {
            D_800EA0A8[n] = 0;
        }
        if (D_800EA0A8[n] == 0) {
            p->f6BC = 0x10D8;
        } else {
            p->f6BC = 0xBD;
        }
        p->f6BE = 2;
        break;
    case -5:
    case -4:
        p->f6BE = 2;
        switch (D_800EA320) {
        case 2:
            if (D_800EA0A8[n] == D_800EA320) {
                if (p->f6BC != 0xBB) {
                    p->f6BC = 0xBB;
                } else if (p->f6B4 >= p->f6B8) {
                    setPos(n);
                    D_800EA0A8[n]++;
                }
                break;
            }
            p->f6BC = -5;
            break;
        case 1:
        case 3:
            p->f6BC = -5;
            break;
        case 0:
        case 4:
            if (D_800EA0A8[n] == D_800EA320) {
                p->f6BC = -6;
            }
            break;
        }
        break;
    case -9:
        func_800C3BF8(n, p);
        break;
    case -8:
        p->f6BC = 0x1CCB;
        p->f6BE = 0;
        break;
    case -3:
        D_800EA0A8[n] = 0;
        D_800EA320 = 0;
        p->f6BC = 0xE3D;
        p->f6BE = 0;
        break;
    case -1:
        D_800EA0A8[n] = 0;
        D_800EA320 = 0;
        p->f6BC = -1;
        p->f6BE = 0;
        break;
    case -6:
    default:
        D_800EA0A8[n] = 0;
        D_800EA320 = 1;
        p->f6BC = -1;
        p->f6BE = 0;
        break;
    }
    if (a < 0 || p->f692 < 0) {
        p->f6C4 = 0x80;
    } else if (p->f6BA == 0) {
        if (p->f6C4 == 0x80) {
            m = n;
            D_800E7920 = func_8000B46C(m);
            D_800E7C84[0] = func_8000B550(m, 1);
            D_800E7C84[1] = func_8000B550(m, 2);
            if (p->f696 & 4) {
                func_80012B38(m, (p->f696 & 0x70) >> 4, 2);
            } else {
                func_80012B38(m, -1, 2);
            }
            p->f6B8 = func_80008574(p->f6B2 = func_800C2E50(p));
            p->f6B4 = 0;
            p->f6B6 = 0;
            func_8000946C(n, p->f6B2, p->f6B4);
        }
        if (D_800E74D8 == -9 || D_800E74D8 == -8 || D_800E74D8 == -10) {
            p->f6C4 = 4;
        } else {
            p->f6C4 = 0;
        }
    }
    D_800E74D4 = p->f6A8;
    D_800EA348 = p->f6AC;
    D_800E73A4[0] = p->f69C & 0xF;
    D_800E73A4[1] = p->f69E & 0xF;
    D_800E73A4[2] = p->f6A0 & 0xF;
}
