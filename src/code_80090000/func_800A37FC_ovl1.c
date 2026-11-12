/* @header
 * func_800A37FC_ovl1  (originally func_800A37FC)
 * VRAM 0x800A37FC | ROM 0x4FF6C | size 0x604
 * asm: asm/nonmatchings/code_80090000/func_800A37FC_ovl1.s
 */
#include "common.h"


#ifdef TARGET_PC
typedef Gfx G; /* PC: a command is port.h's 16-byte Gfx, which keeps a whole pointer in w1 */
#else
typedef struct { u32 w0, w1; } G;
#endif
typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
typedef struct { void *dl; V *addr; u16 n; u8 padA[6]; } VtxSet;
typedef struct { u8 r, g, b; } Rgb;
typedef struct {
    u8 pad0[0x16];
    u8 f16;
    u8 pad17[9];
    u8 f20;
    u8 f21;
    u16 f22;
} Obj;

extern V *D_800E7CB4;
extern s32 D_800E7BF0[4];
extern VtxSet D_800CB7B8[];
extern Rgb D_800CCC90[];
extern Rgb D_800CCC78[];
u32 osVirtualToPhysical(V *);
s32 func_800AA0D8(s32);

#define SHL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#ifdef TARGET_PC
/* PC: the vertices' address as the whole pointer (port.h's DL_ADDR); osVirtualToPhysical returns a u32. */
#define SPVERTEX(g, v, n, v0) { G *_g = (g); _g->w0 = SHL(1, 24, 8) | SHL((n), 12, 8) | SHL((v0) + (n), 1, 7); _g->w1 = DL_ADDR(v); }
#else
#define SPVERTEX(g, v, n, v0) { G *_g = (g); _g->w0 = SHL(1, 24, 8) | SHL((n), 12, 8) | SHL((v0) + (n), 1, 7); _g->w1 = osVirtualToPhysical(v); }
#endif
#define MODVTX(g, vtx, where, val) { G *_g = (g); _g->w0 = SHL(2, 24, 8) | SHL(where, 16, 8) | SHL((vtx) * 2, 0, 16); _g->w1 = (u32)(val); }
#define TRI_W1(v0, v1, v2) (SHL((v0) * 2, 16, 8) | SHL((v1) * 2, 8, 8) | SHL((v2) * 2, 0, 8))
#define SP2TRI(g, a0, a1, a2, b0, b1, b2) { G *_g = (g); _g->w0 = (SHL(7, 24, 8) | TRI_W1(a0, a1, a2)); _g->w1 = TRI_W1(b0, b1, b2); }
#define RGBA(c) (((c)->r << 24) | ((c)->g << 16) | ((c)->b << 8) | 0xFF)
#define RGBK(k) ((D_800CCC90[k].r << 24) | (D_800CCC90[k].g << 16) | (D_800CCC90[k].b << 8) | 0xFF)
#define VTXC(X, Y, c) {                     \
    V *v = D_800E7CB4++;                    \
    v->ob[0] = (X);                         \
    v->ob[1] = (Y);                         \
    v->ob[2] = 0;                           \
    v->flag = 0;                            \
    v->tc[0] = 0;                           \
    v->tc[1] = 0;                           \
    v->cn[0] = D_800CCC78[c].r;             \
    v->cn[1] = D_800CCC78[c].g;             \
    v->cn[2] = D_800CCC78[c].b;             \
    v->cn[3] = 0xFF;                        \
}

void func_800A37FC_ovl1(G **dl, Obj *o) {
    G *g = *dl;
    /* One variable for the object id and, later, both loop counters: the ROM keeps all three in a3. */
    s32 i = o->f21;
    s32 n, x, k;

    if (D_800E7BF0[0] != i && D_800E7BF0[1] != i && D_800E7BF0[2] != i && D_800E7BF0[3] != i) {
        G *d = g++;
        d->w0 = 0xFA000000;
        d->w1 = o->f16;
    }
    n = o->f22;
    k = func_800AA0D8(i);
    SPVERTEX(g++, D_800CB7B8[14].addr, D_800CB7B8[14].n, 0);
    MODVTX(g++, 0, 0x10, RGBK(k));
    MODVTX(g++, 1, 0x10, RGBK(k));
    MODVTX(g++, 2, 0x10, RGBK(k));
    MODVTX(g++, 3, 0x10, RGBK(k));
    MODVTX(g++, 4, 0x10, RGBK(k));
    MODVTX(g++, 5, 0x10, RGBK(k));
    MODVTX(g++, 6, 0x10, RGBK(k));
    MODVTX(g++, 7, 0x10, RGBK(k));
    {
        G *d = g++;
        d->w0 = 0xDE000000;
#ifdef TARGET_PC
        /* PC: the display list's address as the whole pointer (port.h's DL_ADDR). D_800CB7B8 is overlay 1 data whose
         * 16-byte records hold two addresses, and six files read it through views of their own: its PC layout is not
         * decided yet, and this view reads it with real pointers. */
        d->w1 = DL_ADDR(D_800CB7B8[14].dl);
#else
        d->w1 = (u32)D_800CB7B8[14].dl - 0x80000000;
#endif
    }
    if (n != 0) {
        SPVERTEX(g++, D_800E7CB4, n * 4, 0);
        for (i = 0; i < n; i++) {
            x = (i - 3.5) * 10.0;
            VTXC(x - 4, -2, i);
            VTXC(x + 4, -2, i);
            VTXC(x - 4, 2, i);
            VTXC(x + 4, 2, i);
        }
        for (i = 0; i < n; i++) {
            SP2TRI(g++, i * 4, i * 4 + 1, i * 4 + 3, i * 4, i * 4 + 3, i * 4 + 2);
        }
    }
    *dl = g;
}
