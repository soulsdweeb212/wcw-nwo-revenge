/* @header
 * func_800A72FC
 * VRAM 0x800A72FC | ROM 0x9A79C | size 0x2C
 * asm: asm/nonmatchings/code_8009D7A0/func_800A72FC.s
 */
#include "common.h"

void func_800D3838(void *, void *, s16, void *);

/* Sets moveDelta (x and z) to the XZ distance from the wrestler's pelvis joint (jointA[1]) to target, divided by
 * steps when steps is nonzero (func_800D3838). */
void func_800A72FC(Wrestler *w, void *target, s32 steps) {
    func_800D3838(&w->jointA[1], target, steps, w->moveDelta);
}

void func_800D36B4(void *, void *, void *);
void translateEntityXZ(void *, void *);

s32 func_800D3550(s32);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
