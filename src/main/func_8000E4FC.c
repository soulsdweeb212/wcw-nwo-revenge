/* @header
 * func_8000E4FC
 * VRAM 0x8000E4FC | ROM 0xF0FC | size 0x60
 * asm: asm/nonmatchings/main/func_8000E4FC.s
 */
#include "common.h"

extern u16 D_8006A2A4[];
#ifdef TARGET_PC
/* PC: D_80031060 holds addresses (of s16 tables), so it is a table of pointers on PC (8 bytes each), filled from the
 * ROM in that layout (port/game_vars.tsv). */
extern s16 *D_80031060[];
#else
extern u8 D_80031060[];
#endif
extern s16 D_80030DD4[];

/* Decode entity `entity`'s entry in D_8006A2A4, select the pointer-table slot in
 * D_80031060 from its high bits, and return the s16 that `arg1` selects within it. */
s16 func_8000E4FC(s16 entity, s16 arg1) {
    u16 v;
    s16 *p;
    u32 ti;
    s32 idx;
    u32 off;
    v = D_8006A2A4[entity];
    ti = v >> 6;
    idx = (v & 0x1F) - 1;
    off = ti & 0x7C;
    idx = idx * 2;
#ifdef TARGET_PC
    p = D_80031060[off / 4]; /* off is the N64 byte offset of entry off / 4 */
#else
    p = *(s16 **)(D_80031060 + off);
#endif
    return D_80030DD4[p[idx + arg1]];
}
