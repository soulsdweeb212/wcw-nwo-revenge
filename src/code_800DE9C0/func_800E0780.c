/* @header
 * func_800E0780
 * VRAM 0x800E0780 | ROM 0xD3C20 | size 0x5C
 * asm: asm/nonmatchings/code_800DE9C0/func_800E0780.s
 */
#include "common.h"

s32 checkEntityAttackHit(void *, s32);
s32 isEntityActionEligible(void *, void *, s16);
void func_800A6C48(void *, s32);
void func_800E212C(void *);

/* Clears the entity's 0x80000 flag and resets its +0x14 counter to 0x32 when
 * arg1 bit 0x2000 is set. */
void func_800E0780(void *arg0, s32 arg1) {
    u64 f;

    if (arg1 & 0x2000) {
        f = *(u64 *)((u8 *)arg0 + 0x20);
        if (f & 0x80000) {
            *(u64 *)((u8 *)arg0 + 0x20) = f & ~0x80000ULL;
            *(s16 *)((u8 *)arg0 + 0x14) = 0x32;
        }
    }
}
