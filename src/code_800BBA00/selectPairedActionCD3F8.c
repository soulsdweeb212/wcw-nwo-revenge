/* @header
 * selectPairedActionCD3F8  (originally func_800CD3F8)
 * VRAM 0x800CD3F8 | ROM 0xC0898 | size 0x2CC
 * asm: asm/nonmatchings/code_800BBA00/selectPairedActionCD3F8.s
 */
#include "common.h"

/* Chooses the paired action between `source` and `target` from their flag words
 * (+0x20) and state fields, and starts it via beginPairedEntityActions. The first
 * (guard/block) case falls through into the shared block; later cases select grab
 * and collision responses and then clear/set bits on source's +0x2C state word. */
void beginPairedEntityActions(void *source, s32 sourceAction, void *target, s32 targetAction);

void selectPairedActionCD3F8(u8 *source, u8 *target) {
    s32 var_a1;
    s32 var_a3;

    if (!(*(u64 *)(source + 0x20) & 0x9ULL) && (*(u64 *)(source + 0x20) & 0x80ULL)) {
        if (*(s32 *)(source + 0x2C) & 0x40) {
            beginPairedEntityActions(source, 0x72, target, 0x73);
            *(s32 *)(target + 0x2C) = *(s32 *)(source + 0x2C) & ~2;
            return;
        }
        goto block_7;
    }
block_7:
    if ((*(u64 *)(source + 0x20) & 0x100ULL) && (*(u64 *)(target + 0x20) & 0x80ULL)) {
        *(s32 *)(source + 0x2C) = *(s32 *)(source + 0x2C) | 0x10000;
        beginPairedEntityActions(source, 0x87, target, 0x88);
        *(s32 *)(target + 0x2C) = *(s32 *)(source + 0x2C);
        return;
    }
    if ((*(u64 *)(source + 0x20) & 0x100ULL) && (*(u64 *)(target + 0x20) & 0x40ULL)) {
        *(s32 *)(source + 0x2C) = *(s32 *)(source + 0x2C) | 0x20000;
        beginPairedEntityActions(source, 0x79, target, 0x7A);
        *(s32 *)(target + 0x2C) = *(s32 *)(source + 0x2C);
        return;
    }
    if (!(*(u64 *)(source + 0x20) & 0x0ULL) && !(*(u64 *)(source + 0x20) & 0x9ULL)) {
        s32 temp_a0_2 = *(s32 *)(source + 0x2C);
        s32 temp_v1;
        if (temp_a0_2 & 0x40000) {
            beginPairedEntityActions(source, 0x47, target, 0x48);
            return;
        }
        if ((*(s16 *)(target + 0xA) == 0x14) && (*(s16 *)(target + 0xC) == 3)) {
            *(s32 *)(source + 0x2C) = temp_a0_2 | 0x80;
            *(u16 *)(source + 0x3E) = *(u16 *)(target + 0x3E);
        }
        if (*(u64 *)(source + 0x20) & 0x80ULL) {
            *(s32 *)(source + 0x2C) = *(s32 *)(source + 0x2C) | 0x200;
        }
        if (*(u64 *)(target + 0x20) & 0x80ULL) {
            *(s32 *)(source + 0x2C) = *(s32 *)(source + 0x2C) | 0x100;
        }
        temp_v1 = *(s32 *)(source + 0x2C) & ~0x400;
        *(s32 *)(source + 0x2C) = temp_v1;
        if (!(temp_v1 & 0x40384)) {
            temp_v1 = temp_v1 | 0x400;
            *(s32 *)(source + 0x2C) = temp_v1;
            if (!(temp_v1 & 0x40384)) {
                if (temp_v1 & 0x20) {
                    beginPairedEntityActions(source, 0x8B, target, 0x8C);
                    return;
                }
            }
        }
        var_a1 = 0x45;
        var_a3 = 0x46;
        beginPairedEntityActions(source, var_a1, target, var_a3);
        *(s32 *)(target + 0x2C) = *(s32 *)(source + 0x2C) & ~2;
    }
}
