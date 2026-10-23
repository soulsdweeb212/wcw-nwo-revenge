#include "common.h"

extern s16 D_8006A2A4[];
extern u16 *D_80031998[];
extern s16 D_8003673C[];
extern s32 *D_80032B44[];

s16 func_8000B3C4(s32 arg0) {
    return D_8006A2A4[(s16)arg0];
}

s16 func_8000B3DC(u32 arg0) {
    return D_8003673C[D_80031998[(arg0 >> 6) & 0x1F][(arg0 & 0x1F) - 1] & 0x7F];
}

s16 func_8000B41C(u32 arg0) {
    s32 *p = D_80032B44[(arg0 >> 6) & 0x1F][(arg0 & 0x1F) - 1];
    s16 n = 0;
    if (*p != 0) {
        do {
            p++;
            n++;
        } while (*p != 0);
    }
    return n;
}
