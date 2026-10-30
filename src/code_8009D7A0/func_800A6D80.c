/* @header
 * func_800A6D80
 * VRAM 0x800A6D80 | ROM 0x9A220 | size 0xC4
 * asm: asm/nonmatchings/code_8009D7A0/func_800A6D80.s
 */
#include "common.h"

void func_800DECAC(void *, s32, s32, s32);

/* Reset an entity's animation/action state to animation arg1: store arg1 at +0xA, zero the
 * +0xC/+0xE substate fields and the +0x360 input-bits word, clear u64 flag mask
 * 0x10810000000 and set 0x1000000000, run the standard action teardown func_800DECAC,
 * clear flag 0x40000000, set the signed bytes +0x362/+0x363 to -1 and set flag 0x10000000. */
void func_800A6D80(void *arg0, s16 arg1) {
    *(s16 *)((u8 *)arg0 + 0xA) = arg1;
    *(s16 *)((u8 *)arg0 + 0xC) = 0;
    *(s16 *)((u8 *)arg0 + 0xE) = 0;
    *(s16 *)((u8 *)arg0 + 0x360) = 0;
    *(u64 *)((u8 *)arg0 + 0x20) = (*(u64 *)((u8 *)arg0 + 0x20) & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(arg0, 0, 0, 0);
    *(u64 *)((u8 *)arg0 + 0x20) &= ~0x40000000ULL;
    *(s8 *)((u8 *)arg0 + 0x362) = -1;
    *(s8 *)((u8 *)arg0 + 0x363) = -1;
    *(u64 *)((u8 *)arg0 + 0x20) |= 0x10000000ULL;
}
