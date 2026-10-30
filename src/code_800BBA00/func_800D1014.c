/* @header
 * func_800D1014
 * VRAM 0x800D1014 | ROM 0xC44B4 | size 0x710
 * asm: asm/nonmatchings/code_800BBA00/func_800D1014.s
 */
#include "common.h"

typedef struct {
    s8 f0;
    u8 pad1[3];
    s16 f4;
    s16 f6;
    u16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    s16 f16;
    u8 pad18[8];
    u64 flags;
    u8 pad28[4];
    u32 f2C;
    u8 pad30[0xE];
    s16 f3E;
    u8 pad40[0xC];
    f32 vec[3];
    s32 f58;
    u8 pad5C[0x2EC];
    s32 f348;
    u8 pad34C[5];
    u8 f351;
    u8 pad352[0xE];
    u16 f360;
    s8 f362;
    u8 pad363[1];
    void *f364;
    u8 pad368[0xC];
    u8 f374;
    u8 pad375[3];
    u8 f378;
    u8 pad379[0xB];
    s8 f384;
    u8 pad385[0x22];
    u8 f3A7;
    u8 pad3A8[4];
    u32 f3AC;
} Nw2Action5C;

typedef struct {
    f32 x, y, z;
    s32 angle;
} Nw2Dir;

extern Nw2Action5C *D_800FAF5C;
extern Nw2Action5C *D_800F9B00;
extern s8 D_800FADB8;
extern u8 D_800FABE4;
extern u16 D_800E3CD0[];
extern s32 D_800EB5C0[][4];
extern s32 D_800EB5C4[][4];
extern f32 D_800EB5C8[][4];
extern s32 D_800EB5CC[][4];

s16 func_800D5438(void *, s32);
void func_800D427C(void *, s16, s32);
s32 func_800D1B5C(void *, void *);
void func_800D1EA8(void *, void *);
f32 func_800D3890(void *, void *, void *);
s32 func_800D3E40(void *, f32 *, s32, f32 *);
void func_800D36B4(void *, void *, void *);
void translateEntityXZ(void *, void *);
s32 func_800D3684(s32, s32);
s32 func_800D35B0(s32, s32);
s32 func_800D2BAC(void *, void *, f32, s32);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
s16 findBoundaryQuadrant(void *, s32, s32);
void func_800D43B4(void *, s16, s32);
void func_800D4AD0(void *);
s32 func_800D6610(void *, s16);
void func_800A6BE0(void *, s32);
void func_800A6C48(void *, s32);
void func_800A837C(void *);
void func_800A7C40(void *, s8, s16);
void func_800A7240(void *, s32, s32, u64);

