#include "common.h"

extern u16 D_8006A2A4[];
extern u8 D_80031060[];
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
    p = *(s16 **)(D_80031060 + off);
    return D_80030DD4[p[idx + arg1]];
}
