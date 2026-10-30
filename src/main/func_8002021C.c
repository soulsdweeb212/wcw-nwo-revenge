/* @header
 * func_8002021C
 * VRAM 0x8002021C | ROM 0x20E1C | size 0x20
 * asm: asm/nonmatchings/main/func_8002021C.s
 */
#include "common.h"

typedef struct NwNode2 {
    struct NwNode2 *f0;
    struct NwNode2 *f4;
} NwNode2;

/* Insert node n at the head of list head. */
void func_8002021C(NwNode2 *n, NwNode2 *head) {
    NwNode2 *prev = head->f0;

    n->f4 = head;
    n->f0 = prev;
    if (head->f0 != NULL) {
        head->f0->f4 = n;
    }
    head->f0 = n;
}

typedef struct {
    s32 f0;
    u32 f4;
    s32 f8;
} NwAllocHdr;
