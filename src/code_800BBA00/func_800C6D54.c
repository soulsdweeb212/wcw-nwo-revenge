/* @header
 * func_800C6D54
 * VRAM 0x800C6D54 | ROM 0xBA1F4 | size 0x328
 * asm: asm/nonmatchings/code_800BBA00/func_800C6D54.s
 */
#include "common.h"

extern s32 D_800E3F20[],D_800FABD8;extern s8 D_800FADB8;
void func_800D427C(void*,s32,s32);void func_800A7C40(void*,s8,s16);void func_800A7F6C(void*,s32);s16 func_800D5438(void*,s32);s8 func_800C2CDC(void*,s32);void func_800A837C(void*);void func_800E212C(void*);void func_800A7188(void*);s32 func_800D2B64(void*,f32,u16,s32);

/* Three-step machine on D_800FAF5C->step.  Step 0 calls func_800E212C and
 * sends animation 0xB9/0xBA (0xBA when state==0x26) via
 * func_800A7C40/func_800D5438/func_800A7F6C.  Step 1 finds a nearby wrestler
 * (func_800C2CDC(20)); if found it forwards func_800A837C and marks that wrestler's
 * pairSignals (bit4 for state 0x74, also storing self's id into its heldById,
 * else bit0x10) or its opponent's pairSignals, then advances (falling into
 * step 2).  Step 2 applies the approach separation func_800D2B64 with a
 * speed/timer chosen by self flag 0x100 and the state groups (2.0f/4.0f, timer
 * 0xE/0xFFFFE) depending on animFrame vs anim.hitEnd, then calls func_800A7188. */
void func_800C6D54(void) {
    s8 matchIdx; s32 animId; Wrestler *self;
    switch(D_800FAF5C->step) {
    case 0:
        func_800E212C(D_800FAF5C);
        if(D_800FAF5C->state==0x26)animId=0xBA;else animId=0xB9;
        func_800A7C40(D_800FAF5C,D_800FADB8,animId);
        func_800D427C(D_800FAF5C,func_800D5438(D_800FAF5C,0),3);
        func_800A7F6C(D_800FAF5C,0);D_800FAF5C->step++;break;
    case 1:
        D_800FABD8 &= ~D_800E3F20[D_800FADB8];
        matchIdx=func_800C2CDC(D_800FAF5C,20);
        if(matchIdx!=-1) {
            func_800A837C(D_800FAF5C);
            if(D_800F9D10[matchIdx].flags&0x200000000000ULL) {
                if(D_800F9D10[matchIdx].state==0x74) {D_800F9D10[matchIdx].pairSignals|=4;D_800F9D10[matchIdx].heldById=D_800FAF5C->id;}
                else D_800F9D10[matchIdx].pairSignals|=0x10;
            } else D_800F9D10[D_800F9D10[matchIdx].opponentId].pairSignals|=0x10;
            D_800FAF5C->comboHits=0;D_800FAF5C->step++;
        }
    case 2:
        self=D_800FAF5C;
        if(self->flags&0x100)func_800D2B64(self,2.f,0,0xFFFFE);
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
