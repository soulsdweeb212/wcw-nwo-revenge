/* @header
 * func_800900C0
 * VRAM 0x800900C0 | ROM 0x3C830 | size 0x240
 * asm: asm/nonmatchings/code_80090000/func_800900C0.s
 */
#include "common.h"

extern u8 D_800DB348[];
extern u8 D_800D6658[];
extern u8 D_800C5AD0[];
extern u8 D_800C5C50[];
#ifdef TARGET_PC
/* PC: the display list at 0x800C5B90 by its own address (port.h's DL_ADDR turns it into the command word; D_C5B90 is
 * its N64 physical address, a link constant). */
extern u8 D_800C5B90[];
#else
extern u8 D_C5B90[];
#endif
void initializeTransformNode(void *, s32, f32, f32, f32);
void func_800015AC(void *, s32);
void func_80001544(void *);

#ifdef TARGET_PC
typedef Gfx Gx; /* PC: a command is port.h's 16-byte Gfx */
#else
typedef struct { u32 w0, w1; } Gx;
#endif
#define CMD(p, a, b) { Gx *_g = (Gx *)(p); _g->w0 = (a); _g->w1 = (b); }

#ifdef TARGET_PC
/* PC: the objects are scene objects (common.h's Nw2SceneObj), which keep their N64 layout on PC, so their address
 * fields hold handles (port.h's PTR_TO_SLOT): the parent (+0), the next sibling (+8), the vertices (+0xC) and the
 * display list (+0x10); the work block (+0x14, a Nw2SceneWork whose depth bias is at +0x24) is reached through
 * SLOT_TO_PTR. arg0 is the parent's address (func_800C4D70 passes D_800DF4C0), so a pointer.
 * The 48 records at D_800D6658 + 0x6F8 are 0x178 bytes: an object, then at +0xE0 and +0x120 a display list per frame
 * bank (func_80090384 points the object's display list at one of them), then the effect's fields from +0x160. Each
 * list has 0x40 bytes of room and gets 4 commands: 0x20 bytes of the N64's 8-byte commands, exactly 0x40 bytes of
 * 16-byte Gfx on PC, so the record keeps its layout. */
_Static_assert(0x120 + 4 * sizeof(Gx) == 0x160, "two lists of 4 Gfx fit between +0xE0 and +0x160 of a 0x178-byte record");
void func_800900C0(void *arg0) {
    Nw2SceneObj *p;
    u8 *q;
    Nw2SceneObj *o;
    s32 i;
    f32 z;
    Gx *dl;

    i = 0;
    p = (Nw2SceneObj *)(D_800DB348 + 0x88);
    do {
        if (i < 2) {
            initializeTransformNode(p, 0, 0.0f, 0.0f, 0.0f);
        } else {
            initializeTransformNode(p, 6, 0.0f, 0.0f, 0.0f);
        }
        p->vtx = PTR_TO_SLOT(D_800C5AD0);
        p->dl = PTR_TO_SLOT(D_800C5C50);
        func_800015AC(p, 1);
        func_80001544(p);
        if (i == 1) {
            ((Nw2SceneWork *)SLOT_TO_PTR(p->work))->bias = -8192.0f;
        } else {
            ((Nw2SceneWork *)SLOT_TO_PTR(p->work))->bias = 8192.0f;
        }
        p->parent = PTR_TO_SLOT(arg0);
        if (i < 2) {
            p->next = PTR_TO_SLOT(p + 1);
        }
        i++;
        p++;
    } while (i < 3);

    i = 0;
    q = D_800D6658 + 0x6F8;
    z = 0.0f;
    do {
        o = (Nw2SceneObj *)q;
        initializeTransformNode(q, 6, z, z, z);
        o->vtx = PTR_TO_SLOT(D_800C5AD0);
        o->dl = PTR_TO_SLOT(D_800C5C50);
        func_800015AC(q, 1);
        func_80001544(q);
        o->group |= 0x80;
        o->parent = PTR_TO_SLOT(arg0);
        if (i < 0x2F) {
            o->next = PTR_TO_SLOT(q + 0x178);
        }
        i++;
        dl = (Gx *)(q + 0xe0);
        CMD(dl++, 0xe7000000, 0);
        CMD(dl++, 0xfa000000, 0);
        CMD(dl++, 0xde000000, DL_ADDR(D_800C5B90));
        CMD(dl++, 0xdf000000, 0);
        dl = (Gx *)(q + 0x120);
        CMD(dl++, 0xe7000000, 0);
        CMD(dl++, 0xfa000000, 0);
        CMD(dl++, 0xde000000, DL_ADDR(D_800C5B90));
        CMD(dl++, 0xdf000000, 0);
        *(s16 *)(q + 0x160) = -1;
        *(s16 *)(q + 0x170) = 0;
        *(s16 *)(q + 0x162) = 0;
        *(s16 *)(q + 0x166) = 0;
        q += 0x178;
    } while (i < 0x30);
}
#else
void func_800900C0(s32 arg0) {
    u8 *p;
    u8 *q;
    s32 i;
    f32 z;
    s16 m;
    Gx *dl;
    u8 pad[0x3c];

    i = 0;
    p = D_800DB348 + 0x88;
    do {
        if (i < 2) {
            initializeTransformNode(p, 0, 0.0f, 0.0f, 0.0f);
        } else {
            initializeTransformNode(p, 6, 0.0f, 0.0f, 0.0f);
        }
        *(void **)(p + 0xC) = D_800C5AD0;
        *(void **)(p + 0x10) = D_800C5C50;
        func_800015AC(p, 1);
        func_80001544(p);
        if (i == 1) {
            *(f32 *)(*(u8 **)(p + 0x14) + 0x24) = -8192.0f;
        } else {
            *(f32 *)(*(u8 **)(p + 0x14) + 0x24) = 8192.0f;
        }
        *(s32 *)p = arg0;
        if (i < 2) {
            *(u8 **)(p + 8) = p + 0xDC;
        }
        i++;
        p += 0xDC;
    } while (i < 3);

    i = 0;
    q = D_800D6658 + 0x6F8;
    z = 0.0f;
    do {
        initializeTransformNode(q, 6, z, z, z);
        *(void **)(q + 0xC) = D_800C5AD0;
        *(void **)(q + 0x10) = D_800C5C50;
        func_800015AC(q, 1);
        func_80001544(q);
        *(u8 *)(q + 0x18) = *(u8 *)(q + 0x18) | 0x80;
        *(s32 *)q = arg0;
        if (i < 0x2F) {
            *(u8 **)(q + 8) = q + 0x178;
        }
        i++;
        dl = (Gx *)(q + 0xe0);
        CMD(dl++, 0xe7000000, 0);
        CMD(dl++, 0xfa000000, 0);
        CMD(dl++, 0xde000000, D_C5B90);
        CMD(dl++, 0xdf000000, 0);
        dl = (Gx *)(q + 0x120);
        CMD(dl++, 0xe7000000, 0);
        CMD(dl++, 0xfa000000, 0);
        CMD(dl++, 0xde000000, D_C5B90);
        CMD(dl++, 0xdf000000, 0);
        m = -1;
        *(s16 *)(q + 0x160) = m;
        m = 0;
        *(s16 *)(q + 0x170) = m;
        *(s16 *)(q + 0x162) = 0;
        *(s16 *)(q + 0x166) = 0;
        q += 0x178;
    } while (i < 0x30);
}
#endif
