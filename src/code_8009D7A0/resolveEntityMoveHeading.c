/* @header
 * resolveEntityMoveHeading  (originally func_800B4690)
 * VRAM 0x800B4690 | ROM 0xA7B30 | size 0x4AC
 * asm: asm/nonmatchings/code_8009D7A0/resolveEntityMoveHeading.s
 */
#include "common.h"

/* Resolve a wrestler's move heading from the input word.
 * Picks a direction index (dirIndex) from the input, ringSide and the zone flags (WR_FLAG_IN_RING / ON_APRON /
 * ON_FLOOR), validates the resulting target against the ring boundary (getRingBoundaryPointAlongHeading) and the
 * movement check (func_800D2ACC) using the step vector it builds in moveDelta, writes the chosen heading to *out,
 * and returns 1 if the move is allowed or 0 if it is blocked. moveMode is cleared first and collects the resolution
 * bits (1, 2, 4, 8, 0x10, 0x4000); on the apron, flags bit 0x8000000000 is set when dirIndex becomes ringSide - 1. */
extern s32 D_800E3C90[], D_800E3CA0[], D_800E3CB0[], D_800F9B14;
s16 func_800D7B08(u16);
s16 func_800D7A2C(u16);
s16 findBoundaryQuadrant(void *, void *, s32);
s8 func_800B4B3C(void *);
void func_800E212C(void *);
s16 func_800D65D0(void *, u16);
void getRingBoundaryPointAlongHeading(void *, s32, void *);
s32 func_800D6610(void *, s16);
f32 func_800D63F0(void *, s32, s32);
void func_800D37C0(s32, f32, void *);
s8 func_800D26A0(void *, void *, s32);
u32 func_800D2ACC(void *, s32, void *);
s32 resolveEntityMoveHeading(Wrestler *w, u16 input, s32 *out) {
    f32 point[4];
    s16 idx;
    s16 result;
    u32 hit;

    w->moveMode = 0;
    w->flags &= ~0x8001000000ULL;
    if (input & 0xF00) {
        if (((*(volatile u64 *)&w->flags) & WR_FLAG_IN_RING) && ((w->dirIndex = func_800D7B08(input)) != -1)) {
            if (w->dirIndex == findBoundaryQuadrant(w, 0, 2)) return 0;
            w->moveMode |= 9;
        } else w->moveMode |= 3;
    } else w->moveMode = 4;
    if (w->moveMode & 2) {
        if ((w->flags & WR_FLAG_ON_FLOOR) && (result = func_800D7B08(input)) != -1) {
            w->moveMode |= 0x10;
            *out = D_800E3CB0[result];
        } else {
            if (w->flags & (WR_FLAG_IN_RING | WR_FLAG_ON_FLOOR)) {
                w->dirIndex = func_800D7A2C(input);
                *out = D_800E3C90[w->dirIndex];
                if (func_800B4B3C(w)) {
                    w->moveMode |= 0x4000;
                    func_800E212C(w);
                }
            }
            if (w->flags & WR_FLAG_ON_APRON) {
                result = func_800D65D0(w, input);
                if (!result) return 0;
                idx = (u16)w->ringSide;
                if (result == 1) {
                    w->flags |= 0x8000000000ULL;
                    idx--;
                } else idx++;
                w->dirIndex = idx & 3;
                *out = D_800E3C90[w->dirIndex];
            }
        }
    }
    if (w->moveMode & 4) {
        if (w->flags & WR_FLAG_IN_RING) {
            s32 *heading = &D_800F9B14;
            getRingBoundaryPointAlongHeading(&w->jointA[1].x, *heading, point);
            w->dirIndex = findBoundaryQuadrant(w, point, 0);
            if (w->dirIndex == -1) {
                w->dirIndex = getXZDirectionQuadrant(point);
                *out = *heading;
                w->moveMode |= 2;
            } else w->moveMode |= 8;
        }
        if (w->flags & WR_FLAG_ON_APRON) {
            idx = w->ringSide;
            if (func_800D3684(D_800E3CA0[idx], D_800F9B14) < 0) {
                w->flags |= 0x8000000000ULL;
                idx--;
            } else idx++;
            w->dirIndex = idx & 3;
            *out = D_800E3C90[w->dirIndex];
            w->moveMode |= 2;
        }
        if (w->flags & WR_FLAG_ON_FLOOR) *out = D_800F9B14;
    }
    if (w->moveMode & 8) *out = func_800D6610(w, w->dirIndex);
    func_800D37C0(*out, func_800D63F0(w, 0, 2), w->moveDelta);
    if (func_800D26A0(w, w->moveDelta, -1) != -1) return 0;
    hit = func_800D2ACC(w, 2, w->moveDelta);
    if (hit && (w->moveMode & 6)) {
        if (w->flags & WR_FLAG_ON_APRON) return 0;
        if ((w->flags & WR_FLAG_ON_FLOOR) && (hit >> 16)) return 0;
    }
    return 1;
}
