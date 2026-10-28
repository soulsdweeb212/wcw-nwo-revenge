#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
s8 func_800D4198(s16);
f32 func_800B3AD8(void *);
/* Rolls a chance for the action (+0x12 scaled by func_800B3AD8), setting the
 * count word to 0x4000 on success, then resets the action (unless substate 5). */
void func_800AFFE0(void) {
    f32 scale = func_800B3AD8(D_800FABD0);
    u8 *o;
    u8 *g;
    if (func_800D4198((s16)(s32)((f32)*(s16 *)(D_800FABD0 + 0x12) * scale))) {
        *(s16 *)(D_800FABD0 + 8) = 0x4000;
    }
    o = D_800FABD0;
    if (*(s16 *)(o + 0x14) != 5) {
        g = D_800F9B60;
        *(s16 *)(o + 2) = 0;
        *(s16 *)(o + 4) = 0;
        *(u16 *)(o + 0x2E) = *(u16 *)(g + 0xA);
        *(u32 *)(o + 0x5C) &= ~7;
    }
}
