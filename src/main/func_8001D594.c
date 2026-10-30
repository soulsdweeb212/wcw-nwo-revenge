/* @header
 * func_8001D594
 * VRAM 0x8001D594 | ROM 0x1E194 | size 0x8C
 * asm: asm/nonmatchings/main/func_8001D594.s
 */
#include "common.h"

void func_8001B090(void *,void *);
void func_8001F070(void *,void *,void *,s32);
s32 func_800202B0(s32,s32,s32,s32,s32);
void func_8001D720(void);void func_8001DF00(void);void func_8001F200(void);void func_8001F3EC(void);
/* Initializes the single-buffer audio object arg0 with its callbacks and one
 * 32-byte work buffer from arg1, and resets its state fields. */
void func_8001D594(u8 *arg0,s32 arg1) {
 func_8001F070(arg0,func_8001F200,func_8001F3EC,1);
 *(s32*)(arg0+0x14)=func_800202B0(0,0,arg1,1,32);
 *(s32*)(arg0+0x20)=0;*(s32*)(arg0+0x24)=1;*(s32*)(arg0+0x30)=0;
 *(s32*)(arg0+0x1C)=0;*(s32*)(arg0+0x28)=0;*(s32*)(arg0+0x2C)=0;
 *(f32*)(arg0+0x18)=1.0f;
}
u32 func_8001CE80(u32);
