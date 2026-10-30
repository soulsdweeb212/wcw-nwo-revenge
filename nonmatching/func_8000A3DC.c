#include "common.h"

typedef struct {
    f32 a, b, c;
    f32 x, y, z;
    u8 pad18[0x64];
} Part0A3;
typedef struct {
    f32 x, y, z;
} Vec0A3;
typedef struct {
    s32 v;
    u8 pad[0xF8];
} Row0A3;

extern Part0A3 D_80070C40[][23];
extern Vec0A3 D_80070488[];
extern Vec0A3 D_80070B28[];
extern Row0A3 D_800706B0[];
extern s8 D_800307E8[];
extern s8 D_800307FC[];
extern f32 D_80030848[];

void func_80009990(s16);
s32 func_8000AA70(s32, Vec0A3 *, Vec0A3 *);
f32 func_80003CF0(f32);

inline static f32 wrap0A3(f32 value)
{
    if (value >= 0.0) {
        while (value > 180.0)
            value -= 360.0;
    } else {
        while (value <= -180.0)
            value += 360.0;
    }
    return value;
}

inline static f32 wrapDiff(f32 b, f32 a)
{
    f32 value = a - b;
    if (value >= 0.0) {
        while (value > 180.0)
            value -= 360.0;
    } else {
        while (value <= -180.0)
            value += 360.0;
    }
    return value;
}

#define SC (*(&D_80030848[(s16)rem]))

void func_8000A3DC(s32 arg0, s16 arg1)
{
    u32 i;
    u32 j;
    s32 rem;
    s32 r;
    s32 ent;
    Vec0A3 *src;
    Vec0A3 *dst;
    Part0A3 *p;
    f32 t;
    s32 a1;

    a1 = arg1;
    rem = a1 - (a1 / 3) * 3;
    {
        u32 tq = (u32)a1 & 1;
        if (tq >> 1) {
            rem = 0;
        }
    }
    func_80009990((s16)arg0);
    i = 1;
    dst = &D_80070B28[1];
    src = &D_80070488[1];
    r = D_800706B0[(s16)arg0].v;
    ent = arg0;
    do {
        r = func_8000AA70(r, src, dst);
        dst++;
        i++;
        src++;
    } while (i < 20);
    j = 1;
    ent = (s16)ent;
    do {
        i = D_800307E8[j];
        p = &D_80070C40[ent][i];
        if (!D_800307FC[i]) {
            p->x += (D_80070B28[i].x - p->x) * SC;
            p->y += (D_80070B28[i].y - p->y) * SC;
            p->z += (D_80070B28[i].z - p->z) * SC;
        }
        D_80070488[i].x = wrapDiff(p->a, D_80070488[i].x);
        t = p->b;
        D_80070488[i].y = wrap0A3(D_80070488[i].y - t);
        t = p->c;
        D_80070488[i].z = wrap0A3(D_80070488[i].z - t);
        if (func_80003CF0(D_80070488[i].x) > 120.0 || func_80003CF0(D_80070488[i].z) > 120.0) {
            D_80070488[i].x = wrap0A3(D_80070488[i].x + 180.0f);
            D_80070488[i].z = wrap0A3(D_80070488[i].z + 180.0f);
        }
        p->a += D_80070488[i].x * SC;
        p->b += D_80070488[i].y * SC;
        p->c += D_80070488[i].z * SC;
        {
            u32 tq3 = (u32)rem & 1;
            if (tq3 >> 1) {
                j = 0;
            }
        }
        j++;
    } while (j < 20);
}
