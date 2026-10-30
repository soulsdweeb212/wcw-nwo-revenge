/* @header
 * func_800194B8
 * VRAM 0x800194B8 | ROM 0x1A0B8 | size 0x18C
 * asm: asm/nonmatchings/main/func_800194B8.s
 */
#include "common.h"

/* Nw2 render-object sub-state setup (messages 4/5): installs the descriptor,
 * aligns the frame count to 9, sizes the geometry, and copies the optional
 * colour/offset block into the object. Sibling of func_8001DF00. */
typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
} Nw2RenderColor;

typedef struct {
    s32 id;
    s32 frameCount;
    u8 subtype;
    u8 pad9[3];
    Nw2RenderColor *color;
    Nw2RenderColor *geometry;
} Nw2RenderDesc;

typedef struct {
    u8 pad0[0x10];
    s32 sizeArg;
    s32 color0;
    s32 color1;
    s32 color2;
    Nw2RenderDesc *desc;
    s32 geometrySize;
    u8 pad28[8];
    s32 state30;
    s32 state34;
    s32 state38;
    s32 descId;
} Nw2RenderObject;

void func_80020300(void *, s32, s32, void *);

void func_800194B8(Nw2RenderObject *o, s32 message, Nw2RenderDesc *desc) {
    Nw2RenderColor *p;
    s32 n;

    switch (message) {
    case 5:
        o->desc = desc;
        o->descId = desc->id;
        o->state30 = 0;
        switch (o->desc->subtype) {
        case 0:
            o->desc->frameCount = (o->desc->frameCount / 9) * 9;
            p = o->desc->geometry;
            n = p->f4 * 2;
            o->geometrySize = p->f0 * n * 8;
            if (o->desc->color != NULL) {
                o->color0 = o->desc->color->f0;
                o->color1 = o->desc->color->f4;
                o->color2 = o->desc->color->f8;
                func_80020300((u8 *)o->desc->color + 0xC, o->sizeArg, 0x20, o);
            } else {
                o->color2 = 0;
                o->color1 = 0;
                o->color0 = 0;
            }
            break;
        case 1:
            if (o->desc->color != NULL) {
                o->color0 = o->desc->color->f0;
                o->color1 = o->desc->color->f4;
                o->color2 = o->desc->color->f8;
            } else {
                o->color2 = 0;
                o->color1 = 0;
                o->color0 = 0;
            }
            break;
        }
        break;
    case 4:
        o->state34 = 0;
        o->state38 = 1;
        o->state30 = 0;
        if (o->desc == NULL) break;
        o->descId = o->desc->id;
        if (o->desc->subtype == 0) {
            if (o->desc->color != NULL) {
                o->color2 = o->desc->color->f8;
            }
        } else if (o->desc->subtype == 1) {
            if (o->desc->color != NULL) {
                o->color2 = o->desc->color->f8;
            }
        }
        break;
    }
}
