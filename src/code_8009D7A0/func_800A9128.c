#include "common.h"

/* Ring-boundary clamp for an entity position: when the entity's u64 flag
 * 0x0800000000000000 is set, copy its X/Z position (+0x6C/+0x74) into the
 * boundary point (+0x4C/+0x54) and clamp the quadrant-selected axis (s16 +0x3C)
 * to +/-265: quadrant 0 clamps Z=+265, 1 X=+265, 2 Z=-265, 3 X=-265.
 * Returns 1 when applied, otherwise 0. */
s32 func_800A9128(u8 *entity) {
    if (*(u64 *)(entity + 0x20) & 0x0800000000000000ULL) {
        f32 x = *(f32 *)(entity + 0x6C);
        f32 z = *(f32 *)(entity + 0x74);
        s32 quadrant = *(s16 *)(entity + 0x3C);
        *(f32 *)(entity + 0x4C) = x;
        *(f32 *)(entity + 0x54) = z;
        switch (quadrant) {
        case 0: *(f32 *)(entity + 0x54) = 265.0f; break;
        case 1: *(f32 *)(entity + 0x4C) = 265.0f; break;
        case 2: *(f32 *)(entity + 0x54) = -265.0f; break;
        case 3: *(f32 *)(entity + 0x4C) = -265.0f; break;
        }
        return 1;
    }
    return 0;
}
