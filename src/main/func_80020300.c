#include "common.h"

typedef struct {
    s32 f0;
    u32 f4;
    s32 f8;
} NwAllocHdr;

/* Copy arg2 bytes from arg0 to arg1. */
void func_80020300(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < arg2; i++) {
        *arg1 = *arg0;
        arg0++;
        arg1++;
    }
}
