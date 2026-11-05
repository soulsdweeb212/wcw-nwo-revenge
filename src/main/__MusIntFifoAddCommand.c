/* @header
 * __MusIntFifoAddCommand  (originally func_8001446C)
 * VRAM 0x8001446C | ROM 0x1506C | size 0x94
 * asm: asm/nonmatchings/main/__MusIntFifoAddCommand.s
 */
/* SDK: libmus, libmus/src/playerinc/player_fifo.inc.c (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

typedef struct{u8 type;s32 value;}Msg;void __MusIntHandleSetFlag(s32,s32,s32);void __MusIntMemMove(void*,void*,s32);extern s32 fifo_start,fifo_current,fifo_limit;extern u8 *fifo_addr;
/* Copies an 8-byte message into the audio command queue at the write index,
 * advancing it (wrapping) and failing when the queue is full. Returns 1 on
 * success. */
s32 __MusIntFifoAddCommand(void *arg0){s32 old=fifo_current; s32 next=(old+1)%fifo_limit;s32 r;if(next!=fifo_start){__MusIntMemMove(arg0,fifo_addr+old*8,8);fifo_current=next;r=1;}else r=0;return r;}
