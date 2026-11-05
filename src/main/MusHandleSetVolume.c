/* @header
 * MusHandleSetVolume  (originally func_80013DB0)
 * VRAM 0x80013DB0 | ROM 0x149B0 | size 0x60
 * asm: asm/nonmatchings/main/MusHandleSetVolume.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (same code as the SDK source). */
#include "common.h"

typedef struct { u8 pad0[0x60]; s32 key; u8 pad64[0x5A]; s16 value; u8 padC0[0x98]; } VoiceDB0;
extern u32 max_channels; extern VoiceDB0 *mus_channels;
/* Set the s16 value of every voice record whose key matches arg0; return how many
 * records were updated. */
s32 MusHandleSetVolume(s32 key,s32 value) {
    if(!key)return 0;
    {u32 i=0;VoiceDB0 *p=mus_channels;s32 n=0;
        while(i<max_channels) {if(p->key==key){p->value=value;n++;}i++;p++;}
        return n;}
}
