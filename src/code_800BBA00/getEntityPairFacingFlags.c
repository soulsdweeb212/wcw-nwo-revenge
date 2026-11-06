/* @header
 * getEntityPairFacingFlags  (originally func_800D3CCC)
 * VRAM 0x800D3CCC | ROM 0xC716C | size 0x174
 * asm: asm/nonmatchings/code_800BBA00/getEntityPairFacingFlags.s
 */
#include "common.h"

f32 func_80003A3C(f32,f32);
f32 nw2Sqrtf(f32);
extern f64 D_800E6BC8;
typedef union {f32 f;s32 i;} FacingFI;
typedef struct {FacingFI e[4];} FacingVec;
static inline void facingDirection(f32 *a,f32 *b,FacingVec *out) {
    FacingVec v; f32 dz,dx,dist;
    dx=b[0]-a[0]; v.e[0].f=dx;
    dz=b[2]-a[2]; v.e[2].f=dz;
    dist=nw2Sqrtf(dx*dx+dz*dz); v.e[1].f=dist;
    v.e[3].i=(s32)(func_80003A3C(dx,dz)*D_800E6BC8);
    *out=v;
}
static inline s32 facingAbs(s32 d) {s32 a; if(d<0) a=-d; else a=d; return a;}
static inline s32 facingWrap(s32 a) {s32 t=a; a&=0xFFF; if(t&0x800) a|=~0xFFF; return a;}
/* Facing test between wrestlers a and b, using the XZ heading from a's pelvis (jointA[1]) to b's.
 * Bit 1: a's heading is within 0x400 (90 degrees) of the direction to b; else bit 2.
 * Bit 4: b's heading is within 0x400 of the direction back to a; else bit 8. */
u16 getEntityPairFacingFlags(Wrestler *a,Wrestler *b) {
    FacingVec v; s32 diff,ang,t; u16 flags=0;
    facingDirection(&a->jointA[1].x,&b->jointA[1].x,&v);
    diff=a->heading-v.e[3].i;
    if(diff>=0) t=diff; else t=-diff;
    if(t>0x800) {if(diff<0) diff+=0x1000; else diff-=0x1000;}
    if(facingAbs(diff)<=0x400) flags|=1; else flags|=2;
    ang=facingWrap(v.e[3].i+0x800);
    diff=b->heading-ang;
    if(facingAbs(diff)>0x800) {if(diff<0) diff+=0x1000; else diff-=0x1000;}
    if(diff>=0) t=diff; else t=-diff;
    if(t<=0x400) flags|=4; else flags|=8;
    return flags;
}
