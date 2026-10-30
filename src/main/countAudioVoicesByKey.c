/* @header
 * countAudioVoicesByKey  (originally func_80013D58)
 * VRAM 0x80013D58 | ROM 0x14958 | size 0x58
 * asm: asm/nonmatchings/main/countAudioVoicesByKey.s
 */
#include "common.h"

extern u32 D_800604C8; extern u8 *D_800604D0;
/* Count the active voice records whose key (+0x60) equals key. */
s32 countAudioVoicesByKey(s32 key) {
 if(!key)return 0;
 {u32 i=0; u8 *p=D_800604D0; s32 n=0;
 while(i<D_800604C8) { n+=(*(s32 *)(p+0x60)==key); i++;p+=0x158; }
 return n;}
}
