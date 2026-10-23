#include "common.h"

void translateEntityXZ(void*,void*);s32 func_800D35B0(s32,s32);void func_800D3E40(void*,void*,s32,void*);
/* Steps a two-phase reach: while the phase counter (+0x16) is below 10 the
 * entity moves along its stored vector, turns by its +0x348 delta and runs
 * boundary correction, returning 0; afterwards it snaps its heading to a3's
 * +0xC and rotates its position into +0x4C, returning 1. */
s32 func_800CE2C8(u8 *p,u8 *q,void *a2,u8 *a3,void *a4){if(*(s16*)(p+0x16)<10){translateEntityXZ(p,p+0x33c);*(s32*)(p+0x58)=func_800D35B0(*(s32*)(p+0x58),*(s32*)(p+0x348));func_800D2C2C(p,q,a2,4.0f,a4,0xffffe);(*(s16*)(p+0x16))++;return 0;}else{*(s32*)(p+0x58)=*(s32*)(a3+0xc);func_800D3E40(a4,a3,*(s32*)(q+0x58),p+0x4c);return 1;}}
/* Advances the reach until the phase counter reaches 6 (then locks the heading
 * to a1 and returns 1). */
s32 func_800CE6E4(u8 *p,s32 a1){if(*(s16*)(p+0x16)>=6){*(s32*)(p+0x58)=a1;return 1;}translateEntityXZ(p,p+0x33c);*(s32*)(p+0x58)=func_800D35B0(*(s32*)(p+0x58),*(s32*)(p+0x348));(*(s16*)(p+0x16))++;return 0;}
/* Classifies the angle from the entity's heading (+0x58) to a1 into a quadrant
 * 0..3 (2/0 for large/small deltas), rotating by 2 when the 0x200000 flag is set. */
s32 func_800C9AC0(u8 *p,s32 a1){s32 x=func_800D3684(*(s32*)(p+0x58),a1);s32 r;if(func_800D3550(x)>0x600)r=2;else if(func_800D3550(x)<0x200)r=0;else r=x>=0?3:1;if(*(u64*)(p+0x20)&0x200000)r=(r+2)&3;return r;}
