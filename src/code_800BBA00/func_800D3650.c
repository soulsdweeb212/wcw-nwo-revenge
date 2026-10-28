#include "common.h"

s32 func_800D3890(void *, void *, void *);

/* Quadrant (0..7) of the heading between arg0 and arg1. */
s32 func_800D3650(void *arg0, void *arg1) {
    s32 buf[4];
    func_800D3890(arg0, arg1, buf);
    return (buf[3] + 0x1100) / 512 & 7;
}
