/* @header
 * MusSetSongFxChange  (originally func_80014340)
 * VRAM 0x80014340 | ROM 0x14F40 | size 0x5C
 * asm: asm/nonmatchings/main/MusSetSongFxChange.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (same code as the SDK source). */
#include "common.h"

typedef struct{u8 type;s32 value;}Msg;
void __MusIntHandleSetFlag(s32,s32,s32);void __MusIntMemMove(void*,void*,s32);
extern s32 fifo_start,fifo_current,fifo_limit;extern u8 *fifo_addr;
extern s32 mus_songfxchange_flag,mus_last_fxtype;
extern u32 max_channels;extern u8 *mus_channels;
/* When arg0 is zero, queue a type-2 message carrying the current sequence value,
 * then latch arg0 into mus_songfxchange_flag if the enqueue succeeded. */
void MusSetSongFxChange(s32 arg0){Msg msg;s32 r=1;if(arg0==0){msg.type=2;msg.value=mus_last_fxtype;mus_last_fxtype=msg.value;r=__MusIntFifoAddCommand(&msg);}if(r)mus_songfxchange_flag=arg0;}
