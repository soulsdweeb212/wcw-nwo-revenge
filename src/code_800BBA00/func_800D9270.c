/* @header
 * func_800D9270
 * VRAM 0x800D9270 | ROM 0xCC710 | size 0x16C
 * asm: asm/nonmatchings/code_800BBA00/func_800D9270.s
 */
#include "common.h"

extern u8 D_8007E228[], D_8007EF30[];
extern s16 D_800F9848[], D_800F9850[];
s8 func_800D4198(s16);

static inline u8 check9270(Wrestler *p) {
    u8 result;
    s8 id;

    result = 0;
    if (func_800D3550(D_800F9848[p->id] - p->health) > 50) {
        result = func_800D4198(250) != 0;
        goto out2;
    }
    if (D_800F9850[p->id] < 2701) goto out;
    id = p->id ^ 1;
    if (D_800F9D10[id].id == -1) goto out;
    if (!(D_800F9D10[id].flags & WR_FLAG_ON_APRON)) goto out;
    if (func_800D4198(250)) result = 1;
out:
    return result;
out2:
    return result;
}

s32 func_800D9270(Wrestler *p) {
    if ((p->flags & WR_FLAG_IN_RING) && (*(u16 *)(D_8007E228 + 0x58) & 0x200) && !(*(u16 *)(D_8007EF30 + 0x170) & 0x40)) {
        if (check9270(p)) return 1;
    }
    return 0;
}
