#include "common.h"

s32 allocateHeap(s32);
void releaseHeapBlock(s32);

/* Allocates arg1 0x10-byte records from the descriptor's first pool (+0/+4/+6),
 * returning the block or NULL when it would overflow. */
void *func_80007B50(void *arg0, s32 arg1) {
    u16 used = *(u16 *)((u8 *)arg0 + 6);
    s32 p = *(s32 *)arg0 + used * 0x10;
    u16 cap = *(u16 *)((u8 *)arg0 + 4);

    used += arg1;
    *(u16 *)((u8 *)arg0 + 6) = used;
    return (used <= cap) ? (void *)p : NULL;
}

/* Allocates arg1 8-byte records from the descriptor's second pool (+8/+C/+E). */
void *func_80007B84(void *arg0, s32 arg1) {
    u16 used = *(u16 *)((u8 *)arg0 + 0xE);
    s32 p = *(s32 *)((u8 *)arg0 + 8) + used * 8;
    u16 cap = *(u16 *)((u8 *)arg0 + 0xC);

    used += arg1;
    *(u16 *)((u8 *)arg0 + 0xE) = used;
    return (used <= cap) ? (void *)p : NULL;
}

/* Reinitializes the descriptor's two pools: frees the old buffers and allocates
 * new ones sized for arg1 0x10-byte and arg2 8-byte records. */
void func_80007A74(void *arg0, s32 arg1, s32 arg2) {
    s32 old;

    old = *(s32 *)((u8 *)arg0 + 0);
    if (old != 0) {
        releaseHeapBlock(old);
    }
    *(s16 *)((u8 *)arg0 + 6) = 0;
    *(s16 *)((u8 *)arg0 + 4) = arg1;
    *(s32 *)((u8 *)arg0 + 0) = allocateHeap((arg1 & 0xFFFF) * 0x10);
    old = *(s32 *)((u8 *)arg0 + 8);
    if (old != 0) {
        releaseHeapBlock(old);
    }
    *(s16 *)((u8 *)arg0 + 0xE) = 0;
    *(s16 *)((u8 *)arg0 + 0xC) = arg2;
    *(s32 *)((u8 *)arg0 + 8) = allocateHeap((arg2 & 0xFFFF) * 8);
}

/* Packs 16 palette entries from the two nibble planes selected by mode: the low
 * byte is the channel value and the high byte its +7 partner (with a gamma-ish
 * correction). */
void func_800079D8(u16 *arg0, s32 arg1) {
    u32 i;
    u32 mode = arg1 & 0xFF;
    u16 c;
    u16 hi;
    u32 v;

    for (i = 0; i < 16; i++) {
        switch (mode) {
        case 0:
            v = *arg0 >> 8;
            break;
        case 1:
            v = *arg0 >> 3;
            break;
        default:
            v = *arg0 << 2;
            break;
        }
        c = v & 0xF8;
        hi = c;
        if (c != 0) {
            hi = c + 7;
            c = 0xFF - ((u16)((0xFF - c) * (0xFF - c)) >> 8);
        }
        *arg0 = c | (hi << 8);
        arg0++;
    }
}
