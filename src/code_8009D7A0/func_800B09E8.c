/* @header
 * func_800B09E8
 * VRAM 0x800B09E8 | ROM 0xA3E88 | size 0x18C
 * asm: asm/nonmatchings/code_8009D7A0/func_800B09E8.s
 */
#include "common.h"

/* Updates the current action (D_800FABD0) for entity D_800FAF58. When the entity
 * is in state 1 it either selects the "hit" action 0x15 (flag 0x100 set and the
 * tracked target index changed) or, after looking up the facing angle, selects
 * D_800E3CF0[angle] and clears the action when within D_800E5240. A state change
 * on D_800F9B60 always resets the action. */
extern u8 *D_800FAF58, *D_800FABD0, *D_800F9B60;
extern const u16 D_800E3CF0[];
extern const f64 D_800E5240;
s32 func_800D3650(void *, void *);

void func_800B09E8(void) {
    if (*(s16 *)(D_800FAF58 + 0xA) == 1) {
        if ((*(u64 *)(D_800FAF58 + 0x20) & 0x100ULL) && *(s16 *)(D_800FABD0 + 0x1E) != *(s16 *)(D_800FABD0 + 0x2C)) {
            u8 *action = D_800FABD0, *source = D_800F9B60;
            u32 state;
            *(s16 *)(action + 2) = 0x15;
            *(s16 *)(action + 4) = 0;
            state = *(u16 *)(source + 0xA);
            *(u32 *)(action + 0x5C) &= ~7;
            *(u16 *)(action + 0x2E) = state;
            return;
        }
        {
            s16 angle = func_800D3650(D_800FAF58 + 0x6C, D_800F9B60 + 0x6C);
            u8 *action = D_800FABD0;
            f32 distance = *(f32 *)(action + 0x34);
            *(u16 *)(action + 6) = D_800E3CF0[angle];
            if ((f64)distance < D_800E5240) {
                u8 *source = D_800F9B60;
                u32 state;
                *(s16 *)(action + 2) = 0;
                *(s16 *)(action + 4) = 0;
                state = *(u16 *)(source + 0xA);
                *(u32 *)(action + 0x5C) &= ~7;
                *(u16 *)(action + 0x2E) = state;
            }
        }
        {
            u8 *action = D_800FABD0, *source = D_800F9B60;
            if (*(s16 *)(action + 0x2E) != *(s16 *)(source + 0xA)) {
                *(s16 *)(action + 2) = 0;
                *(s16 *)(action + 4) = 0;
                *(u16 *)(action + 0x2E) = *(u16 *)(source + 0xA);
                *(u32 *)(action + 0x5C) &= ~7;
            }
        }
    } else {
        u8 *action = D_800FABD0, *source = D_800F9B60;
        *(s16 *)(action + 2) = 0;
        *(s16 *)(action + 4) = 0;
        *(u16 *)(action + 0x2E) = *(u16 *)(source + 0xA);
        *(u32 *)(action + 0x5C) &= ~7;
    }
}
