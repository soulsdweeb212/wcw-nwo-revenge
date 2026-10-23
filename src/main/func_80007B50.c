#include "common.h"

/* Allocates arg1 0x10-byte records from the descriptor's first pool (+0/+4/+6),
 * returning the block or NULL when it would overflow. */
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

/* Allocates arg1 8-byte records from the descriptor's second pool (+8/+C/+E). */
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

/* Packs 16 palette entries from the two nibble planes selected by mode: the low
 * byte is the channel value and the high byte its +7 partner (with a gamma-ish
 * correction). */
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
