/* @header
 * func_800B2740
 * VRAM 0x800B2740 | ROM 0xA5BE0 | size 0x1F4
 * asm: asm/nonmatchings/code_8009D7A0/func_800B2740.s
 */
#include "common.h"

/* Advance the current move script. `self` (D_800FABD0) is the active action
 * record; its state word at +4 selects a case. The move reacts to the
 * opponent/global state at D_800FAF58+0xA: certain states keep the move,
 * otherwise it either advances to the next step (+8 = 0xF00) or resets the
 * action record (+2/+4 cleared, +0x2E copied from D_800F9B60+0xA, flags
 * +0x5C bits 0..2 cleared). */
extern u8 *volatile D_800FABD0;
extern u8 *D_800F9B60, *D_800FAF58;
extern u16 D_800E3CE0[];
extern f64 D_800E52A0;
void func_800B2740(void) {
    u16 stance;
    u8 *self = D_800FABD0;
    switch (*(s16 *)(self + 4)) {
    case 0:
        if (*(s16 *)(self + 0) == 4) *(s16 *)(self + 6) = D_800E3CE0[*(s16 *)(D_800F9B60 + 0x3E)] | 4;
        { u8 *cur = D_800FABD0; *(s16 *)(cur + 4) = *(u16 *)(cur + 4) + 1; }
        break;
    case 1:
        switch (*(s16 *)(D_800FAF58 + 0xA)) {
        case 4: break;
        case 3:
            if (*(s16 *)(self + 0) == 4) {
                if (*(s16 *)(D_800F9B60 + 0xA) != 10) goto advance;
                stance = *(u16 *)(D_800F9B60 + 0xC);
                if ((u32)(stance - 3) < 2) goto check;
                if ((s16)stance != 7) goto advance;
            check:
                if ((f64)*(f32 *)(self + 0x48 + *(s16 *)(D_800F9B60 + 0x3E) * 4) < D_800E52A0) { *(s16 *)(self + 8) = 0xF00; *(s16 *)(self + 4) = *(u16 *)(self + 4) + 1; }
                goto done;
            advance: { u8 *cur = D_800FABD0; *(s16 *)(cur + 8) = 0xF00; *(s16 *)(cur + 4) = *(u16 *)(cur + 4) + 1; }
            }
        done: break;
        default: { u8 *cur = D_800FABD0; u8 *target = D_800F9B60; *(s16 *)(cur + 2) = 0; *(s16 *)(cur + 4) = 0; *(u16 *)(cur + 0x2E) = *(u16 *)(target + 0xA); *(u32 *)(cur + 0x5C) &= ~7; }
        break;
        }
    case 2:
        switch (*(s16 *)(D_800FAF58 + 0xA)) {
        case 3: { u8 *cur = D_800FABD0; *(s16 *)(cur + 8) = 0xF00; } break;
        case 4: break;
        default: { u8 *cur = D_800FABD0; u8 *target = D_800F9B60; *(s16 *)(cur + 2) = 0; *(s16 *)(cur + 4) = 0; *(u16 *)(cur + 0x2E) = *(u16 *)(target + 0xA); *(u32 *)(cur + 0x5C) &= ~7; } break;
        }
        break;
    }
}
