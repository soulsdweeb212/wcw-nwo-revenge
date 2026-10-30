/* @header
 * func_800B4B3C
 * VRAM 0x800B4B3C | ROM 0xA7FDC | size 0x124
 * asm: asm/nonmatchings/code_8009D7A0/func_800B4B3C.s
 */
#include "common.h"

extern s32 D_800E3CA0[];
extern f64 D_800E5490,D_800E5498,D_800E54A0;
/* Tests whether entity p (only when flagged 0x40) lies outside the ring
 * boundary for its facing quadrant (+0x3E): quadrants 0/1 compare the Z/X
 * position against the high f64 bounds, 2/3 against the low bound. When outside,
 * it also checks the heading delta against D_800E3CA0[quadrant] and returns 1
 * if it is within 0x3C7, else 0. */
s32 func_800B4B3C(u8 *p) {
 s32 outside, result;
 if(*(u64*)(p+0x20)&0x40) {
 outside=0;
 switch(*(s16*)(p+0x3E)) {
 case 0: if(*(f32*)(p+0x74)>D_800E5490) outside=1; result=outside; break;
 case 1: if(*(f32*)(p+0x6C)>D_800E5498) outside=1; result=outside; break;
 case 2: if(*(f32*)(p+0x74)<D_800E54A0) outside=1; result=outside; break;
 case 3: if(*(f32*)(p+0x6C)<D_800E54A0) outside=1; result=outside; break;
 default: result=outside; break;
 }
 if(result) {
 if(func_800D3550(func_800D3684(D_800E3CA0[*(s16*)(p+0x3E)],*(s32*)(p+0x58)))<0x3C7) return 1;
 }
 }
 return 0;
}
