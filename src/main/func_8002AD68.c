/* @header
 * func_8002AD68
 * VRAM 0x8002AD68 | ROM 0x2B968 | size 0xBC
 * asm: asm/nonmatchings/main/func_8002AD68.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a name entry holds addresses (its name, its height and weight texts), so on PC it is the layout that
 * tools/port_data.py gives the entries of D_8003A4F8 and D_8003A59C (its NAME_ENTRY): id, value, a byte and a word as
 * on the N64, then the three addresses at +8, +0x10 and +0x18 (N64: +8, +0xC, +0x10). */
typedef struct {
    u16 id;
    u8 value;
    u8 pad;
    s32 f4;
    u8 *name;
    u8 *height;
    u8 *weight;
} Nw2LookupEntry;
#else
typedef struct {
    u16 id;
    u8 value;
    u8 pad;
    u16 f4;
    u16 f6;
} Nw2LookupEntry;
#endif

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
#ifdef TARGET_PC
/* PC: that word is the address of the entry's height text, which func_80098804 draws as a picture by that name (a key
 * of the resource-name cache), so the result is a pointer; an s32 would cut it in half. */
u8 *func_8002AD68(s32 arg0) {
#else
s32 func_8002AD68(s32 arg0) {
#endif
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
#ifdef TARGET_PC
    return e->height; /* PC: the field by name, in the PC layout above */
#else
    return *(s32 *)((u8 *)e + 0xC);
#endif
}
