#include "common.h"

typedef struct {
    s32 f0;
    u32 f4;
    s32 f8;
} NwAllocHdr;

/* Bump-allocate (arg3 * arg4) bytes, rounded up to 16, from the region described by
 * arg2; returns the block, or NULL when it does not fit. */
void *func_800202B0(void *arg0, void *arg1, NwAllocHdr *arg2, s32 arg3, s32 arg4) {
    u32 size;
    u32 total;
    void *ret;

    size = (arg3 * arg4 + 0xF) & ~0xF;
    total = arg2->f0 + arg2->f8;
    ret = NULL;
    if (total >= arg2->f4 + size) {
        ret = (void *)arg2->f4;
        arg2->f4 += size;
    }
    return ret;
}

/* Copy arg2 bytes from arg0 to arg1. */
void func_80020300(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < arg2; i++) {
        *arg1 = *arg0;
        arg0++;
        arg1++;
    }
}
