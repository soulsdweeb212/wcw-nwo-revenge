#include "common.h"

extern void *D_800EB40C;
s32 func_800D2BEC(void *,void *,void *,f32,u16,s32);
s16 func_800D5438(void *,s32);
void func_800D427C(void *,s16,s32);
void func_800B68A0(void *,void *,void *);
void func_800A837C(void *);
s8 func_800A83DC(void *,void *);
void func_800D4AD0(void *);
void func_800A3A74(void) {
 u8 *p; void *q;
 func_800D2BEC(D_800EB408,D_800EB40C,0,4.0f,0,0xFFFFE);
 if (!(*(u64*)((u8*)D_800EB40C+0x20)&0x800000ULL) && ((Nw2F408*)D_800EB408)->f6 == *(u8*)((u8*)D_800EB408+0x378) && (*(u64*)((u8*)D_800EB40C+0x20)&0x1000000ULL)) {
 *(u64*)((u8*)D_800EB408+0x20)|=0x800000ULL;
 func_800D427C(D_800EB408,func_800D5438(D_800EB40C,1),1);
 }
 if (((Nw2F408*)D_800EB408)->f4==1) func_800B68A0(D_800EB408,D_800EB408,D_800EB40C);
 if (((Nw2F408*)D_800EB408)->f4<=0) {
 func_800A837C(D_800EB408);
 if (!func_800A83DC(D_800EB408,D_800EB40C)) {
 p=D_800EB408;
 *(volatile s8*)(p+0x362)=-1;
 *(volatile u64*)(p+0x20)&=(q=D_800EB408,~0x40000000ULL);
 func_800D4AD0(q);
 func_800A6C48(D_800EB408,0x2B);
 }
 }
}
