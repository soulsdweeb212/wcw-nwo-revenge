/* @header
 * beginEntityActionA8D8C  (originally func_800A8D8C)
 * VRAM 0x800A8D8C | ROM 0x9C22C | size 0x29C
 * asm: asm/nonmatchings/code_8009D7A0/beginEntityActionA8D8C.s
 */
#include "common.h"

/* Starts (or restarts) a wrestler's action after an animation. It copies the
 * animation's end pose (anim.endPose) to pose and maps it to a new state, resets
 * step/stepFlags and pairSignals, applies the shared u64 flag reset
 * (clear 0x10810000000, set 0x1000000000), announces the transition via
 * func_800DECAC and, for the ordinary poses, also sets WR_FLAG_RERUN.
 * End zone 5 (anim.endZone) is handled first as a single special case. Down
 * poses 7..32 split into even (set flag 0x200000) and odd (clear flag 0x200000)
 * halves; unknown poses do nothing. */

void beginEntityActionA8D8C(Wrestler *w) {
    u8 v;
    if (w->anim.endZone == 5) {
        w->state = 0x14;
        w->step = 0;
        w->stepFlags = 0;
        w->pairSignals = 0;
        w->flags = (w->flags & 0xFFFFFEF7EFFFFFFFULL) | 0x1000000000ULL;
        func_800DECAC(w, 0, 0, 0);
        w->step = 2;
        return;
    }
    v = w->anim.endPose;
    w->pose = v;
    switch ((s8)v) {
    case 0:
    case 1:
        D_800FAF5C->flags |= 0x800000ULL << 32;
        w->state = 0x2B;
        w->step = 0;
        w->stepFlags = 0;
        w->pairSignals = 0;
        w->flags = (w->flags & 0xFFFFFEF7EFFFFFFFULL) | 0x1000000000ULL;
        func_800DECAC(w, 0, 0, 0);
        w->flags |= WR_FLAG_RERUN;
        break;
    case 2:
        w->state = 0x2E;
        w->step = 0;
        w->stepFlags = 0;
        w->pairSignals = 0;
        w->flags = (w->flags & 0xFFFFFEF7EFFFFFFFULL) | 0x1000000000ULL;
        func_800DECAC(w, 0, 0, 0);
        w->flags |= WR_FLAG_RERUN;
        break;
    case 3:
        w->state = 0x2D;
        w->step = 0;
        w->stepFlags = 0;
        w->pairSignals = 0;
        w->flags = (w->flags & 0xFFFFFEF7EFFFFFFFULL) | 0x1000000000ULL;
        func_800DECAC(w, 0, 0, 0);
        w->flags |= WR_FLAG_RERUN;
        break;
    case 4:
    case 5:
        w->state = 0x1;
        w->step = 0;
        w->stepFlags = 0;
        w->pairSignals = 0;
        w->flags = (w->flags & 0xFFFFFEF7EFFFFFFFULL) | 0x1000000000ULL;
        func_800DECAC(w, 0, 0, 0);
        w->flags |= WR_FLAG_RERUN;
        break;
    case 7: case 9: case 11: case 13: case 15:
    case 17: case 19: case 21: case 23: case 25:
    case 27: case 29: case 31:
        w->flags &= 0xFFFFFFFFFFDFFFFFULL;
        w->state = 0x2C;
        w->step = 0;
        w->stepFlags = 0;
        w->pairSignals = 0;
        w->flags = (w->flags & 0xFFFFFEF7EFFFFFFFULL) | 0x1000000000ULL;
        func_800DECAC(w, 0, 0, 0);
        w->flags |= WR_FLAG_RERUN;
        break;
    case 8: case 10: case 12: case 14: case 16:
    case 18: case 20: case 22: case 24: case 26:
    case 28: case 30: case 32:
        w->flags |= 0x200000ULL;
        w->state = 0x2C;
        w->step = 0;
        w->stepFlags = 0;
        w->pairSignals = 0;
        w->flags = (w->flags & 0xFFFFFEF7EFFFFFFFULL) | 0x1000000000ULL;
        func_800DECAC(w, 0, 0, 0);
        w->flags |= WR_FLAG_RERUN;
        break;
    default:
        return;
    }
}
