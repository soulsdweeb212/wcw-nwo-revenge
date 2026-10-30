/* @header
 * func_8002B5AC
 * VRAM 0x8002B5AC | ROM 0x2C1AC | size 0xBC
 * asm: asm/nonmatchings/main/func_8002B5AC.s
 */
#include "common.h"

typedef struct {
    u16 id;
    u8 value;
} Nw2LookupEntry;

typedef struct {
    Nw2LookupEntry **entries;
    u16 count;
    u16 pad;
} Nw2LookupTable;

extern Nw2LookupTable D_8003A4F8[];
extern Nw2LookupEntry D_8003A59C;
extern u16 D_8003A4E8[];

/* Resolves entry id arg0 in the first 11 subtables (fallback D_8003A59C) and
 * returns its value byte. */
u8 func_8002B5AC(s32 arg0) {
    Nw2LookupEntry *e;
    s32 k;
    s32 j;
    s32 idx;

    for (k = 0; k < 0xB; k++) {
        for (j = 0; j < D_8003A4F8[k].count; j++) {
            if (D_8003A4F8[k].entries[j]->id == arg0) {
                idx = (k << 8) + j;
                goto lookup;
            }
        }
    }
    idx = -1;
lookup:
    if (idx < 0) {
        e = &D_8003A59C;
    } else {
        e = D_8003A4F8[idx >> 8].entries[idx & 0xFF];
    }
    return e->value;
}
