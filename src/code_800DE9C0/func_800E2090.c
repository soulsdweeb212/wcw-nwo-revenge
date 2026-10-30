/* @header
 * func_800E2090
 * VRAM 0x800E2090 | ROM 0xD5530 | size 0x9C
 * asm: asm/nonmatchings/code_800DE9C0/func_800E2090.s
 */
#include "common.h"

extern s8 D_800F99A0[];
extern u8 D_800F98E2[];

/* Move the paired-entity link from `src` to `dst`: the slot id currently held
 * for the source is re-pointed at the destination (D_800F99A0 table and the
 * reverse D_800F98E2[slot*0x30] entry), and the link-flag bits
 * 0x3000000000000 in the +0x20 u64 are moved from src to dst. */
void func_800E2090(s8 *dst, s8 *src) {
    s8 id;

    id = D_800F99A0[src[0]];
    D_800F99A0[dst[0]] = id;
    D_800F98E2[id * 0x30] = dst[0];
    *(u64 *)(dst + 0x20) |= *(u64 *)(src + 0x20) & 0x3000000000000LL;
    *(u64 *)(src + 0x20) &= ~0x3000000000000LL;
}
