/* @header
 * __osPiGetAccess  (originally func_80027F54)
 * VRAM 0x80027F54 | ROM 0x28B54 | size 0x6C
 * asm: asm/nonmatchings/main/__osPiGetAccess.s
 */
/* SDK: libultra 2.0I, ultralib src/io/piacs.c (same code as the SDK source). */
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

/* Lazily initializes the Controller Pak message queue and then blocks for one
 * message into sp10. */
void __osPiGetAccess(void) {
    s32 sp10;

    if (__osPiAccessQueueEnabled == 0) {
        __osPiAccessQueueEnabled = 1;
        osCreateMesgQueue(piAccessBuf + 0xF3D8, piAccessBuf, 1);
        osSendMesg(__osPiAccessQueue, 0, 0);
    }
    osRecvMesg((u8 *)&__osMaxControllers + 0x3400, &sp10, 1);
}
