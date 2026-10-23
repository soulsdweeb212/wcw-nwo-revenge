#include "common.h"

extern s16 D_800E74DC;
extern s16 D_800E7C88;

extern void *D_800E7518;
extern u8 D_800E7CE0[];
extern u8 D_800E7CE4[];
extern u8 D_800E7CE8[];
extern u8 D_800E7CF0[];
extern s32 D_800E7BE8;
extern s32 D_800E7BEC;
extern s32 D_800E8220;

void *allocateHeap(s32);

/* Return one of the two cached values selected by arg0. */
s16 func_80096A48(s32 arg0) {
    if (arg0 != 0) {
        return D_800E7C88;
    }
    return D_800E74DC;
}

/* Allocate and initialize the 96 resource-request records and 64 cache entries. */
void func_80098E1C(void) {
    volatile u64 pad1;
    volatile u64 pad2;
    u8 *p;
    u8 *next;
    s32 i;
    s32 off;

    p = allocateHeap(0x480);
    i = 0x5F;
    D_800E7518 = p;
    p += 0x474;
    do {
        *(s32 *)p = 0;
        i -= 1;
        p -= 0xC;
    } while (i >= 0);
    i = 0;
    off = 0;
    next = D_800E7CE8;
    do {
        *(u8 **)(D_800E7CE0 + off) = next;
        next += 0x14;
        *(s32 *)(D_800E7CE4 + off) = 1;
        *(s32 *)(D_800E7CE8 + off) = 0;
        *(s32 *)(D_800E7CF0 + off) = 0;
        i += 1;
        off += 0x14;
    } while (i < 0x40);
    D_800E7BEC = 0;
    D_800E7BE8 = 0;
    D_800E8220 = 0;
}
