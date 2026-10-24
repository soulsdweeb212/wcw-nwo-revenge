#include "common.h"

typedef struct{s32 f0;s16 f4,f6,f8,fA,fC,fE;u8 pad10[0x10];u64 flags;u8 pad28[0x14];s16 f3C;u8 pad3E[0xE];f32 f4C,f50,f54;s32 f58;u8 pad5C[0x10];f32 f6C,f70,f74;u8 pad78[0x2DB];s8 f353;}Nw2D6658;
extern s32 D_800E3CFC[];extern u16 D_800E3F84[],D_800E3F8C[];extern f64 D_800E6D60,D_800E6D68,D_800E6D70;
typedef struct{f32 x,y,z;s32 angle;}Nw2DirRes;
s8 func_800D25D0(void*,f32);void func_800D2B64(void*,f32,s32,s32);void func_800D3890(void*,void*,void*);void func_800D427C(void*,s32,s32);s16 func_800D4D44(void*,s32,f32);f32 func_800D63F0(void*,void*,s32);s16 func_800D7A68(u16);void func_800DECAC(void*,s32,s32,s32);
static inline void moveAll(void*e,f32*ofs){s16 i;*(f32*)((u8*)e+0x4C)+=ofs[0];*(f32*)((u8*)e+0x54)+=ofs[2];for(i=1;i<0x14;i++){u8*p=(u8*)e+i*16;*(f32*)(p+0x5C)+=ofs[0];*(f32*)(p+0x64)+=ofs[2];*(f32*)(p+0x1CC)+=ofs[0];*(f32*)(p+0x1D4)+=ofs[2];}}
static inline s16 chooseDirection(s16 q,u16 mask){if(mask&D_800E3F84[q])return 1;if(mask&D_800E3F8C[q])return 2;return 0;}
#define E ((Nw2D6658*)arg0)
#define B ((Nw2D6658*)arg1)
void func_800D6658(void*arg0,void*arg1,u16 arg2,s32 arg3,f32 arg4){f32 off[3];f32 res[3];Nw2DirRes dir;volatile f64 pad[3];f32 t;s16 r;u16 m=arg2;s32 f=arg3;
if(arg2&0xF00){off[0]=0.0f;off[2]=0.0f;t=func_800D63F0(arg0,res,0);if(E->flags&0x80){if(arg2&0x800)off[2]=t;if(arg2&0x100)off[0]=t;if(arg2&0x400)off[2]=-t;if(arg2&0x200)off[0]=-t;moveAll(arg0,off);r=chooseDirection(E->f3C,m);{s32 tt=r;s32 a=0x1081;if(tt!=0)a=0x108D+(((tt<<16)>>16)-tt);func_800D427C(arg0,a,0);}func_800D25D0(arg0,4.0f);
}else{if(m&0x800){if(B->f74>E->f74)off[2]=res[0];else off[2]=res[2];}if(m&0x100){if(B->f6C>E->f6C)off[0]=res[0];else off[0]=res[2];}if(m&0x400){if(B->f74<E->f74)off[2]=-res[0];else off[2]=-res[2];}if(m&0x200){if(B->f6C<E->f6C)off[0]=-res[0];else off[0]=-res[2];}
r=func_800D7A68(m);if(!(r&1)){off[0]*=D_800E6D60;off[2]*=D_800E6D60;}if((s16)f==1){off[0]*=D_800E6D68;off[2]*=D_800E6D68;}
if(E->flags&0x800000000ULL){if(func_800D3550(func_800D3684(E->f58,D_800E3CFC[r]))<0x101&&B->fA==0x2D){off[0]*=D_800E6D70;off[2]*=D_800E6D70;moveAll(arg0,off);moveAll(arg1,off);}else{*(u64*)((u8*)arg0+0x20)&=~0x800000000ULL;moveAll(arg0,off);func_800D427C(arg0,func_800D4D44(arg0,0,arg4),1);}}
else{moveAll(arg0,off);if((s16)f==0){s8 cur;cur=func_800D25D0(arg0,4.0f);if(E->f353==cur&&B->fA==0x2D&&!(E->flags&0x1000000000000ULL)){func_800D3890((u8*)arg0+0x6C,(u8*)arg1+0x6C,&dir);if(func_800D3550(func_800D3684(E->f58,dir.angle))<0x17&&func_800D3550(func_800D3684(E->f58,D_800E3CFC[r]))<0x101)E->flags|=0x800000000ULL;}if(E->flags&0x800000000ULL)func_800D427C(arg0,0xE5F,3);else func_800D427C(arg0,func_800D4D44(arg0,0,arg4),3);}}}}
else{E->flags&=~0x800000000ULL;func_800DECAC(arg0,0,0,0);func_800D25D0(arg0,4.0f);if((s16)arg3==0){if(E->flags&0x80)func_800D427C(arg0,0x1081,0);else func_800D427C(arg0,func_800D4D44(arg0,1,arg4),3);}}func_800D2B64(arg0,1.0f,0,2);}
