/* @header
 * viMgrMain  (originally func_80025A60)
 * VRAM 0x80025A60 | ROM 0x26660 | size 0x198
 * asm: asm/nonmatchings/main/viMgrMain.s
 */
/* SDK: libultra 2.0I, ultralib src/io/vimgr.c (same code as the SDK source). */
#include "common.h"

typedef struct {
    u8 pad[0xC];
    s32 fC;
    s32 f10;
    s32 f14;
} Nw2P25A60;

s32 osRecvMesg(void *, void *, s32);
s32 osSendMesg(void *, s32, s32);
void __osViSwapContext(void);
u32 osGetCount(void);
void __osTimerInterrupt(void);
void *__osViGetCurrentContext(void);

extern u16 retrace;
extern u32 __osBaseCounter;
extern u32 __osViIntrCount;
extern u64 __osCurrentTime;

/* VI manager message loop: consumes messages from queue arg0->fC, swapping the
 * VI context every retrace retraces (case 0xD) and handling timer
 * interrupts (case 0xE). Accumulates per-frame timing in __osCurrentTime. */
void viMgrMain(Nw2P25A60 *arg0) {
    u16 *msg;
    Nw2P25A60 *obj;
    Nw2P25A60 *p;
    u32 t;
    s32 flag;

    msg = NULL;
    retrace = ((u16 *)__osViGetCurrentContext())[1];
    if (retrace == 0) {
        retrace = 1;
    }
    flag = 0;
    obj = arg0;
    for (;;) {
        osRecvMesg(obj->fC, &msg, 1);
        switch (*msg) {
        case 0xD:
            __osViSwapContext();
            if (--retrace == 0) {
                p = __osViGetCurrentContext();
                if (p->f10 != 0) {
                    osSendMesg(p->f10, p->f14, 0);
                }
                retrace = ((u16 *)p)[1];
            }
            __osViIntrCount++;
            if (flag) {
                flag = 0;
                t = osGetCount();
                __osCurrentTime = t;
            }
            t = __osBaseCounter;
            __osBaseCounter = osGetCount();
            t = __osBaseCounter - t;
            __osCurrentTime += t;
            break;
        case 0xE:
            __osTimerInterrupt();
            break;
        }
    }
}
