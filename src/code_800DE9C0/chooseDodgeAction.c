/* @header
 * chooseDodgeAction  (originally func_800DFC8C)
 * VRAM 0x800DFC8C | ROM 0xD312C | size 0x148
 * asm: asm/nonmatchings/code_800DE9C0/chooseDodgeAction.s
 */
#include "common.h"

extern u16 D_800E3CD0[], D_800E3CD8[];
/* Chooses a dodge/counter action for w based on its ringSide against the
 * incoming direction mask: the two ringSide tables pick actions 0x1B and
 * 0x1C, then the attacker's zone flags (WR_FLAG_IN_RING / WR_FLAG_ON_FLOOR) do
 * the same. If the attacker is WR_FLAG_ON_APRON, w's 0x8000000000 flag is set
 * only when func_800D3684(w->heading, dir->angle) <= 0, and action 0x1D is
 * played. */
void chooseDodgeAction(Wrestler *w,Wrestler *attacker,s32 mask,Nw2DirectionResult *dir) {
    s32 index=w->ringSide;
    if (D_800E3CD8[index]&mask) func_800A6C48(w,0x1B);
    else if (D_800E3CD0[index]&mask) func_800A6C48(w,0x1C);
    else if (attacker->flags&WR_FLAG_IN_RING) func_800A6C48(w,0x1B);
    else if (attacker->flags&WR_FLAG_ON_FLOOR) func_800A6C48(w,0x1C);
    else if (attacker->flags&WR_FLAG_ON_APRON) {
        w->flags&=~0x8000000000ULL;
        if (func_800D3684(w->heading,dir->angle)<=0) w->flags|=0x8000000000ULL;
        func_800A6C48(w,0x1D);
    }
}
