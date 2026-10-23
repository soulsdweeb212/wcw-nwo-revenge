#include "common.h"

extern u8 D_8007EF30[];
extern u8 D_800FABE8[], D_800FABEC[], D_800FABEE[];

/* Report whether entity arg0 should be skipped: true when its u64 flags have bits
 * 0/1, or when the global status has neither bit 0x400 nor bit 4. */
s32 func_800C2830(void *arg0) {
    if (*(u64 *)((u8 *)arg0 + 0x20) & 3) return 1;
    return (*(u16 *)(D_8007EF30 + 0x170) & 0x404) == 0;
}

/* Reset the eight 8-byte entries of entity arg0's block. */
void func_800C2B20(s8 arg0) {
    s16 i;
    for (i = 0; i < 8; i++) {
        s32 offset = i * 8 + arg0 * 64;
        *(f32 *)(D_800FABE8 + offset) = 150.0f;
        *(s16 *)(D_800FABEC + offset) = 15;
        *(s16 *)(D_800FABEE + offset) = 0;
    }
}
