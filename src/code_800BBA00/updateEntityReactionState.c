/* @header
 * updateEntityReactionState  (originally func_800C94CC)
 * VRAM 0x800C94CC | ROM 0xBC96C | size 0x4A4
 * asm: asm/nonmatchings/code_800BBA00/updateEntityReactionState.s
 */
#include "common.h"

/* Wrestler reaction/block state machine (steps 0..6). The reacting wrestler
 * (self, D_800FAF5C) responds to its opponent's pairSignals (D_800F9B00): it
 * plays reaction animations (func_800D427C), keeps the pair aligned
 * (func_800D2BEC / func_800D2B64), and on a counter reaction swaps the 0x40000000
 * pair-leader flag between the two and repoints the opponent's heldById and
 * opponentId at self before releasing the pair. */
extern u8 D_800FABE4;
extern u8 D_800FADB8;
extern s8 D_800FAF78;
extern u16 D_800FAF8A;
void func_800A6BE0(void *, s32);
void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void beginEntityActionA8D8C(void *);
void func_800B68A0(void *, void *, void *);
s16 func_800B6DEC(void *, void *, s32);
void func_800C472C(void *, void *, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
s32 func_800D2B64(void *, f32, u16, s32);
#endif
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s32);
#endif
s16 func_800D7690(void *, s32, s32);
s32 func_800D7894(void *, u16);

void updateEntityReactionState(void) {
    s32 animId;
    u16 opponentSignals;

    switch (D_800FAF5C->step) {
    case 0:
        if (D_800F9B00->pairSignals & 8) {
            D_800FAF5C->step = 6;
            animId = 0x10D1;
        } else {
            D_800FAF5C->step++;
            animId = 0x10C1;
        }
        func_800D427C(D_800FAF5C, animId, 3);
        break;
    case 1:
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D427C(D_800FAF5C, 0x10C3, 1);
            D_800FAF5C->escapeTimer = func_800B6DEC(D_800FAF5C, D_800F9B00, 6);
            func_800D7690(D_800FAF5C, 0, 0);
            D_800FAF5C->step++;
        }
        break;
    case 2:
        D_800FAF5C->flags |= 0x400000000000ULL;
        func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 4.0f, 0, 0xFFFFE);
        opponentSignals = D_800F9B00->pairSignals;
        if (opponentSignals & 1) {
            func_800D427C(D_800FAF5C, 0x10C5, 1);
            D_800FAF5C->step++;
            break;
        }
        if (opponentSignals & 0x10) {
            animId = (D_800FAF5C->flags & 0x8000000) ? 0x10CF : 0x10CB;
            func_800D427C(D_800FAF5C, animId, 1);
            D_800FAF5C->step = 4;
            break;
        }
        if (opponentSignals & 4) {
            func_800D427C(D_800FAF5C, 0x10C7, 1);
            D_800FAF5C->step = 5;
            break;
        }
        if (opponentSignals & 2) {
            func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 1);
            func_800A6BE0(D_800FAF5C, 0x53);
            func_800A6BE0(D_800F9B00, 0x54);
            D_800FAF5C->flags |= 0x40000000;
            D_800F9B00->flags &= ~0x40000000;
            D_800FAF5C->attached[0] = D_800FABE4;
            D_800F9B00->attached[0] = -1;
            D_800F9B00->heldById = D_800FADB8;
            D_800F9B00->opponentId = D_800FADB8;
            func_800A7F6C(D_800FAF5C, 0);
            func_800A837C(D_800FAF5C);
        } else {
            if (func_800D7894(D_800FAF5C, D_800FAF8A) << 24) {
                if (D_800FAF78) {
                    D_800FAF5C->escapeTimer = 0;
                } else {
                    if (D_800FAF5C->flags & 9) {
                        D_800F9B00->pairSignals |= 1;
                    } else {
                        D_800F9B00->pairSignals |= 2;
                        func_800A7C40(D_800FAF5C, D_800FADB8, 0x8F);
                    }
                }
            }
        }
        break;
    case 4:
        func_800D2B64(D_800FAF5C, 2.0f, 0, 2);
        if (D_800FAF5C->animFramesLeft <= 0) {
            D_800FAF5C->opponentId = D_800FAF5C->secondAttackerId;
            func_800B68A0(D_800F9B64, D_800F9B64, D_800FAF5C);
            func_800D4AD0(D_800FAF5C);
            beginEntityActionA8D8C(D_800FAF5C);
            func_800C472C(D_800F9B64, D_800FAF5C, 2);
        }
        break;
    case 3:
    case 5:
    case 6:
        func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 4.0f, 0, 0xFFFFE);
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    }
}
