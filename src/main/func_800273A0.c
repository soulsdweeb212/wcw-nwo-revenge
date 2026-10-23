#include "common.h"

extern s32 D_80037600;
extern s32 D_80037608;

/* Start a DMA transfer when the PI status bit 0 is set; returns 0, or -1 if busy. */
s32 func_800273A0(s32 arg0) {
    s32 r;
    if (*(vu32 *)0xA4040010 & 1) {
        *(vu32 *)0xA4080000 = arg0;
        r = 0;
    } else {
        r = -1;
    }
    return r;
}

/* Return the cached PI handle value when the handle is open. */
s32 func_80027950(void) {
    s32 c = D_80037600;
    if (c != 0) {
        return D_80037608;
    }
    return c;
}
