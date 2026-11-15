/* @header
 * func_800936DC
 * VRAM 0x800936DC | ROM 0x3FE4C | size 0x6D0
 * asm: asm/nonmatchings/code_80090000/func_800936DC.s
 */
#include "common.h"

#ifdef TARGET_PC
typedef Gfx Gw936; /* PC: a command is port.h's 16-byte Gfx, which keeps a whole pointer in w1 */
#else
typedef struct { u32 w0, w1; } Gw936;
#endif

#ifdef TARGET_PC
/* PC: Rec936 is a scene of D_800C8E84 (common.h's Nw2EncScene), whose addresses are pointers, so it is 0x58 bytes on
 * PC; this view keeps the file's field names and follows that struct, as the asserts below check. */
typedef struct {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 pad6;
    void **f8;
    struct Sub936 *fC;
    Nw2EncTitle *f10;
    u16 f14[4];
    u16 *f1C[5];
    u32 f30;
} Rec936;
#else
typedef struct {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 pad6;
    void **f8;
    struct Sub936 *fC;
    u8 pad10[0x24];
} Rec936;
#endif

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

#ifdef TARGET_PC
typedef Nw2PicShape Anim936; /* PC: a record of D_800C6508 (common.h), 0x18 bytes, its addresses pointers */
#else
typedef struct {
    u8 pad0[4];
    s32 f4;
    u16 f8;
    u8 padA[6];
} Anim936;
#endif

typedef struct {
    u8 pad0[0x24];
    f32 f24;
} Obj936;

#ifdef TARGET_PC
/* PC: Out936 is the game's 0xDC-byte scene object (Nw2SceneObj in common.h), which keeps its N64 layout on PC, so its
 * vertices (fC), display list (f10) and work block (f14) are 4-byte handles (port.h's PTR_TO_SLOT): the code stores
 * PTR_TO_SLOT(p) and reaches the work block (Nw2SceneWork, whose bias is Obj936's f24) through SLOT_TO_PTR. The asserts
 * check the view against Nw2SceneObj. The vertices that the encounter objects take from their record of D_800C6508
 * (common.h's Nw2PicShape) are a pointer there, stored as the object's handle. */
typedef struct {
    u8 pad0[0xC];
    u32 fC;
    u32 f10;
    u32 f14;
    u8 f18;
    u8 pad19;
    u8 f1A;
    s8 f1B;
    u8 f1C[0xC0];
} Out936;
_Static_assert(offsetof(Out936, fC) == offsetof(Nw2SceneObj, vtx) && offsetof(Out936, f10) == offsetof(Nw2SceneObj, dl) &&
                   offsetof(Out936, f14) == offsetof(Nw2SceneObj, work) &&
                   offsetof(Out936, f18) == offsetof(Nw2SceneObj, group) &&
                   offsetof(Out936, f1A) == offsetof(Nw2SceneObj, lit) &&
                   offsetof(Out936, f1B) == offsetof(Nw2SceneObj, vtxCount) &&
                   offsetof(Out936, f1C) == offsetof(Nw2SceneObj, local) && sizeof(Out936) == sizeof(Nw2SceneObj),
               "Out936 is the scene object's N64 layout");
#define WORK936(o) ((Nw2SceneWork *)SLOT_TO_PTR((o)->f14))
#else
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
#endif

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
#ifdef TARGET_PC
/* PC: the records follow common.h's layouts, in which their addresses are pointers: Rec936 a scene (Nw2EncScene),
 * Sub936 a spot (Nw2EncSpot), Ent936 an entry of D_800DB6A8 (Nw2EncPartDraw) and Enc936 an encounter of D_800DB8C0
 * (Nw2Encounter). */
_Static_assert(sizeof(Rec936) == sizeof(Nw2EncScene) && offsetof(Rec936, f8) == offsetof(Nw2EncScene, parts) &&
                   offsetof(Rec936, fC) == offsetof(Nw2EncScene, spots) &&
                   offsetof(Rec936, f10) == offsetof(Nw2EncScene, title) &&
                   offsetof(Rec936, f14) == offsetof(Nw2EncScene, f14) &&
                   offsetof(Rec936, f1C) == offsetof(Nw2EncScene, phases),
               "Rec936 must follow Nw2EncScene");
