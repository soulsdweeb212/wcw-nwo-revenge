/* @header
 * func_80004BA8
 * VRAM 0x80004BA8 | ROM 0x57A8 | size 0xE8
 * asm: asm/nonmatchings/main/func_80004BA8.s
 */
#include "common.h"

extern void func_8000498C(void *, s16);
extern void func_800015AC(void *, s8);
extern void func_80001544(void *);

#ifndef TARGET_PC /* on PC the definition reads Nw2Descr4BA8, Nw2SceneObj and Nw2SceneWork (common.h) instead */
typedef struct {
    u8 pad0[2];
    s8 f2;
    s8 f3;
    u8 pad4[2];
    u8 f6;
    u8 pad7[5];
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
} Nw2Def;

typedef struct {
    s32 f0;
    u8 pad0[0x28];
    s16 f2C;
    s16 f2E;
    s32 f30;
    s32 f34;
} Nw2Sub;
#endif

/* Initialise entity arg0 from definition src: stash arg2 in the definition, run
 * func_8000498C, copy the appearance fields into arg0, reset it, fill the
 * sub-struct (at arg0+0x14) with the definition's state/frame/size values, then
 * stamp the three positional/behaviour parameters onto arg0. */
#ifdef TARGET_PC
/* PC: the types of port_decls.h's line. The record (Nw2Def above) is the display record, whose PC layout is
 * Nw2Descr4BA8 (common.h): its addresses are pointers, so the arena goes into f28 as a pointer. The object and its work
 * block keep their N64 layout (Nw2SceneObj and Nw2SceneWork in common.h), so their 4-byte address fields take handles
 * (port.h's PTR_TO_SLOT): the vertices, the display list (f10, or else f14, when one is set), and the three objects the
 * callers pass for +0x0, +0x4 and +0x8 (parent, child and next). The object's work block is read back with
 * SLOT_TO_PTR. */
void func_80004BA8(void *obj, void *rec, void *arena, s16 id, void *parent, void *child, void *next)
{
    Nw2SceneObj *o = obj;
    Nw2Descr4BA8 *src = rec;
    Nw2SceneWork *p;

    src->f28 = arena;
    func_8000498C(src, id);
    o->lit = src->f6;
    o->vtx = PTR_TO_SLOT(src->fC);
    func_800015AC(o, src->f2);
    p = SLOT_TO_PTR(o->work);
    p->kind = 1;
    p->vtx = PTR_TO_SLOT(src->fC);
    p->count = src->f2;
    p->start = src->f3;
    if (src->f10 != NULL) {
        p->dl = PTR_TO_SLOT(src->f10);
    } else if (src->f14 != NULL) {
        p->dl = PTR_TO_SLOT(src->f14);
    }
    func_80001544(o);
    o->parent = PTR_TO_SLOT(parent);
    o->child = PTR_TO_SLOT(child);
    o->next = PTR_TO_SLOT(next);
}
#else
void func_80004BA8(u8 *arg0, Nw2Def *src, s32 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6)
{
    Nw2Sub *p;

    src->f28 = arg2;
    func_8000498C(src, arg3);
    arg0[0x1A] = src->f6;
    *(s32 *)(arg0 + 0xC) = src->fC;
    func_800015AC(arg0, src->f2);
    p = *(Nw2Sub **)(arg0 + 0x14);
    p->f0 = 1;
    p->f30 = src->fC;
    p->f2C = src->f2;
    p->f2E = src->f3;
    if (src->f10 != 0) {
        p->f34 = src->f10;
    } else if (src->f14 != 0) {
        p->f34 = src->f14;
    }
    func_80001544(arg0);
    *(s32 *)(arg0 + 0) = arg4;
    *(s32 *)(arg0 + 4) = arg5;
    *(s32 *)(arg0 + 8) = arg6;
}
#endif
