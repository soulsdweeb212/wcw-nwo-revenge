#include "common.h"

typedef struct {s16 f0,f2,f4;u16 f6,f8,fA;u8 pC[0x22];u16 f2E;u8 p30[12];f32 f3C;u8 p40[24];f32 f58;u32 f5C;} ActB3F;
typedef struct {u8 p0[10];s16 fA;u8 pC[0x60];f32 position[3];} EntB3F;
extern ActB3F *D_800FABD0;extern EntB3F *D_800FAF58,*D_800F9B60;extern u16 D_800E3CF0[];extern s32 D_800E3D00[];extern f64 D_800E5470,D_800E5478;
s32 func_800D3650(void*,void*);f32 func_800D3890(void*,void*,void*);s8 func_800D4198(s16);

/* Chooses/holds an idle facing for the D_800FABD0 actor (variant of
 * func_800B0C90) driven by D_800FAF58's state.  Phase 0 sets the 8-way facing
 * (D_800E3CF0) from the bearing between D_800FAF58 and D_800F9B60, biasing by
 * +/-2 when the angle error is under 0x300.  Phase 1 advances when
 * D_800FAF58->fA==1 and the f58/f3C height relation holds, and resets to substate
 * 0 when D_800F9B60->fA isn't 0x2C.  Phases 2/3/4 step through the
 * crouch/anticipation frames (f6/f8) and either hold or reset. */
void func_800B3F24(void) {
 f32 origin[3];s32 facing; s16 facingBias;
 switch(D_800FABD0->f4) {
 case 0:
 origin[0]=0;origin[2]=0;
 facing=func_800D3650(D_800F9B60->position,D_800FAF58->position);
 if(D_800E5470<(f64)func_800D3890(origin,D_800FAF58->position,0)) {
 if(func_800D3550(func_800D3684(D_800E3D00[(s16)func_800D3650(origin,D_800FAF58->position)],D_800E3D00[(s16)facing]))<0x300) {facingBias=func_800D4198(500)?2:-2;facing=(facing+facingBias)&7;}
 }
 D_800FABD0->fA=D_800E3CF0[(s16)facing];D_800FABD0->f4++;break;
 case 1:
 if(D_800FAF58->fA==1) {
 if((f64)D_800FABD0->f58+D_800E5478<(f64)D_800FABD0->f3C)D_800FABD0->f4++;else D_800FABD0->f6=D_800FABD0->fA;
 } else {D_800FABD0->f2=0;D_800FABD0->f4=0;D_800FABD0->f2E=D_800F9B60->fA;D_800FABD0->f5C&=~7;}
 if(D_800F9B60->fA!=0x2C) {D_800FABD0->f2=0;D_800FABD0->f4=0;D_800FABD0->f2E=D_800F9B60->fA;D_800FABD0->f5C&=~7;}
 break;
 case 2:D_800FABD0->f6=4;D_800FABD0->f4++;break;
 case 3:
 switch(D_800FAF58->fA) {
 case 3:if(D_800FABD0->f3C<D_800FABD0->f58) {D_800FABD0->f8=0x4000;D_800FABD0->f6=0x4000;}break;
 case 4:case 0x56:D_800FABD0->f4++;break;
 default:goto reset;
 }break;
 case 4:
 switch(D_800FAF58->fA) {
 case 3:D_800FABD0->f8=0xF00;break;
 case 4:case 0x56:break;
 default:reset:D_800FABD0->f2=0;D_800FABD0->f4=0;D_800FABD0->f2E=D_800F9B60->fA;D_800FABD0->f5C&=~7;break;
 }break;
 }
}
