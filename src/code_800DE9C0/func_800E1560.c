/* @header
 * func_800E1560
 * VRAM 0x800E1560 | ROM 0xD4A00 | size 0xD4
 * asm: asm/nonmatchings/code_800DE9C0/func_800E1560.s
 */
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
        case 0: case 6: case 14: case 15: case 16: case 17: a2 = 0xF30; break;
        case 1: case 7: a2 = 0xF31; break;
        case 2: case 8: a2 = 0xF32; break;
        default:
            break;
        }
    }
    func_800D427C(arg0, (s16)a2, 1);
    *(s32 *)(arg0 + 0x348) = func_800D3684((s32)arg1, *(s32 *)(arg0 + 0x58)) / (u8)arg0[0x36C];
}
