/* @header
 * func_800C12D0
 * VRAM 0x800C12D0 | ROM 0x6DA40 | size 0xA0
 * asm: asm/nonmatchings/code_80090000/func_800C12D0.s
 */
#include "common.h"

typedef struct { u8 p[0x18]; u16 a; u16 m; u8 q[4]; } T;
extern T D_800D4930[];
extern s32 D_800E79C4, D_800E81F8, D_800E81E4;
s32 func_800B600C(s32, s32);
void func_800C0680(s32);

s32 func_800C12D0(s32 a) {
    T *t = &D_800D4930[D_800E79C4];
    if (t->a) {
        D_800E81F8 = func_800B600C(t->a, 0);
    } else {
        D_800E81F8 = 0;
    }
    if (a < 0) {
        a = 0;
    }
    if (a >= t->m) {
        a = t->m;
    }
    func_800C0680(a);
    D_800E81E4 = D_800E79C4;
    return a;
}
