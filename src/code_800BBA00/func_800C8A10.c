/* @header
 * func_800C8A10
 * VRAM 0x800C8A10 | ROM 0xBBEB0 | size 0x374
 * asm: asm/nonmatchings/code_800BBA00/func_800C8A10.s
 */
#include "common.h"

extern u16 D_800FAF8A;
extern s8 D_800FAF78;
void func_800D7E80(void *, void *);
void func_800D427C(void *, s16, s32);
s8 func_800D8D74(void *, s32);
s16 func_800B6DEC(void *, void *, s32);
void func_800D7690(void *, s32, s32);
s8 func_800D7894(void *, u16);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
s32 func_800D2B64(void *, f32, u16, s32);
#endif
void func_800A7188(void *);

void func_800C8A10(void) {
    switch (D_800FAF5C->step) {
    case 0:
        if (!(D_800F9B00->grappleCtx & 0x10)) {
            func_800D427C(D_800FAF5C, 0x10B8, 0);
            D_800FAF5C->step = 2;
            return;
        }
        func_800D7E80(D_800FAF5C, D_800F9B00);
        func_800D427C(D_800FAF5C, 0x10A6, 2);
        {
            u16 *pc = (u16 *)&D_800FAF5C->step;
            s32 v = *pc + 1;
            u32 tq;
            *pc = v;
            tq = v & 1;
            if (tq >> 1) {
                func_800A7188(0);
            }
        }
    case 1:
        if (func_800D8D74(D_800FAF5C, 0)) {
            D_800FAF5C->step++;
        }
        return;
    case 2:
        if (D_800FAF5C->animFramesLeft > 0) {
            return;
        }
        func_800D427C(D_800FAF5C, (D_800F9B00->grappleCtx & 0x10) ? 0x10A8 : 0x10BA, 0);
        {
            s16 r = func_800B6DEC(D_800FAF5C, D_800F9B00, 5);
            D_800FAF5C->escapeTimer = r;
            if (D_800F9B00->grappleCtx & 2) {
                D_800FAF5C->escapeTimer = r + r / 2;
            }
        }
        func_800D7690(D_800FAF5C, 0, 0);
        D_800FAF5C->step++;
        return;
    case 3:
        if (!(D_800F9B00->grappleCtx & 0x10)) {
            D_800FAF5C->flags |= 0x0400400000000000ULL;
        }
        if (D_800F9B00->state != 0x72) {
            D_800FAF5C->step++;
            return;
        }
        if (D_800F9B00->pairSignals & 4) {
            D_800FAF5C->flags |= WR_FLAG_RERUN;
            D_800FAF5C->step++;
        } else {
            if (func_800D7894(D_800FAF5C, D_800FAF8A)) {
                if (D_800FAF78 != 0) {
                    D_800FAF5C->escapeTimer = 0;
                } else {
                    D_800F9B00->pairSignals |= 2;
                }
            }
        }
        if (!(D_800F9B00->grappleCtx & 0x10)) {
            func_800D2BAC(D_800FAF5C, D_800F9B00, 2.0f, 2);
        }
        return;
    case 4:
        {
            s16 anim = (D_800F9B00->grappleCtx & 0x10) ? 0x10AA
                      : (D_800F9B00->state == 0x72) ? ((D_800F9B00->pairSignals & 1) ? 0x10BC : 0x10BE)
                      : 0x10BE;
            func_800D427C(D_800FAF5C, anim, 0);
        }
        D_800FAF5C->step++;
    case 5:
        D_800FAF5C->flags |= 0x1000000000ULL;
        func_800D2B64(D_800FAF5C, 2.0f, 0, 2);
        func_800A7188(D_800FAF5C);
        return;
    }
}
