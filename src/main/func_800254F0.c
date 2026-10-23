#include "common.h"

s32 __osCheckId(void *);
s32 func_80025480(u8 *, s32);
s32 __osContRamWrite(s32, s32, s32, void *, s32);

/* Optional Controller Pak name update: requires bit 0 of the +0 word; validate the pak via
 * __osCheckId, then copy up to 32 non-zero bytes of arg1 into the header name area at
 * +0x2C. When the name-length byte at +0x65 is set, first rewrite the bank descriptor via
 * func_80025480(p, 0) and then write the 7-byte name block at p+0x2C back to the pak. */
s32 func_800254F0(u8 *p, u8 *arg1) {
    s32 r, i;
    if (!(*(s32 *)p & 1)) return 5;
    r = __osCheckId(p);
    if (r != 0) return r;
    if (arg1) {
        for (i = 0; i < 32; i++, arg1++) {
            u8 b = *arg1;
            if (!b) break;
            p[i + 0x2c] = b;
        }
    }
    if (p[0x65]) {
        r = func_80025480(p, 0);
        if (r == 0) r = __osContRamWrite(*(s32 *)(p + 4), *(s32 *)(p + 8), 7, p + 0x2c, 0);
    }
    return r;
}
