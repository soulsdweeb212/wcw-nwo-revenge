/* @header
 * buildWrestlerNameRecord  (originally func_8002B8E4)
 * VRAM 0x8002B8E4 | ROM 0x2C4E4 | size 0x1D4
 * asm: asm/nonmatchings/main/func_8002B8E4.s
 */
#include "common.h"

/* Build a 0x2A-byte wrestler name/appearance record for (id, variant).
 * Scans the 11 lookup sub-tables for the id (falling back to D_8003A59C),
 * maps id/variant to the 5 appearance bytes via func_8000B630 (written to
 * +0x24..+0x28), formats the long (25-byte) and short (11-byte) name strings
 * from the entry's name (special-casing Mortis/THQ man), and clears the
 * trailing bytes at +0x18 and +0x23. */
typedef struct { u16 id; u8 value; u8 pad; s32 field4; char *name; } NameEntry;
typedef struct { NameEntry **entries; u16 count, pad; } NameTable;
extern NameTable lookupSubTables[];
extern NameEntry D_8003A59C;
extern char D_80039958[], D_80039B80[];
void func_8000B630(u8 *, s16, s16);
void func_80021F60(void *, s32);
void func_80028C44(void *, void *);
void func_80028BB8(void *, void *);
void buildWrestlerNameRecord(s32 id, s32 variant, u8 *out) {
    u8 values[5];
    NameEntry *entry;
    s32 k, j, idx;
    char *name;
    for (k = 0; k < 11; k++) {
        for (j = 0; j < lookupSubTables[k].count; j++) {
            if (lookupSubTables[k].entries[j]->id == id) { idx = (k << 8) + j; goto lookup; }
        }
    }
    idx = -1;
lookup:
    if (idx < 0) entry = &D_8003A59C;
    else entry = lookupSubTables[idx >> 8].entries[idx & 255];
    if (id == 0) id = 1;
    func_8000B630(values, (s16)id, (s16)variant);
    out[0x24] = values[1]; out[0x25] = values[0]; out[0x26] = values[2]; out[0x27] = values[3]; out[0x28] = values[4];
    func_80021F60(out, 25); func_80021F60(out + 25, 11);
    if (id == 0x404 && ((variant == 1) | (variant == 3))) name = D_80039958;
    else if (id == 0x601 && ((variant == 1) | (variant == 3))) name = D_80039B80;
    else name = entry->name;
    func_80028C44(out, name); func_80028BB8(out + 25, name);
    out[0x23] = 0; out[0x18] = 0;
}
