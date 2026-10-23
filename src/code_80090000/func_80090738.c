#include "common.h"

/* Per-frame update for the 48-entry rotating effect table at D_800D6D50.
 * Advances the animation tick (D_800C9090), samples the camera/effect basis
 * via func_800B82B8, then for each active entry builds a scaled, spinning
 * (alternating +/-) matrix from its scale/amount, and marks inactive entries
 * with flag 0x80. Finishes by running the effect updater func_800940D8. */
extern s32 D_800C9090;
extern f64 D_800D5F80, D_800D5F88;
extern u8 D_800D6D50[];
extern f32 D_800E7504;
void func_80001DC4(void *);
void func_800B82B8(f32 *, f32 *, f32 *, s32 *, s32 *, s32 *);
void func_8001B3EC(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void buildScaledRotationTranslationMatrix(void *, f32, f32, f32, f32, f32, f32, f32);
void func_800940D8(void);
typedef struct { u8 head[0x18]; u8 flags; u8 pad[0x147]; s16 active; s16 pad162; s16 amount; u8 pad166[14]; f32 scale; } Effect90738;
void func_80090738(void) {
    f32 matrix[4][4];
    f32 x, y, z;
    s32 a, b, c;
    f32 angle, rotation;
    s32 tick, i;
    Effect90738 *initial, *base;
    void *m;
    initial = (Effect90738 *)D_800D6D50;
    func_80001DC4(initial);
    func_800B82B8(&x, &y, &z, &a, &b, &c);
    tick = D_800C9090 + 1;
    i = 0; base = initial;
    D_800C9090 = tick;
    angle = (f32)((f64)((tick & 0x3FF) * 360) * D_800D5F80);
    do {
        m = (u8 *)base + 0x5C;
        if (base->active > 0) {
            base->flags &= 0x7F;
            func_8001B3EC(m, 0.0f, 0.0f, 0.0f, &x, &y, &z);
            rotation = angle;
            if (!(i & 1)) rotation = -rotation;
            buildScaledRotationTranslationMatrix(m, 0.0f, 0.0f, rotation, (f32)((f64)(base->scale * 0.5f) * D_800D5F88 * (f64)base->amount * (f64)D_800E7504), x, y, z);
        } else { base->flags |= 0x80; }
        i++; base++;
    } while (i < 48);
    func_800940D8();
}
