/* @header
 * func_800C3094
 * VRAM 0x800C3094 | ROM 0x6F804 | size 0x7C
 * asm: asm/nonmatchings/code_80090000/func_800C3094.s
 */
#include "common.h"

typedef struct { u8 p[0x6C8]; u8 d; u8 e; s16 a; s16 b; s16 c; } S;
extern S *D_800E79B8;

void func_800C3094(s32 i, s32 a, s32 b, s32 c, s32 d, s32 e) {
    s32 end = i + 1;
    S *p;
    if (i < 0) {
        i = 0;
        end = 4;
    }
    p = &D_800E79B8[i];
    for (; i < end; i++, p++) {
        p->d = d;
        p->e = e;
        p->a = a;
        p->b = b;
        p->c = c;
    }
}
