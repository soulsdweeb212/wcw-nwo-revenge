/* @header
 * func_800A837C
 * VRAM 0x800A837C | ROM 0x9B81C | size 0x60
 * asm: asm/nonmatchings/code_8009D7A0/func_800A837C.s
 */
#include "common.h"

extern u8 D_8007EF30[];
void func_800DECAC(void *, s32, s32, s32);

/* Bump the per-entity/per-animation usage counter unless the entity is already in
 * state 0x57 (the special "no counter" state). */
void func_800A837C(u8 *entity) {
    s16 t = *(s16 *)(entity + 0x388);
    s32 idx;

    if (t != 0x57) {
        idx = (*(s8 *)entity * 0x57 + t) * 8;
        if (*(u32 *)(D_8007EF30 + 0x1B4 + idx) < 0xFFFFFFFFU) {
            *(u32 *)(D_8007EF30 + 0x1B4 + idx) += 1;
        }
    }
}
