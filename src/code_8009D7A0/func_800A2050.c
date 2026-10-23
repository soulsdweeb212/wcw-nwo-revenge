#include "common.h"

typedef struct {s32 f0;s16 f4,f6;s32 f8;s16 fC,fE;u8 pad10[8];s16 f18;u8 pad1A[6];u64 flags;u8 pad28[4];u32 f2C;u8 pad30[0x10];u16 f40;u8 f42,f43;} ObjA2050;
extern void *D_800EB40C;
extern u16 D_800F9D08[];
extern s16 D_800E3262[];
extern u8 D_800FADCF;
extern s8 D_800FAF78,D_800FADB8;
extern u16 D_800FAF8A;
extern u8 D_8007EF30[];
s16 func_800B6DEC(void *,s32,s32);
void func_800D7690(void *,s32,s32);
s8 func_800A93C0(void);
s8 func_800A9348(void *);
s8 func_800B71F8(void *,s32,s32);
void func_800D427C(void *,s16,s32);
s8 func_800D7894(void *,u16);
s8 func_800DA8D0(void *);
void beginEntityActionA8D8C(void *);
void func_800D4AD0(void *);
void func_800A9290(void *);
s32 func_800D2B64(void *,f32,u16,s32);
#define O ((ObjA2050 *)D_800EB408)
void func_800A2050(void) {
 s32 a3;s32 a1;
 switch(O->fC) {
 case 0:
 O->f43=0;O->f40=O->f40+1;D_800F9D08[(s8)D_800FADB8]=0;
 O->f18=func_800B6DEC(O,0,0);func_800D7690(O,0,0);
 if(!func_800A93C0()){if(!(O->flags&0x10ULL)){if(func_800A9348(O)){if(func_800B71F8(O,0,8))O->fE|=1;}}}
 O->fC++;
 case 1:
 O->flags|=0x1000000000ULL|0x400000ULL;
 if((u32)(O->f42-7)>=0x1A){if(O->flags&0x200000ULL)O->f42=0x1C;else O->f42=0x1B;}
 func_800D427C(O,D_800E3262[*(s8 *)&O->f42],1);
 if(O->flags&0x8000ULL)O->flags|=0x10000ULL;
 O->fC++;break;
 case 2:
 O->flags|=0x400000ULL;
 if(O->fE&1){O->fC=4;break;}
 if((u32)(O->f42-0x1B)<2){s8 c=(s8)O->f42;if(c==0x1B)a3=0xFC4;if(c==0x1C)a3=0xFC5;func_800D427C(O,a3,6);}
 if(*(u16 *)(D_8007EF30+0x170)&0x400){if((O->flags&0x100ULL)&&!(O->flags&0x8000ULL)){O->flags|=0x1000000000ULL|0x800ULL;break;}}
 O->fC++;break;
 case 3:
 O->flags|=0x400000ULL;func_800D2B64(O,4.0f,0,0xFFFFE);
 if(D_800FADCF&0x40){
 if(O->flags&0x4000ULL)func_800A6C48(O,0x43);
 if(O->flags&0x8000ULL)break;
 if(!func_800D7894(O,D_800FAF8A))break;
 if(D_800FAF78||func_800DA8D0(O)){O->f18=0;break;}
 func_800A6C48(O,0x43);
 }else{
 if(O->flags&0x10ULL)break;
 if(!func_800D7894(O,D_800FAF8A))break;
 if(D_800FAF78||func_800DA8D0(O)){O->f18=0;break;}
 func_800A6C48(O,(O->flags&0x8000ULL)&&(O->flags&0x40ULL)?0x85:0x43);
 }
 break;
 case 4:func_800A9290(O);O->fC++;break;
 case 5:a3=(O->flags&0x200000ULL)?0xF37:0xF36;func_800D427C(O,a3,6);O->fC++;break;
 case 6:
 func_800D2B64(O,2.0f,0,0xFFFFE);
 if(O->f4<=0){func_800D4AD0(O);beginEntityActionA8D8C(O);}break;
 case 7:
 a3=0x1000;
 if(!(O->flags&0x200000ULL))a3=(*(u32 *)((u8 *)D_800EB40C+0x3AC)&0x10)?0xFFE:0xFFF;
 func_800D427C(O,a3,6);O->fC++;
 case 8:
 func_800D2B64(O,2.0f,0,0xFFFFE);
 if(O->f4<=0){func_800D4AD0(O);func_800A6C48(O,0x2B);}break;
 }
}
