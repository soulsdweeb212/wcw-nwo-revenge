/* @header
 * updateEntityStunTimer  (originally func_800BF700)
 * VRAM 0x800BF700 | ROM 0xB2BA0 | size 0x420
 * asm: asm/nonmatchings/code_800BBA00/updateEntityStunTimer.s
 */
#include "common.h"

/* Per-wrestler spirit timers, indexed by w->id: D_800EB498 (spirit drift, 0x78 ticks), D_800EB4A0
 * (WR_FLAG_SPIRIT_EMPTY, 0x12C), D_800EB4A8 (WR_FLAG_SPIRIT_FULL, 0x258), D_800EB4B0 (WR_FLAG_SPECIAL, 0x258).
 * mode 0 reloads all four. mode 1 (other = the opponent): unless one of the three spirit flags is set, reloads the
 * flag timers and counts the drift timer down; when it runs out it is reloaded and w->spirit moves one step: -8 (to
 * at least 1) when w is on the floor and other is not, otherwise toward 50 (-1 above 50, +2 from 31..49, +3 below
 * 31). mode 2 counts down the timer of each spirit flag that is set; on expiry the flag is cleared and spirit set to
 * 70 (SPIRIT_FULL) or 50 (SPECIAL, SPIRIT_EMPTY). mode 3 takes 60 ticks off the SPIRIT_FULL and SPECIAL timers.
 * mode 4 returns the SPECIAL timer. Other modes and modes 0..3 return 0. */
extern u16 D_800EB498[];
extern u16 D_800EB4A0[];
extern u16 D_800EB4A8[];
extern u16 D_800EB4B0[];

s32 updateEntityStunTimer(Wrestler *w, Wrestler *other, s16 mode) {
    u8 id;
    s16 v;
    s16 h;

    id = w->id;
    switch (mode) {
    case 0:
        D_800EB498[(s8)id] = 0x78;
        D_800EB4A0[(s8)id] = 0x12C;
        D_800EB4A8[(s8)id] = 0x258;
        D_800EB4B0[(s8)id] = 0x258;
        return 0;
    case 1:
        if (w->flags & (WR_FLAG_SPIRIT_EMPTY | WR_FLAG_SPIRIT_FULL | WR_FLAG_SPECIAL)) {
            return 0;
        }
        D_800EB4A0[(s8)id] = 0x12C;
        D_800EB4A8[(s8)id] = 0x258;
        D_800EB4B0[(s8)id] = 0x258;
        if ((s16)--D_800EB498[(s8)id] > 0) {
            return 0;
        }
        D_800EB498[(s8)id] = 0x78;
        if ((w->flags & WR_FLAG_ON_FLOOR) && !(other->flags & WR_FLAG_ON_FLOOR)) {
            v = w->spirit - 8;
            w->spirit = v;
            if (v > 0) {
                return 0;
            }
            v = 1;
        } else {
            h = w->spirit;
            if (h >= 0x33) {
                v = h - 1;
            } else {
                if (h == 0x32) {
                    return 0;
                }
                if (h < 0x1F) {
                    v = h + 3;
                } else {
                    v = h + 2;
                }
            }
        }
        w->spirit = v;
        return 0;
    case 2:
        if (w->flags & WR_FLAG_SPIRIT_FULL) {
            D_800EB4A0[(s8)id] = 0x12C;
            D_800EB4B0[(s8)id] = 0x258;
            if ((s16)--D_800EB4A8[(s8)id] <= 0) {
                w->spirit = 0x46;
                w->flags &= ~WR_FLAG_SPIRIT_FULL;
            }
        }
        if (w->flags & WR_FLAG_SPECIAL) {
            D_800EB4A0[(s8)id] = 0x12C;
            D_800EB4A8[(s8)id] = 0x258;
            if ((s16)--D_800EB4B0[(s8)id] <= 0) {
                w->spirit = 0x32;
                w->flags &= ~WR_FLAG_SPECIAL;
            }
        }
        if (w->flags & WR_FLAG_SPIRIT_EMPTY) {
            D_800EB4A8[(s8)id] = 0x258;
            D_800EB4B0[(s8)id] = 0x258;
            if ((s16)--D_800EB4A0[(s8)id] <= 0) {
                w->spirit = 0x32;
                w->flags &= ~WR_FLAG_SPIRIT_EMPTY;
            }
        }
        return 0;
    case 3:
        if (w->flags & WR_FLAG_SPIRIT_FULL) {
            D_800EB4A8[(s8)id] -= 0x3C;
        }
        if (w->flags & WR_FLAG_SPECIAL) {
            D_800EB4B0[(s8)id] -= 0x3C;
        }
        return 0;
    case 4:
        return (s16)D_800EB4B0[(s8)id];
    }
    return 0;
}
