/* @header
 * func_800D96A0
 * VRAM 0x800D96A0 | ROM 0xCCB40 | size 0x174
 * asm: asm/nonmatchings/code_800BBA00/func_800D96A0.s
 */
#include "common.h"

extern u8 D_8007E228[];
extern u8 D_8007EF30[];
extern u8 D_800F9D12[];
extern u8 D_800F9D30[];

s32 func_800D96A0(u8 *arg0) {
    s16 i;
    s32 off;
    u64 flags;

    if (!(*(u16 *)(D_8007E228 + 0x58) & 0x200))
        goto fail;
    if (*(u16 *)(D_8007EF30 + 0x170) & 0x40)
        goto fail;
    if (*(u64 *)(arg0 + 0x20) & 0x200)
        goto fail;
    if (*(u64 *)(arg0 + 0x358) & 0x600000000000ULL)
        goto fail;
    for (i = 0; i < 4; i++) {
        off = i * 0x3B0;
        if (*(s16 *)(D_800F9D12 + off) == -1)
            continue;
        flags = *(u64 *)(D_800F9D30 + off);
        if (flags & 0x8000)
            continue;
        if (flags & 0x200)
            continue;
        if ((flags & 0x40) && (flags & 0x20000000000000ULL))
            return 1;
    }
    return 0;
fail:
    return 1;
}
