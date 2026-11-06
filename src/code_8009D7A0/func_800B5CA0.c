/* @header
 * func_800B5CA0
 * VRAM 0x800B5CA0 | ROM 0xA9140 | size 0x124
 * asm: asm/nonmatchings/code_8009D7A0/func_800B5CA0.s
 */
#include "common.h"

f32 func_800D3EEC(void *, void *, s32);
void func_800E212C(Wrestler *);
extern f64 D_800E54D8;
extern s32 D_800F9B14;

/* p: the wrestler being updated (heading, pelvis jointA[1]); q: its opponent (root x/y/z, heading, flags).
 * Both callers (func_8009E624, and func_800B5730 forwarding its arguments) pass D_800EB408, D_800EB40C,
 * D_800FABE6 as flags and D_800F9B0C as distance.
 *
 * If flags & 0x4000, p and q are both WR_FLAG_IN_RING or both WR_FLAG_ON_FLOOR, q has flags bit 0x400000, and
 * distance is below func_800D3EEC(&q->x, &p->jointA[1], q->heading) + D_800E54D8 (130), and the angle between
 * D_800F9B14 and p->heading is below 0x200, then p is put in state 0x56 (func_800A6C48, handler rerun this tick),
 * func_800E212C(p) is called and 1 is returned. Otherwise 0. */
s32 func_800B5CA0(Wrestler *p, Wrestler *q, s32 flags, f32 distance) {
    u64 common;
    if (flags & 0x4000) {
        common = p->flags & q->flags;
        if (((common & WR_FLAG_IN_RING) || (common & WR_FLAG_ON_FLOOR)) && (q->flags & 0x400000) &&
            ((f64)distance < (f64)func_800D3EEC(&q->x, &p->jointA[1], q->heading) + D_800E54D8)) {
            if (func_800D3550(func_800D3684(D_800F9B14, p->heading)) < 0x200) {
                func_800A6C48(p, 0x56);
                func_800E212C(p);
                return 1;
            }
        }
    }
    return 0;
}
