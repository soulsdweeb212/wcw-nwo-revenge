/* @header
 * MusBankStartEffect  (originally func_80014064)
 * VRAM 0x80014064 | ROM 0x14C64 | size 0xDC
 * asm: asm/nonmatchings/main/MusBankStartEffect.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

extern u32 max_channels;
extern u8 *mus_channels;
extern s32 *D_800604D8;
extern void *mus_init_bank;
extern void *D_800604F4;
s32 __MusIntStartEffect(void *,s32,s32,s32,s32);

/* Allocates a default voice for channel arg1 (threshold D_800604D8[arg1]):
 * records arg0 as the pending owner when it is due, takes the first free voice,
 * or the least-recently-used one below the threshold. Resets the pending owner
 * to D_800604F4 and returns the voice result (0 if none). */
s32 MusBankStartEffect(void *arg0, s32 arg1) {
    u8 *p;
    u8 *best;
    s32 threshold;
    s32 min;
    u32 i;
    s32 result;

    if (arg0 != NULL && *(s32 *)((u8 *)arg0 + 0x10) < 0)
        mus_init_bank = arg0;

    p = mus_channels;
    threshold = D_800604D8[arg1];
    min = threshold + 1;

    for (i = 0; i < max_channels; i++, p += 0x158) {
        if (*(s32 *)(p + 4) == 0) {
            result = __MusIntStartEffect(p, arg1, 0x80, 0x80, threshold);
            goto done;
        }
        if (*(u16 *)(p + 0xC6) != 0 && *(s32 *)(p + 0x64) < min) {
            min = *(s32 *)(p + 0x64);
            best = p;
        }
    }
    if (min < threshold)
        result = __MusIntStartEffect(best, arg1, 0x80, 0x80, threshold);
    else
        result = 0;
done:
    mus_init_bank = D_800604F4;
    return result;
}
