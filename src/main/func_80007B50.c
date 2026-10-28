#include "common.h"

/* Allocates arg1 0x10-byte records from the descriptor's first pool (+0/+4/+6),
 * returning the block or NULL when it would overflow. */
void *func_80007B50(void *arg0, s32 arg1) {
    u16 used = *(u16 *)((u8 *)arg0 + 6);
    s32 off = used * 0x10;
    u16 cap = *(u16 *)((u8 *)arg0 + 4);
    s32 p = *(s32 *)arg0;

    p += off;
    used += arg1;
    *(u16 *)((u8 *)arg0 + 6) = used;
    return (used <= cap) ? (void *)p : NULL;
}
