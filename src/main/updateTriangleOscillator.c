#include "common.h"

extern f64 D_8003B888,D_8003B890,D_8003B898;
/* Advances a triangle-wave oscillator: phase (+0x14) steps by rate (+0x10)*arg1,
 * wraps by subtracting 4 when it exceeds 2, and returns amplitude(+0x1C) times
 * (|phase|-1). */
f32 updateTriangleOscillator(f32 *arg0,s32 arg1){
 f32 v,t;
 v=arg0[5]+arg0[4]*(f32)arg1; arg0[5]=v;
 if(D_8003B888<(f64)v) v=(f64)v-D_8003B890;
 arg0[5]=v;
 t=(v<0.0f)?-v:v;
 v=(f64)t-D_8003B898;
 return arg0[7]*v;
}
typedef struct {u8 b0,b1,b2,b3; u16 b4; s8 b6,b7;} ReadCmd;
extern ReadCmd D_8006A260[];
extern s32 D_8006A29C;
extern u8 D_80070A98;
/* Builds the controller read-command packet list D_8006A260 (0xFF/1/4/1 type
 * record plus a 0xFE terminator) for each active controller. */
void packControllerReadCommands(void){
 s32 i; s32 *p; ReadCmd *q; ReadCmd tmp;
 q=D_8006A260;
 for(i=0xE,p=(s32*)((u8*)q+0x38);i>=0;i--){*p=0;p--;}
 D_8006A29C=1;
 tmp.b0=0xFF;tmp.b1=1;tmp.b2=4;tmp.b3=1;
 tmp.b4=0xFFFF;tmp.b6=-1;tmp.b7=-1;
 for(i=0;i<D_80070A98;i++){*q++=tmp;}
 *(u8*)q=0xFE;
}
