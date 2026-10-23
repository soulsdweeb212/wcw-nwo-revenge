#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
extern u8 *D_800FAF58;
s8 func_800B4C60(void *, void *, s32, s32);
s8 func_800B5DC4(void *, s32);
/* Returns 1 when arg0 is outside arg1's boundary but within the clamp region. */
s32 func_800B60C8(void *arg0, void *arg1) {
    if (!func_800B4C60(arg0, arg1, 0, 1)) {
        return func_800B5DC4(arg0, 1) != 0;
    }
    return 0;
}
/* Two-state helper (state +4): state 0 sets the count word to 2 and advances;
 * state 1 resets the action unless the entity is in state 0x30. */
void func_800B1BB8(void) {
    u8 *o = D_800FABD0;
    switch (*(s16 *)(o + 4)) {
    case 0:
        *(s16 *)(o + 6) = 2;
        (*(s16 *)(o + 4))++;
        break;
    case 1:
        if (*(s16 *)(D_800FAF58 + 0xA) != 0x30) {
            u8 *g = D_800F9B60;
            *(s16 *)(o + 2) = 0;
            *(s16 *)(o + 4) = 0;
            *(u16 *)(o + 0x2E) = *(u16 *)(g + 0xA);
            *(u32 *)(o + 0x5C) &= ~7;
        }
        break;
    }
}
/* Two-state helper (state +4): state 0 sets the count word to 0x10 and
 * advances; state 1 resets the action unless the entity is in state 0x32. */
void func_800AF1B8(void) {
    u8 *o = D_800FABD0;
    switch (*(s16 *)(o + 4)) {
    case 0:
        *(s16 *)(o + 6) = 0x10;
        (*(s16 *)(o + 4))++;
        break;
    case 1:
        if (*(s16 *)(D_800FAF58 + 0xA) != 0x32) {
            u8 *g = D_800F9B60;
            *(s16 *)(o + 2) = 0;
            *(s16 *)(o + 4) = 0;
            *(u16 *)(o + 0x2E) = *(u16 *)(g + 0xA);
            *(u32 *)(o + 0x5C) &= ~7;
        }
        break;
    }
}
