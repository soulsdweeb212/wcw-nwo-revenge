#include "common.h"

extern u16 D_800F98D8[];
void func_800D427C(void *, s16, s32);

/* Start a character's animation: for a few character ids (D_800F98D8[arg0[0]]
 * in 0xF2D..0xF2F) substitute animation commands 0xF30..0xF32, otherwise use a2;
 * then set the character's per-tick step from the remaining heading distance
 * over the frame count at +0x36C. */
void func_800E1560(u8 *arg0, void *arg1, s32 a2) {
    s32 idx;

    idx = (s16)(D_800F98D8[(s8)arg0[0]] - 0xF2D);
    if ((u32)idx < 18) {
        switch (idx) {
        case 0: a2 = 0xF30; break;
        case 1: a2 = 0xF31; break;
        case 2: a2 = 0xF32; break;
        case 3: case 4: case 5: case 6: case 7:
        case 8: case 9: case 10: case 11: case 12:
        case 13: case 14: case 15: case 16: case 17:
        default:
            break;
        }
    }
    func_800D427C(arg0, (s16)a2, 1);
    *(s32 *)(arg0 + 0x348) = func_800D3684((s32)arg1, *(s32 *)(arg0 + 0x58)) / (u8)arg0[0x36C];
}
