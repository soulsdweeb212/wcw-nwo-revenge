/* @header
 * func_800982AC
 * VRAM 0x800982AC | ROM 0x8B74C | size 0x21C
 * asm: asm/nonmatchings/ovl2_80090000/func_800982AC.s
 */
#include "common.h"

typedef struct {
    u32 w0;
    u32 w1;
} G;

typedef struct {
    s32 flags;
    u8 pad4[0x1C];
    f32 f20;
    f32 f24;
} Node;

typedef struct {
    u8 pad0[0x14];
    Node *node;
    u8 pad18;
    u8 f19;
    u8 pad1A[0x82];
    f32 mtx[16];
} ObjDC; /* 0xDC-byte display object; D_800EB0C4 = .node, D_800EB0C9 = .f19 */

extern ObjDC D_800EB0B0;
extern G *D_800EB18C[3];
extern s16 D_800EB198;
typedef struct {
    s16 id;
    s16 scale;
    s16 x;
    s16 y;
    void *tex;
} Icon;
extern Icon D_800EB19C;
extern s16 D_800EB1A8;
extern Icon D_800EB1AC;
extern u8 *D_800EB1B8;
extern u16 D_800EB1BC;
extern s16 D_800EB1BE;

void func_8002AA28(void);
void initializeTransformNode(void *, s32, f32, f32, f32);
void func_800015AC(void *, s32);
void func_80001544(void *);
void buildOrthoMatrixFloat(void *, f32, f32, f32, f32, f32, f32, f32);
void func_8001A980(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void multiplyMatrix4x4(void *, void *, void *);
void *allocateHeap(s32);

void func_800982AC(void) {
    f32 proj[16];
    f32 view[16];
    u32 i;
    G *g;

    func_8002AA28();
    initializeTransformNode(&D_800EB0B0, 5, 0.0f, 0.0f, 0.0f);
    func_800015AC(&D_800EB0B0, 0);
    func_80001544(&D_800EB0B0);
    buildOrthoMatrixFloat(proj, 0.0f, 480.0f, 0.0f, 240.0f, -1.0f, 10.0f, 1.0f);
    func_8001A980(view, 0.0f, 240.0f, -1.0f, 0.0f, 240.0f, 0.0f, 0.0f, -1.0f, 0.0f);
    multiplyMatrix4x4(view, proj, D_800EB0B0.mtx);
    D_800EB0B0.f19 = 1;
    /* struct fields: the node stores must reload the pointer, and f19 must stay before them */
    D_800EB0B0.node->flags |= 0x80;
    D_800EB0B0.node->f24 = -5000.0f;
    D_800EB0B0.node->f20 = 100.0f;
    for (i = 0; i < 3; i++) {
        g = D_800EB18C[i] = allocateHeap(0x2000);
        g->w0 = 0xDF000000;
        g->w1 = 0;
    }
    /* store order is the ROM's: D_800EB1AC.id must come after .y (id first scores 4) */
    D_800EB198 = 0;
    D_800EB1A8 = -1;
    D_800EB19C.id = -1;
    D_800EB19C.scale = 1;
    D_800EB19C.x = 0xF0;
    D_800EB19C.y = 0xB4;
    D_800EB19C.tex = 0;
    D_800EB1AC.scale = 1;
    D_800EB1AC.x = 0xF0;
    D_800EB1AC.y = 0x8C;
    D_800EB1AC.id = -1;
    D_800EB1AC.tex = 0;
    D_800EB1B8 = allocateHeap(0x100);
    D_800EB1B8[0] = 0;
    D_800EB1BE = -1;
    D_800EB1BC = 0;
}