_Static_assert(sizeof(Sub936) == sizeof(Nw2EncSpot) && offsetof(Sub936, flags) == offsetof(Nw2EncSpot, flags) &&
                   offsetof(Sub936, f6) == offsetof(Nw2EncSpot, f6) &&
                   offsetof(Sub936, f8) == offsetof(Nw2EncSpot, x) &&
                   offsetof(Sub936, fE) == offsetof(Nw2EncSpot, pitch),
               "Sub936 must follow Nw2EncSpot");
_Static_assert(sizeof(Ent936) == sizeof(Nw2EncPartDraw) && offsetof(Ent936, f8) == offsetof(Nw2EncPartDraw, vtx) &&
                   offsetof(Ent936, fC) == offsetof(Nw2EncPartDraw, dl),
               "Ent936 must follow Nw2EncPartDraw");
_Static_assert(sizeof(Enc936) == sizeof(Nw2Encounter) && offsetof(Enc936, f4) == offsetof(Nw2Encounter, obj) &&
                   offsetof(Enc936, f8) == offsetof(Nw2Encounter, shape) &&
                   offsetof(Enc936, fC) == offsetof(Nw2Encounter, kind) &&
                   offsetof(Enc936, f10) == offsetof(Nw2Encounter, frames) &&
                   offsetof(Enc936, f12) == offsetof(Nw2Encounter, color) &&
                   offsetof(Enc936, f14) == offsetof(Nw2Encounter, r),
               "Enc936 must follow Nw2Encounter");
#endif

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
#ifndef TARGET_PC /* on PC, port_decls.h declares D_800DBD44 */
extern s32 D_800DBD44;
#endif
#ifdef TARGET_PC
extern u8 *D_800DBD48; /* PC: it holds an address (func_800914F0 sets it to D_800DB694), so a pointer */
#else
extern s32 D_800DBD48;
#endif
extern Anim936 D_800C6508[];
extern u8 D_800C5E00[];
extern u32 D_800C5D10[];
extern u32 D_800C5C50[];

typedef struct { u32 a, b, size, d; } Desc936;

void func_80002C0C(void);
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void lookupResourceDescriptor(Desc936 *, u16);
#endif
void *allocateHeap(u32);
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void func_80003684(void *, u16, void *);
#endif
Vtx936 *func_800B64EC(void *, u16);
void func_80090908(Part936 *, Vtx936 *);
s32 guRandom(void);
#ifdef TARGET_PC
/* PC: the parameters of func_800914F0's definition: the object, then a control-point block and its count, which it
 * reads only when D_800DB688 is none of 1, 3, 4 and 5 (each of those picks a block of its own). */
void func_800914F0(Out936 *, void *, s32);
#else
void func_800914F0(Out936 *);
#endif
#ifdef TARGET_PC
/* PC: the parameters of func_80092DE0's definition, an encounter and a number. The N64 passes a third argument, which
 * it does not read. */
void func_80092DE0(Enc936 *, s32);
#else
void func_80092DE0(Enc936 *, s32, s32);
#endif
void guPositionF(void *, f32, f32, f32, f32, f32, f32, f32);
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
#ifdef TARGET_PC
                    /* PC: the pack's vertex records keep the N64's byte order (func_800B64EC), and the copies are
                     * vertices that LibUltraShip reads in the PC's, so each 16-bit field is read big-endian. The four
                     * bytes after them are copied as they are. */
                    D_800DB694->f0 = READ_BE16(&src->f0);
                    D_800DB694->f2 = READ_BE16(&src->f2);
                    D_800DB694->f4 = READ_BE16(&src->f4);
                    D_800DB694->f6 = READ_BE16(&src->f6);
                    D_800DB694->f8 = READ_BE16(&src->f8);
                    D_800DB694->fA = READ_BE16(&src->fA);
#else
                    D_800DB694->f0 = src->f0;
                    D_800DB694->f2 = src->f2;
                    D_800DB694->f4 = src->f4;
                    D_800DB694->f6 = src->f6;
                    D_800DB694->f8 = src->f8;
                    D_800DB694->fA = src->fA;
