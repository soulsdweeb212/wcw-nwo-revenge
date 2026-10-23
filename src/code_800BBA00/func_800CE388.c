#include "common.h"

void func_800A72FC(void *,void *,s32); void func_800A7328(void *); void func_800A7C40(void *,s8,s16);s32 func_800D35B0(s32,s32);void func_800D3E40(void *,void *,s32,void *);void func_800D427C(void *,s32,s32);s32 func_800D5438(void *,s32);extern s32 D_800E3CA0[];

/* Sets up a grapple/clinch positioning move between self and partner.  It picks
 * the anchor position (posVec, from the partner's XZ or a fixed +/-345/190 offset
 * chosen by the partner's quadrant) and the facing (the s32 *headingOut, from the
 * quadrant table D_800E3CA0, wrapped by func_800D35B0 when the 0x40 sub-flag is
 * set), plus the animation id (overridden through func_800A7C40 /
 * func_800D5438 when the 0x2000000 sub-flag is clear).  Which side drives depends
 * on which of self/partner carries flag 0x10000.  Finally it starts the move
 * (func_800A72FC + func_800D427C) and stores the per-frame heading increment
 * (+0x348 = heading error / 6) and clears the s16 +0x16. */
void func_800CE388(u8 *self,u8 *partner,s32 *headingOut) {
#define S(p,o) (*(s16 *)((p)+(o)))
#define W(p,o) (*(s32 *)((p)+(o)))
#define F(p,o) (*(f32 *)((p)+(o)))
 f32 offsetVec[4]; f32 posVec[4]; s32 animId; s32 headingStep;
 if((S(self,10)==0x79)|(S(self,10)==0x87)) {
 if(W(self,0x2C)&0x10000) {
 offsetVec[0]=0;offsetVec[2]=-77.0f;
 *headingOut=D_800E3CA0[S(partner,0x3C)];func_800D3E40(partner+0x6C,offsetVec,*headingOut,posVec);
 animId=0x10B5;
 if(!(W(self,0x2C)&0x2000000)) {func_800A7C40(self,*(s8 *)self,0x85);animId=func_800D5438(self,0);}
 } else {
 posVec[0]=F(partner,0x6C);posVec[2]=F(partner,0x74);
 switch(S(self,0x3C)) {case 0:posVec[2]=345.0f;break;case 1:posVec[0]=345.0f;break;case 2:posVec[2]=-345.0f;break;case 3:posVec[0]=-345.0f;break;}
 *headingOut=D_800E3CA0[S(self,0x3C)];animId=0x10AD;if(W(self,0x2C)&0x40) animId=0x10B3;
 }
 goto position;
 } else if(W(partner,0x2C)&0x10000) {
 W(self,0x33C)=0;W(self,0x344)=0;*headingOut=D_800E3CA0[S(self,0x3C)];animId=0x10B6;
 if(!(W(partner,0x2C)&0x2000000)) animId=func_800D5438(partner,1);
 func_800A7328(self);func_800D427C(self,(s16)animId,2);
 } else {
 posVec[0]=F(self,0x6C);posVec[2]=F(self,0x74);
 switch(S(partner,0x3C)) {case 0:posVec[2]=190.0f;break;case 1:posVec[0]=190.0f;break;case 2:posVec[2]=-190.0f;break;case 3:posVec[0]=-190.0f;break;}
 animId=0x10B4;
 if(W(partner,0x2C)&0x40) *headingOut=D_800E3CA0[S(partner,0x3C)];
 else {*headingOut=func_800D35B0(D_800E3CA0[S(partner,0x3C)],0x800);animId=0x10AE;}
 position:func_800A72FC(self,posVec,6);func_800D427C(self,(s16)animId,3);
 }
 headingStep=func_800D3684(*headingOut,W(self,0x58))/6;S(self,0x16)=0;W(self,0x348)=headingStep;
#undef S
#undef W
#undef F
}
