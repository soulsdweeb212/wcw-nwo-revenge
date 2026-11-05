/* @header
 * func_80095CB0
 * VRAM 0x80095CB0 | ROM 0x89150 | size 0x368
 * asm: asm/nonmatchings/ovl2_80090000/func_80095CB0.s
 */
#include "common.h"

typedef struct {
    s32 flags;
} Node;

typedef struct {
    u8 pad0[0x14];
    Node *node;
    u8 pad18[0xC4];
} ObjDC;

typedef struct {
    u8 data[8];
} Tex8;

extern u8 D_8007EF30[];
extern u16 D_800E2B10[];
extern s16 D_800E2B78[];
extern s8 *D_800E2B84[];
extern s8 *D_800E2BB4[];
extern s8 *D_800E2BD4[];
extern s16 D_800E2D8C;
extern s8 D_800E77B8[];
extern ObjDC D_800E7950[];
extern Tex8 D_800E7DA0[];
extern s16 D_800E9448;
extern s16 D_800E944A;
extern s16 D_800F99B6;
s8 func_800D633C(void);
void func_80091CB4(void);
void func_80006814(void *, void *, f32, f32);

void func_80095CB0(s16 sec, s16 min) {
    s8 d[5];
    u32 i;
    s32 k;
    s8 v;

    if (D_800F99B6 != 0 || func_800D633C()) {
        return;
    }
    k = D_8007EF30[0x1A0];
    v = D_800E2B84[k][D_800E2D8C];
    if (v >= 0 && D_800E2BB4[k][D_800E2D8C] == min && D_800E2BD4[k][D_800E2D8C] == sec) {
        D_800E9448 = v;
        D_800E944A = 0;
        if (D_800E2B78[D_800E2B84[k][D_800E2D8C]] < 0) {
            D_800E9448 = -1;
        }
        D_800E2D8C++;
    }
    if (min > 60) {
        min = 60;
        sec = 0;
    }
    if (D_800E7950[0].node->flags & 0x80) {
        for (i = 0; i < 5; i++) {
            D_800E77B8[i] = -1;
            D_800E7950[i].node->flags &= ~0x80;
        }
        if (min == 0 && sec == 0) {
            func_80091CB4();
        }
    }
    d[0] = (min % 100) / 10;
    d[1] = min % 10;
    d[2] = 10;
    d[3] = (sec % 100) / 10;
    d[4] = sec % 10;
    for (i = 0; i < 5; i++) {
        s8 c = d[i];

        if (D_800E77B8[i] != c) {
            D_800E77B8[i] = c;
            func_80006814(&D_800E7950[i], &D_800E7DA0[c], D_800E2B10[i], 208.0f);
        }
    }
}
