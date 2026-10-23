#include "common.h"

/* func_80022484: reads the 32-byte save block from each Controller Pak
 * variant (1, 3, 4 and 6), accepts the first variant whose checksum and its
 * inverse at block[14]/block[15] validate, then writes that block back to the
 * other three variants. Returns the OS error on failure, 0xA if no variant
 * validates, otherwise 0.
 * (Cannot be renamed: two matched callers still carry a local prototype of
 * the old name - see proposal #27.) */
s32 __osContRamRead(s32, s32, u16, u16 *);
s32 __osContRamWrite(s32, s32, u16, u16 *, s32);
s32 func_80025480(void *, s32);

typedef struct { u8 pad0[4]; s32 f4; s32 f8; u8 padC[0x59]; u8 type; } Nw2PakContext;

static __inline__ void checksumSaveBlock(u16 *sum, u16 *inverse, u16 *it, u16 *end) {
    u16 v;
    *inverse = 0;
    *sum = 0;
    do {
        v = *it++;
        *sum += v;
        *inverse += ~v;
    } while (it < end);
}

s32 func_80022484(Nw2PakContext *ctx, u16 *data) {
    u16 variants[4];
    u16 sum, nsum;
    u16 *p;
    s32 index;
    s32 count;
    s32 r;

    if (ctx->type != 0 && (r = func_80025480(ctx, 0)) != 0) {
        return r;
    }
    variants[0] = 1;
    variants[1] = 3;
    variants[2] = 4;
    variants[3] = 6;
    index = 1;
    p = &variants[1];
    for (; index < 4; index++) {
        r = __osContRamRead(ctx->f4, ctx->f8, *p, data);
        if (r != 0) {
            return r;
        }
        checksumSaveBlock(&sum, &nsum, data, data + 14);
        if (data[14] == sum && data[15] == nsum) {
            break;
        }
        p += 1;
    }
    if (index == 4) {
        return 0xA;
    }
    for (count = 0; count < 4; count++) {
        if (count != index) {
            r = __osContRamWrite(ctx->f4, ctx->f8, variants[count], data, 1);
            if (r != 0) {
                return r;
            }
        }
    }
    return 0;
}
