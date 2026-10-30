/* @header
 * func_800BE450
 * VRAM 0x800BE450 | ROM 0xB18F0 | size 0x90
 * asm: asm/nonmatchings/code_800BBA00/func_800BE450.s
 */
#include "common.h"

extern u8 D_800F9D30[];
extern u8 D_800F9D34[];

s8 func_800D26A0(void *, s32, s8);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
void func_800D3890(void *, void *, void *);
extern u8 D_800F9D7C[];

void func_800D3E40(void *, void *, s32, void *);

/* Places arg0 at the two probe offsets around arg1 along arg1's heading. */
void func_800BE450(void *arg0, void *arg1) {
    f32 buf[4];
    void *p = (u8 *)arg1 + 0x4C;

    buf[0] = 1.43f;
    buf[2] = 27.77f;
    func_800D3E40((u8 *)arg1 + 0x6C, buf, *(s32 *)((u8 *)arg1 + 0x58), p);
    buf[0] = 0.0f;
    buf[2] = 73.5f;
    func_800D3E40(p, buf, *(s32 *)((u8 *)arg1 + 0x58), (u8 *)arg0 + 0x4C);
}
