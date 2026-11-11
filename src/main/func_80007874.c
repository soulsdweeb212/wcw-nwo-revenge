/* @header
 * func_80007874
 * VRAM 0x80007874 | ROM 0x8474 | size 0xAC
 * asm: asm/nonmatchings/main/func_80007874.s
 */
#include "common.h"

void func_800015AC(void *, s8);

/* Initializes the object and its sub-record from descriptor arg3, copying the
 * packed descriptor bytes into the sub-record's size/offset fields. */
#ifdef TARGET_PC
/* PC: the object keeps its N64 layout (Nw2SceneObj, common.h), and so does its work block (Nw2SceneWork), so their
 * address fields hold handles (port.h's PTR_TO_SLOT). recs is an array of display records (Nw2Descr4BA8), stepped by
 * its PC size. As on the N64: the object gets the record's light flag, its vertices and a work block (func_800015AC);
 * the block becomes a mesh (kind 1) that loads the record's f2 vertices into vertex slot f3 and draws dl. */
void func_80007874(void *object, void *recs, void *dl, s16 index) {
    Nw2SceneObj *obj = object;
    Nw2Descr4BA8 *t = (Nw2Descr4BA8 *)recs + index;
    Nw2SceneWork *p;

    obj->lit = t->f6;
    obj->vtx = PTR_TO_SLOT(t->fC);
    func_800015AC(obj, t->f2);
    p = SLOT_TO_PTR(obj->work);
    p->kind = 1;
    p->vtx = 0;
    p->dl = 0;
    p->count = t->f2;
    p->start = t->f3;
    p->dl = PTR_TO_SLOT(dl);
    p->vtx = PTR_TO_SLOT(t->fC);
}
#else
void func_80007874(u8 *arg0, s32 arg1, s32 arg2, s16 arg3) {
    u8 *t = (u8 *)(arg3 * 0x2C + arg1);
    s32 *p;
    s32 v;

    arg0[0x1A] = t[6];
    *(s32 *)(arg0 + 0xC) = *(s32 *)(t + 0xC);
    func_800015AC(arg0, t[2]);
    p = *(s32 **)(arg0 + 0x14);
    p[0] = 1;
    p[0xC] = 0;
    p[0xD] = 0;
    *(s16 *)((u8 *)p + 0x2C) = (s8)t[2];
    *(s16 *)((u8 *)p + 0x2E) = (s8)t[3];
    v = *(s32 *)(t + 0xC);
    *(s32 *)((u8 *)p + 0x34) = arg2;
    *(s32 *)((u8 *)p + 0x30) = v;
}
#endif
