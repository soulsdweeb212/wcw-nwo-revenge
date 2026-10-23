#include "common.h"

extern void *D_800FABD0, *D_800FAF58, *D_800F9B60;
extern s16 D_800E3CF0[]; extern s32 D_800E3D00[]; extern f64 D_800E5260;
s32 func_800D3650(void *,void *); f32 func_800D3890(void *,void *,void *); s32 func_800D4148(void); s8 func_800D4198(s16);
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define W(p,o) (*(s32 *)((u8 *)(p)+(o)))
/* 'Seek/approach' action. State 0 aims the entity toward D_800F9B60, choosing
 * the animation from the facing (with a small random jitter when off-axis) and
 * filling in the 0x6 animation and 0xE timer; state 1 counts that timer down and
 * raises the 0x8 flag when it expires; state 2 holds until the entity leaves
 * stance 3/4, then resets the action. */
void func_800B1240(void) {
 f32 pos[3]; s32 dir; s32 jitter; s16 entityState; void *other;
 switch(H(D_800FABD0,4)) {
 case 0:
 pos[0]=0; pos[2]=0;
 dir=func_800D3650((u8 *)D_800F9B60+0x6C,(u8 *)D_800FAF58+0x6C);
 if(func_800D3890(pos,(u8 *)D_800FAF58+0x6C,0)>D_800E5260) {
 if(func_800D3550(func_800D3684(D_800E3D00[(s16)func_800D3650(pos,(u8 *)D_800FAF58+0x6C)],D_800E3D00[(s16)dir]))<0x300) {
 jitter=func_800D4198(500)?0:-2;
 dir=(dir+(jitter|2))&7;
 }
 }
 H(D_800FABD0,6)=D_800E3CF0[(s16)dir]|4;
 H(D_800FABD0,14)=(func_800D4148()&7)+8;
 H(D_800FABD0,4)++;
 break;
 case 1:
 if(--H(D_800FABD0,14)<0) { H(D_800FABD0,8)=0xF00; H(D_800FABD0,4)++; }
 break;
 case 2:
 if(H(D_800FAF58,10)==3) H(D_800FABD0,8)=0xF00;
 else if(H(D_800FAF58,10)!=4) {
 other=D_800F9B60;
 H(D_800FABD0,2)=0; H(D_800FABD0,4)=0;
 entityState=H(other,10);
 W(D_800FABD0,0x5C)&=~7;
 H(D_800FABD0,0x2E)=entityState;
 }
 break;
 }
}
