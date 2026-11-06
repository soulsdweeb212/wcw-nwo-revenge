/* @header
 * func_800DEEE8
 * VRAM 0x800DEEE8 | ROM 0xD2388 | size 0x9C
 * asm: asm/nonmatchings/code_800DE9C0/func_800DEEE8.s
 */
#include "common.h"

extern s8 D_800F99A0[];
extern u8 D_800F98E2[];

s8 func_800D8DF0(Wrestler *);

/* Returns 1 when func_800D8DF0(w) is nonzero or w's ringSide is outside the
 * direction mask arg1 (bit 1 of w->id selects which two ringSide values map
 * to which mask bits: 0 -> 0x200, 1 -> 0x400 when set, 2 -> 0x100,
 * 3 -> 0x800 when clear). */
s32 func_800DEEE8(Wrestler *w, u32 arg1) {
    s32 mask;

    if (func_800D8DF0(w)) {
        return 1;
    }
    mask = 0;
    if (w->id & 2) {
        switch (w->ringSide) {
        case 0: mask = 0x200; break;
        case 1: mask = 0x400; break;
        }
    } else {
        switch (w->ringSide) {
        case 2: mask = 0x100; break;
        case 3: mask = 0x800; break;
        }
    }
    return (mask & arg1) == 0;
}
