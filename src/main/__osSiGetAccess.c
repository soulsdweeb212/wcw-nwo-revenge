/* @header
 * __osSiGetAccess  (originally func_80027744)
 * VRAM 0x80027744 | ROM 0x28344 | size 0x6C
 * asm: asm/nonmatchings/main/__osSiGetAccess.s
 */
/* SDK: libultra 2.0I, ultralib src/io/siacs.c (same code as the SDK source). */
#include "common.h"

extern s32 D_800388A0;
extern s32 D_80037600;
extern s32 D_80037608;
extern u8 D_80064AB0[];
extern u8 D_8007E210[];

s32 osCreateMesgQueue(void *, void *, s32);
s32 osRecvMesg(void *, void *, s32);
s32 osSendMesg(void *, s32, s32);

/* One-time setup: register the send/receive queues and enqueue message 0,
 * then block on the queue anchored above D_800388A0 for the next message. */
void __osSiGetAccess(void) {
    s32 sp10;

    if (D_800388A0 == 0) {
        D_800388A0 = 1;
        osCreateMesgQueue(D_80064AB0 + 0x19760, D_80064AB0, 1);
        osSendMesg(D_8007E210, 0, 0);
    }
    osRecvMesg((u8 *)&D_800388A0 + 0x45970, &sp10, 1);
}
