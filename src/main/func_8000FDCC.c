#include "common.h"

extern s16 D_8005A380[][3][2],D_8005A382[][3][2];extern s8 D_80036D10[];extern f64 D_8003B258;extern u8 D_80070C94[],D_80070C98[],D_80070C9C[];void setupSideSlotRamp(s16,s16,s16,s16,f32,f32,f32);
#define X(n) (*(f32*)(D_80070C94+(n)))
#define Y(n) (*(f32*)(D_80070C98+(n)))
#define Z(n) (*(f32*)(D_80070C9C+(n)))
void func_8000FDCC(void){f32 two=2.0f;f64 half=D_8003B258;u32 side,slot; s16 entity,part; f32 x,z,y;
for(side=0;side<4;side++){for(slot=0;slot<3;slot++){entity=D_8005A380[side][slot][0];part=D_8005A382[side][slot][0];if((entity>=0)&(part!=0)){if((part&3)==3){s32 a,b,e,d;do{a=D_80036D10[(s16)(part&~1)]*124;}while(0);e=entity*0x2C9;do{e*=4;}while(0);do{d=D_80036D10[(s16)(part&~2)];}while(0);a+=e;x=X(a);do{b=d*124+e;}while(0);x+=X(b);z=Z(a);z+=Z(b);y=Y(a)-two;y+=Y(b)-two;x*=half;z*=half;y*=half;}else{s32 a,d;d=D_80036D10[part]*31;a=(entity*0x2C9+d)*4;x=X(a);z=Z(a);y=Y(a)-two;}
switch(side){case 1:{f32 t=x;x=z;z=t;}break;case 2:z=-z;break;case 3:{f32 t=x;x=z;z=-t;}break;}setupSideSlotRamp(side,slot,0,6,x,z,y);}}}}
