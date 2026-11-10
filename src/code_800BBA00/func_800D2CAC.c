/* @header
 * func_800D2CAC
 * VRAM 0x800D2CAC | ROM 0xC614C | size 0x718
 * asm: asm/nonmatchings/code_800BBA00/func_800D2CAC.s
 */
#include "common.h"

typedef struct { f32 x, y, z, w; } V4_2CAC;

typedef struct { f32 x, y, z; s32 angle; } Dir2CAC;

extern f64 D_800E6B38, D_800E6B40, D_800E6B48, D_800E6B50, D_800E6B58, D_800E6B60;
extern V4_2CAC D_800E3D30[];
extern s32 D_800E3D14[];
extern u8 D_800E3E10[];

void func_800D3890(void *, V4_2CAC *, Dir2CAC *);
void translateEntityXZ(void *, f32 *);

/* Boundary check (and correction) of a wrestler against the box of its zone.
 * Reference point vb and half size: on the apron (WR_FLAG_ON_APRON without WR_FLAG_IN_RING) the root x/z with no
 * size (with flag 0x0800000000000000: the pelvis jointA[1] x/z, except that the root's z is kept on ringSide 0/2
 * and the root's x on ringSide 1/3);
 * otherwise the centre and half size of the XZ bounds of the pelvis (widened by D_800E6B38 / D_800E6B40 when
 * bodyMask bit 1 is set) and of jointA[2..19] picked by bodyMask bits 2..19.
 * Box: entry dir of D_800E3D30, shrunk by the half size; dir 0 in the ring, 7 + quadrant on the apron, 3 + quadrant
 * elsewhere (getXZDirectionQuadrant of the pelvis), with special boxes 0xB and 0xC picked by vb for dir 3.
 * Result: side bits 0x100/0x200 (X) and 0x400/0x800 (Z) of the box edges crossed, mostly moved to the high half.
 * With applyFlag, the push back along the axes allowed by dirMask (0 = all, 0xF00), divided by divisor, is applied to
 * the wrestler (translateEntityXZ), to linked1 / linked2 unless attach (a WrAnimMeta, passed only by func_800D2BEC)
 * has a nonzero unk379 below the wrestler's animFrame, to the three 16-byte points and to pos. */

