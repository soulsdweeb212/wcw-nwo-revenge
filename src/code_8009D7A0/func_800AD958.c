/* @header
 * func_800AD958
 * VRAM 0x800AD958 | ROM 0xA0DF8 | size 0x34
 * asm: asm/nonmatchings/code_8009D7A0/func_800AD958.s
 */
#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
extern u8 *D_800FAF58;
s32 func_800D4148(void);

/* Switch the action record to command arg0: reset the substate and timer, copy the
 * entity's +0xA state into +0x2E, and clear the low action-flag bits. */
void func_800AD958(s16 arg0) {
    u8 *o = D_800FABD0;
    u8 *g = D_800F9B60;
    *(s16 *)(o + 2) = arg0;
    *(s16 *)(o + 4) = 0;
    *(u16 *)(o + 0x2E) = *(u16 *)(g + 0xA);
    *(u32 *)(o + 0x5C) &= ~7;
}
