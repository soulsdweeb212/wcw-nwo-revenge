/* @header
 * func_800A0420
 * VRAM 0x800A0420 | ROM 0x4CB90 | size 0x2D8
 * asm: asm/nonmatchings/code_80090000/func_800A0420.s
 */
#include "common.h"

typedef struct { u32 w0; u32 w1; } Gfx0420;
typedef struct { u8 pad0[4]; s32 addr; u16 n; u8 padA[6]; } Vtx0420;
typedef struct { u8 pad0[0xE]; u8 idx; u8 padF[5]; u16 flags; } Def0420;
typedef struct {
    u8 pad0[0x14];
    union { s16 h; struct { u8 hi, lo; } b; } f14;
    u8 alpha;
    u8 f17;
    u8 pad18[4];
    f32 scale;
    u8 pad20[4];
    Def0420 *def;
    u8 pad28[0x50];
    void *dl;
    u8 pad7C[4];
    u8 f80;
    u8 pad81[3];
    s32 mtx[1];
} Obj0420;
typedef struct { f32 x, y, z; f32 rx, ry, rz; f32 s; } Pos0420;

extern Gfx0420 *D_800DC738;
extern s32 D_800E7BEC;
extern Vtx0420 D_800CB7B8[];
extern u8 D_800CCB80[];
void guPositionF(void *, f32, f32, f32, f32, f32, f32, f32);
u32 osVirtualToPhysical(s32);
void func_8009FE3C(Gfx0420 **, Obj0420 *, s32);

#define EMIT(a, b) { Gfx0420 *_g = D_800DC738++; _g->w0 = (a); _g->w1 = (b); }

void func_800A0420(Obj0420 *a, Pos0420 *p) {
    Vtx0420 *v;
    s32 unused;

    if (a->alpha != 0 && D_800E7BEC == 0) {
        a->dl = D_800DC738;
        a->f80 &= 0x7F;
        v = &D_800CB7B8[a->def->idx];
        guPositionF(a->mtx, p->rx, p->ry, p->rz, p->s * a->scale,
                                             a->scale * p->s + p->x, a->scale * p->s + p->y,
                                             a->scale * p->s + p->z);
        EMIT(0x01000000 | ((v->n & 0xFF) << 12) | ((v->n & 0x7F) << 1), osVirtualToPhysical(v->addr));
        EMIT(0xE7000000, 0);
        if (a->alpha == 0xFF && !(a->def->flags & 0x800)) {
            EMIT(0xE200001C, 0x552048);
            EMIT(0xE2001E01, 0);
        } else {
            EMIT(0xE200001C, 0x5041C8);
            EMIT(0xE2001E01, 0);
        }
        if (a->f14.h < 0x100) {
            EMIT(0xFB000000, 0xFF);
            a->f17 = ~a->f14.b.lo;
        } else {
            EMIT(0xFB000000, -1);
            a->f17 = a->f14.h;
        }
        EMIT(0xFA000000, a->alpha);
        func_8009FE3C(&D_800DC738, a, unused);
        EMIT(0xDF000000, 0);
    } else {
        a->dl = D_800CCB80;
        a->f80 |= 0x80;
    }
}
