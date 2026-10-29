#include "common.h"

typedef struct {
    u8 pad0[0x14];
    void *f14;
} Aux18140;

typedef struct {
    s16 f0;
    u8 pad2[0x26];
    void *f28;
} Env18140;

typedef struct {
    u8 pad0[0x14];
    void *f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
} Slot18140;

typedef struct {
    s32 f0;
    s32 f4;
    s16 f8;
    s16 fA;
    s16 fC;
    u8 padE[2];
    f32 f10;
    f32 f14;
    s32 f18;
    f32 f1C;
    Env18140 *f20;
    Slot18140 *f24;
} Region18140;

typedef struct {
    u8 pad0[0x14];
    s16 *f14;
    s16 *f18;
    s32 f1C;
    Region18140 *f20;
    u8 f24;
} Out18140;

typedef struct {
    u8 pad0[0x18];
    s32 f18;
    u8 f1C;
    u8 pad1D[3];
    s32 *f20;
} Desc18140;

extern s32 D_80036F60[];
extern s32 D_80036FC8[];
extern s32 D_80037050[];
extern s32 D_80037078[];
extern s32 D_800370A0[];
extern s32 D_800370C8[];

void *func_800202B0(s32, s32, s32, s32, s32);
void func_8001CEF0(void *);

/* Builds an audio-region set from a parameter table: the descriptor's kind
 * (1..6) picks the table (6 = the descriptor's own), whose first two words give the
 * region count and the size of the s16 array, followed by 7..9 words per region. */
void func_80018140(Out18140 **out, Desc18140 *desc, s32 pool) {
    Out18140 *o;
    Region18140 *r;
    s32 *tbl;
    u16 idx;
    u16 k;
    u16 n;

    o = func_800202B0(0, 0, pool, 1, 0x2C);
    *out = o;
    switch (desc->f1C) {
    case 1:
        tbl = D_80036F60;
        break;
    case 2:
        tbl = D_80036FC8;
        break;
    case 5:
        tbl = D_80037050;
        break;
    case 3:
        tbl = D_80037078;
        break;
    case 4:
        tbl = D_800370A0;
        break;
    case 6:
        tbl = desc->f20;
        break;
    default:
        tbl = D_800370C8;
        break;
    }
    o->f24 = tbl[0];
    o->f1C = tbl[1];
    o->f20 = func_800202B0(0, 0, pool, o->f24, 0x28);
    o->f14 = o->f18 = func_800202B0(0, 0, pool, o->f1C, 2);
    idx = 2;
    if (o->f1C != 0) {
        n = 0;
        do {
            o->f14[n] = 0;
            n++;
        } while (n < o->f1C);
    }
    if (o->f24 != 0) {
        k = 0;
        do {
            r = &o->f20[k];
            r->f0 = tbl[idx++];
            r->f4 = tbl[idx++];
            r->fA = tbl[idx++];
            r->f8 = tbl[idx++];
            r->fC = tbl[idx++];
            if (tbl[idx] != 0) {
                r->f10 = (f64)((f32)tbl[idx] / 1000.0f) * 2.0 / (f64)desc->f18;
                idx++;
                r->f1C = (f64)(f32)tbl[idx] / 173123.404906676 * (f64)(u32)(r->f4 - r->f0);
                idx++;
                r->f18 = 0;
                r->f14 = 1.0f;
                r->f24 = func_800202B0(0, 0, pool, 1, 0x34);
                r->f24->f14 = func_800202B0(0, 0, pool, 1, 0x20);
                r->f24->f20 = 0;
                r->f24->f24 = 1;
            } else {
                r->f24 = 0;
                idx += 2;
            }
            if (tbl[idx] != 0) {
                r->f20 = func_800202B0(0, 0, pool, 1, 0x30);
                r->f20->f28 = func_800202B0(0, 0, pool, 1, 8);
                r->f20->f0 = tbl[idx];
                func_8001CEF0(r->f20);
                idx++;
            } else {
                r->f20 = 0;
                idx++;
            }
            k++;
        } while (k < o->f24);
    }
}
