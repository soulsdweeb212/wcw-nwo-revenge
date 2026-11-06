/* @header
 * func_800A5F34
 * VRAM 0x800A5F34 | ROM 0x993D4 | size 0x1D4
 * asm: asm/nonmatchings/code_8009D7A0/func_800A5F34.s
 */
#include "common.h"

/* Two-step heavy-turn action on self D_800EB408: 0) aim the heading from
 * D_800F9B14 (turned by 0x800 if nearly aligned with the opponent) into the
 * opponent's turnPerTick, play the turn animation, store a sixth of the turn in
 * self's turnPerTick and zero stateTimer; 1) step the heading for 7 ticks, then
 * clear the action on the last animation frame or once the opponent leaves
 * state 0x84. */
extern s32 D_800F9B14;
s32 func_800D2B64(void *,f32,u16,s32);
s32 func_800D35B0(s32,s32);
void func_800D427C(void *,s32,s32);
void func_800D4AD0(void *);
void func_800A5F34(void) {
    s32 angle,delta;
    s32 *heading;
    Wrestler *self;
    Wrestler *selfCopy;
    func_800D2B64(D_800EB408,1.0f,0,2);
    switch(D_800EB408->step) {
    case 0:
        heading=&D_800F9B14;
        if(func_800D3550(func_800D3684(*heading,D_800EB40C->heading))<0x400)
            angle=func_800D35B0(*heading,0x800);
        else angle=*heading;
        D_800EB40C->turnPerTick=angle;
        func_800D427C(D_800EB408,((~func_800D3684(angle,D_800EB40C->heading)>>31)&0xF5F)|0xF5E,3);
        delta=func_800D3684(D_800F9B14,D_800EB408->heading)/6;
        D_800EB408->stateTimer=0;
        D_800EB408->step++;
        D_800EB408->turnPerTick=delta;
    case 1:
        if(++D_800EB408->stateTimer<7)
            D_800EB408->heading=func_800D35B0(D_800EB408->heading,D_800EB408->turnPerTick);
        if(D_800EB408->animFramesLeft==1 || D_800EB40C->state!=0x84) {
            self=D_800EB408;
            self->attached[0]=-1;
            self->flags&=(selfCopy=D_800EB408,~WR_FLAG_PAIR_LEADER);
            func_800D4AD0(selfCopy);
            func_800A6C48(D_800EB408,0x2B);
        }
        break;
    }
}
