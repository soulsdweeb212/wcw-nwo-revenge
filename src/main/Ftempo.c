/* @header
 * Ftempo  (originally func_800162EC)
 * VRAM 0x800162EC | ROM 0x16EEC | size 0xE4
 * asm: asm/nonmatchings/main/Ftempo.s
 */
/* SDK: libmus, libmus/src/playerinc/player_commands.inc.c (same code as the SDK source). */
#include "common.h"

extern u32 max_channels;
extern u8 *mus_channels;
extern s32 mus_vsyncs_per_second;

typedef struct {
    u8 pad0[0x94];
    s32 id;       /* @0x94 */
    u8 pad98[0x24];
    s16 fBC;      /* @0xBC */
    s16 padBE[5];
    s16 fC8;      /* @0xC8 */
    u8 padCA[0x8E];
} Nw2Voice162EC;

/* Read a tuning byte from the sequence stream arg1 and convert it to a pitch:
 * lo = byte * 0x6000 / 120 / mus_vsyncs_per_second, hi = lo * arg1's +0xB8 / 128. If arg0's
 * voice slot (+0xC6) is live, store lo in +0xBC; otherwise find the allocated
 * voice with the same id and store lo/hi in its +0xC8/+0xBC. Returns the
 * advanced stream pointer. */
u8 *Ftempo(u8 *arg0, u8 *arg1)
{
    s32 lo;
    s32 hi;
    u32 i;
    Nw2Voice162EC *p;

    lo = (*arg1++ * 0x6000) / 120 / mus_vsyncs_per_second;
    hi = (lo * *(s16 *)(arg0 + 0xB8)) >> 7;
    if (*(u16 *)(arg0 + 0xC6) != 0) {
        *(s16 *)(arg0 + 0xBC) = lo;
    } else {
        p = (Nw2Voice162EC *)mus_channels;
        for (i = 0; i < max_channels; i++, p++) {
            if (p->id == *(s32 *)(arg0 + 0x94)) {
                p->fC8 = lo;
                p->fBC = hi;
            }
        }
    }
    return arg1;
}
