/* @header
 * osScAddClient  (originally func_80000D28)
 * VRAM 0x80000D28 | ROM 0x1928 | size 0x58
 * asm: asm/nonmatchings/main/osScAddClient.s
 */
/* SDK: libultra 2.0I, ultralib src/sched/sched.c (same code as the SDK source). */
#include "common.h"

s32 osSetIntMask(s32);

/* Push node arg1 (carrying arg2 at +4) onto the list head at arg0+0x260, restoring
 * the interrupt mask afterwards. */
void osScAddClient(void *arg0, void *arg1, s32 arg2) {
    s32 saved;

    saved = osSetIntMask(1);
    *(s32 *)((s8 *)arg1 + 4) = arg2;
    *(void **)((s8 *)arg1 + 0) = *(void **)((s8 *)arg0 + 0x260);
    *(void **)((s8 *)arg0 + 0x260) = arg1;
    osSetIntMask(saved);
}
