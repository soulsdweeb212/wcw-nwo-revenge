/* @header
 * func_80002110
 * VRAM 0x80002110 | ROM 0x2D10 | size 0x214
 * asm: asm/nonmatchings/main/func_80002110.s
 */
#include "common.h"

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

extern s16 D_80047062;
extern s16 D_80047066;
extern Obj2110 *D_80046860[];
extern Obj2110 *D_80047070[][512];
extern u8 D_80048070[];
f32 func_80003CF0(f32);
void func_8001B090(void *, void *);

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
                        func_8001B090(p->model + 0x9C, p->mtx[bank]);
                        p = p->next;
                    }
                } else {
                    while (p != NULL) {
                        dl = *(u32 *)(p->model + 0x10);
                        if (dl) {
                            p->dl = dl;
                        }
                        func_8001B090(p->model + 0x9C, p->mtx[bank]);
                        p = p->next;
                    }
                }
                D_80047066++;
            }
        }
    }
}
