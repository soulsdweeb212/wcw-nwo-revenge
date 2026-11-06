/* @header
 * func_800BF338
 * VRAM 0x800BF338 | ROM 0xB27D8 | size 0x210
 * asm: asm/nonmatchings/code_800BBA00/func_800BF338.s
 */
#include "common.h"

extern u8 D_8007E228[];
extern u16 D_800E3AA0[];
extern u16 D_800E3AA4[];
extern u16 D_800FADD0;
extern u16 D_800FAF50[];
extern u16 D_800EB4B8[];
s8 func_800D4198(s16);

/* Add `amount` to w->health, clamped to w->healthMax. When health reaches zero
 * (clamped to 0), optionally arm the shared D_800FADD0 bits for slots 0/1
 * (w->id < 2, behind a random gate). `mode` then: 0 records |amount| in
 * D_800FAF50[w->id] (a negative amount also raises flag 0x1000000000000000 and
 * sets the D_800EB4B8[w->id] countdown to 30 ticks, see func_800BF26C), 1 does
 * nothing, 2 clears D_800FAF50[w->id]. */
void func_800BF338(Wrestler *w, s16 amount, s16 mode) {
    w->health += amount;
    if (w->health > w->healthMax) w->health = w->healthMax;

    if (w->health <= 0) {
        w->health = 0;
        if ((*(u16 *)(D_8007E228 + 0x58) & 0x100) && w->id < 2) {
            if (*(u16 *)(D_8007E228 + 0x58) & 0x1000) {
                if (!(D_800FADD0 & D_800E3AA4[w->id])) {
                    if (func_800D4198(0xFA)) {
                        D_800FADD0 |= D_800E3AA0[w->id];
                    }
                    D_800FADD0 |= D_800E3AA4[w->id];
                }
            } else {
                if (func_800D4198(0x1F4)) {
                    D_800FADD0 |= D_800E3AA0[w->id];
                }
            }
        }
    }
    switch ((s16)mode) {
    case 0: /* start countdown */
        D_800FAF50[w->id] = func_800D3550(amount);
        if (amount < 0) {
            w->flags |= 0x1000000000000000ULL;
            D_800EB4B8[w->id] = 0x1E;
        }
        break;
    case 1: /* leave as-is */
        break;
    case 2: /* clear */
        D_800FAF50[w->id] = 0;
        break;
    }
}
