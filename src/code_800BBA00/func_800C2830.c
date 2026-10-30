/* @header
 * func_800C2830
 * VRAM 0x800C2830 | ROM 0xB5CD0 | size 0x40
 * asm: asm/nonmatchings/code_800BBA00/func_800C2830.s
 */
#include "common.h"

extern u8 D_8007EF30[];
extern u8 D_800FABE8[], D_800FABEC[], D_800FABEE[];

/* Report whether entity arg0 should be skipped: true when its u64 flags have bits
 * 0/1, or when the global status has neither bit 0x400 nor bit 4. */
s32 func_800C2830(void *arg0) {
    if (*(u64 *)((u8 *)arg0 + 0x20) & 3) return 1;
    return (*(u16 *)(D_8007EF30 + 0x170) & 0x404) == 0;
}
