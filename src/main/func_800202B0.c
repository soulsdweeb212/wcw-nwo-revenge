/* @header
 * func_800202B0
 * VRAM 0x800202B0 | ROM 0x20EB0 | size 0x48
 * asm: asm/nonmatchings/main/func_800202B0.s
 */
#include "common.h"

typedef struct { s32 f0; u32 f4; s32 f8; } NwAllocHdr;

/* Bump-allocate (arg3 * arg4) bytes, rounded up to 16, from the region described by
 * arg2; returns the block, or NULL when it does not fit. */
void *func_800202B0(void *arg0, void *arg1, NwAllocHdr *arg2, s32 arg3, s32 arg4) {
    u32 size = (arg3 * arg4 + 0xF) & ~0xF;
    u32 end = arg2->f4 + size;
    void *ret = NULL;

    if ((u32)(arg2->f0 + arg2->f8) >= end) {
        ret = (void *)arg2->f4;
        arg2->f4 = end;
    }
    return ret;
}
