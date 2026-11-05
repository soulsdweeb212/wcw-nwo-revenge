/* @header
 * __MusIntFifoProcessCommand  (originally func_80014418)
 * VRAM 0x80014418 | ROM 0x15018 | size 0x54
 * asm: asm/nonmatchings/main/__MusIntFifoProcessCommand.s
 */
/* SDK: libmus, libmus/src/playerinc/player_fifo.inc.c (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

typedef struct{u8 type;s32 value;}Msg;void __MusIntHandleSetFlag(s32,s32,s32);void __MusIntMemMove(void*,void*,s32);extern s32 D_80060504,D_80060508,D_8006050C;extern u8 *D_80060510;
/* Dispatch a queued audio message: type 0 starts, type 1 stops the voice; type 2 is
 * a no-op. */
void __MusIntFifoProcessCommand(Msg *p){switch(p->type){case 0:__MusIntHandleSetFlag(p->value,-2,1);break;case 1:__MusIntHandleSetFlag(p->value,-2,0);break;case 2:break;}}
