#include "common.h"

void func_8001B090(void *,void *);
void func_8001F070(void *,void *,void *,s32);
s32 func_800202B0(s32,s32,s32,s32,s32);
void func_8001D720(void);void func_8001DF00(void);void func_8001F200(void);void func_8001F3EC(void);
/* Initializes the two-buffer audio object arg0 with its callbacks, allocates its
 * two 32-byte work buffers from arg2 and seeds its state. */
void func_8001D4E4(u8 *arg0,s32 (*arg1)(void *),s32 arg2) {
 func_8001F070(arg0,func_8001D720,func_8001DF00,0);
 *(s32*)(arg0+0x14)=func_800202B0(0,0,arg2,1,32);
 *(s32*)(arg0+0x18)=func_800202B0(0,0,arg2,1,32);
 *(s32*)(arg0+0x30)=arg1(arg0+0x34);
 *(s32*)(arg0+0x3C)=0;*(s32*)(arg0+0x40)=1;*(s32*)(arg0+0x44)=0;
}
u32 func_8001CE80(u32);
