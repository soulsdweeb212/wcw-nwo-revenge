/* @header
 * osSetEventMesg  (originally func_8001CBF0)
 * VRAM 0x8001CBF0 | ROM 0x1D7F0 | size 0x5C
 * asm: asm/nonmatchings/main/osSetEventMesg.s
 */
/* SDK: libultra 2.0I, ultralib src/os/seteventmesg.c (same code as the SDK source). */
#include "common.h"

extern u32 xseed;

typedef struct {
    f32 m[12];
    f32 x, y, z;
} Xform;

void guMtxF2L(void *, void *);
s32 __osDisableInt(void);
void __osRestoreInt(s32);

typedef struct {
    s32 f0;
    s32 f4;
} Tbl;

extern Tbl __osEventStateTab[];

/* Store arg1/arg2 into the two s32 fields of table entry arg0, with interrupts off. */
void osSetEventMesg(s32 arg0, s32 arg1, s32 arg2) {
    s32 h;
    Tbl *e;
    h = __osDisableInt();
    e = &__osEventStateTab[arg0];
    e->f0 = arg1;
    e->f4 = arg2;
    __osRestoreInt(h);
}
