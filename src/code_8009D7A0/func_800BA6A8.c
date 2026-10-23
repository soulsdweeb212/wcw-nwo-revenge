#include "common.h"

extern u8 D_8007E228[], D_8007EF30[], D_800F9D58[];
extern s16 D_800EB474, D_800EB478;
extern u16 D_800EB476;

/* Rotating per-entity id: while the gate bit 0x400 at D_8007E228+0x58 is set and the index
 * D_800EB478 is below the limit D_800EB474, store the next u16 from the D_8007EF30+0xC90
 * table into this entity's field at D_800F9D58 (record stride 0x3B0), advance the index,
 * decrement the remaining count D_800EB476 and return 1. Otherwise store 0 and return 0. */
s32 func_800BA6A8(s8 arg0) {
    s16 i;
    u16 remaining;
    if (*(u16 *)(D_8007E228 + 0x58) & 0x400) {
        i = D_800EB478;
        if (i < D_800EB474) {
            remaining = D_800EB476 - 1;
            D_800EB478 = i + 1;
            *(u16 *)(D_800F9D58 + arg0 * 0x3B0) = *(u16 *)(D_8007EF30 + 0xC90 + i * 2);
            D_800EB476 = remaining;
            return 1;
        }
    }
    *(u16 *)(D_800F9D58 + arg0 * 0x3B0) = 0;
    return 0;
}
