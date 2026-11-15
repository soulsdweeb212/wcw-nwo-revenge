/* @header
 * func_80092DE0
 * VRAM 0x80092DE0 | ROM 0x3F550 | size 0x8FC
 * asm: asm/nonmatchings/code_80090000/func_80092DE0.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx, which func_80091908, func_80091C48, func_80091F50, func_80092230 and
 * func_80092B20 also write on PC, and every address goes into its command as the whole pointer (port.h's DL_ADDR); the
 * N64 writes 32-bit words. The records hold addresses, so on PC they hold pointers:
 * - S2DE0 is an encounter of D_800DB8C0 (common.h's Nw2Encounter): the addresses of its spot (f0), of its scene
 *   object (f4) and of its record of D_800C6508 (f8), then the kind (fC) and its counters and colour.
 * - Sub2DE0a is the spot (common.h's Nw2EncSpot), a 16-bit value at +6 whose low byte the N64 reads as a byte at +7:
 *   tools/port_data.py converts the spots as 16-bit values, so the PC takes the byte from the value ((u8)f6).
 * - Sub2DE0b is a record of D_800C6508 in overlay 1's data (16 bytes on the N64: the addresses of a display list and
 *   of its vertices, two u16 (the second the picture's index in the texture pack), four bytes); 0x18 bytes on PC.
 * D_800DB69C holds the address of the menu's picture pack (a heap block, func_800936DC allocates it), and
 * func_800B600C (port_decls.h) hands back resource 0x3B's heap block; func_800B64EC takes and returns addresses in
 * such a block (its definition's u8 *). D_800DBD44 holds the address of a display list built here (case 4), which a
 * later encounter branches to, so on PC it is a pointer. */
typedef Nw2EncSpot Sub2DE0a;

typedef struct {
    Gfx *dl;
    Vtx *vtx;
    u16 f8;
    u16 fA;
    u8 fC[4];
} Sub2DE0b;
_Static_assert(offsetof(Sub2DE0b, f8) == offsetof(Nw2PicShape, count) &&
                   offsetof(Sub2DE0b, fA) == offsetof(Nw2PicShape, tile) && sizeof(Sub2DE0b) == sizeof(Nw2PicShape),
               "Sub2DE0b must follow common.h's Nw2PicShape");

typedef struct {
    Sub2DE0a *f0;
    void *f4;
    Sub2DE0b *f8;
    u16 fC;
    u8 padE[2];
    u16 f10;
    u16 f12;
    u8 f14;
    u8 f15;
    u8 f16;
    u8 f17;
} S2DE0;
_Static_assert(sizeof(S2DE0) == sizeof(Nw2Encounter) && offsetof(S2DE0, f4) == offsetof(Nw2Encounter, obj) &&
                   offsetof(S2DE0, f8) == offsetof(Nw2Encounter, shape) &&
                   offsetof(S2DE0, fC) == offsetof(Nw2Encounter, kind) &&
                   offsetof(S2DE0, f10) == offsetof(Nw2Encounter, frames) &&
                   offsetof(S2DE0, f12) == offsetof(Nw2Encounter, color) &&
                   offsetof(S2DE0, f14) == offsetof(Nw2Encounter, r) &&
                   offsetof(S2DE0, f17) == offsetof(Nw2Encounter, a),
               "S2DE0 must follow common.h's Nw2Encounter");

extern Gfx *D_800DB8AC;
extern u8 *D_800DB69C;
extern s32 D_800DB688;
extern Gfx *D_800DBD44;
extern s32 D_800E74C4;
extern u8 D_800C5E00[];
extern u8 D_800C5EC0[];
extern u8 D_800C5D10[];
extern u8 D_800C5C50[];

u8 *func_800B64EC(u8 *, s32);
void func_80091908(Gfx **, S2DE0 *, s32, s32);
void func_80091C48(Gfx **, S2DE0 *, s32, s32);
void func_80091F50(Gfx **, S2DE0 *, s32, s32);
void func_80092230(Gfx **, S2DE0 *, s32, s32);
void func_80092B20(Gfx **, S2DE0 *);