s32 func_800D2CAC(Wrestler *self, Wrestler *linked1, Wrestler *linked2, f32 divisor, WrAnimMeta *attach, void *points, void *pos, u16 dirMask, s32 bodyMask, u16 applyFlag) {
    f32 box[4];
    f32 lo[3];
    f32 hi[3];
    f32 delta[3];
    V4_2CAC vb;
    f32 half[3];
    Dir2CAC res;
    s32 result;
    s16 dir;
    s16 i;
    s32 bit;
    s32 *mp;
    f32 *dp;
    s32 *tbl;

    if (!(self->flags & WR_FLAG_IN_RING) && (self->flags & WR_FLAG_ON_APRON)) {
        half[0] = 0.0f;
        half[2] = 0.0f;
        vb = *(V4_2CAC *)&self->x;
        if (self->flags & 0x0800000000000000ULL) {
            vb.x = self->jointA[1].x;
            vb.z = self->jointA[1].z;
            switch (self->ringSide) {
            case 0:
            case 2:
                vb.z = self->z;
                break;
            case 1:
            case 3:
                vb.x = self->x;
                break;
            }
        }
    } else {
        lo[0] = self->jointA[1].x;
        hi[0] = self->jointA[1].x;
        lo[2] = self->jointA[1].z;
        hi[2] = self->jointA[1].z;
        if (bodyMask & 2) {
            lo[0] = lo[0] + D_800E6B38;
            hi[0] = hi[0] + D_800E6B40;
            lo[2] = lo[2] + D_800E6B38;
            hi[2] = hi[2] + D_800E6B40;
        }
        bit = 4;
        i = 2;
        do {
            if (bodyMask & bit) {
                if (self->jointA[i].x < lo[0]) {
                    lo[0] = self->jointA[i].x;
                }
                if (self->jointA[i].x > hi[0]) {
                    hi[0] = self->jointA[i].x;
                }
                if (self->jointA[i].z < lo[2]) {
                    lo[2] = self->jointA[i].z;
                }
                if (self->jointA[i].z > hi[2]) {
                    hi[2] = self->jointA[i].z;
                }
            }
            i++;
            bit <<= 1;
        } while (i < 20);
        half[0] = (hi[0] - lo[0]) * D_800E6B48;
        half[2] = (hi[2] - lo[2]) * D_800E6B48;
        vb.x = lo[0] + half[0];
        vb.z = lo[2] + half[2];
    }

    dir = 0;
    if (!(self->flags & WR_FLAG_IN_RING)) {
        if (self->flags & WR_FLAG_ON_APRON) {
            dir = getXZDirectionQuadrant(&self->jointA[1].x) + 7;
        } else {
            dir = getXZDirectionQuadrant(&self->jointA[1].x) + 3;
        }
    }
    if (dir == 3) {
        if (vb.z > D_800E6B50) {
            func_800D3890(D_800E3E10, &vb, &res);
            if (func_800D3550(res.angle) < 0x200) {
                dir = 0xB;
            }
        } else if (vb.x > D_800E6B58 && vb.x < D_800E6B60) {
            dir = 0xC;
        }
    }
    box[0] = D_800E3D30[dir].x - half[2];
    box[1] = D_800E3D30[dir].y - half[0];
    box[2] = D_800E3D30[dir].z + half[2];
    box[3] = D_800E3D30[dir].w + half[0];

    tbl = D_800E3D14;
    i = 0;
    do {
        result = 0;
        delta[0] = 0.0f;
        delta[2] = 0.0f;
        if (vb.x < box[3]) {
            result = 0x200;
            delta[0] = box[3] - vb.x;
        }
        if (box[1] < vb.x) {
            result |= 0x100;
            delta[0] = box[1] - vb.x;
        }
        if (vb.z > box[0]) {
            result |= 0x800;
            delta[2] = box[0] - vb.z;
        }
        if (vb.z < box[2]) {
            result |= 0x400;
            delta[2] = box[2] - vb.z;
        }
        if ((u16)(dir - 3) < 4) {
#ifdef TARGET_PC
            /* The N64 code adds the byte offset dir * 4 to the table's address in 32 bits, which would cut a 64-bit
             * pointer; the PC adds it to the pointer: the same entry, D_800E3D14[dir]. */
            mp = (s32 *)((u8 *)tbl + (dir << 2));
#else
            mp = (s32 *)((s32)(dir << 2) + (s32)tbl);
#endif
            if (result & *mp) {
                s16 nd;
                result = (result & ~*mp) << 16;
                nd = getXZDirectionQuadrant(&vb.x) + 3;
                if (nd == dir) {
                    dir = nd;
                    result |= *mp;
                    break;
                }
                dir = nd;
            } else {
                result <<= 16;
                break;
            }
        } else {
            if (dir == 0xB) {
                if (result != 0) {
                    result = (result | 0x2000) << 16;
                }
            } else if (dir == 0xC) {
                if (result & 0x400) {
                    result = ((result & ~0x400) << 16) | 0x400;
                } else {
                    result <<= 16;
                }
            }
            break;
        }
        i++;
    } while (i < 2);

    if (applyFlag) {
        s32 mask;
        if (!dirMask) {
            dirMask = 0xF00;
        }
        mask = (dirMask << 16) | dirMask;
        if (result & mask & 0x03000300) {
            delta[0] = delta[0] / divisor;
        } else {
            delta[0] = 0.0f;
        }
        if (result & mask & 0x0C000C00) {
            delta[2] = delta[2] / divisor;
        } else {
            delta[2] = 0.0f;
        }
        dp = delta;
        translateEntityXZ(self, dp);
        if (attach == NULL || attach->unk379 == 0 || !(attach->unk379 < self->animFrame)) {
            do {
                if (linked1) {
                    translateEntityXZ(linked1, dp);
                }
                if (linked2) {
                    translateEntityXZ(linked2, dp);
                }
            } while (0);
        }
        if (points) {
            ((V4_2CAC *)points)[0].x += delta[0];
            ((V4_2CAC *)points)[0].z += delta[2];
            ((V4_2CAC *)points)[1].x += delta[0];
            ((V4_2CAC *)points)[1].z += delta[2];
            ((V4_2CAC *)points)[2].x += delta[0];
            ((V4_2CAC *)points)[2].z += delta[2];
        }
        if (pos) {
            ((V4_2CAC *)pos)->x += delta[0];
            ((V4_2CAC *)pos)->z += delta[2];
        }
    }
    return result;
}