void func_800D1014(void) {
    Nw2Dir dir;
    f32 buf[4];

    D_800FAF5C->flags |= 0x1000000000ULL;

    switch (D_800FAF5C->fC) {
    case 0: {
        s32 v;
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 2);
        D_800EB5C0[D_800FADB8][0] = 0;
        D_800EB5C8[D_800FADB8][0] = func_800D3890(&D_800FAF5C->vec[0], &D_800F9B00->vec[0], 0);
        v = func_800D1B5C(D_800FAF5C, D_800F9B00);
        D_800EB5CC[D_800FADB8][0] = v;
        D_800FAF5C->f348 = func_800D3684(v, D_800FAF5C->f58) / D_800FAF5C->f4;
        D_800FAF5C->fC++;
        }
    case 1: {
        s32 v;
        if (!(D_800FAF5C->f360 & 0x40)) {
            func_800D2BAC(D_800FAF5C, D_800F9B00, 1.0f, 2);
            v = func_800D35B0(D_800FAF5C->f58, D_800FAF5C->f348);
            D_800FAF5C->f58 = v;
            D_800F9B00->f58 = func_800D35B0(v, 0x800);
            func_800D3E40(&D_800FAF5C->vec[0], &D_800EB5C0[D_800FADB8][0], D_800FAF5C->f58, buf);
            buf[1] = 0;
            func_800D36B4(&D_800F9B00->vec[0], buf, &dir);
            translateEntityXZ(D_800F9B00, &dir);
        }
        if (D_800FAF5C->f6 == D_800FAF5C->f378) {
            if (D_800F9B00->flags & 0x1000000) {
                Nw2Action5C *p;
                func_800D427C(D_800FAF5C, func_800D5438(D_800F9B00, 1), 1);
                func_800A6BE0(D_800FAF5C, 0x4A);
                p = D_800FAF5C;
                p->f351 = D_800FABE4;
                p->f360 |= 8;
                break;
            }
        }
        if (D_800FAF5C->f4 > 0) break;
        func_800A7C40(D_800FAF5C, D_800FAF5C->f384, (s16)((s8)D_800FAF5C->f3A7 + 0xEF));
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
        D_800FAF5C->fC++;
        }
        break;
    case 2:
        func_800D3890(&D_800FAF5C->vec[0], &D_800F9B00->vec[0], &dir);
        D_800EB5C8[D_800FADB8][0] = dir.y;
        D_800EB5C0[D_800FADB8][0] = 0;
        D_800EB5C4[D_800FADB8][0] = 0;
        D_800EB5CC[D_800FADB8][0] = func_800D3684(dir.angle, D_800FAF5C->f58);
        func_800D1EA8(D_800FAF5C, D_800F9B00);
        D_800FAF5C->fC++;
        break;
    case 3: {
        s32 v;
        if (D_800FAF5C->f4 <= 0) {
            func_800D43B4(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 0);
        }
        if ((D_800FAF5C->f3AC & 0x1000) && !(D_800FAF5C->f360 & 0x40)) {
            v = func_800D6610(D_800FAF5C, D_800FAF5C->f3E);
            if (D_800FAF5C->f3AC & 0x20000) {
                v = func_800D35B0(v, 0x800);
            }
            func_800A7240(D_800FAF5C, v, 0x16, 0);
            D_800F9B00->f58 = func_800D35B0(D_800FAF5C->f58, 0x800);
            func_800D3E40(&D_800FAF5C->vec[0], &D_800EB5C0[D_800FADB8][0], func_800D35B0(D_800FAF5C->f58, D_800EB5CC[D_800FADB8][0]), buf);
            buf[1] = 0;
            func_800D36B4(&D_800F9B00->vec[0], buf, &dir);
            translateEntityXZ(D_800F9B00, &dir);
        }
        func_800D1EA8(D_800FAF5C, D_800F9B00);
        if (D_800FAF5C->f3AC & 0x1000) {
            if (!(D_800FAF5C->f3AC & 0x40000)) {
                s16 q = findBoundaryQuadrant(D_800FAF5C, 0, 1);
                if (q != -1 && q == D_800FAF5C->f3E) {
                    D_800FAF5C->f360 |= 1;
                }
            }
            if (!(D_800FAF5C->f360 & 0x40)) {
                func_800D2BAC(D_800FAF5C, D_800F9B00, 1.0f, 2);
            }
        } else {
            s32 w;
            w = func_800D2BAC(D_800FAF5C, D_800F9B00, 1.0f, 2);
            if ((w & 0xFFFF) && (D_800E3CD0[D_800FAF5C->f3E] & w)) {
                D_800FAF5C->f360 |= 1;
            }
        }
        if (D_800FAF5C->f360 & 1) {
            D_800FAF5C->f360 |= 2;
            func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 2), 3);
            func_800A837C(D_800FAF5C);
            D_800FAF5C->fC++;
        }
        }
        break;
    case 4: {
        Nw2Action5C *p;
        if (D_800FAF5C->f374 != 1) {
            func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 4.0f, 0, 2);
        }
        p = D_800FAF5C;
        if (p->f4 <= 0) {
            p->f362 = -1;
            p->flags &= ~0x40000000ULL;
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    }
    }
}
