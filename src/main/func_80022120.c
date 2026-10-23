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

/* Decode the queued controller-read entries into six-byte result records. */
void func_80023058(u8 *arg0) {
    u16 *d16;
    u8 *d8;
    Cmd8 *src;
    s32 i;

    d16 = (u16 *)arg0;
    src = D_8006A260;
    i = 0;
    d8 = arg0 + 3;
    for (; i < D_80070A98; i++) {
        Cmd8 t = src[i];
        s32 v = (t.b2 & 0xC0) >> 4;
        d8[1] = v;
        if (v == 0) {
            d16[0] = t.f4;
            d8[-1] = t.b6;
            d8[0] = t.b7;
        }
        d16 += 3;
        d8 += 6;
    }
}
