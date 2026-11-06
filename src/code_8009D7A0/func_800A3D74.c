/* @header
 * func_800A3D74
 * VRAM 0x800A3D74 | ROM 0x97214 | size 0xE0
 * asm: asm/nonmatchings/code_8009D7A0/func_800A3D74.s
 */
#include "common.h"

s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800B68A0(void *, void *, void *);
s8 func_800A83DC(void *, void *);
void func_800D4AD0(void *);

/* Interaction action on D_800EB408 with target D_800EB40C: drive the
 * interaction (flag mask 0xFFFFE); on the last animation frame run the connect
 * handler; and once the animation ends and the check succeeds, clear
 * attached[0], drop WR_FLAG_PAIR_LEADER and finish with command 0x2B. */
void func_800A3D74(void) {
    Wrestler *e;

    func_800D2BEC(D_800EB408, D_800EB40C, 0, 4.0f, 0, 0xFFFFE);
    if (D_800EB408->animFramesLeft == 1) {
        func_800B68A0(D_800EB408, D_800EB408, D_800EB40C);
    }
    if (D_800EB408->animFramesLeft <= 0 && func_800A83DC(D_800EB408, D_800EB40C) == 0) {
        e = D_800EB408;
        e->attached[0] = -1;
        e->flags &= ~WR_FLAG_PAIR_LEADER;
        func_800D4AD0(D_800EB408);
        func_800A6C48(D_800EB408, 0x2B);
    }
}