#define EMIT(a, b) { Gfx *_g = D_800DB8AC++; _g->w0 = (u32)(a); _g->w1 = (u32)(b); }
#define EMITA(a, p) { Gfx *_g = D_800DB8AC++; _g->w0 = (u32)(a); _g->w1 = DL_ADDR(p); }
#define LOADTEX(tex, a, b, c, d, e, dl) \
    EMITA(0xFD500000, tex); \
    EMIT(0xF5500000, a); \
    EMIT(0xE6000000, 0); \
    EMIT(0xF3000000, b); \
    EMIT(0xE7000000, 0); \
    EMIT(c, d); \
    EMIT(0xF2000000, e); \
    EMITA(0xDE000000, dl);

void func_80092DE0(S2DE0 *s, s32 arg1)
{
    s32 k;
    s32 id;
    s32 i;
    u8 *tex;
    u8 *tbl;

    k = s->f10 & 0x3F;
    id = (u8)s->f0->f6; /* the low byte of the spot's f6, as above */
    if (k == 0) {
        if (++s->f12 >= 7) {
            s->f12 = 0;
        }
    }
    if (k >= 0x30) {
        u8 *p1;
        u8 *p0;
        s32 n;
        k &= 0xF;
        n = s->f12 + 1;
        if (n >= 7) {
            n = 0;
        }
        p1 = &D_800C5E00[n * 3];
        p0 = &D_800C5E00[s->f12 * 3];
        s->f14 = p0[0] + (p1[0] - p0[0]) * k / 16;
        s->f15 = p0[1] + (p1[1] - p0[1]) * k / 16;
        s->f16 = p0[2] + (p1[2] - p0[2]) * k / 16;
    }
    EMIT(0xFB000000, (s->f14 << 24) | (s->f15 << 16) | (s->f16 << 8) | s->f17);
    if (s->fC == 0xB) {
        EMIT(0xFB000000, 0xFFFF0080);
        tex = func_800B64EC(D_800DB69C, 0x28);
        LOADTEX(tex, 0x07018060, 0x073FF200, 0xF5400800, 0x18060, 0xFC0FC, s->f8->dl);
    } else if (D_800E74C4 < 0) {
        tbl = func_800B600C(0x3B, 0);
        if (tbl == NULL) {
            tex = NULL;
        } else {
            tex = func_800B64EC(tbl, 0x70);
        }
        if (tex != NULL) {
            LOADTEX(tex, 0x07014050, 0x070FF400, 0xF5400400, 0x14050, 0x7C07C, D_800C5EC0);
        }
        EMITA(0xDE000000, D_800C5C50);
        EMIT(0xDF000000, 0);
    } else if (s->fC == 0xA) {
        u32 c;
        arg1 = arg1 / 2 + 0x80;
        EMITA(0xDE000000, D_800C5D10);
        c = arg1 & 0xFF;
        EMIT(0xFA000000, (c << 24) | (c << 16) | (c << 8) | 0xFF);
        switch (D_800DB688) {
        case 3:
            i = 0;
            k = (s16)s->f10;
            for (; i < 4; i++) {
                s32 sel = k & 0x180;
                s32 mode = 0;
                if (sel != 0) {
                    mode = 1;
                    if (sel != 0x100) {
                        mode = 2;
                    }
                }
                func_80091908(&D_800DB8AC, s, i, mode);
                k -= 0x10;
            }
            break;
        case 1:
            i = 0;
            k = (s16)s->f10;
            for (; i < 4; i++) {
                func_80091C48(&D_800DB8AC, s, i, k & 0x100);
                k--;
            }
            break;
        case 4:
            if (((s16)s->f10 + (id << 6)) & 0x100) {
                if (D_800DBD44 == NULL) {
                    D_800DBD44 = D_800DB8AC;
                    func_80091F50(&D_800DB8AC, s, 0, 1);
                } else {
                    EMITA(0xDE000000, D_800DBD44);
                }
            } else {
                func_80091F50(&D_800DB8AC, s, 0, 0);
            }
            break;
        case 5:
            if (((s16)s->f10 + (id << 6)) & 0x100) {
                func_80092230(&D_800DB8AC, s, id, 1);
            } else {
                func_80092230(&D_800DB8AC, s, 0, 0);
            }
            break;
        }
        EMITA(0xDE000000, s->f8->dl);
    } else {
        switch (s->fC) {
        case 6:
        case 7:
        case 8:
        case 9:
            func_80092B20(&D_800DB8AC, s);
            EMITA(0xDE000000, s->f8->dl);
            break;
        case 0: {
            u16 idx = s->f8->fA;
            tbl = func_800B600C(0x3B, 0);
            if (tbl == NULL) {
                tex = NULL;
            } else {
                tex = func_800B64EC(tbl, idx);
            }
            if (tex != NULL) {
                LOADTEX(tex + ((s16)((s16)s->f10 % 6) << 9), 0x07014050, 0x070FF400, 0xF5400400, 0x14050, 0x7C07C, s->f8->dl);
            }
            break;
        }
        default: {
            u16 idx = s->f8->fA;
            tbl = func_800B600C(0x3B, 0);
            if (tbl == NULL) {
                tex = NULL;
            } else {
                tex = func_800B64EC(tbl, idx);
            }
            if (tex != NULL) {
                LOADTEX(tex, 0x07018060, 0x073FF200, 0xF5400800, 0x18060, 0xFC0FC, s->f8->dl);
            }
            break;
        }
        }
    }
    EMITA(0xDE000000, D_800C5C50);
    EMIT(0xDF000000, 0);
}
#else
typedef struct { u32 w0; u32 w1; } Gfx2DE0;

