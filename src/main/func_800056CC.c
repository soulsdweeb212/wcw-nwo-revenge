/* @header
 * func_800056CC
 * VRAM 0x800056CC | ROM 0x62CC | size 0x28
 * asm: asm/nonmatchings/main/func_800056CC.s
 */
#include "common.h"

extern f32 D_80048580;
extern f32 D_80048584;
extern f32 D_80048588;

/* Return the cached camera eye position (X/Y/Z). */
void func_800056CC(f32 *arg0, f32 *arg1, f32 *arg2) {
    *arg0 = D_80048580;
    *arg1 = D_80048584;
    *arg2 = D_80048588;
}
