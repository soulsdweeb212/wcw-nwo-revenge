#include "common.h"

extern u16 **D_80036710[];

/* Decode one 4-byte variant of a name/definition record into five bytes.
 * D_80036710 is a table of u16 pointer tables: id bits8..12 (byte offset (id>>6)&0x7C)
 * select the sub-table, id bits0..4 minus one select the entry. Variant >= 4 falls back
 * to entry 0. out[0]/out[1] are the low/high byte of the first u16 (minus one when
 * nonzero), out[2] = 15, out[3] = record byte 3 - 1, out[4] = high byte of the second
 * u16 - 1; out[2..4] are then masked to nibbles. */
void func_8000B630(u8 *out, u32 id, s16 variant) {
    u16 *entry;
    u32 i;
    u32 group = (id >> 6) & 0x7C;

    id &= 31;
    id--;
    entry = *(u16 **)((id << 2) + *(u32 *)((u8 *)D_80036710 + group));
    if (variant >= 4) variant = 0;
    entry += variant * 2;
    out[0] = entry[0];
    if (out[0]) out[0]--;
    out[1] = (s16)entry[0] >> 8;
    if (out[1]) out[1]--;
    out[2] = 15;
    out[3] = ((u8 *)entry)[3] - 1;
    out[4] = ((s16)entry[1] >> 8) - 1;
    i = 0;
    do { *(out + i + 2) &= 15; i++; } while (i < 3);
}
