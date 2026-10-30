#include "common.h"

typedef struct {
    s8 id;
    u8 pad1[9];
    u16 state;
    u8 padC[0x14];
    u64 flags;
    u8 pad28[0xC];
    u8 f34;
    u8 pad35[7];
    s16 f3C;
    s16 f3E;
    u8 pad40[0x18];
    s32 f58;
    u8 pad5C[0x10];
    f32 x;
    u8 pad70[4];
    f32 z;
    u8 pad78[0x2C8];
    f32 f340;
    u8 pad344[0x20];
    void *att;
    u8 pad368[0x12];
    u8 f37A;
    u8 f37B;
    u8 pad37C[0xA];
    u16 f386;
    u8 pad388[0x12];
    s8 f39A;
    u8 pad39B[0xB];
    u8 f3A6;
} Nw2ACE4;

typedef struct {
    f32 x, y, z;
    s32 angle;
    s32 extra;
} Nw2Dir5;

extern s16 D_800F9888[];
extern u8 D_800F9890[];
extern u8 D_800F9898[];
extern s32 D_800E3C90[];
extern s32 D_800E3CA0[];
extern s32 D_800E3CB0[];
extern s32 D_800E3CC0[];
extern f32 D_800E3FC0[][2];
extern f32 D_800E3FC4[][2];
extern f32 D_800E3FE0[][2];
extern f32 D_800E3FE4[][2];

void func_800D3890(void *, void *, void *);
s32 func_800D3684(s32, s32);
s32 func_800D3550(s32);
f32 func_800D3564(f32);
s32 func_800D35B0(s32, s32);
void func_800D37C0(void *, f32, void *);

s32 func_800DACE4(void *arg0, void *arg1) {
    Nw2ACE4 *o;
    s32 id;
    s8 sid;
    Nw2DirectionResult dir;
    f32 vec[4];
    Nw2Dir5 dir2;
    f32 floor;
    f32 cap;
    s16 v;
    s32 d;
    s32 r;

    o = arg0;
    id = o->id;
    sid = id;
    o->f34 = 0;
    D_800F9888[id] = v = o->f37B - o->f37A + 1;
    if (v <= 0) {
        D_800F9888[id] = 1;
    }

    switch ((s16)(o->state - 0x65)) {
    case 6:
    case 8:
    case 9:
        o->flags = (o->flags & ~0x80ULL) | 0x40ULL;
        floor = 0.0f;
        break;
    case 7:
    case 10:
        o->flags = (o->flags & ~0x40ULL) | 0x180ULL;
        floor = 0.0f;
        o->f340 = -90.0 / (f32)D_800F9888[sid];
        break;
    case 2:
        o->flags = (o->flags & ~0x80ULL) | 0x100ULL;
        floor = 50.0f;
        break;
    case 3:
        o->flags = (o->flags & ~0x80ULL) | 0x100ULL;
        floor = 90.0f;
        break;
    case 4:
        o->flags = (o->flags & ~0x80ULL) | 0x40ULL;
        floor = 100.0f;
        break;
    case 0:
    case 1:
    case 5:
        floor = 50.0f;
        break;
    default:
        break;
    }

    func_800D3890(&o->x, (u8 *)arg1 + (o->f39A * 16 + 0x5C), &dir);

    switch ((s16)(o->f386 - 0xD1)) {
    case 15:
        d = func_800D3550(func_800D3684(dir.angle, D_800E3C90[o->f3C]));
        if (d >= 0x400) {
            dir.y = 50.0f;
        } else {
            dir.y = func_800D3564((o->f3C & 1) ? dir.x : dir.z);
        }
        dir.angle = func_800D35B0(o->f58, 0x800);
        break;
    case 16:
        if (o->flags & 0x8000000000ULL) {
            vec[0] = D_800E3FC0[o->f3C][0];
            vec[2] = D_800E3FC4[o->f3C][0];
            func_800D3890(&o->x, vec, &dir2);
            d = func_800D3684(dir2.angle, dir.angle);
            if ((u32)(d + 0x200) >= 0x201) {
                if (d > 0) {
                    dir.angle = dir2.angle;
                } else {
                    dir.angle = func_800D35B0(dir2.angle, 0x200);
                }
            }
        } else {
            vec[0] = D_800E3FE0[o->f3C][0];
            vec[2] = D_800E3FE4[o->f3C][0];
            func_800D3890(&o->x, vec, &dir2);
            d = func_800D3684(dir2.angle, dir.angle);
            if ((u32)d >= 0x201) {
                if (d < 0) {
                    dir.angle = dir2.angle;
                } else {
                    dir.angle = func_800D35B0(dir2.angle, -0x200);
                }
            }
        }
        break;
    case 13:
    case 22:
        d = func_800D3550(func_800D3684(dir.angle, D_800E3C90[o->f3E]));
        if (d < 0x401) {
            dir.y = 50.0f;
        } else {
            dir.y = func_800D3564((o->f3E & 1) ? dir.x : dir.z);
        }
        dir.angle = D_800E3CA0[o->f3E];
        break;
    case 14:
        dir.angle = D_800E3CC0[o->f3E];
        break;
    case 17:
    case 18:
    case 19:
    case 25:
        d = func_800D3550(func_800D3684(dir.angle, D_800E3CA0[o->f3C]));
        if (d >= 0x400) {
            dir.y = 100.0f;
        } else {
            dir.y = func_800D3564((o->f3C & 1) ? dir.x : dir.z);
        }
        dir.angle = o->f58;
        break;
    case 4:
    case 5:
    case 6:
        o->f34 |= 2;
    case 0:
    case 1:
    case 23:
        r = D_800E3CC0[o->f3E];
        d = func_800D3684(r, dir.angle);
        if (func_800D3550(d) >= 0x1C8) {
            if (d < 0) {
                dir.angle = func_800D35B0(r, 0x1C7);
            } else {
                dir.angle = func_800D35B0(r, -0x1C7);
            }
        }
        break;
    case 8:
        o->f34 |= 2;
    case 7:
    case 24:
        r = D_800E3CB0[o->f3E];
        d = func_800D3684(r, dir.angle);
        if (func_800D3550(d) >= 0x5C8) {
            if (d < 0) {
                dir.angle = func_800D35B0(r, 0x5C7);
            } else {
                dir.angle = func_800D35B0(r, -0x5C7);
            }
        }
        break;
    default:
        break;
    }

    cap = (f32)(((f64)o->f3A6 + (f64)o->f3A6) * 0.1 * (f64)*(s8 *)((u8 *)o->att + 0x1B));
    if (cap <= dir.y) {
        dir.y = cap;
        o->f34 |= 1;
    }
    if (dir.y <= floor) {
        dir.y = floor;
    }

    func_800D37C0((void *)dir.angle, dir.y, &dir);
    *(f32 *)(D_800F9890 + sid * 16) = o->x + dir.x;
    *(f32 *)(D_800F9898 + sid * 16) = o->z + dir.z;
    return dir.angle;
}
