/* @header
 * func_800C0680
 * VRAM 0x800C0680 | ROM 0x6CDF0 | size 0x55C
 * asm: asm/nonmatchings/code_80090000/func_800C0680.s
 */
#include "common.h"

typedef struct { u8 pad0[2]; u16 w; u16 h; u8 pad6[2]; u16 w2; } Pic;
#ifdef TARGET_PC
/* PC: D_800E7558 holds four 0xEC-byte layers, which func_8009F8BC steps by 0xEC: a 0xDC-byte scene object (common.h's
 * Nw2SceneObj, which keeps its N64 layout on PC and holds handles), then the picture's fields (func_8009EC58's P). So a
 * layer keeps its N64 layout too, and the address of its picture at +0xDC is a 4-byte handle (port.h's PTR_TO_SLOT),
 * which func_8009EC58 and func_8009C218 turn back with SLOT_TO_PTR. The picture sets D_800D4930 hold addresses, so
 * they have their PC layout (common.h's Nw2MenuShot). */
typedef struct {
    Nw2SceneObj obj;
    u32 pic;
    s16 x;
    s16 y;
    u16 scale;
    s16 alpha;
    u16 flags;
    s16 fEA;
} Layer;
_Static_assert(offsetof(Layer, pic) == 0xDC && offsetof(Layer, x) == 0xE0 && offsetof(Layer, fEA) == 0xEA &&
                   sizeof(Layer) == 0xEC,
               "a layer of D_800E7558 keeps its N64 layout on PC");
typedef Nw2MenuShot Shot;
#else
typedef struct {
    u8 pad0[0xDC];
    Pic *pic;
    s16 x;
    s16 y;
    u16 scale;
    s16 alpha;
    u16 flags;
    s16 fEA;
} Layer;
typedef struct { Pic *pic[4]; u16 n[4]; u8 pad18[8]; } Shot;
#endif

extern Layer D_800E7558[];
extern Shot D_800D4930[];
extern s32 D_800E79C4;
extern s32 D_800EA0B4;
extern s32 D_800DF304;

void func_800C0680(s32 a) {
    s32 i;
    Shot *t;
    Layer *c;
    Pic *p;
    s32 k;
    s32 start;

    t = &D_800D4930[D_800E79C4];
    c = D_800E7558;
    for (i = 0; i < 4; i++, c++) {
        c->flags &= ~3;
        p = t->pic[i];
        if (p == 0) {
            c->flags = 0;
            continue;
        }
#ifdef TARGET_PC
        c->pic = PTR_TO_SLOT(p); /* PC: as a handle (see above) */
#else
        c->pic = p;
#endif
        if (t->n[i] > D_800EA0B4) {
            c->flags |= 2;
        } else {
            c->flags |= 1;
        }
        c->x = 0;
        c->y = -a;
        c->alpha = a;
        c->scale = 0x100;
        switch (D_800E79C4) {
        case 1:
            start = i * 0x60 + 0x3C;
            if (a < 0x3C) {
                if (i == 0) {
                    c->alpha = 0xFF;
                } else {
                    c->alpha = 0;
                }
            } else {
                D_800DF304 = 1;
                k = a - start + 0x40;
                if (k < 0 || k >= 0x80) {
                    c->alpha = 0;
                } else if (k < 0x20) {
                    c->alpha = k * 8;
                } else if (k >= 0x60) {
                    c->alpha = (0x7F - k) * 8;
                } else {
                    c->alpha = 0xFF;
                }
            }
            c->y = 0;
            break;
        case 2:
            if (i == 3) {
                c->y = 0;
                if (a < 0x40) {
                    c->alpha = (0x3F - a) * 4;
                } else {
                    c->alpha = 0;
                }
            } else {
                c->y = 0;
                c->alpha = 0;
            }
            break;
        case 5:
            c->scale = (240 - a) * 256 / 120 + 0x100;
            c->x = (480 - c->scale * 480 / 256) * 320 / 480;
            c->y = (240 - c->scale * 240 / 256) * 187 / 240;
            c->alpha = 0;
            break;
        case 6:
            c->scale = (240 - a) * 256 / 120 + 0x100;
            c->x = (480 - c->scale * 480 / 256) / 2;
            c->y = (240 - c->scale * 240 / 256) * 187 / 240;
            c->alpha = 0;
            break;
        case 8:
            c->scale = 0x100;
            c->x = a * 8 - 0x170;
            c->y = 0;
            break;
        case 9:
            c->scale = 0x100;
            c->x = 0x170 - a * 8;
            c->y = 0;
            break;
        case 10:
        case 12:
        case 20:
            c->scale = a;
            c->x = 0;
            c->y = 0;
            break;
        case 13:
            c->x = a - 0xC0;
            c->y = 0xC0 - a;
            break;
        case 14:
            c->x = 0xC0 - a;
            c->y = 0xC0 - a;
            break;
        case 17:
        case 22:
            c->scale = a * 8;
#ifdef TARGET_PC
            /* PC: p is the layer's picture, which c->pic holds as a handle (above). */
            c->x = (480 - c->scale * (p->w * 480 / 320) / 256) / 2;
            c->y = (240 - c->scale * p->h / 256) / 4;
#else
            c->x = (480 - c->scale * (c->pic->w * 480 / 320) / 256) / 2;
            c->y = (240 - c->scale * c->pic->h / 256) / 4;
#endif
            c->alpha = 0;
            break;
        case 18:
            c->y = a - 0x190;
            break;
        case 23:
            if (i == 1) {
                if (a < 0x40) {
                    c->scale = c->alpha = a * 4;
                } else if (a > 0xC0) {
                    c->alpha = (0x100 - a) * 4;
                    c->scale = 0x100;
                } else {
                    c->alpha = 0xFF;
                    c->scale = 0x100;
                }
            }
            break;
        case 24:
            c->x = 0;
            c->alpha = a;
            c->y = 0;
            break;
        case 25:
            switch (i) {
            case 0:
                c->x = -a;
                c->y = 0;
                c->alpha = 0xFF;
                break;
            case 1:
                c->x = a;
                c->y = 0;
                c->alpha = 0xFF;
                break;
            case 3:
                c->scale = a;
#ifdef TARGET_PC
                /* PC: as above. */
                c->x = (480 - c->scale * p->w2 / 256) / 2;
                c->y = (240 - c->scale * p->h / 256) / 2;
#else
                c->x = (480 - c->scale * c->pic->w2 / 256) / 2;
                c->y = (240 - c->scale * c->pic->h / 256) / 2;
#endif
                break;
            }
            break;
        }
    }
}
