#include "common.h"

extern u8 D_80037520;

s32 func_8001CE80(s32);
s32 ai_is_busy(void);

/* Starts an AI DMA transfer of arg1 bytes from arg0: sets the wrap flag when the
 * buffer ends on an 8KB boundary, bails if the AI is busy, then programs the
 * AI DRAM address (physical) and length registers. Returns -1 if busy. */
s32 func_80020AA0(s32 arg0, s32 arg1) {
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
    if (ai_is_busy() != 0) {
        return -1;
    }
    result = func_8001CE80(a);
    *(vu32 *)0xA4500000 = result;
    *(vu32 *)0xA4500004 = arg1;
    return 0;
}
