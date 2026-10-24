#include "common.h"

typedef struct { u32 w0, w1; } Gfx2454;

typedef struct Obj2454 {
    s32 key;
    void *model;
    struct Obj2454 *next;
    u8 pad0C[0x20];
    s16 count;
    s16 start;
    void *vtx;
    u32 dl;
    f32 mtx[4][4][4];
} Obj2454;

extern Obj2454 *D_80047070[][512];
extern s16 D_80047066;
u32 func_8001CE80(void *);

s16 func_80002454(Gfx2454 **gfx, s16 bank, s16 first)
{
    u32 i;
    s32 key;
    Obj2454 *p;
    u32 addr;
    u32 n;
    u32 start;

    key = D_80047070[bank][first]->key;
    for (i = first; i < (u32)D_80047066; i++) {
        p = D_80047070[bank][i];
        if (p->key != key) {
            break;
        }
        for (; p != NULL; p = p->next) {
            {
                Gfx2454 *g = *gfx;
                *gfx = g + 1;
                g->w0 = 0xDC38000E;
                g->w1 = (u32)p->mtx[bank] - 0x80000000;
            }
            {
                Gfx2454 *g = *gfx;
                *gfx = g + 1;
                g->w0 = 0xDB0C0000;
                g->w1 = 0x10000;
            }
            if (p->vtx != NULL) {
                addr = func_8001CE80(p->vtx);
                n = p->count;
                start = p->start;
                while (n > 32) {
                    Gfx2454 *g = *gfx;
                    *gfx = g + 1;
                    g->w0 = 0x01020000 | (((start + 32) & 0x7F) << 1);
                    g->w1 = addr;
                    start += 32;
                    n -= 32;
                    addr += 0x200;
                }
                {
                    Gfx2454 *g = *gfx;
                    *gfx = g + 1;
                    g->w0 = 0x01000000 | ((n & 0xFF) << 12) | (((start + n) & 0x7F) << 1);
                    g->w1 = addr;
                }
            }
        }
        for (p = D_80047070[bank][i]; p != NULL; p = p->next) {
            if (p->dl != 0) {
                Gfx2454 *g = *gfx;
                *gfx = g + 1;
                g->w0 = 0xDE000000;
                g->w1 = p->dl - 0x80000000;
            }
        }
    }
    return i;
}
