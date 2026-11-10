/* @header
 * advanceAttackAction  (originally func_8009F654)
 * VRAM 0x8009F654 | ROM 0x92AF4 | size 0xE8
 * asm: asm/nonmatchings/code_8009D7A0/advanceAttackAction.s
 */
#include "common.h"

void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
s32 func_800D2B64(void *, f32, u16, s32);
#endif
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s32);
#endif
extern s8 D_800FADB8;

/* Attack action on D_800EB408: step 0 plays animation 0xAE, sets the action
 * from func_800D5438 and runs the two setup handlers; step 1 drives the action
 * until animFramesLeft equals the step (1), then completes with command
 * 0x2B. */
void advanceAttackAction(void) {
    s16 step = D_800EB408->step;
    switch (step) {
    case 0:
        func_800A7C40(D_800EB408, D_800FADB8, 0xAE);
        func_800D427C(D_800EB408, func_800D5438(D_800EB408, 0), 1);
        func_800A7F6C(D_800EB408, 0);
        func_800A837C(D_800EB408);
        D_800EB408->step++;
        break;
    case 1:
        func_800D2B64(D_800EB408, 1.0f, 0, 0xFFFFE);
        if (D_800EB408->animFramesLeft == step) {
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
