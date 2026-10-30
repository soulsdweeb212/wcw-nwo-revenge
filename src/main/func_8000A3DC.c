/* @header
 * func_8000A3DC
 * VRAM 0x8000A3DC | ROM 0xAFDC | size 0x694
 * asm: asm/nonmatchings/main/func_8000A3DC.s
 */
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

#define SC D_80030848[rem]

void func_8000A3DC(s32 arg0, s16 arg1)
{
    u32 i;
    u32 j;
    s16 e;
    s16 rem;
    s32 r;
    Vec0A3 *src;
    Vec0A3 *dst;
    Part0A3 *p;
    f32 t;

    e = arg0;
    rem = arg1 % 3;
    func_80009990(e);
    i = 1;
    dst = &D_80070B28[1];
    src = &D_80070488[1];
    r = D_800706B0[e].v;
    do {
        r = func_8000AA70(r, src, dst);
        dst++;
        i++;
        src++;
    } while (i < 20);
    j = 1;
    do {
        i = D_800307E8[j];
        p = &D_80070C40[e][i];
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
        j++;
    } while (j < 20);
}
