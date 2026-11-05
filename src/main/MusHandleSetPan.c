/* @header
 * MusHandleSetPan  (originally func_80013E10)
 * VRAM 0x80013E10 | ROM 0x14A10 | size 0x70
 * asm: asm/nonmatchings/main/MusHandleSetPan.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (same code as the SDK source). */
#include "common.h"

typedef struct{u8 type;s32 value;}Msg;
void __MusIntHandleSetFlag(s32,s32,s32);void __MusIntMemMove(void*,void*,s32);
extern s32 D_80060504,D_80060508,D_8006050C;extern u8 *D_80060510;
extern s32 D_800604F8,D_800604FC;
extern u32 D_800604C8;extern u8 *D_800604D0;
/* Sets the pan (clamped 0..0xFF) of every voice whose key matches arg0. Returns
 * the number updated. */
s32 MusHandleSetPan(s32 arg0,s32 arg1){u32 i;s32 n;u8 *p;if(arg0==0)return 0;n=0;p=D_800604D0;for(i=0;i<D_800604C8;i++){if(*(s32*)(p+0x60)==arg0){n++;*(s16*)(p+0xD0)=arg1;p[0xDE]=255;}p+=0x158;}return n;}
