/* @header
 * func_80014064
 * VRAM 0x80014064 | ROM 0x14C64 | size 0xDC
 * asm: asm/nonmatchings/main/func_80014064.s
 */
#include "common.h"

extern u32 D_800604C8;
extern u8 *D_800604D0;
extern s32 *D_800604D8;
extern void *D_800604F0;
extern void *D_800604F4;
s32 func_80015F64(void *,s32,s32,s32,s32);

/* Allocates a default voice for channel arg1 (threshold D_800604D8[arg1]):
 * records arg0 as the pending owner when it is due, takes the first free voice,
 * or the least-recently-used one below the threshold. Resets the pending owner
 * to D_800604F4 and returns the voice result (0 if none). */
s32 func_80014064(void *arg0, s32 arg1) {
    u8 *p;
    u8 *best;
    s32 threshold;
    s32 min;
    u32 i;
    s32 result;

    if (arg0 != NULL && *(s32 *)((u8 *)arg0 + 0x10) < 0)
        D_800604F0 = arg0;

    p = D_800604D0;
    threshold = D_800604D8[arg1];
    min = threshold + 1;

    for (i = 0; i < D_800604C8; i++, p += 0x158) {
        if (*(s32 *)(p + 4) == 0) {
            result = func_80015F64(p, arg1, 0x80, 0x80, threshold);
            goto done;
        }
        if (*(u16 *)(p + 0xC6) != 0 && *(s32 *)(p + 0x64) < min) {
            min = *(s32 *)(p + 0x64);
            best = p;
        }
    }
    if (min < threshold)
        result = func_80015F64(best, arg1, 0x80, 0x80, threshold);
    else
        result = 0;
done:
    D_800604F0 = D_800604F4;
    return result;
}
