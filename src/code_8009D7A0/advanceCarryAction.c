/* @header
 * advanceCarryAction  (originally func_800A3970)
 * VRAM 0x800A3970 | ROM 0x96E10 | size 0x104
 * asm: asm/nonmatchings/code_8009D7A0/advanceCarryAction.s
 */
#include "common.h"

void beginEntityActionA8D8C(void *);
void func_800C472C(void *, void *, s32);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s32);
#endif
void func_800D7E80(void *, void *);
void func_800D8D74(void *, s32);

/* Action state machine for an entity (D_800EB408) carrying/attaching to
 * D_800EB40C. State 0 plays the carry animation and attaches to the target,
 * then falls into state 1, which drives the attach with a 0xFFFFE flag mask and,
 * once the animation ends (animFramesLeft <= 0), releases and hands control back. */
void advanceCarryAction(void) {
    switch (D_800EB408->step) {
    case 0:
        func_800D427C(D_800EB408, func_800D5438(D_800EB40C, 1), 2);
        func_800D7E80(D_800EB408, D_800EB40C);
        D_800EB408->step++;
    case 1:
        func_800D8D74(D_800EB408, 0);
        func_800D2BEC(D_800EB408, D_800EB40C, 0, 2.0f, 0, 0xFFFFE);
        if (D_800EB408->animFramesLeft <= 0) {
            func_800D4AD0(D_800EB408);
            beginEntityActionA8D8C(D_800EB408);
            func_800C472C(D_800EB40C, D_800EB408, 2);
        }
        break;
    }
}
