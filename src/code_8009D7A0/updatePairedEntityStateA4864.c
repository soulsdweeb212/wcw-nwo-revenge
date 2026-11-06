/* @header
 * updatePairedEntityStateA4864  (originally func_800A4864)
 * VRAM 0x800A4864 | ROM 0x97D04 | size 0x274
 * asm: asm/nonmatchings/code_8009D7A0/updatePairedEntityStateA4864.s
 */
#include "common.h"

/* Paired-entity action state machine for D_800EB408 with its
 * opponent D_800EB40C (switch on step):
 *  0 -> start action 0xEBE (setup 0x21), pair the entities, fall through;
 *  1 -> wait for readiness; set stateTimer to 0x5A, or 0x1E when
 *       the opponent has WR_FLAG_SPECIAL, then advance;
 *  2 -> React: on controller bits D_800FAF8A & 0xC000 set pairSignals 2 and play
 *       clip 0x9B (bit 0x8000) or 0x9C, else count stateTimer down and set
 *       pairSignals 4 when it expires;
 *  3 -> play the reaction animation, advance;
 *  4 -> when the animation ends, end the pair: clear flag 0x40000000,
 *       run func_800A83DC and finish the action. */
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800D7E80(void *, void *);
s8 func_800D8D74(void *, s32);
void func_800A7C40(void *, s8, s16);
s16 func_800D5438(void *, s16);
void func_800B68A0(void *, void *, void *);
s8 func_800A83DC(void *, void *);
void func_800D4AD0(void *);
extern u16 D_800FAF8A;

void updatePairedEntityStateA4864(void) {
    s16 step;
    s16 anim;

    func_800D2BEC(D_800EB408, D_800EB40C, 0, 4.0f, 0, 0xFFFFE);
    step = D_800EB408->step;
    switch (step) {
    case 0:
        func_800D427C(D_800EB408, 0xEBE, 2);
        func_800A7F6C(D_800EB408, 0x21);
        func_800A837C(D_800EB408);
        func_800D7E80(D_800EB408, D_800EB40C);
        D_800EB408->step++;
    case 1:
        if ((s8)func_800D8D74(D_800EB408, 0)) {
            if (D_800EB40C->flags & WR_FLAG_SPECIAL) {
                D_800EB408->stateTimer = 0x1E;
            } else {
                D_800EB408->stateTimer = 0x5A;
            }
            D_800EB408->step++;
        }
        break;
    case 2:
        if (D_800FAF8A & 0xC000) {
            D_800EB408->pairSignals |= 2;
            anim = 0x9C;
            if (D_800FAF8A & 0x8000) {
                anim = 0x9B;
            }
            func_800A7C40(D_800EB408, D_800EB408->id, anim);
            D_800EB408->step++;
        } else {
            D_800EB408->stateTimer--;
            if (D_800EB408->stateTimer < 0) {
                D_800EB408->pairSignals |= 4;
            }
        }
        break;
    case 3:
        func_800D427C(D_800EB408, func_800D5438(D_800EB408, 0), 2);
        D_800EB408->step++;
        break;
    case 4:
        if (D_800EB408->animFramesLeft <= 0) {
            Wrestler *p;
            func_800B68A0(D_800EB408, D_800EB408, D_800EB40C);
            if ((s8)func_800A83DC(D_800EB408, D_800EB40C) == 0) {
                p = D_800EB408;
                p->attached[0] = -1;
                p->flags &= 0xFFFFFFFFBFFFFFFFULL;
                func_800D4AD0(D_800EB408);
                func_800A6C48(D_800EB408, 0x2B);
            }
        }
        break;
    }
}
