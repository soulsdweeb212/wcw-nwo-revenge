/* @header
 * func_80013E80
 * VRAM 0x80013E80 | ROM 0x14A80 | size 0x70
 * asm: asm/nonmatchings/main/func_80013E80.s
 */
#include "common.h"

typedef struct { u8 p0[0x44]; f32 value; u8 p48[0x18]; s32 key; u8 p64[0x48]; f32 base; u8 pB0[0xA8]; } VoiceE80;
extern u32 D_800604C8; extern VoiceE80 *D_800604D0;
/* Adds arg1 to the pitch of every voice whose key matches arg0. Returns the
 * number updated. */
s32 func_80013E80(s32 arg0,f32 arg1) {
 if(!arg0)return 0;
 {u32 i=0;VoiceE80 *p=D_800604D0;s32 n=0;
 while(i<D_800604C8) {if(p->key==arg0){n++;p->value=arg1+p->base;}i++;p++;}
 return n;}
}
