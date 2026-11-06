/* @header
 * updatePairedEntityStateA4AD8  (originally func_800A4AD8)
 * VRAM 0x800A4AD8 | ROM 0x97F78 | size 0x29C
 * asm: asm/nonmatchings/code_8009D7A0/updatePairedEntityStateA4AD8.s
 */
#include "common.h"

/* Paired-entity action state machine: steps the global entity pair
 * (D_800EB408 self / D_800EB40C opponent) through steps 0..4.
 * Step 0 kicks off the shared action (0xEBF) and step 1 waits for the
 * ready callback (func_800D8D74). Step 2 watches controller bits
 * (D_800FABE6 & 0xC000) together with the opponent's moveId (0x9B/0x9C)
 * and the pairSignals words to decide when both actors begin the paired
 * animation (beginPairedEntityActions with actions 0x5D/0x5E). Steps 3/4
 * play it out and tear the pair down. */
extern u16 D_800FABE6;

void func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D7E80(void *, void *);
s8 func_800D8D74(void *, s32);
void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void beginPairedEntityActions(void *, s32, void *, s32);
s16 func_800D5438(void *, s16);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
void func_800C472C(void *, void *, s32);

void updatePairedEntityStateA4AD8(void) {
    func_800D2BEC(D_800EB408, D_800EB40C, 0, 4.0f, 0, 0xFFFFE);
    switch (D_800EB408->step) {
    case 0:
        func_800D427C(D_800EB408, 0xEBF, 2);
        func_800D7E80(D_800EB408, D_800EB40C);
        D_800EB408->step++;
    case 1:
        if ((s8)func_800D8D74(D_800EB408, 0)) {
            D_800EB408->step++;
        }
        break;
    case 2:
        if (!(D_800EB40C->pairSignals & 0x2))
            goto start_pair;
        if (D_800FABE6 & 0xC000) {
            if ((D_800FABE6 & 0xC000) != 0xC000) {
                if (D_800FABE6 & 0x8000) {
                    if (D_800EB40C->moveId == 0x9B) {
                        D_800EB408->pairSignals |= 8;
                    }
                }
                if (D_800FABE6 & 0x4000) {
                    if (D_800EB40C->moveId == 0x9C) {
                        D_800EB408->pairSignals |= 8;
                    }
                }
            }
        }
        if (!(D_800EB408->pairSignals & 0x8)) {
            D_800EB408->step++;
            break;
        }
start_pair:
        if (D_800EB40C->pairSignals & 0x4)
            goto begin_anim;
        if (!(D_800EB408->pairSignals & 0x8))
            break;
begin_anim:
        func_800A7C40(D_800EB408, D_800EB408->id, 0x9A);
        func_800A7F6C(D_800EB408, 0);
        func_800A837C(D_800EB408);
        beginPairedEntityActions(D_800EB408, 0x5D, D_800EB40C, 0x5E);
        D_800EB408->step = 3;
        D_800EB40C->step = 3;
        break;
    case 3:
        func_800D427C(D_800EB408, func_800D5438(D_800EB40C, 1), 2);
        D_800EB408->step++;
        break;
    case 4:
        if (D_800EB408->animFramesLeft <= 0) {
            func_800D4AD0(D_800EB408);
            beginEntityActionA8D8C(D_800EB408);
            func_800C472C(D_800EB40C, D_800EB408, 2);
        }
        break;
    }
}
