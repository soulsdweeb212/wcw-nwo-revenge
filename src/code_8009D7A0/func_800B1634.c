#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
s8 func_800D4198(s16);
f32 func_800B3AD8(void *);
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

/* Return a countdown value for the current action record D_800FABD0 when its
 * mode field (+0x22) is one of 6/0x17/0x11 and the entity animation check
 * func_800D4198 passes: entity[D_800F9B60+0x370] minus the timer (entity+6)
 * minus one, clamped at 0. */
s16 func_800B1634(void) {
    s16 count = 0;
    u8 *act = D_800FABD0;
    s16 mode = *(s16 *)(act + 0x22);
    if (mode == 6 || mode == 0x17 || mode == 0x11) {
        if (func_800D4198(*(s16 *)(act + 0x12))) {
            count = D_800F9B60[0x370] - *(u16 *)(D_800F9B60 + 6) - 1;
            if (count < 0) count = 0;
        }
    }
    return count;
}
