/* @header
 * func_800A7828
 * VRAM 0x800A7828 | ROM 0x9ACC8 | size 0x140
 * asm: asm/nonmatchings/code_8009D7A0/func_800A7828.s
 */
#include "common.h"

void func_800DECAC(void *, s32, s32, s32);
s8 func_800D4198(s16);
#define F(o,t) (*(t *)((u8 *)arg1+(o)))
void func_800A7828(void *arg0, void *arg1) {
    u64 f0 = *(u64 *)((u8 *)arg0 + 0x20);
    u64 f1 = *(u64 *)((u8 *)arg1 + 0x20);
    if ((f0 & f1 & 0x140) && !(f1 & 0x1000000000) && (f1 & 0x400000)) {
        if ((*(u16 *)((u8 *)arg0 + 0xE) & 1) || func_800D4198(0x12C)) {
            F(0xA, s16) = 0x2C;
            F(0xC, s16) = 0;
            F(0xE, s16) = 0;
            F(0x360, s16) = 0;
            *(u64 *)((u8 *)arg1 + 0x20) = (*(u64 *)((u8 *)arg1 + 0x20) & ~0x10810000000ULL) | 0x1000000000ULL;
            func_800DECAC(arg1, 0, 0, 0);
            F(0xC, s16) = 4;
            *(u64 *)((u8 *)arg1 + 0x20) |= 0x10000000;
        }
    }
}
#undef F
