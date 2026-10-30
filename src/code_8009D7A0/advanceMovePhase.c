/* @header
 * advanceMovePhase  (originally func_800B16D0)
 * VRAM 0x800B16D0 | ROM 0xA4B70 | size 0x210
 * asm: asm/nonmatchings/code_8009D7A0/func_800B16D0.s
 */
#include "common.h"

/* Globals: D_800FABD0 is the move currently running, D_800FAF58 the attacker
 * and D_800F9B60 the opponent. */
extern u8 *D_800FAF58, *D_800FABD0, *D_800F9B60;
extern const u16 D_800E3CF0[];
extern const f64 D_800E5268;
s32 func_800D3650(void *, void *);
f32 func_800D3EEC(void *, void *, s32);

/* Advances the running move by one frame: in phase 0 it starts the next
 * animation command (or aborts into the 0x15 state), in phase 1 it watches the
 * attacker's timer and the opponent's state id to end or re-sync the move. */
void advanceMovePhase(void) {
    switch (*(s16 *)(D_800FABD0 + 4)) {
    case 0:
        if ((*(u64 *)(D_800FAF58 + 0x20) & 0x100ULL) && *(s16 *)(D_800FABD0 + 0x1E) != *(s16 *)(D_800FABD0 + 0x2C)) {
            u8 *move = D_800FABD0, *foe = D_800F9B60;
            u32 foeState;
            *(s16 *)(move + 2) = 0x15;
            *(s16 *)(move + 4) = 0;
            foeState = *(u16 *)(foe + 0xA);
            *(u32 *)(move + 0x5C) &= ~7;
            *(u16 *)(move + 0x2E) = foeState;
            return;
        }
        {
            u16 command = D_800E3CF0[(s16)func_800D3650(D_800FAF58 + 0x6C, D_800F9B60 + 0x6C)];
            u8 *move = D_800FABD0;
            *(u16 *)(move + 0xA) = command;
            (*(s16 *)(move + 4))++;
        }
        break;
    case 1:
        {
            f32 limit;
            *(u16 *)(D_800FABD0 + 6) = *(u16 *)(D_800FABD0 + 0xA);
            if (*(s16 *)(D_800FABD0 + 0x22) == 8)
                limit = func_800D3EEC(D_800F9B60 + 0x4C, D_800FAF58 + 0x6C, *(s32 *)(D_800F9B60 + 0x58)) + D_800E5268;
            else
                limit = 125.0f;
            {
                u8 *move = D_800FABD0;
                if (*(f32 *)(move + 0x3C) < limit) {
                    u8 *foe = D_800F9B60;
                    u32 foeState;
                    *(s16 *)(move + 2) = 0;
                    *(s16 *)(move + 4) = 0;
                    foeState = *(u16 *)(foe + 0xA);
                    *(u32 *)(move + 0x5C) &= ~7;
                    *(u16 *)(move + 0x2E) = foeState;
                }
            }
            {
                u8 *move = D_800FABD0, *foe = D_800F9B60;
                if (*(s16 *)(move + 0x2E) != *(s16 *)(foe + 0xA)) {
                    *(s16 *)(move + 2) = 0;
                    *(s16 *)(move + 4) = 0;
                    *(u16 *)(move + 0x2E) = *(u16 *)(foe + 0xA);
                    *(u32 *)(move + 0x5C) &= ~7;
                }
            }
            if (*(s16 *)(D_800FAF58 + 0xA) != 1) {
                u8 *move = D_800FABD0, *foe = D_800F9B60;
                *(s16 *)(move + 2) = 0;
                *(s16 *)(move + 4) = 0;
                *(u16 *)(move + 0x2E) = *(u16 *)(foe + 0xA);
                *(u32 *)(move + 0x5C) &= ~7;
            }
        }
        break;
    }
}
