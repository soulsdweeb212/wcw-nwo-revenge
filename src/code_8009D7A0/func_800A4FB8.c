#include "common.h"

typedef struct{u8 pad0[4];s16 f4;u8 pad1[6];s16 fC;u8 pad2[8];u16 f16;u8 pad3[8];u64 flags;u8 pad4[0x16];s16 f3E;u8 pad5[0x2FC];f32 f33C;u8 pad6[4];f32 f344;}Nw2Action800A4FB8;
#define P ((Nw2Action800A4FB8*)D_800EB408)
extern f32 D_800E3248[]; extern f32 D_800E324C[]; extern s32 D_800E3238[]; extern s32 D_800F9B0C; extern s32 D_800F9B24[]; extern s8 D_800FADB8;
s32 func_800D4D44(void*,s32,s32); void func_800D427C(void*,s32,s32); void func_800A7240(void*,s32,s32,u64); void func_800A6BE0(void*,s32); void translateEntityXZ(void*,void*); s32 func_800D2B64(void*,f32,u16,s32);
void func_800A4FB8(void){
 P->flags|=0x1000000000ULL;
 switch(P->fC){
 case 0: if (P->flags&0x200000ULL) func_800D427C(P,0xFC5,1); else func_800D427C(P,0xFC4,1); P->f16=0x3C; P->fC++;
 case 1: { Nw2Action800A4FB8 *q = P; q->f16--; if((s16)q->f16<0){ if (q->flags&0x200000ULL) func_800D427C(q,0xF33,1); else func_800D427C(q,0xF2D,1); P->flags&=0xFFFFFFFFFFDFFFFFULL; P->fC++; } } break;
 case 2: if(P->f4>0) break; func_800D427C(P,(s16)func_800D4D44(P,0,D_800F9B0C),1); P->f3E=getXZDirectionQuadrant((f32*)((u8*)P+0x4C)); P->f33C=D_800E3248[P->f3E*2]; P->f344=D_800E324C[P->f3E*2]; D_800F9B24[D_800FADB8*4]=D_800E3238[P->f3E]; P->flags|=0x10000000ULL; P->fC++; break;
 case 3: { s32 a = D_800F9B24[D_800FADB8*4]; func_800A7240(P,a,0x155,0); } translateEntityXZ(P,(u8*)P+0x33C); if((u16)func_800D2B64(P,1.0f,0,2)) func_800A6BE0(P,0x60); break;
 }
}
