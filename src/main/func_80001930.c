/* @header
 * func_80001930
 * VRAM 0x80001930 | ROM 0x2530 | size 0x2F8
 * asm: asm/nonmatchings/main/func_80001930.s
 */
#include "common.h"

void guMtxXFMF(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void guNormalize(f32 *, f32 *, f32 *);
extern f64 D_8003B0A0;
extern f32 D_80048270, D_80048274, D_80048278, D_8004827C, D_80048280;
typedef struct V1930 { u8 pad[12]; s8 nx, ny, nz; u8 alpha; } V1930;
#ifndef TARGET_PC /* on PC, the function reads the object and its work blocks as Nw2SceneObj and Nw2SceneWork */
typedef struct L1930 { s32 f0; u8 *model; struct L1930 *next; f32 x, y, z; u8 pad18[20]; s16 count; u8 pad2E[2]; V1930 *vertices; } L1930;
typedef struct N1930 { s32 f0; struct N1930 *child, *next; u8 padC[8]; L1930 *list; u8 pad18[2]; u8 enabled; u8 pad1B[0x41]; f32 matrix[16]; } N1930;
#endif

#ifdef TARGET_PC
/* PC: the objects (N1930 on the N64) and their work blocks (L1930) keep their N64 layout (Nw2SceneObj and Nw2SceneWork
 * in common.h), so their links hold handles (port.h's PTR_TO_SLOT): the object's child, next and first work block, and
 * the block's owner, next and vertices. This version reads the same fields by name and turns each handle back with
 * SLOT_TO_PTR. The object's matrix at +0x5C is its world matrix, and the owner's too. */
void func_80001930(Nw2SceneObj *node) {
    f32 sp20, sp24, sp28, sp2C, sp30, sp34, sp38, sp3C, sp40;
    f32 dot, value;
    u32 i;
    V1930 *p;
    Nw2SceneWork *list;
    Nw2SceneObj *model;

    for (; node != NULL; node = SLOT_TO_PTR(node->next)) {
        list = SLOT_TO_PTR(node->work);
        if (list && node->lit) {
            guMtxXFMF(node->world, list->center[0], list->center[1], list->center[2], &sp20, &sp24, &sp28);
            sp20 = D_80048278 - sp20;
            sp24 = D_8004827C - sp24;
            sp28 = D_80048280 - sp28;
            guNormalize(&sp20, &sp24, &sp28);
            for (; list != NULL; list = SLOT_TO_PTR(list->next)) {
                model = SLOT_TO_PTR(list->owner);
                guMtxXFMF(model->world, 0.0f, 0.0f, 0.0f, &sp2C, &sp30, &sp34);
                p = SLOT_TO_PTR(list->vtx);
                for (i = 0; i < (u32)list->count; i++, p++) {
                    guMtxXFMF(model->world, (f32)p->nx, (f32)p->ny, (f32)p->nz, &sp38, &sp3C, &sp40);
                    sp38 -= sp2C;
                    sp3C -= sp30;
                    sp40 -= sp34;
                    guNormalize(&sp38, &sp3C, &sp40);
                    dot = sp20 * sp38 + sp24 * sp3C + sp28 * sp40;
                    value = D_80048274;
                    if (dot > 0.0f) {
                        value += D_80048270 * dot;
                        if (D_8003B0A0 < value) {
                            value = 255.0f;
                        }
                    }
                    p->alpha = value;
                }
            }
        }
        if (node->child) {
            func_80001930(SLOT_TO_PTR(node->child));
        }
    }
}
#else
void func_80001930(N1930 *node) {
    f32 sp20, sp24, sp28, sp2C, sp30, sp34, sp38, sp3C, sp40;
    f32 dot, value;
    u32 i;
    V1930 *p;
    L1930 *list;

    for (; node != NULL; node = node->next) {
        list = node->list;
        if (list && node->enabled) {
            guMtxXFMF(node->matrix, list->x, list->y, list->z, &sp20, &sp24, &sp28);
            sp20 = D_80048278 - sp20;
            sp24 = D_8004827C - sp24;
            sp28 = D_80048280 - sp28;
            guNormalize(&sp20, &sp24, &sp28);
            for (; list != NULL; list = list->next) {
                guMtxXFMF(list->model + 0x5C, 0.0f, 0.0f, 0.0f, &sp2C, &sp30, &sp34);
                p = list->vertices;
                for (i = 0; i < (u32)list->count; i++, p++) {
                    guMtxXFMF(list->model + 0x5C, (f32)p->nx, (f32)p->ny, (f32)p->nz, &sp38, &sp3C, &sp40);
                    sp38 -= sp2C;
                    sp3C -= sp30;
                    sp40 -= sp34;
                    guNormalize(&sp38, &sp3C, &sp40);
                    dot = sp20 * sp38 + sp24 * sp3C + sp28 * sp40;
                    value = D_80048274;
                    if (dot > 0.0f) {
                        value += D_80048270 * dot;
                        if (D_8003B0A0 < value) {
                            value = 255.0f;
                        }
                    }
                    p->alpha = value;
                }
            }
        }
        if (node->child) {
            func_80001930(node->child);
        }
    }
}
#endif
