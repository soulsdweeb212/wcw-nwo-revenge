/* @header
 * initAudioStream  (originally func_8001CF94)
 * VRAM 0x8001CF94 | ROM 0x1DB94 | size 0x498
 * asm: asm/nonmatchings/main/initAudioStream.s
 */
#include "common.h"

/* Initialize an audio-stream voice (obj) from a stream descriptor (arg1).
 * Selects the region coefficient table by arg1->f1C, allocates the region
 * array and the envelope array, and fills each region's envelope data
 * (attack/decay coefficients, auxiliary envelope) from the table. */
typedef struct { u8 pad[0x14]; void *f14; s32 pad18[2]; s32 f20,f24; } AuxCF;
typedef struct { s16 f0,f2; u8 pad4[4]; s16 coeff[16]; void *f28; s32 f2C; } AuxBCF;
typedef struct { u32 f0,f4; u16 f8,fA,fC,padE; f32 f10,f14,f18,f1C; AuxBCF *f20; AuxCF *f24; } EntryCF;
typedef struct { s32 f0; void (*f4)(); u8 pad8[0xC]; u16 *f14,*f18; u32 f1C; EntryCF *f20; u8 f24; u8 pad25[3]; void (*f28)(); } ObjCF;
typedef struct { u8 pad0[0x18]; s32 f18; u8 f1C; u8 pad1D[3]; s32 *f20; } DescCF;
extern s32 D_80037260[],D_800372C8[],D_80037350[],D_80037378[],D_800373A0[],D_800373C8[];
s32 func_800202B0(s32,s32,s32,s32,s32);
void func_8001F070(void*,s32,void (*)(),s32);
void func_8001F860(); void func_8001F4B0(); void setAudioStreamRegionParameter();
void initAudioStream(ObjCF *obj, DescCF *arg1, s32 arg2) {
 s32 *table; u16 index; u16 i; u16 j; EntryCF *entry;
 func_8001F070(obj,0,func_8001F860,5);
 obj->f4=func_8001F4B0; obj->f28=setAudioStreamRegionParameter;
 switch(arg1->f1C) {case 1: table=D_80037260;break; case 2:table=D_800372C8;break;case 5:table=D_80037350;break;case 3:table=D_80037378;break;case 4:table=D_800373A0;break;case 6:table=arg1->f20;break;default:table=D_800373C8;break;}
 obj->f24=table[0]; obj->f1C=table[1];
 obj->f20=(EntryCF*)func_800202B0(0,0,arg2,obj->f24,0x28);
 obj->f14=(u16*)func_800202B0(0,0,arg2,obj->f1C,2); obj->f18=obj->f14;
 index=2;
 for(j=0;j<obj->f1C;j++) obj->f14[j]=0;
 for(i=0;i<obj->f24;i++) {
 entry=&obj->f20[i];
 entry->f0=table[index++]; entry->f4=table[index++]; entry->fA=table[index++]; entry->f8=table[index++]; entry->fC=table[index++];
 if(table[index]) {
 entry->f10=((f32)table[index++]/1000.0f)*2.0/arg1->f18;
 entry->f1C=((f32)table[index++]/173123.404906676)* (entry->f4-entry->f0);
 entry->f14=1.0f; entry->f18=0.0f;
 entry->f24=(AuxCF*)func_800202B0(0,0,arg2,1,0x34);
 entry->f24->f14=(void*)func_800202B0(0,0,arg2,1,0x20);
 entry->f24->f20=0;entry->f24->f24=1;
 } else { entry->f24=0;index+=2; }
 if(table[index]) {
 s32 v,k,t; s16 h; f64 r,step; AuxBCF *p;
 entry->f20=(AuxBCF*)func_800202B0(0,0,arg2,1,0x30);
 entry->f20->f28=(void*)func_800202B0(0,0,arg2,1,8);
 entry->f20->f0=table[index++]; p=entry->f20;
 t=p->f0; h=t; v=h>>1; h=v;
 p->f2C=1; p->f2=0x4000-v;
 for(k=7;k>=0;k--) *(s16*)((u8*)p+k*2+8)=0;
 r=(f64)h/16384.0; p->coeff[8]=h; step=r;
 for(k=9;k<16;k++){r=r*step;*(s16*)((u8*)p+k*2+8)=(s16)(s32)(r*16384.0);}
 }else {entry->f20=0;index++;}
 }
}
