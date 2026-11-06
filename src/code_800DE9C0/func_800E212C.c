/* @header
 * func_800E212C
 * VRAM 0x800E212C | ROM 0xD55CC | size 0x104
 * asm: asm/nonmatchings/code_800DE9C0/func_800E212C.s
 */
#include "common.h"

/* Detach a wrestler from its model part. When w->flags holds bit
 * 0x1000000000000, its 0x3000000000000 bits are cleared, the part slot is found
 * through D_800F99A0[w->id], and that part record (stride 0x30) is reset:
 * D_800F98E2 is marked -1 (unbound), func_80012364 is notified with the part's
 * D_800F98E1/D_800F98E4 fields, and bit 1 (or bits 1|8 when the wrestler is
 * WR_FLAG_IN_RING) is ORed into the part's D_800F98E3 state byte. */
s32 func_80012364(s8, s32, s8, void *);
extern s8 D_800F99A0[];
extern u8 D_800F98E1[];
extern s8 D_800F98E2[];
extern u8 D_800F98E3[];
extern u8 D_800F98E4[];

void func_800E212C(Wrestler *w) {
    s8 idx;
    s32 off;
    u8 v;
    s8 id;
    if (w->flags & 0x1000000000000ULL) {
        w->flags &= ~0x3000000000000ULL;
        id = w->id;
        idx = D_800F99A0[id];
        off = idx * 0x30;
        D_800F98E2[off] = -1;
        func_80012364(idx, -1, D_800F98E1[off], &D_800F98E4[off]);
        v = D_800F98E3[off];
        D_800F98E3[off] = v | 1;
        if (w->flags & WR_FLAG_IN_RING)
            D_800F98E3[off] = v | 9;
    }
}
