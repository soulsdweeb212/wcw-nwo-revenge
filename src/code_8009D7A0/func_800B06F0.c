/* @header
 * func_800B06F0
 * VRAM 0x800B06F0 | ROM 0xA3B90 | size 0x140
 * asm: asm/nonmatchings/code_8009D7A0/func_800B06F0.s
 */
#include "common.h"

typedef struct {s16 f0,f2,f4,f6,f8,fA;u8 padC[0x22];u16 f2E;u8 pad30[0x2C];u32 f5C;u8 pad60[0xC];f32 pos[3];} B06Obj;
extern B06Obj *D_800FABD0,*D_800FAF58,*D_800F9B60;
extern u16 D_800E3CF0[];
s32 func_800D3650(void *,void *);
s8 func_800D4198(s16);
void func_800B06F0(void) {
 s16 state;
 u16 anim;
 switch(D_800FABD0->f4) {
 case 0:
  D_800FABD0->f8=8;
  anim=D_800E3CF0[(s16)func_800D3650(D_800FAF58->pos,D_800F9B60->pos)];
  D_800FABD0->f6=anim;
  state=D_800FAF58->fA;
  if(state!=1) {
   if(state==0x60) {D_800FABD0->f4++;return;}
   {B06Obj *g=D_800F9B60;u16 oldState;
   D_800FABD0->f2=0;
   D_800FABD0->f4=0;
   oldState=g->fA;
   D_800FABD0->f5C&=~7;
   D_800FABD0->f2E=oldState;}
  }
  return;
 case 1:
  if(func_800D4198(500)) D_800FABD0->f6=8;
  if(D_800FAF58->fA!=0x60) {
   B06Obj *g=D_800F9B60;
   D_800FABD0->f2=0;
   D_800FABD0->f4=0;
   D_800FABD0->f2E=g->fA;
   D_800FABD0->f5C&=~7;
  }
  break;
 }
}
