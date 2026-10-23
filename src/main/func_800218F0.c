#include "common.h"

/* identical to func_800213CC (matched), with its names changed by decomp.wtf */
typedef struct { u8 b0,b1,b2,b3,b4,b5,b6,b7; } Cmd8;
typedef struct { s16 f0; u8 f2, f3; } Out4;
extern Cmd8 D_8007DFD0[];
extern u8 D_80070A98;
/* Decodes the polled controller responses: for each of the D_80070A98 entries
 * writes the error nibble and (for good entries) the two payload bytes and the
 * type, and returns the connected bitmask in *arg0. */
void func_800218F0(u8 *arg0, s16 *arg1) {
    Out4 *d; Cmd8 *src; s32 i; s16 res;
    d = (Out4 *)arg1;
    i = 0;
    res = 0;
    src = D_8007DFD0;
    for (; i < D_80070A98; i++, src++, d++) {
        Cmd8 t = *src;
        s32 v = (t.b2 & 0xC0) >> 4;
        d->f3 = v;
        if (v == 0) { d->f0 = t.b4 | (t.b5 << 8); res |= 1 << i; d->f2 = t.b6; }
    }
    *arg0 = res;
}
