#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
s8 func_800D4198(s16);
f32 func_800B3AD8(void *);

/* Reset the action record to command 0 with the 0x50 substate marker. */
void func_800B09A4(void) {
    u8 *o;
    u8 *g;
    D_800FABD0[0xC] = 0x50;
    o = D_800FABD0;
    g = D_800F9B60;
    *(s16 *)(o + 2) = 0;
    *(s16 *)(o + 4) = 0;
    *(u16 *)(o + 0x2E) = *(u16 *)(g + 0xA);
    *(u32 *)(o + 0x5C) &= ~7;
}
