/* @header
 * func_8009DD60
 * VRAM 0x8009DD60 | ROM 0x91200 | size 0x7FC
 * asm: asm/nonmatchings/code_8009D7A0/func_8009DD60.s
 */
#include "common.h"

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

void func_800A7240(void *, s32, s32, u64);
s8 selectNewLinkedTarget(void *, s32);
s8 updateSpecialMoveRequest(void *);
s8 isEntityActionAllowedC2870(void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D6658 */
u32 func_800D6658(void *, void *, s32, s32, f32);
#endif
s8 func_800DF5C4(void *, void *, u16, u16, s8, s32);
s8 func_800DE9C0(void *, void *, u16, u16, s32);
s8 tryEntityAttackDEF84(void *, u16, u16, s32);
s8 func_800E2400(void *, u16, u16, u32);
s8 func_800DF214(void *, u16);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800DF3E4 */
s8 func_800DF3E4(void *, void *, u16, f32);
#endif
s8 func_800DFDD4(void *, void *, u16, void *);
s8 func_800DF99C(void *, void *, u16, void *);
s8 func_800E022C(void *, void *, u16, void *);
s8 func_800E0590(void *, void *, u16, void *);
s8 func_800E074C(void *, u16, u16);
s8 func_800E06C0(void *, void *, s8);
void func_800BF548(void *, s32);
void updateEntityStunTimer(void *, void *, s32);

void func_8009DD60(void) {
    D_800EB408->flags |= 0x100000000000ULL;

    if (D_800FADCF & 0x40) {
        if (D_800EB408->flags & 0x4000) {
            if (D_800EB408->flags & 0x40) {
                func_800A6C48(D_800EB408, 0x17);
            }
            if (D_800EB408->flags & 0x80) {
                D_800EB408->dirIndex = D_800EB408->ringSide;
                func_800A6C48(D_800EB408, 0x61);
            }
            if (D_800EB408->flags & 0x100) {
                if (*(u16 *)(D_8007EF30 + 0x170) & 0x100) {
                    func_800A6C48(D_800EB408, 0x17);
                    return;
                }
                func_800A6C48(D_800EB408, 0x70);
            }
            return;
        }
        if (D_800EB408->flags & 0x140) {
            func_800A7240(D_800EB408, D_800F9B14, 0x155, 0x100000000ULL);
        }
        func_800D6658(D_800EB408, D_800EB40C, 0, 0, D_800F9B0C[0]);
        return;
    }

    if (D_800EB408->flags & 0x8000) {
        D_800EB408->flags |= 0x10000ULL;
    }
    if (selectNewLinkedTarget(D_800EB408, D_800FAF8A)) {
        return;
    }
    if (D_800EB408->flags & 0x8000) {
        if (D_800EB408->flags & 0x40) {
            func_800A6C48(D_800EB408, 0x82);
            return;
        }
        if (D_800EB408->flags & 0x80) {
            D_800EB408->dirIndex = D_800EB408->ringSide;
            func_800A6C48(D_800FAF5C, 0x60);
            return;
        }
    }
    if (updateSpecialMoveRequest(D_800EB408)) {
        func_800A6C48(D_800EB408, 0x7E);
        return;
    }
    if (*(u16 *)(D_8007EF30 + 0x170) & 4) {
        if (D_800EB408->flags & 0x100) {
            if (*(u16 *)(D_8007E228 + 0x58) & 0x100) {
                if (D_800EB408->flags & 0x200) {
                    func_800A6C48(D_800EB408, 0x70);
                    return;
                }
            }
            if (*(u16 *)(D_8007E228 + 0x58) & 0x200) {
                func_800A6C48(D_800EB408, 0x70);
                return;
            }
        }
    }
    if (D_800EB408->flags & 3) {
        if (!isEntityActionAllowedC2870(D_800EB408)) {
            if (D_800EB408->flags & 0x40) {
                func_800A6C48(D_800EB408, 0x90);
                return;
            }
            if (D_800EB408->flags & 0x80) {
                D_800EB408->dirIndex = D_800EB408->ringSide;
                func_800A6C48(D_800FAF5C, 0x60);
                return;
            }
        }
    }

    if (D_800EB408->flags & 0x10) {
        D_800FABE6 = 0;
        D_800FAF8A = 0;
        D_800FAF78 = 0;
    }
    if (*(u16 *)(D_8007EF30 + 0x170) & 0x400) {
        if (D_800EB408->flags & 0x100) {
            if (!(D_800EB408->flags & 0x8000)) {
                D_800EB408->flags |= 0x1000000800ULL;
                D_800FABE6 = 0;
                D_800FAF8A = 0;
                D_800FAF78 = 0;
            }
        }
    }
    if (D_800EB408->flags & 0x140) {
        func_800A7240(D_800EB408, D_800F9B14, 0x155, 0x100000000ULL);
    }

    D_800EB408->knockdowns = 0;
    D_800F9D08[D_800FADB8] = 0;
    D_800EB408->steppedOverId = -1;
    func_800BF548(D_800EB408, 1);
    updateEntityStunTimer(D_800EB408, D_800EB40C, 1);
    func_800D93DC(D_800EB408);
    {
        u32 r = func_800D6658(D_800EB408, D_800EB40C, D_800FABE6, 0, D_800F9B0C[0]);
        u32 s1 = r;
        u32 s0 = s1 & 0xFFFF;
        void *p;
        if (s0) {
            if (((s8 (*)(void *, s32, s32, s32))func_800DECAC)(D_800EB408, D_800FABE6, s0, 1)) {
                return;
            }
            if (func_800DF5C4(D_800EB408, D_800EB40C, D_800FAF8A, D_800FABE6,
                              D_800FAF78, s0)) {
                return;
            }
            if (func_800DE9C0(D_800EB408, D_800EB40C, D_800FABE6, D_800FAF8A, s0)) {
                return;
            }
            if (tryEntityAttackDEF84(D_800EB408, D_800FABE6, D_800FAF8A, s0)) {
                return;
            }
        }
        if (s1 >> 16) {
            if (func_800E2400(D_800EB408, D_800FABE6, D_800FAF8A, s1 >> 16)) {
                return;
            }
        }
        if (func_800DF214(D_800EB408, D_800FABE6)) {
            return;
        }
        if (func_800DF3E4(D_800EB408, D_800EB40C, D_800FABE6, D_800F9B0C[0])) {
            return;
        }
        p = D_800F9B0C - 1;
        if (func_800DFDD4(D_800EB408, D_800EB40C, D_800FABE6, p)) {
            return;
        }
        if (func_800DF99C(D_800EB408, D_800EB40C, D_800FABE6, p)) {
            return;
        }
        if (func_800E022C(D_800EB408, D_800EB40C, D_800FABE6, p)) {
            return;
        }
        if (func_800E0590(D_800EB408, D_800EB40C, D_800FABE6, p)) {
            return;
        }
        if (func_800E074C(D_800EB408, D_800FABE6, D_800FAF8A)) {
            return;
        }
        func_800E06C0(D_800EB408, D_800EB40C, D_800FAF78);
    }
}
