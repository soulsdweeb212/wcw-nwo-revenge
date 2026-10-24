#include "common.h"

typedef struct Elem159EC {u32 f0;u8 pad4[4];u8 f8,f9;u8 padA[2];void *fC,*f10;} Elem159EC;
typedef struct {u8 pad0[16];s32 f10;u8 pad14[12];u32 f20;u8 *f24;f32 *f28;Elem159EC **f2C;} Thing159EC;
void func_80015F2C(void *,void *,u32);void func_8001C860(void);extern f64 D_8003B3B8;
#define CONVERT(out,in) do {s32 b=(in);s32 v;if(b&128)v=(b&255)-256;else v=b&255;(out)=(f32)v;}while(0)
#define CONVERT8(out,in) do {u8 b=(in);s32 v;if(b&128)v=(b&255)-256;else v=b&255;(out)=(f32)v;}while(0)
void func_800159EC(void *arg0,s32 arg1){
 Thing159EC *s0=arg0; s32 m=0x80000000; u32 i; volatile s32 unused[4];
 if(s0->f10>=0){
 {s32 f10=s0->f10; s0->f10=f10|m;}
 func_80015F2C(&s0->f24,s0,3);
 func_80015F2C(s0->f2C,s0,s0->f20);
 i=0;
 if(s0->f20){f64 scale=D_8003B3B8;
 do {volatile f32 *p=&s0->f28[i]; f32 f; Elem159EC *e;
 CONVERT(f,*(u8*)p);
 *p=(f32)((f64)f/scale);
 CONVERT8(f,s0->f24[i]-48);
 *p+=f;
 e=s0->f2C[i];
 if(e->f9==0){
 u32 t=e->f0;
 if((t&0xFF000000)!=0xFF000000){t+=arg1;e->f0=t;}
 s0->f2C[i]->f9=1;
 if(s0->f2C[i]->fC)s0->f2C[i]->fC=(u8*)s0->f2C[i]->fC+(u32)arg0;
 if(s0->f2C[i]->f8==0)s0->f2C[i]->f10=(u8*)s0->f2C[i]->f10+(u32)arg0;
 }
 i++;
 }while(i<s0->f20);
 }
 func_8001C860();
 }
}
