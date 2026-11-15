/* @header
 * func_800A0420
 * VRAM 0x800A0420 | ROM 0x4CB90 | size 0x2D8
 * asm: asm/nonmatchings/code_80090000/func_800A0420.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx. Vtx0420 is an entry of D_800CB7B8 (0x10 bytes on the N64: the addresses of
 * a display list and of vertices, then the vertex count), which on PC holds pointers, as func_8009FE3C's view of it
 * has them. */
typedef Gfx Gfx0420;
typedef struct { void *dl; Vtx *addr; u16 n; u8 padA[6]; } Vtx0420;
#else
typedef struct { u32 w0; u32 w1; } Gfx0420;
typedef struct { u8 pad0[4]; s32 addr; u16 n; u8 padA[6]; } Vtx0420;
#endif
typedef struct { u8 pad0[0xE]; u8 idx; u8 padF[5]; u16 flags; } Def0420;
#ifdef TARGET_PC
/* PC: a is a menu element (0x148 bytes on the N64), which holds a scene object (common.h's Nw2SceneObj) at +0x68 on
 * the N64: its display list at +0x78, its draw group at +0x80 (bit 0x80 hides it) and its matrix from +0x84. def is a
 * pointer, 8 bytes at +0x28 on PC, so what follows it sits 8 bytes later than on the N64, as in the other PC views of
 * the element (func_800A171C's El, func_8009FE3C's Obj): the scene object at +0x70. The object keeps its N64 layout
 * and holds its display list as a handle (port.h's PTR_TO_SLOT). */
typedef struct {
    u8 pad0[0x14];
    s16 f14;
    u8 alpha;
    u8 f17;
    u8 pad18[4];
    f32 scale;
    u8 pad20[4];
    Def0420 *def;
    u8 pad30[0x68 - 0x28];
    Nw2SceneObj obj;
} Obj0420;
_Static_assert(offsetof(Obj0420, def) == 0x28 && offsetof(Obj0420, obj) == 0x70,
               "Obj0420 must place the scene object after the 8-byte def");
#else
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
#endif
typedef struct { f32 x, y, z; f32 rx, ry, rz; f32 s; } Pos0420;

extern Gfx0420 *D_800DC738;
extern s32 D_800E7BEC;
extern Vtx0420 D_800CB7B8[];
extern u8 D_800CCB80[];
void guPositionF(void *, f32, f32, f32, f32, f32, f32, f32);
#ifndef TARGET_PC /* on PC the vertices' address goes into the command through port.h's DL_ADDR */
u32 osVirtualToPhysical(s32);
#endif
void func_8009FE3C(Gfx0420 **, Obj0420 *, s32);

#define EMIT(a, b) { Gfx0420 *_g = D_800DC738++; _g->w0 = (a); _g->w1 = (b); }

void func_800A0420(Obj0420 *a, Pos0420 *p) {
    Vtx0420 *v;
    s32 unused;

    if (a->alpha != 0 && D_800E7BEC == 0) {
#ifdef TARGET_PC
        /* PC: the scene object's fields by name (see Obj0420), and the vertices' address as the whole pointer (port.h's
         * DL_ADDR); osVirtualToPhysical returns a u32. */
        a->obj.dl = PTR_TO_SLOT(D_800DC738);
        a->obj.group &= 0x7F;
        v = &D_800CB7B8[a->def->idx];
        guPositionF(a->obj.local, p->rx, p->ry, p->rz, p->s * a->scale,
                                             a->scale * p->s + p->x, a->scale * p->s + p->y,
                                             a->scale * p->s + p->z);
        EMIT(0x01000000 | ((v->n & 0xFF) << 12) | ((v->n & 0x7F) << 1), DL_ADDR(v->addr));
#else
        a->dl = D_800DC738;
        a->f80 &= 0x7F;
        v = &D_800CB7B8[a->def->idx];
        guPositionF(a->mtx, p->rx, p->ry, p->rz, p->s * a->scale,
                                             a->scale * p->s + p->x, a->scale * p->s + p->y,
                                             a->scale * p->s + p->z);
        EMIT(0x01000000 | ((v->n & 0xFF) << 12) | ((v->n & 0x7F) << 1), osVirtualToPhysical(v->addr));
#endif
        EMIT(0xE7000000, 0);
        if (a->alpha == 0xFF && !(a->def->flags & 0x800)) {
            EMIT(0xE200001C, 0x552048);
            EMIT(0xE2001E01, 0);
        } else {
            EMIT(0xE200001C, 0x5041C8);
            EMIT(0xE2001E01, 0);
        }
#ifdef TARGET_PC
        /* PC: the N64 reads the s16's second byte, its low byte in the N64's byte order; on PC that is (u8)f14
         * (docs/port.md, "Byte order on PC"). The colour word as 32 bits. */
        if (a->f14 < 0x100) {
            EMIT(0xFB000000, 0xFF);
            a->f17 = ~(u8)a->f14;
        } else {
            EMIT(0xFB000000, 0xFFFFFFFF);
            a->f17 = a->f14;
        }
#else
        if (a->f14.h < 0x100) {
            EMIT(0xFB000000, 0xFF);
            a->f17 = ~a->f14.b.lo;
        } else {
            EMIT(0xFB000000, -1);
            a->f17 = a->f14.h;
        }
#endif
        EMIT(0xFA000000, a->alpha);
        func_8009FE3C(&D_800DC738, a, unused);
        EMIT(0xDF000000, 0);
    } else {
#ifdef TARGET_PC
        /* PC: as above; the element is hidden, so the list D_800CCB80 is not drawn. */
        a->obj.dl = PTR_TO_SLOT(D_800CCB80);
        a->obj.group |= 0x80;
#else
        a->dl = D_800CCB80;
        a->f80 |= 0x80;
#endif
    }
}
