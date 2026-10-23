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
