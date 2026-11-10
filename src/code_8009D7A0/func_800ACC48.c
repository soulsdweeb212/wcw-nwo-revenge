/* @header
 * func_800ACC48
 * VRAM 0x800ACC48 | ROM 0xA00E8 | size 0x5D0
 * asm: asm/nonmatchings/code_8009D7A0/func_800ACC48.s
 */
#include "common.h"

extern u8 D_800FABE4;
extern u8 D_800FADB8;
extern u16 D_800FABE6;
extern u16 D_800FAF8A;
extern s16 D_800EB420[];
extern s16 D_800EB430[];
extern s16 D_800EB440[];
extern s16 D_800EB450[];

void func_800D427C(void *, s16, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s32);
#endif
void func_800D43B4(void *, s16, s32);
void tryApplyHitReaction(void *, void *, u16, u16);
void func_800AD574(void *, void *, u16);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800A6BE0(void *, s32);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
void func_800D7E80(void *, void *);
s8 func_800D8D74(void *, s32);
s32 func_800C472C(void *, void *, s32);
void func_800B68A0();

void func_800ACC48(void) {
    register s16 r;
    Wrestler *o;

    func_800D2BAC(D_800FAF5C, D_800F9B00, 2.0f, 0xFFFFE);
    switch (D_800FAF5C->step) {
    case 0:
        func_800D427C(D_800FAF5C, D_800EB430[(s8)D_800FABE4], 3);
        D_800FAF5C->step++;
        break;
    case 1:
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D427C(D_800FAF5C, D_800EB440[(s8)D_800FABE4], 3);
            D_800FAF5C->step += 1;
        }
        break;
    case 2:
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D43B4(D_800FAF5C, D_800EB440[(s8)D_800FABE4], 3);
        }
        break;
    case 4:
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D43B4(D_800FAF5C, D_800EB440[(s8)D_800FABE4], 3);
        }
        tryApplyHitReaction(D_800F9B00, D_800FAF5C, D_800FABE6, D_800FAF8A);
        o = D_800FAF5C;
        if (o->pairSignals & 4) {
            o->pairSignals &= ~4;
            if (o->pairSignals & 2) {
                if (D_800EB420[(s8)D_800FABE4] == 0 && !(D_800F9B00->grappleCtx & 0x400000)) {
                    if (o->move.moveCode) {
                        r = func_800D5438(o, 0);
                        func_800D43B4(D_800FAF5C, r, 2);
                        func_800D7E80(D_800FAF5C, D_800F9B00);
                    } else {
                        r = func_800D5438(o, 0);
                        func_800D43B4(D_800FAF5C, r, 1);
                    }
                    D_800FAF5C->step = 6;
                } else {
                    r = func_800D5438(D_800FAF5C, 0);
                    func_800D43B4(D_800FAF5C, r, 1);
                    func_800B68A0(D_800FAF5C, D_800FAF5C, D_800F9B00);
                    D_800FAF5C->step++;
                }
                func_800A7F6C(D_800FAF5C, 0x2B);
                func_800A837C(D_800FAF5C);
                goto finish;
            }
        } else {
            break;
        }
        func_800B68A0(D_800F9B00, D_800F9B00);
        if ((func_800C472C(D_800F9B00, D_800FAF5C, 0) << 24) != 0) {
            D_800FAF5C->flags &= ~0x08000000ULL;
            break;
        }
        r = func_800D5438(D_800F9B00, 1);
        func_800D43B4(D_800FAF5C, r, 1);
        D_800FAF5C->step++;
finish:
        o = D_800FAF5C;
        o->pairSignals &= ~2;
        o->flags |= WR_FLAG_RERUN;
        break;
    case 5:
        if (D_800FAF5C->animFramesLeft > 0) {
            break;
        }
        if (D_800EB420[(s8)D_800FABE4] == 0 || D_800F9B00->state != 0x4B) {
            func_800D4AD0(D_800FAF5C);
            beginEntityActionA8D8C(D_800FAF5C);
            break;
        }
        if (D_800F9B00->grappleCtx & 0x400000) {
    case 3:
            func_800D4AD0(D_800FAF5C);
            beginEntityActionA8D8C(D_800FAF5C);
            break;
        }
        func_800D427C(D_800FAF5C, D_800EB440[(s8)D_800FABE4], 3);
        D_800FAF5C->step = 2;
        D_800FAF5C->flags |= WR_FLAG_RERUN;
        break;
    case 6:
        if (D_800FAF5C->move.moveCode && (func_800D8D74(D_800FAF5C, 0) << 24) == 0) {
            break;
        }
        func_800A6BE0(D_800FAF5C, 0x53);
        func_800A6BE0(D_800F9B00, 0x54);
        D_800FAF5C->flags |= WR_FLAG_PAIR_LEADER;
        D_800F9B00->flags &= ~WR_FLAG_PAIR_LEADER;
        D_800FAF5C->attached[0] = D_800FABE4;
        D_800F9B00->attached[0] = -1;
        D_800F9B00->heldById = D_800FADB8;
        break;
    case 7:
        D_800FAF5C->flags &= ~0x07800000ULL;
        func_800D427C(D_800FAF5C, D_800EB450[(s8)D_800FABE4], 3);
        *(volatile s16 *)&D_800FAF5C->step += 1;
    case 8:
        func_800AD574(D_800F9B00, D_800FAF5C, D_800FAF8A);
        if (D_800FAF5C->animFramesLeft <= 0) {
            r = func_800D5438(D_800F9B00, 1);
            func_800D427C(D_800FAF5C, r, 1);
            func_800A6BE0(D_800FAF5C, 0x52);
        }
        break;
    }
}
