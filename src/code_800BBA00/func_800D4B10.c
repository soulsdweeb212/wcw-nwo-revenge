/* @header
 * func_800D4B10
 * VRAM 0x800D4B10 | ROM 0xC7FB0 | size 0xEC
 * asm: asm/nonmatchings/code_800BBA00/func_800D4B10.s
 */
#include "common.h"

/* Applies the zone the animation ends in (anim.endZone): 1 sets the zone bits to WR_FLAG_IN_RING and y to 90,
 * 2 sets WR_FLAG_ON_FLOOR and y to 0, 3 sets WR_FLAG_ON_APRON and y to 90. The WR_FLAG_ZONE_MASK bits are cleared
 * first; other values change nothing. */
void func_800D4B10(Wrestler *w) {
    switch (w->anim.endZone) {
    case 1:
        w->flags = (w->flags & ~WR_FLAG_ZONE_MASK) | WR_FLAG_IN_RING;
        w->y = 90.0f;
        break;
    case 2:
        w->y = 0.0f;
        w->flags = (w->flags & ~WR_FLAG_ZONE_MASK) | WR_FLAG_ON_FLOOR;
        break;
    case 3:
        w->flags = (w->flags & ~WR_FLAG_ZONE_MASK) | WR_FLAG_ON_APRON;
        w->y = 90.0f;
        break;
    }
}
