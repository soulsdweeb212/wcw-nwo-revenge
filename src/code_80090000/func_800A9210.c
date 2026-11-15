/* @header
 * func_800A9210
 * VRAM 0x800A9210 | ROM 0x55980 | size 0x25C
 * asm: asm/nonmatchings/code_80090000/func_800A9210.s
 */
#include "common.h"

typedef struct { u8 pad[4]; s16 x, y, z, rx, ry, rz; } C;
#ifdef TARGET_PC
/* PC: D_800E9208 is D_800E8230[13], so w[0] and w[1] are the menus 13 and 14. The menus hold addresses, so they are
 * common.h's Nw2Menu (0x140 bytes on PC), which W follows (the asserts check), and the label has no PC symbol: the PC
 * reads &D_800E8230[13]. p is the menu's element list (Nw2MenuItems), i its f4, and m the local matrix of the menu's
 * scene object (Nw2SceneObj, which keeps its N64 layout). el, unused here, keeps its pointer where the other views
 * of the menus have it. */
typedef struct { u8 pad[8]; u8 i; } P;
typedef struct { P *p; u8 pad8[0x10]; void *el; u8 pad20[0x5C]; s32 m[0x31]; } W;
_Static_assert(offsetof(P, i) == offsetof(Nw2MenuItems, f4) && offsetof(W, el) == offsetof(Nw2Menu, el) &&
                   offsetof(W, m) == offsetof(Nw2Menu, obj) + offsetof(Nw2SceneObj, local) &&
                   sizeof(W) == sizeof(Nw2Menu),
               "W must follow common.h's Nw2Menu");
extern W D_800E8230[];
#else
typedef struct { u8 pad[4]; u8 i; } P;
typedef struct { P *p; u8 pad[0x70]; s32 m[0x31]; } W;
extern W D_800E9208[];
#endif
extern C D_800CC8A4[];
extern s32 D_800E7B58;
void guPositionF(void *, f32, f32, f32, f32, f32, f32, f32);

void func_800A9210(s32 a) {
#ifdef TARGET_PC
    W *w = &D_800E8230[13]; /* PC: by name (see above) */
#else
    W *w = D_800E9208;
#endif
    C *c = &D_800CC8A4[w[0].p->i];
    C *d = &D_800CC8A4[w[1].p->i];
    if (a) {
        guPositionF(w[0].m, c->rx, c->ry, c->rz, 1.0f, c->x - D_800E7B58 - 0x30, c->y, c->z);
        guPositionF(w[1].m, d->rx, d->ry, d->rz, 1.0f, d->x - D_800E7B58 + 0x30, d->y, d->z);
    } else {
        guPositionF(w[0].m, c->rx, c->ry, c->rz, 1.0f, c->x, c->y, c->z);
        guPositionF(w[1].m, d->rx, d->ry, d->rz, 1.0f, d->x, d->y, d->z);
    }
}
