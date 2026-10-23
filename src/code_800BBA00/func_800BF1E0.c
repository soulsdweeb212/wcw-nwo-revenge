#include "common.h"

/* Return arg0's per-part byte at +0x34C+arg1, or the constant 0x32 when flag 0x80000
 * is set. */
s32 func_800BF1E0(void *arg0, s16 arg1) {
    s32 v;

    if (*(u64 *)((u8 *)arg0 + 0x20) & 0x80000) {
        v = 0x32;
    } else {
        v = *(s8 *)((u8 *)arg0 + arg1 + 0x34C);
    }
    return v;
}
