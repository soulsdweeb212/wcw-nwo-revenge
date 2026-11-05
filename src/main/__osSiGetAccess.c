/* @header
 * __osSiGetAccess  (originally func_80027744)
 * VRAM 0x80027744 | ROM 0x28344 | size 0x6C
 * asm: asm/nonmatchings/main/__osSiGetAccess.s
 */
/* SDK: libultra 2.0I, ultralib src/io/siacs.c (same code as the SDK source). */
#include "common.h"

extern s32 __osSiAccessQueueEnabled;
extern s32 __osPiDevMgr;
extern s32 D_80037608;
extern u8 siAccessBuf[];
extern u8 __osSiAccessQueue[];

s32 osCreateMesgQueue(void *, void *, s32);
s32 osRecvMesg(void *, void *, s32);
s32 osSendMesg(void *, s32, s32);

/* One-time setup: register the send/receive queues and enqueue message 0,
 * then block on the queue anchored above __osSiAccessQueueEnabled for the next message. */
void __osSiGetAccess(void) {
    s32 sp10;

    if (__osSiAccessQueueEnabled == 0) {
        __osSiAccessQueueEnabled = 1;
        osCreateMesgQueue(siAccessBuf + 0x19760, siAccessBuf, 1);
        osSendMesg(__osSiAccessQueue, 0, 0);
    }
    osRecvMesg((u8 *)&__osSiAccessQueueEnabled + 0x45970, &sp10, 1);
}
