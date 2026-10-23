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
extern u8 D_8003A59C[];

/* Return the s32 field at +0x10 of the lookup entry for arg0: search the 11 sub-tables
 * (D_8003A4F8) for a matching id, encoding its position as (subTable << 8) + index, and
 * fall back to the record D_8003A59C when no entry matches. */
s32 func_8002AE24(s32 arg0) {
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
        e = (Nw2LookupEntry *)D_8003A59C;
    } else {
        e = D_8003A4F8[idx >> 8].entries[idx & 0xFF];
    }
    return *(s32 *)((u8 *)e + 0x10);
}
