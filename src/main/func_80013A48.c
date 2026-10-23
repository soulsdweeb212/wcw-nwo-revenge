#include "common.h"

extern u32 D_800604C8;
extern u8 *D_800604D0;
extern s32 *D_800604D8;
s32 func_80015F64(void *, s32, s32, s32, s32);

s32 func_80013A48(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *p;
    u8 *best;
    s32 threshold;
    s32 min;
    u32 i;

    threshold = arg4;
    if (threshold == -1)
        threshold = D_800604D8[arg0];

    if (arg3 != 0) {
        p = D_800604D0;
        for (i = 0; i < D_800604C8; i++, p += 0x158) {
            if (*(u16 *)(p + 0xC6) == arg0)
                return func_80015F64(p, arg0, arg1, arg2, threshold);
        }
    }

    min = threshold + 1;
    p = D_800604D0;
    for (i = 0; i < D_800604C8; i++, p += 0x158) {
        if (*(s32 *)(p + 4) == 0)
            return func_80015F64(p, arg0, arg1, arg2, threshold);
        if (*(u16 *)(p + 0xC6) != 0 && *(s32 *)(p + 0x64) < min) {
            min = *(s32 *)(p + 0x64);
            best = p;
        }
    }
    if (min < threshold)
        return func_80015F64(best, arg0, arg1, arg2, threshold);
    return 0;
}
