/* @header
 * func_800CDF40
 * VRAM 0x800CDF40 | ROM 0xC13E0 | size 0x1E4
 * asm: asm/nonmatchings/code_800BBA00/func_800CDF40.s
 */
#include "common.h"

/* Attack-eligibility tick for a wrestler: count down self->stateTimer (reset to 0
 * first when func_800A93C0 (a global check; it takes no argument) is true or
 * inputBits has 0x10); when it goes negative, start the animation picked from
 * self->grappleCtx bits 0x400/0x40/0x80/0x100/0x200 (0xE8C..0xE9C, the last set
 * bit wins) and return 2. Otherwise latch grappleCtx bit 0x200000
 * and return 1 when flag is set and grappleCtx has 0x401 or isEntityActionEligible
 * passes for 0x7E or 0x6E; else return 1 with *animOut = accepted input bits
 * (0xC028 with grappleCtx 0x40, 0xC004 without) | (animBits & 0xF00), 3 for input
 * 0x20 with grappleCtx 0x400 (and not 0x40), or 0. */
s8 func_800A93C0(void*);s8 isEntityActionEligible(void*,s32,s32);void func_800D427C(void*,s16,s32);
s32 func_800CDF40(Wrestler*self,u16 animBits,u16 inputBits,s16 flag,s16*animOut){
    s16 action;
    s32 bits,mask;
    if(func_800A93C0(self))self->stateTimer=0;
    if(inputBits&0x10)self->stateTimer=0;
    if(--self->stateTimer<0){
        s32 state=self->grappleCtx;
        if(state&0x400)action=0xE8C;
        if(state&0x40)action=0xE90;
        if(state&0x80)action=0xE94;
        if(state&0x100)action=0xE98;
        if(state&0x200)action=0xE9C;
        func_800D427C(self,action,1);
        return 2;
    }
    bits=self->grappleCtx;
    if(((bits&0x401)==0x401)&((s8)flag!=0)){
        self->grappleCtx|=0x200000;
        return 1;
    }
    if(isEntityActionEligible(self,0,0x7E)&&(s8)flag){
        self->grappleCtx|=0x200000;
        return 1;
    }
    if(isEntityActionEligible(self,0,0x6E)&&(s8)flag){
        self->grappleCtx|=0x200000;
        return 1;
    }
    bits=self->grappleCtx;
    if(bits&0x40){
        mask=inputBits&0xC028;
        if(mask){
            *animOut=mask|(animBits&0xF00);
            return 1;
        }
    }else{
        mask=inputBits&0xC004;
        if(mask){
            *animOut=mask|(animBits&0xF00);
            return 1;
        }
        if((bits&0x400)&&(inputBits&0x20))return 3;
    }
    return 0;
}
