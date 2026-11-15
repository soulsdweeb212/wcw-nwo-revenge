/* @header
 * func_800C1370
 * VRAM 0x800C1370 | ROM 0x6DAE0 | size 0x230
 * asm: asm/nonmatchings/code_80090000/func_800C1370.s
 */
#include "common.h"

typedef struct { u16 id; u8 p0[6]; s16 x; s16 y; s16 z; s16 w; u16 fl; } E;
#ifdef TARGET_PC
/* PC: the wrestlers' records D_800DF330 have their PC layout (common.h's Nw2MenuSceneCast): e, the cast word, is an
 * IdOrAddr there (keys), w is r and h is idx. */
typedef Nw2MenuSceneCast C;
#else
typedef struct { E *e; f32 x; f32 y; f32 z; s32 w; s16 h; u8 p[6]; } C;
#endif
typedef struct {
    u8 p0[0x680];
    f32 x;     /* 680 */
    f32 y;     /* 684 */
    f32 z;     /* 688 */
    s32 w;     /* 68C */
    u8 p1[4];
    s16 id;    /* 694 */
    u8 p2[4];
    u16 k;     /* 69A */
    u8 p3[0x14];
    s16 t;     /* 6B0 */
    u8 p4[2];
    s16 u;     /* 6B4 */
    u8 p5[6];
    s16 v;     /* 6BC */
    u8 p6[6];
    s32 st;    /* 6C4 */
    u8 p7[8];
} R;
extern R *D_800E79B8;
extern C D_800DF330[];
#ifdef TARGET_PC
/* PC: the current scene, in its PC layout (common.h's Nw2MenuScene), whose cast words start at +0x10. */
extern Nw2MenuScene *D_800DF31C;
#else
extern u8 *D_800DF31C;
#endif
extern s32 D_800E9F70;
void func_800BF2F0(R *, C *);
void func_80012B38(s32, s32, s32);
void func_80012364(s32, s32, s32, s32);

#ifdef TARGET_PC
/* PC: the N64's function, with the records read by field name. Each of the scene's cast words is an IdOrAddr: 0, the
 * wrestler's character as a number, or the address of the wrestler's keys (E is the first key), which
 * ID_OR_ADDR_IS_ADDR tells apart (the N64's sign test). e stands for the N64's c->e. */
void func_800C1370(void) {
    R *p = D_800E79B8;
    s32 i = 0;
    C *c = D_800DF330;
    IdOrAddr v;
    E *e;
    s32 b, m;

    for (; i < 4; i++, p++, c++) {
        v = D_800DF31C->cast[i];
        c->keys = v;
        if (v == 0) {
            p->st = 0x80;
        } else if (!ID_OR_ADDR_IS_ADDR(v)) {
            p->id = v & 0xFFF;
            p->k = 8;
            p->v = -5;
            p->t = -5;
            p->u = 0;
            p->st = 0x80;
        } else {
            e = (E *)v;
            p->k = (e->fl & 0x70) | 8;
            c->x = e->x;
            c->y = e->y;
            c->z = e->z;
            c->r = e->w;
            if (D_800E9F70 < 0) {
                p->st = 4;
            } else {
                p->st = 0;
            }
            if (c->idx >= 0) {
                func_800BF2F0(p, c);
            }
            p->x = c->x;
            p->y = c->y;
            p->z = c->z;
            p->w = c->r;
            if (p->id != e->id) {
                p->id = e->id;
                p->st |= 0x80;
            } else {
                m = -1;
                b = -1;
                switch (p->k & 0xF0) {
                case 0x10:
                    m = 4;
                    break;
                case 0x30:
                    b = 2;
                    break;
                case 0x40:
                    b = 10;
                    break;
                }
                func_80012B38((s16)i, m, 2);
                func_80012364((s16)i, (s16)i, b, 0);
            }
        }
    }
}
#else
void func_800C1370(void) {
    R *p = D_800E79B8;
    s32 i = 0;
    C *c = D_800DF330;
    s32 v, b, m;

    for (; i < 4; i++, p++, c++) {
        v = *(s32 *)(D_800DF31C + i * 4 + 0xC);
        c->e = (E *)v;
        if (v == 0) {
            p->st = 0x80;
        } else if (v >= 0) {
            p->id = v & 0xFFF;
            p->k = 8;
            p->v = -5;
            p->t = -5;
            p->u = 0;
            p->st = 0x80;
        } else {
            p->k = (((E *)v)->fl & 0x70) | 8;
            c->x = c->e->x;
            c->y = c->e->y;
            c->z = c->e->z;
            c->w = c->e->w;
            if (D_800E9F70 < 0) {
                p->st = 4;
            } else {
                p->st = 0;
            }
            if (c->h >= 0) {
                func_800BF2F0(p, c);
            }
            p->x = c->x;
            p->y = c->y;
            p->z = c->z;
            p->w = c->w;
            if (p->id != c->e->id) {
                p->id = c->e->id;
                p->st |= 0x80;
            } else {
                m = -1;
                b = -1;
                switch (p->k & 0xF0) {
                case 0x10:
                    m = 4;
                    break;
                case 0x30:
                    b = 2;
                    break;
                case 0x40:
                    b = 10;
                    break;
                }
                func_80012B38((s16)i, m, 2);
                func_80012364((s16)i, (s16)i, b, 0);
            }
        }
    }
}
#endif
