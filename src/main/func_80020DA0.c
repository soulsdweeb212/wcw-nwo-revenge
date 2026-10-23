#include "common.h"

extern s32 func_80027380(void);

/* Update arg0's +4 status from the hardware VI status: when status bit 0x80 is set,
 * OR in the retrace bit (bit 8) and clear bit 1; return the retrace bit. */
s32 func_80020DA0(void *arg0) {
    u32 v;
    s32 r;

    v = func_80027380();
    r = v >> 8;
    r &= 1;
    if (v & 0x80) {
        *(s32 *)((u8 *)arg0 + 4) = (*(s32 *)((u8 *)arg0 + 4) | r) & ~2;
    }
    return r;
}
