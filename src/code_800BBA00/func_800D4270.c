/* @header
 * func_800D4270
 * VRAM 0x800D4270 | ROM 0xC7710 | size 0xC
 * asm: asm/nonmatchings/code_800BBA00/func_800D4270.s
 */
#include "common.h"

/* Set the wrestler's animId to -1 so the next animation start always restarts. */
void func_800D4270(Wrestler *w) {
    w->animId = -1;
}
