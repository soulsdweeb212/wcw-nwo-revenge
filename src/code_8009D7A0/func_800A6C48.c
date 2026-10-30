/* @header
 * func_800A6C48
 * VRAM 0x800A6C48 | ROM 0x9A0E8 | size 0x94
 * asm: asm/nonmatchings/code_8009D7A0/func_800A6C48.s
 */
#include "common.h"

extern u8 D_8007EF30[];
void func_800DECAC(void *, s32, s32, s32);

/* Like func_800A6BE0 but also raises the 0x10000000 flag. */
void func_800A6C48(void *arg0, s32 arg1) {
    *(s16 *)((u8 *)arg0 + 0xA) = arg1;
    *(s16 *)((u8 *)arg0 + 0xC) = 0;
    *(s16 *)((u8 *)arg0 + 0xE) = 0;
    *(s16 *)((u8 *)arg0 + 0x360) = 0;
    *(u64 *)((u8 *)arg0 + 0x20) = (*(u64 *)((u8 *)arg0 + 0x20) & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(arg0, 0, 0, 0);
    *(u64 *)((u8 *)arg0 + 0x20) |= 0x10000000ULL;
}
