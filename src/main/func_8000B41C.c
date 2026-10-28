#include "common.h"

extern u16 *D_80031998[];
extern s16 D_8003673C[];
extern s32 *D_80032B44[];

/* Decode part arg0 and count the nonzero words in its D_80032B44 list. */
s16 func_8000B41C(u32 arg0) {
    u32 g = (arg0 >> 8) & 0x1F;
    u32 n = (arg0 & 0x1F) - 1;
    s32 *p = D_80032B44[g][n];
    s16 c = 0;
    if (*p != 0) {
        do {
            p++;
            c++;
        } while (*p != 0);
    }
    return c;
}
