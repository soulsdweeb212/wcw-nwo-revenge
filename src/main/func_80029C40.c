#include "common.h"

void func_80029C7C(void *, u16, s32 *, s32);

/* Render arg0 into a scratch result array and return the arg2-th entry. */
s32 func_80029C40(void *arg0, u16 arg1, s32 arg2) {
    s32 values[256];
    func_80029C7C(arg0, arg1, values, arg2);
    return values[arg2];
}

typedef struct { u32 w0, w1; } Cmd;
extern u8 D_38D80[], D_38DB0[];

/* Append the standard palette/texture setup commands to the display list. */
void appendPaletteSetupDisplayList(Cmd **arg0) {
    Cmd *p = *arg0;
    Cmd *q;
    q = p++; q->w0 = 0xDE000000; q->w1 = (u32)D_38D80;
    q = p++; q->w0 = 0xFD100000; q->w1 = (u32)D_38DB0;
    q = p++; q->w0 = 0xE8000000; q->w1 = 0;
    q = p++; q->w0 = 0xF5000100; q->w1 = 0x07000000;
    q = p++; q->w0 = 0xE6000000; q->w1 = 0;
    q = p++; q->w0 = 0xF0000000; q->w1 = 0x0703C000;
    q = p++; q->w0 = 0xE7000000; q->w1 = 0;
    *arg0 = p;
}

extern u8 sjisCodeTable[];

/* Look up a two-byte Shift-JIS code in sjisCodeTable, returning the matching entry
 * or NULL. */
u8 *findSjisCodeEntry(u8 *arg0) {
    s32 i = 0;
    s32 index;
    u8 *p = sjisCodeTable;
    do {
        if (arg0[1] == p[1] && arg0[0] == p[0]) {
            index = i;
            goto found;
        }
        p += 2;
        i += 2;
    } while (*p);
    index = -1;
found:
    if (index < 0) return NULL;
    return sjisCodeTable + index;
}

typedef struct { u8 text[64]; s32 key0, key1; } Entry;
extern Entry *D_8007FC3C;

/* Find or create the 40-entry cache slot for (arg0, arg1). */
Entry *func_80028D18(s32 arg0, s32 arg1) {
    s32 i = 0;
    Entry *p;
    Entry *result;
    if ((arg0 == 0) | (arg1 == 0)) return NULL;
    p = D_8007FC3C;
    for (; i < 40; i++, p++) {
        if (p->key0 == arg0 && p->key1 == arg1) {
            result = p;
            goto found;
        }
    }
    p = D_8007FC3C;
    for (i = 0; i < 40; i++, p++) {
        if (p->key0 == 0) {
            result = p;
            goto found;
        }
    }
    result = NULL;
found:
    if (result == NULL) return NULL;
    if (result->key0 == 0) {
        result->key0 = arg0;
        result->key1 = arg1;
        result->text[0] = 0;
    }
    return result;
}
