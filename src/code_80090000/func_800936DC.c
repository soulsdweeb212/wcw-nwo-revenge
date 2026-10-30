/* @header
 * func_800936DC
 * VRAM 0x800936DC | ROM 0x3FE4C | size 0x6D0
 * asm: asm/nonmatchings/code_80090000/func_800936DC.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } Gw936;

typedef struct {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 pad6;
    void **f8;
    struct Sub936 *fC;
    u8 pad10[0x24];
} Rec936;

typedef struct {
    u16 f0, f2, f4, f6, f8, fA;
    u8 fC, fD, fE, fF;
} Vtx936;

typedef struct {
    u8 pad0[4];
    u16 count;
    u16 resId;
} Part936;

typedef struct {
    Part936 *f0;
    u32 f4;
    Vtx936 *f8;
    Gw936 *fC;
} Ent936;

typedef struct Sub936 {
    u16 id;
    u16 count;
    u16 flags;
    u16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
} Sub936;

typedef struct {
    u8 pad0[4];
    s32 f4;
    u16 f8;
    u8 padA[6];
} Anim936;

typedef struct {
    u8 pad0[0x24];
    f32 f24;
} Obj936;

typedef struct {
    u8 pad0[0xC];
    s32 fC;
    Gw936 *f10;
    Obj936 *f14;
    u8 f18;
    u8 pad19;
    u8 f1A;
    s8 f1B;
    u8 f1C[0xC0];
} Out936;

typedef struct {
    Sub936 *f0;
    Out936 *f4;
    Anim936 *f8;
    u16 fC;
    u16 pad;
    u16 f10;
    u16 f12;
    u8 f14, f15, f16, pad17;
} Enc936;

extern Rec936 D_800C8E84[];
extern Rec936 *D_800DB680;
extern Sub936 *D_800DB684;
extern Gw936 *D_800DB68C;
extern Gw936 *D_800DB690;
extern Vtx936 *D_800DB694;
extern Vtx936 *D_800DB698;
extern void *D_800DB69C;
extern void *D_800DB6A0;
extern Ent936 D_800DB6A8[];
extern Out936 *D_800DB674;
extern Gw936 *D_800DB8AC;
extern Enc936 D_800DB8C0[];
extern s32 D_800DBD40;
extern s32 D_800DBD44;
extern s32 D_800DBD48;
extern Anim936 D_800C6508[];
extern u8 D_800C5E00[];
extern u32 D_800C5D10[];
extern u32 sceneNodeCallback5C50[];

typedef struct { u32 a, b, size, d; } Desc936;

void func_80002C0C(void);
void lookupResourceDescriptor(Desc936 *, u16);
void *allocateHeap(u32);
void func_80003684(void *, u16, void *);
Vtx936 *func_800B64EC(void *, u16);
void func_80090908(Part936 *, Vtx936 *);
s32 func_8001C580(void);
void func_800914F0(Out936 *);
void func_80092DE0(Enc936 *, s32, s32);
void buildScaledRotationTranslationMatrix(void *, f32, f32, f32, f32, f32, f32, f32);
void func_800015AC(Out936 *, s32);
void relinkEntityList(void);
void releaseHeapBlock(void *);
void func_80002C74(void);

void func_800936DC(s32 arg0) {
    Ent936 *ent = D_800DB6A8;
    Enc936 *enc = D_800DB8C0;
    Desc936 desc;
    u8 bufA[0x10];
    u8 bufB[0x10];
    Rec936 *rec;
    Sub936 *sub;
    void **partp;
    Part936 *part;
    Vtx936 *src;
    Out936 *out;
    Ent936 *e;
    Gw936 *g;
    s32 i, j, k;

    if (arg0 >= 0 && arg0 < 10) {
        D_800DB680 = rec = &D_800C8E84[arg0];
        D_800DB684 = rec->fC;
        sub = D_800DB684;
        if (arg0 < 9) {
            partp = rec->f8;
            func_80002C0C();
            lookupResourceDescriptor(&desc, D_800DB680->f2);
            D_800DB69C = allocateHeap(desc.size);
            func_80003684(bufA, D_800DB680->f2, D_800DB69C);
            lookupResourceDescriptor(&desc, D_800DB680->f0);
            D_800DB6A0 = allocateHeap(desc.size);
            func_80003684(bufB, D_800DB680->f0, D_800DB6A0);
            D_800DB694 = D_800DB698;
            D_800DB68C = D_800DB690;
            for (i = 0; i < D_800DB680->f4; i++) {
                ent->f0 = *partp;
                ent->f8 = D_800DB694;
                part = ent->f0;
                src = func_800B64EC(D_800DB6A0, part->resId);
                j = 0;
                while (j < part->count) {
                    D_800DB694->f0 = src->f0;
                    D_800DB694->f2 = src->f2;
                    D_800DB694->f4 = src->f4;
                    D_800DB694->f6 = src->f6;
                    D_800DB694->f8 = src->f8;
                    D_800DB694->fA = src->fA;
                    D_800DB694->fC = src->fC;
                    D_800DB694->fD = src->fD;
                    D_800DB694->fE = src->fE;
                    D_800DB694->fF = src->fF;
                    j++;
                    src++;
                    D_800DB694++;
                }
                ent->fC = D_800DB68C;
                partp++;
                func_80090908(ent->f0, ent->f8);
                D_800DB68C->w0 = 0xDF000000;
                D_800DB68C->w1 = 0;
                D_800DB68C++;
                ent++;
            }

            out = D_800DB674;
            D_800DBD40 = 0;
            D_800DBD44 = 0;
            D_800DBD48 = 0;
            for (k = 0; sub->count != 0; k++) {
                if (sub->flags & 0x8000) {
                    enc->f0 = sub;
                    enc->f4 = out;
                    enc->fC = sub->id;
                    enc->f8 = &D_800C6508[sub->id];
                    enc->f12 = func_8001C580() % 7;
                    enc->f14 = D_800C5E00[enc->f12 * 3];
                    enc->f15 = D_800C5E00[enc->f12 * 3 + 1];
                    enc->f16 = D_800C5E00[enc->f12 * 3 + 2];
                    enc->f10 = 0;
                    if (enc->fC == 0xA) {
                        func_800914F0(out);
                    } else {
                        out->fC = enc->f8->f4;
                        out->f1B = enc->f8->f8;
                    }
                    out->f10 = D_800DB8AC;
                    out->f1A = 0;
                    func_80092DE0(enc, 0, 0);
                    if (sub->f6 & 0x8000) {
                        out->f14->f24 = 0.0f;
                    } else if ((sub->f6 & 0x7000) == 0x1000) {
                        out->f14->f24 = -512.0f;
                    } else {
                        out->f14->f24 = -256.0f;
                    }
                    D_800DBD40++;
                    enc++;
                } else {
                    ent = &D_800DB6A8[sub->id];
                    out->fC = (s32)ent->f8;
                    out->f1B = ent->f0->count;
                    if (sub->flags & 0x2000) {
                        out->f14->f24 = sub->f6 << 8;
                    } else {
                        out->f14->f24 = 0.0f;
                    }
                    out->f10 = D_800DB8AC;
                    e = &D_800DB6A8[sub->id];
                    g = D_800DB8AC++;
                    g->w0 = 0xDE000000;
                    g->w1 = (u32)D_800C5D10;
                    g = D_800DB8AC++;
                    g->w0 = 0xFA000000;
                    g->w1 = 0xFF;
                    for (j = 0; j < sub->count; j++, e++) {
                        D_800DB8AC->w0 = 0xDE000000;
                        D_800DB8AC->w1 = (u32)e->fC;
                        D_800DB8AC++;
                    }
                    g = D_800DB8AC++;
                    g->w0 = 0xDE000000;
                    g->w1 = (u32)sceneNodeCallback5C50;
                    g = D_800DB8AC++;
                    g->w0 = 0xDF000000;
                    g->w1 = 0;
                }
                buildScaledRotationTranslationMatrix(out->f1C, 0.0f, sub->fE, 0.0f, 1.0f, sub->f8, sub->fA, sub->fC);
                if (arg0 < 6 && k == 0) {
                    out->f14->f24 = 1024.0f;
                }
                out->f18 &= 0x7F;
                func_800015AC(out, out->f1B);
                sub++;
                out++;
            }
            for (i = k; i < 0x48; i++) {
                out->f18 |= 0x80;
                out++;
            }
            relinkEntityList();
            releaseHeapBlock(D_800DB6A0);
            D_800DB6A0 = 0;
            func_80002C74();
        }
    }
}
