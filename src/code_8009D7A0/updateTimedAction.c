/* @header
 * updateTimedAction  (originally func_800A6108)
 * VRAM 0x800A6108 | ROM 0x995A8 | size 0x13C
 * asm: asm/nonmatchings/code_8009D7A0/updateTimedAction.s
 */
#include "common.h"

extern s32 D_800F9B0C;
s32 func_800D2B64(void *, f32, u16, s32);
s32 func_800D3684(s32, s32);
s32 func_800D35B0(s32, s32);
s32 func_800D4D44(void *, s32, s32);
void func_800D427C(void *, s32, s32);

/* Tick a timed turn: on entry (step 0) zero stateTimer, set turnPerTick to 1/20
 * of the turn from the heading to the target held in turnPerTick and fall into
 * step 1, which steps the heading toward it. Animation 0xF5B chains the next
 * animation when it ends. After 0x15 ticks it issues the follow-up command
 * (0x2D for animation 0xF5A, otherwise 1). */
void updateTimedAction(void)
{
    func_800D2B64(D_800EB408, 1.0f, 0, 2);

    switch (D_800EB408->step) {
    case 0:
        D_800EB408->stateTimer = 0;
        D_800EB408->turnPerTick = func_800D3684(D_800EB408->turnPerTick, D_800EB408->heading) / 20;
        D_800EB408->step++;
    case 1:
        D_800EB408->heading = func_800D35B0(D_800EB408->heading, D_800EB408->turnPerTick);
        if (D_800EB408->animId == 0xF5B && D_800EB408->animFramesLeft <= 0) {
            func_800D427C(D_800EB408, (s16)func_800D4D44(D_800EB408, 1, D_800F9B0C), 2);
        }
        if (++D_800EB408->stateTimer >= 0x15) {
            if (D_800EB408->animId == 0xF5A)
                func_800A6C48(D_800EB408, 0x2D);
            else
                func_800A6C48(D_800EB408, 1);
        }
        break;
    }
}
