#include "common.h"

void translateEntityXZ(void *, void *);
s32 func_800D35B0(s32, s32);
s32 func_800D2C2C(void *, void *, void *, f32, void *, s32);
s32 func_800D3E40(void *, void *, s32, void *);

/* Two-phase XZ move toward a target: while the entity's s16 +0x16 is below 10, translate it
 * toward the +0x33C offset, turn its heading (+0x58) by its +0x348 delta, run the boundary
 * correction func_800D2C2C with a 4.0f step and mask 0xFFFFE, then bump +0x16 and return 0.
 * Once +0x16 reaches 10, snap the heading to a3's +0xC, run the final boundary correction
 * func_800D3E40 toward q's heading into p+0x4C and return 1. */
s32 func_800CE2C8(u8 *p, u8 *q, void *a2, u8 *a3, void *a4) {
    if (*(s16 *)(p + 0x16) >= 10) {
        *(s32 *)(p + 0x58) = *(s32 *)(a3 + 0xC);
        func_800D3E40(a4, a3, *(s32 *)(q + 0x58), p + 0x4C);
        return 1;
    }
    translateEntityXZ(p, p + 0x33C);
    *(s32 *)(p + 0x58) = func_800D35B0(*(s32 *)(p + 0x58), *(s32 *)(p + 0x348));
    func_800D2C2C(p, q, a2, 4.0f, a4, 0xFFFFE);
    (*(s16 *)(p + 0x16))++;
    return 0;
}
