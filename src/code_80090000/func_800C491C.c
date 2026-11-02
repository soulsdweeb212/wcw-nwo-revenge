/* @header
 * func_800C491C
 * VRAM 0x800C491C | ROM 0x7108C | size 0x234
 * asm: asm/nonmatchings/code_80090000/func_800C491C.s
 */
#include "common.h"

typedef struct { s16 a; s16 b; u16 c; s16 d; } T;
typedef struct {
    u8 p0[0x680];
    f32 x;     /* 680 */
    s32 y;     /* 684 */
    f32 z;     /* 688 */
    s32 w;     /* 68C */
    u8 p1[2];
    s16 h;     /* 692 */
    s16 id;    /* 694 */
    u16 fl;    /* 696 */
    u8 p2[2];
    s16 k;     /* 69A */
    u8 p3[0x14];
    s16 t;     /* 6B0 */
    u8 p4[2];
    s16 u;     /* 6B4 */
    u8 p5[4];
    s16 c;     /* 6BA */
    u8 p6[8];
    s32 st;    /* 6C4 */
    u8 p7[8];
} R;
extern R *D_800E79B8;
extern s32 D_800E7C98[], D_800E6B68[], D_800EA308[];
extern T D_800D5E20[];
void func_800C33F4(s32);
void func_80012B38(s32, s32, s32);

void func_800C491C(s32 i) {
    R *p = &D_800E79B8[i];
    s32 v, a;
    s32 *n;

    for (; i < 4; i++, p++) {
        v = D_800E7C98[i];
        if (v >= 0) {
            p->id = v;
            p->k = D_800E6B68[i];
            p->t = -5;
            n = &D_800EA308[i];
            p->x = D_800D5E20[*n].a;
            p->z = D_800D5E20[*n].b;
            p->w = D_800D5E20[*n].c;
            if (p->x > -300.0f && p->x < 300.0f && p->z > -300.0f && p->z < 300.0f) {
                *(f32 *)&p->y = 90.0f;
            } else {
                p->y = 0;
            }
            func_800C33F4(i);
            if (p->h >= 0) {
                if (p->c == 0) {
                    if (p->st == 0x80) {
                        a = p->fl;
                        p->u = 0;
                        if (a & 4) {
                            func_80012B38((s16)i, (a & 0x70) >> 4, 2);
                        } else {
                            func_80012B38((s16)i, -1, 2);
                        }
                    }
                    p->st = 4;
                }
            } else {
                p->st = 0x80;
            }
        } else {
            p->st = 0x80;
        }
    }
}
