#include "common.h"

extern u32 D_800604C8;
extern u8 *D_800604D0;

/* Applies the mask/value pair (flags & arg1) | arg2 to the flags word of every
 * voice whose key matches arg0. */
void func_800160E8(s32 arg0, u32 arg1, u32 arg2) {
    volatile u64 pad;
    u32 n = D_800604C8;
    u8 *p = D_800604D0;
    u32 i = 0;
    u32 count;

    if (n != 0) {
        count = n;
        do {
            i++;
            if (*(s32 *)(p + 0x60) == arg0) {
                *(s32 *)p = (*(s32 *)p & arg1) | arg2;
            }
            p += 0x158;
        } while (i < count);
    }
}
