#include "common.h"

/* Sum arg1 bytes at arg0, truncated to 16 bits. */
s32 func_80022120(u8 *arg0, s32 arg1) {
    s32 i;
    s32 sum = 0;

    for (i = 0; i < arg1; i++) {
        sum += *arg0;
        arg0++;
    }
    return sum & 0xFFFF;
}

typedef struct {
    u8 b0, b1, b2, b3;
    u16 f4;
    u8 b6, b7;
} Cmd8;

extern Cmd8 D_8006A260[];
