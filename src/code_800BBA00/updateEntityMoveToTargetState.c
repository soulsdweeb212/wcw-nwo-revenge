#include "common.h"

/* Entity run-to-target / attack state machine (states 0..3).
 * It picks a target-relative offset (vec) from the target's facing quadrant
 * (func_800C9AC0), converts it into a world point with func_800D3E40, follows
 * it as a quadratic spline (stepEntityXZQuadraticSpline, with a heading
 * correction via func_800A7240), then plays the strike animation chosen from
 * the quadrant and releases the run. */
typedef struct {s32 f0;s16 f4,f6,f8,fA,fC;u8 pE[0x12];u64 flags;u8 p28[0x16];s16 f3E;u8 p40[0x18];s32 heading;u8 p5C[0x304];u16 f360;s8 f362;} E8188;
extern E8188 *D_800FAF5C,*D_800F9B00;extern s32 D_800F9B14;extern s8 D_800FADB8;extern s32 D_800EB530[];extern u8 D_800FACF8[];
s32 func_800C9AC0(void*,s32);s32 func_800D35B0(s32,s32);void func_800D3E40(void*,f32*,s32,void*);void func_800D7128(void*,void*,void*,void*);s8 stepEntityXZQuadraticSpline(void*,void*);s32 func_800A7240(void*,s32,s32,u64);void func_800D427C(void*,s16,s32);void func_800D4AD0(void*);
void updateEntityMoveToTargetState(void) {
 f32 vec[4]; f32 out[4]; s32 angle; s16 quad; s16 animId; s16 done;E8188 *ent;
 switch(D_800FAF5C->fC) {
 case 0:func_800D427C(D_800FAF5C,0xFB9,3);D_800FAF5C->fC++;break;
 case 1:
 quad=func_800C9AC0(D_800F9B00,D_800F9B14);D_800FAF5C->f3E=quad;
 switch(quad) {
 case 0:vec[0]=0.0f;vec[2]=-130.0f;angle=0;break;
 case 1:vec[0]=-100.0f;vec[2]=-25.0f;angle=0x400;break;
 case 2:vec[0]=0.0f;vec[2]=150.0f;angle=0x800;break;
 case 3:vec[0]=100.0f;vec[2]=-25.0f;angle=-0x400;break;
 }
 D_800EB530[D_800FADB8]=func_800D35B0(angle,D_800F9B00->heading);
 if(D_800F9B00->flags&0x200000ULL) {vec[0]=-vec[0];vec[2]=-vec[2];D_800EB530[D_800FADB8]=func_800D35B0(D_800EB530[D_800FADB8],0x800);}
 func_800D3E40((u8*)D_800F9B00+0x4C,vec,D_800F9B00->heading,out);
 func_800D7128(D_800F9B00,D_800FAF5C,out,D_800FACF8+D_800FADB8*0x30);
 D_800FAF5C->fC++;
 case 2:
 func_800D2C68(D_800FAF5C,D_800F9B00,2.0f,D_800FACF8+D_800FADB8*0x30,2);
 done=stepEntityXZQuadraticSpline(D_800FAF5C,D_800FACF8+D_800FADB8*0x30);
 done+=(s8)func_800A7240(D_800FAF5C,D_800EB530[D_800FADB8],0x71,0ULL);
 if(done==2 && D_800FAF5C->f4<=0) {
 animId=D_800FAF5C->f3E*2+0xF6B;if(D_800F9B00->flags&0x200000ULL) animId=D_800FAF5C->f3E*2+0xF63;
 func_800D427C(D_800FAF5C,animId,2);D_800FAF5C->f360|=1;D_800FAF5C->fC++;
 }break;
 case 3:func_800D2BAC(D_800FAF5C,D_800F9B00,2.0f,2);ent=D_800FAF5C;if(ent->f4==1) {ent->f362=-1;ent->flags&=~0x40000000ULL;func_800D4AD0(D_800FAF5C);func_800A6C48(D_800FAF5C,0x2B);}break;
 }
}
