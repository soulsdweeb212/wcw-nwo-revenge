/* @header
 * func_800A5BA4
 * VRAM 0x800A5BA4 | ROM 0x99044 | size 0x1C0
 * asm: asm/nonmatchings/code_8009D7A0/func_800A5BA4.s
 */
#include "common.h"

/* Two-step run/charge action on self D_800EB408:
 * 0) copy the opponent's dirIndex, choose the run animation by whether the
 *    opponent's heading is roughly aligned with that side's direction (else
 *    set grappleCtx bit 0x40), then arm the anim;
 * 1) run the move until the animation ends; if the follow-up test fails, clear
 *    the pair link and hand back. */
void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
s8 func_800A83DC(void *, void *);
void func_800B68A0(void *, void *, void *);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s32);
#endif
void func_800D7E80(void *, s32);
void func_800D8D74(void *, s32);
extern s32 D_800E3CC0[];
extern s8 D_800FADB8;

void func_800A5BA4(void) {
    Wrestler *self;
    Wrestler *opp;
    Wrestler *selfCopy;
    u16 facing;
    s16 animId;
    s32 angleDiff;

    switch (D_800EB408->step) {
    case 0:
        opp = D_800EB40C;
        facing = opp->dirIndex;
        D_800EB408->dirIndex = facing;
        angleDiff = func_800D3550(func_800D3684(opp->heading, D_800E3CC0[(s16)facing]));
        if (angleDiff < 0x400) {
            animId = 0x78;
        } else {
            animId = 0x79;
            D_800EB408->grappleCtx |= 0x40;
        }
        func_800A7C40(D_800EB408, D_800FADB8, animId);
        func_800D427C(D_800EB408, func_800D5438(D_800EB408, 0), 2);
        func_800A7F6C(D_800EB408, 0);
        func_800A837C(D_800EB408);
        func_800D7E80(D_800EB408, 0);
        D_800EB408->step++;
    case 1:
        func_800D8D74(D_800EB408, 0);
        if (D_800EB408->animFramesLeft == 1)
            func_800B68A0(D_800EB408, D_800EB408, D_800EB40C);
        if (D_800EB408->animFramesLeft <= 0) {
            if ((func_800A83DC(D_800EB408, D_800EB40C) << 24) == 0) {
                self = D_800EB408;
                self->attached[0] = -1;
                self->flags &= (selfCopy = D_800EB408, ~WR_FLAG_PAIR_LEADER);
                func_800D4AD0(selfCopy);
                func_800A6C48(D_800EB408, 0x2B);
            }
        }
        break;
    }
}
