#include "common.h"

typedef struct {u8 p0[4];s16 f4,f6,f8,fA,fC;u8 pE[0x12];u64 flags;u16 f28;u8 p2A[0x33A];void *attachment;u8 p368[6];u8 f36E,f36F,f370,f371;u8 p372[0x30];s8 f3A2;} EDD6;
extern EDD6 *D_800FAF5C,*D_800F9B00;extern s8 D_800FADB8,D_800FAF78;extern s32 D_800E3F20[],D_800FABD8;
void func_800A7C40(void*,s8,s16);s16 func_800D5438(void*,s32);void func_800D427C(void*,s16,s32);void func_800A7F6C(void*,s32);s8 func_800DB4FC(void*,void*);void func_800C38FC(void*,u64,s32);s32 func_800D2B64(void*,f32,u16,s32);void func_800D4AD0(void*);void func_800A7D1C(void*,s32);void func_800B68A0(void*,void*,void*);s8 func_800D4CC4(void*);void addEntityHealthDelta(void*,s32);void beginEntityActionA8D8C(void*);void func_800A837C(void*);
void func_800DD6B4(void) {
 s16 anim; EDD6 *e;
 switch(D_800FAF5C->fC) {
 case 0:
 if(D_800FAF5C->f28&1) {
 if(D_800FAF78 && (*(u64*)((u8*)D_800FAF5C->attachment+0x38)&0x80000000ULL) && !(D_800FAF5C->f28&8)) {
 func_800A7C40(D_800FAF5C,D_800FADB8,0xDC);func_800D427C(D_800FAF5C,func_800D5438(D_800FAF5C,0),1);D_800FAF5C->fC=4;break;
 }
 anim=0xDB;
 }else anim=0xDA;
 func_800A7C40(D_800FAF5C,D_800FADB8,anim);func_800D427C(D_800FAF5C,func_800D5438(D_800FAF5C,0),1);func_800A7F6C(D_800FAF5C,0);D_800FAF5C->fC++;break;
 case 1:
 if(D_800FAF5C->f4<=0) {func_800D427C(D_800FAF5C,func_800D5438(D_800FAF5C,1),1);D_800FAF5C->fC++;}break;
 case 2:
 D_800FABD8&=~D_800E3F20[D_800FADB8];
 if(D_800FAF5C->f6>=D_800FAF5C->f370) D_800FAF5C->flags=(D_800FAF5C->flags&~0x40ULL)|0x100ULL;
 if(func_800DB4FC(D_800FAF5C,D_800F9B00)) D_800FAF5C->fC++;
 if(D_800FAF5C->f36E!=2) D_800FAF5C->flags=(D_800FAF5C->flags&~0x100ULL)|0x40ULL;
 case 3:
 D_800FAF5C->flags|=0x80000000000ULL;func_800C38FC(D_800FAF5C,0x1000000000ULL,0x800000);
 if(D_800FAF5C->f6>=D_800FAF5C->f371) {D_800FAF5C->flags&=~0x80000000000ULL;if(D_800FAF5C->f36E==2)func_800D2B64(D_800FAF5C,4.0f,0,0xFFFFE);}
 if(D_800FAF5C->f4<=0) {
 func_800D4AD0(D_800FAF5C);e=D_800FAF5C;
 if(e->fC==2) {func_800A7D1C(e,0x23);func_800B68A0(D_800FAF5C,D_800FAF5C,D_800FAF5C);if(func_800D4CC4(e))addEntityHealthDelta(e,e->f3A2);beginEntityActionA8D8C(e);}else func_800A6C48(e,0x2B);
 }break;
 case 4:
 if(D_800FAF5C->f4<=0) {func_800B68A0(D_800FAF5C,D_800FAF5C,D_800F9B00);func_800D4AD0(D_800FAF5C);func_800A6C48(D_800FAF5C,0x2B);func_800A7F6C(D_800FAF5C,0);func_800A837C(D_800FAF5C);}break;
 }
}
