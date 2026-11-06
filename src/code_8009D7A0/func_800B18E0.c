/* @header
 * func_800B18E0
 * VRAM 0x800B18E0 | ROM 0xA4D80 | size 0xCC
 * asm: asm/nonmatchings/code_8009D7A0/func_800B18E0.s
 */
#include "common.h"

extern u8 *D_800FABD0;

/* Two-step action state machine driven by the s16 at D_800FABD0+4:
 * step 0 stores the byte 0x50 at D_800FABD0+0xC and advances the step; step 1 finishes the
 * action (reset +2/+4, copy D_800F9B60->state into +0x2E and clear the low three bits
 * of the u32 flags at +0x5C) whenever the recorded +0x2E differs from D_800F9B60's current
 * state, or D_800FAF58->state is not 0x17. */
void func_800B18E0(void) {
    switch (*(s16 *)(D_800FABD0 + 4)) {
    case 0:
        *(u8 *)(D_800FABD0 + 0xC) = 0x50;
        (*(s16 *)(D_800FABD0 + 4))++;
        break;
    case 1:
        if (*(s16 *)(D_800FABD0 + 0x2E) != D_800F9B60->state) {
            Wrestler *g = D_800F9B60;
            *(s16 *)(D_800FABD0 + 2) = 0;
            *(s16 *)(D_800FABD0 + 4) = 0;
            *(u16 *)(D_800FABD0 + 0x2E) = (u16)g->state;
            *(u32 *)(D_800FABD0 + 0x5C) &= ~7;
        }
        if (D_800FAF58->state != 0x17) {
            Wrestler *g = D_800F9B60;
            *(s16 *)(D_800FABD0 + 2) = 0;
            *(s16 *)(D_800FABD0 + 4) = 0;
            *(u16 *)(D_800FABD0 + 0x2E) = (u16)g->state;
            *(u32 *)(D_800FABD0 + 0x5C) &= ~7;
        }
        break;
    }
}
