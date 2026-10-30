/* @header
 * func_800A7188
 * VRAM 0x800A7188 | ROM 0x9A628 | size 0xB8
 * asm: asm/nonmatchings/code_8009D7A0/func_800A7188.s
 */
#include "common.h"

s32 func_800D36E8(f32, f32);
void func_800D4AD0(void *);
void func_800DECAC(void *, s32, s32, s32);
/* Resets the entity's action when its +4 counter is 1: clears the substate,
 * timer, anim and input words, replaces the 0x10810000000 flags with
 * 0x1000000000, resets the action variant and sets 0x10000000. Returns 1. */
s32 func_800A7188(void *arg0) {
    if (*(s16 *)((u8 *)arg0 + 4) == 1) {
        func_800D4AD0(arg0);
        *(s16 *)((u8 *)arg0 + 0xA) = 0x2B;
        *(s16 *)((u8 *)arg0 + 0xC) = 0;
        *(s16 *)((u8 *)arg0 + 0xE) = 0;
        *(s16 *)((u8 *)arg0 + 0x360) = 0;
        *(u64 *)((u8 *)arg0 + 0x20) = (*(u64 *)((u8 *)arg0 + 0x20) & ~0x10810000000ULL) | 0x1000000000ULL;
        func_800DECAC(arg0, 0, 0, 0);
        *(u64 *)((u8 *)arg0 + 0x20) |= 0x10000000ULL;
        return 1;
    }
    return 0;
}
