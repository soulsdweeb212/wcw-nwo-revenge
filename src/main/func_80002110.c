/* @header
 * func_80002110
 * VRAM 0x80002110 | ROM 0x2D10 | size 0x214
 * asm: asm/nonmatchings/main/func_80002110.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: Obj2110 is a work block, which keeps its N64 layout (Nw2SceneWork in common.h), so its owner (model) and next
 * hold 4-byte handles (port.h's PTR_TO_SLOT) and the code below turns them back with SLOT_TO_PTR. dl holds the handle
 * of a display list, which is copied as it is. The asserts check the view against Nw2SceneWork. */
typedef struct Obj2110 {
    s32 type;
    u32 model;
    u32 next;
    u8 pad0C[0xC];
    f32 x, y, z;
    u8 pad24[0x10];
    u32 dl;
    f32 mtx[4][4][4];
} Obj2110;
_Static_assert(offsetof(Obj2110, model) == offsetof(Nw2SceneWork, owner) &&
                   offsetof(Obj2110, next) == offsetof(Nw2SceneWork, next) &&
                   offsetof(Obj2110, x) == offsetof(Nw2SceneWork, eye) &&
                   offsetof(Obj2110, dl) == offsetof(Nw2SceneWork, dl) &&
                   offsetof(Obj2110, mtx) == offsetof(Nw2SceneWork, mtx),
               "Obj2110 must follow Nw2SceneWork");
#else
typedef struct Obj2110 {
    s32 type;
    u8 *model;
    struct Obj2110 *next;
    u8 pad0C[0xC];
    f32 x, y, z;
    u8 pad24[0x10];
    u32 dl;
    f32 mtx[4][4][4];
} Obj2110;
#endif

extern s16 D_80047062;
extern s16 D_80047066;
#ifndef TARGET_PC /* on PC, port_decls.h declares D_80046860 */
extern Obj2110 *D_80046860[];
#endif
#ifndef TARGET_PC /* on PC, port_decls.h declares D_80047070 */
extern Obj2110 *D_80047070[][512];
#endif
extern u8 D_80048070[];
f32 func_80003CF0(f32);
void guMtxF2L(void *, void *);

static inline s32 func_80002110_visible(Obj2110 *p)
{
    f32 z = p->z + 150.0f;

    if (z <= 0.0f) {
        return 0;
    }
    if (func_80003CF0(p->x / z) > 1.5 || func_80003CF0(p->y / z) > 1.5) {
        return 0;
    }
    return 1;
}

void func_80002110(s16 bank, s32 group, s8 kind)
{
    u32 i;
    Obj2110 *p;
    u32 dl;
    s32 type;
    s32 g;

    i = 0;
    g = group;
    for (; i < (u32)D_80047062; i++) {
        if (D_80048070[i] == (g & 0xFF)) {
            p = D_80046860[i];
            type = p->type;
            if (type == kind) {
                D_80048070[i] = 0xFF;
                D_80047070[bank][D_80047066] = p;
                if (type == 1) {
                    if (!func_80002110_visible(p)) {
                        continue;
                    }
                    while (p != NULL) {
#ifdef TARGET_PC
                        /* PC: the owner and the next block are handles (see Obj2110 above); the owner's +0x9C is
                         * its view matrix. */
                        guMtxF2L(((Nw2SceneObj *)SLOT_TO_PTR(p->model))->view, p->mtx[bank]);
                        p = SLOT_TO_PTR(p->next);
#else
                        guMtxF2L(p->model + 0x9C, p->mtx[bank]);
                        p = p->next;
#endif
                    }
                } else {
                    while (p != NULL) {
#ifdef TARGET_PC
                        /* PC: as above. The owner's display list at +0x10 is a handle too, and the block's dl takes
                         * the handle as it is. */
                        dl = ((Nw2SceneObj *)SLOT_TO_PTR(p->model))->dl;
                        if (dl) {
                            p->dl = dl;
                        }
                        guMtxF2L(((Nw2SceneObj *)SLOT_TO_PTR(p->model))->view, p->mtx[bank]);
                        p = SLOT_TO_PTR(p->next);
#else
                        dl = *(u32 *)(p->model + 0x10);
                        if (dl) {
                            p->dl = dl;
                        }
                        guMtxF2L(p->model + 0x9C, p->mtx[bank]);
                        p = p->next;
#endif
                    }
                }
                D_80047066++;
            }
        }
    }
}
