#include "common.h"

typedef struct {
    s8 f0;
    u8 pad1[0xF];
    s16 f10;
    u8 pad12[2];
    s16 f14;
    u8 pad16[0xA];
    u64 flags;
    u8 pad28[0x18];
    s16 f40;
} Ent6DEC;

extern s16 D_800FAF50[];
extern s16 D_800FADD2[];
extern s8 D_800FACE8;
extern u8 D_8007EF2C;
extern u16 D_8007E280;
extern f64 D_800E55E8;
extern f64 D_800E55F0;

s16 func_800BF2FC(Ent6DEC *);

s16 func_800B6DEC(Ent6DEC *o, Ent6DEC *other, s16 type) {
    u16 v[3];
    s32 a;
    s32 b;
    s32 c;
    s32 r;
    s16 t;

    switch (type) {
    case 0:
        r = 0;
        if (o->flags & 0x80000ULL) {
            break;
        }
        a = 180 + D_800FAF50[o->f0] * 3;
        v[0] = a;
        b = (o->f10 + o->f14) / 2;
        v[1] = b;
        r = a - b;
        c = o->f40 * 80;
        v[2] = c;
        r = r - c;
        if ((D_8007E280 & 0x200) && (o->flags & 0x100ULL)) {
            r = (s32)((f64)(s16)r * 1.5);
        }
        if (o->flags & 0x80ULL) {
            r = (s32)((f64)(s16)r * 0.65);
        }
        break;
    case 1:
        v[0] = 110 + other->f14 / 4;
        v[1] = D_800FADD2[o->f0] * 3;
        c = func_800BF2FC(o) + (s16)o->f14 / 2;
        v[2] = c;
        r = v[0] + v[1] - c;
        if ((s16)r >= 90) {
            if (!(o->f14 < 90)) {
                r = 87;
            }
        }
        break;
    case 2:
        r = 0;
        if (o->flags & 0x80000ULL) {
            break;
        }
        r = 100 - (o->f14 / 2 + o->f10 / 4);
        break;
    case 3:
        if (o->flags & 0x80000ULL) {
            r = 60;
            break;
        }
        r = 60;
        goto tail;
    case 4:
        r = 0;
        if (o->flags & 0x80000ULL) {
            break;
        }
        r = 180 - (o->f14 / 2 + o->f10 / 4);
        if (D_8007EF2C != 0) {
            r = (D_800FACE8 >= 6) ? r : 0;
        }
        break;
    case 5:
        if (o->flags & 0x80000ULL) {
            r = 0;
            break;
        }
        r = 0;
        goto tail;
    case 6:
        r = 0;
        if (o->flags & 0x80000ULL) {
            break;
        }
    tail:
        v[0] = 300 + other->f14 / 2;
        v[1] = o->f10 + o->f14 / 4;
        r = ((s16)v[0] - (s16)v[1]) / 2;
        break;
    }
    t = r;
    if (t < 0) {
        t = 0;
    }
    return t;
}
