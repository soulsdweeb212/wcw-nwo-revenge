#include "common.h"

extern u32 D_80037230;

typedef struct {
    f32 m[12];
    f32 x, y, z;
} Xform;

void func_8001B090(void *, void *);

/* Steps the gameplay RNG seed. */
void func_8001C580(void) {
    D_80037230 = (u32)((D_80037230 * 4 + 2) * (D_80037230 * 4 + 3)) >> 2;
}

/* Builds a translation matrix (arg1/arg2/arg3) and converts it to fixed point
 * at arg0. */
void func_8001C144(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    Xform s;
    Xform *p = &s;

    initIdentityMatrix4x4(p);
    p->x = arg1;
    p->y = arg2;
    p->z = arg3;
    func_8001B090(p, arg0);
}
