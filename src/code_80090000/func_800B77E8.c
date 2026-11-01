/* @header
 * func_800B77E8
 * VRAM 0x800B77E8 | ROM 0x63F58 | size 0x6C
 * asm: asm/nonmatchings/code_80090000/func_800B77E8.s
 */
#include "common.h"

u8 *func_800B600C(s32, s32);
void appendPaletteSetupDisplayList(u32 **);

u8 *func_800B77E8(u32 **dl, s32 a, s32 c, s32 b) {
    u32 *g = *dl;
    u8 *v;
    if (a >= 0) {
        return 0;
    }
    v = func_800B600C(a, b);
    if (v == 0) {
        return 0;
    }
    appendPaletteSetupDisplayList(&g);
    *dl = g;
    return v;
}
