/* @header
 * func_800C9AC0
 * VRAM 0x800C9AC0 | ROM 0xBCF60 | size 0x9C
 * asm: asm/nonmatchings/code_800BBA00/func_800C9AC0.s
 */
#include "common.h"

void translateEntityXZ(void*,void*);s32 func_800D35B0(s32,s32);void func_800D3E40(void*,void*,s32,void*);
/* Classifies the angle from w->heading to a1 into a quadrant 0..3 (2 when its magnitude is above 0x600,
 * 0 below 0x200, else 3 for a positive / 1 for a negative delta), rotating by 2 when flag 0x200000 is set. */
s32 func_800C9AC0(Wrestler *w,s32 a1){
    s32 x=func_800D3684(w->heading,a1);
    s32 r;
    if(func_800D3550(x)>0x600)r=2;
    else if(func_800D3550(x)<0x200)r=0;
    else r=x>=0?3:1;
    if(w->flags&0x200000)r=(r+2)&3;
    return r;
}
