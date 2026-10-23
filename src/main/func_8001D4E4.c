#include "common.h"

void func_8001B090(void *,void *);
/* Builds a scale matrix (diagonal arg1/arg2/arg3, 1 for w) and converts it to
 * fixed point at arg0. */
void buildScaleMatrixFixed(void *arg0,f32 arg1,f32 arg2,f32 arg3) {
 f32 m[4][4]; f32 (*p)[4]=m;
 initIdentityMatrix4x4(p);
 p[0][0]=arg1;p[1][1]=arg2;p[2][2]=arg3;p[3][3]=1.0f;
 func_8001B090(p,arg0);
}
void func_8001F070(void *,void *,void *,s32);
s32 func_800202B0(s32,s32,s32,s32,s32);
void func_8001D720(void);void func_8001DF00(void);void func_8001F200(void);void func_8001F3EC(void);
/* Initializes the two-buffer audio object arg0 with its callbacks, allocates its
 * two 32-byte work buffers from arg2 and seeds its state. */
void func_8001D4E4(u8 *arg0,s32 (*arg1)(void *),s32 arg2) {
 func_8001F070(arg0,func_8001D720,func_8001DF00,0);
 *(s32*)(arg0+0x14)=func_800202B0(0,0,arg2,1,32);
 *(s32*)(arg0+0x18)=func_800202B0(0,0,arg2,1,32);
 *(s32*)(arg0+0x30)=arg1(arg0+0x34);
 *(s32*)(arg0+0x3C)=0;*(s32*)(arg0+0x40)=1;*(s32*)(arg0+0x44)=0;
}
/* Initializes the single-buffer audio object arg0 with its callbacks and one
 * 32-byte work buffer from arg1, and resets its state fields. */
void func_8001D594(u8 *arg0,s32 arg1) {
 func_8001F070(arg0,func_8001F200,func_8001F3EC,1);
 *(s32*)(arg0+0x14)=func_800202B0(0,0,arg1,1,32);
 *(s32*)(arg0+0x20)=0;*(s32*)(arg0+0x24)=1;*(s32*)(arg0+0x30)=0;
 *(s32*)(arg0+0x1C)=0;*(s32*)(arg0+0x28)=0;*(s32*)(arg0+0x2C)=0;
 *(f32*)(arg0+0x18)=1.0f;
}
u32 func_8001CE80(u32);
/* Emits a four-word audio command block for arg0 into arg2 and clears its +0x2C
 * field, returning the advanced cursor. */
u32 *func_8001A2C0(u8 *arg0,s32 arg1,u32 *arg2) {
 s32 t=arg1>>8;
 arg2[0]=0x0B000020;
 arg2[1]=func_8001CE80((u32)(arg0+8));
 arg2[2]=(arg0[0x2F]<<16)|(*(u16*)(arg0+2)|0x0E000000);
 arg2[3]=(t<<24)|(func_8001CE80(*(u32*)(arg0+0x28))&0xFFFFFF);
 *(s32*)(arg0+0x2C)=0;
 return arg2+4;
}
