/* @header
 * func_800B0654
 * VRAM 0x800B0654 | ROM 0x5CDC4 | size 0x120
 * asm: asm/nonmatchings/code_80090000/func_800B0654.s
 */
#include "common.h"

typedef struct { u8 id; u8 pad1[5]; u16 flags; u8 pad8[8]; u8 *list; } Cup;
typedef struct { s16 f0; s16 id; u8 pad4[0xC]; } Pl;
typedef struct {
    u8 pad0[8];
    u16 mode;
    u8 padA[0x26];
    Cup *cup;
    u8 pad34[0x18];
    Pl pl[4];
    u8 pad8C[0x14E - 0x8C];
    u16 f14E[5];
    u16 f158;
    u16 f15A[5];
    u16 f164;
    u8 pad166[0xC90 - 0x166];
    u16 opp[18];
} Game;

extern Game D_8007EF30;

/* -1 if `id` is this cup's f14E entry, 1 if it is f158 in cup 2, else 0 (always 0 outside mode 0x8000).
   Same body as the standalone func_800B04BC, with early returns. */
static inline s32 isCupBoss(s32 id) {
    u8 k;
    if (!(D_8007EF30.mode & 0x8000)) {
        return 0;
    }
    k = D_8007EF30.cup->id;
    if ((D_8007EF30.f14E[k] & 0xFFF) == id) {
        return -1;
    }
    if (k == 2 && (D_8007EF30.f158 & 0xFFF) == id) {
        return 1;
    }
    return 0;
}

/* The values are read before either store, as arguments. */
static inline void setLastPair(s32 a, s32 b) {
    D_8007EF30.opp[16] = a;
    D_8007EF30.opp[17] = b;
}


void func_800B0654(void) {
    s32 a;
    u16 v;
    s32 r;

    r = isCupBoss(D_8007EF30.pl[0].id);
    /* Each arm has its own compare; jump2 merges the identical tails, so the id is a temporary
       local to each arm and `a` ends up in a0. */
    if (r != 0) {
        a = D_8007EF30.f15A[D_8007EF30.cup->id] & 0xFFF;
        if (a == D_8007EF30.pl[1].id) {
            a = D_8007EF30.f164;
        }
    } else {
        a = D_8007EF30.f15A[D_8007EF30.cup->id] & 0xFFF;
        if (a == D_8007EF30.pl[0].id) {
            a = D_8007EF30.f164;
        }
    }
    if (r < 0) {
        v = D_8007EF30.f158;
    } else {
        v = D_8007EF30.f14E[D_8007EF30.cup->id];
    }
    setLastPair(a, v);
}
