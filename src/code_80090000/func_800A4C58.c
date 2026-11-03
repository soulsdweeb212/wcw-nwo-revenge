/* @header
 * func_800A4C58
 * VRAM 0x800A4C58 | ROM 0x513C8 | size 0x60C
 * asm: asm/nonmatchings/code_80090000/func_800A4C58.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
typedef struct { u8 pad[0xE]; s16 h; s16 w; } T;
typedef struct { u8 pad0[0x16]; u8 f16; u8 f17; u8 pad18[8]; u16 f20; u8 pad22[0x148 - 0x22]; } Item;
typedef struct { u8 pad0[4]; void *f4; } Arg;

extern struct { u8 pad0[8]; u16 mode; } D_8007EF30;
extern s32 D_800EA220[][11];
extern u16 D_800C9200[];
extern u8 D_800D621C[], D_800D6224[];
u8 *func_800B6FE0(G **, s32);
void appendPaletteSetupDisplayList(G **);
s32 func_800AA100(s32);
T *func_800B75D4(G **, void *, s32);
T *func_800B7A00(G **, s32, s32);
void func_800A46EC(G **, s32, s32, void *);

#define SHL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define EMIT(a, b) { G *_g = g++; _g->w0 = (a); _g->w1 = (b); }
#define MODVTX(g, vtx, where, val) { G *_g = (g); _g->w0 = SHL(2, 24, 8) | SHL(where, 16, 8) | SHL((vtx) * 2, 0, 16); _g->w1 = (u32)(val); }
#define TRI_W1(v0, v1, v2) (SHL((v0) * 2, 16, 8) | SHL((v1) * 2, 8, 8) | SHL((v2) * 2, 0, 8))
#define SP2TRI(g, a0, a1, a2, b0, b1, b2) { G *_g = (g); _g->w0 = (SHL(7, 24, 8) | TRI_W1(a0, a1, a2)); _g->w1 = TRI_W1(b0, b1, b2); }

void func_800A4C58(G **dl, Item *it, Arg *arg) {
    G *g = *dl;
    s32 p = it->f20 & 3;
    s32 q = (it->f20 >> 4) & 0xF;
    T *t;
    s32 i, w;

    EMIT(0xFC5196A3, 0x112CFE7F);
    EMIT(0xFA000000, ((it->f16 * 2) / 3) & 0xFF);
    if (q & 4) {
        EMIT(0x02140002, 0x04000000);
        EMIT(0x02140036, 0x04000800);
    } else if (q & 8) {
        EMIT(0x02140000, 0x04000000);
        EMIT(0x02140034, 0x04000800);
    }
    func_800B6FE0(&g, D_800C9200[q & 3]);
    EMIT(0x07000236, 0x3634);
    if (it->f20 & 4) {
        goto end;
    }
    appendPaletteSetupDisplayList(&g);
    if (!(D_8007EF30.mode & 0x800)) {
        switch (func_800AA100(it[-1].f20 & 3)) {
        case 1:
            t = func_800B75D4(&g, D_800D621C, 0x80008000);
            break;
        case 2:
            t = func_800B75D4(&g, D_800D6224, 0x80008000);
            break;
        default:
            t = 0;
            break;
        }
        if (t) {
            EMIT(0xFA000000, (it->f17 << 24) | (it->f17 << 16) | (it->f17 << 8) | (((it->f16 * 80) / 256) & 0xFF));
            MODVTX(g++, 2, 0x14, (u32)(t->h << 21) >> 16);
            MODVTX(g++, 3, 0x14, 0);
            MODVTX(g++, 22, 0x14, ((u32)(t->h << 21) >> 16) | (t->w << 21));
            MODVTX(g++, 23, 0x14, t->w << 21);
            SP2TRI(g++, 2, 3, 23, 2, 23, 22);
        }
    }
    EMIT(0xFA000000, (it->f17 << 24) | (it->f17 << 16) | (it->f17 << 8) | it->f16);
    if (!(it->f20 & 8)) {
        t = func_800B7A00(&g, D_800EA220[p][10], 0x80000018);
        w = t->w;
        if (w < 0x50) {
            w = 0x50;
        }
        MODVTX(g++, 24, 0x14, w << 21);
        MODVTX(g++, 25, 0x14, 0);
        MODVTX(g++, 26, 0x14, (w << 21) | 0x1C0);
        MODVTX(g++, 27, 0x14, 0x1C0);
        SP2TRI(g++, 24, 25, 27, 24, 27, 26);
    }
    i = 0;
    if (D_8007EF30.mode & 0x80) {
        for (; i < 10; i++) {
            func_800A46EC(&g, D_800EA220[p][i], i, arg->f4);
        }
        goto end;
    }
    for (; i < 10; i++) {
        if ((!(it->f20 & 8) || i != 8) && (!(D_8007EF30.mode & 0x800) || i != 9)) {
            t = func_800B7A00(&g, D_800EA220[p][i], 0x80000018);
            w = t->w;
            if (w < 0x50) {
                w = 0x50;
            }
            MODVTX(g++, i * 2 + 2, 0x14, w << 21);
            MODVTX(g++, i * 2 + 3, 0x14, 0);
            MODVTX(g++, i * 2 + 4, 0x14, (w << 21) | 0x1C0);
            MODVTX(g++, i * 2 + 5, 0x14, 0x1C0);
            SP2TRI(g++, i * 2 + 2, i * 2 + 3, i * 2 + 5, i * 2 + 2, i * 2 + 5, i * 2 + 4);
        }
    }
end:
    *dl = g;
}
