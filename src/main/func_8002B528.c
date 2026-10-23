#include "common.h"

typedef struct {
    u16 id;
    u8 value;
    u8 pad;
    u16 f4;
    u16 f6;
} Nw2LookupEntry;

typedef struct {
    Nw2LookupEntry **entries;
    u16 count;
    u16 pad;
} Nw2LookupTable;

extern Nw2LookupTable D_8003A4F8[];
extern Nw2LookupEntry D_8003A59C;

extern u8 D_8003A380[];

u8 func_8002B5AC(s32 arg0);

/* Finds the first entry whose value equals arg0 and returns its id, or the
 * fallback id. */
u16 func_8002B528(s32 arg0) {
    Nw2LookupEntry *e;
    s32 k;
    s32 j;

    for (k = 0; k < 0xB; k++) {
        for (j = 0; j < D_8003A4F8[k].count; j++) {
            e = D_8003A4F8[k].entries[j];
            if (e->value == arg0) {
                goto done;
            }
        }
    }
    e = &D_8003A59C;
done:
    return e->id;
}

/* Scans the D_8003A380 byte list for the position of the value produced by
 * func_8002B5AC(arg0), then returns the paired entry's id (or 0). */
u16 func_8002B4AC(s32 arg0) {
    s32 i;

    func_8002B5AC(arg0);
    i = 0;
    if (D_8003A380[0] == 0) {
        return 0;
    }
    while (D_8003A380[i] != i) {
        if (D_8003A380[i + 1] == 0) {
            break;
        }
        i++;
    }
    if (D_8003A380[i] != 0) {
        return func_8002B528(D_8003A380[i ^ 1]);
    }
    return 0;
}
