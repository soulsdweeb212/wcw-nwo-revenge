/* @header
 * __osSiRawStartDma  (originally func_80025810)
 * VRAM 0x80025810 | ROM 0x26410 | size 0xA4
 * asm: asm/nonmatchings/main/__osSiRawStartDma.s
 */
/* SDK: libultra 2.0I, ultralib src/io/sirawdma.c (same code as the SDK source). */
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

/* Start a transfer into the fixed buffer 0x1FC007C0. Polls the controller/PI
 * status at 0xA4800018; if busy (bits 0-1) returns -1. Otherwise latches the
 * source address osVirtualToPhysical(addr) into 0xA4800000 and the destination into
 * 0xA4800004 (channel 0) or 0xA4800010 (channel 1), with direction setup via
 * osWritebackDCache/osInvalDCache. Returns 0. */
s32 __osSiRawStartDma(s32 channel, s32 addr) {
    if (*(volatile s32 *)0xA4800018 & 3) {
        return -1;
    }
    if (channel == 1) {
        osWritebackDCache(addr, 0x40);
    }
    *(volatile s32 *)0xA4800000 = osVirtualToPhysical(addr);
    if (channel == 0) {
        *(volatile s32 *)0xA4800004 = 0x1FC007C0;
    } else {
        *(volatile s32 *)0xA4800010 = 0x1FC007C0;
    }
    if (channel == 0) {
        osInvalDCache(addr, 0x40);
    }
    return 0;
}
