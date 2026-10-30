/* @header
 * func_8002B750
 * VRAM 0x8002B750 | ROM 0x2C350 | size 0x40
 * asm: asm/nonmatchings/main/func_8002B750.s
 */
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
