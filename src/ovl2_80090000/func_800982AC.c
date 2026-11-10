/* @header
 * func_800982AC
 * VRAM 0x800982AC | ROM 0x8B74C | size 0x21C
 * asm: asm/nonmatchings/ovl2_80090000/func_800982AC.s
 */
#include "common.h"

#ifdef TARGET_PC
typedef Gfx G; /* on PC a command is port.h's 16-byte Gfx, which keeps a whole pointer in w1 */
#else
typedef struct {
    u32 w0;
    u32 w1;
} G;
#endif

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
void guOrthoF(void *, f32, f32, f32, f32, f32, f32, f32);
void guLookAtF(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
#ifdef TARGET_PC
/* PC: the definition's types (multiplyMatrix4x4.c), so that the compiler checks the call below. port_decls.h cannot
 * declare it yet, because other files still pass a flat f32[16] or a byte array. */
void multiplyMatrix4x4(f32 arg0[4][4], f32 arg1[4][4], f32 arg2[4][4]);
#else
void multiplyMatrix4x4(void *, void *, void *);
#endif
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
    guOrthoF(proj, 0.0f, 480.0f, 0.0f, 240.0f, -1.0f, 10.0f, 1.0f);
    guLookAtF(view, 0.0f, 240.0f, -1.0f, 0.0f, 240.0f, 0.0f, 0.0f, -1.0f, 0.0f);
#ifdef TARGET_PC
    /* PC: view, proj and mtx each hold the 16 floats of a 4x4 matrix, which the function takes as f32[4][4]. */
    multiplyMatrix4x4((f32(*)[4])view, (f32(*)[4])proj, (f32(*)[4])D_800EB0B0.mtx);
#else
    multiplyMatrix4x4(view, proj, D_800EB0B0.mtx);
#endif
    D_800EB0B0.f19 = 1;
    /* struct fields: the node stores must reload the pointer, and f19 must stay before them */
    D_800EB0B0.node->flags |= 0x80;
    D_800EB0B0.node->f24 = -5000.0f;
    D_800EB0B0.node->f20 = 100.0f;
    for (i = 0; i < 3; i++) {
#ifdef TARGET_PC
        /* PC: room for the same 1024 commands at 16 bytes each instead of 8. */
        g = D_800EB18C[i] = allocateHeap(0x2000 / 8 * sizeof(G));
#else
        g = D_800EB18C[i] = allocateHeap(0x2000);
#endif
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
