/* @header
 * advanceTwoPhaseAction  (originally func_800A4D74)
 * VRAM 0x800A4D74 | ROM 0x98214 | size 0xF4
 * asm: asm/nonmatchings/code_8009D7A0/advanceTwoPhaseAction.s
 */
#include "common.h"

#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
s32 func_800D2B64(void *, f32, u16, s32);
#endif
void func_800D427C(void *, s32, s32);
void func_800D4AD0(void *);

/* Two-phase action on D_800EB408: step 0 plays animation 0xEBA and zeroes
 * stateTimer; step 1 counts stateTimer up and waits for the last animation frame
 * (animFramesLeft == 1); step 2 plays animation 0xEBB; step 3 waits for the last
 * frame. Either waiting step finishes with command 0x2B. */
void advanceTwoPhaseAction(void) {
    s16 step;

    func_800D2B64(D_800EB408, 1.0f, 0, 2);
    step = D_800EB408->step;
    switch (step) {
    case 0:
        func_800D427C(D_800EB408, 0xEBA, 3);
        D_800EB408->stateTimer = 0;
        D_800EB408->step++;
        break;
    case 1:
        D_800EB408->stateTimer++;
        if (D_800EB408->animFramesLeft == 1) {
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    case 2:
        func_800D427C(D_800EB408, 0xEBB, 3);
        D_800EB408->step++;
        break;
    case 3:
        if (D_800EB408->animFramesLeft == 1) {
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
