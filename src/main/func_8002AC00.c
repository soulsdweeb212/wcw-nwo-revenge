#include "common.h"

typedef struct {
    u8 b[6];
} Nw2Six;

extern s32 D_8007E00C[];

extern u8 D_8007DFD0[];

extern Nw2IdSubTable lookupSubTables[];

/* Finds entry id arg0 across the first 11 lookup subtables, returning the
 * (subtable<<8)|index key or -1. */
s32 func_8002AC00(s32 arg0) {
    s32 g;
    s32 i;

    for (g = 0; g < 0xB; g++) {
        for (i = 0; i < lookupSubTables[g].count; i++) {
            if (lookupSubTables[g].entries[i]->id == arg0) {
                return (g << 8) + i;
            }
        }
    }
    return -1;
}
