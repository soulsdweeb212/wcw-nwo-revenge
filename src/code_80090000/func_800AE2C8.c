/* @header
 * func_800AE2C8
 * VRAM 0x800AE2C8 | ROM 0x5AA38 | size 0x2FC
 * asm: asm/nonmatchings/code_80090000/func_800AE2C8.s
 */
#include "common.h"

typedef struct { u8 pad0[0xA]; u16 flags; u8 fC; u8 fD; s8 fE; u8 padF; s16 f10; u8 pad12[0x148 - 0x12]; } El;
typedef struct { void *items; s16 cur; u8 pad6[0xE]; El *el; u8 pad18[0x138 - 0x18]; } Menu;
typedef struct {
    u8 pad0[8];
    u16 mode;
    u8 padA[0x26];
    u8 *p30;
    u8 pad34[0x16C];
    u8 b[11];
} Game;

extern Game D_8007EF30;
extern Menu D_800E8230[];
extern El *D_800E8FAC; /* D_800E8230[11].el, by its own name in the inlined func_800AE1E4 */
void func_800A8EF0(s32);
s16 func_800A06F8(El *, s8);

/* func_800AE1E4, inlined (it is a separate function too) */
static inline void setup(void) {
    u16 f = D_8007EF30.mode;
    El *p = D_800E8FAC;
    s32 a;

    if (f & 0x8000) {
        a = *D_8007EF30.p30;
        a += 2;
    } else if (f & 0x80) {
        a = 8;
    } else {
        a = 7;
    }
    func_800A8EF0(a);
    p[0].fE = D_8007EF30.b[0];
    p[4].fE = D_8007EF30.b[2];
    p[2].fE = D_8007EF30.b[1];
    p[6].fE = D_8007EF30.b[3];
    p[8].fE = D_8007EF30.b[4];
    p[10].fE = D_8007EF30.b[5];
    p[12].fE = D_8007EF30.b[6];
    p[14].fE = D_8007EF30.b[7];
    p[16].fE = D_8007EF30.b[8];
    p[18].fE = D_8007EF30.b[9];
    p[20].fE = D_8007EF30.b[10];
}

void func_800AE2C8(void) {
    El *e = D_800E8230[11].el;
    s32 i;

    setup();
    if (D_8007EF30.mode & 0x60) {
        e[16].flags |= 1;
        e[17].flags |= 1;
        e[18].flags &= ~1;
        e[19].flags &= ~1;
        e[20].flags &= ~1;
        e[21].flags &= ~1;
    } else {
        e[16].flags &= ~1;
        e[17].flags &= ~1;
        e[18].flags |= 1;
        e[19].flags |= 1;
        e[20].flags |= 1;
        e[21].flags |= 1;
    }
    if (D_8007EF30.mode & 0x8000) {
        e[22].flags |= 1;
        D_800E8230[11].cur = 0x17;
    } else {
        e[22].flags &= ~1;
        D_800E8230[11].cur = 0x16;
    }
    if (D_8007EF30.mode & 0x80) {
        e[2].flags = 0x3400;
        e[0].flags |= 0x40;
        e[1].flags |= 0x40;
        e[16].flags |= 1;
        e[17].flags |= 1;
        if (e[2].fE == 4) {
            e[14].fE = 1;
        }
        if (e[14].fE == 0) {
            e[2].fE = 3;
        }
    } else {
        e[2].flags = 0x300;
        e[0].flags &= ~0x40;
        e[1].flags &= ~0x40;
    }
    if (e[6].fE == 1) {
        e[12].fE = 1;
    }
    if (e[2].fE == 2) {
        e[14].fE = 1;
    }
    if (e[18].fE == 1) {
        e[20].flags |= 0x40;
        e[21].flags |= 0x40;
    } else {
        e[20].flags &= ~0x40;
        e[21].flags &= ~0x40;
    }
    e = D_800E8230[11].el;
    for (i = 0; i < 22; i += 2, e += 2) {
        e->fC = e->fD = e->fE;
        e->f10 = func_800A06F8(e, e->fE);
    }
}
