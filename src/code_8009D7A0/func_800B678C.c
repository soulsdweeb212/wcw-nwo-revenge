#include "common.h"

/* Target-acquisition check between two entities. If p is not already locked
 * (p->flags28 bit 0x20 clear) and the caller passes flag 4, it intersects the
 * two entities' u64 flag words at +0x20: only when they share bit 0x40 or 0x100
 * and q has bit 0x400000 does it consider q a valid target. If p's stored
 * target id (0x354) differs from q's id, it computes the direction between the
 * entities' positions (+0x6C) and, when the heading error is below 0x2AA,
 * records q as the new target and returns 1. Returns 2 if q is already p's
 * target and 0 otherwise. */
typedef struct {
    s8 f0;               /* @0x0 entity id */
    u8 pad1[0x1F];
    u64 flags20;         /* @0x20 */
    u16 flags28;         /* @0x28 */
    u8 pad2A[0x2E];
    s32 f58;             /* @0x58 heading */
    u8 pad5C[0x10];
    f32 pos6C[3];        /* @0x6C position xyz */
    u8 pad78[0x2DC];
    s8 target354;        /* @0x354 current target id */
} Nw2Target678C;

f32 func_800D3890(void *, void *, void *);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);

s32 func_800B678C(Nw2Target678C *p, Nw2Target678C *q, s32 flags) {
    Nw2DirectionResult result;
    u64 shared;

    if (!(p->flags28 & 0x20)) {
        if (flags & 4) {
            shared = p->flags20 & q->flags20;
            if (((shared & 0x40) || (shared & 0x100)) && (q->flags20 & 0x400000)) {
                if (p->target354 != q->f0) {
                    func_800D3890(p->pos6C, q->pos6C, &result);
                    if (func_800D3550(func_800D3684(result.angle, p->f58)) < 0x2AA) {
                        p->target354 = q->f0;
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
