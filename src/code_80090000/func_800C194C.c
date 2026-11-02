/* @header
 * func_800C194C
 * VRAM 0x800C194C | ROM 0x6E0BC | size 0x1D8
 * asm: asm/nonmatchings/code_80090000/func_800C194C.s
 */
#include "common.h"

typedef struct { u8 pad[0xC]; u32 f[4]; } A;
typedef struct { u32 a; u8 pad[0x10]; s16 b; s16 c; u8 pad2[4]; } C;
typedef struct { u8 pad[0x18]; u16 s; u16 m; u8 pad2[4]; } T;
extern s32 D_80038A98, D_800DF30C, D_800DF308, D_800DF310, D_800E74D8, D_800DF3A8, D_800E79C4;
extern s32 D_800DF318, D_800E81F8, D_800E81E4, D_800DF314;
extern s8 *D_800DF31C;
extern A D_800D4ED8[];
extern C D_800DF330[];
extern T D_800D4930[];
void func_800C15A0(s32);
void func_800C0BDC(void);
void func_8000E55C(s32, s32, s32);
s32 func_800B600C(s32, s32);
void func_800C0680(s32);
void func_80099478(s32, s32, s32);

void func_800C194C(s32 a) {
    T *t;
    C *c;
    s16 *q;
    u32 *p;
    u32 m;
    s32 k;
    s32 i, n, v;
    u32 f;

    if (D_80038A98 != 0) {
        return;
    }
    if (D_800DF30C != D_800DF308) {
        D_800DF310 = D_800DF308;
        D_800DF30C = D_800DF308;
        func_800C15A0(D_800DF308);
    }
    n = D_800DF310;
    if (n != D_800DF308) {
        i = 0;
        c = D_800DF330;
        m = 0x80000000;
        k = -1;
        q = &c->c;
        p = (u32 *)&D_800D4ED8[n];
        for (; i < 4; i++, q += 14, c++) {
            f = p[3];
            p++;
            c->a = f;
            if (f & m) {
                q[-1] = k;
                q[0] = 0;
            }
        }
    }
    D_800E74D8 = -6;
    if (a != 0) {
        return;
    }
    func_800C0BDC();
    if (D_800DF3A8) {
        func_8000E55C(0xA, 1, 0x50);
    } else {
        func_8000E55C(0, 1, 0x50);
    }
    t = &D_800D4930[D_800E79C4];
    v = D_800DF318;
    if (t->s != 0) {
        D_800E81F8 = func_800B600C(t->s, 0);
    } else {
        D_800E81F8 = 0;
    }
    v = v > 0 ? v : 0;
    if (v >= t->m) {
        v = t->m;
    }
    func_800C0680(v);
    D_800DF318 = v;
    D_800E81E4 = D_800E79C4;
    func_80099478(D_800DF31C[0], 0x20, 0xA);
    func_80099478(D_800DF31C[1], 0x36, 0xA);
    func_80099478(D_800DF314 - 1, 0x20, 0x19);
}
