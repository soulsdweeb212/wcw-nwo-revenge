/* @header
 * func_800D2ACC
 * VRAM 0x800D2ACC | ROM 0xC5F6C | size 0x98
 * asm: asm/nonmatchings/code_800BBA00/func_800D2ACC.s
 */
#include "common.h"

void translateEntityXZ(void *, void *);
/* Test w's boundary as if it stood moved by the XZ offset delta (called with w->moveDelta): translate w by it, run
 * func_800D2CAC(w, ..., divisor 1.0, bodyMask) without applying a correction, then translate w back.
 * Returns func_800D2CAC's side bits. */
s32 func_800D2ACC(Wrestler *w, s32 bodyMask, f32 *delta) {
    f32 offset[4];
    s32 result;
    translateEntityXZ(w, delta);
    result = func_800D2CAC(w, NULL, NULL, 1.0f, NULL, NULL, NULL, 0, bodyMask, 0);
    offset[0] = -delta[0];
    offset[2] = -delta[2];
    translateEntityXZ(w, offset);
    return result;
}
