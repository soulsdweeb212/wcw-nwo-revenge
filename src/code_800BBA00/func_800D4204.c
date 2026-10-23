#include "common.h"

extern s32 gRandSeed;
extern s32 D_800EB634;
extern u16 D_800EB638[];

s32 func_8001C580(void);
void func_800D427C(void *, s32);
s32 func_800D4204(void);

/* Linear-congruential random value in [0,1000). */
s32 func_800D4204(void) {
    s32 x;
    s16 y;
    do {
        x = gRandSeed * 0x5D588B65 + D_800EB634;
        gRandSeed = x;
        y = (u32)(x & 0xFFFFF) / 1000;
    } while (y >= 1000);
    return y;
}

/* Replace one of the 32 rolling slots in D_800EB638 (chosen by the low 5 bits of
 * func_8001C580()) with a fresh random value and return the previous value. */
s32 func_800D4148(void) {
    u16 *slot = (u16 *)((u32)&D_800EB638 + (func_8001C580() & 0x1F) * 2);
    u16 old = *slot;
    *slot = func_800D4204();
    return (s16)old;
}

/* As func_800D4148, but reports whether arg0 is at least the replaced value. */
s32 func_800D4198(s16 arg0) {
    u16 *slot = (u16 *)((u32)&D_800EB638 + (func_8001C580() & 0x1F) * 2);
    u16 old = *slot;
    *slot = func_800D4204();
    return arg0 >= (s16)old;
}
