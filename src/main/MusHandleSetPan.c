/* @header
 * MusHandleSetPan  (originally func_80013E10)
 * VRAM 0x80013E10 | ROM 0x14A10 | size 0x70
 * asm: asm/nonmatchings/main/MusHandleSetPan.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (same code as the SDK source). */
#include "common.h"

typedef struct{u8 type;s32 value;}Msg;
void __MusIntHandleSetFlag(s32,s32,s32);void __MusIntMemMove(void*,void*,s32);
extern s32 fifo_start,fifo_current,fifo_limit;extern u8 *fifo_addr;
extern s32 mus_songfxchange_flag,mus_last_fxtype;
extern u32 max_channels;extern u8 *mus_channels;
/* Sets the pan (clamped 0..0xFF) of every voice whose key matches arg0. Returns
 * the number updated. */
s32 MusHandleSetPan(s32 arg0,s32 arg1){u32 i;s32 n;u8 *p;if(arg0==0)return 0;n=0;p=mus_channels;for(i=0;i<max_channels;i++){if(*(s32*)(p+0x60)==arg0){n++;*(s16*)(p+0xD0)=arg1;p[0xDE]=255;}p+=0x158;}return n;}
