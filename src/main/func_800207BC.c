/* @header
 * func_800207BC
 * VRAM 0x800207BC | ROM 0x213BC | size 0x2C
 * asm: asm/nonmatchings/main/func_800207BC.s
 */
#include "common.h"

/* identical to func_80017F18 (matched), with its names changed by decompdecomp */
extern void *D_80037510;

/* Pop and return a command packet from the free list at D_80037510+0x2C. */
s32 *func_800207BC(void) {
    s32 *pkt;
    s32 *ret;

    pkt = *(s32 **)((u8 *)D_80037510 + 0x2C);
    ret = NULL;
    if (pkt != NULL) {
        ret = pkt;
        *(s32 **)((u8 *)D_80037510 + 0x2C) = (s32 *) *ret;
        *ret = NULL;
    }
    return ret;
}
