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
typedef struct { u8 b[0x2A]; } Nw2Move;

extern Nw2LookupTable lookupSubTables[];
extern u16 D_8003A4FC[][4];
extern Nw2LookupEntry D_8003A59C;
extern Nw2Move *D_8003A594;

static inline Nw2Move *nw2MoveFor(s32 move, u32 slot) {
    if ((u32)(move - 1) >= 0x4F) {
        goto fallback;
    }
    if (slot < 4) {
        goto found;
    }
fallback:
    return D_8003A594;
found:
    return &D_8003A594[move * 4 + slot];
}

Nw2Move *func_8002B7E0(s32 arg0, u32 arg1) {
    Nw2LookupEntry *e;
    s32 k;
    s32 j;
    s32 idx;

    for (k = 0; k < 0xB; k++) {
        for (j = 0; j < D_8003A4FC[k][0]; j++) {
            if (lookupSubTables[k].entries[j]->id == arg0) {
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
        e = lookupSubTables[idx >> 8].entries[idx & 0xFF];
    }
    return nw2MoveFor(e->value, arg1);
}
