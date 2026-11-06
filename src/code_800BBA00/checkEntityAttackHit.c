/* @header
 * checkEntityAttackHit  (originally func_800D9944)
 * VRAM 0x800D9944 | ROM 0xCCDE4 | size 0x490
 * asm: asm/nonmatchings/code_800BBA00/checkEntityAttackHit.s
 */
#include "common.h"

/* Attack hit test between wrestler self and its partner record (partnerId).
 * First self attacking the partner, then the partner attacking self: checks the
 * two are not the same, the target is within facing/range (state/dirIndex/flags
 * and the pelvis position jointA[1].x/.z against the D_800E70xx limits), and the
 * attack mask matches the target's hit table (frameBits); on success applies the
 * hit via func_800D9E1C and returns 1, otherwise 0. */
extern u8 D_8007E228[];
extern u8 D_8007EF30[];
extern u16 D_800E3CD0[];
extern u16 D_800E3CE0[];
extern f64 D_800E7000, D_800E7008, D_800E7010, D_800E7018;
s8 func_800D9DD4(void *, void *);
void func_800D9E1C(void *, void *, s16);

s32 checkEntityAttackHit(Wrestler *self, s32 mask) {
    Wrestler *partner;
    s32 v;
    s16 tmp;

    if (!(*(u16 *)(D_8007E228 + 0x58) & 0x200)) goto ret0;
    if (*(u16 *)(D_8007EF30 + 0x170) & 0x40) goto ret0;
    if (self->partnerId == self->id) goto ret0;
    partner = &D_800F9D10[self->partnerId];

    if (!(self->flags & WR_FLAG_IN_RING)) goto L_BD0;
    if (!(self->flags & WR_FLAG_LEGAL)) goto L_BC8;

    if (partner->flags & WR_FLAG_IN_RING) {
        if (partner->state == 0xA) {
            if (partner->flags & WR_FLAG_TEAM_B) tmp = 0; else tmp = 2;
            if ((s16)tmp == partner->dirIndex) {
                v = 1;
                goto L_B10;
            }
        }
    }
    if (partner->flags & WR_FLAG_ON_APRON) {
        if (partner->flags & WR_FLAG_TEAM_B) {
            v = 0;
            if (D_800E7000 < (f64)partner->jointA[1].x)
                v = D_800E7000 < (f64)partner->jointA[1].z;
        } else {
            v = 0;
            if ((f64)partner->jointA[1].x < D_800E7008)
                v = (f64)partner->jointA[1].z < D_800E7008;
        }
    } else {
        v = 0;
    }
L_B10:
    if (v == 0) goto L_BC8;
    if (func_800D9DD4(self, partner) == 0) goto L_BC8;
    if (partner->frameBits & 1) {
        if (D_800E3CD0[partner->ringSide] & mask) {
            func_800D9E1C(self, partner, 0);
            return 1;
        }
    }
    if (partner->frameBits & 2) {
        if (self->flags & WR_FLAG_TEAM_B) tmp = 0; else tmp = 2;
        if ((D_800E3CE0[tmp] & mask) == D_800E3CE0[tmp]) {
            func_800D9E1C(self, partner, 1);
            return 1;
        }
    }
    goto L_BC8;

L_BC8:
    ;
L_BD0:
    if (self->flags & WR_FLAG_LEGAL) goto ret0;
    if (self->flags & WR_FLAG_IN_RING) {
        if (self->state == 0xA) {
            if (self->flags & WR_FLAG_TEAM_B) tmp = 0; else tmp = 2;
            if ((s16)tmp == self->dirIndex) {
                v = 1;
                goto L_D10;
            }
        }
    }
    if (self->flags & WR_FLAG_ON_APRON) {
        if (self->flags & WR_FLAG_TEAM_B) {
            v = 0;
            if (D_800E7010 < (f64)self->jointA[1].x)
                v = D_800E7010 < (f64)self->jointA[1].z;
        } else {
            v = 0;
            if ((f64)self->jointA[1].x < D_800E7018)
                v = (f64)self->jointA[1].z < D_800E7018;
        }
    } else {
        v = 0;
    }
L_D10:
    if (v == 0) goto ret0;
    if (func_800D9DD4(self, partner) == 0) goto ret0;
    if (partner->state != 1) goto ret0;
    if (!(partner->flags & WR_FLAG_IN_RING)) goto ret0;
    if (self->state == 0xA) {
        func_800D9E1C(self, partner, 1);
        return 1;
    }
    if (self->flags & WR_FLAG_ON_APRON) {
        func_800D9E1C(self, partner, 0);
        return 1;
    }
ret0:
    return 0;
}
