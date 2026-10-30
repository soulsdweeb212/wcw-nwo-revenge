/* @header
 * advanceCheckAction  (originally func_800B1440)
 * VRAM 0x800B1440 | ROM 0xA48E0 | size 0xF0
 * asm: asm/nonmatchings/code_8009D7A0/advanceCheckAction.s
 */
#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
extern u8 *D_800FAF58;

/* Check-action phase on D_800FABD0 (state at +4). State 0 arms +6 and advances.
 * State 1 inspects the actor's sub-state: at 0x42 the record is reset, within
 * [0x40,0x42) it either advances or resets depending on the target's sub-state
 * and frame, and anything below 0x40 resets. Resetting copies the target's
 * sub-state into +0x2E and clears the low 3 bits of +0x5C. */
void advanceCheckAction(void) {
    switch (*(s16 *)(D_800FABD0 + 4)) {
    case 0:
        *(s16 *)(D_800FABD0 + 6) = 0x10;
        (*(u16 *)(D_800FABD0 + 4))++;
        break;
    case 1:
        if (*(s16 *)(D_800FAF58 + 0xA) < 0x42) {
            if (*(s16 *)(D_800FAF58 + 0xA) >= 0x40) {
                if (*(s16 *)(D_800FABD0 + 0x2E) != *(s16 *)(D_800F9B60 + 0xA) ||
                    *(u8 *)(D_800F9B60 + 0x36C) - 3 < *(s16 *)(D_800F9B60 + 6)) {
                    *(s16 *)(D_800FABD0 + 2) = 0;
                    *(s16 *)(D_800FABD0 + 4) = 0;
                    *(u16 *)(D_800FABD0 + 0x2E) = *(u16 *)(D_800F9B60 + 0xA);
                    *(u32 *)(D_800FABD0 + 0x5C) &= ~7;
                } else {
                    *(s16 *)(D_800FABD0 + 6) = 0x10;
                }
                break;
            }
        }
        {
            u8 *target = D_800F9B60;
            *(s16 *)(D_800FABD0 + 2) = 0;
            *(s16 *)(D_800FABD0 + 4) = 0;
            *(u16 *)(D_800FABD0 + 0x2E) = *(u16 *)(target + 0xA);
            *(u32 *)(D_800FABD0 + 0x5C) &= ~7;
        }
        break;
    }
}
