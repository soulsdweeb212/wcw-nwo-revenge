/* @header
 * osAiSetNextBuffer  (originally func_80020AA0)
 * VRAM 0x80020AA0 | ROM 0x216A0 | size 0x94
 * asm: asm/nonmatchings/main/osAiSetNextBuffer.s
 */
/* SDK: libultra 2.0I, ultralib src/io/aisetnextbuf.c (same code as the SDK source). */
#include "common.h"

extern u8 D_80037520;

s32 osVirtualToPhysical(s32);
s32 __osAiDeviceBusy(void);

/* Starts an AI DMA transfer of arg1 bytes from arg0: sets the wrap flag when the
 * buffer ends on an 8KB boundary, bails if the AI is busy, then programs the
 * AI DRAM address (physical) and length registers. Returns -1 if busy. */
s32 osAiSetNextBuffer(s32 arg0, s32 arg1) {
    s32 a;
    s32 result;

    a = arg0;
    if (D_80037520 != 0) {
        a -= 0x2000;
    }
    if (((arg0 + arg1) & 0x1FFF) == 0) {
        D_80037520 = 1;
    } else {
        D_80037520 = 0;
    }
    if (__osAiDeviceBusy() != 0) {
        return -1;
    }
    result = osVirtualToPhysical(a);
    *(vu32 *)0xA4500000 = result;
    *(vu32 *)0xA4500004 = arg1;
    return 0;
}
