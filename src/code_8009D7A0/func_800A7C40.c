/* @header
 * func_800A7C40
 * VRAM 0x800A7C40 | ROM 0x9B0E0 | size 0xDC
 * asm: asm/nonmatchings/code_8009D7A0/func_800A7C40.s
 */
#include "common.h"

extern u8 D_80075468[];
void unpackAnimationParameters(void *, void *);

/* Set w's current move to entry moveId of owner's move table: store moveOwnerId and moveId, then unpack the
 * 0x18-byte entry (D_80075468 + 0x10 + owner*0x1A30 + moveId*0x18) into w->move. For moveId below 0xEF, set or
 * clear the 0x4000000000000000 flag from bit 0x8000 of move.flags. */
void func_800A7C40(Wrestler *w, s8 owner, s16 moveId) {
    s32 idx;
    u8 *tbl;

    /* volatile store: the asm stores moveOwnerId and loads it back (lb); a plain member store does not match */
    *(volatile s8 *)&w->moveOwnerId = owner;
    idx = w->moveOwnerId;
    w->moveId = moveId;
    tbl = &D_80075468[0x10] + idx * 0x1A30;
    unpackAnimationParameters(&w->move, tbl + moveId * 0x18);
    if (moveId < 0xEF) {
        if (w->move.flags & 0x8000)
            w->flags |= 0x4000000000000000ULL;
        else
            w->flags &= ~0x4000000000000000ULL;
    }
}
