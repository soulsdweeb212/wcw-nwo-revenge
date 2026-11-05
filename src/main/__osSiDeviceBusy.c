/* @header
 * __osSiDeviceBusy  (originally func_800281F0)
 * VRAM 0x800281F0 | ROM 0x28DF0 | size 0x18
 * asm: asm/nonmatchings/main/__osSiDeviceBusy.s
 */
/* SDK: libultra 2.0I, ultralib src/io/si.c (same code as the SDK source). */
#include "common.h"

extern s32 D_800389A0;
extern u8 D_80064AC0[];
extern u8 D_80073E98[];
extern u8 D_80070A98;

extern s32 D_80037248;
extern void *D_80037250;

s32 osCreateMesgQueue(void *, void *, s32);
s32 osRecvMesg(void *, void *, s32);
s32 osSendMesg(void *, s32, s32);
s32 __osDisableInt(void);
void __osEnqueueAndYield(s32 *, s32);
void __osRestoreInt(s32);

s32 __osSiDeviceBusy(void) {
    return (*(volatile u32 *)0xA4800018 & 3) != 0;
}
