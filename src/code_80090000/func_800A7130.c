/* @header
 * func_800A7130
 * VRAM 0x800A7130 | ROM 0x538A0 | size 0x78
 * asm: asm/nonmatchings/code_80090000/func_800A7130.s
 */
#include "common.h"

void func_800B6FE0(u32 **, s32);

void func_800A7130(u32 **dl, s32 b, s32 c, s32 d) {
    u32 *g = *dl;
    u32 *p;
    func_800B6FE0(&g, d);
    p = g;
    g = p + 2;
    p[0] = 0x70C0E0A;
    p[1] = 0xC0A08;
    func_800B6FE0(&g, c);
    *dl = g;
}
