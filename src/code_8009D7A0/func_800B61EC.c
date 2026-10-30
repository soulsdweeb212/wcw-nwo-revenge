/* @header
 * func_800B61EC
 * VRAM 0x800B61EC | ROM 0xA968C | size 0x5A0
 * asm: asm/nonmatchings/code_8009D7A0/func_800B61EC.s
 */
#include "common.h"

typedef struct {
    u8 pad0[0x20];
    u64 flags;
    u16 f28;
    u8 pad2A[0x14];
    s16 f3E;
    u8 pad40[0x2C];
    f32 f6C;
    f32 f70;
    f32 f74;
} Ent61EC;

extern u16 D_8007E280;
extern s32 D_800E3CA0[];
extern f64 D_800E5510, D_800E5518, D_800E5520, D_800E5528, D_800E5530, D_800E5538, D_800E5540, D_800E5548, D_800E5550;
extern f64 D_800E5558, D_800E5560, D_800E5568, D_800E5570, D_800E5578, D_800E5580, D_800E5588, D_800E5590, D_800E5598;
extern f64 D_800E55A0, D_800E55A8, D_800E55B0;
s8 func_800C2830(void *);
s8 isEntityActionAllowedC2870(void *);
f32 func_800D3564(f32);
f32 func_800D3890(void *, void *, s32);
void getRingBoundaryPointAlongHeading(f32 *, s32, f32 *);
void func_800E212C(void *);

s32 func_800B61EC(Ent61EC *p, Ent61EC *q, u16 mode, s32 heading) {
    u16 fl;
    f32 d;
    s32 r;
    s32 t;
    s16 dir;
    s32 quad;
    s16 k;
    f32 *pos;
    f32 pt[3];

    fl = p->f28;
    p->f28 = fl & 0x7FFF;
    if (fl & 0x28) {
        return 0;
    }
    if (p->flags & 0x40) {
        if ((mode & 8) && (fl & 1)) {
            switch (p->f3E) {
            case 0:
            case 2:
                d = p->f74;
                break;
            case 1:
            case 3:
                d = p->f6C;
                break;
            }
            dir = p->f3E;
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
                p->f28 |= 0x8000;
                func_800E212C(p);
                return 1;
            }
        }
        t = mode & 4;
        if (t && func_800C2830(p) && (q->flags & 0x180)) {
            pos = &p->f6C;
            getRingBoundaryPointAlongHeading(pos, heading, pt);
            d = func_800D3890(pos, pt, 0);
            if (D_800E5530 <= d && d <= D_800E5538) {
                return 1;
            }
        }
    } else if (p->flags & 0x100) {
        if ((mode & 8) && (isEntityActionAllowedC2870(p) || (D_8007E280 & 0x200))) {
            if ((p->f28 & 1) && !(p->f28 & 0x10)) {
                quad = (getXZDirectionQuadrant(&p->f6C) + 2) & 3;
                if (quad == p->f3E) {
                    switch (quad) {
                    case 0:
                    case 2:
                        d = func_800D3564(p->f74);
                        break;
                    case 1:
                    case 3:
                        d = func_800D3564(p->f6C);
                        break;
                    }
                    if (d < D_800E5540 && D_800E5548 < d) {
                        switch (p->f3E) {
                        case 0:
                        case 2:
                            d = func_800D3564(p->f6C);
                            break;
                        case 1:
                        case 3:
                            d = func_800D3564(p->f74);
                            break;
                        }
                        if (d < D_800E5550) {
                            p->f28 |= 0x8000;
                            func_800E212C(p);
                            return 1;
                        }
                    }
                }
            }
        }
        if ((mode & 4) && isEntityActionAllowedC2870(p)) {
            k = -1;
            if (D_800E5558 < p->f6C && p->f6C < D_800E5560) {
                if (p->f74 < D_800E5568 && D_800E5570 < p->f74) {
                    k = 0;
                }
                if (D_800E5578 < p->f74 && p->f74 < D_800E5580) {
                    k = 2;
                }
            }
            if (D_800E5588 < p->f74 && p->f74 < D_800E5590) {
                if (p->f6C < D_800E5598 && D_800E55A0 < p->f6C) {
                    k = 1;
                }
                if (D_800E55A8 < p->f6C && p->f6C < D_800E55B0) {
                    k = 3;
                }
            }
            if (k != -1 && func_800D3550(func_800D3684(heading, D_800E3CA0[k])) < 0x2AA) {
                p->f3E = k;
                return 1;
            }
        }
    }
    return 0;
}
