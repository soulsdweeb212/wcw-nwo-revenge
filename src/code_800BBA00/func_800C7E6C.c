/* @header
 * func_800C7E6C
 * VRAM 0x800C7E6C | ROM 0xBB30C | size 0x31C
 * asm: asm/nonmatchings/code_800BBA00/func_800C7E6C.s
 */
#include "common.h"

extern s8 D_800FADB8;

void func_800A9290(void *);
void func_800D427C(void *, s16, s32);
s16 func_800BF2FC(void *);
s8 func_800B71F8(void *, s32, s32);
s8 func_800D4198(s16);
void func_800A7C40(void *, s8, s16);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
s16 func_800D5438(void *, s32);
void beginPairedEntityActions(void *, s32, void *, s32);

/* Five-step paired grapple/throw on D_800FAF5C->step.  Step 0 calls
 * func_800A9290 and falls into step 1, which raises flag 0x1000000000 and, when
 * the opponent's (D_800F9B00) pairSignals bit0 is set, sends the contact animation
 * opponent animId+1 and optionally performs a counter via func_800B71F8(0xC) on a
 * low-range opponent (func_800BF2FC < 0x81), setting the opponent's pairSignals
 * bit1.  Step 2 animates the impact (opponent animId-1, then re-sends 0x44/0x45 for
 * animId 0xF56/0xF58) or the follow-up (own animId+4).  Step 3 ends it: for animId
 * 0xF56/0xF58 it sends 0xE8F and copies the opponent's heading before advancing,
 * otherwise it finishes with beginEntityActionA8D8C or func_800A6C48(0x2B).  Step 4
 * starts the paired throw (0x53/0x54) and sets grappleCtx to 0x440/0x442 on both. */
void func_800C7E6C(void) {
    switch (D_800FAF5C->step) {
    case 0:
        func_800A9290(D_800FAF5C);
        D_800FAF5C->step++;
        /* fallthrough */
    case 1:
        D_800FAF5C->flags |= 0x1000000000ULL;
        if (!(D_800F9B00->pairSignals & 1)) {
            break;
        }
        func_800D427C(D_800FAF5C, (s16)(D_800F9B00->animId + 1), 6);
        if (!(D_800FAF5C->flags & 9)) {
            if ((s16)func_800BF2FC(D_800FAF5C) < 0x81) {
                if (func_800B71F8(D_800FAF5C, 0, 0xC)) {
                    D_800F9B00->pairSignals |= 2;
                }
            }
        }
        D_800FAF5C->step++;
        break;
    case 2:
        if (D_800FAF5C->animFramesLeft <= 0) {
            if (D_800F9B00->pairSignals & 2) {
                func_800D427C(D_800FAF5C, (s16)(D_800F9B00->animId - 1), 1);
                if (D_800FAF5C->animId == 0xF56) {
                    func_800A7C40(D_800FAF5C, D_800FADB8, (func_800D4198(0x2EE) == 0) ? 0x45 : 0x44);
                } else if (D_800FAF5C->animId == 0xF58) {
                    func_800A7C40(D_800FAF5C, D_800FADB8, (func_800D4198(0x2EE) == 0) ? 0x45 : 0x44);
                }
            } else {
                func_800D427C(D_800FAF5C, (s16)(D_800FAF5C->animId + 4), 0);
            }
            D_800FAF5C->step++;
        }
        break;
    case 3:
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            if (D_800FAF5C->animId == 0xF56 || D_800FAF5C->animId == 0xF58) {
                func_800D427C(D_800FAF5C, 0xE8F, 1);
                D_800FAF5C->heading = D_800F9B00->heading;
                D_800FAF5C->step++;
            } else if (D_800FAF5C->animId < 0xF52) {
                beginEntityActionA8D8C(D_800FAF5C);
            } else {
                func_800A6C48(D_800FAF5C, 0x2B);
            }
        }
        break;
    case 4:
        func_800D427C(D_800FAF5C, (s16)func_800D5438(D_800FAF5C, 0), 1);
        beginPairedEntityActions(D_800FAF5C, 0x53, D_800F9B00, 0x54);
        D_800FAF5C->grappleCtx = 0x440;
        if (D_800FAF5C->moveId == 0x45) {
            D_800FAF5C->grappleCtx = 0x442;
        }
        D_800F9B00->grappleCtx = D_800FAF5C->grappleCtx;
        break;
    }
}
