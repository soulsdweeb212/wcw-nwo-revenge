/* @header
 * func_800907A0
 * VRAM 0x800907A0 | ROM 0x83C40 | size 0x298
 * asm: asm/nonmatchings/ovl2_80090000/func_800907A0.s
 */
#include "common.h"

void func_80007920(void *, s16, s16, s16, s16, u8, u8, u8, u8);

typedef struct {
    u8 v[16];
} Vtx16;

typedef struct {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 pad3[5];
    s16 w;
    s16 h;
    Vtx16 *vtx;
    void *dl2;
    void *dl;
} Node;
#ifdef TARGET_PC
/* PC: n is a display record of a picture (common.h's Nw2Descr4BA8, whose first 0x20 bytes follow Nw2TextureDisplayObj).
 * With 8-byte pointers, Node's w, h, vtx, dl2 and dl fall on that struct's width, height, colorPtr (the vertices), dl
 * (the material list) and next, as the asserts check. dst is not such a record but a 0xDC-byte scene object
 * (Nw2SceneObj); see the store at the end. */
_Static_assert(offsetof(Node, w) == offsetof(Nw2TextureDisplayObj, width) &&
                   offsetof(Node, h) == offsetof(Nw2TextureDisplayObj, height) &&
                   offsetof(Node, vtx) == offsetof(Nw2TextureDisplayObj, colorPtr) &&
                   offsetof(Node, dl2) == offsetof(Nw2TextureDisplayObj, dl) &&
                   offsetof(Node, dl) == offsetof(Nw2TextureDisplayObj, next),
               "Node must follow the PC layout of Nw2TextureDisplayObj");
#endif

/* Fill the sprite's four vertices: an x by y rectangle of w*sx by h*sy anchored at (ax, ay). */
void func_800907A0(Node *dst, Node *n, s16 x, s16 y, f32 ax, f32 ay, f32 sx, f32 sy, u8 r, u8 g, u8 b, u8 a) {
    Vtx16 *v;
    s16 w;
    s16 h;
    f32 sw;
    f32 sh;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;

    v = n->vtx;
    w = n->w;
    h = n->h;
    sw = w * sx;
    x0 = x - sw * ax;
    x1 = x + sw * (1.0 - ax);
    sh = h * sy;
    y0 = y - sh * ay;
    y1 = y + sh * (1.0 - ay);
    /* texture coordinates are 10.5 fixed point */
    w <<= 5;
    h <<= 5;
    func_80007920(v++, x0, y0, 0x1F, 0x1F, r, g, b, a);
    func_80007920(v++, x0, y1, 0x1F, h - 1, r, g, b, a);
    func_80007920(v++, x1, y0, w - 1, 0x1F, r, g, b, a);
    func_80007920(v, x1, y1, w - 1, h - 1, r, g, b, a);
    if (dst != NULL) {
#ifdef TARGET_PC
        /* PC: dst is a scene object, which keeps its N64 layout, so its display list at +0x10 is a 4-byte handle
         * (port.h's PTR_TO_SLOT) of the record's material list (f10), not Node's dl2 at +0x18. */
        ((Nw2SceneObj *)dst)->dl = PTR_TO_SLOT(((Nw2Descr4BA8 *)n)->f10);
#else
        dst->dl2 = n->dl2;
#endif
    }
}
