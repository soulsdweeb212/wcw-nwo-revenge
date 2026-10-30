/* @header
 * func_800D2CAC
 * VRAM 0x800D2CAC | ROM 0xC614C | size 0x718
 * asm: asm/nonmatchings/code_800BBA00/func_800D2CAC.s
 */
#include "common.h"

typedef struct { f32 x, y, z, w; } V4_2CAC;

typedef struct {
    u8 p0[6];
    s16 f6;
    u8 p8[0x18];
    u64 flags;
    u8 p28[0x14];
    s16 f3C;
    u8 p3E[0xE];
    V4_2CAC v4C;
    V4_2CAC parts[20];
} Ent2CAC;

typedef struct { u8 p0[0x11]; u8 f11; } Att2CAC;
typedef struct { f32 x, y, z; s32 angle; } Dir2CAC;

extern f64 D_800E6B38, D_800E6B40, D_800E6B48, D_800E6B50, D_800E6B58, D_800E6B60;
extern V4_2CAC D_800E3D30[];
extern s32 D_800E3D14[];
extern u8 D_800E3E10[];

void func_800D3890(void *, V4_2CAC *, Dir2CAC *);
void translateEntityXZ(void *, f32 *);

#define e ((Ent2CAC *)entity)

s32 func_800D2CAC(void *entity, void *linked1, void *linked2, f32 divisor, void *attach, void *points, void *pos, u16 dirMask, s32 bodyMask, u16 applyFlag) {
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

    if (!(e->flags & 0x40) && (e->flags & 0x80)) {
        half[0] = 0.0f;
        half[2] = 0.0f;
        vb = e->v4C;
        if (e->flags & 0x0800000000000000ULL) {
            vb.x = e->parts[1].x;
            vb.z = e->parts[1].z;
            switch (e->f3C) {
            case 0:
            case 2:
                vb.z = e->v4C.z;
                break;
            case 1:
            case 3:
                vb.x = e->v4C.x;
                break;
            }
        }
    } else {
        lo[0] = e->parts[1].x;
        hi[0] = e->parts[1].x;
        lo[2] = e->parts[1].z;
        hi[2] = e->parts[1].z;
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
                if (e->parts[i].x < lo[0]) {
                    lo[0] = e->parts[i].x;
                }
                if (e->parts[i].x > hi[0]) {
                    hi[0] = e->parts[i].x;
                }
                if (e->parts[i].z < lo[2]) {
                    lo[2] = e->parts[i].z;
                }
                if (e->parts[i].z > hi[2]) {
                    hi[2] = e->parts[i].z;
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
    if (!(e->flags & 0x40)) {
        if (e->flags & 0x80) {
            dir = getXZDirectionQuadrant(&e->parts[1].x) + 7;
        } else {
            dir = getXZDirectionQuadrant(&e->parts[1].x) + 3;
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
            mp = (s32 *)((s32)(dir << 2) + (s32)tbl);
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
        translateEntityXZ(entity, dp);
        if (attach == 0 || ((Att2CAC *)attach)->f11 == 0 || !(((Att2CAC *)attach)->f11 < e->f6)) {
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
