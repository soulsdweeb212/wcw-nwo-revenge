#include "common.h"

typedef struct {s8 f0;u8 pad1[5];s16 f6;u8 pad8[2];s16 fA;s16 fC;u8 padE[0x12];u64 flags;u8 pad28[0x1B];u8 f43;u8 pad44[0x32D];u8 f371;} EntC6D;
extern EntC6D *D_800FAF5C;extern s32 D_800E3F20[],D_800FABD8;extern s8 D_800FADB8;extern s16 D_800F9D1A[][472];extern u16 D_800FA070[][472];extern s8 D_800FA063[][944];
void func_800D427C(void*,s32,s32);void func_800A7C40(void*,s8,s16);void func_800A7F6C(void*,s32);s16 func_800D5438(void*,s32);s8 func_800C2CDC(void*,s32);void func_800A837C(void*);void func_800E212C(void*);void func_800A7188(void*);s32 func_800D2B64(void*,f32,u16,s32);

/* Three-state action machine on D_800FAF5C's fC.  State 0 calls func_800E212C and
 * sends animation 0xB9/0xBA (0xBA when state fA==0x26) via
 * func_800A7C40/func_800D5438/func_800A7F6C.  State 1 finds a nearby entity
 * (func_800C2CDC(20)); if found it forwards func_800A837C and marks that entity's
 * per-entity word D_800FA070 (bit4 for state 0x74, also storing self's id into
 * D_800FA061, else bit0x10) or the linked entity D_800FA063->D_800FA070, then
 * advances (falling into state 2).  State 2 applies the approach separation
 * func_800D2B64 with a speed/timer chosen by self flag 0x100 and the fA groups
 * (2.0f/4.0f, timer 0xE/0xFFFFE) depending on f6 vs f371, then calls
 * func_800A7188. */
void func_800C6D54(void) {
 s8 matchIdx; s32 animId; EntC6D *self;
 switch(D_800FAF5C->fC) {
 case 0:
 func_800E212C(D_800FAF5C);
 if(D_800FAF5C->fA==0x26)animId=0xBA;else animId=0xB9;
 func_800A7C40(D_800FAF5C,D_800FADB8,animId);
 func_800D427C(D_800FAF5C,func_800D5438(D_800FAF5C,0),3);
 func_800A7F6C(D_800FAF5C,0);D_800FAF5C->fC++;break;
 case 1:
 D_800FABD8 &= ~D_800E3F20[D_800FADB8];
 matchIdx=func_800C2CDC(D_800FAF5C,20);
 if(matchIdx!=-1) {
 func_800A837C(D_800FAF5C);
 if(*(u64*)(D_800F9D30+matchIdx*0x3B0)&0x200000000000ULL) {
 if(D_800F9D1A[matchIdx][0]==0x74) {D_800FA070[matchIdx][0]|=4;*(s8*)((u8*)&D_800FA061+matchIdx*0x3B0)=D_800FAF5C->f0;}
 else D_800FA070[matchIdx][0]|=0x10;
 } else D_800FA070[D_800FA063[matchIdx][0]][0]|=0x10;
 D_800FAF5C->f43=0;D_800FAF5C->fC++;
 }
 case 2:
 self=D_800FAF5C;
 if(self->flags&0x100)func_800D2B64(self,2.f,0,0xFFFFE);
 else {
 switch((s16)(self->fA-7)) {
 case 0:case 15: if(self->f6>self->f371)func_800D2B64(self,2.f,0,0xE);break;
 case 24:case 25:case 26:case 29:case 30:case 31:case 78:case 79:
 if(self->f6>self->f371)func_800D2B64(self,4.f,0,0xFFFFE);else func_800D2B64(self,2.f,0,0xE);break;
 case 1:case 23:case 27:case 28:case 32:func_800D2B64(D_800FAF5C,2.f,0,0xE);break;
 }
 }
 func_800A7188(D_800FAF5C);break;
 }
}
