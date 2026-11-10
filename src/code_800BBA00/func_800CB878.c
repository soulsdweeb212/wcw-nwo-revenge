/* @header
 * func_800CB878
 * VRAM 0x800CB878 | ROM 0xBED18 | size 0x3D4
 * asm: asm/nonmatchings/code_800BBA00/func_800CB878.s
 */
#include "common.h"

extern u16 D_800FAF8A;
extern s8 D_800FAF78;

void func_800A9290(void *);
void func_800CBD5C(void *, void *, u16);
void func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
void func_800C472C(void *, void *, s32);
void func_800D427C(void *, s16, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s32 func_800D5438(void *, s32);
#endif
void beginPairedEntityActions(void *, s32, void *, s32);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
s8 func_800D7984(void *, u16, s8);
void func_800D43B4(void *, s16, s32);

/* Paired action state machine, steps 0..5 on self->step.  Self (D_800FAF5C) plays
 * a grab/throw sequence against its opponent (D_800F9B00): it raises its flag bit
 * 0x1000000000, waits on animFramesLeft, then advances the step and either re-sends
 * the animation (func_800D427C), starts a paired maneuvre
 * (func_800D2BEC/func_800D2BAC/beginPairedEntityActions), or returns self to
 * step 1 with flag 0x80000000000000 on completion.  The opponent's pairSignals bits
 * 1/2/4/8/0x20 select which branch runs, and D_800FAF78/D_800FAF8A feed the
 * proximity test func_800D7984. */
void func_800CB878(void) {
    switch (D_800FAF5C->step) {
    case 0:
        func_800A9290(D_800FAF5C);
        D_800FAF5C->step++;
        /* fall through */
    case 1: {
        u16 opponentSignals;
        D_800FAF5C->flags |= 0x1000000000ULL;
        func_800CBD5C(D_800FAF5C, D_800F9B00, D_800FAF8A);
        opponentSignals = D_800F9B00->pairSignals;
        if (opponentSignals & 1) {
            func_800D427C(D_800FAF5C, (s16)func_800D5438(D_800F9B00, 1), 6);
            D_800FAF5C->step++;
        } else if (opponentSignals & 2) {
            func_800D427C(D_800FAF5C, (s16)func_800D5438(D_800FAF5C, 0), 6);
            beginPairedEntityActions(D_800FAF5C, 0x3A, D_800F9B00, 0x3B);
            D_800FAF5C->step = 4;
            D_800F9B00->step = 2;
            func_800A7F6C(D_800FAF5C, 0);
            func_800A837C(D_800FAF5C);
        } else if (opponentSignals & 4) {
            func_800D427C(D_800FAF5C, (s16)(D_800F9B00->animId + 1), 6);
            D_800FAF5C->step = 3;
        }
        break;
    }
    case 2:
        func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 8.0f, 0, 0xFFFFE);
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            beginEntityActionA8D8C(D_800FAF5C);
            func_800C472C(D_800F9B00, D_800FAF5C, 2);
        }
        break;
    case 3:
        func_800D2BAC(D_800FAF5C, D_800F9B00, 4.0f, 0xFFFFE);
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D427C(D_800FAF5C, (s16)(D_800F9B00->animId + 1), 0);
            D_800FAF5C->step++;
        }
        break;
    case 4:
        if (func_800D7984(D_800FAF5C, D_800FAF8A, D_800FAF78)) {
            D_800FAF5C->pairSignals |= 0x10;
        }
        if (D_800FAF5C->animFramesLeft <= 0) {
            if (D_800F9B00->pairSignals & 0x20) {
                func_800D427C(D_800FAF5C, (s16)(D_800F9B00->animId + 1), 1);
                D_800FAF5C->step++;
            } else {
                func_800D43B4(D_800FAF5C, (s16)D_800FAF5C->animId, 1);
            }
        }
        func_800D2BAC(D_800FAF5C, D_800F9B00, 4.0f, 0xFFFFE);
        break;
    case 5:
        func_800D2BAC(D_800FAF5C, D_800F9B00, 4.0f, 0xFFFFE);
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            if (D_800FAF5C->pairSignals & 8) {
                func_800A6C48(D_800FAF5C, 0x2C);
                D_800FAF5C->step = 1;
            } else {
                D_800FAF5C->flags |= 0x80000000000000ULL;
                func_800A6C48(D_800FAF5C, 0x2B);
            }
        }
        break;
    }
}
