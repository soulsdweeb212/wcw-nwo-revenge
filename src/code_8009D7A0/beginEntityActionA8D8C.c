/* @header
 * beginEntityActionA8D8C  (originally func_800A8D8C)
 * VRAM 0x800A8D8C | ROM 0x9C22C | size 0x29C
 * asm: asm/nonmatchings/code_8009D7A0/func_800A8D8C.s
 */
#include "common.h"

/* Starts (or restarts) an entity's action. It maps the entity's mode
 * (+0x36F) to an action id written to +0x0A, resets the action state
 * (+0x0C/+0x0E) and +0x360, applies the shared u64 flag reset
 * (clear 0x10810000000, set 0x1000000000), announces the transition via
 * func_800DECAC and, for the ordinary modes, also sets flag 0x10000000.
 * Mode 5 at +0x36E is handled first as a single special case. Modes 7..31
 * split into even (set flag 0x200000) and odd (clear flag 0x200000) halves;
 * unknown modes do nothing. */
typedef struct {
    u8 pad0[0xA];
    s16 action;       /* +0x0A */
    s16 state;        /* +0x0C */
    s16 subState;     /* +0x0E */
    u8 pad10[0x10];
    u64 flags;        /* +0x20 */
    u8 pad28[0x1A];
    u8 savedMode;     /* +0x42 */
    u8 pad43[0x31D];
    u16 actionFlags;  /* +0x360 */
    u8 pad362[0xC];
    u8 specialMode;   /* +0x36E */
    u8 mode;          /* +0x36F */
} Nw2Entity;

extern Nw2Entity *D_800FAF5C;

void beginEntityActionA8D8C(Nw2Entity *s0) {
    u8 v;
    if (s0->specialMode == 5) {
        s0->action = 0x14;
        s0->state = 0;
        s0->subState = 0;
        s0->actionFlags = 0;
        s0->flags = (s0->flags & 0xFFFFFEF7EFFFFFFFULL) | 0x1000000000ULL;
        func_800DECAC(s0, 0, 0, 0);
        s0->state = 2;
        return;
    }
    v = s0->mode;
    s0->savedMode = v;
    switch ((s8)v) {
    case 0:
    case 1:
        D_800FAF5C->flags |= 0x800000ULL << 32;
        s0->action = 0x2B;
        s0->state = 0;
        s0->subState = 0;
        s0->actionFlags = 0;
        s0->flags = (s0->flags & 0xFFFFFEF7EFFFFFFFULL) | 0x1000000000ULL;
        func_800DECAC(s0, 0, 0, 0);
        s0->flags |= 0x10000000ULL;
        break;
    case 2:
        s0->action = 0x2E;
        s0->state = 0;
        s0->subState = 0;
        s0->actionFlags = 0;
        s0->flags = (s0->flags & 0xFFFFFEF7EFFFFFFFULL) | 0x1000000000ULL;
        func_800DECAC(s0, 0, 0, 0);
        s0->flags |= 0x10000000ULL;
        break;
    case 3:
        s0->action = 0x2D;
        s0->state = 0;
        s0->subState = 0;
        s0->actionFlags = 0;
        s0->flags = (s0->flags & 0xFFFFFEF7EFFFFFFFULL) | 0x1000000000ULL;
        func_800DECAC(s0, 0, 0, 0);
        s0->flags |= 0x10000000ULL;
        break;
    case 4:
    case 5:
        s0->action = 0x1;
        s0->state = 0;
        s0->subState = 0;
        s0->actionFlags = 0;
        s0->flags = (s0->flags & 0xFFFFFEF7EFFFFFFFULL) | 0x1000000000ULL;
        func_800DECAC(s0, 0, 0, 0);
        s0->flags |= 0x10000000ULL;
        break;
    case 7: case 9: case 11: case 13: case 15:
    case 17: case 19: case 21: case 23: case 25:
    case 27: case 29: case 31:
        s0->flags &= 0xFFFFFFFFFFDFFFFFULL;
        s0->action = 0x2C;
        s0->state = 0;
        s0->subState = 0;
        s0->actionFlags = 0;
        s0->flags = (s0->flags & 0xFFFFFEF7EFFFFFFFULL) | 0x1000000000ULL;
        func_800DECAC(s0, 0, 0, 0);
        s0->flags |= 0x10000000ULL;
        break;
    case 8: case 10: case 12: case 14: case 16:
    case 18: case 20: case 22: case 24: case 26:
    case 28: case 30: case 32:
        s0->flags |= 0x200000ULL;
        s0->action = 0x2C;
        s0->state = 0;
        s0->subState = 0;
        s0->actionFlags = 0;
        s0->flags = (s0->flags & 0xFFFFFEF7EFFFFFFFULL) | 0x1000000000ULL;
        func_800DECAC(s0, 0, 0, 0);
        s0->flags |= 0x10000000ULL;
        break;
    default:
        return;
    }
}
