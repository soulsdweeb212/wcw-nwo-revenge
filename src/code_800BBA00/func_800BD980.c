/* @header
 * func_800BD980
 * VRAM 0x800BD980 | ROM 0xB0E20 | size 0xAD0
 * asm: asm/nonmatchings/code_800BBA00/func_800BD980.s
 */
#include "common.h"

/* 16-byte copy of x, y, z, heading. */
typedef struct { u32 w[4]; } V4D980;

extern s32 D_800E3CA0[];
extern s32 D_800E3CC0[];
extern u16 D_8007F0A0;
extern f64 D_800E5708, D_800E5710, D_800E5718, D_800E5720, D_800E5728, D_800E5730;
extern f64 D_800E5738, D_800E5740, D_800E5748, D_800E5750;
extern f64 D_800E5758, D_800E5760, D_800E5768, D_800E5770, D_800E5778, D_800E5780;
extern f64 D_800E5788, D_800E5790, D_800E5798, D_800E57A0, D_800E57A8, D_800E57B0;
extern f64 D_800E57B8, D_800E57C0, D_800E57C8, D_800E57D0, D_800E57D8, D_800E57E0;
extern f64 D_800E57E8, D_800E57F0, D_800E57F8, D_800E5800, D_800E5808, D_800E5810;
extern f64 D_800E5818, D_800E5820;

void func_800A7F6C(Wrestler *, s32);
void func_800A837C(Wrestler *);
void func_800D3838(void *, void *, s16, void *);
void func_800D427C(Wrestler *, s16, s32);

/* Try to start a scripted move of wrestler e toward side or corner arg2 (side = arg2 / 2, odd arg2 = the corner
 * table D_800E3CC0, even = the side table D_800E3CA0); b is the other wrestler (the caller passes the opponent).
 * Requires grappleCtx bit 2. With WR_FLAG_IN_RING: odd arg2 needs the heading within 0x300 of the corner angle and
 * the pelvis (jointA[1].x / .z) past that corner's thresholds, target (+-190, +-190), animation 0xEE7, sets
 * b->pairSignals bit 4 and statistics kind 0x53; even arg2 (only when D_8007F0A0 bit 0x400 is clear) needs the heading
 * within 0x600 of the side angle and the pelvis past the side threshold, target = own x,y,z,heading with x or z set
 * to +-190, animation 0xEE3, pairSignals bit 1, kind 0x50. With WR_FLAG_ON_FLOOR and even arg2: the pelvis inside a
 * window by that side gives z/x = +-320, animation 0xEE5, pairSignals bit 2 (no statistics); otherwise other
 * thresholds give z = 1210, x = +-134, or +-488, animation 0xEE7, pairSignals bit 8, kind 0x51.
 * func_800A7F6C sets moveStatKind to that kind and counts it (first word of its statistics row); func_800A837C
 * counts it again in the second word. When a target is found: start the
 * animation (func_800D427C(e, anim, 2)), moveDelta = per-tick XZ step from x,y,z to the target over 15 ticks,
 * dirIndex = side on both e and b, turnPerTick = func_800D3684(table angle, heading) / 15, stateTimer = 15,
 * step = 4; return 1.
 * Otherwise return 0. */
