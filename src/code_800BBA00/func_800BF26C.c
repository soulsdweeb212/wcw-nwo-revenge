#include "common.h"

extern u16 D_800EB4B8[];

/* Decrements the entity's counter D_800EB4B8[id]; when it underflows the
 * 0x1000000000000000 flag is cleared (and the counter clamped to 0), otherwise
 * the flag stays set. */
void func_800BF26C(u8 *arg0) {
    u64 *flags = (u64 *)(arg0 + 0x20);
    u16 v;

    *flags &= ~0x1000000000000000ULL;
    v = D_800EB4B8[(s8)arg0[0]] - 1;
    D_800EB4B8[(s8)arg0[0]] = v;
    if ((s16)v < 0) {
        D_800EB4B8[(s8)arg0[0]] = 0;
        return;
    }
    *flags |= 0x1000000000000000ULL;
}

/* Returns the entity's per-slot byte (+0x34C+arg1), or 0x32 when flagged
 * 0x80000. */
s32 func_800BF1E0(void *arg0, s16 arg1) {
    s32 v = 0x32;

    if ((*(u64 *)((u8 *)arg0 + 0x20) & 0x80000) == 0) {
        v = *(s8 *)((u8 *)arg0 + arg1 + 0x34C);
    }
    return v;
}
