/* @header
 * func_800B5F24
 * VRAM 0x800B5F24 | ROM 0xA93C4 | size 0x1A4
 * asm: asm/nonmatchings/code_8009D7A0/func_800B5F24.s
 */
#include "common.h"

extern f32 D_800E3C50[];
extern f32 D_800E3C54[];
extern f64 D_800E54F8;
extern f64 D_800E5500;

f32 func_800D3890(void *, void *, s32);
s8 func_800B71F8(Wrestler *, s32, s32);

/* Called by func_800B5730 when w->moveMode & 0x20 (running), with other = w's opponent and arg2 = D_800FAF8A.
 * Only for a wrestler that is WR_FLAG_IN_RING and has neither flags bit 0x1 nor 0x8. f = XZ distance
 * (func_800D3890) from w's pelvis (jointA[1]) to the rope corner dirIndex (D_800E3C50/54[dirIndex * 2]: 0 (230,230),
 * 1 (230,-230), 2 (-230,-230), 3 (-230,230)). When w has WR_FLAG_SPECIAL or other does not, the moveMode word
 * (moveMode + unk02A) & 0x8880000 is 0x80000, arg2 & 0xC030 is set and D_800E54F8 <= f <= D_800E5500 (about 75.3
 * to 175.3), it ORs a bit into moveMode: 0x800, or 0x1000 when func_800B71F8(w, 0, 3) is nonzero (0x2000 if also
 * arg2 & 0x8000). Always returns 0. */
s32 func_800B5F24(Wrestler *w, Wrestler *other, u16 arg2) {
    f32 sp10[4];
    f32 f;
    s32 bits;
    u64 fl;

    fl = w->flags;
    if (!(fl & WR_FLAG_IN_RING)) {
        return 0;
    }
    if (fl & 0x9ULL) {
        return 0;
    }
    sp10[0] = D_800E3C50[w->dirIndex * 2];
    sp10[2] = D_800E3C54[w->dirIndex * 2];
    f = func_800D3890(&w->jointA[1], sp10, 0);
    if (w->moveMode & 0x20) {
        if ((w->flags & WR_FLAG_SPECIAL) || !(other->flags & WR_FLAG_SPECIAL)) {
#ifdef TARGET_PC
            /* PC: the N64 code reads moveMode and the u16 after it as one big-endian u32, so bits 0x8880000 are moveMode's
             * bits 0x888. A little-endian PC would test the u16 instead, so the PC tests moveMode. */
            if ((w->moveMode & 0x888) != 0x8) {
#else
            if ((*(u32 *)&w->moveMode & 0x8880000) != 0x80000) {
#endif
                return 0;
            }
            if (!(arg2 & 0xC030)) {
                return 0;
            }
            if (D_800E54F8 <= f) {
                if (f <= D_800E5500) {
                    bits = 0x800;
                    if (func_800B71F8(w, 0, 3)) {
                        bits = 0x1000;
                        if (arg2 & 0x8000) {
                            bits = 0x2000;
                        }
                    }
                    w->moveMode |= bits;
                }
            } else {
                return 0;
            }
        }
    }
    return 0;
}
