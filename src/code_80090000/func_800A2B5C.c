/* @header
 * func_800A2B5C
 * VRAM 0x800A2B5C | ROM 0x4F2CC | size 0x64
 * asm: asm/nonmatchings/code_80090000/func_800A2B5C.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
void func_800B6FE0(G **, s32);
extern u16 D_8003A4FE[];

void func_800A2B5C(G **dl, s32 unused, s32 k) {
    G *g;
    G *p;
    g = *dl;
    func_800B6FE0(&g, D_8003A4FE[k * 4]);
    p = g++;
    p->w0 = 0x7000206;
    p->w1 = 0x604;
    *dl = g;
}
