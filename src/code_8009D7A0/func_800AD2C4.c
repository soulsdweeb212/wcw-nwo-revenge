/* @header
 * func_800AD2C4
 * VRAM 0x800AD2C4 | ROM 0xA0764 | size 0x190
 * asm: asm/nonmatchings/code_8009D7A0/func_800AD2C4.s
 */
#include "common.h"

void func_800A7C40(Wrestler *, s8, s16);
void func_800A7F6C(void *, s32);
extern s16 D_800EB458[];

/* Sets w's next move (func_800A7C40) from the grappleCtx bits and the direction mask (opp = the opponent):
 * - grappleCtx bits 0x200001 both set: move 0x3A from w's own table;
 * - else grappleCtx bit 0 and both mask bits 0xC000: move 0x3C from opp's table;
 * - else mask 0x8000: move 0x17 (mask 0x800), 0x1C (mask 0x400) or 0x12 from w's table;
 *   these three cases also set grappleCtx bit 0x80000;
 * - else a base move 0x21, or 0x26 / 0x2B / 0x30 / 0x35 for mask 0x800 / 0x400 / 0x200 / 0x100 (the last one set
 *   in that order wins): stored in D_800EB458[id] and set from w's table. If the new move.flags has bit 0x80000,
 *   grappleCtx bit 0x400000 is set and that move stays; otherwise the move (plus 2 when mode is 1) is set again.
 * Ends with func_800A7F6C(w, 0). */
void func_800AD2C4(Wrestler *w, Wrestler *opp, u16 mask, s16 mode) {
    s16 move;
    u32 ctx = w->grappleCtx;

    if ((ctx & 0x200001) == 0x200001) {
        w->grappleCtx = ctx | 0x80000;
        func_800A7C40(w, w->id, 0x3A);
    } else if ((ctx & 1) && ((mask & 0xC000) == 0xC000)) {
        w->grappleCtx = ctx | 0x80000;
        func_800A7C40(w, opp->id, 0x3C);
    } else {
        if (mask & 0x8000) {
            w->grappleCtx |= 0x80000;
            if (mask & 0x800) {
                move = 0x17;
            } else {
                move = 0x12;
                if (mask & 0x400) {
                    move = 0x1C;
                }
            }
        } else {
            move = 0x21;
            if (mask & 0x800) {
                /* w++; w--; is a no-op needed for the match */
                w++;
                w--;
                move = 0x26;
            }
            if (mask & 0x400) {
                move = 0x2B;
            }
            if (mask & 0x200) {
                move = 0x30;
            }
            if (mask & 0x100) {
                move = 0x35;
            }
            D_800EB458[w->id] = move;
            func_800A7C40(w, w->id, move);
            if (w->move.flags & 0x80000) {
                w->grappleCtx |= 0x400000;
                goto done;
            }
            if (mode == 1) {
                move += 2;
            }
        }
        func_800A7C40(w, w->id, move);
    }
done:
    func_800A7F6C(w, 0);
}
