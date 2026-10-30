/* @header
 * updateTriangleOscillator  (originally func_8001FFF8)
 * VRAM 0x8001FFF8 | ROM 0x20BF8 | size 0x8C
 * asm: asm/nonmatchings/main/updateTriangleOscillator.s
 */
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
