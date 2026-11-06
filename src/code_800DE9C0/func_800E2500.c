/* @header
 * func_800E2500
 * VRAM 0x800E2500 | ROM 0xD59A0 | size 0x268
 * asm: asm/nonmatchings/code_800DE9C0/func_800E2500.s
 */
#include "common.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    s32 angle;
} Dir2500;
typedef struct {
    u8 b[0x5C];
} Rec7E010;
typedef struct {
    u8 f0;
    u8 f1;
    s8 f2;
    u8 f3;
    f32 f4;
    f32 f8;
    f32 fC;
    u8 pad10[0xC];
    s32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
    s32 f2C;
} Slot2500;
extern Rec7E010 D_8007E010[];
extern f64 D_800E7788;
extern f64 D_800E7790;
extern f64 D_800E7798;
extern f64 D_800E77A0;
extern Slot2500 D_800F98E0[];
extern s8 D_800F99A0[];
s8 func_800E2A18(void *);
s32 func_800D3E40(void *, f32 *, s32, f32 *);
void func_800D3890(void *, void *, void *);

static inline void setup2500(Wrestler *self, Wrestler *other, s8 id) {
    f32 sp10[3];
    f32 sp20[3];
    Dir2500 dr;

    D_800F98E0[id].f2 = -1;
    D_800F98E0[id].f1 = D_800F98E0[id].f0;
    sp10[0] = 0.0f;
    sp10[2] = 20.0f;
    func_800D3E40(&self->jointA[4], sp10, self->heading, sp20);
    D_800F98E0[id].f4 = sp20[0];
    D_800F98E0[id].fC = sp20[2];
    D_800F98E0[id].f8 = (self->jointA[5].y + other->jointA[5].y) * D_800E7788;
    func_800D3890(&self->jointA[5], &other->jointA[5], &dr);
    D_800F98E0[id].f1C = dr.angle;
    D_800F98E0[id].f20 = dr.y * D_800E7790;
    D_800F98E0[id].f24 = -(dr.y * D_800E7798);
    D_800F98E0[id].f28 = (other->jointA[5].y - self->jointA[5].y) * D_800E77A0;
    D_800F98E0[id].f2C = 0;
    D_8007E010[id].b[0] = 0;
}

/* With arg2 == 0: when self->anim.unk372[2] is nonzero and animFrame equals anim.unk372[3], take a free effect
 * slot from func_800E2A18, store it in D_800F99A0[self->id], give it type 0xC/2 (unk372[2] == 1) or 0xB/4, and
 * fill it with the point 20 units ahead of self->jointA[4] (func_800D3E40 rotates (0, 20) by self->heading),
 * the two wrestlers' jointA[5].y, and the XZ distance and angle from self->jointA[5] to other->jointA[5]
 * (func_800D3890; Dir2500.y holds the distance). Returns 1 when a slot was filled, else 0.
 * Any other arg2 returns 0. */
s32 func_800E2500(Wrestler *self, Wrestler *other, s16 arg2) {
    s8 id;
    s32 t;

    if (arg2 == 0) {
        if (self->anim.unk372[2] != 0 && self->animFrame == self->anim.unk372[3]) {
            id = func_800E2A18(self);
            if (id != -1) {
                D_800F99A0[self->id] = id;
                if (self->anim.unk372[2] == 1) {
                    D_800F98E0[id].f0 = 0xC;
                    D_800F98E0[id].f3 = 2;
                } else {
                    D_800F98E0[id].f0 = 0xB;
                    D_800F98E0[id].f3 = 4;
                }
                setup2500(self, other, id);
                return 1;
            }
        }
        return 0;
    }
    t = arg2;
    return ((t << 16) >> 16) - t;
}
