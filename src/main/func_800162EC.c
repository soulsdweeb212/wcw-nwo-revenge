#include "common.h"

extern u32 D_800604C8;
extern u8 *D_800604D0;
extern s32 D_800604DC;

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
 * lo = byte * 0x6000 / 120 / D_800604DC, hi = lo * arg1's +0xB8 / 128. If arg0's
 * voice slot (+0xC6) is live, store lo in +0xBC; otherwise find the allocated
 * voice with the same id and store lo/hi in its +0xC8/+0xBC. Returns the
 * advanced stream pointer. */
u8 *func_800162EC(u8 *arg0, u8 *arg1)
{
    s32 lo;
    s32 hi;
    u32 i;
    Nw2Voice162EC *p;

    lo = (*arg1++ * 0x6000) / 120 / D_800604DC;
    hi = (lo * *(s16 *)(arg0 + 0xB8)) >> 7;
    if (*(u16 *)(arg0 + 0xC6) != 0) {
        *(s16 *)(arg0 + 0xBC) = lo;
    } else {
        p = (Nw2Voice162EC *)D_800604D0;
        for (i = 0; i < D_800604C8; i++, p++) {
            if (p->id == *(s32 *)(arg0 + 0x94)) {
                p->fC8 = lo;
                p->fBC = hi;
            }
        }
    }
    return arg1;
}
