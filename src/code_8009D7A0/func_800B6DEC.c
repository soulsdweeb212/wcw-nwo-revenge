/* @header
 * func_800B6DEC
 * VRAM 0x800B6DEC | ROM 0xAA28C | size 0x40C
 * asm: asm/nonmatchings/code_8009D7A0/func_800B6DEC.s
 */
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
extern s8 D_8007EF2C;
extern u16 D_8007E280;
extern f64 D_800E55E8;
extern f64 D_800E55F0;

s32 func_800BF2FC(Ent6DEC *);

s16 func_800B6DEC(Ent6DEC *o, Ent6DEC *other, s16 type) {
    u16 v[3];
    s16 r;
    s16 x;

    switch (type) {
    case 0:
        r = 0;
        if (o->flags & 0x80000ULL) {
            break;
        }
        v[0] = 180 + D_800FAF50[o->f0] * 3;
        v[1] = (o->f10 + o->f14) / 2;
        v[2] = o->f40 * 80;
        x = v[0] - v[1] - v[2];
        r = x;
        if ((D_8007E280 & 0x200) && (o->flags & 0x100ULL)) {
            r = x * D_800E55E8;
        }
        if (o->flags & 0x80ULL) {
            r = r * D_800E55F0;
        }
        break;
    case 1:
        v[0] = 110 + other->f14 / 4;
        v[1] = D_800FADD2[o->f0] * 3;
        v[2] = func_800BF2FC(o) + (s16)o->f14 / 2;
        x = v[0] + v[1] - v[2];
        r = x;
        if (x >= 90 && o->f14 >= 90) {
            r = 87;
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
        x = 180 - (o->f14 / 2 + o->f10 / 4);
        r = x;
        if (D_8007EF2C != 0) {
            r = (D_800FACE8 >= 6) ? x : 0;
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
    return (r < 0) ? 0 : r;
}
