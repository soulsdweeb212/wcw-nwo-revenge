#include "common.h"

extern s32 D_8003A594;

s32 func_8002B7E0(s32, s32);
void func_80021C40(void *, void *, s32);
void func_8002BAB8(void);
s32 allocateHeap(s32);

/* Copies the 0x2A-byte name record for group arg0 / variant arg1 into arg2. */
void func_8002BB98(s32 arg0, s32 arg1, void *arg2) {
    func_80021C40(arg2, (void *)func_8002B7E0(arg0, arg1), 0x2A);
}
