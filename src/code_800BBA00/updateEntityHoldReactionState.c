/* @header
 * updateEntityHoldReactionState  (originally func_800D1724)
 * VRAM 0x800D1724 | ROM 0xC4BC4 | size 0x438
 * asm: asm/nonmatchings/code_800BBA00/updateEntityHoldReactionState.s
 */
#include "common.h"

/* Entity hold reaction state machine (steps 0..3). Self (D_800FAF5C)
 * reacts to its opponent D_800F9B00's pairSignals: it aligns to the opponent
 * (func_800D2BAC/func_800D2BEC), takes over the pair-leader flag and attached[0]
 * slot, and releases the hold when the animation finishes. */
extern u8 D_800FABE4;
extern u16 D_800E3CD0[];

void func_800A6BE0(void *, s32);
void beginEntityActionA8D8C(void *);
void func_800B68A0(void *, void *, void *);
void func_800C472C(void *, void *, s32);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
s16 findBoundaryQuadrant(void *, void *, s32);
void func_800D427C(void *, s16, s32);
void func_800D43B4(void *, s16, s32);
void func_800D4AD0(void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s32);
#endif

void updateEntityHoldReactionState(void) {
    D_800FAF5C->flags |= 0x1000000000ULL;
    switch (D_800FAF5C->step) {
    case 0:
        func_800D427C(D_800FAF5C, func_800D5438(D_800F9B00, 1), 2);
        D_800FAF5C->lastMoveTakenParam = (s8)D_800F9B00->move.unk3A4;
        D_800FAF5C->step++;
        /* fallthrough */
    case 1:
        if (!(D_800F9B00->pairSignals & 0x40)) {
            func_800D2BAC(D_800FAF5C, D_800F9B00, 1.0f, 2);
        }
        if (D_800F9B00->pairSignals & 8) {
            D_800F9B00->flags &= ~WR_FLAG_PAIR_LEADER;
            D_800FAF5C->flags |= WR_FLAG_PAIR_LEADER;
            D_800F9B00->attached[0] = -1;
            D_800FAF5C->attached[0] = D_800FABE4;
            func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 1);
            func_800A6BE0(D_800FAF5C, 0x49);
            break;
        }
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D43B4(D_800FAF5C, func_800D5438(D_800F9B00, 1), 3);
            D_800FAF5C->step++;
        }
        break;
    case 2:
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D43B4(D_800FAF5C, func_800D5438(D_800F9B00, 1), 0);
        }
        if (D_800F9B00->move.flags & 0x1000) {
            if (D_800F9B00->move.flags & 0x40000) {
                s16 r = findBoundaryQuadrant(D_800FAF5C, &D_800FAF5C->jointA[D_800F9B00->move.targetJoint], 1);
                if (r != -1 && r == D_800FAF5C->dirIndex) {
                    D_800F9B00->pairSignals |= 1;
                }
            }
            if (!(D_800F9B00->pairSignals & 0x40)) {
                func_800D2BAC(D_800FAF5C, D_800F9B00, 1.0f, 2);
            }
        } else {
            s32 r = func_800D2BAC(D_800FAF5C, D_800F9B00, 1.0f, 2);
            if (r & 0xFFFF) {
                if ((D_800F9B00->move.flags & 0x40000) && (D_800E3CD0[D_800F9B00->dirIndex] & r)) {
                    D_800F9B00->pairSignals |= 1;
                }
            }
        }
        if (D_800F9B00->pairSignals & 2) {
            func_800D427C(D_800FAF5C, func_800D5438(D_800F9B00, 3), 3);
            D_800FAF5C->step++;
        }
        break;
    case 3:
        if (D_800FAF5C->anim.unk372[2] != 1) {
            func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 4.0f, 0, 2);
        }
        if (D_800FAF5C->animFramesLeft == 1) {
            func_800B68A0(D_800F9B00, D_800F9B00, D_800FAF5C);
        }
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            beginEntityActionA8D8C(D_800FAF5C);
            {
                s16 tmp = D_800FAF5C->lastMoveTakenParam;
                func_800C472C(D_800F9B00, D_800FAF5C, 2);
                D_800FAF5C->lastMoveTakenParam = tmp;
            }
        }
        break;
    }
}
