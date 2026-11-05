/* @header
 * MusSetSongFxChange  (originally func_80014340)
 * VRAM 0x80014340 | ROM 0x14F40 | size 0x5C
 * asm: asm/nonmatchings/main/MusSetSongFxChange.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (same code as the SDK source). */
#include "common.h"

typedef struct{u8 type;s32 value;}Msg;
void __MusIntHandleSetFlag(s32,s32,s32);void __MusIntMemMove(void*,void*,s32);
extern s32 D_80060504,D_80060508,D_8006050C;extern u8 *D_80060510;
extern s32 D_800604F8,D_800604FC;
extern u32 D_800604C8;extern u8 *D_800604D0;
/* When arg0 is zero, queue a type-2 message carrying the current sequence value,
 * then latch arg0 into D_800604F8 if the enqueue succeeded. */
void MusSetSongFxChange(s32 arg0){Msg msg;s32 r=1;if(arg0==0){msg.type=2;msg.value=D_800604FC;D_800604FC=msg.value;r=__MusIntFifoAddCommand(&msg);}if(r)D_800604F8=arg0;}
