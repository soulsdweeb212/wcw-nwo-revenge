/* @header
 * func_800B2740
 * VRAM 0x800B2740 | ROM 0xA5BE0 | size 0x1F4
 * asm: asm/nonmatchings/code_8009D7A0/func_800B2740.s
 */
#include "common.h"

/* Advance the current move script. `self` (D_800FABD0) is the active action
 * record; its state word at +4 selects a case. The move reacts to the
 * AI wrestler's state (D_800FAF58->state): certain states keep the move,
 * otherwise it either advances to the next step (+8 = 0xF00) or resets the
 * action record (+2/+4 cleared, +0x2E copied from D_800F9B60->state, flags
 * +0x5C bits 0..2 cleared). */
extern u8 *volatile D_800FABD0;
extern u16 D_800E3CE0[];
extern f64 D_800E52A0;
void func_800B2740(void) {
    u16 stance;
    u8 *self = D_800FABD0;
    switch (*(s16 *)(self + 4)) {
    case 0:
        if (*(s16 *)(self + 0) == 4) *(s16 *)(self + 6) = D_800E3CE0[D_800F9B60->dirIndex] | 4;
        { u8 *cur = D_800FABD0; *(s16 *)(cur + 4) = *(u16 *)(cur + 4) + 1; }
        break;
    case 1:
        switch (D_800FAF58->state) {
        case 4: break;
        case 3:
            if (*(s16 *)(self + 0) == 4) {
                if (D_800F9B60->state != 10) goto advance;
                stance = (u16)D_800F9B60->step;
                if ((u32)(stance - 3) < 2) goto check;
                if ((s16)stance != 7) goto advance;
check:
                if ((f64)*(f32 *)(self + 0x48 + D_800F9B60->dirIndex * 4) < D_800E52A0) { *(s16 *)(self + 8) = 0xF00; *(s16 *)(self + 4) = *(u16 *)(self + 4) + 1; }
                goto done;
                advance: { u8 *cur = D_800FABD0; *(s16 *)(cur + 8) = 0xF00; *(s16 *)(cur + 4) = *(u16 *)(cur + 4) + 1; }
            }
            done: break;
        default: { u8 *cur = D_800FABD0; Wrestler *target = D_800F9B60; *(s16 *)(cur + 2) = 0; *(s16 *)(cur + 4) = 0; *(u16 *)(cur + 0x2E) = (u16)target->state; *(u32 *)(cur + 0x5C) &= ~7; }
            break;
        }
    case 2:
        switch (D_800FAF58->state) {
        case 3: { u8 *cur = D_800FABD0; *(s16 *)(cur + 8) = 0xF00; } break;
        case 4: break;
        default: { u8 *cur = D_800FABD0; Wrestler *target = D_800F9B60; *(s16 *)(cur + 2) = 0; *(s16 *)(cur + 4) = 0; *(u16 *)(cur + 0x2E) = (u16)target->state; *(u32 *)(cur + 0x5C) &= ~7; } break;
        }
        break;
    }
}
