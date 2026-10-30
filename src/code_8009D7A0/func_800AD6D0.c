/* @header
 * func_800AD6D0
 * VRAM 0x800AD6D0 | ROM 0xA0B70 | size 0x60
 * asm: asm/nonmatchings/code_8009D7A0/func_800AD6D0.s
 */
#include "common.h"

extern s16 D_800EB420[], D_800F9B78[];

/* Initialize entity entityId's state timer from its base value, clamped to a
 * minimum of 30. */
void func_800AD6D0(s8 *entityId)
{
    s16 *timer;
    D_800F9B78[*entityId] = D_800EB420[*entityId] * 10;
    timer = &D_800F9B78[*entityId];
    if (*timer < 30)
        *timer = 30;
}
