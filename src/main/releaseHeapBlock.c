#include "common.h"

typedef struct Nw2MemBlock {
    struct Nw2MemBlock *next;
    u32 size;
    u64 tag;
} Nw2MemBlock;

extern Nw2MemBlock *D_8002EE94;
extern s32 D_8007C430;

/* Frees the block whose payload is arg0: clears its magic, re-inserts it into
 * the circular free list in address order, and coalesces with the following
 * and/or preceding free block when they are adjacent. */
void releaseHeapBlock(u8 *arg0) {
    Nw2MemBlock *p;
    Nw2MemBlock *cur;
    Nw2MemBlock *next;
    u32 size;

    if (arg0 == NULL) {
        return;
    }
    cur = D_8002EE94;
    p = (Nw2MemBlock *)(arg0 - 0x10);
    p->tag = 0;
    for (;;) {
        if (cur < p) {
            if (p < cur->next) {
                break;
            }
        }
        next = cur->next;
        if (cur < next) {
            cur = next;
            continue;
        }
        if (cur < p) {
            break;
        }
        if (p < next) {
            break;
        }
        cur = next;
    }
    if (p + p->size == cur->next) {
        p->size = p->size + cur->next->size;
        p->next = cur->next->next;
    } else {
        p->next = cur->next;
    }
    size = cur->size;
    if (cur + size == p) {
        cur->size = size + p->size;
        cur->next = p->next;
    } else {
        cur->next = p;
    }
    D_8002EE94 = cur;
    D_8007C430 = D_8007C430 - 1;
}
