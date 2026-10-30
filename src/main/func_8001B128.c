/* @header
 * func_8001B128
 * VRAM 0x8001B128 | ROM 0x1BD28 | size 0xA8
 * asm: asm/nonmatchings/main/func_8001B128.s
 */
#include "common.h"

/* Converts the 2x4 fixed-point matrix at in (packed 16.16 word/halfword pairs)
 * back into the 4x4 float matrix at out, scaling each value by 1/65536. */
void func_8001B128(f32 *out, s32 *in) {
    s32 tmp[2]; s32 *w=in; u16 *h=(u16*)(in+8); f32 *base=out; s32 i,j;
    for(i=0;i<4;i++){ f32 val0,val1; f32 *p; j=0; p=base;
      while(j<2){ tmp[0]=(*w&(s32)0xFFFF0000)|*h; tmp[1]=((*w<<16)&(s32)0xFFFF0000)|h[1];
        h+=2; w++; val0=(f32)tmp[0]*(1.0f/65536.0f); val1=(f32)tmp[1]*(1.0f/65536.0f);
        p[0]=val0; p[1]=val1; p+=2; j++; }
      base+=4; }
}
