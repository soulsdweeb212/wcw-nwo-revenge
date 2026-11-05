/* @header
 * osYieldThread  (originally func_800281A0)
 * VRAM 0x800281A0 | ROM 0x28DA0 | size 0x48
 * asm: asm/nonmatchings/main/osYieldThread.s
 */
/* SDK: libultra 2.0I, ultralib src/os/yieldthread.c (same code as the SDK source). */
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

/* Mark the current thread stopped (state 2) and enqueue it on the runnable list. */
void osYieldThread(void) {
    s32 s;
    s32 v;

    s = __osDisableInt();
    v = 2;
    *(s16 *)((u8 *)D_80037250 + 0x10) = v;
    __osEnqueueAndYield(&D_80037248, v);
    __osRestoreInt(s);
}
