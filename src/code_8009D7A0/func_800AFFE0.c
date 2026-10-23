#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
s8 func_800D4198(s16);
f32 func_800B3AD8(void *);
/* Sets the action substate byte to 0x50 and resets the action to state 0 with
 * the entity's animation copied. */
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
/* Returns the remaining countdown for the entity when it is in state 0x44 (and
 * the chance roll passes): the entity limit minus the elapsed counter. */
s16 func_800B10B8(void) {
    s16 result = 0;
    if (*(s16 *)(D_800F9B60 + 0xA) == 0x44) {
        if (func_800D4198(*(s16 *)(D_800FABD0 + 0x12))) {
            result = D_800F9B60[0x370] - *(u16 *)(D_800F9B60 + 6) - 1;
            if (result < 0) result = 0;
        }
    }
    return result;
}
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
/* Returns the remaining countdown for the action when its substate (+0x22) is
 * 6/0x11/0x17 (and the chance roll passes). */
s16 func_800B1634(void) {
    s16 result = 0;
    u8 *o = D_800FABD0;
    s16 state = *(s16 *)(o + 0x22);
    if (state == 6 || state == 0x17 || state == 0x11) {
        if (func_800D4198(*(s16 *)(o + 0x12))) {
            result = D_800F9B60[0x370] - *(u16 *)(D_800F9B60 + 6) - 1;
            if (result < 0) result = 0;
        }
    }
    return result;
}
