/* @header
 * updateEntityModeFlags  (originally func_800D4BFC)
 * VRAM 0x800D4BFC | ROM 0xC809C | size 0xC8
 * asm: asm/nonmatchings/code_800BBA00/updateEntityModeFlags.s
 */
#include "common.h"

/* Sets the zone bits (WR_FLAG_ZONE_MASK) of w->flags from the zone the current animation ends in (anim.endZone):
 * 1 -> WR_FLAG_IN_RING, 2 -> WR_FLAG_ON_FLOOR, 3 -> WR_FLAG_ON_APRON; other values leave the flags unchanged. */
void updateEntityModeFlags(Wrestler *w) {
    switch (w->anim.endZone) {
    case 1: w->flags = (w->flags & ~WR_FLAG_ZONE_MASK) | WR_FLAG_IN_RING; break;
    case 2: w->flags = (w->flags & ~WR_FLAG_ZONE_MASK) | WR_FLAG_ON_FLOOR; break;
    case 3: w->flags = (w->flags & ~WR_FLAG_ZONE_MASK) | WR_FLAG_ON_APRON; break;
    }
}
