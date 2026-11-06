/* @header
 * func_800B6DEC
 * VRAM 0x800B6DEC | ROM 0xAA28C | size 0x40C
 * asm: asm/nonmatchings/code_8009D7A0/func_800B6DEC.s
 */
#include "common.h"

extern s16 D_800FAF50[];
extern s16 D_800FADD2[];
extern s8 D_800FACE8;
extern s8 D_8007EF2C;
extern u16 D_8007E280;
extern f64 D_800E55E8;
extern f64 D_800E55F0;

s32 func_800BF2FC(Wrestler *);

/* Timer value for w by type (the callers store it in escapeTimer or stateTimer); never below 0. Types 0, 2, 4, 5 and
 * 6 give 0 while w has WR_FLAG_SPECIAL (type 3 gives 60).
 * 0: 180 + 3 * D_800FAF50[id] (set by func_800BF338 to the size of a health change) - (health + spirit) / 2
 *    - 80 * knockdowns, scaled by D_800E55E8 (1.5) on the floor when D_8007E280 bit 0x200 is set and by
 *    D_800E55F0 (0.65) on the apron.
 * 1: 110 + other->spirit / 4 + 3 * D_800FADD2[id] - func_800BF2FC(w) - spirit / 2; 87 when that and spirit are
 *    both >= 90.
 * 2: 100 - (spirit / 2 + health / 4).
 * 4: 180 - (spirit / 2 + health / 4); 0 when D_8007EF2C is set and D_800FACE8 < 6.
 * 3, 5, 6: (300 + other->spirit / 2 - (health + spirit / 4)) / 2. */
s16 func_800B6DEC(Wrestler *w, Wrestler *other, s16 type) {
    u16 v[3];
    s16 r;
    s16 x;

    switch (type) {
    case 0:
        r = 0;
        if (w->flags & WR_FLAG_SPECIAL) {
            break;
        }
        v[0] = 180 + D_800FAF50[w->id] * 3;
        v[1] = (w->health + w->spirit) / 2;
        v[2] = w->knockdowns * 80;
        x = v[0] - v[1] - v[2];
        r = x;
        if ((D_8007E280 & 0x200) && (w->flags & WR_FLAG_ON_FLOOR)) {
            r = x * D_800E55E8;
        }
        if (w->flags & WR_FLAG_ON_APRON) {
            r = r * D_800E55F0;
        }
        break;
    case 1:
        v[0] = 110 + other->spirit / 4;
        v[1] = D_800FADD2[w->id] * 3;
        v[2] = func_800BF2FC(w) + w->spirit / 2;
        x = v[0] + v[1] - v[2];
        r = x;
        if (x >= 90 && w->spirit >= 90) {
            r = 87;
        }
        break;
    case 2:
        r = 0;
        if (w->flags & WR_FLAG_SPECIAL) {
            break;
        }
        r = 100 - (w->spirit / 2 + w->health / 4);
        break;
    case 3:
        if (w->flags & WR_FLAG_SPECIAL) {
            r = 60;
            break;
        }
        r = 60;
        goto tail;
    case 4:
        r = 0;
        if (w->flags & WR_FLAG_SPECIAL) {
            break;
        }
        x = 180 - (w->spirit / 2 + w->health / 4);
        r = x;
        if (D_8007EF2C != 0) {
            r = (D_800FACE8 >= 6) ? x : 0;
        }
        break;
    case 5:
        if (w->flags & WR_FLAG_SPECIAL) {
            r = 0;
            break;
        }
        r = 0;
        goto tail;
    case 6:
        r = 0;
        if (w->flags & WR_FLAG_SPECIAL) {
            break;
        }
tail:
        v[0] = 300 + other->spirit / 2;
        v[1] = w->health + w->spirit / 4;
        r = ((s16)v[0] - (s16)v[1]) / 2;
        break;
    }
    return (r < 0) ? 0 : r;
}
