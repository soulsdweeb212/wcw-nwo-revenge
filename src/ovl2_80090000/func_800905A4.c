/* @header
 * func_800905A4
 * VRAM 0x800905A4 | ROM 0x83A44 | size 0x134
 * asm: asm/nonmatchings/ovl2_80090000/func_800905A4.s
 */
#include "common.h"

void initializeTransformNode(void *, s8, f32, f32, f32);
void func_800015AC(void *, s32);
void func_80001544(void *);
void guOrthoF(f32 m[4][4], f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, f32 scale);
void guLookAtF(f32 mf[4][4], f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
void multiplyMatrix4x4(f32 *, f32 *, f32 *);

typedef struct {
    u32 flags;
    u8 pad4[0x1C];
    f32 f20;
    f32 f24;
} Cam;

typedef struct {
    u8 pad0[0x14];
    Cam *cam;
    u8 pad18;
    u8 f19;
    u8 pad1A[0x82];
    f32 mtx[4][4];
} Node;

/* Set up a 480x240 orthographic camera node. */
void func_800905A4(Node *n) {
    f32 proj[4][4];
    f32 view[4][4];

    initializeTransformNode(n, 5, 0.0f, 0.0f, 0.0f);
    func_800015AC(n, 0);
    func_80001544(n);
    guOrthoF(proj, 0.0f, 480.0f, 0.0f, 240.0f, -1.0f, 10.0f, 1.0f);
    guLookAtF(view, 0.0f, 240.0f, -1.0f, 0.0f, 240.0f, 0.0f, 0.0f, -1.0f, 0.0f);
    multiplyMatrix4x4((f32 *)view, (f32 *)proj, (f32 *)n->mtx);
    n->f19 = 1;
    n->cam->flags |= 0x80;
    n->cam->f24 = -5000.0f;
    n->cam->f20 = 100.0f;
}
