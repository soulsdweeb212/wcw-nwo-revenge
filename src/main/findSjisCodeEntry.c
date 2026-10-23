#include "common.h"

typedef struct { u32 w0, w1; } Cmd;
extern u8 D_80038D80[], D_80038DB0[];
void appendPaletteSetupDisplayList(Cmd **arg0) {
    Cmd *p = *arg0;
    { Cmd *q = p++; q->w0 = 0xDE000000; q->w1 = (u32)(D_80038D80 - 0x80000000); }
    { Cmd *q = p++; q->w0 = 0xFD100000; q->w1 = (u32)(D_80038DB0 - 0x80000000); }
    { Cmd *q = p++; q->w0 = 0xE8000000; q->w1 = 0; }
    { Cmd *q = p++; q->w0 = 0xF5000100; q->w1 = 0x07000000; }
    { Cmd *q = p++; q->w0 = 0xE6000000; q->w1 = 0; }
    { Cmd *q = p++; q->w0 = 0xF0000000; q->w1 = 0x0703C000; }
    { Cmd *q = p++; q->w0 = 0xE7000000; q->w1 = 0; }
    *arg0 = p;
}
extern u8 sjisCodeTable[];
/* Linear search of the zero-terminated two-byte Shift-JIS table; returns the
 * byte offset of the matching entry (or -1). */
static inline s32 findCode(u8 *code) {
    s32 i = 0;
    u8 *p = sjisCodeTable;
    do {
        if (code[1] == p[1] && code[0] == p[0]) return i;
        p += 2;
        i += 2;
    } while (*p);
    return -1;
}
/* Look up a two-byte Shift-JIS code in sjisCodeTable, returning a pointer to the
 * matching entry, or NULL when the table has no such code. */
u8 *findSjisCodeEntry(u8 *code) {
    s32 index = findCode(code);
    u8 *result;
    if (index < 0) result = NULL;
    else result = sjisCodeTable + index;
    return result;
}
typedef struct { u8 text[64]; s32 key0, key1; } Entry;
extern Entry *D_8007FC3C;
Entry *func_80028D18(s32 arg0, s32 arg1) {
    s32 i = 0;
    s32 j;
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
    j = 0;
    p = D_8007FC3C;
    for (; j < 40; j++, p++) {
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
