/* @header
 * func_800AAF5C
 * VRAM 0x800AAF5C | ROM 0x576CC | size 0x450
 * asm: asm/nonmatchings/code_80090000/func_800AAF5C.s
 */
#include "common.h"

typedef struct { u8 pad0[0xA]; u16 flags; u8 padC[0x16]; u16 f22; u8 pad24[0x148 - 0x24]; } El;
typedef struct { void *items; s16 cur; u8 pad6[0xE]; El *el; u8 pad18[0x138 - 0x18]; } Menu;
typedef struct { s16 f4C; s16 f4E; u8 f50; u8 pad51; u8 f52; u8 pad53[9]; } Pl;
typedef struct {
    u8 pad0[8];
    u16 mode;
    u8 padA[6];
    s16 f10;
    s16 f12;
    u8 pad14[0x38];
    Pl pl[0xCB];
    u8 padCFC[4];
    s32 fD00;
} Game;

extern s16 D_80038A90;
extern s16 D_800E7CB8;
extern s16 D_800E7B68[];
extern s32 D_800EA318, D_800E6B90, D_800E7C90, D_800E74E0, D_800E7934;
extern s16 D_800E8D2C, D_800E995C;
extern u16 D_800EA0C0;
extern struct { u8 pad0[6]; u16 f6; } D_8006E178;
extern Game D_8007EF30;
extern Menu D_800E8230[];
s32 func_800AAC2C(s32);
void func_800A9210(s32);

static inline void push(s32 id, s32 n) {
    if (D_800E7CB8 < 0) {
        D_800E7CB8 = 0;
    }
    D_800E7B68[D_800E7CB8++] = id | (n << 8);
    if (D_800E7CB8 >= 0x40) {
        D_800E7CB8 = 0;
    }
}

static inline void rec(s32 i, s32 a, s32 c, s32 b) {
    D_8007EF30.pl[i].f50 = b;
    D_8007EF30.pl[i].f4C = a;
    D_8007EF30.pl[i].f52 = 5;
    D_8007EF30.pl[i].f4E = c;
}

s32 func_800AAF5C(Menu *m, s32 ev) {
    s32 r = -1;

    switch (D_80038A90) {
    case 0xB:
        if (m->cur == 0x16 || m->cur == 0x17) {
            push(D_80038A90, m->cur);
            r = 0x41D;
        } else {
            m->cur = 0x16;
            D_800EA318 = 0x401;
        }
        break;
    case 9:
        if (m->cur == 0x10) {
            push(D_80038A90, 0x10);
            r = 0x420;
        } else {
            D_800E8D2C = 0x10;
            D_800EA318 = 0x401;
        }
        break;
    case 0x13:
        if (m->cur == 0xA) {
            push(D_80038A90, 0xA);
            r = 0x425;
        } else {
            D_800E995C = 0xA;
            D_800EA318 = 0x401;
        }
        break;
    case 1:
    case 0x15:
    case 0x16:
    case 0x17:
        break;
    default:
        switch (ev) {
        case 0x400:
            D_800E6B90 = 0;
            if (D_800EA0C0 & 0x2000) {
                D_800E7C90 = 0x2F;
                D_800E74E0 = 0;
            } else {
                r = 0x400;
            }
            break;
        case 0x417:
            if ((D_8006E178.f6 & 0x1000) && !(m->el[m->cur].flags & 0x53)) {
                if ((D_8007EF30.mode & 0xF) == 8) {
                    push(D_80038A90, m->cur);
                    D_800EA318 = 0x42A;
                    r = 0x417;
                } else {
                    push(D_80038A90, m->cur);
                    rec(D_8007EF30.fD00, D_8007EF30.f10, m->el[m->cur].f22, D_8007EF30.f12);
                    r = func_800AAC2C(1);
                    func_800A9210(D_800E7934);
                    D_800EA318 = 0x402;
                    D_800E8230[20].el[3].flags |= 0x20;
                }
            }
            break;
        }
        break;
    }
    return r;
}
