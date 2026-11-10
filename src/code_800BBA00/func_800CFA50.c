/* @header
 * func_800CFA50
 * VRAM 0x800CFA50 | ROM 0xC2EF0 | size 0x6AC
 * asm: asm/nonmatchings/code_800BBA00/func_800CFA50.s
 */
#include "common.h"

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
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s32);
#endif
void func_800A6BE0(void *, s32);
void beginPairedEntityActions(void *, s32, void *, s32);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D4AD0(void *);

void func_800CFA50(void) {
    switch (D_800FAF5C->step) {
    case 0:
        D_800FAF5C->flags &= 0xFFFFFFFFF87FFFFFULL;
        selectTurnAnimationCDC04(D_800FAF5C, D_800F9B00);
        D_800FAF5C->stateTimer = 0;
        D_800FAF5C->step++;
        /* fall through */
    case 1: {
        Wrestler *nw;
        Wrestler *b;
        s32 inc;
        func_800D0700(D_800FAF5C, D_800F9B00, D_800FAF8A);
        nw = D_800FAF5C;
        nw->stateTimer++;
        b = D_800F9B00;
        if (D_800EB628[nw->id] < (s16)nw->stateTimer) {
            nw->heading = D_800EB610[nw->id];
            if (b->grappleCtx & 0x100000) {
                nw->step = 7;
            }
            inc = 1;
        } else {
            if (b->grappleCtx & 0x200) {
                translateEntityXZ(nw, nw->moveDelta);
            }
            nw->heading = func_800D35B0(nw->heading, nw->turnPerTick);
            inc = 0;
        }
        {
            u16 res;
            if (res = inc) {
                D_800FAF5C->step++;
            }
        }
        break;
    }
    case 2:
        func_800D0700(D_800FAF5C, D_800F9B00, D_800FAF8A);
        D_800FAF5C->stateTimer++;
        if (D_800F9B00->pairSignals & 1) {
            func_800D427C(D_800FAF5C, (s16)(D_800F9B00->animId + 1), 1);
            D_800FAF5C->step = 7;
        }
        if (D_800F9B00->pairSignals & 2) {
            D_800FAF5C->step++;
        }
        if (D_800F9B00->pairSignals & 8) {
            D_800FAF5C->step = 9;
        }
        break;
    case 3:
        D_800FAF5C->step++;
        /* fall through */
    case 4:
        if (D_800F9B00->state == 0x45) {
            if (!(D_800F9B00->pairSignals & 2)) {
                D_800FAF5C->step -= 2;
                break;
            }
        }
        if (D_800F9B00->pairSignals & 4) {
            func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 1);
            func_800A6BE0(D_800FAF5C, 0x49);
            func_800A6BE0(D_800F9B00, 0x4A);
            D_800FAF5C->flags |= WR_FLAG_PAIR_LEADER;
            D_800F9B00->flags &= ~WR_FLAG_PAIR_LEADER;
            D_800FAF5C->attached[0] = D_800FABE4;
            D_800F9B00->attached[0] = -1;
            D_800F9B00->heldById = D_800FADB8;
            D_800FAF5C->grappleCtx = D_800F9B00->grappleCtx;
            break;
        }
        if (D_800F9B00->grappleCtx & 0x80) {
            if (D_800F9B00->move.flags & 0x100000) {
                s16 anim;
                if (*(u64 *)(D_800F9B00->profile + 0x38) & 0x1000000000ULL) {
                    anim = 0xEC2;
                } else {
                    anim = 0xEC2;
                }
                func_800D427C(D_800FAF5C, anim, 1);
                D_800FAF5C->step++;
                break;
            }
        }
        D_800FAF5C->step = 6;
        D_800FAF5C->flags |= WR_FLAG_RERUN;
        break;
    case 5:
        if (D_800FAF5C->animFramesLeft == 1) {
            D_800FAF5C->step++;
        }
        break;
    case 6:
        if (D_800F9B00->grappleCtx & 0xC0) {
            func_800D427C(D_800FAF5C, func_800D5438(D_800F9B00, 1), 1);
        } else {
            func_800D427C(D_800FAF5C, func_800D5438(D_800F9B00, 1), 3);
        }
        func_800A6BE0(D_800FAF5C, 0x4A);
        break;
    case 7:
        if (!(D_800F9B00->grappleCtx & 0x380)) {
            func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 1.0f, 0, 2);
        }
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    case 8:
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            func_800D427C(D_800FAF5C, 0xE8E, 1);
            D_800FAF5C->flags &= 0xFFFFFFFFF87FFFFFULL;
            D_800F9B00->flags &= 0xFFFFFFFFF87FFFFFULL;
            beginPairedEntityActions(D_800FAF5C, 0x45, D_800F9B00, 0x46);
            D_800FAF5C->step = 2;
            D_800F9B00->step = 2;
            D_800F9B00->stateTimer = 0;
            D_800F9B00->grappleCtx &= 0x402;
            D_800FAF5C->grappleCtx = D_800F9B00->grappleCtx | 0x40;
            if (D_800FAF5C->grappleCtx & 2) {
                D_800FAF5C->stateTimer = 0x5A;
            } else {
                D_800FAF5C->stateTimer = 0x3C;
            }
        }
        break;
    case 9:
        func_800D427C(D_800FAF5C, 0xEA1, 3);
        D_800FAF5C->step++;
        break;
    case 10:
        func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 1.0f, 0, 2);
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            D_800FAF5C->stateTimer = 0;
            D_800FAF5C->flags &= 0xFFFFFFFFF87FFFFFULL;
            func_800D427C(D_800FAF5C, 0xE8F, 1);
            D_800FAF5C->step = 2;
        }
        break;
    }
}
