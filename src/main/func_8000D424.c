/* @header
 * func_8000D424
 * VRAM 0x8000D424 | ROM 0xE024 | size 0x1D4
 * asm: asm/nonmatchings/main/func_8000D424.s
 */
#include "common.h"

/* Outside-of-arena containment/zone test for a position (x,y,z): within the
 * inner 224 unit box -> zone 4; within the higher 230 unit box -> zone 4;
 * otherwise split into one of four quadrants by the x+/-z diagonals and look
 * up the zone (elevated positions get their own sub-zone). Writes to out+0x18. */
f32 func_80003CF0(f32);
s32 func_8001143C(s32);
extern f64 D_8003B1C8,D_8003B1D0,D_8003B1D8;
static __inline__ s32 inBoundsD424(f32 x,f32 z) {
 f64 bound=D_8003B1D8;
 f32 ax=func_80003CF0(x);
 s32 inside=0;
 if (ax<bound) inside=func_80003CF0(z)<bound;
 return inside;
}
void func_8000D424(u8 *dst,f32 x,f32 y,f32 z) {
 s32 quadrant,zone;
 if(func_80003CF0(x)<224.0f && func_80003CF0(z)<224.0f) zone=4;
 else if(D_8003B1C8<=y && func_80003CF0(x)<230.0f && func_80003CF0(z)<230.0f) zone=4;
 else {
 quadrant=0;
 if(x+z<0.0) quadrant=2;
 quadrant|=(x-z<0.0);
 if(D_8003B1D0<=y && inBoundsD424(x,z)) {
 zone=func_8001143C(quadrant);
 if(zone!=0) zone=5; else zone=1;
 } else zone=func_8001143C(quadrant);
 }
 dst[0x18]=zone;
}
