#include "common.h"

void func_800194B8(void *, s32);

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

extern Nw2IdSubTable lookupSubTables[];
extern Nw2LookupTable D_8003A4F8[];
extern Nw2LookupEntry D_8003A59C;

/* Finds entry id arg0 across subtables 12..0 (reverse order), returning the
 * (subtable<<8)|index key or -1. */
s32 func_8002AC84(s32 arg0) {
    s32 g, i;
    for (g = 12; g >= 0; g--) {
        for (i = 0; i < lookupSubTables[g].count; i++) {
            if (lookupSubTables[g].entries[i]->id == arg0) {
                return (g << 8) + i;
            }
        }
    }
    return -1;
}

typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7;
} Cmd8;

extern Cmd8 D_8006A260[];
extern u8 D_80070A98;
