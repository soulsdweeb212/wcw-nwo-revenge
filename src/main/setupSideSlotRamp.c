/* @header
 * setupSideSlotRamp  (originally func_8001009C)
 * VRAM 0x8001009C | ROM 0x10C9C | size 0x164
 * asm: asm/nonmatchings/main/func_8001009C.s
 */
#include "common.h"

extern u8 D_80036D28[], D_80036D2C[];
extern f64 D_8003B260;
extern u8 D_8005A1A0[];
typedef struct {s16 mode,steps; f32 angle,x,y,pad10; volatile f32 tx,ty; f32 pad1c,dx,dy;} Ramp1009C;
/* Initializes the ramp record for side arg0 / slot arg1: mirrors the angle for
 * the right-hand side, clamps it to +/-180, sets the current x/y (screen-relative),
 * and when a step count is given computes the target (mirrored through
 * D_8003B260) and per-step increments for both channels. Stores mode/steps. */
void setupSideSlotRamp(s16 arg0,s16 arg1,s16 arg2,s16 arg3,f32 arg4,f32 arg5,f32 arg6) {
 s32 side; Ramp1009C *p;
 side=D_80036D28[arg0];
 arg6-=D_80036D2C[arg1]; arg5-=230.0f;
 if(side<2) arg4=-arg4;
 if(arg4>180.0f) arg4=180.0f;
 if(arg4< -180.0f) arg4=-180.0f;
 p=(Ramp1009C *)(D_8005A1A0+side*120+arg1*40);
 p->angle=arg4; p->x=arg6; p->y=arg5;
 if(arg3) {
 p->tx=-arg6*D_8003B260;
 p->dx=(p->tx-p->x)/(f32)arg3;
 p->ty=-arg5*D_8003B260;
 p->dy=(p->ty-p->y)/(f32)arg3;
 } else {p->tx=0; p->ty=0; p->dx=0; p->dy=0;}
 p->mode=arg2; p->steps=arg3;
}
