/* @header
 * func_800CA114
 * VRAM 0x800CA114 | ROM 0xBD5B4 | size 0x1E8
 * asm: asm/nonmatchings/code_800BBA00/func_800CA114.s
 */
#include "common.h"

void func_800A9290(void *);
s8 func_800D4CC4(void *);
void func_800D4AD0(void *);
void func_800D427C(void *, s16, s32);

/* 'Get-up / recovery' action for self (D_800FAF5C). Step 0 enters the pose
 * and raises the 0x1000000000 flag. Step 1 waits for the pairSignals bits: bit 1
 * skips to step 3 and lights 0x10000000, bit 0 starts the animation after the
 * opponent's (D_800F9B00) animId and advances. Step 2 re-raises the flag and, when
 * animFramesLeft runs out, drops the pose, advances, and lights 0x10000000. Step 3
 * restarts the animation after the opponent's (variant 1 or 6 depending on bit 0)
 * and advances. Step 4 finishes into state 0x39 when pairSignals has bit 2. */
void func_800CA114(void) {
    switch (D_800FAF5C->step) {
    case 0:
        func_800A9290(D_800FAF5C);
        D_800FAF5C->step++;
        /* fall through */
    case 1:
        D_800FAF5C->flags |= 0x1000000000ULL;
        if (D_800FAF5C->pairSignals & 2) {
            D_800FAF5C->step = 3;
            D_800FAF5C->flags |= 0x10000000;
        } else if (D_800FAF5C->pairSignals & 1) {
            func_800D427C(D_800FAF5C, (s16)(D_800F9B00->animId + 1), 6);
            D_800FAF5C->step++;
        }
        break;
    case 2:
        D_800FAF5C->flags |= 0x1000000000ULL;
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4CC4(D_800FAF5C);
            func_800D4AD0(D_800FAF5C);
            D_800FAF5C->step++;
            D_800FAF5C->flags |= 0x10000000;
        }
        break;
    case 3:
        if (D_800FAF5C->pairSignals & 2) {
            if (D_800FAF5C->pairSignals & 1) {
                func_800D427C(D_800FAF5C, (s16)(D_800F9B00->animId + 1), 1);
            } else {
                func_800D427C(D_800FAF5C, (s16)(D_800F9B00->animId + 1), 6);
            }
            D_800FAF5C->step++;
        }
        break;
    case 4:
        if (D_800FAF5C->pairSignals & 4)
            func_800A6C48(D_800FAF5C, 0x39);
        break;
    }
}
