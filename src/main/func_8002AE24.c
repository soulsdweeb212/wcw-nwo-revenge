/* @header
 * func_8002AE24
 * VRAM 0x8002AE24 | ROM 0x2BA24 | size 0xBC
 * asm: asm/nonmatchings/main/func_8002AE24.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a name entry holds addresses (its name, its height and weight texts), so on PC it is the layout that
 * tools/port_data.py gives the entries of D_8003A4F8 and D_8003A59C (its NAME_ENTRY): id, value, a byte and a word as
 * on the N64, then the three addresses at +8, +0x10 and +0x18 (N64: +8, +0xC, +0x10). D_8003A59C is such an entry. */
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
} Nw2LookupEntry;
#endif

typedef struct {
    Nw2LookupEntry **entries;
    u16 count;
    u16 pad;
} Nw2LookupTable;

extern Nw2LookupTable D_8003A4F8[];
#ifdef TARGET_PC
extern Nw2LookupEntry D_8003A59C; /* PC: the entry for an unknown id, as above */
#else
extern u8 D_8003A59C[];
#endif

/* Return the s32 field at +0x10 of the lookup entry for arg0: search the 11 sub-tables
 * (D_8003A4F8) for a matching id, encoding its position as (subTable << 8) + index, and
 * fall back to the record D_8003A59C when no entry matches. */
#ifdef TARGET_PC
/* PC: that field is the address of the entry's weight text, which func_80098804 draws as a picture by that name (a key
 * of the resource-name cache), so the result is a pointer; an s32 would cut it in half. */
u8 *func_8002AE24(s32 arg0) {
#else
s32 func_8002AE24(s32 arg0) {
#endif
    Nw2LookupEntry *e;
    s32 k;
    s32 j;
    s32 idx;

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
#ifdef TARGET_PC
        e = &D_8003A59C;
#else
        e = (Nw2LookupEntry *)D_8003A59C;
#endif
    } else {
        e = D_8003A4F8[idx >> 8].entries[idx & 0xFF];
    }
#ifdef TARGET_PC
    return e->weight; /* PC: the field by name, in the PC layout above */
#else
    return *(s32 *)((u8 *)e + 0x10);
#endif
}
