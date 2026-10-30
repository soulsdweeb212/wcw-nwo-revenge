/* @header
 * func_80013EF0
 * VRAM 0x80013EF0 | ROM 0x14AF0 | size 0x8C
 * asm: asm/nonmatchings/main/func_80013EF0.s
 */
#include "common.h"

typedef struct { u8 p0[0x60]; s32 key; u8 p64[0x54]; s16 value; s16 padBA; s16 scaled; u8 pBE[0xA]; u16 base; u8 pCA[0x8E]; } VoiceEF0;
extern u32 D_800604C8; extern VoiceEF0 *D_800604D0;
/* Sets the volume (clamped 1..256) of every voice whose key matches arg0,
 * scaling the voice's base level by the new value. Returns the number updated. */
s32 func_80013EF0(s32 arg0,s32 arg1) {
 if(!arg0)return 0;
 if(arg1<=0)arg1=1;else if(arg1>=257)arg1=256;
 {u32 i=0;VoiceEF0 *p=D_800604D0;s32 n=0;
 while(i<D_800604C8) {if(p->key==arg0){n++;p->value=arg1;p->scaled=(p->base*arg1)>>7;}i++;p++;}
 return n;}
}
