#include "common.h"

void *func_80001694();

/* Allocate a new scratch block, attach arg0 as its owner (+4), and append it to the
 * end of arg0's work-block chain (linked through +8). */
void *func_8000160C(void *arg0) {
    void *block;
    void *tail;

    block = func_80001694();
    *(void **)((s8 *)block + 4) = arg0;
    tail = *(void **)((s8 *)arg0 + 0x14);
    if (*(s32 *)((s8 *)tail + 8) != 0) {
        do {
            tail = *(void **)((s8 *)tail + 8);
        } while (*(s32 *)((s8 *)tail + 8) != 0);
    }
    *(void **)((s8 *)tail + 8) = block;
    return block;
}
