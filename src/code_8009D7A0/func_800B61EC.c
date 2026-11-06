/* @header
 * func_800B61EC
 * VRAM 0x800B61EC | ROM 0xA968C | size 0x5A0
 * asm: asm/nonmatchings/code_8009D7A0/func_800B61EC.s
 */
#include "common.h"

extern u16 D_8007E280;
extern s32 D_800E3CA0[];
extern f64 D_800E5510, D_800E5518, D_800E5520, D_800E5528, D_800E5530, D_800E5538, D_800E5540, D_800E5548, D_800E5550;
extern f64 D_800E5558, D_800E5560, D_800E5568, D_800E5570, D_800E5578, D_800E5580, D_800E5588, D_800E5590, D_800E5598;
extern f64 D_800E55A0, D_800E55A8, D_800E55B0;
s8 func_800C2830(Wrestler *);
s8 isEntityActionAllowedC2870(Wrestler *);
f32 func_800D3564(f32);
f32 func_800D3890(void *, void *, s32);
void getRingBoundaryPointAlongHeading(f32 *, s32, f32 *);
void func_800E212C(Wrestler *);

/* p: the wrestler being updated, q: its opponent; func_8009E624 passes D_800FABE6 as mode and either
 * D_800EB3E0[slot] or p->heading as heading. Always clears moveMode bit 0x8000 first; returns 0 when the old
 * moveMode had 0x20 or 0x8 set. Positions are p's pelvis, jointA[1].
 * - WR_FLAG_IN_RING: with mode & 8 and old moveMode & 1, if jointA[1].z (sides 0/2) or .x (sides 1/3) of the side
 *   dirIndex is in 185..200 (sides 0/1) or -200..-185 (sides 2/3), sets moveMode 0x8000, calls func_800E212C(p)
 *   and returns 1. With mode & 4, func_800C2830(p) nonzero and q on the apron or floor, returns 1 when the XZ
 *   distance from the pelvis to the rope-line point along heading (getRingBoundaryPointAlongHeading) is in 80..95.
 * - else WR_FLAG_ON_FLOOR: with mode & 8 (and isEntityActionAllowedC2870(p) or D_8007E280 & 0x200), moveMode & 1
 *   and not 0x10, and the side opposite the pelvis quadrant equal to dirIndex, if |coordinate toward that side| is
 *   between 280 and 335 and |the other coordinate| < 230, sets moveMode 0x8000, calls func_800E212C(p) and
 *   returns 1. With mode & 4 and isEntityActionAllowedC2870(p), picks the side k (0..3) whose window (one
 *   coordinate within +-230, the other 280..335 out toward k; D_800E5558..D_800E55B0) holds the pelvis; when
 *   heading is within 0x2AA of D_800E3CA0[k], sets dirIndex = k and returns 1.
 * Otherwise returns 0. */
s32 func_800B61EC(Wrestler *p, Wrestler *q, u16 mode, s32 heading) {
    u16 fl;
    f32 d;
    s32 r;
    s32 t;
    s16 dir;
    s32 quad;
    s16 k;
    f32 *pos;
    f32 pt[3];

    fl = p->moveMode;
    p->moveMode = fl & 0x7FFF;
    if (fl & 0x28) {
        return 0;
    }
    if (p->flags & WR_FLAG_IN_RING) {
        if ((mode & 8) && (fl & 1)) {
            switch (p->dirIndex) {
            case 0:
            case 2:
                d = p->jointA[1].z;
                break;
            case 1:
            case 3:
                d = p->jointA[1].x;
                break;
            }
            dir = p->dirIndex;
            r = 0;
            if (dir >= 0) {
                if (dir < 2) {
                    if (D_800E5510 <= d && d <= D_800E5518) {
                        r = 1;
                    }
                } else if (dir < 4) {
                    if (d <= D_800E5520 && D_800E5528 <= d) {
                        r = 1;
                    }
                }
            }
            t = r;
            if (t) {
                p->moveMode |= 0x8000;
                func_800E212C(p);
                return 1;
            }
        }
        t = mode & 4;
        if (t && func_800C2830(p) && (q->flags & (WR_FLAG_ON_APRON | WR_FLAG_ON_FLOOR))) {
            pos = &p->jointA[1].x;
            getRingBoundaryPointAlongHeading(pos, heading, pt);
            d = func_800D3890(pos, pt, 0);
            if (D_800E5530 <= d && d <= D_800E5538) {
                return 1;
            }
        }
    } else if (p->flags & WR_FLAG_ON_FLOOR) {
        if ((mode & 8) && (isEntityActionAllowedC2870(p) || (D_8007E280 & 0x200))) {
            if ((p->moveMode & 1) && !(p->moveMode & 0x10)) {
                quad = (getXZDirectionQuadrant(&p->jointA[1].x) + 2) & 3;
                if (quad == p->dirIndex) {
                    switch (quad) {
                    case 0:
                    case 2:
                        d = func_800D3564(p->jointA[1].z);
                        break;
                    case 1:
                    case 3:
                        d = func_800D3564(p->jointA[1].x);
                        break;
                    }
                    if (d < D_800E5540 && D_800E5548 < d) {
                        switch (p->dirIndex) {
                        case 0:
                        case 2:
                            d = func_800D3564(p->jointA[1].x);
                            break;
                        case 1:
                        case 3:
                            d = func_800D3564(p->jointA[1].z);
                            break;
                        }
                        if (d < D_800E5550) {
                            p->moveMode |= 0x8000;
                            func_800E212C(p);
                            return 1;
                        }
                    }
                }
            }
        }
        if ((mode & 4) && isEntityActionAllowedC2870(p)) {
            k = -1;
            if (D_800E5558 < p->jointA[1].x && p->jointA[1].x < D_800E5560) {
                if (p->jointA[1].z < D_800E5568 && D_800E5570 < p->jointA[1].z) {
                    k = 0;
                }
                if (D_800E5578 < p->jointA[1].z && p->jointA[1].z < D_800E5580) {
                    k = 2;
                }
            }
            if (D_800E5588 < p->jointA[1].z && p->jointA[1].z < D_800E5590) {
                if (p->jointA[1].x < D_800E5598 && D_800E55A0 < p->jointA[1].x) {
                    k = 1;
                }
                if (D_800E55A8 < p->jointA[1].x && p->jointA[1].x < D_800E55B0) {
                    k = 3;
                }
            }
            if (k != -1 && func_800D3550(func_800D3684(heading, D_800E3CA0[k])) < 0x2AA) {
                p->dirIndex = k;
                return 1;
            }
        }
    }
    return 0;
}
