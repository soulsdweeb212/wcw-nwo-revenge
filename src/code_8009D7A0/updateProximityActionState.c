/* @header
 * updateProximityActionState  (originally func_800B2934)
 * VRAM 0x800B2934 | ROM 0xA5DD4 | size 0x144
 * asm: asm/nonmatchings/code_8009D7A0/func_800B2934.s
 */
#include "common.h"

s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
extern f64 D_800E52A8;
extern u8 *D_800FAF58;
extern u8 *D_800F9B60;
extern u8 *D_800FABD0;
extern u8 D_800FAC20[];
extern u8 D_800FAC24[];

/* When the entity is in state 1 and it faces the target within the threshold
 * (angle >= 0x401) and its action timer is below the per-entity limit, the
 * action count is bumped. Otherwise (or when the action substate is not 5) the
 * action record is reset to state 0 with the entity's animation copied. */
void updateProximityActionState(void) {
    u8 *o;
    u8 *g;
    if (*(s16 *)(D_800FAF58 + 0xA) == 1) {
        if (func_800D3550(func_800D3684(*(s32 *)(D_800FAF58 + 0x58), *(s32 *)(D_800F9B60 + 0x58))) >= 0x401) {
            s32 idx = *(s8 *)D_800FAF58 << 6;
            if (*(f32 *)(D_800FABD0 + 0x34) < (f32)(*(f32 *)(D_800FAC20 + idx) + *(s16 *)(D_800FAC24 + idx) * D_800E52A8)) {
                *(s16 *)(D_800FABD0 + 6) = 0x4000;
                *(u16 *)(D_800FABD0 + 4) = *(u16 *)(D_800FABD0 + 4) + 1;
            }
        }
        o = D_800FABD0;
        if (*(s16 *)(o + 0x22) != 5) {
            g = D_800F9B60;
            *(s16 *)(o + 2) = 0;
            *(s16 *)(o + 4) = 0;
            *(u16 *)(o + 0x2E) = *(u16 *)(g + 0xA);
            *(u32 *)(o + 0x5C) &= ~7;
        }
    } else {
        u8 *o2 = D_800FABD0;
        u8 *g2 = D_800F9B60;
        *(s16 *)(o2 + 2) = 0;
        *(s16 *)(o2 + 4) = 0;
        *(u16 *)(o2 + 0x2E) = *(u16 *)(g2 + 0xA);
        *(u32 *)(o2 + 0x5C) &= ~7;
    }
}
