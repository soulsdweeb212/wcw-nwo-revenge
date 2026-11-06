/* @header
 * func_800CDEE4
 * VRAM 0x800CDEE4 | ROM 0xC1384 | size 0x5C
 * asm: asm/nonmatchings/code_800BBA00/func_800CDEE4.s
 */
#include "common.h"

void translateEntityXZ(void*,void*);s32 func_800D35B0(s32,s32);void func_800D3E40(void*,void*,s32,void*);
/* Duration (in frames) of a grab/reaction, stored by the callers in self->stateTimer: 30 when other is
 * SPECIAL (WR_FLAG_SPECIAL); otherwise from self->grappleCtx: 90 with bit 0x2 (unless 0x300 is set), else 60. */
s32 func_800CDEE4(Wrestler *self,Wrestler *other){
    s32 r;
    if(other->flags&WR_FLAG_SPECIAL){
        r=30;
    }else{
        s32 flags=self->grappleCtx;
        r=60;
        if(flags&2)r=90;
        if(flags&0x300)r=60;
    }
    return r;
}
