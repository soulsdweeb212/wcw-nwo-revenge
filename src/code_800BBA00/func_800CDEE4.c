#include "common.h"

void translateEntityXZ(void*,void*);s32 func_800D35B0(s32,s32);void func_800D3E40(void*,void*,s32,void*);
/* Duration (in frames) of a grab/reaction from the source's +0x2C flags and the
 * target's flag 0x80000. */
s32 func_800CDEE4(u8 *p,u8 *q){s32 r;if(*(u64*)(q+0x20)&0x80000){r=30;}else{s32 flags=*(s32*)(p+0x2c);r=60;if(flags&2)r=90;if(flags&0x300)r=60;}return r;}
