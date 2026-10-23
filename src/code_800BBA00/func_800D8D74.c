#include "common.h"

s16 func_800D7690(void *, s32, s32);
s32 func_800D35B0(s32, s32);
void translateEntityXZ(void *, void *);

extern u8 D_8007E228[];
extern u8 D_8007EF30[];
extern u8 D_800F9850[];

/* Ticks the entity's 0x18 counter down (an extra tick when the movement check
 * succeeds) and returns 1 when it has gone negative. */
s32 func_800D7894(u8 *arg0, s32 arg1) {
    *(u16 *)(arg0 + 0x18) = *(u16 *)(arg0 + 0x18) - 1;
    if (func_800D7690(arg0, arg1 & 0xFFFF, 1) == 1) {
        *(u16 *)(arg0 + 0x18) = *(u16 *)(arg0 + 0x18) - 1;
    }
    return (u32)(s16)*(u16 *)(arg0 + 0x18) >> 31;
}

/* Ticks the entity's 0x18 counter down (an extra tick when the movement check
 * succeeds), returning 1 when it reaches zero unless arg2 holds it at zero. */
s32 func_800D78F4(u8 *arg0, s32 arg1, s32 arg2) {
    *(u16 *)(arg0 + 0x18) = *(u16 *)(arg0 + 0x18) - 1;
    if (func_800D7690(arg0, arg1 & 0xFFFF, 1) == 1) {
        *(u16 *)(arg0 + 0x18) = *(u16 *)(arg0 + 0x18) - 1;
    }
    if ((s16)*(u16 *)(arg0 + 0x18) < 0) {
        if (arg2 << 24) {
            *(u16 *)(arg0 + 0x18) = 0;
        } else {
            return 1;
        }
    }
    return 0;
}

/* Advances the entity along its stored vector for the remaining +0x16 ticks,
 * turning by +0x348; returns 1 when the counter is exhausted. */
s32 func_800D8D74(u8 *arg0, void *arg1) {
    u16 v;

    if (*(s16 *)(arg0 + 0x16) > 0) {
        translateEntityXZ(arg0, arg0 + 0x33C);
        if (arg1 != 0) {
            translateEntityXZ(arg1, arg0 + 0x33C);
        }
        *(s32 *)(arg0 + 0x58) = func_800D35B0(*(s32 *)(arg0 + 0x58), *(s32 *)(arg0 + 0x348));
    }
    v = *(u16 *)(arg0 + 0x16) - 1;
    *(u16 *)(arg0 + 0x16) = v;
    return (v << 16) < 1;
}

/* Increments the entity's D_800F9850 counter when the global and per-entity
 * gates are set. */
void func_800D91C0(u8 *arg0) {
    if ((*(u16 *)(D_8007E228 + 0x58) & 0x200) &&
        !(*(u16 *)(D_8007EF30 + 0x170) & 0x40) &&
        (*(u32 *)(arg0 + 0x24) & 0x200)) {
        *(u16 *)(D_800F9850 + (*(s8 *)arg0) * 2) += 1;
    }
}
