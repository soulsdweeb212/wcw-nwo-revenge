/* @header
 * func_800281A0
 * VRAM 0x800281A0 | ROM 0x28DA0 | size 0x48
 * asm: asm/nonmatchings/main/func_800281A0.s
 */
#include "common.h"

extern s32 D_800389A0;
extern u8 D_80064AC0[];
extern u8 D_80073E98[];
extern u8 D_80070A98;

extern s32 D_80037248;
extern void *D_80037250;

s32 func_8001C890(void *, void *, s32);
s32 func_8001C990(void *, void *, s32);
s32 func_8001CAC0(void *, s32, s32);
s32 nw2DisableInterrupts(void);
void func_800265AC(s32 *, s32);
void nw2RestoreInterrupts(s32);

/* Mark the current thread stopped (state 2) and enqueue it on the runnable list. */
void func_800281A0(void) {
    s32 s;
    s32 v;

    s = nw2DisableInterrupts();
    v = 2;
    *(s16 *)((u8 *)D_80037250 + 0x10) = v;
    func_800265AC(&D_80037248, v);
    nw2RestoreInterrupts(s);
}
