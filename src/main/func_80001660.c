/* @header
 * func_80001660
 * VRAM 0x80001660 | ROM 0x2260 | size 0x34
 * asm: asm/nonmatchings/main/func_80001660.s
 */
#include "common.h"

void *func_80001694();

/* Allocate a new scratch block, attach arg0 as its owner, and push it onto the head
 * of arg0's work-block chain (+0x14). */
void func_80001660(void *arg0) {
    void *block;

    block = func_80001694();
    *(void **)((s8 *)block + 4) = arg0;
    *(void **)((s8 *)block + 8) = (void *) *(void **)((s8 *)arg0 + 0x14);
    *(void **)((s8 *)arg0 + 0x14) = block;
}
