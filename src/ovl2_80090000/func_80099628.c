/* @header
 * func_80099628
 * VRAM 0x80099628 | ROM 0x8CAC8 | size 0x2C4
 * asm: asm/nonmatchings/ovl2_80090000/func_80099628.s
 */
#include "common.h"

#ifdef TARGET_PC
typedef Gfx G; /* on PC a command is port.h's 16-byte Gfx, which keeps a whole pointer in w1 */
#else
typedef struct {
    u32 w0, w1;
} G;
#endif

#ifndef TARGET_PC /* on PC, D_800EB1C0 is common.h's Nw2SceneObj and its work block a Nw2SceneWork, read by name */
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
#endif

#ifndef TARGET_PC /* on PC, port_decls.h declares D_800EB1C0 (a Nw2SceneObj) */
extern ObjDC D_800EB1C0;
#endif
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
void guOrthoF(void *, f32, f32, f32, f32, f32, f32, f32);
void guLookAtF(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
#ifdef TARGET_PC
/* PC: the definition's types (multiplyMatrix4x4.c), so that the compiler checks the call below. port_decls.h cannot
 * declare it yet, because other files still pass a flat f32[16] or a byte array. */
void multiplyMatrix4x4(f32 arg0[4][4], f32 arg1[4][4], f32 arg2[4][4]);
#else
void multiplyMatrix4x4(void *, void *, void *);
#endif
void *allocateHeap(u32);
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void lookupResourceDescriptor(void *, u16);
void func_80003684(void *, u16, void *);
#endif

void func_80099628(void) {
    s32 desc[4];
    f32 proj[4][4];
    f32 view[4][4];
    s32 buf[4];
    u32 i;
    s32 id;
    G *g;
    void *p;
#ifdef TARGET_PC
    Nw2SceneWork *work;
#endif

    initializeTransformNode(&D_800EB1C0, 5, 0.0f, 0.0f, 0.0f);
    func_800015AC(&D_800EB1C0, 0);
    func_80001544(&D_800EB1C0);
    guOrthoF(proj, 0.0f, 480.0f, 0.0f, 240.0f, -1.0f, 10.0f, 1.0f);
    guLookAtF(view, 0.0f, 240.0f, -1.0f, 0.0f, 240.0f, 0.0f, 0.0f, -1.0f, 0.0f);
#ifdef TARGET_PC
    /* PC: the product goes to the object's view matrix (+0x9C). The object keeps its N64 layout (Nw2SceneObj), so its
     * work (+0x14) is the handle (port.h's PTR_TO_SLOT) of its work block (Nw2SceneWork), which func_800015AC set up:
     * kind 0x80 hides it, bias is the block's depth bias (+0x24) and eye[2] its +0x20. */
    multiplyMatrix4x4(view, proj, D_800EB1C0.view);
    D_800EB1C0.flat = 1;
    work = SLOT_TO_PTR(D_800EB1C0.work);
    work->kind |= 0x80;
    work->bias = -5000.0f;
    work->eye[2] = 100.0f;
#else
    multiplyMatrix4x4(view, proj, D_800EB1C0.mtx);
    D_800EB1C0.f19 = 1;
    D_800EB1C0.node->flags |= 0x80;
    D_800EB1C0.node->f24 = -5000.0f;
    D_800EB1C0.node->f20 = 100.0f;
#endif
    for (i = 0; i < 3; i++) {
#ifdef TARGET_PC
        /* PC: room for the same 512 commands at 16 bytes each instead of 8. */
        g = allocateHeap(0x1000 / 8 * sizeof(G));
#else
        g = allocateHeap(0x1000);
#endif
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
