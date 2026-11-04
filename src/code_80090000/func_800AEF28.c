/* @header
 * func_800AEF28
 * VRAM 0x800AEF28 | ROM 0x5B698 | size 0x2F0
 * asm: asm/nonmatchings/code_80090000/func_800AEF28.s
 */
#include "common.h"

typedef struct { f32 x; f32 y; u8 pad8[2]; u16 flags; u8 padC[0x148 - 0xC]; } El;
typedef struct { void *items; s16 cur; u8 pad6[0xE]; El *el; u8 pad18[0x138 - 0x18]; } Menu;
typedef struct { s16 x, y, z; } Pt;
typedef struct { u8 b[8]; } Ent;

extern Menu D_800E8230[];
extern struct { u8 pad0[8]; u16 mode; u8 padA[2]; s16 fC; } D_8007EF30;
extern struct { u8 pad0[0x60]; Ent e[4]; } D_8007E228;
void func_800AEA7C(void);
void func_800A90DC(Ent *);
s32 func_800A9E40(void);
Pt *func_800A9010(void);

void func_800AEF28(s32 a) {
    Menu *m = &D_800E8230[12];
    El *e;
    El *p;
    Pt *q;
    s32 i;

    if (a) {
        func_800AEA7C();
    } else {
        Ent *t = D_8007E228.e;
        func_800A90DC(&t[0]);
        func_800A90DC(&t[1]);
        func_800A90DC(&t[2]);
        func_800A90DC(&t[3]);
    }
    switch (D_8007EF30.mode & 0xF) {
    case 1:
    case 3:
    case 6:
        if (func_800A9E40()) {
            break;
        }
        switch (D_8007EF30.mode & 0xF0) {
        case 0x10:
            D_8007EF30.fC = 2;
            break;
        case 0x40:
            D_8007EF30.fC = 3;
            break;
        case 0x20:
            D_8007EF30.fC = 4;
            break;
        case 0x80:
            D_8007EF30.fC = 4;
            break;
        default:
            D_8007EF30.fC = 1;
            break;
        }
        e = &m->el[3];
        D_800E8230[12].cur = 0;
        for (i = 3; i < 15; i++, e++) {
            e->flags |= 1;
        }
        return;
    default:
        D_800E8230[12].cur = 2;
        break;
    }
    q = func_800A9010();
    p = &m->el[3];
    for (i = 0; i < 4; i++, p += 3, q++) {
        if (q->x == 0 && q->y == 0) {
            p[0].flags |= 1;
            p[1].flags |= 1;
            p[2].flags |= 1;
        } else {
            p[0].flags &= ~1;
            p[1].flags |= 1;
            p[2].flags |= 1;
            p[0].x = q->x;
            p[0].y = a ? q->y : q->y + 7;
            p[1].x = q->x < 0 ? q->x + 59.5 : q->x - 59.5;
            p[1].y = q->y;
            p[1].flags |= 0x20;
            p[2].x = q->x;
            p[2].y = q->y + 14;
            p[2].flags |= 0x20;
        }
    }
    D_800E8230[12].cur = 5;
    m->el[2].flags &= ~1;
}
