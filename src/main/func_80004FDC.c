/* @header
 * func_80004FDC
 * VRAM 0x80004FDC | ROM 0x5BDC | size 0x38
 * asm: asm/nonmatchings/main/func_80004FDC.s
 */
#include "common.h"

/* Enable a descriptor subrecord: mark it active (f0 = 1), store the frame
 * count (f2C) and length (f2E), and set the derived end value f30 to
 * base + length*16 when count is nonzero, otherwise 0. */
void func_80004FDC(Nw2Sub4BA8 *sub, s32 base, s16 count, s16 length) {
    sub->f2C = count;
    sub->f0 = 1;
    sub->f2E = length;
    if ((count << 0x10) != 0) {
        sub->f30 = (s32)(base + ((s32)(length << 0x10) >> 0xC));
        return;
    }
    sub->f30 = 0;
}