#endif
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
                    enc->f12 = guRandom() % 7;
                    enc->f14 = D_800C5E00[enc->f12 * 3];
                    enc->f15 = D_800C5E00[enc->f12 * 3 + 1];
                    enc->f16 = D_800C5E00[enc->f12 * 3 + 2];
                    enc->f10 = 0;
                    if (enc->fC == 0xA) {
#ifdef TARGET_PC
                        /* PC: the N64 call leaves a1 and a2 as the last function called left them (here guRandom,
                         * which does not touch them), so a block and count are only defined for the four modes that
                         * pick their own. The PC passes none: another mode would read through NULL. */
                        func_800914F0(out, NULL, 0);
#else
                        func_800914F0(out);
#endif
                    } else {
#ifdef TARGET_PC
                        out->fC = PTR_TO_SLOT(enc->f8->vtx); /* PC: a handle (see Out936) */
                        out->f1B = enc->f8->count;
#else
                        out->fC = enc->f8->f4;
                        out->f1B = enc->f8->f8;
#endif
                    }
#ifdef TARGET_PC
                    /* PC: the display list's handle (see Out936). */
                    out->f10 = PTR_TO_SLOT(D_800DB8AC);
#else
                    out->f10 = D_800DB8AC;
#endif
                    out->f1A = 0;
#ifdef TARGET_PC
                    func_80092DE0(enc, 0); /* PC: as declared above */
#else
                    func_80092DE0(enc, 0, 0);
#endif
                    if (sub->f6 & 0x8000) {
#ifdef TARGET_PC
                        /* PC: the work block is a handle (see Out936). */
                        WORK936(out)->bias = 0.0f;
#else
                        out->f14->f24 = 0.0f;
#endif
                    } else if ((sub->f6 & 0x7000) == 0x1000) {
#ifdef TARGET_PC
                        WORK936(out)->bias = -512.0f; /* PC: as above */
#else
                        out->f14->f24 = -512.0f;
#endif
                    } else {
#ifdef TARGET_PC
                        WORK936(out)->bias = -256.0f; /* PC: as above */
#else
                        out->f14->f24 = -256.0f;
#endif
                    }
                    D_800DBD40++;
                    enc++;
                } else {
                    ent = &D_800DB6A8[sub->id];
#ifdef TARGET_PC
                    /* PC: the vertices' handle (see Out936). */
                    out->fC = PTR_TO_SLOT(ent->f8);
#else
                    out->fC = (s32)ent->f8;
#endif
                    out->f1B = ent->f0->count;
                    if (sub->flags & 0x2000) {
#ifdef TARGET_PC
                        WORK936(out)->bias = sub->f6 << 8; /* PC: as above */
#else
                        out->f14->f24 = sub->f6 << 8;
#endif
                    } else {
#ifdef TARGET_PC
                        WORK936(out)->bias = 0.0f; /* PC: as above */
#else
                        out->f14->f24 = 0.0f;
#endif
                    }
#ifdef TARGET_PC
                    out->f10 = PTR_TO_SLOT(D_800DB8AC); /* PC: as above */
#else
                    out->f10 = D_800DB8AC;
#endif
                    e = &D_800DB6A8[sub->id];
                    g = D_800DB8AC++;
                    g->w0 = 0xDE000000;
#ifdef TARGET_PC
                    /* PC: the display list's address as the whole pointer (port.h's DL_ADDR). */
                    g->w1 = DL_ADDR(D_800C5D10);
#else
                    g->w1 = (u32)D_800C5D10;
#endif
                    g = D_800DB8AC++;
                    g->w0 = 0xFA000000;
                    g->w1 = 0xFF;
                    for (j = 0; j < sub->count; j++, e++) {
                        D_800DB8AC->w0 = 0xDE000000;
#ifdef TARGET_PC
                        D_800DB8AC->w1 = DL_ADDR(e->fC); /* PC: as above */
#else
                        D_800DB8AC->w1 = (u32)e->fC;
#endif
                        D_800DB8AC++;
                    }
                    g = D_800DB8AC++;
                    g->w0 = 0xDE000000;
#ifdef TARGET_PC
                    g->w1 = DL_ADDR(D_800C5C50); /* PC: as above */
#else
                    g->w1 = (u32)D_800C5C50;
#endif
                    g = D_800DB8AC++;
                    g->w0 = 0xDF000000;
                    g->w1 = 0;
                }
                guPositionF(out->f1C, 0.0f, sub->fE, 0.0f, 1.0f, sub->f8, sub->fA, sub->fC);
                if (arg0 < 6 && k == 0) {
#ifdef TARGET_PC
                    WORK936(out)->bias = 1024.0f; /* PC: as above */
#else
                    out->f14->f24 = 1024.0f;
#endif
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
