/* @header
 * func_8001852C
 * VRAM 0x8001852C | ROM 0x1912C | size 0x134
 * asm: asm/nonmatchings/main/func_8001852C.s
 */
#include "common.h"

s32 func_800202B0(s32, s32, s32, s32, s32);
#define W(o) (*(volatile s32 *)((u8 *)arg0 + (o)))
#define H(o) (*(volatile s16 *)((u8 *)arg0 + (o)))
/* Initialize an object with four sub-records: three allocated with size class
 * 0x20 (offsets +0xC, +0x10, +0x40) and one with 0x50 (+0x54), then set the
 * initial counter/flag/state fields and call the supplied callback with
 * object+0x2C, storing its result at +0x28. The object fields are volatile and
 * the +0x64/+0x66 stores are intentionally duplicated. */
void func_8001852C(void *arg0, s32 (*callback)(void *), s32 mode) {
    W(0xC) = func_800202B0(0, 0, mode, 1, 0x20);
    W(0x10) = func_800202B0(0, 0, mode, 1, 0x20);
    W(0x28) = callback((u8 *)arg0 + 0x2C);
    W(0x34) = 0; W(0x38) = 1; W(0x3C) = 0;
    W(0x40) = func_800202B0(0, 0, mode, 1, 0x20);
    W(0x4C) = 0; W(0x50) = 1; W(0x48) = 0;
    *(volatile f32 *)((u8 *)arg0 + 0x44) = 1.0f;
    W(0x54) = func_800202B0(0, 0, mode, 1, 0x50);
    W(0x78) = 1; W(0x84) = 0;
    H(0x5A) = 1; H(0x68) = 1; H(0x6E) = 1; H(0x5C) = 1; H(0x5E) = 1;
    H(0x60) = 0; H(0x62) = 0; H(0x66) = 1; H(0x64) = 0; H(0x66) = 1; H(0x64) = 0;
    W(0x70) = 0; W(0x74) = 0; H(0x58) = 0; W(0x7C) = 0; W(0x80) = 0;
}
