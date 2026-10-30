/* @header
 * func_8002AD68
 * VRAM 0x8002AD68 | ROM 0x2B968 | size 0xBC
 * asm: asm/nonmatchings/main/func_8002AD68.s
 */
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

/* Search the first 11 lookup tables for an entry with the given id, then return
 * that entry's data word (+0xC); the default entry D_8003A59C is used when the
 * id isn't found. */
s32 func_8002AD68(s32 arg0) {
    Nw2LookupEntry *e;
    s32 k, j, idx;
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
    return *(s32 *)((u8 *)e + 0xC);
}
