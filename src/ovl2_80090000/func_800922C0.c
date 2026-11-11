/* @header
 * func_800922C0
 * VRAM 0x800922C0 | ROM 0x85760 | size 0x2030
 * asm: asm/nonmatchings/ovl2_80090000/func_800922C0.s
 */
#include "common.h"

#ifdef TARGET_PC
typedef Gfx Gfx2; /* on PC a command is port.h's 16-byte Gfx, as func_80090380 allocates them */
#else
typedef struct {
    u32 w0;
    u32 w1;
} Gfx2;
#endif

typedef struct {
    s32 flags;
    u8 pad4[0x1C];
    f32 f20;
    f32 f24;
} Cam;
#ifdef TARGET_PC
/* Cam is a work block (common.h's Nw2SceneWork, N64 layout on PC): flags is its kind, f20 the depth of its eye
 * (eye[2]) and f24 its depth bias. */
_Static_assert(offsetof(Cam, flags) == offsetof(Nw2SceneWork, kind) &&
                   offsetof(Cam, f20) == offsetof(Nw2SceneWork, eye) + 2 * sizeof(f32) &&
                   offsetof(Cam, f24) == offsetof(Nw2SceneWork, bias),
               "Cam must follow Nw2SceneWork");
#endif

#ifdef TARGET_PC
/* PC: a scene object (common.h's Nw2SceneObj), which keeps its N64 layout on PC. Its display list (+0x10) and its
 * work block (+0x14) are 4-byte handles (port.h's PTR_TO_SLOT): code reads them through SLOT_TO_PTR. */
typedef struct {
    u8 pad0[0x10];
    u32 dl;
    u32 node;
    u8 pad18;
    u8 f19;
    u8 pad1A[0x82];
    f32 mtx[4][4];
} Spr;
_Static_assert(offsetof(Spr, dl) == offsetof(Nw2SceneObj, dl) && offsetof(Spr, node) == offsetof(Nw2SceneObj, work) &&
                   offsetof(Spr, f19) == offsetof(Nw2SceneObj, flat) &&
                   offsetof(Spr, mtx) == offsetof(Nw2SceneObj, view) && sizeof(Spr) == sizeof(Nw2SceneObj),
               "Spr must follow Nw2SceneObj");
#else
/* 0xDC-byte sprite/display object */
typedef struct {
    u8 pad0[0x10];
    void *dl;
    Cam *node;
    u8 pad18;
    u8 f19;
    u8 pad1A[0x82];
    f32 mtx[4][4];
} Spr;
#endif

#ifdef TARGET_PC
/* PC: the display record (dl is its f10, then f18 and f1C, the picture's texture and palette) and the picture pair
 * are common.h's PC layouts, the types port_decls.h declares the arrays with. */
typedef Nw2Descr4BA8 SprTex;
typedef Nw2TexPair Tex8;
#else
/* 0x2C-byte texture record */
typedef struct {
    u8 pad0[0x10];
    Gfx2 *dl;
    u8 pad14[4];
    s32 f18;
    s32 f1C;
    u8 pad20[0xC];
} SprTex;

/* 8-byte texture handle */
typedef struct {
    s32 w0;
    s32 w1;
} Tex8;
#endif

extern u8 D_8007E228[];
extern s32 D_8007E8C0[];
extern u16 D_800307A0;
extern u16 D_800E2D84[];
extern s16 D_800E2B24[];
extern s16 D_800E2B34[];
extern s16 D_800E2B44[];
extern s16 D_800E2B54[];
extern s16 D_800E2B74[];
extern s16 D_800E2BEC[];
extern s16 D_800E2BF0[];
extern s16 D_800E2C08[];
extern s16 D_800E2C14[];
extern s8 D_800E2C3C[];
extern s8 D_800E2C44[];

