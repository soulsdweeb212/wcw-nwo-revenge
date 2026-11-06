/* @header
 * func_800D7B54
 * VRAM 0x800D7B54 | ROM 0xCAFF4 | size 0x324
 * asm: asm/nonmatchings/code_800BBA00/func_800D7B54.s
 */
#include "common.h"

extern u16 D_800F9830[];
extern s16 D_800F9828[];
extern s8 func_800B71F8(Wrestler *, s32, s32);

/* Per-wrestler attack/hit bookkeeping: D_800F9830[id] is a u16 state bitmask and
 * D_800F9828[id] a hit counter.  Mode 0 clears bit0.  Mode 1 records an incoming
 * attack (attackMask) as a defender-response bit (0x10->8, 0x20->0x10, else 4)
 * with a counter, lets a matching attack (incomingMask) increment the counter,
 * clears the mask when no attack is incoming, sets bit0 ('defending'), and adds a
 * per-state bit from w->state (0x2D -> 0x20/0x40 by w->step == 1, 0x2E -> 0x100,
 * 0x2F -> 0x80).  Modes 2/3/4 mark the call ready (local `ready`, never returned)
 * when the matching defender bit (8/0x10/4) is set and the counter is under 3, so
 * modes 0 and 1 always return 0.  If w->flags has 0x1 or 0x8 set or it isn't ready
 * it returns 0; otherwise, while bit0 is set, it maps the state bit (0x20/0x40/0x80/
 * 0x100, the last set one wins) to a code (0xE/0xF/0x10/0x11) and returns 1 when the
 * random-chance roll func_800B71F8(w, 0, code) succeeds (code 0xE: odds from
 * w->escapeTimer; 0xF, 0x10, 0x11: fixed odds 700, 500, 600), else 0. */
s32 func_800D7B54(Wrestler *w, u16 incomingMask, u16 attackMask, s16 mode) {
    u16 bits;
    s16 actionCode;
    s32 ready = 0;

    switch (mode) {
    case 0:
        D_800F9830[w->id] &= 0xFFFE;
        break;
    case 1:
        if (attackMask & 0x8030) {
            D_800F9828[w->id] = 0;
            if (attackMask & 0x10) {
                bits = 8;
            } else if (attackMask & 0x20) {
                bits = 0x10;
            } else {
                bits = 4;
            }
            D_800F9830[w->id] = bits;
        }
        if (incomingMask & 0x8030) {
            if (((incomingMask & 0x10) && (D_800F9830[w->id] & 8)) ||
                ((incomingMask & 0x20) && (D_800F9830[w->id] & 0x10)) ||
                ((incomingMask & 0x8000) && (D_800F9830[w->id] & 4))) {
                D_800F9828[w->id]++;
            }
        } else {
            D_800F9830[w->id] = 0;
        }
        D_800F9830[w->id] |= 1;
        bits = 0;
        switch (w->state) {
        case 0x2D:
            bits = (w->step == 1) ? 0x20 : 0x40;
            break;
        case 0x2E:
            bits = 0x100;
            break;
        case 0x2F:
            bits = 0x80;
            break;
        }
        D_800F9830[w->id] |= bits;
        break;
    case 3:
        if (D_800F9830[w->id] & 0x10) {
            if (D_800F9828[w->id] < 3) {
                ready = 2;
            }
        }
        break;
    case 4:
        if (D_800F9830[w->id] & 0x4) {
            if (D_800F9828[w->id] < 3) {
                ready = 2;
            }
        }
        break;
    case 2:
        if (D_800F9830[w->id] & 0x8) {
            if (D_800F9828[w->id] < 3) {
                ready = 2;
            }
        }
        break;
    }

    if (w->flags & 0x9ULL) {
        return 0;
    }
    if (ready == 0) {
        return 0;
    }
    if (D_800F9830[w->id] & 1) {
        if (D_800F9830[w->id] & 0x20) actionCode = 0xE;
        if (D_800F9830[w->id] & 0x40) actionCode = 0xF;
        if (D_800F9830[w->id] & 0x80) actionCode = 0x10;
        if (D_800F9830[w->id] & 0x100) actionCode = 0x11;
        if (func_800B71F8(w, 0, actionCode)) {
            return 1;
        }
    }
    return 0;
}
