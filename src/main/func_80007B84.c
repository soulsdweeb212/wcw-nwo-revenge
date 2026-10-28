#include "common.h"

/* Allocate arg1 8-byte records from the second pool in arg0. */
void *func_80007B84(void *arg0, s32 arg1) {
    u16 used = *(u16 *)((u8 *)arg0 + 0xE);
    s32 off = used * 8;
    u16 cap = *(u16 *)((u8 *)arg0 + 0xC);
    s32 p = *(s32 *)((u8 *)arg0 + 8);

    p += off;
    used += arg1;
    *(u16 *)((u8 *)arg0 + 0xE) = used;
    return (used <= cap) ? (void *)p : NULL;
}
