/* @header
 * func_800D93DC
 * VRAM 0x800D93DC | ROM 0xCC87C | size 0x18C
 * asm: asm/nonmatchings/code_800BBA00/func_800D93DC.s
 */
#include "common.h"

extern u8 D_8007E228[];
extern u8 D_8007EF30[];

/* Sets bits in frameBits from the wrestler's state and step, unless the global gate D_8007E228+0x58 bit 0x200 is
 * clear, D_8007EF30+0x170 bit 0x40 is set, or the wrestler has no tag partner (partnerId == id). Bit 1 is set in
 * state 1 on the apron, state 0x81 step < 2, state 0x17 step 1 on the apron, state 3 step < 4 on the apron and
 * state 9; bit 2 in state 0x81 step >= 2 and state 10 step 4 or 7. The meaning of the two bits is not known. */
void func_800D93DC(Wrestler *w) {
    s32 bits;
    if (!(*(u16 *)(D_8007E228 + 0x58) & 0x200)) {
        return;
    }
    if (*(u16 *)(D_8007EF30 + 0x170) & 0x40) {
        return;
    }
    if (w->partnerId == w->id) {
        return;
    }
    bits = 0;
    switch (w->state) {
    case 1:
        if (w->flags & WR_FLAG_ON_APRON) {
            bits = 1;
        }
        break;
    case 129:
        bits = 2;
        if (w->step < 2) {
            bits = 1;
        }
        break;
    case 23:
        if (w->step == 1 && (w->flags & WR_FLAG_ON_APRON)) {
            bits = 1;
        }
        break;
    case 3:
        if (w->flags & WR_FLAG_ON_APRON) {
            if (w->step < 4) {
                bits = 1;
            }
        }
        break;
    case 9:
        bits = 1;
        break;
    case 10:
        if (w->step == 4 || w->step == 7) {
            bits = 2;
        }
        break;
    }
    w->frameBits |= bits;
}
