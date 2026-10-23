#include "common.h"

void translateEntityXZ(void*,void*);s32 func_800D35B0(s32,s32);void func_800D3E40(void*,void*,s32,void*);
/* Duration (in frames) of a grab/reaction from the source's +0x2C flags and the
 * target's flag 0x80000. */
s32 func_800CDEE4(u8 *p,u8 *q){s32 r;if(*(u64*)(q+0x20)&0x80000){r=30;}else{s32 flags=*(s32*)(p+0x2c);r=60;if(flags&2)r=90;if(flags&0x300)r=60;}return r;}
/* First ten frames translate the entity and advance its heading; afterwards snap it
 * to the target and rotate. */
s32 func_800CE2C8(u8 *p,u8 *q,void *a2,u8 *a3,void *a4){s32 r;if(*(s16*)(p+0x16)<10){translateEntityXZ(p,p+0x33c);*(s32*)(p+0x58)=func_800D35B0(*(s32*)(p+0x58),*(s32*)(p+0x348));func_800D2C2C(p,q,a2,4.0f,a4,0xffffe);(*(s16*)(p+0x16))++;r=0;}else{*(s32*)(p+0x58)=*(s32*)(a3+0xc);func_800D3E40(a4,a3,*(s32*)(q+0x58),p+0x4c);r=1;}return r;}
/* Advance the grab timer for six frames, then hold the given heading. */
s32 func_800CE6E4(u8 *p,s32 a1){s32 r;if(*(s16*)(p+0x16)>=6){*(s32*)(p+0x58)=a1;r=1;}else{translateEntityXZ(p,p+0x33c);*(s32*)(p+0x58)=func_800D35B0(*(s32*)(p+0x58),*(s32*)(p+0x348));(*(s16*)(p+0x16))++;r=0;}return r;}
/* Classify the heading delta between the entity and a1 into a 0..3 quadrant,
 * mirrored when flag 0x200000 is set. */
s32 func_800C9AC0(u8 *p,s32 a1){s32 x=func_800D3684(*(s32*)(p+0x58),a1);s32 r=2;if(func_800D3550(x)<0x601){r=0;if(func_800D3550(x)>=0x200)r=x>=0?3:1;}if(*(u64*)(p+0x20)&0x200000)r=(r+2)&3;return r;}
