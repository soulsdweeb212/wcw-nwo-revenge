/* @header
 * func_800C4B50
 * VRAM 0x800C4B50 | ROM 0x712C0 | size 0x128
 * asm: asm/nonmatchings/code_80090000/func_800C4B50.s
 */
#include "common.h"

typedef struct { u8 pad[0x692]; s16 a; u8 pad2[0x1E]; s16 b; s16 c; s16 d; s16 e; s16 f; u8 pad3[0x14]; } T;
extern T *D_800E79B8;
extern s32 D_800D5E80, D_800D5E84;
void func_800C33F4(s32);
void func_800BF65C(void);
s32 func_800C2E50(T *);
s16 func_80008574(s16);
void func_8000946C(s16, s16, s16);

void func_800C4B50(void) {
    T *p = D_800E79B8;
    s32 i;
    s32 v;
    for (i = 0; i < 4; i++, p++) {
        if (D_800D5E80 != 0) {
            do {
                D_800D5E84 = 0;
                func_800C33F4(i);
            } while (p->f != 0);
        } else {
            func_800C33F4(i);
        }
    }
    func_800BF65C();
    p = D_800E79B8;
    for (i = 0; i < 4; i++, p++) {
        if (p->a >= 0 && p->f == 0) {
            v = func_800C2E50(p);
            if ((v != p->b && p->c != 0) || p->d != p->c) {
                p->b = v;
                p->e = func_80008574(v);
                p->d = p->c;
                func_8000946C(i, p->b, p->c);
            }
        }
    }
}