extern Spr D_800E77C0;
extern s16 D_800E7940;
extern s16 D_800E7942;
extern void *D_800E789C[3];
extern Tex8 D_800E78A8[19];
extern Spr D_800E7950[5];
extern Tex8 D_800E7DA0[11];
extern Spr D_800E7DF8;
extern Spr D_800E7ED8;
extern SprTex D_800E7FB8[3];
extern SprTex D_800E8040[3];
extern s16 D_800E80C4;
extern Spr D_800E80C8[2];
extern Spr D_800E8280[2];
extern SprTex D_800E8438[2][10];
extern SprTex D_800E87A8[2][10];
extern s16 D_800E8B18;
extern s16 D_800E8B1A;
extern Spr D_800E8B28;
extern Spr D_800E8C08;
extern SprTex D_800E8CE8[2];
extern SprTex D_800E8D40[2];
extern s16 D_800E8D98;
extern s16 D_800E8D9A;
extern Spr D_800E8DA0;
extern Spr D_800E8E80;
extern SprTex D_800E8F60[7];
extern SprTex D_800E9098[7];
extern s16 D_800E91CC;
extern s16 D_800E91CE;
extern Spr D_800E91D8;
extern Spr D_800E92B8;
extern SprTex D_800E9398[2];
extern SprTex D_800E93F0[2];
extern s16 D_800E9448;
extern Spr D_800E9450[2];
extern Spr D_800E9608[2];
extern SprTex D_800E97C0[2];
extern SprTex D_800E9818[2];
extern s16 D_800E9870;
extern Spr D_800E9878[4];
extern Tex8 D_800E9BE8[20];
extern SprTex D_800E9C88[4];
extern s8 D_800E9D38[4];
extern Spr D_800E9D70[4];
extern Tex8 D_800EA0E0[4];
extern Tex8 D_800EA100[2];
extern Tex8 D_800EA110[20];
extern SprTex D_800EA1B0[4];
extern Spr D_800EA268[4];
extern Tex8 D_800EA5D8;
extern Tex8 D_800EA5E0;
extern SprTex D_800EA5E8[4];
extern SprTex D_800EA698[4];
extern Tex8 D_800EA748[2];
extern Spr D_800EA758[4];
extern SprTex D_800EAAC8[4];
extern Spr D_800EAB78;
extern SprTex D_800EAC58;
extern Spr D_800EAC88[4];
extern SprTex D_800EAFF8[4];
extern u16 D_800EB0AA;
extern s8 D_800F99B4;
extern s8 D_800F99B5;
extern s16 D_800F99B6;
extern s16 D_800F99B8;
extern s16 D_800F9A9C;
extern s8 D_800F9A9E;
extern s16 D_800F9AA0;
extern s16 D_800F9AA2;
extern s8 D_800F9AF8;
extern s16 D_800F9AFA;

