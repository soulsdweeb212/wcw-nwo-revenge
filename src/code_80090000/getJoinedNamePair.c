/* @header
 * getJoinedNamePair  (originally func_80099480)
 * VRAM 0x80099480 | ROM 0x45BF0 | size 0xE8
 * asm: asm/nonmatchings/code_80090000/getJoinedNamePair.s
 */
#include "common.h"

extern u8 D_800C94CC[];
u8 *func_80028B5C(u8 *, u8 *);
#ifdef TARGET_PC
/* PC: func_80028D18 finds or claims the name buffer of D_8007FC3C (common.h's Nw2KeyedBufferEntry) for two keys, here
 * the addresses of the two names, so the keys must be as wide as a pointer; the N64 compares them as 32-bit words.
 * This is the declaration func_80028D18's PC definition must have (its keys uintptr_t, and Nw2KeyedBufferEntry's
 * key0 and key1 with them); its definition still takes s32 keys. */
u8 *func_80028D18(uintptr_t, uintptr_t);
#else
u8 *func_80028D18(s32, s32);
#endif

/* Build the text "A & B" from two names: if arg0 is empty return the default string; otherwise
 * look it up in the text cache via func_80028D18 and, when the result is empty, append arg0, the
 * fixed 5-byte separator from D_800C94CC+0x1EC..0x1F0, and arg1,
 * NUL-terminated. Returns the lookup result (or the default). */
u8 *getJoinedNamePair(u8 *arg0, u8 *arg1) {
    u8 *r;
    u8 *p;

    if (*arg0 == 0) {
        return D_800C94CC + 0x64;
    }
#ifdef TARGET_PC
    r = func_80028D18((uintptr_t)arg0, (uintptr_t)arg1); /* PC: the names' addresses as the keys, as above */
#else
    r = func_80028D18(arg0, arg1);
#endif
    if (r == NULL) {
        return D_800C94CC + 0x64;
    }
    if (*r == 0) {
        p = func_80028B5C(r, arg0);
        if (*arg1 != 0) {
            *p++ = D_800C94CC[0x1EC];
            *p++ = D_800C94CC[0x1ED];
            *p++ = D_800C94CC[0x1EE];
            *p++ = D_800C94CC[0x1EF];
            *p++ = D_800C94CC[0x1F0];
            p = func_80028B5C(p, arg1);
        }
        *p = 0;
    }
    return r;
}
