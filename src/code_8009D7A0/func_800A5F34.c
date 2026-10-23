#include "common.h"

/* Two-stage heavy-turn action on self D_800EB408: 0) aim the heading toward
 * the target (snapping by 0x800 if nearly aligned), play the turn animation,
 * store a per-frame step and start the counter; 1) step the heading each of 7
 * frames, then clear the action (also when the opposing state ends). */
extern void *D_800EB40C;
extern s32 D_800F9B14;
s32 func_800D2B64(void *,f32,u16,s32);
s32 func_800D35B0(s32,s32);
void func_800D427C(void *,s32,s32);
void func_800D4AD0(void *);
#define F(p,o,t) (*(t *)((u8 *)(p)+(o)))
void func_800A5F34(void) {
 s32 angle,delta;
 s32 *heading;
 u8 *self;
 void *selfCopy;
 func_800D2B64(D_800EB408,1.0f,0,2);
 switch(((Nw2F408 *)D_800EB408)->fC) {
 case 0:
 heading=&D_800F9B14;
 if(func_800D3550(func_800D3684(*heading,F(D_800EB40C,0x58,s32)))<0x400)
 angle=func_800D35B0(*heading,0x800);
 else angle=*heading;
 F(D_800EB40C,0x348,s32)=angle;
 func_800D427C(D_800EB408,((~func_800D3684(angle,F(D_800EB40C,0x58,s32))>>31)&0xF5F)|0xF5E,3);
 delta=func_800D3684(D_800F9B14,F(D_800EB408,0x58,s32))/6;
 F(D_800EB408,0x16,s16)=0;
 ((Nw2F408 *)D_800EB408)->fC++;
 F(D_800EB408,0x348,s32)=delta;
 case 1:
 if(++F(D_800EB408,0x16,s16)<7)
 F(D_800EB408,0x58,s32)=func_800D35B0(F(D_800EB408,0x58,s32),F(D_800EB408,0x348,s32));
 if(((Nw2F408 *)D_800EB408)->f4==1 || F(D_800EB40C,0xA,s16)!=0x84) {
 self=D_800EB408;
 F(self,0x362,volatile s8)=-1;
 F(self,0x20,volatile u64)&=(selfCopy=D_800EB408,~0x40000000ULL);
 func_800D4AD0(selfCopy);
 func_800A6C48(D_800EB408,0x2B);
 }
 break;
 }
}
