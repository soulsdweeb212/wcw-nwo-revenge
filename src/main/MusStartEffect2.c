/* @header
 * MusStartEffect2  (originally func_80013A48)
 * VRAM 0x80013A48 | ROM 0x14648 | size 0x110
 * asm: asm/nonmatchings/main/MusStartEffect2.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

extern u32 max_channels;
extern u8 *mus_channels;
extern s32 *D_800604D8;
s32 __MusIntStartEffect(void *, s32, s32, s32, s32);

s32 MusStartEffect2(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *p;
    u8 *best;
    s32 threshold;
    s32 min;
    u32 i;

    threshold = arg4;
    if (threshold == -1)
        threshold = D_800604D8[arg0];

    if (arg3 != 0) {
        p = mus_channels;
        for (i = 0; i < max_channels; i++, p += 0x158) {
            if (*(u16 *)(p + 0xC6) == arg0)
                return __MusIntStartEffect(p, arg0, arg1, arg2, threshold);
        }
    }

    min = threshold + 1;
    p = mus_channels;
    for (i = 0; i < max_channels; i++, p += 0x158) {
        if (*(s32 *)(p + 4) == 0)
            return __MusIntStartEffect(p, arg0, arg1, arg2, threshold);
        if (*(u16 *)(p + 0xC6) != 0 && *(s32 *)(p + 0x64) < min) {
            min = *(s32 *)(p + 0x64);
            best = p;
        }
    }
    if (min < threshold)
        return __MusIntStartEffect(best, arg0, arg1, arg2, threshold);
    return 0;
}
