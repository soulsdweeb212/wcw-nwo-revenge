/* @header
 * func_8009FE3C
 * VRAM 0x8009FE3C | ROM 0x4C5AC | size 0x5E4
 * asm: asm/nonmatchings/code_80090000/func_8009FE3C.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx, which the functions this one hands the list to also write on PC. */
typedef Gfx G;
#else
typedef struct { u32 w0, w1; } G;
#endif
typedef struct { void *dl; void *addr; u16 n; u8 padA[6]; } VtxSet;
typedef struct { u8 pad0[0xE]; u8 idx; } Def;
typedef struct {
    u8 pad0[0xD];
    s8 fD;
    s8 fE;
    u8 padF[0x11];
    u16 f20;
    u16 f22;
    Def *def;
} Obj;

extern VtxSet D_800CB7B8[];
extern u16 D_800C9110[], D_800C9130[];
extern s32 D_800CCA64[][2];
extern u8 D_800D6178[], D_8007E8C0[];
void func_800A2158(G **, Obj *, s32);
void func_800A2B5C(G **, Obj *, s32);
void func_800A3500(G **, Obj *, void *, s32);
#ifdef TARGET_PC
/* PC: func_800AA070 returns the address of a name record (its PC definition, func_800AA070.c), which this file hands
 * to func_800A3E00 as the name of the picture to draw; an s32 would cut it in half. */
void func_800A3E00(G **, u8 *);
#else
void func_800A3E00(G **, s32);
#endif
void func_800B7260(G **, s32, s32, s32);
void func_800A37FC_ovl1(G **, Obj *);
void func_800A1C30(G **, Obj *);
void func_800A7130(G **, Obj *, s32, s32);
void func_800A7290(G **, Obj *, s32, s32);
void func_800A73AC(G **, Obj *, VtxSet *);
void func_800996B0(G **, s32, s32);
void func_800A71A8(G **, Obj *);
void func_800B6FE0(G **, s32);
void func_800A4C58(G **, Obj *, VtxSet *);
void func_800A542C(G **, Obj *);
void func_800A4284(G **, Obj *);
void func_800A55AC(G **, Obj *, s32);
void func_800A6B24(G **, Obj *);
void func_800A5A30(G **, Obj *);
void func_800A6498(G **, Obj *);
void func_800A7C34(G **, Obj *);
void func_800A7E9C(G **, Obj *);
void func_800A83FC(G **, Obj *);
void func_800A8BB0(G **, Obj *);
#ifdef TARGET_PC
/* PC: the name record's address, as above. */
u8 *func_800AA070(s32);
#else
s32 func_800AA070(s32);
#endif
s32 func_800AA0D8(s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_8002AD04, which returns the name record's address */
void *func_8002AD04(s32, s32);
#endif

void func_8009FE3C(G **dl, Obj *o) {
    G *g = *dl;
    VtxSet *vs = &D_800CB7B8[o->def->idx];
    s32 k = o->f20 & 0xFF;
    s32 t;
    u8 a, b;

    switch (o->f20 & 0xFF00) {
    case 0xFF00:
        { G *d = g++; d->w0 = 0xDF000000; d->w1 = 0; }
        break;
    case 0x600:
        func_800A2158(&g, o, o->f22);
        break;
    case 0x5300:
        func_800A2B5C(&g, o, k);
        break;
    case 0x5000:
        if (o->f22 == 0) {
            func_800A3500(&g, o, D_800D6178, 0);
        } else {
            func_800A3500(&g, o, func_8002AD04(o->f22, k & 3), 0);
        }
        break;
    case 0x700:
        func_800B6FE0(&g, D_800C9130[k]);
        func_800A1C30(&g, o);
        break;
    case 0x4100:
        func_800A3E00(&g, func_800AA070(k));
        break;
    case 0x4300:
        k = func_800AA0D8(k);
        if (k < 0) {
            { G *d = g++; d->w0 = 0xDF000000; d->w1 = 0; }
            break;
        }
        if (o->f22 != 0 && k == 0) {
            k = 1;
        }
        func_800B7260(&g, k << 4, 0x10, 0x58);
        func_800A1C30(&g, o);
        break;
    case 0x4200:
        if (func_800AA0D8(k) < 0) {
            { G *d = g++; d->w0 = 0xDF000000; d->w1 = 0; }
        } else {
            func_800A37FC_ovl1(&g, o);
        }
        break;
    case 0x6200:
        if (o->fD & 1) {
            t = (D_800CCA64[k][0] + o->fD) & 0xFF;
            k = (D_800CCA64[k][0] + o->fE) & 0xFF;
        } else {
            t = (D_800CCA64[k][0] + o->fE) & 0xFF;
            k = (D_800CCA64[k][0] + o->fD) & 0xFF;
        }
        func_800A1C30(&g, o);
        func_800A7130(&g, o, D_800C9110[k], D_800C9110[t]);
        break;
    case 0x5900:
        if (k == 0) {
            func_800A3500(&g, o, D_8007E8C0 + 0xB8, 0x10000);
        } else {
            func_800A3500(&g, o, D_8007E8C0 + 0xDA, 0x10000);
        }
        break;
    case 0x5A00:
    case 0x5B00:
        func_800A7290(&g, o, k + 1, 0);
        break;
    case 0x5C00:
        func_800A73AC(&g, o, vs);
        break;
    case 0x5800:
        { G *d = g++; d->w0 = 0xDF000000; d->w1 = 0; }
        break;
    case 0x100:
        if (o->f20 < 0x121) {
            { G *d = g++; d->w0 = 0xDF000000; d->w1 = 0; }
        } else {
            func_800996B0(&g, o->f20, 8);
            func_800A71A8(&g, o);
        }
        break;
    case 0x7700:
        func_800B6FE0(&g, 0xE4);
        if (o->f22 != 0) {
            func_800A1C30(&g, o);
        }
        break;
    case 0x7300:
        func_800A4C58(&g, o, vs);
        break;
    case 0x7400:
        func_800A542C(&g, o);
        break;
    case 0x7500:
        func_800A4284(&g, o);
        break;
    case 0x7600:
        func_800A55AC(&g, o, k - 1);
        break;
    case 0x6400:
        func_800A6B24(&g, o);
        break;
    case 0x7C00:
        func_800A5A30(&g, o);
        break;
    case 0x7D00:
        func_800A6498(&g, o);
        break;
    case 0x1000:
        func_800A7C34(&g, o);
        break;
    case 0x1100:
        func_800A7E9C(&g, o);
        break;
    case 0x1200:
        func_800A83FC(&g, o);
        break;
    case 0x800:
        func_800A8BB0(&g, o);
        break;
    default:
        func_800B6FE0(&g, D_800C9110[o->f20]);
        func_800A1C30(&g, o);
        break;
    }
    if (vs->dl != 0) {
        G *d = g++;
        d->w0 = 0xDE000000;
#ifdef TARGET_PC
        /* PC: the display list's address as the whole pointer (port.h's DL_ADDR). */
        d->w1 = DL_ADDR(vs->dl);
#else
        d->w1 = (u32)vs->dl - 0x80000000;
#endif
    }
    *dl = g;
}
