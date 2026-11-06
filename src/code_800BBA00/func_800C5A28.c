/* @header
 * func_800C5A28
 * VRAM 0x800C5A28 | ROM 0xB8EC8 | size 0x320
 * asm: asm/nonmatchings/code_800BBA00/func_800C5A28.s
 */
#include "common.h"

extern s32 D_800E3F20[],D_800FABD8;extern s8 D_800FADB8;extern u16 D_800FAF8E[];
void func_800D427C(void*,s32,s32);void func_800A7C40(void*,s8,s16);void func_800A7F6C(void*,s32);s16 func_800D5438(void*,s32);s8 func_800C2CDC(void*,s32);void func_800C3A78(void*,void*,s32);void func_800C5FBC(void*);void func_800D25D0(void*,f32);void func_800A7188(void*);s32 func_800D2B64(void*,f32,u16,s32);

/* Step machine on D_800FAF5C->step.  State 0 picks the attack animation
 * (5/6 by the 0xF00 bits of D_800FAF8E when flag 0x100000000000000 is set, else
 * 0x9D/0x9F) and sends it, then jumps to state 2.  State 1 re-sends move.moveCode and falls
 * through; state 2 sends the range-based animation via
 * func_800D427C/func_800A7F6C; state 3 clears the entity bit, runs func_800C5FBC
 * and, on finding a close entity (func_800C2CDC(1)), advances and hands that
 * entity to func_800C3A78(entity, ..., 2); state 4 applies the approach separation
 * func_800D2B64 with a scale/timer chosen by flag 0x100 and the state groups,
 * depending on animFrame vs anim.hitEnd, and ends with func_800A7188. */
void func_800C5A28(void) {
    s8 matchIdx; s32 animId; f32 scale; Wrestler *self;
    switch(D_800FAF5C->step) {
    case 0:
        if(D_800FAF5C->flags&0x100000000000000ULL) {
            if(D_800FAF8E[D_800FADB8]&0xF00)animId=6;else animId=5;
        }else animId=(D_800FAF8E[D_800FADB8]&0xF00)?0x9F:0x9D;
        func_800A7C40(D_800FAF5C,D_800FADB8,animId);
        D_800FAF5C->step=2;D_800FAF5C->flags|=WR_FLAG_RERUN;
        break;
    case 1:
        func_800A7C40(D_800FAF5C,D_800FADB8,D_800FAF5C->move.moveCode);
        D_800FAF5C->step++;
    case 2:
        func_800D427C(D_800FAF5C,func_800D5438(D_800FAF5C,0),3);
        func_800A7F6C(D_800FAF5C,0);D_800FAF5C->step++;
    case 3:
        D_800FABD8 &= ~D_800E3F20[D_800FADB8];
        func_800C5FBC(D_800FAF5C);matchIdx=func_800C2CDC(D_800FAF5C,1);
        if(matchIdx!=-1) {D_800FAF5C->step++;func_800C3A78(D_800FAF5C,&D_800F9D10[matchIdx],2);}
    case 4:
        scale=2.f;func_800D25D0(D_800FAF5C,scale);self=D_800FAF5C;
        if(self->flags&0x100) func_800D2B64(self,scale,0,0xFFFFE);
        else {
            switch((s16)(self->state-7)) {
            case 15: if(self->animFrame>self->anim.hitEnd)func_800D2B64(self,2.f,0,0xE);break;
            case 0: case 24: case 25: case 26: case 29: case 30: case 31: case 78: case 79:
                if(self->animFrame>self->anim.hitEnd)func_800D2B64(self,4.f,0,0xFFFFE);else func_800D2B64(self,2.f,0,0xE);break;
            case 1: case 23: case 27: case 28: case 32:func_800D2B64(D_800FAF5C,2.f,0,0xE);break;
            }
        }
        func_800A7188(D_800FAF5C);break;
    }
}
