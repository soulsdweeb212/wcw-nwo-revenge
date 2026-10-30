/* @header
 * unpackAnimationParameters  (originally func_800A7D64)
 * VRAM 0x800A7D64 | ROM 0x9B204 | size 0x208
 * asm: asm/nonmatchings/code_8009D7A0/func_800A7D64.s
 */
#include "common.h"

/* Unpack one packed animation/skeleton parameter record (6 u32 words) into a
 * 30-byte destination: a fixed layout of 3/6/7/8/10/12-bit fields, plus a
 * flag pass that sets the top two bits of sign-flagged 6-bit angle fields. */
typedef struct { u16 high:10; u16 low:6; } Nw2PackedSixBits;
void unpackAnimationParameters(u8 *dst, u32 *packed) {
 *(u16 *)(dst+0)=packed[0]&0x7FF;
 *(u16 *)(dst+2)=(packed[5]>>5)&0xFFF;
 dst[4]=(packed[0]>>11)&63;
 dst[5]=(packed[0]>>17)&63;
 dst[6]=(packed[0]>>23)&63;
 dst[7]=packed[1]&7;
 dst[8]=(packed[1]>>3)&7;
 dst[9]=(packed[1]>>6)&7;
 dst[10]=(packed[1]>>9)&7;
 dst[11]=packed[2]&31;
 dst[12]=(packed[2]>>5)&31;
 dst[13]=(packed[2]>>10)&31;
 dst[14]=packed[5]&31;
 dst[15]=(packed[3]>>22)&7;
 dst[16]=(packed[3]>>28)&7;
 dst[17]=packed[4]&7;
 dst[18]=(packed[4]>>3)&7;
 dst[19]=packed[1]>>28;
 dst[20]=(packed[1]>>12)&15;
 dst[21]=(packed[3]>>25)&7;
 dst[22]=((Nw2PackedSixBits *)((u8 *)packed+12))->low;
 dst[23]=packed[3];
 dst[24]=(packed[2]>>20)&63;
 dst[25]=(packed[2]>>15)&31;
 dst[26]=packed[3]>>8;
 dst[27]=packed[2]>>26;
 dst[28]=((Nw2PackedSixBits *)((u8 *)packed+4))->low;
 dst[29]=(packed[1]>>22)&63;
 *(u32 *)(dst+32)=packed[4]>>6;
 if(dst[5]&32)dst[5]|=0xC0;
 if(dst[6]&32)dst[6]|=0xC0;
 if(dst[28]&32)dst[28]|=0xC0;
 if(dst[29]&32)dst[29]|=0xC0;
 if(dst[22]&32)dst[22]|=0xC0;
}