typedef struct {
    u8 pad0[7];
    u8 f7;
} Sub2DE0a;

typedef struct {
    u32 dl;
    u8 pad4[6];
    u16 fA;
} Sub2DE0b;

typedef struct {
    Sub2DE0a *f0;
    u8 pad4[4];
    Sub2DE0b *f8;
    u16 fC;
    u8 padE[2];
    u16 f10;
    u16 f12;
    u8 f14;
    u8 f15;
    u8 f16;
    u8 f17;
} S2DE0;

extern Gfx2DE0 *D_800DB8AC;
extern s32 D_800DB69C;
extern s32 D_800DB688;
extern u32 D_800DBD44;
extern s32 D_800E74C4;
extern u8 D_800C5E00[];
extern u8 D_800C5EC0[];
extern u8 D_800C5D10[];
extern u8 D_800C5C50[];

s32 func_800B64EC(s32, s32);
s32 func_800B600C(s32, s32);
void func_80091908(Gfx2DE0 **, S2DE0 *, s32, s32);
void func_80091C48(Gfx2DE0 **, S2DE0 *, s32, s32);
void func_80091F50(Gfx2DE0 **, S2DE0 *, s32, s32);
void func_80092230(Gfx2DE0 **, S2DE0 *, s32, s32);
void func_80092B20(Gfx2DE0 **, S2DE0 *);

#define EMIT(a, b) { Gfx2DE0 *_g = D_800DB8AC++; _g->w0 = (a); _g->w1 = (b); }
#define LOADTEX(tex, a, b, c, d, e, dl) \
    EMIT(0xFD500000, (u32)(tex) - 0x80000000); \
    EMIT(0xF5500000, a); \
    EMIT(0xE6000000, 0); \
    EMIT(0xF3000000, b); \
    EMIT(0xE7000000, 0); \
    EMIT(c, d); \
    EMIT(0xF2000000, e); \
    EMIT(0xDE000000, dl);

