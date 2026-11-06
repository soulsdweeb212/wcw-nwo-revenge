/* @header
 * func_800AD6D0
 * VRAM 0x800AD6D0 | ROM 0xA0B70 | size 0x60
 * asm: asm/nonmatchings/code_8009D7A0/func_800AD6D0.s
 */
#include "common.h"

extern s16 D_800EB420[], D_800F9B78[];

/* Set D_800F9B78[w->id] to 10 * D_800EB420[w->id], at least 30. */
void func_800AD6D0(Wrestler *w)
{
    s16 *timer;
    D_800F9B78[w->id] = D_800EB420[w->id] * 10;
    timer = &D_800F9B78[w->id];
    if (*timer < 30)
        *timer = 30;
}
