/* @header
 * func_800A3EF0
 * VRAM 0x800A3EF0 | ROM 0x97390 | size 0x138
 * asm: asm/nonmatchings/code_8009D7A0/func_800A3EF0.s
 */
#include "common.h"

void func_800A9290(void *);
void func_800B68A0(void *, void *, void *);
void func_800C472C(void *, void *, s32);
s32 func_800D2B64(void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
/* Three-step action machine on D_800EB408 (step):
 *   0: enter the action, advance to step 1
 *   1: start animation 0xFC7 when flag 0x200000 is set, else 0xFC6; hand the
 *      action off to the holder D_800EB414; advance to step 2
 *   2: run the boundary-correction/timer update; when the animation ends,
 *      exit the action back to step 1, decrement escapeTimer by 15 and
 *      tell the holder. */
void func_800A3EF0(void) {
    s32 animId;
    switch (D_800EB408->step) {
    case 0: func_800A9290(D_800EB408); D_800EB408->step++; break;
    case 1:
        if (D_800EB408->flags & 0x200000) animId = 0xFC7; else animId = 0xFC6;
        func_800D427C(D_800EB408, animId, 6);
        func_800B68A0(D_800EB414, D_800EB414, D_800EB408);
        D_800EB408->step++; break;
    case 2:
        func_800D2B64(D_800EB408, 4.0f, 0, 0xFFFFE);
        if (D_800EB408->animFramesLeft <= 0) {
            func_800D4AD0(D_800EB408); func_800A6C48(D_800EB408, 0x2C);
            D_800EB408->step = 1; D_800EB408->escapeTimer -= 15;
            func_800C472C(D_800EB414, D_800EB408, 1);
        } break;
    }
}
