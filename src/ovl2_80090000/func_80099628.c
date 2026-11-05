/* @header
 * func_80099628
 * VRAM 0x80099628 | ROM 0x8CAC8 | size 0x2C4
 * asm: asm/nonmatchings/ovl2_80090000/func_80099628.s
 */
#include "common.h"

typedef struct {
    u32 w0, w1;
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
    u8 pad1A[0x9C - 0x1A];
    u8 mtx[0xDC - 0x9C];
} ObjDC;

extern ObjDC D_800EB1C0;
extern G *D_800EB29C[3];
extern s8 D_800EB2AC[6];
extern s16 D_800EB2B2;
extern s16 D_800EB2B4;
extern void *D_800EB2B8[0x23];
extern s32 D_8007E8C0[];
extern u16 D_800E2F50[];

void initializeTransformNode(void *, s32, f32, f32, f32);
void func_800015AC(void *, s32);
void func_80001544(void *);
void buildOrthoMatrixFloat(void *, f32, f32, f32, f32, f32, f32, f32);
void func_8001A980(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void multiplyMatrix4x4(void *, void *, void *);
void *allocateHeap(u32);
void lookupResourceDescriptor(void *, u16);
void func_80003684(void *, u16, void *);

void func_80099628(void) {
    s32 desc[4];
    f32 proj[4][4];
    f32 view[4][4];
    s32 buf[4];
    u32 i;
    s32 id;
    G *g;
    void *p;

    initializeTransformNode(&D_800EB1C0, 5, 0.0f, 0.0f, 0.0f);
    func_800015AC(&D_800EB1C0, 0);
    func_80001544(&D_800EB1C0);
    buildOrthoMatrixFloat(proj, 0.0f, 480.0f, 0.0f, 240.0f, -1.0f, 10.0f, 1.0f);
    func_8001A980(view, 0.0f, 240.0f, -1.0f, 0.0f, 240.0f, 0.0f, 0.0f, -1.0f, 0.0f);
    multiplyMatrix4x4(view, proj, D_800EB1C0.mtx);
    D_800EB1C0.f19 = 1;
    D_800EB1C0.node->flags |= 0x80;
    D_800EB1C0.node->f24 = -5000.0f;
    D_800EB1C0.node->f20 = 100.0f;
    for (i = 0; i < 3; i++) {
        g = allocateHeap(0x1000);
        D_800EB29C[i] = g;
        g->w0 = 0xDF000000;
        g->w1 = 0;
    }
    for (i = 0; i < 0x23; i++) {
        id = i + 0x2CA;
        lookupResourceDescriptor(desc, id);
        p = allocateHeap(desc[2]);
        D_800EB2B8[i] = p;
        func_80003684(buf, id, p);
    }
    for (i = 0; i < 6; i++) {
        D_800EB2AC[i] = 0;
    }
    D_800EB2B4 = D_800E2F50[D_8007E8C0[4]];
    D_800EB2B2 = 0;
    for (i = 0; i < D_800EB2B4; i++) {
        if (D_8007E8C0[i] != 0) {
            D_800EB2B2++;
        }
    }
    if ((D_8007E280 & 0x1000) && D_800EB2B2 > 0) {
        D_800EB2AC[1] = -1;
    }
    if (!(D_8007E280 & 0x100)) {
        D_800EB2AC[4] = -1;
    }
    if (D_8007E280 & 0x200) {
        D_800EB2AC[5] = -1;
    }
}
