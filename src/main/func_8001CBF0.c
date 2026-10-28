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
