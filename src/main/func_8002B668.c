/* @header
 * func_8002B668
 * VRAM 0x8002B668 | ROM 0x2C268 | size 0x54
 * asm: asm/nonmatchings/main/func_8002B668.s
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
