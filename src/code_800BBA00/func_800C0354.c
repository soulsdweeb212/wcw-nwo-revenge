/* @header
 * func_800C0354
 * VRAM 0x800C0354 | ROM 0xB37F4 | size 0x664
 * asm: asm/nonmatchings/code_800BBA00/func_800C0354.s
 */
#include "common.h"

typedef struct {
 u8 p0[2]; s16 f2,f4,f6,f8,fA,fC; u8 pE[6]; s16 f14,f16; u8 p18[8]; u64 flags; u8 p28[4]; u32 f2C; u8 p30[0x18]; u16 f48; u8 p4A[2]; f32 f4C,f50,f54; s32 f58; u8 p5C[0x2E0]; f32 vec[3]; u8 p348[0xD]; s8 f355;
} ObjC0354;
extern ObjC0354 *D_800FAF5C;
extern s8 D_800FADB8;
extern u8 D_8007E228[],D_80070494[],D_80075468[],D_8007C438[],D_8007EF30[],D_800FA065[];
extern u16 D_800FADD0,D_800F99BA,D_800EB4C0,D_800E3AB4[],D_800E3970[];
extern u8 *D_80038A64[];
extern f64 D_800E58C8,D_800E58D0,D_800E58D8;
void func_8000DB90(s32,s32);
s32 func_8000DC50(s32,s32);
void func_80003684(void*,s32,void*);
void func_800BA770(s32,s32,s32);
void func_800C2B8C(void*);
void func_800E1920(void*,s32);
void func_800D427C(void*,s16,s32);
s16 func_800D4D44(void*,s32,s32);
f32 func_800D63F0(void*,void*,s32);
void func_800D37C0(void*,f32,void*);
s8 func_800D25D0(void*,f32);
void func_800D4AD0(void*);
s32 func_800D2B64(void*,f32,u16,s32);
void translateEntityXZ(void*,void*);
void func_800C0354(void) {
 u16 mask; s16 anim; s32 mode; f32 speed; u8 buf[0x30];
 D_800FAF5C->flags |= 0x1000000000ULL;
 mask=D_800E3AB4[D_800FADB8];
 if (D_800FADD0 & (mask ^ 15)) return;
 D_800FADD0 |= mask;
 if (D_800FAF5C->fC >= 5) D_800F99BA = D_800E3970[D_800FADB8] | 0x21; else D_800F99BA = 0x124;
 switch(D_800FAF5C->fC) {
 case 0: if(D_800FAF5C->f4<=0) D_800FAF5C->fC++; break;
 case 1: {
 u16 v; s32 i; s32 lo; s32 j;
 func_8000DB90(D_800FADB8,0);
 v=D_800FAF5C->f48; lo=v&0xFF; j=(v&0xF00)>>6; i=lo-1;
 D_800EB4C0=*(u16*)(*(u8**)((u8*)D_80038A64+j)+i*2);
 func_80003684(buf,D_800EB4C0,D_80070494+0x10C+D_800FADB8*0x40);
 D_800FAF5C->fC++; break;
 }
 case 2: func_80003684(buf+0x10,(u16)(D_800EB4C0+1),D_80075468+0x10+D_800FADB8*0x1A30); D_800FAF5C->fC++; break;
 case 3: func_80003684(buf+0x20,(u16)(D_800EB4C0+2),D_8007C438+0x180+D_800FADB8*0x600); D_800FAF5C->fC++; break;
 case 4: if((func_8000DC50(D_800FADB8,(s16)D_800FAF5C->f48)<<16)==0) D_800FAF5C->fC++; break;
 case 5:
 func_8000DB90(D_800FADB8,1);
 if(D_8007E280&0x400) func_800BA770(D_800FADB8,(s16)D_800FAF5C->f48,1);
 D_800FAF5C->flags &= ~0x1C0ULL;
 if(D_800FAF5C->f2==1) {
 D_800FAF5C->f58=0x800; D_800FAF5C->f4C=0; D_800FAF5C->f54=0; D_800FAF5C->f50=1500.0f; D_800FAF5C->flags|=0x40ULL;
 } else {
 D_800FAF5C->f58=0x800; D_800FAF5C->f4C=0; D_800FAF5C->f50=0; D_800FAF5C->f54=1150.0f; D_800FAF5C->flags|=0x100ULL;
 }
 D_800FA065[D_800FAF5C->f355*0x3B0]=(u8)D_800FADB8;
 if(D_8007E280&0x100) { D_800FAF5C->f14=100; D_800FAF5C->flags|=0x80000ULL; D_800FAF5C->flags|=0x20ULL; D_800FAF5C->flags|=4ULL; }
 func_800E1920(D_800FAF5C,6);
 if(D_800FAF5C->f2==1) { func_800D427C(D_800FAF5C,0x10DD,0); D_800FAF5C->fC=8; }
 else {
 anim=func_800D4D44(D_800FAF5C,10,0); func_800D427C(D_800FAF5C,anim,0);
 speed=(f64)func_800D63F0(D_800FAF5C,0,2)*D_800E58C8;
 func_800D37C0((void*)D_800FAF5C->f58,speed,D_800FAF5C->vec); D_800FAF5C->fC++;
 }
 D_800FAF5C->f16=0; break;
 case 6:
 D_800FAF5C->f16++; if(D_800FAF5C->f16==5) func_800C2B8C(D_800FAF5C);
 translateEntityXZ(D_800FAF5C,D_800FAF5C->vec);
 if(!(*(u16*)(D_8007EF30+0x170)&0x400)) { if(func_800D25D0(D_800FAF5C,4.0f)!=-1) { func_800D427C(D_800FAF5C,func_800D4D44(D_800FAF5C,11,0),3); D_800FAF5C->fC++; break; } }
 if(func_800D2B64(D_800FAF5C,4.0f,0,0xFFFFE)) { D_800FAF5C->flags=(D_800FAF5C->flags&~0x100ULL)|0xC0ULL; func_800D427C(D_800FAF5C,0xE7D,3); D_800FAF5C->fC++; } break;
 case 8:
 D_800FAF5C->f16++; if(D_800FAF5C->f16==5) func_800C2B8C(D_800FAF5C);
 D_800FAF5C->f50=D_800FAF5C->f50-D_800E58D0;
 if(!(D_800FAF5C->f50<D_800E58D8)) break;
 D_800FAF5C->f50=90.0f;
 func_800D427C(D_800FAF5C,0x10DE,0); D_800FAF5C->fC++; break;
 case 7: case 9: if(D_800FAF5C->f4<=0) { D_800FADD0 &= ~D_800E3AB4[D_800FADB8]; func_800D4AD0(D_800FAF5C); func_800A6C48(D_800FAF5C,0x2B); } break;
 }
}
