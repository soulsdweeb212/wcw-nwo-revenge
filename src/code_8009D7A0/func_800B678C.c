/* @header
 * func_800B678C
 * VRAM 0x800B678C | ROM 0xA9C2C | size 0x10C
 * asm: asm/nonmatchings/code_8009D7A0/func_800B678C.s
 */
#include "common.h"

f32 func_800D3890(void *, void *, void *);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);

/* Step-over check of w against the wrestler it walked into (startEntityGrapple starts state 0x8A on a 1). Only when
 * w is not running (moveMode bit 0x20 clear), the caller passes flag 4, both share WR_FLAG_IN_RING or
 * WR_FLAG_ON_FLOOR and other has flag 0x400000 (down on the mat). If w->steppedOverId is already other->id it returns
 * 2; otherwise it takes the direction from w's pelvis (jointA[1]) to other's and, when it is within 0x2AA of
 * w->heading, stores other->id in w->steppedOverId and returns 1. Returns 0 in every other case. */
s32 func_800B678C(Wrestler *w, Wrestler *other, s32 flags) {
    Nw2DirectionResult result;
    u64 shared;

    if (!(w->moveMode & 0x20)) {
        if (flags & 4) {
            shared = w->flags & other->flags;
            if (((shared & WR_FLAG_IN_RING) || (shared & WR_FLAG_ON_FLOOR)) && (other->flags & 0x400000)) {
                if (w->steppedOverId != other->id) {
                    func_800D3890(&w->jointA[1].x, &other->jointA[1].x, &result);
                    if (func_800D3550(func_800D3684(result.angle, w->heading)) < 0x2AA) {
                        w->steppedOverId = other->id;
                        return 1;
                    }
                } else {
                    return 2;
                }
            }
        }
    }
    return 0;
}
