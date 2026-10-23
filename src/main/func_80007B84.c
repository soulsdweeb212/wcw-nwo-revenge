#include "common.h"

/* Allocate arg1 16-byte records from the pool at arg0; returns the block, or NULL
 * when the capacity is exceeded. */
void *func_80007B50(void *arg0, s32 arg1) {
    u16 used = *(u16 *)((u8 *)arg0 + 6);
    s32 off = used * 0x10;
    u16 cap = *(u16 *)((u8 *)arg0 + 4);
    s32 p = *(s32 *)arg0;

    p += off;
    used += arg1;
    *(u16 *)((u8 *)arg0 + 6) = used;
    return (used <= cap) ? (void *)p : NULL;
}

/* Allocate arg1 8-byte records from the second pool in arg0. */
void *func_80007B84(void *arg0, s32 arg1) {
    u16 used = *(u16 *)((u8 *)arg0 + 0xE);
    s32 off = used * 8;
    u16 cap = *(u16 *)((u8 *)arg0 + 0xC);
    s32 p = *(s32 *)((u8 *)arg0 + 8);

    p += off;
    used += arg1;
    *(u16 *)((u8 *)arg0 + 0xE) = used;
    return (used <= cap) ? (void *)p : NULL;
}

/* Convert 16 color words with a gamma-ish curve selected by mode (arg1 & 0xFF). */
void func_800079D8(u16 *arg0, s32 arg1) {
    s32 mode = arg1 & 0xFF;
    u32 i;
    u16 c;
    s32 hi;

    for (i = 0; i < 16; i++, arg0++) {
        u32 v;

        if (mode == 1) {
            v = *arg0 >> 3;
        } else if (mode < 2) {
            if (mode) {
                v = *arg0 << 2;
            } else {
                v = *arg0 >> 8;
            }
        } else {
            v = *arg0 << 2;
        }
        c = v & 0xF8;
        if (c != 0) {
            hi = c + 7;
            c = 0xFF - ((u16)((0xFF - c) * (0xFF - c)) >> 8);
        } else {
            hi = c;
        }
        *arg0 = c | (hi << 8);
    }
}
