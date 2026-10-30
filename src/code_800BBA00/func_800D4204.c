/* @header
 * func_800D4204
 * VRAM 0x800D4204 | ROM 0xC76A4 | size 0x64
 * asm: asm/nonmatchings/code_800BBA00/func_800D4204.s
 */
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
