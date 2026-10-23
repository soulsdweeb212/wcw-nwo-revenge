#include "common.h"

extern s32 D_8003A594;

s32 func_8002B7E0(s32, s32);
void func_80021C40(void *, void *, s32);
void func_8002BAB8(void);
s32 allocateHeap(s32);

/* Copies the four 0x2A-byte name variants (0x18- and 0xA-byte halves) of the
 * group arg0 into consecutive records. */
void func_8002BBCC(s32 arg0) {
    s32 i = 1;
    u8 *base = (u8 *)func_8002B7E0(arg0, 0);
    u8 *p = base + 0x2A;

    for (; i < 4; i++) {
        func_80021C40(base, p, 0x18);
        func_80021C40(base + 0x19, p + 0x19, 0xA);
        p += 0x2A;
    }
}

/* Returns the address of the 0x2A-byte record for group arg0 / variant arg1, or
 * the table base when the indices are out of range. */
s32 func_8002B790(s32 arg0, u32 arg1) {
    s32 *p = &D_8003A594;
    u32 idx;

    if ((u32)(arg0 - 1) >= 0x4F || arg1 >= 4U) {
        return *p;
    }
    idx = arg0 * 4 + arg1;
    return *p + idx * 0x2A;
}

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
