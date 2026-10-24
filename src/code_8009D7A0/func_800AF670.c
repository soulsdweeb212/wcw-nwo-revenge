#include "common.h"

typedef struct {u8 p0[2];s16 f2,f4;u16 f6,f8;s16 fA;s8 fC;u8 pD;s16 fE;u8 p10[22];s16 f26;u8 p28[6];u16 f2E;u8 p30[44];u32 f5C;} Act670;
typedef struct {u8 p0[10];u16 fA;u8 pC[20];u64 flags20;} Ctl670;
typedef struct {u8 p0[24];s8 f18;u8 p19[31];u64 flags38;} Att670;
typedef struct {u8 p0[10];s16 fA,fC;u8 pE[30];u32 f2C;u8 p30[820];Att670 *f364;} Ent670;
extern Act670 *D_800FABD0;extern Ctl670 *D_800F9B60;extern Ent670 *D_800FAF58;
extern u16 D_800E3764[],D_800E3770[],D_800E3CD0[],D_800E3CE0[];extern s16 D_800E3758[];
s8 func_800D4198(s16);s32 func_800D4148(void);
static __inline__ s16 lookup670(s16 *p){s16 r=func_800D4148();while(*p!=-1){if(*p>=r)return p[1];p+=2;}return 0;}
void func_800AF670(void){Act670 *a=D_800FABD0;s32 value;Act670 *p;
switch(a->f4){
case 0:{s16 s1=15,s0;if(D_800F9B60->flags20&0x80000)s0=7;else {s8 q=D_800FAF58->f364->f18/3;s1=D_800E3764[q];s0=D_800E3770[q];if(func_800D4198(100)){s1=15;s0=5;}}{s16 t=func_800D4148();D_800FABD0->f4++;D_800FABD0->fE=s1+t%(s0*2)-s0;}break;}
case 1:
if(D_800FAF58->fA!=0x45)goto reset;
if(--a->fE>=0)break;
if(func_800D4198(100)&&!(D_800FAF58->f2C&0x3C0)){D_800FABD0->f8=0x20;D_800FABD0->f6=0x20;D_800FABD0->f4=3;break;}
if((D_800FAF58->f2C&3)==3){
if(D_800FAF58->f2C&0x80){if(D_800FAF58->f364->flags38&0x400000000000ULL)D_800FABD0->fC=0x50;else if(func_800D4198(500))D_800FABD0->f8=0x8000;else {p=D_800FABD0;value=0x4000;goto store8;}}
else {if(D_800FAF58->f364->flags38&1)D_800FABD0->f8=0x4000;else if(D_800FABD0->f26<10&&func_800D4198(500))D_800FABD0->f8=0xC000;else D_800FABD0->fC=0x50;}
goto advance;}
if(D_800FAF58->f2C&0x80){s16 v=(D_800FAF58->f2C&2)?50:100;if(func_800D4198(v)){D_800FABD0->f8=4;D_800FABD0->f6=4;D_800FABD0->f4++;break;}}
if(!(D_800FAF58->f2C&0xC0)&&func_800D4198(350)){s16 t=func_800D4148();s16 rem=t%4;if(func_800D4198(500))value=D_800E3CE0[rem];else value=D_800E3CD0[rem];p=D_800FABD0;value|=4;
store8:p->f8=value;
advance:D_800FABD0->f6=D_800FABD0->f8;D_800FABD0->f4++;break;}
if((D_800FAF58->f2C&2)&&(D_800FAF58->f364->flags38&1)){D_800FABD0->f8=0x4000;D_800FABD0->f6=0x4000;}
else {if(func_800D4198(500))D_800FABD0->f8=0x8000;else D_800FABD0->f8=0x4000;{u16 v=lookup670(D_800E3758);D_800FABD0->f6=D_800FABD0->f8|v;}}
D_800FABD0->f4++;break;
case 2:
if(D_800FAF58->fA==0x45)break;if(D_800FAF58->fA!=0x4B)goto reset;
if(func_800D4198(100)){if(D_800FAF58->f2C&1){if(D_800FABD0->f26<10&&func_800D4198(500))D_800FABD0->f8=0xC000;else D_800FABD0->fC=0x50;}else D_800FABD0->f8=0x8000;{u16 v=lookup670(D_800E3758);D_800FABD0->f6=D_800FABD0->f8|v;}break;}
D_800FABD0->f8=0x4000;{s16 t=func_800D4148();switch((s16)(t%5)){case 0:D_800FABD0->f6=0x4000;break;case 1:D_800FABD0->f6=0x800;break;case 2:D_800FABD0->f6=0x100;break;case 3:D_800FABD0->f6=0x400;break;case 4:D_800FABD0->f6=0x200;break;}}break;
case 3:if(D_800FAF58->fA==0x45){if(D_800FAF58->fC==2)a->f4=0;}else goto reset;break;
}return;
reset:a->f2=0;a->f4=0;a->f2E=D_800F9B60->fA;a->f5C&=~7;
}
