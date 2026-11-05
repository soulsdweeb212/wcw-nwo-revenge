/* @header
 * __osTimerServicesInit  (originally func_80027040)
 * VRAM 0x80027040 | ROM 0x27C40 | size 0x54
 * asm: asm/nonmatchings/main/__osTimerServicesInit.s
 */
/* SDK: libultra 2.0I, ultralib src/os/timerintr.c (same code as the SDK source). */
#include "common.h"

extern void *__osTimerList;
extern s32 __osBaseCounter;
extern s32 __osViIntrCount;
extern s32 __osCurrentTime;
extern s32 D_80070B24;

s32 osWritebackDCache(s32, s32);
s32 osVirtualToPhysical(s32);
void osInvalDCache(s32, s32);
s64 func_80028624(u32, u32, u32, u32);
s64 func_80028528(u32, u32, u32, u32);

typedef struct {
    void *next;
    void *prev;
    u64 a;
    u64 b;
    s32 c0;
    s32 c1;
} Node80038820;

/* Reset the PI DMA queue node and its associated counters. */
void __osTimerServicesInit(void) {
    Node80038820 *p = __osTimerList;
    *(u64 *)&__osCurrentTime = 0;
    __osBaseCounter = 0;
    __osViIntrCount = 0;
    p->b = 0;
    p->a = 0;
    p->prev = p;
    p->next = p;
    p->c0 = 0;
    p->c1 = 0;
}
