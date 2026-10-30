/* @header
 * func_800CFA50
 * VRAM 0x800CFA50 | ROM 0xC2EF0 | size 0x6AC
 * asm: asm/nonmatchings/code_800BBA00/func_800CFA50.s
 */
#include "common.h"

typedef struct {
    u8 pad38[0x38];
    u64 flags;
} Nw2Attach38;

typedef struct {
    s8 f0;
    u8 pad1[3];
    s16 f4;
    s16 f6;
    u16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[6];
    s16 f16;
    u8 pad18[8];
    u64 flags;
    u8 pad28[4];
    u32 f2C;
    u8 pad30[0x28];
    s32 f58;
    u8 pad5C[0x2E0];
    f32 vec[3];
    s32 f348;
    u8 pad34C[5];
    u8 f351;
    u8 pad352[0xE];
    u16 f360;
    s8 f362;
    u8 pad363;
    Nw2Attach38 *f364;
    u8 pad368[0x44];
    u32 f3AC;
} Nw2F5CState;

#define O ((Nw2F5CState *)D_800FAF5C)
#define B ((Nw2F5CState *)D_800F9B00)

extern Nw2F5CState *D_800FAF5C;
extern Nw2F5CState *D_800F9B00;
extern u16 D_800FAF8A;
extern u8 D_800FABE4;
extern u8 D_800FADB8;
extern s16 D_800EB628[];
extern s32 D_800EB610[];

void selectTurnAnimationCDC04(void *, void *);
void func_800D0700(void *, void *, u16);
void translateEntityXZ(void *, void *);
s32 func_800D35B0(s32, s32);
void func_800D427C(void *, s16, s32);
s16 func_800D5438(void *, s32);
void func_800A6BE0(void *, s32);
void beginPairedEntityActions(void *, s32, void *, s32);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D4AD0(void *);

void func_800CFA50(void) {
    switch (O->fC) {
    case 0:
        O->flags &= 0xFFFFFFFFF87FFFFFULL;
        selectTurnAnimationCDC04(D_800FAF5C, D_800F9B00);
        O->f16 = 0;
        O->fC++;
        /* fall through */
    case 1: {
        Nw2F5CState *nw;
        Nw2F5CState *b;
        s32 inc;
        func_800D0700(D_800FAF5C, D_800F9B00, D_800FAF8A);
        nw = D_800FAF5C;
        nw->f16++;
        b = D_800F9B00;
        if (D_800EB628[nw->f0] < (s16)nw->f16) {
            nw->f58 = D_800EB610[nw->f0];
            if (b->f2C & 0x100000) {
                nw->fC = 7;
            }
            inc = 1;
        } else {
            if (b->f2C & 0x200) {
                translateEntityXZ(nw, (u8 *)nw + 0x33C);
            }
            nw->f58 = func_800D35B0(nw->f58, nw->f348);
            inc = 0;
        }
        {
            u16 res;
            if (res = inc) {
                O->fC++;
            }
        }
        break;
    }
    case 2:
        func_800D0700(D_800FAF5C, D_800F9B00, D_800FAF8A);
        O->f16++;
        if (B->f360 & 1) {
            func_800D427C(D_800FAF5C, (s16)(B->f8 + 1), 1);
            O->fC = 7;
        }
        if (B->f360 & 2) {
            O->fC++;
        }
        if (B->f360 & 8) {
            O->fC = 9;
        }
        break;
    case 3:
        O->fC++;
        /* fall through */
    case 4:
        if (B->fA == 0x45) {
            if (!(B->f360 & 2)) {
                O->fC -= 2;
                break;
            }
        }
        if (B->f360 & 4) {
            func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 1);
            func_800A6BE0(D_800FAF5C, 0x49);
            func_800A6BE0(D_800F9B00, 0x4A);
            O->flags |= 0x40000000ULL;
            B->flags &= 0xFFFFFFFFBFFFFFFFULL;
            O->f362 = D_800FABE4;
            B->f362 = -1;
            B->f351 = D_800FADB8;
            O->f2C = B->f2C;
            break;
        }
        if (B->f2C & 0x80) {
            if (B->f3AC & 0x100000) {
                s16 anim;
                if (B->f364->flags & 0x1000000000ULL) {
                    anim = 0xEC2;
                } else {
                    anim = 0xEC2;
                }
                func_800D427C(D_800FAF5C, anim, 1);
                O->fC++;
                break;
            }
        }
        O->fC = 6;
        O->flags |= 0x10000000ULL;
        break;
    case 5:
        if (O->f4 == 1) {
            O->fC++;
        }
        break;
    case 6:
        if (B->f2C & 0xC0) {
            func_800D427C(D_800FAF5C, func_800D5438(D_800F9B00, 1), 1);
        } else {
            func_800D427C(D_800FAF5C, func_800D5438(D_800F9B00, 1), 3);
        }
        func_800A6BE0(D_800FAF5C, 0x4A);
        break;
    case 7:
        if (!(B->f2C & 0x380)) {
            func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 1.0f, 0, 2);
        }
        if (O->f4 <= 0) {
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    case 8:
        if (O->f4 <= 0) {
            func_800D4AD0(D_800FAF5C);
            func_800D427C(D_800FAF5C, 0xE8E, 1);
            O->flags &= 0xFFFFFFFFF87FFFFFULL;
            B->flags &= 0xFFFFFFFFF87FFFFFULL;
            beginPairedEntityActions(D_800FAF5C, 0x45, D_800F9B00, 0x46);
            O->fC = 2;
            B->fC = 2;
            B->f16 = 0;
            B->f2C &= 0x402;
            O->f2C = B->f2C | 0x40;
            if (O->f2C & 2) {
                O->f16 = 0x5A;
            } else {
                O->f16 = 0x3C;
            }
        }
        break;
    case 9:
        func_800D427C(D_800FAF5C, 0xEA1, 3);
        O->fC++;
        break;
    case 10:
        func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 1.0f, 0, 2);
        if (O->f4 <= 0) {
            func_800D4AD0(D_800FAF5C);
            O->f16 = 0;
            O->flags &= 0xFFFFFFFFF87FFFFFULL;
            func_800D427C(D_800FAF5C, 0xE8F, 1);
            O->fC = 2;
        }
        break;
    }
}
