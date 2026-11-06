/* @header
 * func_800D8DF0
 * VRAM 0x800D8DF0 | ROM 0xCC290 | size 0x154
 * asm: asm/nonmatchings/code_800BBA00/func_800D8DF0.s
 */
#include "common.h"

extern u8 D_8007E228[];
extern u8 D_8007EF30[];

s8 func_800D8DF0(Wrestler *arg0) {
    s16 i;
    u64 flags;

    if (!(*(u16 *)(D_8007E228 + 0x58) & 0x200))
        goto fail;
    if (*(u16 *)(D_8007EF30 + 0x170) & 0x40)
        goto fail;
    if (arg0->flags & WR_FLAG_LEGAL)
        goto fail;
    if (arg0->partnerFlags & 0x600000000000ULL)
        goto fail;
    for (i = 0; i < 4; i++) {
        if (D_800F9D10[i].characterId == -1)
            continue;
        flags = D_800F9D10[i].flags;
        if (flags & 0x8000)
            continue;
        if (!(flags & 0x200))
            continue;
        if (flags & 0x100)
            return 1;
    }
    return 0;
fail:
    return 1;
}
