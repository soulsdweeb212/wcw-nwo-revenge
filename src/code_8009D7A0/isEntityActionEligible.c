/* @header
 * isEntityActionEligible  (originally func_800A94B4)
 * VRAM 0x800A94B4 | ROM 0x9C954 | size 0x2E8
 * asm: asm/nonmatchings/code_8009D7A0/isEntityActionEligible.s
 */
#include "common.h"

/* Whether `actor` may start the given action toward `other`: each action checks a combination of actor->grappleCtx
 * bits, the u64 at actor->profile + 0x38, WR_FLAG_SPECIAL in actor->flags and other's flags (0x100000 walking, 0x400000
 * down) and moveMode; actions 0x56/0x57 also need both in the ring or both on the floor. Only 0x56/0x57 and 0xE4 read
 * other; callers pass 0 for it with 0x7E, 0x6E and 0xD2. */
s32 isEntityActionEligible(Wrestler *actor, Wrestler *other, s16 action) {
    switch (action) {
    case 0x7E:
    case 0x82:
        if ((actor->grappleCtx & 0x300)
            && (*(u64 *)(actor->profile + 0x38) & 0x800000000000ULL)
            && ((actor->grappleCtx & 3) == 3))
            return 1;
        break;
    case 0x6E:
    case 0x77:
        if ((actor->grappleCtx & 0x80)
            && (*(u64 *)(actor->profile + 0x38) & 0x400000000000ULL)
            && ((actor->grappleCtx & 3) == 3))
            return 1;
        break;
    case 0x56:
    case 0x57:
        if ((*(u64 *)(actor->profile + 0x38) & 0x100000000000ULL)
            && (actor->flags & WR_FLAG_SPECIAL)
            && (other->flags & 0x100000)
            && (other->moveMode & 0x420)
            && (actor->flags & other->flags & (WR_FLAG_IN_RING | WR_FLAG_ON_FLOOR)))
            return 1;
        break;
    case 0x58:
    case 0x59:
        if ((*(u64 *)(actor->profile + 0x38) & 0x200000000000ULL)
            && (actor->flags & WR_FLAG_SPECIAL))
            return 1;
        break;
    case 0xE4:
        if ((*(u64 *)(actor->profile + 0x38) & 0x8000000000000ULL)
            && (actor->flags & WR_FLAG_SPECIAL)
            && !(other->flags & 0x400000))
            return 1;
        break;
    case 0xD2:
        if ((*(u64 *)(actor->profile + 0x38) & 0x4000000000000ULL)
            && (actor->flags & WR_FLAG_SPECIAL))
            return 1;
        break;
    }
    return 0;
}
