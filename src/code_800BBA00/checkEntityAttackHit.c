/* @header
 * checkEntityAttackHit  (originally func_800D9944)
 * VRAM 0x800D9944 | ROM 0xCCDE4 | size 0x490
 * asm: asm/nonmatchings/code_800BBA00/func_800D9944.s
 */
#include "common.h"

/* Attack hit test for entity s1 against another entity s0 (both EntD9944).
 * First s1 attacking s0, then s0 attacking s1: checks the two entities are not
 * the same, the target is within facing/range (fA/quadrant/flags and the
 * distance fields f6C/f74 against the D_800E70xx limits), and the attack mask
 * matches the target's hit table; on success applies the hit via func_800D9E1C
 * and returns 1, otherwise 0. */
typedef struct {
    s8 id;              /* +0x00 */
    u8 pad1[9];
    s16 fA;             /* +0x0A */
    s16 fC;
    u8 padE[8];
    s16 f16;
    u8 pad18[8];
    u64 flags;          /* +0x20 entity status bits */
    u8 pad28[0x10];
    u8 hitFlags;        /* +0x38 which hit tables apply */
    u8 pad39[3];
    s16 f3C;            /* +0x3C */
    s16 f3E;            /* +0x3E facing quadrant */
    u8 pad40[0x18];
    s32 f58;
    u8 pad5C[0x10];
    f32 distA;          /* +0x6C */
    u8 pad70[4];
    f32 distB;          /* +0x74 */
    u8 pad78[0x2DD];
    s8 targetIndex;     /* +0x355 */
} EntD9944;
extern u8 D_8007E228[];
extern u8 D_8007EF30[];
extern u16 D_800E3CD0[];
extern u16 D_800E3CE0[];
extern f64 D_800E7000, D_800E7008, D_800E7010, D_800E7018;
extern u8 D_800F9D10[];
s8 func_800D9DD4(void *, void *);
void func_800D9E1C(void *, void *, s16);

s32 checkEntityAttackHit(EntD9944 *s1, s32 mask) {
    EntD9944 *s0;
    s32 v;
    s16 tmp;

    if (!(*(u16 *)(D_8007E228 + 0x58) & 0x200)) goto ret0;
    if (*(u16 *)(D_8007EF30 + 0x170) & 0x40) goto ret0;
    if (s1->targetIndex == s1->id) goto ret0;
    s0 = (EntD9944 *)(D_800F9D10 + s1->targetIndex * 0x3B0);

    if (!(s1->flags & 0x40)) goto L_BD0;
    if (!(s1->flags & 0x200)) goto L_BC8;

    if (s0->flags & 0x40) {
        if (s0->fA == 0xA) {
            if (s0->flags & 0x200000000) tmp = 0; else tmp = 2;
            if ((s16)tmp == s0->f3E) {
                v = 1;
                goto L_B10;
            }
        }
    }
    if (s0->flags & 0x80) {
        if (s0->flags & 0x200000000) {
            v = 0;
            if (D_800E7000 < (f64)s0->distA)
                v = D_800E7000 < (f64)s0->distB;
        } else {
            v = 0;
            if ((f64)s0->distA < D_800E7008)
                v = (f64)s0->distB < D_800E7008;
        }
    } else {
        v = 0;
    }
L_B10:
    if (v == 0) goto L_BC8;
    if (func_800D9DD4(s1, s0) == 0) goto L_BC8;
    if (s0->hitFlags & 1) {
        if (D_800E3CD0[s0->f3C] & mask) {
            func_800D9E1C(s1, s0, 0);
            return 1;
        }
    }
    if (s0->hitFlags & 2) {
        if (s1->flags & 0x200000000) tmp = 0; else tmp = 2;
        if ((D_800E3CE0[tmp] & mask) == D_800E3CE0[tmp]) {
            func_800D9E1C(s1, s0, 1);
            return 1;
        }
    }
    goto L_BC8;

L_BC8:
    ;
L_BD0:
    if (s1->flags & 0x200) goto ret0;
    if (s1->flags & 0x40) {
        if (s1->fA == 0xA) {
            if (s1->flags & 0x200000000) tmp = 0; else tmp = 2;
            if ((s16)tmp == s1->f3E) {
                v = 1;
                goto L_D10;
            }
        }
    }
    if (s1->flags & 0x80) {
        if (s1->flags & 0x200000000) {
            v = 0;
            if (D_800E7010 < (f64)s1->distA)
                v = D_800E7010 < (f64)s1->distB;
        } else {
            v = 0;
            if ((f64)s1->distA < D_800E7018)
                v = (f64)s1->distB < D_800E7018;
        }
    } else {
        v = 0;
    }
L_D10:
    if (v == 0) goto ret0;
    if (func_800D9DD4(s1, s0) == 0) goto ret0;
    if (s0->fA != 1) goto ret0;
    if (!(s0->flags & 0x40)) goto ret0;
    if (s1->fA == 0xA) {
        func_800D9E1C(s1, s0, 1);
        return 1;
    }
    if (s1->flags & 0x80) {
        func_800D9E1C(s1, s0, 0);
        return 1;
    }
ret0:
    return 0;
}
