/* @header
 * func_800B16F0
 * VRAM 0x800B16F0 | ROM 0x5DE60 | size 0x2B0
 * asm: asm/nonmatchings/code_80090000/func_800B16F0.s
 */
#include "common.h"

typedef struct { s32 k; s32 v; } St;
typedef struct { St s[25]; u8 pad[0x2B8 - 25 * 8]; } P;
typedef struct { u8 b[0x18]; } In;
extern struct { u8 pad[0x1B0]; P pl[4]; } D_8007EF30;
extern struct { u8 pad[0x628]; In in[4]; } D_8007E228;
extern s32 D_800EA220[][11];
s32 func_800AA100(s32);
#define PL D_8007EF30.pl
#define IN D_8007E228.in

void func_800B16F0(void) {
    s32 i, j;
    P *p;
    In *q;
    for (i = 0; i < 4; i++) {
        for (j = 0x18; j >= 0; j--) {
            PL[i].s[j].v = 0;
        }
    }
    p = PL;
    q = IN;
    for (i = 0; i < 4; i++) {
        p[i].s[0].v = q[i].b[4];
        p[i].s[1].v = q[i].b[5];
        p[i].s[2].v = q[i].b[6];
        p[i].s[3].v = q[i].b[7];
        p[i].s[4].v = q[i].b[8];
        p[i].s[5].v = q[i].b[9];
        p[i].s[6].v = q[i].b[10];
        p[i].s[7].v = q[i].b[11];
        p[i].s[8].v = q[i].b[22];
        p[i].s[9].v = q[i].b[23];
        p[i].s[10].v = q[i].b[2];
        p[i].s[11].v = q[i].b[3];
        p[i].s[12].v = q[i].b[12];
        p[i].s[13].v = q[i].b[13];
        p[i].s[14].v = q[i].b[14];
        p[i].s[15].v = q[i].b[15];
        p[i].s[16].v = q[i].b[16];
        p[i].s[17].v = q[i].b[17];
        p[i].s[18].v = q[i].b[18];
        p[i].s[19].v = q[i].b[19];
        p[i].s[20].v = q[i].b[20];
        p[i].s[21].v = q[i].b[21];
    }
    for (i = 0; i < 4; i++) {
        p = &PL[i];
        p->s[22].v = p->s[12].v * 2000 + p->s[13].v * 1000 + p->s[14].v * 500 + p->s[15].v * 100;
        p->s[23].v = p->s[9].v * 100;
        if (func_800AA100(i) == 1) {
            p->s[24].v = 3000;
        }
        if (IN[i].b[0] && IN[i].b[1]) {
            D_800EA220[i][0] = D_800EA220[i][1] = D_800EA220[i][2] = D_800EA220[i][3] = D_800EA220[i][4] = D_800EA220[i][5] = D_800EA220[i][6] = D_800EA220[i][7] = D_800EA220[i][8] = D_800EA220[i][9] = 0x01000000;
        }
        D_800EA220[i][i] = -1;
    }
}
