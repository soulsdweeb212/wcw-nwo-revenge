/* @header
 * lookupPlayerNameById  (originally func_80099480)
 * VRAM 0x80099480 | ROM 0x45BF0 | size 0xE8
 * asm: asm/nonmatchings/code_80090000/lookupPlayerNameById.s
 */
#include "common.h"

extern u8 D_800C94CC[];
u8 *func_80028B5C(u8 *, u8 *);
u8 *func_80028D18(s32, s32);

/* Build a name string: if arg0 is empty return the default string; otherwise
 * look it up via func_80028D18 and, when the result is empty, append arg0, the
 * fixed 5-byte separator from D_800C94CC+0x1EC..0x1F0, and arg1,
 * NUL-terminated. Returns the lookup result (or the default). */
u8 *lookupPlayerNameById(u8 *arg0, u8 *arg1) {
    u8 *r;
    u8 *p;

    if (*arg0 == 0) {
        return D_800C94CC + 0x64;
    }
    r = func_80028D18(arg0, arg1);
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
