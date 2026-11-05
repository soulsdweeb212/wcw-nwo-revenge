/* @header
 * MusHandleSetFreqOffset  (originally func_80013E80)
 * VRAM 0x80013E80 | ROM 0x14A80 | size 0x70
 * asm: asm/nonmatchings/main/MusHandleSetFreqOffset.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (same code as the SDK source). */
#include "common.h"

typedef struct { u8 p0[0x44]; f32 value; u8 p48[0x18]; s32 key; u8 p64[0x48]; f32 base; u8 pB0[0xA8]; } VoiceE80;
extern u32 max_channels; extern VoiceE80 *mus_channels;
/* Adds arg1 to the pitch of every voice whose key matches arg0. Returns the
 * number updated. */
s32 MusHandleSetFreqOffset(s32 arg0,f32 arg1) {
    if(!arg0)return 0;
    {u32 i=0;VoiceE80 *p=mus_channels;s32 n=0;
        while(i<max_channels) {if(p->key==arg0){n++;p->value=arg1+p->base;}i++;p++;}
        return n;}
}
