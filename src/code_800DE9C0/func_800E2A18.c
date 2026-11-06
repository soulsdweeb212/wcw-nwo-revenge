/* @header
 * func_800E2A18
 * VRAM 0x800E2A18 | ROM 0xD5EB8 | size 0xF8
 * asm: asm/nonmatchings/code_800DE9C0/func_800E2A18.s
 */
#include "common.h"

extern s8 D_800F98E0[][0x30];    /* 4 slots (stride 0x30), [0] = type set by func_800E1920 (-1 = free) */

/* Slot availability check: count the occupied wrestler records (D_800F9D10[i].characterId != -1) and the free
 * D_800F98E0 slots. Returns the index of the first free slot when there are more free slots than empty records
 * (4 - occupied), else -1. */
s8 func_800E2A18(void) {
    s16 emptyCount;
    s16 i;
    s16 slot;
    s16 usedCount;
    s8 stateId;

    usedCount = 0;
    for (i = 0; i < 4; i++) {
        if (-1 != D_800F9D10[i].characterId) {
            usedCount++;
        }
    }
    emptyCount = 0;
    slot = -1;
    for (i = 0; i < 4; i++) {
        stateId = D_800F98E0[i][0];
        if (stateId == -1) {
            emptyCount++;
            if (slot == stateId) {
                slot = i;
            }
        }
    }
    if (emptyCount <= 4 - usedCount) {
        return -1;
    }
    return slot;
}
