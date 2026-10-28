#include "common.h"

extern s32 D_8003A594;

s32 func_8002B7E0(s32, s32);
void func_80021C40(void *, void *, s32);
void func_8002BAB8(void);
s32 allocateHeap(s32);

/* Lazily allocates the 0x3480-byte wrestler-name table and builds it. Returns 1
 * when it was just created. */
s32 func_8002B750(void) {
    if (D_8003A594 == 0) {
        D_8003A594 = allocateHeap(0x3480);
        func_8002BAB8();
        return 1;
    }
    return 0;
}
