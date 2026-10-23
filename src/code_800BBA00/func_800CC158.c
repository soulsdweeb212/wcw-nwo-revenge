#include "common.h"

typedef struct {s8 f0;u8 pad1;s16 f2,f4,f6,f8,fA,fC,fE;u8 pad10[4];s16 f14,f16,f18;u8 pad1A[6];u64 flags;u8 pad28[0x320];s8 f348;u8 pad349[3];s8 f34C[4];u8 pad350[0x10];u16 f360;u8 pad362[2];void *f364;u8 pad368[0x2E];s8 f396;u8 pad397[0x15];u32 f3AC;} Nw2Entity;
extern Nw2Entity *D_800FAF5C,*D_800F9B00;extern u16 D_800EB5B8[];extern u8 D_8007EF30[];extern s8 D_800FADB8,D_800FAF78;extern u16 D_800FABE6,D_800FAF8A;
s16 func_800D5438(void*,s32);void func_800D427C(void*,s16,s32);s16 func_800B6DEC(void*,void*,s32);void func_800D7690(void*,s32,s32);s16 func_8000B710(s8);s8 func_800B71F8(void*,s32,s32);void func_800B68A0(void*,void*,void*);void func_800A7F6C(void*,s32);void func_800A837C(void*);void func_800D2BEC(void*,void*,void*,f32,u16,s32);void beginEntityActionA8D8C(void*);void func_800C472C(void*,void*,s32);void func_800D4AD0(void*);void func_800D7894(void*,u16,u64);void *func_800087DC(s16);void func_8000B728(s8,void*);void func_8000C784(s8);void func_800CCC64(void*,void*,u32);void func_8009786C(s32);void func_8009791C(void);void func_80097BB4(void);
#define O D_800FAF5C
#define T D_800F9B00
#define CONFIG (*(u16*)&D_8007EF30[0x170])
void func_800CC158(void){switch(O->fC){case 0:
O->flags|=0x400000000000ULL;func_800D427C(O,func_800D5438(T,1),1);D_800EB5B8[D_800FADB8]=0;O->f18=func_800B6DEC(O,T,3);func_800D7690(O,0,0);
if(T->f3AC&0x80){if((CONFIG&0x100)||(O->flags&0x40)){if(O->flags&T->flags&0x200)func_8009786C(4);}}O->fC++;break;
case 1:O->flags|=0x400000000000ULL;func_800D7894(O,D_800FAF8A,0x400000000000ULL);
if(D_800FAF78){if(O->f18<=0){if((CONFIG&0x100)||(O->flags&0x40))O->flags|=0x800000000000ULL;}O->f18=1;}
if(O->f18<0){if(!(T->f360&0x21F))T->f360|=2;}
if(O->f18<5){if(!(T->f360&0x100)){if(!(T->f360&0x21F)){
if((CONFIG&0x10)&&(T->f3AC&0x80)){if(O->flags&T->flags&0x200){if((CONFIG&0x100)||(O->flags&0x40)){if(O->f14<0x5B){if(O->f34C[T->f396]<=0){if(O->flags&0x800000000000ULL)T->f360|=8;}}}}}
if(T->f3AC&0x4000){if(func_8000B710(O->f0)){if(!(O->flags&0x4000000000000ULL)){if(!(O->f360&0x400)){if(O->f34C[T->f396]<=0){O->f360|=0x400;if(func_800B71F8(O,0,0xD)){O->flags|=0x4000000000000ULL;T->f360|=0x200;}}}}}}
}}}
{u16 *p=&D_800EB5B8[D_800FADB8];*p=*p+1;if((s16)*p>=0x1F){func_800B68A0(T,T,O);D_800EB5B8[D_800FADB8]=0;
if(!(T->f360&0x100)){if(!(T->f360&0x21F)){if(!(O->f360&0x80)){O->f360|=0x80;if((CONFIG&8)&&(T->f3AC&0x80)){if((CONFIG&0x100)||(O->flags&0x40)){if(O->flags&T->flags&0x200){if(O->f14<0x5B){if(func_800B71F8(O,0,7))T->f360|=8;}}}}}}}}}
if(O->flags&0x40){if(D_800FAF8A&0xC030){if(!(T->f3AC&0x200000)){func_800CCC64(O,T,D_800FABE6);}}}
if(!(T->f3AC&0x400000)){if(func_800D2BAC(O,T,4.0f,0xFFFFC)){if(!(T->f360&0x21F)){if(CONFIG&2){if(!(O->flags&0x100)){if(T->f3AC&0x100){T->f360|=4;func_800A7F6C(O,0x56);func_800A837C(O);T->f360|=4;if(O->flags&T->flags&0x200)func_8009791C();}}}}}}
if(T->f360&0x20){if(T->f3AC&0x80){if(!(T->f360&0xC)){if(O->flags&T->flags&0x200)func_80097BB4();}}
if(T->f360&2){if((CONFIG&0x100)||(O->flags&0x40))O->flags|=0x800000000000ULL;}
{s16 a1;if(T->f360&0x10)a1=7;else if(T->f360&0x208)a1=5;else a1=3;func_800D427C(O,func_800D5438(T,a1),0);}O->fC++;}break;
case 2:func_800D2BEC(O,T,0,2.0f,0,0xFFFFE);
if(T->f360&8){u8 *ptr=func_800087DC(T->f8);s16 i;for(i=0;i<8;i++){u8 a=ptr[0];if(a){if(a==O->f6){if(ptr[1]==2)O->flags|=0x1000;}}ptr+=2;}}
if(T->f360&0x200){if(O->f6==0x28){O->f14=0x64;func_8000B728(D_800FADB8,O);if(O->flags&0x400000000ULL)func_8000C784(D_800FADB8);}}
if(O->f4<=0){func_800D4AD0(O);if((O->flags&0x100)||(T->f3AC&4)||(O->flags&0x8000))beginEntityActionA8D8C(O);else{O->flags|=0x80000000000000ULL;func_800A6C48(O,0x2B);}if(!(O->flags&0x8000)||(O->flags&0x10000))func_800C472C(T,O,2);}break;}}
