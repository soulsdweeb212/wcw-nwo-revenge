/* @header
 * func_800A9210
 * VRAM 0x800A9210 | ROM 0x55980 | size 0x25C
 * asm: asm/nonmatchings/code_80090000/func_800A9210.s
 */
#include "common.h"

typedef struct { u8 pad[4]; s16 x, y, z, rx, ry, rz; } C;
typedef struct { u8 pad[4]; u8 i; } P;
typedef struct { P *p; u8 pad[0x70]; s32 m[0x31]; } W;
extern W D_800E9208[];
extern C D_800CC8A4[];
extern s32 D_800E7B58;
void guPositionF(void *, f32, f32, f32, f32, f32, f32, f32);

void func_800A9210(s32 a) {
    W *w = D_800E9208;
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
