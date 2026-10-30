/* @header
 * func_800BF548
 * VRAM 0x800BF548 | ROM 0xB29E8 | size 0xE4
 * asm: asm/nonmatchings/code_800BBA00/func_800BF548.s
 */
#include "common.h"

extern s16 D_800EB490[];
void func_800BF338(void *, s8, s32);

/* Per-entity cooldown counter keyed by the entity id at p+0. Mode 0 resets it;
 * mode 1 increments it and, when it reaches the limit -- 90 when p has flag
 * 0x400000000, else 60, with the amount read from the attachment's +2/+1 byte --
 * resets it and fires func_800BF338. */
void func_800BF548(u8 *p, s16 mode) {
    s32 limit; u8 amount;
    switch (mode) {
    case 0: D_800EB490[*(s8 *)p] = 0; break;
    case 1:
        D_800EB490[*(s8 *)p]++;
        if (*(u64 *)(p + 0x20) & 0x400000000ULL) {
            amount = (*(u8 **)(p + 0x364))[2]; limit = 90;
        } else {
            amount = (*(u8 **)(p + 0x364))[1]; limit = 60;
        }
        if (D_800EB490[*(s8 *)p] >= limit) {
            D_800EB490[*(s8 *)p] = 0;
            func_800BF338(p, (s8)amount, 1);
        }
        break;
    }
}
