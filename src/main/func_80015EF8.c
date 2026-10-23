#include "common.h"

typedef struct {
    u8 pad0[0x58];
    s32 f58;
    s32 f5C;
    u8 pad60[0x50];
    s32 fB0;
    s32 fB4;
    u8 padB8[0x25];
    u8 fDD;
    u8 padDE[0x1B];
    u8 fF9;
    u8 fFA;
} Nw15468Obj;

/* Reset the voice's envelope state from its +0x58/+0x5C/+0xDD fields. */
void func_80015468(Nw15468Obj *p) {
    s32 a = p->f58;
    s32 b = p->f5C;
    u8 c = p->fDD;

    p->fF9 = 0;
    p->fB0 = a;
    p->fB4 = b;
    p->fFA = c & 0x40;
}

typedef struct {
    u8 pad0[0x50];
    u64 f50;
    u64 f58;
    u8 pad60[0x10];
    u64 f70;
    u8 pad78[0x42];
    u16 fBA;
    u8 padBC[0x16];
    u16 fD2;
    u16 fD4;
    u8 padD6[9];
    u8 fDF;
    u8 fE0;
    u8 padE1[2];
    u8 fE3;
    u8 fE4;
    u8 fE5;
} Nw15068Obj;

/* Recompute the voice's +0x70 target from its key/velocity fields. */
void func_80015068(Nw15068Obj *p) {
    if (p->fBA != 0x7FFF) {
        if (p->fD2 != 0) {
            p->f70 = p->f58 + ((u32)p->fD2 << 8);
        } else {
            p->f70 = p->f50 - ((u32)p->fD4 << 8);
        }
    } else {
        p->f70 = 0x7FFFFFFF;
    }
    p->fE3 = 1;
    p->fE4 = p->fE0;
    p->fE5 = p->fDF;
}

/* Fill arg2 bytes at arg0 with arg1. */
void func_80015ECC(u8 *arg0, u8 arg1, s32 arg2) {
    s32 i;

    for (i = arg2 - 1; i != -1; i--) {
        *arg0 = arg1;
        arg0++;
    }
}

/* Copy arg2 bytes from arg0 to arg1. */
void func_80015EF8(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 i;

    for (i = arg2 - 1; i != -1; i--) {
        *arg1 = *arg0;
        arg0++;
        arg1++;
    }
}
