#include "common.h"

extern void *D_800E7518;
extern u8 D_800E7CE0[];
extern u8 D_800E7CE4[];
extern u8 D_800E7CE8[];
extern u8 D_800E7CF0[];
extern s32 D_800E7BE8;
extern s32 D_800E7BEC;
extern s32 D_800E8220;

void *allocateHeap(s32);

/* Allocate and clear the 0x480-byte entry pool: zero the 0x60 records (0xC bytes
 * apart, backwards from +0x474), then initialise the 0x40 cache entries
 * (0x14 bytes apart) with their storage pointer, a use count of 1 and zeroed
 * fields. Resets the pool's free counters. */
void func_80098E1C(void) {
    volatile u64 pad1;
    volatile u64 pad2;
    u8 *p;
    u8 *next;
    s32 i;
    s32 off;
    s32 one;

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
    one = 1;
    next = D_800E7CE8;
    off = 0;
    for (; i < 0x40; i++) {
        *(u8 **)(D_800E7CE0 + off) = next;
        next += 0x14;
        *(s32 *)(D_800E7CE4 + off) = one;
        *(s32 *)(D_800E7CE8 + off) = 0;
        *(s32 *)(D_800E7CF0 + off) = 0;
        off += 0x14;
    }
    D_800E7BEC = 0;
    D_800E7BE8 = 0;
    D_800E8220 = 0;
}
