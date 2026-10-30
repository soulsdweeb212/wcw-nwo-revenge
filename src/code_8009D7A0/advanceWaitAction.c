/* @header
 * advanceWaitAction  (originally func_800B1530)
 * VRAM 0x800B1530 | ROM 0xA49D0 | size 0x104
 * asm: asm/nonmatchings/code_8009D7A0/advanceWaitAction.s
 */
#include "common.h"

s16 func_800B1634(void);
extern u8 *D_800FABD0, *D_800F9B60, *D_800FAF58;

/* Wait-action phases on the action record D_800FABD0 (state at +4). State 0
 * samples the delay from func_800B1634 into +0xE; if it is zero the record is
 * reset from the target, otherwise it advances. State 1 counts +0xE down and,
 * when it expires, arms +6 and advances. State 2 resets the record unless the
 * actor's sub-state is 0x40. */
void advanceWaitAction(void) {
    u8 *act = D_800FABD0;
    u8 *target;
    u16 delay;
    switch (*(s16 *)(act + 4)) {
    case 0:
        delay = func_800B1634();
        act = D_800FABD0;
        *(u16 *)(act + 0xE) = delay;
        if ((delay << 16) == 0) {
            target = D_800F9B60;
            *(s16 *)(act + 2) = 0x1F;
            *(s16 *)(act + 4) = 0;
            *(u16 *)(act + 0x2E) = *(u16 *)(target + 0xA);
            *(u32 *)(act + 0x5C) &= ~7;
        } else {
            (*(s16 *)(act + 4))++;
        }
        break;
    case 1:
        (*(s16 *)(act + 0xE))--;
        if (*(s16 *)(act + 0xE) <= 0) {
            *(s16 *)(act + 6) = 0x10;
            (*(s16 *)(act + 4))++;
        }
        break;
    case 2:
        if (*(s16 *)(D_800FAF58 + 0xA) != 0x40) {
            target = D_800F9B60;
            *(s16 *)(act + 2) = 0;
            *(s16 *)(act + 4) = 0;
            *(u16 *)(act + 0x2E) = *(u16 *)(target + 0xA);
            *(u32 *)(act + 0x5C) &= ~7;
        }
        break;
    }
}