void func_80092DE0(S2DE0 *s, s32 arg1)
{
    s32 k;
    s32 id;
    s32 i;
    s32 tex;
    s32 tbl;

    k = s->f10 & 0x3F;
    id = s->f0->f7;
    if (k == 0) {
        if (++s->f12 >= 7) {
            s->f12 = 0;
        }
    }
    if (k >= 0x30) {
        u8 *p1;
        u8 *p0;
        s32 n;
        k &= 0xF;
        n = s->f12 + 1;
        if (n >= 7) {
            n = 0;
        }
        p1 = &D_800C5E00[n * 3];
        p0 = &D_800C5E00[s->f12 * 3];
        s->f14 = p0[0] + (p1[0] - p0[0]) * k / 16;
        s->f15 = p0[1] + (p1[1] - p0[1]) * k / 16;
        s->f16 = p0[2] + (p1[2] - p0[2]) * k / 16;
    }
    EMIT(0xFB000000, (s->f14 << 24) | (s->f15 << 16) | (s->f16 << 8) | s->f17);
    if (s->fC == 0xB) {
        EMIT(0xFB000000, 0xFFFF0080);
        tex = func_800B64EC(D_800DB69C, 0x28);
        LOADTEX(tex, 0x07018060, 0x073FF200, 0xF5400800, 0x18060, 0xFC0FC, s->f8->dl);
    } else if (D_800E74C4 < 0) {
        tbl = func_800B600C(0x3B, 0);
        if (tbl == 0) {
            tex = 0;
        } else {
            tex = func_800B64EC(tbl, 0x70);
        }
        if (tex != 0) {
            LOADTEX(tex, 0x07014050, 0x070FF400, 0xF5400400, 0x14050, 0x7C07C, (u32)D_800C5EC0);
        }
        EMIT(0xDE000000, (u32)D_800C5C50);
        EMIT(0xDF000000, 0);
    } else if (s->fC == 0xA) {
        u32 c;
        arg1 = arg1 / 2 + 0x80;
        EMIT(0xDE000000, (u32)D_800C5D10);
        c = arg1 & 0xFF;
        EMIT(0xFA000000, (c << 24) | (c << 16) | (c << 8) | 0xFF);
        switch (D_800DB688) {
        case 3:
            i = 0;
            k = (s16)s->f10;
            for (; i < 4; i++) {
                s32 sel = k & 0x180;
                s32 mode = 0;
                if (sel != 0) {
                    mode = 1;
                    if (sel != 0x100) {
                        mode = 2;
                    }
                }
                func_80091908(&D_800DB8AC, s, i, mode);
                k -= 0x10;
            }
            break;
        case 1:
            i = 0;
            k = (s16)s->f10;
            for (; i < 4; i++) {
                func_80091C48(&D_800DB8AC, s, i, k & 0x100);
                k--;
            }
            break;
        case 4:
            if (((s16)s->f10 + (id << 6)) & 0x100) {
                if (D_800DBD44 == 0) {
                    D_800DBD44 = (u32)D_800DB8AC;
                    func_80091F50(&D_800DB8AC, s, 0, 1);
                } else {
                    EMIT(0xDE000000, D_800DBD44);
                }
            } else {
                func_80091F50(&D_800DB8AC, s, 0, 0);
            }
            break;
        case 5:
            if (((s16)s->f10 + (id << 6)) & 0x100) {
                func_80092230(&D_800DB8AC, s, id, 1);
            } else {
                func_80092230(&D_800DB8AC, s, 0, 0);
            }
            break;
        }
        EMIT(0xDE000000, s->f8->dl);
    } else {
        switch (s->fC) {
        case 6:
        case 7:
        case 8:
        case 9:
            func_80092B20(&D_800DB8AC, s);
            EMIT(0xDE000000, s->f8->dl);
            break;
        case 0: {
            u16 idx = s->f8->fA;
            tbl = func_800B600C(0x3B, 0);
            if (tbl == 0) {
                tex = 0;
            } else {
                tex = func_800B64EC(tbl, idx);
            }
            if (tex != 0) {
                LOADTEX(tex + ((s16)((s16)s->f10 % 6) << 9), 0x07014050, 0x070FF400, 0xF5400400, 0x14050, 0x7C07C, s->f8->dl);
            }
            break;
        }
        default: {
            u16 idx = s->f8->fA;
            tbl = func_800B600C(0x3B, 0);
            if (tbl == 0) {
                tex = 0;
            } else {
                tex = func_800B64EC(tbl, idx);
            }
            if (tex != 0) {
                LOADTEX(tex, 0x07018060, 0x073FF200, 0xF5400800, 0x18060, 0xFC0FC, s->f8->dl);
            }
            break;
        }
        }
    }
    EMIT(0xDE000000, (u32)D_800C5C50);
    EMIT(0xDF000000, 0);
}
#endif
