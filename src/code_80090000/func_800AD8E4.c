/* @header
 * func_800AD8E4
 * VRAM 0x800AD8E4 | ROM 0x5A054 | size 0x8C
 * asm: asm/nonmatchings/code_80090000/func_800AD8E4.s
 */
#include "common.h"

typedef struct { u8 p[0xC]; s8 c; u8 q[3]; s16 g; } A;

void func_800AD8E4(A *a, A *b, s32 k) {
    switch (k) {
    case 1:
        if (a->c) {
            a->c = 1;
            b->c = 0;
        } else {
            b->c = 1;
        }
        break;
    case 2:
        a->c = 1;
        b->c = 1;
        break;
    case 3:
        a->c = 2;
        b->c = 1;
        break;
    }
    a->g = a->c << 7;
    b->g = b->c << 7;
}
