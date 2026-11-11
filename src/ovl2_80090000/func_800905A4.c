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

#ifdef TARGET_PC
/* PC: Node is the game's 0xDC-byte scene object, common.h's Nw2SceneObj, which keeps its N64 layout on PC: the address
 * of its first work block at +0x14 is a 4-byte handle (port.h's PTR_TO_SLOT), f19 is its flat byte and mtx its view
 * matrix. Cam is that work block: its kind word, the depth in camera space at +0x20 (f20) and the depth bias at +0x24
 * (f24). Code reaches the work block through SLOT_TO_PTR. The asserts check both views against those records. */
typedef struct {
    u8 pad0[0x14];
    u32 cam;
    u8 pad18;
    u8 f19;
    u8 pad1A[0x82];
    f32 mtx[4][4];
} Node;
_Static_assert(sizeof(Node) == sizeof(Nw2SceneObj) && offsetof(Node, cam) == offsetof(Nw2SceneObj, work) &&
                   offsetof(Node, f19) == offsetof(Nw2SceneObj, flat) &&
                   offsetof(Node, mtx) == offsetof(Nw2SceneObj, view),
               "Node must follow Nw2SceneObj");
_Static_assert(offsetof(Cam, flags) == offsetof(Nw2SceneWork, kind) &&
                   offsetof(Cam, f20) == offsetof(Nw2SceneWork, eye) + 2 * sizeof(f32) &&
                   offsetof(Cam, f24) == offsetof(Nw2SceneWork, bias),
               "Cam must follow Nw2SceneWork");
#else
typedef struct {
    u8 pad0[0x14];
    Cam *cam;
    u8 pad18;
    u8 f19;
    u8 pad1A[0x82];
    f32 mtx[4][4];
} Node;
#endif

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
#ifdef TARGET_PC
    /* PC: the object's work block through its handle (see Node above). */
    ((Cam *)SLOT_TO_PTR(n->cam))->flags |= 0x80;
    ((Cam *)SLOT_TO_PTR(n->cam))->f24 = -5000.0f;
    ((Cam *)SLOT_TO_PTR(n->cam))->f20 = 100.0f;
#else
    n->cam->flags |= 0x80;
    n->cam->f24 = -5000.0f;
    n->cam->f20 = 100.0f;
#endif
}
