/* @header
 * func_800AD574
 * VRAM 0x800AD574 | ROM 0xA0A14 | size 0x15C
 * asm: asm/nonmatchings/code_8009D7A0/func_800AD574.s
 */
#include "common.h"

s8 func_800B71F8(Wrestler *, Wrestler *, s32);
s16 func_800A8D14(Wrestler *, Wrestler *);
void func_800A7C40(Wrestler *, s8, s16);

/* Called with atk = the opponent, def = the wrestler being updated, input = D_800FAF8A.
 * When atk's moveId is not 0x3A / 0x3C and its move.flags has bit 1, def has none of flag bits 0x9, atk lacks
 * WR_FLAG_SPECIAL unless def has it too, def's flag 0x4000000 (docs: reversal attempt used) is clear and input
 * has a 0xC030 bit: roll func_800B71F8(def, atk, 1); on success set def's flag 0x1000000 and give def move
 * func_800A8D14(atk, def) from atk's move table. In all these cases def's flag 0x4000000 is then set. */
void func_800AD574(Wrestler *atk, Wrestler *def, s32 input) {
    Wrestler *a = atk; /* the copies are needed for the match */
    Wrestler *b = def;
    s16 move = a->moveId;
    s32 c0 = (move != 0x3A);
    s32 c1 = (move != 0x3C);

    if ((c0 & c1) && (a->move.flags & 1)) {
        if (!(b->flags & 9) && (!(a->flags & WR_FLAG_SPECIAL) || (b->flags & WR_FLAG_SPECIAL)) && !(b->flags & 0x4000000) && (input & 0xC030)) {
            if (func_800B71F8(b, a, 1)) {
                b->flags |= 0x1000000;
                func_800A7C40(b, a->id, func_800A8D14(a, b));
            }
            b->flags |= 0x4000000;
        }
    }
}
