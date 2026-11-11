/* @header
 * func_8000FAF8
 * VRAM 0x8000FAF8 | ROM 0x106F8 | size 0x23C
 * asm: asm/nonmatchings/main/func_8000FAF8.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: an Elem is a work block and a Slot a scene object (Nw2SceneWork and Nw2SceneObj, common.h), which keep their N64
 * layout on PC, so their address fields are 4-byte handles (port.h's PTR_TO_SLOT): the work block's vertices (f30),
 * and the object's vertices (fC), display list (f10) and work block (f14). The asserts check both views. */
typedef struct { s32 f0; u8 pad4[8]; f32 fC; f32 f10; u8 pad14[0x18]; s16 f2C; s16 f2E; u32 f30; } Elem;
_Static_assert(offsetof(Elem, f0) == offsetof(Nw2SceneWork, kind) &&
                   offsetof(Elem, fC) == offsetof(Nw2SceneWork, center) &&
                   offsetof(Elem, f2C) == offsetof(Nw2SceneWork, count) &&
                   offsetof(Elem, f2E) == offsetof(Nw2SceneWork, start) &&
                   offsetof(Elem, f30) == offsetof(Nw2SceneWork, vtx),
               "Elem must follow Nw2SceneWork");
#else
typedef struct { s32 f0; u8 pad4[8]; f32 fC; f32 f10; u8 pad14[0x18]; s16 f2C; s16 f2E; void *f30; } Elem;
#endif
typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } Vtx16;
#ifdef TARGET_PC
typedef struct { u8 pad0[0xC]; u32 fC; u32 f10; u32 f14; u8 rest[0xDC - 0x18]; } Slot;
_Static_assert(offsetof(Slot, fC) == offsetof(Nw2SceneObj, vtx) && offsetof(Slot, f10) == offsetof(Nw2SceneObj, dl) &&
                   offsetof(Slot, f14) == offsetof(Nw2SceneObj, work) && sizeof(Slot) == sizeof(Nw2SceneObj),
               "Slot must follow Nw2SceneObj");
#else
typedef struct { u8 pad0[0xC]; Vtx16 *fC; void *f10; Elem *f14; u8 rest[0xDC - 0x18]; } Slot;
#endif
#ifdef TARGET_PC
/* PC: each entry of D_8005A100 holds six element addresses and then eight s16 heights (func_8000F710's Tab, which
 * fills the heights and reads both). This view covers the N64's 40 bytes with ten addresses, of which it writes the
 * first six. On PC an address takes 8 bytes, so the view follows Tab's fields, and the entries step by its size. */
typedef struct { Elem *e[6]; s16 v[8]; } ElemTab;
_Static_assert(offsetof(ElemTab, e) == 0 && offsetof(ElemTab, v) == 6 * sizeof(void *) &&
                   sizeof(ElemTab) == 6 * sizeof(void *) + 8 * sizeof(s16),
               "ElemTab: e[6] at +0, v[8] after it, as func_8000F710's Tab");
#else
typedef struct { Elem *e[10]; } ElemTab;
#endif
extern Slot D_80059D90[];
extern ElemTab D_8005A100[];
extern s8 D_80036D20[4];
extern u8 D_80036D24[4];
extern void *allocateHeap(u32);
extern s32 func_80001544(void *);
extern s32 func_800015AC(void *, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_8000F710 */
extern void func_8000F710(void *, s32);
#endif
extern void buildFadeColorDisplayList(void *);
extern s32 guRandom(void);

void func_8000FAF8(s32 idx) {
    Slot *s;
    Elem *e;
    Vtx16 *v;
    void *dl;
    s32 i;
    s16 row;
    u32 j, k;
    s32 x;
    s32 u;
#ifdef TARGET_PC
    /* PC: the vertex block, kept as a pointer: the object gets its handle, each work block that of its own part. */
    u8 *vb;
#endif

    s = &D_80059D90[idx];
#ifdef TARGET_PC
    /* PC: handles in the object (see Slot). The display list holds the N64's 0x200 / 8 commands, each sizeof(Gfx). */
    vb = allocateHeap(0x540);
    s->fC = PTR_TO_SLOT(vb);
    dl = allocateHeap(0x200 / 8 * sizeof(Gfx));
    s->f10 = PTR_TO_SLOT(dl);
#else
    s->fC = allocateHeap(0x540);
    dl = allocateHeap(0x200);
    s->f10 = dl;
#endif
    buildFadeColorDisplayList(dl);
    for (i = 0; i < 6; i++) {
#ifdef TARGET_PC
        /* PC: handles, as above; 0 stands for none, so func_800015AC hands out a new work block. */
        s->f14 = 0;
        func_800015AC(s, 0);
        func_80001544(s);
        e = SLOT_TO_PTR(s->f14);
#else
        s->f14 = NULL;
        func_800015AC(s, 0);
        func_80001544(s);
        e = s->f14;
#endif
        e->f0 = 1;
        e->f2C = 0x18;
        e->f2E = 0;
#ifdef TARGET_PC
        e->f30 = PTR_TO_SLOT(vb + i * 0xC0);
#else
        e->f30 = (u8 *)s->fC + i * 0xC0;
#endif
        e->fC = -187 + i * 74;
        e->f10 = 180.0f;
        D_8005A100[idx].e[i] = e;
    }
#ifdef TARGET_PC
    v = (Vtx16 *)vb;
#else
    v = s->fC;
#endif
    for (row = 0; row < 7; row++) {
        x = row * 74 - 0xE0;
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 4; k++) {
                v->ob[0] = x;
                u = guRandom() % 8 + 0xE0;
                v->tc[0] = (x + u) << 5;
                v->tc[1] = D_80036D20[k] << 5;
                v->cn[0] = D_80036D24[k];
                v->cn[1] = D_80036D24[k];
                v->cn[2] = D_80036D24[k];
                v->cn[3] = 0xFF;
                v++;
            }
        }
    }
#ifdef TARGET_PC
    /* PC: func_8000F710 takes the vertices as u8 *, its definition's type (port_decls.h); the N64 line passes them
     * through its own void * parameter. The object holds their handle, so the PC passes the pointer it kept. */
    func_8000F710(vb, idx);
#else
    func_8000F710(s->fC, idx);
#endif
}
