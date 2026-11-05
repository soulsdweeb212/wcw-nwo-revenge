/* @header
 * func_80090A38
 * VRAM 0x80090A38 | ROM 0x83ED8 | size 0x6D0
 * asm: asm/nonmatchings/ovl2_80090000/func_80090A38.s
 */
#include "common.h"

typedef struct {
    u32 flags;
} Cam;

typedef struct {
    u8 pad0[0x14];
    Cam *cam;
} Obj;

typedef struct Spr Spr;

void func_800907A0(Obj *dst, Spr *n, s16 x, s16 y, f32 ax, f32 ay, f32 sx, f32 sy, u8 r, u8 g, u8 b, u8 a);

extern u16 D_800EB0AA;
extern u16 D_800F99BA;

/* Cross-fade from sprite a to sprite b over t frames; returns 1 once both are hidden. */
s32 func_80090A38(Obj *a, Spr *as, Obj *b, Spr *bs, f32 y, s16 t, s16 flag) {
    s32 done;

    done = 1;
    if (!(a->cam->flags & 0x80) || !(b->cam->flags & 0x80)) {
        done = 0;
        if (t < 6) {
            func_800907A0(a, as, 0xF0, y, 0.5f, -0.2f, 3.0 - t * 0.33, 3.0 - t * 0.33, 0xFF, 0xFF, 0xFF, t * 32 + 0x5F);
            func_800907A0(b, bs, 0xF0, y, 0.5f, -0.2f, 3.0 - t * 0.33, 3.0 - t * 0.33, 0xFF, 0xFF, 0xFF, t * 32 + 0x5F);
            a->cam->flags |= 0x80;
            b->cam->flags &= ~0x80;
        } else if (t < 9) {
            func_800907A0(a, as, 0xF0, y, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(b, bs, 0xF0, y, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
            a->cam->flags &= ~0x80;
            b->cam->flags |= 0x80;
        } else if (t < 18) {
            func_800907A0(a, as, 0xF0, y, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(b, bs, 0xF0, y, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF - (t - 9) * 30);
            a->cam->flags &= ~0x80;
            b->cam->flags |= 0x80;
        } else {
            if (flag == 0) {
                if (t < 24) {
                    func_800907A0(a, as, 0xF0, y, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
                    func_800907A0(b, bs, 0xF0, y, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
                } else if (t < 27) {
                    func_800907A0(a, as, 0xF0, y, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF - (t - 24) * 90);
                    func_800907A0(b, bs, 0xF0, y, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
                } else {
                    func_800907A0(a, as, 0xF0, y, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
                    func_800907A0(b, bs, 0xF0, y, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
                    done = 1;
                }
            } else {
                if (t < 54) {
                    func_800907A0(a, as, 0xF0, y, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
                    func_800907A0(b, bs, 0xF0, y, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
                } else if (t < 57) {
                    func_800907A0(a, as, 0xF0, y, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF - (t - 54) * 90);
                    func_800907A0(b, bs, 0xF0, y, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
                } else {
                    func_800907A0(a, as, 0xF0, y, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
                    func_800907A0(b, bs, 0xF0, y, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
                    done = 1;
                }
            }
            if (done) {
                a->cam->flags |= 0x80;
                b->cam->flags |= 0x80;
            } else {
                a->cam->flags &= ~0x80;
                b->cam->flags |= 0x80;
            }
        }
        if (D_800EB0AA == 2 && flag == 0) {
            if (!done) {
                D_800F99BA = 0x11A;
                if (t == 0) {
                    D_800F99BA = 0x15A;
                }
            } else {
                D_800F99BA = 0;
            }
        }
    }
    return done;
}
