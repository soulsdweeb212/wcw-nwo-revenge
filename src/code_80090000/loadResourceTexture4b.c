#include "common.h"

/* Emits the RDP setup for a 4-bit (CI4) texture and returns -1 on success
 * (0 when the texture resource is missing).
 * arg0 = display-list cursor, arg1 = texture info (fA base tile id, fD/fE the
 * log2 width/height), arg2 = tile index offset. The tile id arg1->fA+arg2 is
 * looked up through resource 0x3B (func_800B600C/func_800B64EC).
 * The emitted words set the texture image (0xFD), tile descriptor (0xF5,
 * indexed by the tile id), the two tile-size fields (0xF3/0xF2) derived from
 * W=2^fD, H=2^fE, and the 0xE6/0xE7 no-op pair. */
typedef union { struct { u32 w0, w1; } words; u64 align; } G912;
typedef struct { u8 p0[10]; u16 fA; u8 fC, fD, fE; } T912;
s32 func_800B600C(s32, s32);
s32 func_800B64EC(s32, s32);
#define C(a, b) { G912 *g = dl++; g->words.w0 = (a); g->words.w1 = (b); }
#define W (1 << arg1->fD)
#define H (1 << arg1->fE)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

s32 loadResourceTexture4b(G912 **arg0, T912 *arg1, s32 arg2) {
    G912 *dl = *arg0;
    s32 texIdx = arg1->fA + arg2;
    s32 res = func_800B600C(0x3B, 0);
    s32 tex;
    if (res == 0)
        tex = 0;
    else
        tex = func_800B64EC(res, texIdx);
    if (!tex)
        return 0;
    C(0xFD500000, tex - 0x80000000);
    C(0xF5500000, 0x07000000 | ((arg1->fE & 15) << 14) | ((arg1->fD & 15) << 4));
    C(0xE6000000, 0);
    C(0xF3000000, 0x07000000 | ((MIN(((W * H + 3) >> 2) - 1, 2047) & 0xFFF) << 12) | ((((2048 + MAX(1, W / 16) - 1) / MAX(1, W / 16))) & 0xFFF));
    C(0xE7000000, 0);
    C(0xF5400000 | (((((W >> 1) + 7) >> 3) & 0x1FF) << 9), ((arg1->fE & 15) << 14) | ((arg1->fD & 15) << 4));
    C(0xF2000000, ((((W - 1) << 2) & 0xFFF) << 12) | (((H - 1) << 2) & 0xFFF));
    *arg0 = dl;
    return -1;
}
