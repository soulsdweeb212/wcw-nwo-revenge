/* @header
 * func_800A8D14
 * VRAM 0x800A8D14 | ROM 0x9C1B4 | size 0x78
 * asm: asm/nonmatchings/code_8009D7A0/func_800A8D14.s
 */
#include "common.h"

extern u8 D_80064AD8[];

/* Returns w's moveId plus 1..4: a packed 2-bit entry, indexed by w->move.unk38C, from the 400-byte table of
 * D_80064AD8 + 8 picked by byte 0x20 of other's profile. */
s16 func_800A8D14(Wrestler *w, Wrestler *other) {
    s8 *rec;
    s16 i;
    u8 *base;
    u8 *p;
    s16 v;

    rec = (s8 *)other->profile;
    i = w->move.unk38C;
    base = &D_80064AD8[8];
    p = base + rec[0x20] * 400;
    v = ((p[i / 4] >> ((i & 3) * 2)) & 3) + 1;
    return (u16)w->moveId + v;
}
