/* @header
 * func_800DA8D0
 * VRAM 0x800DA8D0 | ROM 0xCDD70 | size 0xF0
 * asm: asm/nonmatchings/code_800BBA00/func_800DA8D0.s
 */
#include "common.h"

extern s16 D_800F9D12[][0x1D8];
extern s8 D_800FA063[][0x3B0];
extern s16 D_800F9D1A[][0x1D8];
extern u16 D_800F9D1C[][0x1D8];
extern u8 D_800F9D44[][0x3B0];

s32 func_800DA8D0(s8 *arg0) {
    s16 i;
    for (i = 0; i < 4; i++) {
        if (D_800F9D12[i][0] == -1) continue;
        if (D_800FA063[i][0] != *arg0) continue;
        if (D_800F9D1A[i][0] >= 0x6E) continue;
        if (D_800F9D1A[i][0] < 0x6B) continue;
        if ((D_800F9D44[i][0] & 2) == 0) continue;
        if ((u32)(D_800F9D1C[i][0] - 2) >= 2) continue;
        if (D_800F9D44[i][0] & 1) continue;
        D_800F9D44[i][0] |= 0x10;
        return 1;
    }
    return 0;
}
