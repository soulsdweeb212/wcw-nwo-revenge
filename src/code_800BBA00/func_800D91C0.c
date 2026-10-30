/* @header
 * func_800D91C0
 * VRAM 0x800D91C0 | ROM 0xCC660 | size 0x74
 * asm: asm/nonmatchings/code_800BBA00/func_800D91C0.s
 */
#include "common.h"

s16 func_800D7690(void *, s32, s32);

extern u8 D_8007E228[];
extern u8 D_8007EF30[];
extern u8 D_800F9850[];

/* Increments the entity's D_800F9850 counter when the global and per-entity
 * gates are set. */
void func_800D91C0(u8 *arg0) {
    if ((*(u16 *)(D_8007E228 + 0x58) & 0x200) &&
        !(*(u16 *)(D_8007EF30 + 0x170) & 0x40) &&
        (*(u64 *)(arg0 + 0x20) & 0x200)) {
        *(u16 *)(D_800F9850 + (*(s8 *)arg0) * 2) += 1;
    }
}
