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

/* Return the entry value at (table arg0, index arg1), or the fallback value. */
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
