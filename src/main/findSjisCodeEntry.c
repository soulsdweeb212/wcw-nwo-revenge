/* @header
 * findSjisCodeEntry  (originally func_80028DC0)
 * VRAM 0x80028DC0 | ROM 0x299C0 | size 0x68
 * asm: asm/nonmatchings/main/func_80028DC0.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } Cmd;
extern u8 D_80038D80[], D_80038DB0[];
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
