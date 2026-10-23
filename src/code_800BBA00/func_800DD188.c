#include "common.h"

/* Three-state paired-action driver on self D_800FAF5C:
 * 0) start the action when func_800B60C8 agrees and arm the animation,
 * 1) clear the action's input mask and advance when func_800DB4FC completes,
 * 2) run func_800DB348 until the timer expires, then finish (combo) or clear. */
extern void *D_800FAF5C,*D_800F9B00;
extern s32 D_800E3F20[],D_800FABD8;
extern s8 D_800FADB8;
void func_800A7C40(void *,s8,s16); void func_800A7D1C(void *,s32); void func_800A7F6C(void *,s32); void beginEntityActionA8D8C(void *); void func_800B68A0(void *,void *,void *); void addEntityHealthDelta(void *,s32); void func_800D427C(void *,s16,s32); void func_800D4AD0(void *); s8 func_800D4CC4(void *); s16 func_800D5438(void *,s32); s32 func_800DACE4(void *,void *); void func_800DB348(void *,void *); s8 func_800DB4FC(void *,void *); s8 func_800B60C8(void *,void *);
void func_800DD188(void) {
 void *actor;
 switch(((Nw2F408 *)D_800FAF5C)->fC) {
 case 0:
 if(func_800B60C8(D_800FAF5C,D_800F9B00)) {
 func_800A7C40(D_800FAF5C,D_800FADB8,0xE7);
 func_800D427C(D_800FAF5C,func_800D5438(D_800FAF5C,0),1);
 func_800A7F6C(D_800FAF5C,0);
 func_800DACE4(D_800FAF5C,D_800F9B00);
 ((Nw2F408 *)D_800FAF5C)->fC++;
 } break;
 case 1:
 D_800FABD8&=~D_800E3F20[D_800FADB8];
 if(func_800DB4FC(D_800FAF5C,D_800F9B00))((Nw2F408 *)D_800FAF5C)->fC++;
 case 2:
 func_800DB348(D_800FAF5C,D_800F9B00);
 if(((Nw2F408 *)D_800FAF5C)->f4<=0) {
 func_800D4AD0(D_800FAF5C);actor=D_800FAF5C;
 if(((Nw2F408 *)actor)->fC==1) {
 func_800A7D1C(actor,0x23);func_800B68A0(D_800FAF5C,D_800FAF5C,D_800FAF5C);
 if(func_800D4CC4(actor))addEntityHealthDelta(actor,*(s8 *)((u8 *)actor+0x3A2));
 beginEntityActionA8D8C(actor);
 }else func_800A6C48(actor,0x2B);
 } break;
 }
}
