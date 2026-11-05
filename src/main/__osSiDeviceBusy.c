/* @header
 * __osSiDeviceBusy  (originally func_800281F0)
 * VRAM 0x800281F0 | ROM 0x28DF0 | size 0x18
 * asm: asm/nonmatchings/main/__osSiDeviceBusy.s
 */
/* SDK: libultra 2.0I, ultralib src/io/si.c (same code as the SDK source). */
#include "common.h"

extern s32 __osPiAccessQueueEnabled;
extern u8 piAccessBuf[];
extern u8 __osPiAccessQueue[];
extern u8 __osMaxControllers;

extern s32 __osRunQueue;
extern void *__osRunningThread;

s32 osCreateMesgQueue(void *, void *, s32);
s32 osRecvMesg(void *, void *, s32);
s32 osSendMesg(void *, s32, s32);
s32 __osDisableInt(void);
void __osEnqueueAndYield(s32 *, s32);
void __osRestoreInt(s32);

s32 __osSiDeviceBusy(void) {
    return (*(volatile u32 *)0xA4800018 & 3) != 0;
}
