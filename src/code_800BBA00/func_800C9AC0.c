/* @header
 * func_800C9AC0
 * VRAM 0x800C9AC0 | ROM 0xBCF60 | size 0x9C
 * asm: asm/nonmatchings/code_800BBA00/func_800C9AC0.s
 */
#include "common.h"

void translateEntityXZ(void*,void*);s32 func_800D35B0(s32,s32);void func_800D3E40(void*,void*,s32,void*);
/* Classifies the angle from the entity's heading (+0x58) to a1 into a quadrant
 * 0..3 (2/0 for large/small deltas), rotating by 2 when the 0x200000 flag is set. */
s32 func_800C9AC0(u8 *p,s32 a1){s32 x=func_800D3684(*(s32*)(p+0x58),a1);s32 r;if(func_800D3550(x)>0x600)r=2;else if(func_800D3550(x)<0x200)r=0;else r=x>=0?3:1;if(*(u64*)(p+0x20)&0x200000)r=(r+2)&3;return r;}
