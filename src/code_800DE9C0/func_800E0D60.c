/* @header
 * func_800E0D60
 * VRAM 0x800E0D60 | ROM 0xD4200 | size 0x698
 * asm: asm/nonmatchings/code_800DE9C0/func_800E0D60.s
 */
#include "common.h"

typedef struct {
    s32 f0;
    s16 f4;
    s16 f6;
    s32 f8;
    s16 fC;
    s16 fE;
    u8 pad10[6];
    s16 f16;
    u8 pad18[8];
    u64 flags;
    u8 pad28[0x30];
    s32 f58;
    u8 pad5C[0x2EC];
    s32 f348;
} Nw2Action0D60;

extern Nw2Action0D60 *D_800FAF5C;
extern u16 D_800FABE6;
extern s8 D_800FADB8;
extern s16 D_800FADBE[];
extern s16 D_800F9B70[];
extern u16 D_800FAF8E[];
extern s8 D_800FAF78;
extern u16 D_800FAF8A;
extern s32 D_800F9B14;

void func_800D25D0(Nw2Action0D60 *, f32);
s32 func_800D2B64(Nw2Action0D60 *, s32, u16, s32);
void func_800D427C(Nw2Action0D60 *, s16, s32);
void func_800D4AD0(Nw2Action0D60 *);
s8 func_800D8DF0(Nw2Action0D60 *);
s16 updateEntityHealthLevel(Nw2Action0D60 *);
void func_800E1560(Nw2Action0D60 *, s32);
s8 func_800A93C0(void);
s32 func_800D35B0(s32, s32);
s8 selectNewLinkedTarget(void *, s32);
void func_800A7240(Nw2Action0D60 *, s32, s32, u64);

void func_800E0D60(void) {
    func_800D25D0(D_800FAF5C, 4.0f);
    func_800D2B64(D_800FAF5C, 0x40000000, 0, 0xFFFFE);

    switch (D_800FAF5C->fC) {
    case 0:
        func_800D427C(D_800FAF5C, updateEntityHealthLevel(D_800FAF5C), 6);
        D_800FADBE[D_800FADB8] = 0;
        D_800F9B70[D_800FADB8] = 0;
        D_800FAF8E[D_800FADB8] = 0;
        D_800FAF5C->f16 = 0x96;
        D_800FAF5C->flags &= 0xFEFFFFFFFFFFFFFFULL;
        D_800FAF5C->fC++;
        /* fall through */
    case 1:
        if (D_800FAF5C->f4 > 0) {
            break;
        }
        func_800D4AD0(D_800FAF5C);
        if (!func_800A93C0() && (D_800FABE6 & 0x10) &&
            (func_800D8DF0(D_800FAF5C) || (D_800FAF5C->flags & 0x100))) {
            func_800D427C(D_800FAF5C, 0xF38, 1);
            D_800FAF5C->fC++;
            break;
        }
        D_800FAF5C->fC = 3;
        D_800FAF5C->flags |= 0x10000000ULL;
        break;
    case 2: {
        s32 id;
        selectNewLinkedTarget(D_800FAF5C, D_800FAF8A);
        id = D_800F9B14;
        func_800A7240(D_800FAF5C, id, 0x71, 0x100000000ULL);
        if (D_800FAF78) {
            func_800A6C48(D_800FAF5C, 0x17);
            D_800FAF5C->fC = 2;
            return;
        }
        if ((D_800FABE6 & 0x20) && !(D_800FAF5C->flags & 1)) {
            func_800D427C(D_800FAF5C, 0xF39, 1);
            D_800FAF5C->fC = 5;
            return;
        }
        D_800FAF5C->f16--;
        if (D_800FABE6 & 0x10) {
            if (D_800FAF5C->f16 < 0 ||
                (!func_800D8DF0(D_800FAF5C) && (D_800FAF5C->flags & 0x40))) {
                D_800FAF5C->fC++;
                return;
            }
            if (D_800FABE6 & 0x8000) {
                if (D_800FAF5C->flags & 9) {
                    func_800A6C48(D_800FAF5C, 0x21);
                } else {
                    func_800A6C48(D_800FAF5C, 0x44);
                    D_800FAF5C->fC = 7;
                }
                return;
            }
            if (D_800FABE6 & 0x4000) {
                func_800A6C48(D_800FAF5C, 0x21);
                return;
            }
            break;
        } else {
            D_800FAF5C->fC++;
            break;
        }
    }
    case 3:
        func_800E1560(D_800FAF5C, D_800F9B14);
        D_800FAF5C->fC++;
        break;
    case 4:
        D_800FAF5C->f58 = func_800D35B0(D_800FAF5C->f58, D_800FAF5C->f348);
        if (D_800FAF5C->f4 <= 0) {
            D_800FAF5C->fC = 6;
        }
        break;
    case 5:
        if (D_800FAF5C->f4 <= 0) {
            D_800FAF5C->fC = 6;
        }
        break;
    }

    if (D_800FABE6 & 0x8000) {
        D_800FADBE[D_800FADB8]++;
    } else {
        D_800FADBE[D_800FADB8] = 0;
    }
    if (D_800FABE6 & 0x4000) {
        D_800F9B70[D_800FADB8]++;
    } else {
        D_800F9B70[D_800FADB8] = 0;
    }
    if (D_800FADBE[D_800FADB8] | D_800F9B70[D_800FADB8]) {
        D_800FAF8E[D_800FADB8] |= D_800FABE6 & 0xF00;
    } else {
        D_800FAF8E[D_800FADB8] = 0;
    }

    if (D_800FAF5C->fC != 6) {
        return;
    }
    D_800FAF5C->flags &= 0xFFFFFDFFFFFFFFFFULL;
    func_800D4AD0(D_800FAF5C);
    if (func_800D8DF0(D_800FAF5C) || (D_800FAF5C->flags & 0x100)) {
        if (D_800FADBE[D_800FADB8]) {
            if (D_800FAF5C->flags & 9) {
                D_800FAF5C->flags |= 0x0100000000000000ULL;
                D_800F9B70[D_800FADB8] = D_800FADBE[D_800FADB8];
                func_800A6C48(D_800FAF5C, 0x1E);
            } else {
                func_800A6C48(D_800FAF5C, 0x44);
            }
            D_800FAF5C->fC = 1;
            return;
        }
        if (D_800F9B70[D_800FADB8]) {
            func_800A6C48(D_800FAF5C, 0x1E);
            D_800FAF5C->fC = 1;
            return;
        }
    }
    func_800A6C48(D_800FAF5C, 0x2B);
}
