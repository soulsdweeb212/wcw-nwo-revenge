/* @header
 * func_8001FF5C
 * VRAM 0x8001FF5C | ROM 0x20B5C | size 0x9C
 * asm: asm/nonmatchings/main/func_8001FF5C.s
 */
#include "common.h"

u32 func_8001CE80(void *);
typedef struct{u32 w0,w1;} AudioCmd;
/* Emits the three-command audio buffer sequence for arg0 (SETBUFF with arg1/arg2,
 * a pointer command and a format command), clears arg0's +0x2C and returns the
 * advanced cursor. */
AudioCmd *func_8001FF5C(u8 *arg0,s32 arg1,s32 arg2,AudioCmd *arg3){
 AudioCmd *p=arg3;
 p[0].w0=(arg1&0xFFFF)|0x08000000;p[0].w1=((arg1&0xFFFF)<<16)|((arg2*2)&0xFFFF);
 p[1].w0=0x0B000020;p[1].w1=func_8001CE80(arg0+8);
 p[2].w0=0x0E000000|(arg0[0x2F]<<16)|*(u16*)(arg0+2);
 {
  AudioCmd *np=p+3;
  p[2].w1=func_8001CE80(*(void**)(arg0+0x28));
  *(u32*)(arg0+0x2C)=0;
  return np;
 }
}
