/* @header
 * func_800CA758
 * VRAM 0x800CA758 | ROM 0xBDBF8 | size 0x8FC
 * asm: asm/nonmatchings/code_800BBA00/func_800CA758.s
 */
#include "common.h"

typedef struct {
    s8 f0;
    u8 pad1[3];
    s16 f4;
    u8 pad6[2];
    u16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[4];
    s16 f14;
    s16 f16;
    s16 f18;
    u8 pad1A[6];
    u64 flags;
    u8 pad28[0x1C];
    s16 f44;
    u8 pad46[0x12];
    s32 f58;
    u8 pad5C[0x304];
    u16 f360;
    u8 pad362[0x4A];
    u32 f3AC;
} Nw2F5C;

extern void *D_800FAF5C;
extern void *D_800F9B00;
extern void *D_800F9B64;
extern s8 D_800FADB8;
extern u16 D_8007EF30[];
extern u16 D_800EB570[];
extern s16 D_800F9B80[];
extern u16 D_800FADD2[];
extern s8 D_800FAF78;
extern u16 D_800FAF8A;

s16 func_800D7690(u8 *, s32, s16);
s32 func_800D5438(void *, s16);
void func_800D427C(void *, s16, s32);
u16 func_800B6DEC(void *, void *, s32);
s8 func_800D4198(s16);
s16 func_800BF2FC(void *);
void func_800A7D1C(void *, s32);
void func_800B68A0(void *, void *, void *);
s32 func_800D2BAC(void *, void *, f32, s32);
void func_8009791C(void);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
void func_800A6C48(void *, s32);
s32 func_800D3684(s32, s32);
s32 func_800D35B0(s32, s32);
void func_800A7240(void *, s32, s32, u64);

#define O ((Nw2F5C *)D_800FAF5C)
#define B ((Nw2F5C *)D_800F9B00)

void func_800CA758(void) {
    s32 anim;
    switch (O->fC) {
    case 0: {
        u16 mask;

        O->flags |= 0x400000000000ULL;
        if (O->fA == 0x39) {
            anim = B->f8 + 1;
            O->f44 = -1;
        } else {
            anim = func_800D5438(D_800F9B00, 1);
        }
        func_800D427C(D_800FAF5C, (s16)anim, 1);

        mask = D_8007EF30[0xB8];
        D_800EB570[D_800FADB8] = 0;
        if (mask & 0x20) {
            if ((O->flags & 0x100) && !(mask & 0x100)) {
                O->f18 = 0x1E;
            } else {
                D_800FADD2[D_800FADB8]++;
                O->f18 = func_800B6DEC(D_800FAF5C, D_800F9B00, 1);
                if (O->fA == 0x3F) {
                    if ((B->flags & 0x80000) && func_800D4198(0x1F4)) {
                        O->f18 = 0x7530;
                    }
                }
                if (D_800F9B80[D_800FADB8] < 2) {
                    if ((B->f14 - O->f14) < 0x46 || func_800BF2FC(D_800FAF5C) > 0) {
                        if (O->f18 >= 0x58) O->f18 = 0x57;
                    }
                }
                if ((O->flags & B->flags) & 0x200) O->flags |= 0x400;
            }
            if (O->f18 < 0xF) O->f18 = 0xF;
        } else {
            O->f18 = 5;
        }
        func_800D7690(D_800FAF5C, 0, 0);
        O->fC++;
        break;
    }
    case 1: {
        s16 r;

        O->flags |= 0x400000000000ULL;
        r = func_800D7690(D_800FAF5C, D_800FAF8A, 1);
        if (r != 0 && (r == 1 || r == 3)) {
            u16 t = O->f18;
            O->f18 = t - 1;
            if (r == 3) O->f18 = t - 2;
        }
        O->f18 = O->f18 - 1;
        if (D_800FAF78) O->f18 = 1;
        if (O->f18 < 0) {
            if ((B->f360 & 0x1F) == 0) {
                B->f360 |= 2;
                func_800A7D1C(D_800FAF5C, 0x13);
                func_800B68A0(D_800FAF5C, D_800FAF5C, D_800F9B00);
            }
        }
        if (O->fA == 0x3F) {
            u16 *p = D_800EB570;
            if ((s16)++p[D_800FADB8] >= 0x1F) {
                func_800B68A0(D_800F9B00, D_800F9B00, D_800FAF5C);
                p[D_800FADB8] = 0;
            }
        }
        if (func_800D2BAC(D_800FAF5C, D_800F9B00, 4.0f, 0xFFFFE)) {
            if ((B->f360 & 0x1F) == 0) {
                if ((D_8007EF30[0xB8] & 2) && !(O->flags & 0x100)) {
                    B->f360 |= 4;
                    if ((O->flags & B->flags) & 0x200) func_8009791C();
                }
            }
        }
        if ((B->f360 & 0x1F) != 0) {
            O->flags &= ~0x400ULL;
        }
        if (B->f360 & 0x20) {
            if ((D_8007EF30[0xB8] & 0x20) && (B->f360 & 2)) {
                if ((O->flags & 0x40) || ((O->flags & 0x100) && (D_8007EF30[0xB8] & 0x100)))
                    D_800F9B80[D_800FADB8]++;
            }
            if (O->fA == 0x39) {
                anim = B->f8 + 1;
            } else {
                if (B->f360 & 0x10) anim = 7;
                else if (B->f360 & 8) anim = 5;
                else anim = 3;
                anim = func_800D5438(D_800F9B00, anim);
            }
            func_800D427C(D_800FAF5C, (s16)anim, 6);
            O->fC++;
        }
        break;
    }
    case 2: {
        func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 2.0f, 0, 0xFFFFE);
        if (O->f4 <= 0) {
            func_800D4AD0(D_800FAF5C);
            if (O->fA == 0x39) {
                if (O->flags & 0x8000) {
                    beginEntityActionA8D8C(D_800FAF5C);
                } else {
                    O->flags |= 0x80000000000000ULL;
                    func_800A6C48(D_800FAF5C, 0x2B);
                }
            } else {
                if ((O->flags & 0x100) || (B->f3AC & 4) || (O->f360 & 0x40) || (O->flags & 0x8000)) {
                    beginEntityActionA8D8C(D_800FAF5C);
                } else {
                    O->flags |= 0x80000000000000ULL;
                    func_800A6C48(D_800FAF5C, 0x2B);
                }
            }
        }
        break;
    }
    case 3:
        func_800D427C(D_800FAF5C, 0xFC6, 1);
        func_800B68A0(D_800F9B64, D_800F9B64, D_800FAF5C);
        O->fC++;
        break;
    case 4: {
        s32 r;

        func_800D2BAC(D_800FAF5C, D_800F9B00, 4.0f, 0xFFFFE);
        if (func_800D3684(O->f58, B->f58) < 0)
            r = func_800D35B0(B->f58, -0x400);
        else
            r = func_800D35B0(B->f58, 0x400);
        func_800A7240(D_800FAF5C, r, 0x16, 0);
        if (O->f4 <= 0 && B->fC != 3) {
            O->fC = 0;
            O->flags |= 0x10000000;
        }
        break;
    }
    }
}
