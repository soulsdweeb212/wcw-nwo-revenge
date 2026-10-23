#include "common.h"

/* Three-state turn/move action on self D_800FAF5C:
 * 0) choose the turn animation and reset the frame counter,
 * 1) advance the turn each frame (switching to the follow-up action id and
 *    setting state 7 when the opponent is in a given mode),
 * 2) run the 4-frame hold then hand control back. */
extern void *D_800FAF5C, *D_800F9B00;
extern s32 D_800EB610[]; extern s16 D_800EB628[];
void selectTurnAnimationCDC04(void *,void *); void func_800D427C(void *,s16,s32); s16 func_800D5438(void *,s32); s32 func_800D35B0(s32,s32); void translateEntityXZ(void *,void *); s32 func_800D2BEC(void *,void *,void *,f32,u16,s32); void func_800D4AD0(void *); void beginEntityActionA8D8C(void *); void func_800C472C(void *,void *,s32);
#define F(p,t,o) (*(t *)((u8 *)(p)+(o)))
static inline s16 step(void *self,void *other) {
 s8 animId;
 F(self,s16,0x16)++; animId=F(self,s8,0);
 if(D_800EB628[animId]<F(self,s16,0x16)) {
 F(self,s32,0x58)=D_800EB610[animId];
 if(F(other,u32,0x2C)&0x100000) F(self,s16,0xC)=7;
 return 1;
 }
 if(F(other,u32,0x2C)&0x200) translateEntityXZ(self,(u8 *)self+0x33C);
 F(self,s32,0x58)=func_800D35B0(F(self,s32,0x58),F(self,s32,0x348));
 return 0;
}
void func_800D21E0(void) {
 switch(F(D_800FAF5C,s16,0xC)) {
 case 0:
 selectTurnAnimationCDC04(D_800FAF5C,D_800F9B00);
 ((Nw2F5CAction *)D_800FAF5C)->f16=0;
 func_800D427C(D_800FAF5C,func_800D5438(D_800F9B00,1),2);
 F(D_800FAF5C,s16,0xC)++;
 case 1:
 if(step(D_800FAF5C,D_800F9B00)) F(D_800FAF5C,s16,0xC)++;
 break;
 case 2:
 func_800D2BEC(D_800FAF5C,D_800F9B00,0,4.0f,0,0xFFFFE);
 if(F(D_800FAF5C,s16,4)<=0) { func_800D4AD0(D_800FAF5C); beginEntityActionA8D8C(D_800FAF5C); func_800C472C(D_800F9B00,D_800FAF5C,2); }
 break;
 }
}
