/* @header
 * func_80028D18
 * VRAM 0x80028D18 | ROM 0x29918 | size 0xA8
 * asm: asm/nonmatchings/main/func_80028D18.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: an entry is common.h's Nw2KeyedBufferEntry, whose keys are as wide as a pointer: a key can be a name's address
 * (lookupPlayerNameById passes two), which an s32 would cut in half. */
typedef Nw2KeyedBufferEntry Entry;
#else
typedef struct { u8 text[64]; s32 key0, key1; } Entry;
#endif
extern Entry *D_8007FC3C;
/* Finds the 0x48-byte name record for the two keys (arg0,arg1), or claims the
 * first free record and initializes it. Returns NULL when both keys are zero or
 * no free record exists. */
#ifdef TARGET_PC
Entry *func_80028D18(uintptr_t arg0, uintptr_t arg1) {
#else
Entry *func_80028D18(s32 arg0, s32 arg1) {
#endif
    Entry *p;
    s32 i;
    Entry *result;
    if ((arg0 == 0) | (arg1 == 0)) return NULL;
    p = D_8007FC3C;
    for (i = 0; i < 40; i++, p++) {
        if (p->key0 == arg0 && p->key1 == arg1) {
            result = p;
            goto found;
        }
    }
    i = 0;
    p = D_8007FC3C;
    for (; i < 40; i++, p++) {
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
#ifdef TARGET_PC
        result->buffer[0] = 0; /* PC: Nw2KeyedBufferEntry names the text buffer */
#else
        result->text[0] = 0;
#endif
    }
    return result;
}
