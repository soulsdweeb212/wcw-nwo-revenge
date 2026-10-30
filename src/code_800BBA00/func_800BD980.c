/* @header
 * func_800BD980
 * VRAM 0x800BD980 | ROM 0xB0E20 | size 0xAD0
 * asm: asm/nonmatchings/code_800BBA00/func_800BD980.s
 */
#include "common.h"

typedef struct { u32 w[4]; } V4D980;

typedef struct {
    u8 pad0[0xC];
    s16 fC;
    u8 padE[8];
    s16 f16;
    u8 pad18[8];
    u64 flags;
    u8 pad28[4];
    u32 f2C;
    u8 pad30[0xE];
    s16 f3E;
    u8 pad40[0xC];
    V4D980 f4C;
    u8 pad5C[0x10];
    f32 f6C;
    f32 f70;
    f32 f74;
    u8 pad78[0x2C4];
    u8 f33C[0xC];
    s32 f348;
    u8 pad34C[0x14];
    u16 f360;
} ED980;

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

void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800D3838(void *, void *, s16, void *);
void func_800D427C(void *, s16, s32);

s32 func_800BD980(ED980 *e, ED980 *b, s16 arg2)
{
    s8 found;
    s32 ang;
    s16 dur;
    s16 anim;
    s16 idx;
    f64 t;
    f32 v[4];

    if (!(e->f2C & 2)) {
        return 0;
    }
    found = 0;
    if (e->flags & 0x40) {
        if (arg2 & 1) {
            idx = arg2 / 2;
            if (func_800D3550(func_800D3684(D_800E3CC0[idx], e->f4C.w[3])) < 0x300) {
                switch (idx) {
                case 0:
                    if (D_800E5708 < e->f6C && D_800E5708 < e->f74) {
                        v[0] = 190.0f;
                        v[2] = 190.0f;
                        found = 1;
                    }
                    break;
                case 1:
                    if (D_800E5710 < e->f6C && e->f74 < D_800E5718) {
                        v[0] = 190.0f;
                        v[2] = -190.0f;
                        found = 1;
                    }
                    break;
                case 2:
                    if (e->f6C < D_800E5720 && e->f74 < D_800E5720) {
                        v[0] = -190.0f;
                        v[2] = -190.0f;
                        found = 1;
                    }
                    break;
                case 3:
                    if (e->f6C < D_800E5728 && D_800E5730 < e->f74) {
                        v[0] = -190.0f;
                        v[2] = 190.0f;
                        found = 1;
                    }
                    break;
                }
                if (found) {
                    anim = 0xEE7;
                    dur = 0xF;
                    b->f360 |= 4;
                    ang = D_800E3CC0[arg2 / 2];
                    func_800A7F6C(e, 0x53);
                    func_800A837C(e);
                }
            }
        } else if (!(D_8007F0A0 & 0x400)) {
            idx = arg2 / 2;
            if (func_800D3550(func_800D3684(D_800E3CA0[idx], e->f4C.w[3])) < 0x600) {
                *(V4D980 *)v = e->f4C;
                switch (idx) {
                case 0:
                    if (D_800E5738 < e->f74) {
                        v[2] = 190.0f;
                        found = 1;
                    }
                    break;
                case 1:
                    if (D_800E5740 < e->f6C) {
                        v[0] = 190.0f;
                        found = 1;
                    }
                    break;
                case 2:
                    if (e->f74 < D_800E5748) {
                        v[2] = -190.0f;
                        found = 1;
                    }
                    break;
                case 3:
                    if (e->f6C < D_800E5750) {
                        v[0] = -190.0f;
                        found = 1;
                    }
                    break;
                }
                if (found) {
                    anim = 0xEE3;
                    dur = 0xF;
                    b->f360 |= 1;
                    ang = D_800E3CA0[arg2 / 2];
                    func_800A7F6C(e, 0x50);
                    func_800A837C(e);
                }
            }
        }
    } else if ((e->flags & 0x100) && !(arg2 & 1)) {
        idx = arg2 / 2;
        if (func_800D3550(func_800D3684(D_800E3CA0[idx], e->f4C.w[3])) < 0x600) {
            *(V4D980 *)v = e->f4C;
            switch (idx) {
            case 0:
                t = e->f74;
                if (D_800E5758 < t && t < D_800E5760) {
                    t = e->f6C;
                    if (D_800E5768 < t && t < D_800E5770) {
                        v[2] = -320.0f;
                        found = 1;
                    }
                }
                break;
            case 1:
                t = e->f6C;
                if (D_800E5778 < t && t < D_800E5780) {
                    t = e->f74;
                    if (D_800E5788 < t && t < D_800E5790) {
                        v[0] = -320.0f;
                        found = 1;
                    }
                }
                break;
            case 2:
                t = e->f74;
                if (t < D_800E5798 && D_800E57A0 < t) {
                    t = e->f6C;
                    if (D_800E57A8 < t && t < D_800E57B0) {
                        v[2] = 320.0f;
                        found = 1;
                    }
                }
                break;
            case 3:
                t = e->f6C;
                if (t < D_800E57B8 && D_800E57C0 < t) {
                    t = e->f74;
                    if (D_800E57C8 < t && t < D_800E57D0) {
                        v[0] = 320.0f;
                        found = 1;
                    }
                }
                break;
            }
            if (found) {
                anim = 0xEE5;
                b->f360 |= 2;
                ang = D_800E3CA0[arg2 / 2];
                dur = 0xF;
            } else {
                t = e->f74;
                if (D_800E57D8 < t) {
                    switch (arg2 / 2) {
                    case 0:
                        if (D_800E57E0 < t) {
                            v[2] = 1210.0f;
                            found = 1;
                        }
                        break;
                    case 1:
                        if (D_800E57E8 < e->f6C) {
                            v[0] = 134.0f;
                            found = 1;
                        }
                        break;
                    case 3:
                        if (e->f6C < D_800E57F0) {
                            v[0] = -134.0f;
                            found = 1;
                        }
                        break;
                    }
                } else {
                    switch (arg2 / 2) {
                    case 0:
                        if (D_800E57F8 < t) {
                            t = e->f6C;
                            if (t < D_800E5800 || D_800E5808 < t) {
                                v[2] = 488.0f;
                                found = 1;
                            }
                        }
                        break;
                    case 1:
                        if (D_800E5810 < e->f6C) {
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
                        if (e->f6C < D_800E5820) {
                            v[0] = -488.0f;
                            found = 1;
                        }
                        break;
                    }
                }
                if (found) {
                    anim = 0xEE7;
                    dur = 0xF;
                    b->f360 |= 8;
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
    func_800D3838(&e->f4C, v, dur, e->f33C);
    idx = arg2 / 2;
    b->f3E = idx;
    e->f3E = idx;
    e->f348 = func_800D3684(ang, e->f4C.w[3]) / dur;
    e->f16 = dur;
    e->fC = 4;
    return 1;
}
