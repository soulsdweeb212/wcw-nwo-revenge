/* @header
 * func_80014340
 * VRAM 0x80014340 | ROM 0x14F40 | size 0x5C
 * asm: asm/nonmatchings/main/func_80014340.s
 */
#include "common.h"

typedef struct{u8 type;s32 value;}Msg;
void func_800160E8(s32,s32,s32);void func_80015EF8(void*,void*,s32);
extern s32 D_80060504,D_80060508,D_8006050C;extern u8 *D_80060510;
extern s32 D_800604F8,D_800604FC;
extern u32 D_800604C8;extern u8 *D_800604D0;
/* When arg0 is zero, queue a type-2 message carrying the current sequence value,
 * then latch arg0 into D_800604F8 if the enqueue succeeded. */
void func_80014340(s32 arg0){Msg msg;s32 r=1;if(arg0==0){msg.type=2;msg.value=D_800604FC;D_800604FC=msg.value;r=func_8001446C(&msg);}if(r)D_800604F8=arg0;}
