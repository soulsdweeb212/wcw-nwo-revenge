/* @header
 * advanceTargetedAction  (originally func_800A64CC)
 * VRAM 0x800A64CC | ROM 0x9996C | size 0x11C
 * asm: asm/nonmatchings/code_8009D7A0/advanceTargetedAction.s
 */
#include "common.h"

s32 func_800D2B64(void *, f32, u16, s32);
void func_800D427C(void *, s32, s32);
void func_800D4AD0(void *);
void func_800D2600(void *, s32, f32);

/* Timed-action state machine (sibling of updateTimedAction). On the object
 * D_800EB408: step 0 starts animation 0xE7A; step 1 re-evaluates the current
 * target of D_800FAF5C (turning toward it unless it has flag 0x400000) and,
 * once the animation ends, runs the completion handler and issues command 0x2B. */
void advanceTargetedAction(void) {
    s8 targetId;
    func_800D2B64(D_800EB408, 1.0f, 0, 2);
    switch (D_800EB408->step) {
    case 0:
        func_800D427C(D_800EB408, 0xE7A, 3);
        D_800EB408->step++;
        break;
    case 1:
        targetId = func_800D26A0(D_800FAF5C, 0, -1);
        if (targetId != -1 && !(D_800F9D10[targetId].flags & 0x400000ULL))
            func_800D2600(D_800FAF5C, -1, 2.0f);
        if (D_800EB408->animFramesLeft <= 0) {
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
