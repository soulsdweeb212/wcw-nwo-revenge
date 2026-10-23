#include "common.h"

extern u8 D_8007EF30[];
extern u8 D_800FABE8[], D_800FABEC[], D_800FABEE[];
/* True when the entity's +0x20 flags have no low 2 bits set and the global
 * 0x170 bits 0x404 are clear. */
s32 func_800C2830(void *arg0) {
    if (*(u64 *)((u8 *)arg0 + 0x20) & 3) return 1;
    return (*(u16 *)(D_8007EF30 + 0x170) & 0x404) == 0;
}
/* Initialises the 8 animation frames of entity-type arg0 to 150.0f / 15 / 0. */
void func_800C2B20(s8 arg0) {
    s16 i;
    for (i = 0; i < 8; i++) {
        s32 offset = i * 8 + arg0 * 64;
        *(f32 *)(D_800FABE8 + offset) = 150.0f;
        *(s16 *)(D_800FABEC + offset) = 15;
        *(s16 *)(D_800FABEE + offset) = 0;
    }
}
