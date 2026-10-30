/* @header
 * func_800D7B54
 * VRAM 0x800D7B54 | ROM 0xCAFF4 | size 0x324
 * asm: asm/nonmatchings/code_800BBA00/func_800D7B54.s
 */
#include "common.h"

extern u16 D_800F9830[];
extern s16 D_800F9828[];
extern s8 func_800B71F8(void *, s32, s32);

typedef struct {
    s8 id;
    u8 pad1[9];
    s16 fA;
    s16 fC;
    u8 pad10[0x10];
    u64 flags;
} Nw2EntD7B54;

#define ENT ((Nw2EntD7B54 *)entity)

/* Per-entity attack/hit bookkeeping: D_800F9830[id] is a u16 state bitmask and
 * D_800F9828[id] a hit counter.  Mode 0 clears bit0.  Mode 1 records an incoming
 * attack (attackMask) as a defender-response bit (0x10->8, 0x20->0x10, else 4)
 * with a counter, lets a matching attack (incomingMask) increment the counter,
 * clears the mask when no attack is incoming, sets bit0 ('defending'), and adds a
 * per-state bit from fA (0x2D -> 0x20/0x40 by fC, 0x2E -> 0x100, 0x2F -> 0x80).
 * Modes 2/3/4 report ready-to-counter (returns 2) when the matching defender bit
 * is set and the counter is under 3.  If the entity has flags 9 or isn't ready it
 * returns 0; otherwise, while defending, it maps the response bit to an action
 * code (0xE/0xF/0x10/0x11) and asks func_800B71F8 to perform it. */
s32 func_800D7B54(void *entity, u16 incomingMask, u16 attackMask, s16 mode) {
    u16 bits;
    s16 actionCode;
    s32 ready = 0;

    switch (mode) {
    case 0:
        D_800F9830[ENT->id] &= 0xFFFE;
        break;
    case 1:
        if (attackMask & 0x8030) {
            D_800F9828[ENT->id] = 0;
            if (attackMask & 0x10) {
                bits = 8;
            } else if (attackMask & 0x20) {
                bits = 0x10;
            } else {
                bits = 4;
            }
            D_800F9830[ENT->id] = bits;
        }
        if (incomingMask & 0x8030) {
            if (((incomingMask & 0x10) && (D_800F9830[ENT->id] & 8)) ||
                ((incomingMask & 0x20) && (D_800F9830[ENT->id] & 0x10)) ||
                ((incomingMask & 0x8000) && (D_800F9830[ENT->id] & 4))) {
                D_800F9828[ENT->id]++;
            }
        } else {
            D_800F9830[ENT->id] = 0;
        }
        D_800F9830[ENT->id] |= 1;
        bits = 0;
        switch (ENT->fA) {
        case 0x2D:
            bits = (ENT->fC == 1) ? 0x20 : 0x40;
            break;
        case 0x2E:
            bits = 0x100;
            break;
        case 0x2F:
            bits = 0x80;
            break;
        }
        D_800F9830[ENT->id] |= bits;
        break;
    case 3:
        if (D_800F9830[ENT->id] & 0x10) {
            if (D_800F9828[ENT->id] < 3) {
                ready = 2;
            }
        }
        break;
    case 4:
        if (D_800F9830[ENT->id] & 0x4) {
            if (D_800F9828[ENT->id] < 3) {
                ready = 2;
            }
        }
        break;
    case 2:
        if (D_800F9830[ENT->id] & 0x8) {
            if (D_800F9828[ENT->id] < 3) {
                ready = 2;
            }
        }
        break;
    }

    if (ENT->flags & 0x9ULL) {
        return 0;
    }
    if (ready == 0) {
        return 0;
    }
    if (D_800F9830[ENT->id] & 1) {
        if (D_800F9830[ENT->id] & 0x20) actionCode = 0xE;
        if (D_800F9830[ENT->id] & 0x40) actionCode = 0xF;
        if (D_800F9830[ENT->id] & 0x80) actionCode = 0x10;
        if (D_800F9830[ENT->id] & 0x100) actionCode = 0x11;
        if (func_800B71F8(entity, 0, actionCode)) {
            return 1;
        }
    }
    return 0;
}
