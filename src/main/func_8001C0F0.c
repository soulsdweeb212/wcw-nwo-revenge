#include "common.h"

extern u32 D_80037230;

typedef struct {
    f32 m[12];
    f32 x, y, z;
} Xform;

void func_8001B090(void *, void *);
s32 nw2DisableInterrupts(void);
void nw2RestoreInterrupts(s32);

typedef struct {
    s32 f0;
    s32 f4;
} Tbl;

extern Tbl D_8007DF30[];

/* Advance the pseudo-random sequence. */
void func_8001C580(void) {
    s32 t = D_80037230 * 4;
    D_80037230 = (u32)((t + 2) * (t + 3)) >> 2;
}

/* Build an identity matrix translated to (arg1,arg2,arg3) in a local and convert it. */
void func_8001C144(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    Xform s;
    initIdentityMatrix4x4(&s);
    s.x = arg1;
    s.y = arg2;
    s.z = arg3;
    func_8001B090(&s, arg0);
}

/* Initialize arg0 as an identity matrix translated to (arg1,arg2,arg3). */
void func_8001C0F0(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    Xform *s = arg0;
    initIdentityMatrix4x4(arg0);
    s->x = arg1;
    s->y = arg2;
    s->z = arg3;
}

/* Store arg1/arg2 into the two s32 fields of table entry arg0, with interrupts off. */
void func_8001CBF0(s32 arg0, s32 arg1, s32 arg2) {
    s32 h;
    Tbl *e;
    h = nw2DisableInterrupts();
    e = &D_8007DF30[arg0];
    e->f0 = arg1;
    e->f4 = arg2;
    nw2RestoreInterrupts(h);
}
