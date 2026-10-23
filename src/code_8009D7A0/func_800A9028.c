#include "common.h"

extern u8 D_800F9D1A[], D_800F9D3C[];

/* Return the state-derived action mask for entity index arg0 (record stride 0x3B0):
 * state 0x58 -> 4, state 0x3E -> 2, state 0x49 -> 1 only when the entity word at
 * D_800F9D3C has bit 1 set, state 7 -> 0x10 only when the entity u64 flags at
 * D_800F9D30 contain 0x10000000000; otherwise 0. */
s32 func_800A9028(s16 arg0) {
    s32 off = arg0 * 0x3B0;
    s16 state = *(s16 *)(D_800F9D1A + off);
    s32 result = 0;

    switch (state) {
    case 0x58: result = 4; break;
    case 0x49: if (*(u32 *)(D_800F9D3C + off) & 2) result = 1; break;
    case 0x3E: result = 2; break;
    case 7: if (*(u64 *)(D_800F9D30 + off) & 0x10000000000ULL) result = 0x10; break;
    }
    return result;
}
