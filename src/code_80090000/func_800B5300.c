/* @header
 * func_800B5300
 * VRAM 0x800B5300 | ROM 0x61A70 | size 0x404
 * asm: asm/nonmatchings/code_80090000/func_800B5300.s
 */
#include "common.h"

typedef struct { u8 pad0[4]; u16 f4; } Info;
typedef struct {
    f32 x, y;
    s16 f8;
    u16 flags;
    u8 padC[3];
    u8 fF;
    u8 pad10[6];
    u8 f16;
    u8 pad17[5];
    f32 f1C;
    u16 f20;
    s16 f22;
    Info *f24;
    u8 pad28[0x148 - 0x28];
} El;
typedef struct { void *items; s16 cur; u8 pad6[0xE]; El *el; u8 pad18[0x138 - 0x18]; } Menu;

extern Menu D_800E8230[];
extern struct { u8 pad0[8]; u16 mode; } D_8007EF30;
extern f64 D_800D6710;

void func_800B5300(s32 id) {
    El *d = NULL;
    El *s = NULL;
    s32 kind = 0;
    u16 t;

    switch (id) {
    case 0x401:
    case 0x402:
    case 0x404:
    case 0x408:
    case 0x409:
        d = &D_800E8230[20].el[1];
        s = &D_800E8230[1].el[D_800E8230[1].cur];
        break;
    case 0x40D:
        d = &D_800E8230[20].el[2];
        s = &D_800E8230[4].el[D_800E8230[4].cur];
        break;
    case 0x40A:
        d = &D_800E8230[20].el[2];
        s = &D_800E8230[5].el[D_800E8230[5].cur];
        break;
    case 0x411:
        d = &D_800E8230[20].el[2];
        s = &D_800E8230[6].el[D_800E8230[6].cur];
        break;
    case 0x40B:
        kind = 1;
        d = &D_800E8230[20].el[3];
        s = &D_800E8230[3].el[D_800E8230[3].cur];
        d->f20 = 0x120F;
        break;
    case 0x41E:
        d = &D_800E8230[20].el[4];
        s = &D_800E8230[9].el[14];
        break;
    case 0x41F:
        kind = 2;
        d = &D_800E8230[20].el[4];
        s = &D_800E8230[9].el[15];
        break;
    case 0x422:
        d = &D_800E8230[20].el[4];
        s = &D_800E8230[19].el[1];
        break;
    case 0x423:
        d = &D_800E8230[20].el[4];
        s = &D_800E8230[19].el[3];
        break;
    case 0x436:
    case 0x437:
    case 0x438:
    case 0x439:
        d = &D_800E8230[20].el[id - 0x431];
        kind = 3;
        d->y = 72.0f;
        d->f8 = -90 - (id - 0x436) * 4;
        d->f22 = 0;
        d->f1C = 0.5f;
        break;
    case 0x13:
        D_800E8230[20].el[2].flags &= ~1;
        if (D_8007EF30.mode & 0x8000) {
            D_800E8230[20].el[1].f20 = 1;
        } else if (D_8007EF30.mode & 0xC0) {
            D_800E8230[20].el[1].f20 = 2;
        } else {
            D_800E8230[20].el[1].f20 = 0;
        }
        D_800E8230[20].el[1].f16 = 0;
        D_800E8230[20].el[3].flags &= ~0x20;
        return;
    }
    if (d != NULL) {
        if (kind != 3) {
            if (kind == 1) {
                t = s->f20;
                if (t >= 0x15 && t < 0x18) {
                    d->f22 = 0;
                } else if (t >= 0x18 && t < 0x1E) {
                    d->f22 = 0x10;
                } else {
                    d->f22 = 0x20;
                }
            } else {
                d->f20 = s->f20;
            }
            d->x = s->x;
            d->y = s->y;
            s->flags |= 1;
            d->f8 = -90;
            d->f1C = s->f24->f4 * D_800D6710;
        }
        d->fF = 2;
        d->f16 = 0xFF;
        d->flags = (d->flags | 8) & ~0x20;
    }
}
