/* @header
 * func_800A73AC
 * VRAM 0x800A73AC | ROM 0x53B1C | size 0x418
 * asm: asm/nonmatchings/code_80090000/func_800A73AC.s
 */
#include "common.h"


#ifdef TARGET_PC
typedef Gfx G; /* PC: a command is port.h's 16-byte Gfx */
#else
typedef struct { u32 w0, w1; } G;
#endif
typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
typedef struct { u8 pad0[0xA]; u16 flags; s8 idx; u8 padD[0x14]; u8 col; } Item;
#ifdef TARGET_PC
/* PC: s is an entry of D_800CB7B8 (func_8009FE3C passes it; 0x10 bytes on the N64: the addresses of a display list
 * and of vertices, then the vertex count), which holds pointers on PC, as func_8009FE3C's view of it has them. */
typedef struct { void *dl; V *v; } Spr;
#else
typedef struct { u8 pad0[4]; V *v; } Spr;
#endif
extern V *D_800E7CB4;
extern u16 D_800E7C84[];
u32 osVirtualToPhysical(V *);

#define EMIT(a, b) { G *_g = g++; _g->w0 = (a); _g->w1 = (b); }

void func_800A73AC(G **dl, Item *it, Spr *s) {
    G *g = *dl;
    V *src = s->v;
    s32 r, gr, b, i;
    u32 c1;

    EMIT(0xE7000000, 0);
    EMIT(0xFC51FEA3, 0x44FE773B);
    if (!(it->flags & 0x53)) {
        s32 n = it->idx;
#ifdef TARGET_PC
        /* PC: the vertices' address as the whole pointer (port.h's DL_ADDR); osVirtualToPhysical returns a u32. */
        EMIT(0x01004008, DL_ADDR(D_800E7CB4));
#else
        EMIT(0x01004008, osVirtualToPhysical(D_800E7CB4));
#endif
        {
            V *v = D_800E7CB4++;
            V *q = &src[n * 4 + 0];
            v->ob[0] = q->ob[0] - 1;
            v->ob[1] = q->ob[1] - 1;
            v->ob[2] = q->ob[2];
            v->flag = 0;
            v->tc[0] = q->tc[0];
            v->tc[1] = q->tc[1];
            v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
        }
        {
            V *v = D_800E7CB4++;
            V *q = &src[n * 4 + 1];
            v->ob[0] = q->ob[0] + 1;
            v->ob[1] = q->ob[1] - 1;
            v->ob[2] = q->ob[2];
            v->flag = 0;
            v->tc[0] = q->tc[0];
            v->tc[1] = q->tc[1];
            v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
        }
        {
            V *v = D_800E7CB4++;
            V *q = &src[n * 4 + 2];
            v->ob[0] = q->ob[0] - 1;
            v->ob[1] = q->ob[1] + 1;
            v->ob[2] = q->ob[2];
            v->flag = 0;
            v->tc[0] = q->tc[0];
            v->tc[1] = q->tc[1];
            v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
        }
        {
            V *v = D_800E7CB4++;
            V *q = &src[n * 4 + 3];
            v->ob[0] = q->ob[0] + 1;
            v->ob[1] = q->ob[1] + 1;
            v->ob[2] = q->ob[2];
            v->flag = 0;
            v->tc[0] = q->tc[0];
            v->tc[1] = q->tc[1];
            v->cn[0] = 0xFF; v->cn[1] = 0xFF; v->cn[2] = 0xFF; v->cn[3] = 0xFF;
        }
        EMIT(0x07000206, 0x604);
    }
#ifdef TARGET_PC
    EMIT(0x01004010, DL_ADDR(&src[60])); /* PC: as above */
#else
    EMIT(0x01004010, osVirtualToPhysical(&src[60]));
#endif
    i = D_800E7C84[it->col];
    r = (u32)i >> 11;
    gr = ((u32)i >> 6) & 0x1F;
    b = ((u32)i >> 1) & 0x1F;
    c1 = (r << 27) | (gr << 19) | (b << 11) | 0xFF;
    EMIT(0x02100008, ((r * 16 / 3) << 24) | (((gr * 16 / 3) & 0xFF) << 16) | (((b * 16 / 3) & 0xFF) << 8) | 0xFF);
    EMIT(0x0210000A, c1);
    EMIT(0x0210000C, c1);
    EMIT(0x0210000E, ((r * 16 / 3) << 24) | (((gr * 16 / 3) & 0xFF) << 16) | (((b * 16 / 3) & 0xFF) << 8) | 0xFF);
    EMIT(0x07080A0E, 0x00080E0C);
    for (i = 0; i < 15; i++) {
#ifdef TARGET_PC
        EMIT(0x01004008, DL_ADDR(&src[i * 4])); /* PC: as above */
#else
        EMIT(0x01004008, osVirtualToPhysical(&src[i * 4]));
#endif
        EMIT(0x07000206, 0x604);
    }
    *dl = g;
}
