/* @header
 * func_800B2588
 * VRAM 0x800B2588 | ROM 0x5ECF8 | size 0x42C
 * asm: asm/nonmatchings/code_80090000/func_800B2588.s
 */
#include "common.h"

typedef struct { u8 pad0[0xA]; u16 flags; u8 padC[0x14]; u16 f20; u16 f22; u8 pad24[0x148 - 0x24]; } El;
typedef struct { s32 w[11]; } Ent;
typedef struct { u8 on; u8 pad1[0x17]; } Slot;
typedef struct { u8 pad0[0x628]; Slot slot[4]; } Cfg;

extern El *D_800E948C;
extern Ent D_800EA220[];
extern struct { u8 pad0[8]; u16 mode; } D_8007EF30;
extern u16 D_800CD83C[][8];
extern s32 D_8007E8C0[];
extern Cfg D_8007E228;
extern s16 D_800E947C;
void func_800B19A0(void);

void func_800B2588(void) {
    El *e = D_800E948C;
    u16 *t;
    s32 i, j, k, b;
    u16 m;

    for (i = 0; i < 4; i++) {
        for (k = 10; k >= 0; k--) {
            D_800EA220[i].w[k] = 0;
        }
    }
    func_800B19A0();
    e[10].f22 = 0;
    e[19].flags |= 1;
    e[20].flags |= 1;
    m = D_8007EF30.mode;
    if (m & 0x800) {
        if (m & 0x20) {
            t = D_800CD83C[5];
        } else {
            t = D_800CD83C[4];
        }
    } else {
        switch (m & 0xF0) {
        case 0x20:
            t = D_800CD83C[0];
            break;
        case 0x40:
            t = D_800CD83C[1];
            break;
        case 0x80:
            t = D_800CD83C[2];
            break;
        default:
            t = D_800CD83C[3];
            break;
        }
    }
    for (j = 10; j < 0x12; j++, t++) {
        e[j].f20 = *t;
    }
    e = D_800E948C;
    m = D_8007EF30.mode;
    if (m & 0x800) {
        if (!(m & 0x20)) {
            goto skip;
        }
        if (D_8007E8C0[1] == 1) {
            e[16].f20 |= 4;
        }
    } else {
        switch (m & 0xF0) {
        case 0x40:
            if (D_8007E8C0[0] == 0) {
                e[10].f20 |= 4;
            }
            if (D_8007E8C0[1] == 0 || D_8007E8C0[1] == D_8007E8C0[0]) {
                e[12].f20 |= 4;
            }
            if (D_8007E8C0[2] == 0) {
                e[16].f20 |= 4;
            }
            break;
        case 0x20:
            if (D_8007E8C0[0] == 0) {
                e[10].f20 |= 4;
            }
            if (D_8007E8C0[1] == 0 || D_8007E8C0[1] == D_8007E8C0[0]) {
                e[12].f20 |= 4;
            }
            if (D_8007E8C0[2] == 0) {
                e[14].f20 |= 4;
            }
            if (D_8007E8C0[3] == 0 || D_8007E8C0[3] == D_8007E8C0[2]) {
                e[16].f20 |= 4;
            }
            break;
        case 0x80:
            if (!D_8007E228.slot[0].on) {
                e[10].f20 |= 4;
            } else {
                D_8007E8C0[0] = 1;
            }
            if (!D_8007E228.slot[1].on) {
                e[12].f20 |= 4;
            } else {
                D_8007E8C0[1] = 2;
            }
            if (!D_8007E228.slot[2].on) {
                e[14].f20 |= 4;
            } else {
                D_8007E8C0[2] = 3;
            }
            if (!D_8007E228.slot[3].on) {
                e[16].f20 |= 4;
            } else {
                D_8007E8C0[3] = 4;
            }
            break;
        default:
            if (D_8007E8C0[0] == 0) {
                e[12].f20 |= 4;
            }
            if (D_8007E8C0[1] == 0) {
                e[16].f20 |= 4;
            }
            break;
        }
    }
    m = D_8007EF30.mode;
skip:
    if (m & 0x800) {
        b = (m & 0x20) ? 0x30 : 0x10;
        for (j = 0; j < 9; j++, b++) {
            e[j].f20 = 0x7400 + b;
        }
        e[9].flags |= 1;
    } else if (m & 0x80) {
        b = 0x40;
        for (j = 0; j < 10; j++, b++) {
            e[j].f20 = 0x7400 + b;
        }
        e[9].flags &= ~1;
    } else {
        b = 0;
        for (j = 0; j < 10; j++, b++) {
            e[j].f20 = 0x7400 + b;
        }
        e[9].flags &= ~1;
    }
    D_800E947C = 0x12;
}
