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

/* Returns the 1-based position of arg0 in the zero-terminated D_8003A4E8
 * table, or 0 if absent. */
s32 func_8002B710(s32 arg0) {
    u16 *p;
    s32 i;

    for (p = D_8003A4E8, i = 0; *p != 0; p++, i++) {
        if (*p == arg0) {
            return i + 1;
        }
    }
    return 0;
}

/* Returns subtable arg0's entry arg1 id, or the fallback id when out of range. */
u16 func_8002B668(u32 arg0, s32 arg1) {
    if (arg0 < 0xD) {
        if (arg1 >= 0) {
            if (arg1 < D_8003A4F8[arg0].count) {
                return D_8003A4F8[arg0].entries[arg1]->id;
            }
        }
    }
    return D_8003A59C.id;
}

/* Returns subtable arg0's entry arg1 value, or the fallback value. */
u8 func_8002B6BC(u32 arg0, s32 arg1) {
    Nw2LookupEntry *e;

    if (arg0 >= 0xD) {
        goto fallback;
    }
    if (arg1 < 0) {
        goto fallback;
    }
    if (arg1 < D_8003A4F8[arg0].count) {
        goto found;
    }
fallback:
    e = &D_8003A59C;
    goto done;
found:
    e = D_8003A4F8[arg0].entries[arg1];
done:
    return e->value;
}

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
