/* @header
 * func_800A700C
 * VRAM 0x800A700C | ROM 0x9A4AC | size 0x120
 * asm: asm/nonmatchings/code_8009D7A0/func_800A700C.s
 */
#include "common.h"

/* Unlinks the wrestler w from the attached[] slots of each of the four
 * records: any slot holding its id is cleared to -1 and that record's
 * WR_FLAG_PAIR_LEADER is dropped. */
void func_800A700C(Wrestler *w) {
    s16 i = 0;
    for (; i < 4; i++) {
        if (D_800F9D10[i].characterId != -1) {
            if (D_800F9D10[i].attached[0] == w->id) {
                D_800F9D10[i].attached[0] = -1;
                D_800F9D10[i].flags &= ~WR_FLAG_PAIR_LEADER;
            }
            if (D_800F9D10[i].attached[1] == w->id) {
                D_800F9D10[i].attached[1] = -1;
                D_800F9D10[i].flags &= ~WR_FLAG_PAIR_LEADER;
            }
        }
    }
}
