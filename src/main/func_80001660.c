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
