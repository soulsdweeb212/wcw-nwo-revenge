#include "common.h"

typedef struct NwNode2 {
    struct NwNode2 *f0;
    struct NwNode2 *f4;
} NwNode2;

/* Insert node n at the head of list head. */
void func_8002021C(NwNode2 *n, NwNode2 *head) {
    NwNode2 *prev = head->f0;

    n->f4 = head;
    n->f0 = prev;
    if (head->f0 != NULL) {
        head->f0->f4 = n;
    }
    head->f0 = n;
}

/* Node callback: handle messages 1 and 6 by storing arg2. */
s32 func_80020190(void *arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 1:
        *(s32 *)arg0 = arg2;
        break;
    case 6:
        *(s32 *)((u8 *)arg0 + 0x14) = arg2;
        break;
    }
    return 0;
}

typedef struct {
    s32 f0;
    u32 f4;
    s32 f8;
} NwAllocHdr;

/* Bump-allocate (arg3 * arg4) bytes, rounded up to 16, from the region described by
 * arg2; returns the block, or NULL when it does not fit. */
void *func_800202B0(void *arg0, void *arg1, NwAllocHdr *arg2, s32 arg3, s32 arg4) {
    u32 off;
    u32 size;
    void *ret;

    size = (arg3 * arg4 + 0xF) & ~0xF;
    off = arg2->f4;
    ret = NULL;
    if ((u32)(arg2->f0 + arg2->f8) >= off + size) {
        ret = (void *)off;
        arg2->f4 = off + size;
    }
    return ret;
}

/* Copy arg2 bytes from arg0 to arg1. */
void func_80020300(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 i;

    i = 0;
    if (arg2 > 0) {
        do {
            *arg1 = *arg0;
            arg0++;
            i++;
            arg1++;
        } while (i < arg2);
    }
}
