#include "common.h"

extern u8 D_8007E228[], D_8007EF30[];
extern s16 D_800F9848[], D_800F9850[];
extern s8 D_800F9D10[];
s8 func_800D4198(s16);

static inline u8 check9270(u8 *p) {
    u8 result;
    s8 id;
    s32 offset;

    result = 0;
    if (func_800D3550(D_800F9848[*(s8 *)p] - *(s16 *)(p + 0x10)) > 50) {
        result = func_800D4198(250) != 0;
        goto out2;
    }
    if (D_800F9850[*(s8 *)p] < 2701) goto out;
    id = *(s8 *)p ^ 1;
    offset = id * 0x3B0;
    if (D_800F9D10[offset] == -1) goto out;
    if (!(*(u64 *)(D_800F9D30 + offset) & 0x80ULL)) goto out;
    if (func_800D4198(250)) result = 1;
out:
    return result;
out2:
    return result;
}

s32 func_800D9270(u8 *p) {
    if ((*(u64 *)(p + 0x20) & 0x40ULL) && (*(u16 *)(D_8007E228 + 0x58) & 0x200) && !(*(u16 *)(D_8007EF30 + 0x170) & 0x40)) {
        if (check9270(p)) return 1;
    }
    return 0;
}
