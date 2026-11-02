/* @header
 * func_800B7F3C
 * VRAM 0x800B7F3C | ROM 0x646AC | size 0x114
 * asm: asm/nonmatchings/code_80090000/func_800B7F3C.s
 */
#include "common.h"

typedef struct { f32 v; s32 pad; } K;
typedef struct { K *k; s32 n; } C;
typedef struct { C *c; u16 a; u16 id; } E;
extern E D_800D2530[];
extern s32 D_800D28F4, D_800DC8E0;
extern s32 D_800DC918[];
extern f32 D_800DC930[], D_800DC940, D_800DC944;
void func_800B8368(f32, f32, f32, f32, f32, f32);

s32 func_800B7F3C(s32 id) {
    s32 i, f;
    C *c;
    f = -1;
    for (i = 0; D_800D2530[i].c != 0; i++) {
        if (D_800D2530[i].id == id) {
            f = i;
        }
    }
    if (f < 0) {
        return 0;
    }
    if (D_800D28F4 != id) {
        c = D_800D2530[f].c;
        D_800D28F4 = id;
        D_800DC8E0 = f;
        for (i = 0; i < 6; i++, c++) {
            D_800DC930[i] = c->k[c->n - 1].v;
            D_800DC918[i] = 0;
        }
        func_800B8368(D_800DC930[0], D_800DC930[1], D_800DC930[2], D_800DC930[3], D_800DC940, D_800DC944);
    }
    return -1;
}