void *allocateHeap(s32);
void releaseHeapBlock(void *);
void initializeTransformNode(void *, s32, f32, f32, f32);
void func_80006814(void *, void *, f32, f32);
void func_80001DC4(void *);
void func_800015AC(void *, s32);
void func_80001544(void *);
void guOrthoF(void *, f32, f32, f32, f32, f32, f32, f32);
void guLookAtF(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void multiplyMatrix4x4(void *, void *, void *);
void func_8000670C(void *, s16, s16);
#ifndef TARGET_PC /* on PC, port_decls.h declares convertRgba16ToGrayscale */
void convertRgba16ToGrayscale(s32, s32);
#endif
void func_80004F80(void *, s16, s16);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_80007960 */
void func_80007960(s32, s32);
#endif
void func_80090380(void *, u16);
void func_800907A0(void *, void *, s16, s16, f32, f32, f32, f32, u8, u8, u8, u8);
void func_800948B4(void);

/* func_800905A4: 480x240 orthographic camera node */
static inline void initCamera(Spr *n) {
    f32 proj[4][4];
    f32 view[4][4];
    f32 z[1]; /* one-element array: gives the sw zero/lw/move zero arguments (as func_800C1B24) */

    z[0] = 0.0f;
    initializeTransformNode(n, 5, z[0], z[0], z[0]);
    func_800015AC(n, 0);
    func_80001544(n);
    guOrthoF(proj, 0.0f, 480.0f, 0.0f, 240.0f, -1.0f, 10.0f, 1.0f);
    guLookAtF(view, 0.0f, 240.0f, -1.0f, 0.0f, 240.0f, 0.0f, 0.0f, -1.0f, 0.0f);
    multiplyMatrix4x4(view, proj, n->mtx);
    n->f19 = 1;
#ifdef TARGET_PC
    /* PC: node is the work block's handle; SLOT_TO_PTR gives the work block. */
    ((Cam *)SLOT_TO_PTR(n->node))->flags |= 0x80;
    ((Cam *)SLOT_TO_PTR(n->node))->f24 = -5000.0f;
    ((Cam *)SLOT_TO_PTR(n->node))->f20 = 100.0f;
#else
    n->node->flags |= 0x80;
    n->node->f24 = -5000.0f;
    n->node->f20 = 100.0f;
#endif
}

static inline void initSprite(Spr *n) {
    f32 z[1]; /* one-element array, as in initCamera */

    z[0] = 0.0f;
    initializeTransformNode(n, 5, z[0], z[0], z[0]);
    func_80006814(n, NULL, 0.0f, 0.0f);
    func_80001DC4(n);
#ifdef TARGET_PC
    /* PC: the work block through its handle, as in initCamera. */
    ((Cam *)SLOT_TO_PTR(n->node))->flags |= 0x80;
    ((Cam *)SLOT_TO_PTR(n->node))->f24 = -3000.0f;
#else
    n->node->flags |= 0x80;
    n->node->f24 = -3000.0f;
#endif
}

/* func_800906D8 */
static inline void loadTex(SprTex *n, s16 a, s16 b, s32 c) {
    Gfx2 *g;

    func_80004F80(n, a, b);
    func_80007960(n->f1C, c & 0xFF);
#ifdef TARGET_PC
    /* PC: the record's display list is its f10, by name; its commands are 16-byte Gfx. */
    g = n->f10;
#else
    g = n->dl;
#endif
    {
        Gfx2 *d = g++;
        d->w0 = 0xE200001C;
        d->w1 = 0x504240;
    }
    {
        Gfx2 *d = g++;
        d->w0 = 0xFC121824;
        d->w1 = 0xFF33FFFF;
    }
}

/* func_8009075C */
static inline void loadTexFrom(SprTex *n, Tex8 *v) {
#ifdef TARGET_PC
    /* PC: the pair's texture and palette are pointers, copied into the record's f18 and f1C by name, then cleared. */
    n->f18 = v->img;
    n->f1C = v->pal;
    func_80004F80(n, 0, 0);
    n->f18 = NULL;
    n->f1C = NULL;
#else
    n->f18 = v->w0;
    n->f1C = v->w1;
    func_80004F80(n, 0, 0);
    n->f18 = 0;
    n->f1C = 0;
#endif
}

void func_800922C0(void) {
    u32 i;
    u32 j;

    D_800F99B6 = 0;
    D_800F9AFA = 0;
    D_800E80C4 = 0;
    D_800E8B1A = 0;
    D_800F9A9C = 1;
    D_800EB0AA = D_800E2D84[D_8007E8C0[4]];
    for (i = 0; i < 5; i++) {
        initSprite(&D_800E7950[i]);
    }
    for (i = 0; i < 11; i++) {
        func_8000670C(&D_800E7DA0[i], i + 0x228, 0x227);
    }
    if (D_800EB0AA < 3 && ((u8 *)D_8007E8C0)[0x66E] == 0) {
        D_800F9AA2 = 1;
    } else {
        D_800F9AA2 = 0;
    }
    D_800F99B5 = 0;
    D_800F9A9E = 0;
    D_800F99B8 = 0;
    D_800F9AA0 = 0x6F;
    D_800F99B4 = 0;
    D_800F9AF8 = 0;
    initSprite(&D_800E77C0);
    D_800E7942 = 0x80;
#ifdef TARGET_PC
    /* PC: the object's display list is a handle (func_80006814 allocated it): free the list it names, then clear it. */
    releaseHeapBlock(SLOT_TO_PTR(D_800E77C0.dl));
    D_800E77C0.dl = 0;
#else
    releaseHeapBlock(D_800E77C0.dl);
    D_800E77C0.dl = NULL;
#endif
    for (i = 0; i < 3; i++) {
#ifdef TARGET_PC
        /* PC: each list holds the N64's 320 commands (0xA00 bytes of 8-byte commands), which func_80006814 writes
         * into it, at sizeof(Gfx) = 16 bytes each. */
        D_800E789C[i] = allocateHeap(0xA00 / 8 * sizeof(Gfx));
#else
        D_800E789C[i] = allocateHeap(0xA00);
#endif
    }
    D_800E7940 = 0;
    for (i = 0; i < 19; i++) {
        func_8000670C(&D_800E78A8[i], i * 2 + 0x2A5, i * 2 + 0x2A4);
        if (D_800307A0 == 1) {
#ifdef TARGET_PC
            /* PC: the pair's palette (16 colours), by name. */
            convertRgba16ToGrayscale(D_800E78A8[i].pal, 0x10);
#else
            convertRgba16ToGrayscale(D_800E78A8[i].w1, 0x10);
#endif
        }
    }
    for (i = 0; i < 3; i++) {
        func_80090380(&D_800E7FB8[i], 2);
        loadTex(&D_800E7FB8[i], i + 0x238, 0x237, 0);
        func_80090380(&D_800E8040[i], 2);
        loadTex(&D_800E8040[i], i + 0x234, 0x233, 0);
    }
    initCamera(&D_800E7ED8);
    initCamera(&D_800E7DF8);
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 10; i++) {
            func_80090380(&D_800E8438[j][i], 2);
            loadTex(&D_800E8438[j][i], i + 0x245, 0x237, 0);
            func_80090380(&D_800E87A8[j][i], 2);
            loadTex(&D_800E87A8[j][i], i + 0x23B, 0x233, 0);
        }
        initCamera(&D_800E8280[j]);
        initCamera(&D_800E80C8[j]);
    }
    D_800E8B1A = -1;
    D_800E8B18 = -1;
    for (i = 0; i < 2; i++) {
        func_80090380(&D_800E8CE8[i], 2);
        func_80090380(&D_800E8D40[i], 2);
        loadTex(&D_800E8CE8[i], D_800E2BEC[i] + 1, 0x226, 2);
        loadTex(&D_800E8D40[i], D_800E2BEC[i], 0x225, 2);
    }
    initCamera(&D_800E8C08);
    initCamera(&D_800E8B28);
    D_800E8D98 = 0;
    D_800E8D9A = -1;
    for (i = 0; i < 7; i++) {
        func_80090380(&D_800E8F60[i], 2);
        func_80090380(&D_800E9098[i], 2);
        if (*(u16 *)(D_8007E228 + 0x58) & 0x400) {
            loadTex(&D_800E8F60[i], D_800E2B54[i], 0x237, 0);
            loadTex(&D_800E9098[i], D_800E2B44[i], 0x233, 0);
        } else {
            loadTex(&D_800E8F60[i], D_800E2B34[i], 0x237, 0);
            loadTex(&D_800E9098[i], D_800E2B24[i], 0x233, 0);
        }
    }
    initCamera(&D_800E8E80);
    initCamera(&D_800E8DA0);
    D_800E91CE = 0;
    D_800E91CC = -1;
    for (i = 0; i < 2; i++) {
        func_80090380(&D_800E9398[i], 2);
        func_80090380(&D_800E93F0[i], 2);
        if (D_800E2B74[i] >= 0) {
            loadTex(&D_800E9398[i], D_800E2B74[i] + 1, 0x237, 0);
            loadTex(&D_800E93F0[i], D_800E2B74[i], 0x233, 0);
        }
    }
    initCamera(&D_800E92B8);
    initCamera(&D_800E91D8);
    D_800E9448 = -1;
    for (i = 0; i < 2; i++) {
        func_80090380(&D_800E97C0[i], 2);
        loadTex(&D_800E97C0[i], D_800E2BF0[i] + 1, 0x237, 0);
        func_80090380(&D_800E9818[i], 2);
        loadTex(&D_800E9818[i], D_800E2BF0[i], 0x233, 0);
    }
    initCamera(&D_800E9608[0]);
    initCamera(&D_800E9608[1]);
    initCamera(&D_800E9450[0]);
    initCamera(&D_800E9450[1]);
    D_800E9870 = -1;
    for (i = 0; i < 20; i++) {
        func_8000670C(&D_800E9BE8[i], i + 0x24F, 0x263);
    }
    for (i = 0; i < 4; i++) {
        func_80090380(&D_800E9C88[i], 1);
        initCamera(&D_800E9878[i]);
        D_800E9D38[i] = -1;
    }
    for (i = 0; i < 4; i++) {
#ifdef TARGET_PC
        /* PC: the pair's two pointers, by name. */
        D_800EA0E0[i].img = NULL;
        D_800EA0E0[i].pal = NULL;
#else
        D_800EA0E0[i].w0 = 0;
        D_800EA0E0[i].w1 = 0;
#endif
    }
    func_8000670C(&D_800EA100[0], 0x27E, 0x274);
    func_8000670C(&D_800EA100[1], 0x27F, 0x274);
    for (i = 0; i < 20; i++) {
#ifdef TARGET_PC
        /* PC: the pair's texture pointer, by name. */
        D_800EA110[i].img = NULL;
#else
        D_800EA110[i].w0 = 0;
#endif
        func_8000670C(&D_800EA110[i], 0, D_800E2C14[i]);
    }
    func_8000670C(&D_800EA5D8, 0x281, 0x280);
    func_8000670C(&D_800EA5E0, 0x283, 0x282);
    for (i = 0; i < 2; i++) {
        func_8000670C(&D_800EA748[i], D_800E2C08[i] + 1, D_800E2C08[i]);
    }
    func_80090380(&D_800EAC58, 1);
    initCamera(&D_800EAB78);
    loadTexFrom(&D_800EAC58, &D_800EA748[1]);
    func_800907A0(&D_800EAB78, &D_800EAC58, 0x40, 0x18, 0.0f, 0.0f, 2.0f, 1.0f, 0xFF, 0xFF, 0xFF, 0xFF);
    for (i = 0; i < 4; i++) {
        func_80090380(&D_800EA1B0[i], 1);
        if (((s32 *)(D_8007E228 + 0x688))[i] > 0) {
            if (!(*(u16 *)(D_8007E228 + 0x58) & 0x100)) {
                if (*(u16 *)(D_8007E228 + 0x58) & 0x400) {
                    if (i < 2) {
                        func_8000670C(&D_800EA0E0[i], D_800E2C3C[D_8007E8C0[i]] + 0x278, D_800E2C14[D_8007E8C0[i] * 2]);
                    } else {
                        func_8000670C(&D_800EA0E0[i], D_800E2C44[D_8007E8C0[i]] + 0x278, D_800E2C14[D_8007E8C0[i] * 2]);
                    }
                } else {
                    if (i < 2) {
                        func_8000670C(&D_800EA0E0[i], D_800E2C3C[D_8007E8C0[i]] + 0x278, 0x265);
                    } else {
                        func_8000670C(&D_800EA0E0[i], D_800E2C44[D_8007E8C0[i]] + 0x278, 0x269);
                    }
                }
            } else if (i == 0) {
                func_8000670C(&D_800EA0E0[i], D_800E2C3C[D_8007E8C0[i]] + 0x278, 0x264);
            } else {
                func_8000670C(&D_800EA0E0[i], D_800E2C44[D_8007E8C0[i]] + 0x278, 0x268);
            }
        } else {
            func_8000670C(&D_800EA0E0[i], 0x27E, 0x275);
        }
        loadTexFrom(&D_800EA1B0[i], &D_800EA0E0[i]);
        initCamera(&D_800E9D70[i]);
        func_80090380(&D_800EAFF8[i], 1);
        initCamera(&D_800EAC88[i]);
        initCamera(&D_800EA268[i]);
        func_80090380(&D_800EA5E8[i], 0);
        loadTexFrom(&D_800EA5E8[i], &D_800EA5D8);
        func_80090380(&D_800EA698[i], 0);
        loadTexFrom(&D_800EA698[i], &D_800EA5E0);
        func_80090380(&D_800EAAC8[i], 1);
        initCamera(&D_800EA758[i]);
        if (((s32 *)(D_8007E228 + 0x688))[i] > 0) {
            loadTexFrom(&D_800EAAC8[i], &D_800EA748[0]);
        }
    }
    func_800948B4();
}
