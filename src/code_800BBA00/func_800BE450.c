/* @header
 * func_800BE450
 * VRAM 0x800BE450 | ROM 0xB18F0 | size 0x90
 * asm: asm/nonmatchings/code_800BBA00/func_800BE450.s
 */
#include "common.h"

s8 func_800D26A0(void *, s32, s8);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
void func_800D3890(void *, void *, void *);

void func_800D3E40(void *, void *, s32, void *);

/* Places arg0 at the two probe offsets around arg1 (from its pelvis, then its root) along arg1's heading. */
void func_800BE450(Wrestler *arg0, Wrestler *arg1) {
    f32 buf[4];
    void *p = &arg1->x;

    buf[0] = 1.43f;
    buf[2] = 27.77f;
    func_800D3E40(&arg1->jointA[1], buf, arg1->heading, p);
    buf[0] = 0.0f;
    buf[2] = 73.5f;
    func_800D3E40(p, buf, arg1->heading, &arg0->x);
}
