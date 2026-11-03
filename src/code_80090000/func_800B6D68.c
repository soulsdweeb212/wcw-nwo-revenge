/* @header
 * func_800B6D68
 * VRAM 0x800B6D68 | ROM 0x634D8 | size 0xB0
 * asm: asm/nonmatchings/code_80090000/func_800B6D68.s
 */
#include "common.h"

u8 *func_800B600C(s32, s32);
void func_800B6548(u32 **, s32, s32, s32, u8 *, u8 *);

u8 *func_800B6D68(u32 **dl, s32 a, s32 b, s32 d, s32 i, s32 j) {
    s32 id;
    u32 *g;
    u8 *v;
    u8 *w;

    /* Placeholder: keeps i in its stack slot so the early `id = i` load is
       not merged into the call's a0 setup (the ROM loads it before *dl). */
    (void)&i;
    id = i;
    g = *dl;
    v = func_800B600C(id, 0);
    if (v == 0) {
        return 0;
    }
    w = func_800B600C(j, 0);
    if (w) {
        func_800B6548(&g, a == 1, b, d, v, w);
        *dl = g;
        return v;
    }
    return 0;
}
