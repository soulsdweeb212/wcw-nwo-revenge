#include "common.h"

extern s32 D_800388A0;
extern s32 D_80037600;
extern s32 D_80037608;
extern u8 D_80064AB0[];
extern u8 D_8007E210[];

s32 func_8001C890(void *, void *, s32);
s32 func_8001C990(void *, void *, s32);
s32 func_8001CAC0(void *, s32, s32);

/* If the PI DMA channel is idle, record the pending value in D_800388A0 and
 * return 0; otherwise return -1. */
s32 func_800273A0(s32 value) {
    s32 r;
    if (*(vu32 *)0xA4040010 & 1) {
        *(vu32 *)&D_800388A0 = value;
        r = 0;
    } else {
        r = -1;
    }
    return r;
}

/* Returns the cached pointer D_80037608 when the D_80037600 flag is set. */
s32 func_80027950(void) {
    return D_80037600 ? D_80037608 : 0;
}

/* One-time setup: register the send/receive queues and enqueue message 0,
 * then block on the queue anchored above D_800388A0 for the next message. */
void func_80027744(void) {
    s32 sp10;

    if (D_800388A0 == 0) {
        D_800388A0 = 1;
        func_8001C890(D_80064AB0 + 0x19760, D_80064AB0, 1);
        func_8001CAC0(D_8007E210, 0, 0);
    }
    func_8001C990((u8 *)&D_800388A0 + 0x45970, &sp10, 1);
}
