#include "common.h"

/* Sum arg1 bytes at arg0, truncated to 16 bits. */
s32 func_80022120(u8 *arg0, s32 arg1) {
    s32 i = 0;
    s32 sum = 0;

    if (arg1 > 0) {
        do {
            i++;
            sum += *arg0++;
        } while (i < arg1);
    }
    return sum & 0xFFFF;
}

/* Compute the 14-word checksum pair (sum and complement-sum) for the 0x20-byte
 * command block. */
s32 func_80022154(u16 *arg0, u16 *arg1, u16 *arg2) {
    u16 *end = arg0 + 14;
    u16 v;

    *arg2 = 0;
    *arg1 = 0;
    do {
        v = *arg0;
        *arg1 += v;
        arg0++;
        *arg2 += ~v;
    } while (arg0 < end);
    return 0;
}

s32 __osContRamRead(s32, s32, s32, void *);
s32 func_80025480(void *, s32);
s32 bcmp(void *, void *, s32);

/* Validate the Controller Pak's ID block, returning 0, 2 or an error code. */
s32 __osCheckId(u8 *arg0) {
    s32 v;
    u8 buf[0x20];

    if (arg0[0x65] != 0) {
        v = func_80025480(arg0, 0);
        if (v == 2)
            v = func_80025480(arg0, 0);
        if (v != 0)
            return v;
    }
    v = __osContRamRead(*(s32 *)(arg0 + 4), *(s32 *)(arg0 + 8), 1, buf);
    if (v != 0) {
        if (v != 2)
            return v;
        v = __osContRamRead(*(s32 *)(arg0 + 4), *(s32 *)(arg0 + 8), 1, buf);
        if (v != 0)
            return v;
    }
    return (bcmp(arg0 + 0xC, buf, 0x20) != 0) << 1;
}

typedef struct {
    u8 b[8];
} Ent8;

extern Ent8 D_8006A260[];

/* Decode the queued controller-read entries into six-byte result records. */
void func_80023058(u8 *arg0) {
    Ent8 *src;
    u8 *dst;
    Ent8 e;
    s32 i;
    u32 v;

    src = D_8006A260;
    dst = arg0;
    i = 0;
    if (D_80070A98 > 0) {
        do {
            e = *src;
            v = (e.b[2] & 0xC0) >> 4;
            dst[4] = v;
            if (v == 0) {
                *(u16 *)dst = *(u16 *)(e.b + 4);
                dst[2] = e.b[6];
                dst[3] = e.b[7];
            }
            i++;
            src++;
            dst += 6;
        } while (i < D_80070A98);
    }
}
