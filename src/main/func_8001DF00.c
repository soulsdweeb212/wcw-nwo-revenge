/* @header
 * func_8001DF00
 * VRAM 0x8001DF00 | ROM 0x1EB00 | size 0x1AC
 * asm: asm/nonmatchings/main/func_8001DF00.s
 */
#include "common.h"

/* Nw2 render-object setup for a display object's sub-state (4 or 5): installs
 * the draw handler, aligns the frame count to 9, sizes the geometry, and
 * copies the optional colour/offset block into the object. */
typedef struct Nw2DataDF00 {
    s32 f0;
    s32 f4;
    s32 f8;
} Nw2DataDF00;

typedef struct Nw2DescDF00 {
    s32 f0;
    s32 f4;
    u8 f8;
    u8 pad9[3];
    Nw2DataDF00 *fC;
    Nw2DataDF00 *f10;
} Nw2DescDF00;

typedef struct Nw2ObjDF00 {
    u8 pad0[4];
    s32 f4;
    u8 pad8[0x10];
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    Nw2DescDF00 *f28;
    s32 f2C;
    u8 pad30[8];
    s32 f38;
    s32 f3C;
    s32 f40;
    s32 f44;
} Nw2ObjDF00;

void func_80020300(void *, s32, s32, void *);
void func_8001D720(void);
void func_8001DB64(void);

void func_8001DF00(Nw2ObjDF00 *o, s32 arg1, Nw2DescDF00 *arg2) {
    Nw2DataDF00 *p;
    s32 n;

    switch (arg1) {
    case 5:
        o->f28 = arg2;
        o->f44 = arg2->f0;
        o->f38 = 0;
        switch (o->f28->f8) {
        case 0:
            o->f4 = (s32)func_8001D720;
            o->f28->f4 = (o->f28->f4 / 9) * 9;
            p = o->f28->f10;
            n = p->f4 * 2;
            o->f2C = p->f0 * n * 8;
            if (o->f28->fC != NULL) {
                o->f1C = o->f28->fC->f0;
                o->f20 = o->f28->fC->f4;
                o->f24 = o->f28->fC->f8;
                func_80020300((u8 *)o->f28->fC + 0xC, o->f18, 0x20, o);
            } else {
                o->f24 = 0;
                o->f20 = 0;
                o->f1C = 0;
            }
            break;
        case 1:
            o->f4 = (s32)func_8001DB64;
            if (o->f28->fC != NULL) {
                o->f1C = o->f28->fC->f0;
                o->f20 = o->f28->fC->f4;
                o->f24 = o->f28->fC->f8;
            } else {
                o->f24 = 0;
                o->f20 = 0;
                o->f1C = 0;
            }
            break;
        }
        break;
    case 4:
        o->f3C = 0;
        o->f40 = 1;
        o->f38 = 0;
        if (o->f28 == NULL) break;
        o->f44 = o->f28->f0;
        if (o->f28->f8 == 0) {
            if (o->f28->fC != NULL) {
                o->f24 = o->f28->fC->f8;
            }
        } else if (o->f28->f8 == 1) {
            if (o->f28->fC != NULL) {
                o->f24 = o->f28->fC->f8;
            }
        }
        break;
    }
}
