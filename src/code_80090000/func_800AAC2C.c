/* @header
 * func_800AAC2C
 * VRAM 0x800AAC2C | ROM 0x5739C | size 0x330
 * asm: asm/nonmatchings/code_80090000/func_800AAC2C.s
 */
#include "common.h"

typedef struct { u8 pad0[8]; s16 f8; u16 flags; u8 padC[8]; s16 f14; u8 f16; u8 pad17[9]; s16 f20; u8 pad22[0x148 - 0x22]; } El;
typedef struct { void *items; s16 cur; u8 pad6[0xE]; El *el; u8 pad18[0x138 - 0x18]; } Menu;
typedef struct { s16 f4C; s16 f4E; u8 pad4[0xC]; } Pl;
typedef struct {
    u8 pad0[8];
    u16 mode;
    u8 padA[2];
    s16 fC;
    u8 padE[0xC];
    s16 f1A;
    u8 pad1C[0x30];
    Pl pl[8];
} Game;

extern s16 D_80038A90;
extern Menu D_800E8230[];
extern Game D_8007EF30;
extern s32 D_8007FC30; /* right after D_8007EF30 */
extern s32 D_800EA31C, D_80038AA8, D_800E7934;
extern s32 D_800E8204[], D_800E8200[];

void func_800B4BF4(s32);
void func_800B0774(void);
void func_800AEF28(s32);
void func_800AFEF0(s32);
void func_800AEB68(void);
void func_800B1484(s32, s32);

s32 func_800AAC2C(s32 a) {
    s32 r = D_80038A90;
    El *e = &D_800E8230[r].el[D_800E8230[r].cur];
    s32 cnt = 0;
    s32 i, old;
    u16 mode;

    for (i = 0; i < 8; i++) {
        cnt += D_8007EF30.pl[i].f4E > 0;
    }
    e->f14 = 0xFF;
    e->f8 = 0;
    old = D_800EA31C;
    D_8007FC30++;
    r = 0xD;
    if (a) {
        func_800B4BF4(D_8007FC30 - 1);
        r = 0x13;
        D_800E8230[20].el[2].flags |= 1;
        D_800E8230[20].el[1].f20 = 3;
        D_800E8230[20].el[1].f16 = 0;
    } else {
        mode = D_8007EF30.mode;
        if (mode & 0x8000) {
            if (((mode & 0x20) && cnt >= 2) || (!(mode & 0x20) && cnt > 0)) {
                func_800B0774();
                func_800AEF28(1);
                func_800AFEF0(0);
                r = 0xB;
            }
        } else if (mode & 0x80) {
            if (cnt < D_8007EF30.fC) {
                D_800EA31C = D_8007FC30;
            } else {
                D_80038AA8 = D_8007EF30.f1A;
                func_800AEB68();
                r = 0xB;
                func_800AEF28(1);
                func_800AFEF0(0);
            }
        } else if ((mode & 0xF) == 8) {
            func_800B4BF4(0);
            r = 0x13;
        } else if (cnt >= D_8007EF30.fC) {
            r = 0xC;
            func_800AEF28(1);
            func_800AFEF0(0);
        } else if ((mode & 0x10) || !(cnt & 1)) {
            D_800EA31C = D_8007FC30;
        }
    }
    if (r == 0xD || r == 0xE) {
        if (old != D_800EA31C) {
            D_800E7934 = 0;
            if (D_80038A90 == 0xE) {
                func_800B1484(0xE, -1);
                func_800B1484(0xD, 1);
                D_80038A90 = 0xD;
            }
            if (r == 0xD) {
                r = 0xE;
            }
            D_800E8204[0] = -1;
            D_800E8200[0] = -1;
        } else if (D_80038A90 == 0xE) {
            if (r == 0xD) {
                r = 0xE;
            } else if (r != 0xE) {
                func_800B1484(0xE, -1);
                func_800B1484(0xD, 1);
                D_80038A90 = 0xD;
            }
        }
    }
    if (r == 0xD || r == 0xE) {
        D_800E8230[20].el[3].f20 = D_8007FC30 | 0x1200;
    } else {
        D_800E8230[20].el[3].f20 = 0x120F;
        D_800E8204[0] = -1;
        D_800E8200[0] = -1;
    }
    return r;
}
