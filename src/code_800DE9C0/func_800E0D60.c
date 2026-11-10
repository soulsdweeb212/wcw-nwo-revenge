/* @header
 * func_800E0D60
 * VRAM 0x800E0D60 | ROM 0xD4200 | size 0x698
 * asm: asm/nonmatchings/code_800DE9C0/func_800E0D60.s
 */
#include "common.h"

extern u16 D_800FABE6;
extern s8 D_800FADB8;
extern s16 D_800FADBE[];
extern s16 D_800F9B70[];
extern u16 D_800FAF8E[];
extern s8 D_800FAF78;
extern u16 D_800FAF8A;
extern s32 D_800F9B14;

void func_800D25D0(Wrestler *, f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
s32 func_800D2B64(Wrestler *, s32, u16, s32);
#endif
void func_800D427C(Wrestler *, s16, s32);
void func_800D4AD0(Wrestler *);
s8 func_800D8DF0(Wrestler *);
s16 updateEntityHealthLevel(Wrestler *);
#ifdef TARGET_PC
/* PC: func_800E1560 with its definition's types: a third parameter, the animation to start (see step 3). */
void func_800E1560(Wrestler *w, s32 targetHeading, s32 a2);
#else
void func_800E1560(Wrestler *, s32);
#endif
s8 func_800A93C0(void);
s32 func_800D35B0(s32, s32);
s8 selectNewLinkedTarget(void *, s32);
void func_800A7240(Wrestler *, s32, s32, u64);

void func_800E0D60(void) {
    func_800D25D0(D_800FAF5C, 4.0f);
#ifdef TARGET_PC
    /* PC: func_800D2B64 takes a float as its second parameter (port_decls.h). The N64 code passes 0x40000000, the
     * bits of 2.0f, in a1, an integer register, where the N64 callee reads them as a float. On the PC the integer
     * would be converted to 1073741824.0f, so the PC passes 2.0f itself. */
    func_800D2B64(D_800FAF5C, 2.0f, 0, 0xFFFFE);
#else
    func_800D2B64(D_800FAF5C, 0x40000000, 0, 0xFFFFE);
#endif

    switch (D_800FAF5C->step) {
    case 0:
        func_800D427C(D_800FAF5C, updateEntityHealthLevel(D_800FAF5C), 6);
        D_800FADBE[D_800FADB8] = 0;
        D_800F9B70[D_800FADB8] = 0;
        D_800FAF8E[D_800FADB8] = 0;
        D_800FAF5C->stateTimer = 0x96;
        D_800FAF5C->flags &= 0xFEFFFFFFFFFFFFFFULL;
        D_800FAF5C->step++;
        /* fall through */
    case 1:
        if (D_800FAF5C->animFramesLeft > 0) {
            break;
        }
        func_800D4AD0(D_800FAF5C);
        if (!func_800A93C0() && (D_800FABE6 & 0x10) &&
            (func_800D8DF0(D_800FAF5C) || (D_800FAF5C->flags & WR_FLAG_ON_FLOOR))) {
            func_800D427C(D_800FAF5C, 0xF38, 1);
            D_800FAF5C->step++;
            break;
        }
        D_800FAF5C->step = 3;
        D_800FAF5C->flags |= 0x10000000ULL;
        break;
    case 2: {
        s32 id;
        selectNewLinkedTarget(D_800FAF5C, D_800FAF8A);
        id = D_800F9B14;
        func_800A7240(D_800FAF5C, id, 0x71, 0x100000000ULL);
        if (D_800FAF78) {
            func_800A6C48(D_800FAF5C, 0x17);
            D_800FAF5C->step = 2;
            return;
        }
        if ((D_800FABE6 & 0x20) && !(D_800FAF5C->flags & 1)) {
            func_800D427C(D_800FAF5C, 0xF39, 1);
            D_800FAF5C->step = 5;
            return;
        }
        D_800FAF5C->stateTimer--;
        if (D_800FABE6 & 0x10) {
            if (D_800FAF5C->stateTimer < 0 ||
                (!func_800D8DF0(D_800FAF5C) && (D_800FAF5C->flags & WR_FLAG_IN_RING))) {
                D_800FAF5C->step++;
                return;
            }
            if (D_800FABE6 & 0x8000) {
                if (D_800FAF5C->flags & 9) {
                    func_800A6C48(D_800FAF5C, 0x21);
                } else {
                    func_800A6C48(D_800FAF5C, 0x44);
                    D_800FAF5C->step = 7;
                }
                return;
            }
            if (D_800FABE6 & 0x4000) {
                func_800A6C48(D_800FAF5C, 0x21);
                return;
            }
            break;
        } else {
            D_800FAF5C->step++;
            break;
        }
    }
    case 3:
#ifdef TARGET_PC
        /* PC: the N64 call passes no third argument, so func_800E1560 gets whatever a2 holds (left over from
         * func_800D2B64, before the switch). It reads a2 only when D_800F98D8[w->id] is not one of the values
         * updateEntityHealthLevel stores there (0xF2D-0xF2F, 0xF33-0xF35, 0xF3B-0xF3E): for those it picks the
         * animation 0xF30, 0xF31 or 0xF32 itself. Only updateEntityHealthLevel writes D_800F98D8, and this state (0x43)
         * calls it for this wrestler in step 0, before step 3 is reached (func_800A6C48 starts a state at step 0), so
         * a2 is never read here: the PC passes 0. */
        func_800E1560(D_800FAF5C, D_800F9B14, 0);
#else
        func_800E1560(D_800FAF5C, D_800F9B14);
#endif
        D_800FAF5C->step++;
        break;
    case 4:
        D_800FAF5C->heading = func_800D35B0(D_800FAF5C->heading, D_800FAF5C->turnPerTick);
        if (D_800FAF5C->animFramesLeft <= 0) {
            D_800FAF5C->step = 6;
        }
        break;
    case 5:
        if (D_800FAF5C->animFramesLeft <= 0) {
            D_800FAF5C->step = 6;
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

    if (D_800FAF5C->step != 6) {
        return;
    }
    D_800FAF5C->flags &= 0xFFFFFDFFFFFFFFFFULL;
    func_800D4AD0(D_800FAF5C);
    if (func_800D8DF0(D_800FAF5C) || (D_800FAF5C->flags & WR_FLAG_ON_FLOOR)) {
        if (D_800FADBE[D_800FADB8]) {
            if (D_800FAF5C->flags & 9) {
                D_800FAF5C->flags |= 0x0100000000000000ULL;
                D_800F9B70[D_800FADB8] = D_800FADBE[D_800FADB8];
                func_800A6C48(D_800FAF5C, 0x1E);
            } else {
                func_800A6C48(D_800FAF5C, 0x44);
            }
            D_800FAF5C->step = 1;
            return;
        }
        if (D_800F9B70[D_800FADB8]) {
            func_800A6C48(D_800FAF5C, 0x1E);
            D_800FAF5C->step = 1;
            return;
        }
    }
    func_800A6C48(D_800FAF5C, 0x2B);
}