s32 func_800BD980(Wrestler *e, Wrestler *b, s16 arg2)
{
    s8 found;
    s32 ang;
    s16 dur;
    s16 anim;
    s16 idx;
    f64 t;
    f32 v[4];

    if (!(e->grappleCtx & 2)) {
        return 0;
    }
    found = 0;
    if (e->flags & WR_FLAG_IN_RING) {
        if (arg2 & 1) {
            idx = arg2 / 2;
            if (func_800D3550(func_800D3684(D_800E3CC0[idx], e->heading)) < 0x300) {
                switch (idx) {
                case 0:
                    if (D_800E5708 < e->jointA[1].x && D_800E5708 < e->jointA[1].z) {
                        v[0] = 190.0f;
                        v[2] = 190.0f;
                        found = 1;
                    }
                    break;
                case 1:
                    if (D_800E5710 < e->jointA[1].x && e->jointA[1].z < D_800E5718) {
                        v[0] = 190.0f;
                        v[2] = -190.0f;
                        found = 1;
                    }
                    break;
                case 2:
                    if (e->jointA[1].x < D_800E5720 && e->jointA[1].z < D_800E5720) {
                        v[0] = -190.0f;
                        v[2] = -190.0f;
                        found = 1;
                    }
                    break;
                case 3:
                    if (e->jointA[1].x < D_800E5728 && D_800E5730 < e->jointA[1].z) {
                        v[0] = -190.0f;
                        v[2] = 190.0f;
                        found = 1;
                    }
                    break;
                }
                if (found) {
                    anim = 0xEE7;
                    dur = 0xF;
                    b->pairSignals |= 4;
                    ang = D_800E3CC0[arg2 / 2];
                    func_800A7F6C(e, 0x53);
                    func_800A837C(e);
                }
            }
        } else if (!(D_8007F0A0 & 0x400)) {
            idx = arg2 / 2;
            if (func_800D3550(func_800D3684(D_800E3CA0[idx], e->heading)) < 0x600) {
                *(V4D980 *)v = *(V4D980 *)&e->x;
                switch (idx) {
                case 0:
                    if (D_800E5738 < e->jointA[1].z) {
                        v[2] = 190.0f;
                        found = 1;
                    }
                    break;
                case 1:
                    if (D_800E5740 < e->jointA[1].x) {
                        v[0] = 190.0f;
                        found = 1;
                    }
                    break;
                case 2:
                    if (e->jointA[1].z < D_800E5748) {
                        v[2] = -190.0f;
                        found = 1;
                    }
                    break;
                case 3:
                    if (e->jointA[1].x < D_800E5750) {
                        v[0] = -190.0f;
                        found = 1;
                    }
                    break;
                }
                if (found) {
                    anim = 0xEE3;
                    dur = 0xF;
                    b->pairSignals |= 1;
                    ang = D_800E3CA0[arg2 / 2];
                    func_800A7F6C(e, 0x50);
                    func_800A837C(e);
                }
            }
        }
    } else if ((e->flags & WR_FLAG_ON_FLOOR) && !(arg2 & 1)) {
        idx = arg2 / 2;
        if (func_800D3550(func_800D3684(D_800E3CA0[idx], e->heading)) < 0x600) {
            *(V4D980 *)v = *(V4D980 *)&e->x;
            switch (idx) {
            case 0:
                t = e->jointA[1].z;
                if (D_800E5758 < t && t < D_800E5760) {
                    t = e->jointA[1].x;
                    if (D_800E5768 < t && t < D_800E5770) {
                        v[2] = -320.0f;
                        found = 1;
                    }
                }
                break;
            case 1:
                t = e->jointA[1].x;
                if (D_800E5778 < t && t < D_800E5780) {
                    t = e->jointA[1].z;
                    if (D_800E5788 < t && t < D_800E5790) {
                        v[0] = -320.0f;
                        found = 1;
                    }
                }
                break;
            case 2:
                t = e->jointA[1].z;
                if (t < D_800E5798 && D_800E57A0 < t) {
                    t = e->jointA[1].x;
                    if (D_800E57A8 < t && t < D_800E57B0) {
                        v[2] = 320.0f;
                        found = 1;
                    }
                }
                break;
            case 3:
                t = e->jointA[1].x;
                if (t < D_800E57B8 && D_800E57C0 < t) {
                    t = e->jointA[1].z;
                    if (D_800E57C8 < t && t < D_800E57D0) {
                        v[0] = 320.0f;
                        found = 1;
                    }
                }
                break;
            }
            if (found) {
                anim = 0xEE5;
                b->pairSignals |= 2;
                ang = D_800E3CA0[arg2 / 2];
                dur = 0xF;
            } else {
                t = e->jointA[1].z;
                if (D_800E57D8 < t) {
                    switch (arg2 / 2) {
                    case 0:
                        if (D_800E57E0 < t) {
                            v[2] = 1210.0f;
                            found = 1;
                        }
                        break;
                    case 1:
                        if (D_800E57E8 < e->jointA[1].x) {
                            v[0] = 134.0f;
                            found = 1;
                        }
                        break;
                    case 3:
                        if (e->jointA[1].x < D_800E57F0) {
                            v[0] = -134.0f;
                            found = 1;
                        }
                        break;
                    }
                } else {
                    switch (arg2 / 2) {
                    case 0:
                        if (D_800E57F8 < t) {
                            t = e->jointA[1].x;
                            if (t < D_800E5800 || D_800E5808 < t) {
                                v[2] = 488.0f;
                                found = 1;
                            }
                        }
                        break;
                    case 1:
                        if (D_800E5810 < e->jointA[1].x) {
                            v[0] = 488.0f;
                            found = 1;
                        }
                        break;
                    case 2:
                        if (t < D_800E5818) {
                            v[2] = -488.0f;
                            found = 1;
                        }
                        break;
                    case 3:
                        if (e->jointA[1].x < D_800E5820) {
                            v[0] = -488.0f;
                            found = 1;
                        }
                        break;
                    }
                }
                if (found) {
                    anim = 0xEE7;
                    dur = 0xF;
                    b->pairSignals |= 8;
                    ang = D_800E3CA0[arg2 / 2];
                    func_800A7F6C(e, 0x51);
                    func_800A837C(e);
                }
            }
        }
    }
    if (!found) {
        return 0;
    }
    func_800D427C(e, anim, 2);
    func_800D3838(&e->x, v, dur, e->moveDelta);
    idx = arg2 / 2;
    b->dirIndex = idx;
    e->dirIndex = idx;
    e->turnPerTick = func_800D3684(ang, e->heading) / dur;
    e->stateTimer = dur;
    e->step = 4;
    return 1;
}
