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
    u16 *p = D_8003A4E8;
    s32 i = 0;

    if (D_8003A4E8[0] == 0) {
        return 0;
    }
    for (; *p != 0; p++, i++) {
        if (*p == arg0) {
            return i + 1;
        }
    }
    return 0;
}

/* Returns subtable arg0's entry arg1 id, or the fallback id when out of range. */
u16 func_8002B668(u32 arg0, s32 arg1) {
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
    return e->id;
}
