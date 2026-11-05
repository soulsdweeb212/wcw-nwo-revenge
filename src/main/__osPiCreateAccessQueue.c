/* @header
 * __osPiCreateAccessQueue  (originally func_80027F00)
 * VRAM 0x80027F00 | ROM 0x28B00 | size 0x54
 * asm: asm/nonmatchings/main/__osPiCreateAccessQueue.s
 */
/* SDK: libultra 2.0I, ultralib src/io/piacs.c (same code as the SDK source). */
#include "common.h"

s32 osCreateMesgQueue(s32 *, s32 *, s32);
s32 osSendMesg(s32 *, s32, s32);
extern s32 __osPiAccessQueueEnabled;
extern s32 piAccessBuf;
extern s32 __osPiAccessQueue;

/* Initialize the message queue at __osPiAccessQueue from piAccessBuf, mark it active, and
 * send a zero message. */
void __osPiCreateAccessQueue(void) {
    __osPiAccessQueueEnabled = 1;
    osCreateMesgQueue(&__osPiAccessQueue, &piAccessBuf, 1);
    osSendMesg(&__osPiAccessQueue, 0, 0);
}
