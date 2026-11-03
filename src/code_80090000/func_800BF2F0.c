/* @header
 * func_800BF2F0
 * VRAM 0x800BF2F0 | ROM 0x6BA60 | size 0x36C
 * asm: asm/nonmatchings/code_80090000/func_800BF2F0.s
 */
#include "common.h"

typedef struct { u16 f0; u16 f2; s16 f4; s16 len; s16 v[4]; u16 flags; u16 f12; } Key;
typedef struct { Key *keys; f32 x, y, z; s32 r; s16 idx; s16 t; } Anim;
typedef struct { u8 pad0[0x6B8]; s16 f6B8; u8 pad6BA[0xA]; s32 f6C4; } WrF2F0;

extern f64 D_800D6AD0;
void buildScaledRotationTranslationMatrix(void *, f32, f32, f32, f32, f32, f32, f32);
void func_8001B3EC(void *, f32, f32, f32, f32 *, f32 *, f32 *);

void func_800BF2F0(WrF2F0 *w, Anim *a) {
    Key *k = &a->keys[a->idx];
    s32 s = 0;
    s32 done = 0;
    s32 n;
    f32 m[16];

    switch (k->flags & 7) {
    case 2:
        s = 0xC;
        break;
    case 1:
        s = 4;
        break;
    case 3:
        s = 4;
        break;
    case 4:
        if (k->len >= 0) {
            n = k->len;
        } else {
            n = w->f6B8 - k->f2;
        }
        if (n > 0) {
            a->x = k[0].v[0] + (k[1].v[0] - k[0].v[0]) * a->t / n;
            a->y = k[0].v[1] + (k[1].v[1] - k[0].v[1]) * a->t / n;
            a->z = k[0].v[2] + (k[1].v[2] - k[0].v[2]) * a->t / n;
            a->r = k[0].v[3] + (k[1].v[3] - k[0].v[3]) * a->t / n;
            done = 1;
        }
        break;
    }
    if (s != 0) {
        buildScaledRotationTranslationMatrix(m, 0.0f, a->r * D_800D6AD0, 0.0f, 1.0f, a->x, a->y, a->z);
        func_8001B3EC(m, 0.0f, 0.0f, s, &a->x, &a->y, &a->z);
    }
    if (!done && w->f6C4 == 4 && -300.0f < a->x && a->x < 300.0f && -300.0f < a->z && a->z < 300.0f) {
        a->y = 90.0f;
    }
}
