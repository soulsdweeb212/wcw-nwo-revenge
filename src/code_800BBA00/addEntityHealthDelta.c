/* @header
 * addEntityHealthDelta  (originally func_800BF62C)
 * VRAM 0x800BF62C | ROM 0xB2ACC | size 0xD4
 * asm: asm/nonmatchings/code_800BBA00/addEntityHealthDelta.s
 */
#include "common.h"

/* Despite the name, adds delta to w->spirit (not health), unless w has WR_FLAG_SPIRIT_EMPTY, WR_FLAG_SPIRIT_FULL or
 * WR_FLAG_SPECIAL. At 100 or more it clamps to 99 when flags bit 1 is set, else sets 100 and raises
 * WR_FLAG_SPIRIT_FULL; at 0 or below it clamps to 0 and raises WR_FLAG_SPIRIT_EMPTY. */
void addEntityHealthDelta(Wrestler *w, s32 delta) {
    if (!(w->flags & (WR_FLAG_SPIRIT_EMPTY | WR_FLAG_SPIRIT_FULL | WR_FLAG_SPECIAL))) {
        w->spirit += delta;
        if (w->spirit >= 100) {
            if (w->flags & 1) w->spirit = 99;
            else { w->spirit = 100; w->flags |= WR_FLAG_SPIRIT_FULL; }
        }
        if (w->spirit <= 0) { w->spirit = 0; w->flags |= WR_FLAG_SPIRIT_EMPTY; }
    }
}
