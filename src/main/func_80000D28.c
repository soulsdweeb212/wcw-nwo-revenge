#include "common.h"

s32 func_8001C740(s32);

/* Push node arg1 (carrying arg2 at +4) onto the list head at arg0+0x260, restoring
 * the interrupt mask afterwards. */
void func_80000D28(void *arg0, void *arg1, s32 arg2) {
    s32 saved;

    saved = func_8001C740(1);
    *(s32 *)((s8 *)arg1 + 4) = arg2;
    *(void **)((s8 *)arg1 + 0) = *(void **)((s8 *)arg0 + 0x260);
    *(void **)((s8 *)arg0 + 0x260) = arg1;
    func_8001C740(saved);
}
