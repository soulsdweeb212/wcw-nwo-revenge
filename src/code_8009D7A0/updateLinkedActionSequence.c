#include "common.h"

extern void *D_800EB40C;
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800B68A0(void *, void *, void *);
void func_800CE388(void *, s32, void *);
s8 func_800CE6E4(void *, s32);
s32 func_800D2B64(void *,f32,u16,s32);
void func_800D4AD0(void *);
void func_800A6C48(void *, s32);
extern s32 D_800F9B24[][4];
extern s8 D_800FADB8;
/* Three-state handler for a linked action on the D_800EB408 object (state +0xC).
 * State 0 kicks off the paired action using the D_800F9B24 record for the
 * current entity, sets animation 0x54 and advances. State 1 waits for the
 * paired action to finish. State 2 runs boundary correction while the timer
 * counts down, then tears the action down and returns to action 0x2B. */
void updateLinkedActionSequence(void) {
 u8 *p;
 void *q;
 switch (((Nw2F408 *)D_800EB408)->fC) {
 case 0:
  func_800CE388(D_800EB408,(s32)D_800EB40C,D_800F9B24[D_800FADB8]);
  func_800A7F6C(D_800EB408,0x54);
  func_800A837C(D_800EB408);
  ((Nw2F408 *)D_800EB408)->fC++;
 case 1:
  if(func_800CE6E4(D_800EB408,D_800F9B24[D_800FADB8][0])) ((Nw2F408 *)D_800EB408)->fC++;
  break;
 case 2:
  if(((Nw2F408 *)D_800EB408)->f6>=0x2C) func_800D2B64(D_800EB408,2.0f,0,0xFFFFE);
  if(((Nw2F408 *)D_800EB408)->f4<=0) {
   func_800B68A0(D_800EB408,D_800EB408,D_800EB40C);
   p=D_800EB408;
   *(volatile s8 *)(p+0x362)=-1;
   *(volatile u64 *)(p+0x20)&=(q=D_800EB408,~0x40000000ULL);
   func_800D4AD0(q);
   func_800A6C48(D_800EB408,0x2B);
  }
  break;
 }
}
