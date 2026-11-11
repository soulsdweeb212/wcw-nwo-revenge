/* @header
 * func_800DECAC
 * VRAM 0x800DECAC | ROM 0xD214C | size 0x23C
 * asm: asm/nonmatchings/code_800DE9C0/func_800DECAC.s
 */
#include "common.h"

extern u16 D_800F98D0[];
s32 func_800D65D0(void *, s32);
s32 func_800DEEE8(void *, s32);

/* arg3 == 0: only zeroes D_800F98D0[w->id] (the slot's counter). arg3 == 1, w WR_FLAG_ON_APRON: side =
 * func_800D65D0(w, arg2) (1 when D_800E3F84[ringSide] & arg2, else 2 when D_800E3F8C[ringSide] & arg2, else 0).
 * If side is 0 or the low 16 bits of arg1 & arg2 are 0 the counter is zeroed; else, while func_800DEEE8(w, arg2)
 * is nonzero, the counter counts up and from 13 on the side index is ringSide (minus 1, & 3, when side == 1). Unless a present wrestler is already in state 2 with that
 * dirIndex, flag 0x8000000000 is set to (side == 1), dirIndex = that index, state 2 starts and 1 is returned. */
#ifdef TARGET_PC
/* PC: the function returns an s32 (1 when state 2 starts, else 0), whose low byte func_8009DD60 tests; its other
 * callers drop it. The N64 file gives this body a second, void name with an alias between two function types, which
 * GCC warns about (-Wattribute-alias) and macOS does not support. On PC the body is func_800DECAC itself, and
 * port_decls.h declares it returning s32. */
s32 func_800DECAC(Wrestler *w, s32 arg1, s32 arg2, s32 arg3) {
#else
static s32 func_800DECAC_impl(Wrestler *w, s32 arg1, s32 arg2, s32 arg3) {
#endif
    u8 id = w->id;
    s32 s3 = (s16)arg3;
    u16 a2 = arg2;
    s32 s7;
    s16 i;
    s16 a2v;

    if (s3 == 0) {
        D_800F98D0[(s8)id] = 0;
        return 0;
    }
    if (s3 != 1) return 0;
    if (!(w->flags & WR_FLAG_ON_APRON)) return 0;
    s7 = func_800D65D0(w, a2);
    if ((s16)s7 == 0) goto clear;
    if (((arg1 & arg2) & 0xFFFF) == 0) goto clear;
    if ((s8)func_800DEEE8(w, a2) == 0) return 0;
    if ((s16)++D_800F98D0[(s8)id] < 13) return 0;
    a2v = (u16)w->ringSide;
    if ((s16)s7 == s3) a2v = (a2v - 1) & 3;
    for (i = 0; i < 4; i++) {
        if (D_800F9D10[i].characterId != -1 && D_800F9D10[i].state == 2 && D_800F9D10[i].dirIndex == a2v) break;
    }
    if (i != 4) return 0;
    w->flags &= ~0x8000000000ULL;
    if ((s16)s7 == 1) w->flags |= 0x8000000000ULL;
    w->dirIndex = a2v;
    func_800A6C48(w, 2);
    return 1;
clear:
    D_800F98D0[(s8)id] = 0;
    return 0;
}

#ifndef TARGET_PC /* on PC the body above is func_800DECAC itself */
void func_800DECAC(Wrestler *, s32, s32, s32) __attribute__((alias("func_800DECAC_impl")));
#endif
