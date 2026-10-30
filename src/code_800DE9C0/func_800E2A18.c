/* @header
 * func_800E2A18
 * VRAM 0x800E2A18 | ROM 0xD5EB8 | size 0xF8
 * asm: asm/nonmatchings/code_800DE9C0/func_800E2A18.s
 */
#include "common.h"

extern s8 D_800F98E0[][0x30];    /* per-player state, [0] = id (-1 = empty) */
extern s16 D_800F9D12[][0x1D8];  /* per-player entry, [0] = occupant (-1 = free) */

/* Slot availability check: scan the four players, count how many entries are
 * occupied and how many state slots are empty. Returns the index of the last
 * empty state slot when more slots are empty than are in use, else -1. */
s8 func_800E2A18(void) {
    s16 emptyCount;
    s16 i;
    s16 slot;
    s16 usedCount;
    s8 stateId;

    usedCount = 0;
    for (i = 0; i < 4; i++) {
        if (-1 != D_800F9D12[i][0]) {
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
