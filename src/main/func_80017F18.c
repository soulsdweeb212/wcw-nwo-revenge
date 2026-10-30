/* @header
 * func_80017F18
 * VRAM 0x80017F18 | ROM 0x18B18 | size 0x2C
 * asm: asm/nonmatchings/main/func_80017F18.s
 */
#include "common.h"

extern void *D_80036F54;

/* Pop and return a command packet from the free list at D_80036F54+0x2C. */
s32 *func_80017F18(void) {
    s32 *pkt;
    s32 *ret;

    pkt = *(s32 **)((u8 *)D_80036F54 + 0x2C);
    ret = NULL;
    if (pkt != NULL) {
        ret = pkt;
        *(s32 **)((u8 *)D_80036F54 + 0x2C) = (s32 *) *ret;
        *ret = NULL;
    }
    return ret;
}
