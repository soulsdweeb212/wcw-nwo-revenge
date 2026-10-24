#include "common.h"

void func_8001B3EC(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_8001B4A0(f32 *, f32 *, f32 *);
extern f64 D_8003B0A0;
extern f32 D_80048270, D_80048274, D_80048278, D_8004827C, D_80048280;
typedef struct V1930 { u8 pad[12]; s8 nx, ny, nz; u8 alpha; } V1930;
typedef struct L1930 { s32 f0; u8 *model; struct L1930 *next; f32 x, y, z; u8 pad18[20]; s16 count; u8 pad2E[2]; V1930 *vertices; } L1930;
typedef struct N1930 { s32 f0; struct N1930 *child, *next; u8 padC[8]; L1930 *list; u8 pad18[2]; u8 enabled; u8 pad1B[0x41]; f32 matrix[16]; } N1930;

void func_80001930(N1930 *node) {
    f32 sp20, sp24, sp28, sp2C, sp30, sp34, sp38, sp3C, sp40;
    f32 dot, value;
    u32 i;
    V1930 *p;
    L1930 *list;

    for (; node != NULL; node = node->next) {
        list = node->list;
        if (list && node->enabled) {
            func_8001B3EC(node->matrix, list->x, list->y, list->z, &sp20, &sp24, &sp28);
            sp20 = D_80048278 - sp20;
            sp24 = D_8004827C - sp24;
            sp28 = D_80048280 - sp28;
            func_8001B4A0(&sp20, &sp24, &sp28);
            for (; list != NULL; list = list->next) {
                func_8001B3EC(list->model + 0x5C, 0.0f, 0.0f, 0.0f, &sp2C, &sp30, &sp34);
                p = list->vertices;
                for (i = 0; i < (u32)list->count; i++, p++) {
                    func_8001B3EC(list->model + 0x5C, (f32)p->nx, (f32)p->ny, (f32)p->nz, &sp38, &sp3C, &sp40);
                    sp38 -= sp2C;
                    sp3C -= sp30;
                    sp40 -= sp34;
                    func_8001B4A0(&sp38, &sp3C, &sp40);
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
