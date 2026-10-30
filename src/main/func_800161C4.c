/* @header
 * func_800161C4
 * VRAM 0x800161C4 | ROM 0x16DC4 | size 0x128
 * asm: asm/nonmatchings/main/func_800161C4.s
 */
#include "common.h"

#define F(o,t,x) (*(t *)((u8 *)(o)+(x)))
/* Parses the audio voice envelope descriptor pointed to by arg1 into voice
 * arg0: attack/decay/release times, the per-stage deltas derived from the peak
 * levels, and the corresponding step rates; returns the cursor past the parsed
 * bytes. */
u8 *func_800161C4(void *arg0, u8 *arg1) {
 s32 n, v;
 n=*arg1++;
 if(n==0) n=1;
 F(arg0,u8,0xDF)=n;
 F(arg0,s32,0x84)=0x400/n;
 F(arg0,u8,0xE0)=*arg1++;
 n=*arg1++;
 F(arg0,u8,0xE6)=n;
 v=*arg1++;
 F(arg0,f32,0x78)=(1.0/(f32)n)*(f32)(v-F(arg0,u8,0xE0));
 F(arg0,u8,0xE1)=v;
 n=*arg1++;
 F(arg0,u8,0xE7)=n;
 v=*arg1++;
 F(arg0,f32,0x7C)=(1.0/(f32)n)*(f32)(v-F(arg0,u8,0xE1));
 F(arg0,u8,0xE2)=v;
 n=*arg1++;
 F(arg0,u8,0xE8)=n;
 F(arg0,f32,0x80)=1.0/(f32)n;
 return arg1;
}
