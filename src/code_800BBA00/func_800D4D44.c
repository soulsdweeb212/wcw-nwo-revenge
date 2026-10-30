/* @header
 * func_800D4D44
 * VRAM 0x800D4D44 | ROM 0xC81E4 | size 0x6F4
 * asm: asm/nonmatchings/code_800BBA00/func_800D4D44.s
 */
#include "common.h"

typedef struct {
    u8 pad0[0x38];
    u64 flags;
} Nw2D44Cap;
typedef struct {
    s8 f0;
    u8 pad1[7];
    s16 f8;
    u8 padA[0x16];
    u64 flags;
    u16 f28;
    u8 pad2A[0x33A];
    Nw2D44Cap *f364;
} Nw2D44Obj;
extern s16 D_800E3E70[];
extern s16 D_800E3E80[];
extern s16 D_800E3E90[];
extern s16 D_800E3EA0[];
extern s16 D_800E3EB0[];
extern s16 D_800E3EC0[];
extern s16 D_800E3ED0[];
extern s16 D_800E3EE0[];
extern s16 D_800E3EF0[];
extern s16 D_800E3F00[];
extern s16 D_800E3F10[];
extern s16 D_800E3F18[];
extern s8 D_800FADB9[];
extern s16 func_800BF1E0(void *, s32);

s32 func_800D4D44(Nw2D44Obj *o, s16 action, f32 timer)
{
    s16 s1;
    s16 s2;

    if (o->f364->flags & 4) s1 = 0;
    if (o->f364->flags & 8) s1 = 1;
    if (o->f364->flags & 0x10) s1 = 2;
    if (o->f364->flags & 0x20) s1 = 3;
    if (o->f364->flags & 0x40) s1 = 4;
    if (o->f364->flags & 0x80) s1 = 5;
    if (o->f364->flags & 0x100) s1 = 6;

    switch (action) {
    case 2: return D_800E3EA0[s1];
    case 3: return D_800E3EB0[s1];
    case 4: return D_800E3EC0[s1];
    case 5: return D_800E3ED0[s1];
    case 6: return D_800E3EE0[s1];
    case 7: return D_800E3EF0[s1];
    case 8: return D_800E3F00[s1];
    case 0:
        if (o->flags & 0x1000000000000ULL) {
            if (o->flags & 0x2000000000000ULL) return 0x100C;
            return 0x1004;
        }
        if (o->flags & 1) return D_800E3E70[s1];
        s2 = D_800FADB9[o->f0];
        if (func_800BF1E0(o, s2) < 0x19) return D_800E3F10[s2];
        if (timer < 350.0) return D_800E3E70[s1];
        if (timer > 355.0) return 0xE72;
        {
            s32 v;
            v = o->f8;
            if ((v ^ 0xE73) == 0) return 0xE72;
            return D_800E3E70[s1];
        }
    case 1:
        if (o->flags & 0x1000000000000ULL) {
            if (o->flags & 0x2000000000000ULL) return 0x100B;
            return 0x1003;
        }
        if (o->flags & 1) return D_800E3E80[s1];
        s2 = D_800FADB9[o->f0];
        if (func_800BF1E0(o, s2) < 0x19) return D_800E3F18[s2];
        if (timer < 350.0) return D_800E3E80[s1];
        if (timer > 355.0) return 0xE73;
        {
            s32 v;
            v = o->f8;
            if ((v ^ 0xE73) == 0) return 0xE73;
            return D_800E3E80[s1];
        }
    case 12: return D_800E3E80[s1];
    case 9:
        if (o->flags & 0x80) {
            if (o->flags & 0x8000000000ULL) return 0x1091;
            return 0x1092;
        }
        if (o->flags & 0x1000000000000ULL) {
            if (o->flags & 0x2000000000000ULL) return 0x1026;
            return 0x102A;
        }
        if (s1 == 6) return 0xE82;
        return 0xE6F;
    case 10:
        if (o->flags & 0x80) {
            if (o->flags & 0x8000000000ULL) return 0x108F;
            return 0x1090;
        }
        if (o->flags & 0x1000000000000ULL) {
            if (o->flags & 0x2000000000000ULL) return 0x1027;
            return 0x102B;
        }
        if (o->f364->flags & 0x100) {
            if (o->f28 & 0x20) return 0xE6E;
        }
        return D_800E3E90[s1];
    case 11:
        if (o->flags & 0x80) {
            if (o->flags & 0x8000000000ULL) return 0x1093;
            return 0x1094;
        }
        if (o->flags & 0x1000000000000ULL) {
            if (o->flags & 0x2000000000000ULL) return 0x1028;
            return 0x102C;
        }
        if (o->f364->flags & 0x100) return 0xE83;
        if (o->f364->flags & 0x200) return 0xE75;
        if (o->flags & 8) return 0xE75;
        return 0xE70;
    }
    return 0;
}
