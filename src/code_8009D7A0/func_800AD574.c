#include "common.h"

/* func_800AD574: links target entity arg1 to source entity arg0 when the
 * source is in a non-attack animation (not 0x3A/0x3C) and its grab/attach
 * flag is set, the target is not already attached or grabbed, the source is
 * not exclusively attached unless the target is too, and the requested
 * direction mask intersects 0xC030. On success it sets the target's attached
 * bit, selects the target's animation from the source, then marks the target
 * as claimed (bit 0x4000000). */
s8 func_800B71F8(void *, void *, s32);
s16 func_800A8D14(void *, void *);
void func_800A7C40(void *, s8, s16);

void func_800AD574(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 *a = arg0;
    u8 *b = arg1;
    s16 anim = *(s16 *)(a + 0x386);
    s32 c0 = (anim != 0x3A);
    s32 c1 = (anim != 0x3C);

    if ((c0 & c1) && (*(u32 *)(a + 0x3AC) & 1)) {
        if (!(*(u64 *)(b + 0x20) & 9) && (!(*(u64 *)(a + 0x20) & 0x80000) || (*(u64 *)(b + 0x20) & 0x80000)) && !(*(u64 *)(b + 0x20) & 0x4000000) && (arg2 & 0xC030)) {
            if (func_800B71F8(b, a, 1)) {
                *(u64 *)(b + 0x20) |= 0x1000000;
                func_800A7C40(b, *(s8 *)a, func_800A8D14(a, b));
            }
            *(u64 *)(b + 0x20) |= 0x4000000;
        }
    }
}
