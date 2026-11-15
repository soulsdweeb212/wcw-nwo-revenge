/* @header
 * func_800B0408
 * VRAM 0x800B0408 | ROM 0x5CB78 | size 0xB4
 * asm: asm/nonmatchings/code_80090000/func_800B0408.s
 */
#include "common.h"

extern u8 D_8007EF30[];
#ifdef TARGET_PC
/* PC: D_800E8724 is D_800E8230[4].el, and e's offsets are the flags fA (+0xA) and y (+4) of its elements 3 and 4
 * (0x148 bytes each on the N64). The menus and their elements hold addresses, so they are common.h's Nw2Menu and
 * Nw2MenuEl on PC, read by field name: the label has no PC symbol. */
extern Nw2Menu D_800E8230[];
#else
extern u8 *D_800E8724;
#endif
extern f64 D_800D66D8, D_800D66E0;

#ifdef TARGET_PC
void func_800B0408(void) { /* PC: by name (see above) */
    Nw2MenuEl *e = D_800E8230[4].el;
    s32 n = 3;
    f64 x;
    if (D_8007EF30[0x14D] & 1) {
        e[3].fA &= ~1;
        e[3].y = 65.0f;
        n = 4;
    } else {
        e[3].fA |= 1;
    }
    e = D_800E8230[4].el;
    if (D_8007EF30[0x14D] & 2) {
        x = (n - D_800D66D8) * D_800D66E0;
        e[4].fA &= ~1;
        e[4].y = x;
    } else {
        e[4].fA |= 1;
    }
}
#else
void func_800B0408(void) {
    u8 *e = D_800E8724;
    s32 n = 3;
    f64 x;
    if (D_8007EF30[0x14D] & 1) {
        *(u16 *)(e + 0x3E2) &= ~1;
        *(f32 *)(e + 0x3DC) = 65.0f;
        n = 4;
    } else {
        *(u16 *)(e + 0x3E2) |= 1;
    }
    e = D_800E8724;
    if (D_8007EF30[0x14D] & 2) {
        x = (n - D_800D66D8) * D_800D66E0;
        *(u16 *)(e + 0x52A) &= ~1;
        *(f32 *)(e + 0x524) = x;
    } else {
        *(u16 *)(e + 0x52A) |= 1;
    }
}
#endif
