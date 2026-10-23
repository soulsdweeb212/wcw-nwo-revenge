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

/* As func_800AD958, but also set the source entity's action-locked bit. */
void func_800AD98C(s16 arg0) {
    u8 *o = D_800FABD0;
    u8 *g = D_800F9B60;
    *(s16 *)(o + 2) = arg0;
    *(s16 *)(o + 4) = 0;
    *(u16 *)(o + 0x2E) = *(u16 *)(g + 0xA);
    *(u32 *)(o + 0x5C) &= ~7;
    *(u64 *)(D_800FAF58 + 0x20) |= 0x10000000;
}

/* As func_800AD958, but only when the command actually changes. */
void func_800AD9E8(s16 arg0) {
    u8 *o = D_800FABD0;
    if (*(s16 *)(o + 2) != arg0) {
        u8 *g = D_800F9B60;
        *(s16 *)(o + 2) = arg0;
        *(s16 *)(o + 4) = 0;
        *(u16 *)(o + 0x2E) = *(u16 *)(g + 0xA);
        *(u32 *)(o + 0x5C) &= ~7;
    }
}

/* Pick the first threshold record whose key is >= a fresh random value, apply its
 * command and flags, and copy the entity state. */
void func_800ADA38(s16 *arg0) {
    s16 r;
    s16 *p;
    u16 v;

    p = arg0;
    r = func_800D4148();
    while (*p != -1) {
        if (*p >= r) {
            break;
        }
        p += 3;
    }
    v = *(u16 *)(p + 1);
    *(u16 *)(D_800FABD0 + 2) = v;
    *(s16 *)(D_800FABD0 + 4) = 0;
    *(u16 *)(D_800FABD0 + 0x2E) = *(u16 *)(D_800F9B60 + 0xA);
    *(u32 *)(D_800FABD0 + 0x5C) &= ~7;
    *(u32 *)(D_800FABD0 + 0x5C) |= *(u16 *)(p + 2);
}
