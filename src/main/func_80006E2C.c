#include "common.h"

s32 releaseHeapBlock(s32);

/* Release the two heap allocations referenced by arg0 (+0 and +4) and clear the
 * pointers. */
void func_80006E2C(void *arg0) {
    s32 a;
    s32 b;

    a = *(s32 *)((s8 *)arg0 + 0);
    if (a != 0) {
        releaseHeapBlock(a);
        *(s32 *)((s8 *)arg0 + 0) = 0;
    }
    b = *(s32 *)((s8 *)arg0 + 4);
    if (b != 0) {
        releaseHeapBlock(b);
        *(s32 *)((s8 *)arg0 + 4) = 0;
    }
}
