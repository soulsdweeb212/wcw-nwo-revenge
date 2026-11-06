/* @header
 * func_800A5D64
 * VRAM 0x800A5D64 | ROM 0x99204 | size 0x128
 * asm: asm/nonmatchings/code_8009D7A0/func_800A5D64.s
 */
#include "common.h"

s32 beginEntityActionA8D8C(void *);
s32 func_800C472C(void *, void *, s32);
s32 func_800D427C(void *, s16, s32);
s32 func_800D4AD0(void *);
s16 func_800D5438(void *, s32);
s32 func_800D7E80(void *, void *);
s32 func_800D8D74(void *, s32);

/* Two-step action machine for D_800EB408, driven by the opponent D_800EB40C's
 * grappleCtx bit 0x04000000:
 *   0: pick animation func_800D5438(D_800EB40C,1) and start it (arg 3 when the
 *      bit is set, else arg 2 plus a func_800D7E80 handoff), then advance.
 *   1: while the bit is clear, stop the sub-action; once the animation ends,
 *      end the action, queue the follow-up and notify D_800EB40C. */
void func_800A5D64(void) {
    s16 step;

    step = D_800EB408->step;
    switch (step) {
    case 0:
        if (D_800EB40C->grappleCtx & 0x04000000) {
            func_800D427C(D_800EB408, func_800D5438(D_800EB40C, 1), 3);
        } else {
            func_800D427C(D_800EB408, func_800D5438(D_800EB40C, 1), 2);
            func_800D7E80(D_800EB408, D_800EB40C);
        }
        D_800EB408->step = (s16)((u16)D_800EB408->step + 1);
        return;
    case 1:
        if (!(D_800EB40C->grappleCtx & 0x04000000)) {
            func_800D8D74(D_800EB408, 0);
        }
        if (D_800EB408->animFramesLeft <= 0) {
            func_800D4AD0(D_800EB408);
            beginEntityActionA8D8C(D_800EB408);
            func_800C472C(D_800EB40C, D_800EB408, 2);
        }
        return;
    }
}
