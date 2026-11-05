/* @header
 * func_800D4088
 * VRAM 0x800D4088 | ROM 0xC7528 | size 0xC0
 * asm: asm/nonmatchings/code_800BBA00/func_800D4088.s
 */
#include "common.h"

s32 guRandom(void);
s16 func_800D4204(void);
extern s32 gRandSeed;
extern s32 D_800EB634;
extern s16 D_800EB638[];

/* Seed/refresh the random generator: store a fresh entropy sample (guRandom) in
 * gRandSeed, advance the generator (arg0 & 0xF) times, then store a fresh odd seed in
 * D_800EB634 and refill the 32-entry s16 table D_800EB638 with func_800D4204 samples. */
void func_800D4088(s32 arg0) {
    u32 n;
    s16 i;
    u32 count;

    gRandSeed = guRandom();
    n = (arg0 & 0xF) << 24;
    i = 0;
    if (n != 0) {
        count = n;
        goto _loop;
_loop:
        guRandom();
        i = i + 1;
        if (i < (s16)(count >> 24)) goto _loop;
    }
    D_800EB634 = guRandom() | 1;
    for (i = 0; i < 32; i++) {
        D_800EB638[i] = func_800D4204();
    }
}
