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

/* Initialize arg0 as an identity matrix translated to (arg1,arg2,arg3). */
void func_8001C0F0(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    Xform *s = arg0;
    initIdentityMatrix4x4(arg0);
    s->x = arg1;
    s->y = arg2;
    s->z = arg3;
}
