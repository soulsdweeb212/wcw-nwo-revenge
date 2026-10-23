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

/* Dispatches a message to the child pointer at arg0+0x80 (command 3), resets the
 * parent state (command 4), sets the pending flag (command 9), else forwards to
 * func_800194B8. */
s32 func_80018C24(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 3:
        if (*(s32 *)(arg0 + 0x80) == 0) {
            *(s32 *)(arg0 + 0x7C) = arg2;
        } else {
            *(s32 *)*(s32 *)(arg0 + 0x80) = arg2;
        }
        *(s32 *)(arg0 + 0x80) = arg2;
        break;
    case 4:
        arg1 = 4;
        *(s32 *)(arg0 + 0x78) = 1;
        *(s32 *)(arg0 + 0x84) = 0;
        *(s16 *)(arg0 + 0x5A) = 1;
        *(s32 *)(arg0 + 0x4C) = 0;
        *(s32 *)(arg0 + 0x50) = 1;
        *(s32 *)(arg0 + 0x48) = 0;
        func_800194B8(arg0, arg1);
        break;
    case 9:
        *(s32 *)(arg0 + 0x84) = 1;
        break;
    default:
        func_800194B8(arg0, arg1);
        break;
    }
    return 0;
}

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

/* Resolves entry id arg0 (fallback D_8003A59C) and returns the s32 at +0xC. */
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

typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7;
} Cmd8;

extern Cmd8 D_8006A260[];
extern u8 D_80070A98;

/* Decodes D_80070A98 controller response records into the 4-byte status array:
 * writes the error nibble and, for good entries, the two payload bytes, and
 * returns the connected bitmask. */
void func_800213CC(u8 *arg0, s16 *arg1) {
    s16 *d16;
    u8 *d8;
    Cmd8 *src;
    u8 res;
    s32 i;

    d16 = arg1;
    res = 0;
    src = D_8006A260;
    i = 0;
    d8 = (u8 *)arg1 + 2;
    for (; i < D_80070A98; i++) {
        Cmd8 t = src[i];
        s32 v = (t.b2 & 0xC0) >> 4;
        d8[1] = v;
        if (v == 0) {
            d16[0] = t.b4 | (t.b5 << 8);
            res |= 1 << i;
            d8[0] = t.b6;
        }
        d16 += 2;
        d8 += 4;
    }
    *arg0 = res;
}
