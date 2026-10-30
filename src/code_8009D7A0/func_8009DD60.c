/* @header
 * func_8009DD60
 * VRAM 0x8009DD60 | ROM 0x91200 | size 0x7FC
 * asm: asm/nonmatchings/code_8009D7A0/func_8009DD60.s
 */
#include "common.h"

typedef struct {
    s32 f0;
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[0x10];
    u64 flags;
    u8 pad28[0x14];
    u16 f3C;
    u16 f3E;
    u16 f40;
    u8 pad42[0x312];
    s8 f354;
} Nw2DD60;

#define O ((Nw2DD60 *)D_800EB408)

extern void *D_800EB40C;
extern void *D_800FAF5C;
extern u8 D_800FADCF;
extern s8 D_800FADB8;
extern s8 D_800FAF78;
extern u16 D_800FABE6;
extern u16 D_800FAF8A;
extern u32 D_800F9B14;
extern f32 D_800F9B0C[];
extern s16 D_800F9D08[];
extern u8 D_8007EF30[];
extern u8 D_8007E228[];

void func_800A6C48(void *, s32);
void func_800A7240(void *, s32, s32, u64);
s8 selectNewLinkedTarget(void *, s32);
s8 updateSpecialMoveRequest(void *);
s8 isEntityActionAllowedC2870(void *);
u32 func_800D6658(void *, void *, s32, s32, f32);
s8 func_800DF5C4(void *, void *, u16, u16, s8, s32);
s8 func_800DE9C0(void *, void *, u16, u16, s32);
s8 tryEntityAttackDEF84(void *, u16, u16, s32);
s8 func_800E2400(void *, u16, u16, u32);
s8 func_800DF214(void *, u16);
s8 func_800DF3E4(void *, void *, u16, f32);
s8 func_800DFDD4(void *, void *, u16, void *);
s8 func_800DF99C(void *, void *, u16, void *);
s8 func_800E022C(void *, void *, u16, void *);
s8 func_800E0590(void *, void *, u16, void *);
s8 func_800E074C(void *, u16, u16);
s8 func_800E06C0(void *, void *, s8);
void func_800BF548(void *, s32);
void updateEntityStunTimer(void *, void *, s32);
void func_800D93DC(void *);

void func_8009DD60(void) {
    O->flags |= 0x100000000000ULL;

    if (D_800FADCF & 0x40) {
        if (O->flags & 0x4000) {
            if (O->flags & 0x40) {
                func_800A6C48(O, 0x17);
            }
            if (O->flags & 0x80) {
                O->f3E = O->f3C;
                func_800A6C48(O, 0x61);
            }
            if (O->flags & 0x100) {
                if (*(u16 *)(D_8007EF30 + 0x170) & 0x100) {
                    func_800A6C48(O, 0x17);
                    return;
                }
                func_800A6C48(O, 0x70);
            }
            return;
        }
        if (O->flags & 0x140) {
            func_800A7240(O, D_800F9B14, 0x155, 0x100000000ULL);
        }
        func_800D6658(O, D_800EB40C, 0, 0, D_800F9B0C[0]);
        return;
    }

    if (O->flags & 0x8000) {
        O->flags |= 0x10000ULL;
    }
    if (selectNewLinkedTarget(O, D_800FAF8A)) {
        return;
    }
    if (O->flags & 0x8000) {
        if (O->flags & 0x40) {
            func_800A6C48(O, 0x82);
            return;
        }
        if (O->flags & 0x80) {
            O->f3E = O->f3C;
            func_800A6C48(D_800FAF5C, 0x60);
            return;
        }
    }
    if (updateSpecialMoveRequest(O)) {
        func_800A6C48(O, 0x7E);
        return;
    }
    if (*(u16 *)(D_8007EF30 + 0x170) & 4) {
        if (O->flags & 0x100) {
            if (*(u16 *)(D_8007E228 + 0x58) & 0x100) {
                if (O->flags & 0x200) {
                    func_800A6C48(O, 0x70);
                    return;
                }
            }
            if (*(u16 *)(D_8007E228 + 0x58) & 0x200) {
                func_800A6C48(O, 0x70);
                return;
            }
        }
    }
    if (O->flags & 3) {
        if (!isEntityActionAllowedC2870(O)) {
            if (O->flags & 0x40) {
                func_800A6C48(O, 0x90);
                return;
            }
            if (O->flags & 0x80) {
                O->f3E = O->f3C;
                func_800A6C48(D_800FAF5C, 0x60);
                return;
            }
        }
    }

    if (O->flags & 0x10) {
        D_800FABE6 = 0;
        D_800FAF8A = 0;
        D_800FAF78 = 0;
    }
    if (*(u16 *)(D_8007EF30 + 0x170) & 0x400) {
        if (O->flags & 0x100) {
            if (!(O->flags & 0x8000)) {
                O->flags |= 0x1000000800ULL;
                D_800FABE6 = 0;
                D_800FAF8A = 0;
                D_800FAF78 = 0;
            }
        }
    }
    if (O->flags & 0x140) {
        func_800A7240(O, D_800F9B14, 0x155, 0x100000000ULL);
    }

    O->f40 = 0;
    D_800F9D08[D_800FADB8] = 0;
    O->f354 = -1;
    func_800BF548(O, 1);
    updateEntityStunTimer(O, D_800EB40C, 1);
    func_800D93DC(O);
    {
        u32 r = func_800D6658(O, D_800EB40C, D_800FABE6, 0, D_800F9B0C[0]);
        u32 s1 = r;
        u32 s0 = s1 & 0xFFFF;
        void *p;
        if (s0) {
            if (((s8 (*)(void *, s32, s32, s32))func_800DECAC)(O, D_800FABE6, s0, 1)) {
                return;
            }
            if (func_800DF5C4(O, D_800EB40C, D_800FAF8A, D_800FABE6,
                              D_800FAF78, s0)) {
                return;
            }
            if (func_800DE9C0(O, D_800EB40C, D_800FABE6, D_800FAF8A, s0)) {
                return;
            }
            if (tryEntityAttackDEF84(O, D_800FABE6, D_800FAF8A, s0)) {
                return;
            }
        }
        if (s1 >> 16) {
            if (func_800E2400(O, D_800FABE6, D_800FAF8A, s1 >> 16)) {
                return;
            }
        }
        if (func_800DF214(O, D_800FABE6)) {
            return;
        }
        if (func_800DF3E4(O, D_800EB40C, D_800FABE6, D_800F9B0C[0])) {
            return;
        }
        p = D_800F9B0C - 1;
        if (func_800DFDD4(O, D_800EB40C, D_800FABE6, p)) {
            return;
        }
        if (func_800DF99C(O, D_800EB40C, D_800FABE6, p)) {
            return;
        }
        if (func_800E022C(O, D_800EB40C, D_800FABE6, p)) {
            return;
        }
        if (func_800E0590(O, D_800EB40C, D_800FABE6, p)) {
            return;
        }
        if (func_800E074C(O, D_800FABE6, D_800FAF8A)) {
            return;
        }
        func_800E06C0(O, D_800EB40C, D_800FAF78);
    }
}
