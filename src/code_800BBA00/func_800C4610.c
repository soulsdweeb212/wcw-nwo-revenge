#include "common.h"

s32 func_800D35B0(s32, s32);
f32 func_800D3890(void *, void *, void *);

/* Steer arg0's heading (+0x58) toward arg1. For a few reaction ids (+0x386) the
 * heading is first offset by 0x800. Half of the angular difference to the
 * target is applied, and when the resulting heading is within 0x400 of the
 * target's heading, the entity's "facing target" flag (bit 0x08000000 of the
 * +0x20 flag word) and bit 0x1000 of +0x30 are set; the facing flag is cleared
 * up front. */
void func_800C4610(u8 *arg0, u8 *arg1) {
    Nw2DirectionResult direction;
    s32 angle;
    *(u64 *)(arg1 + 0x20) &= ~0x08000000ULL;
    angle = *(s32 *)(arg0 + 0x58);
    switch (*(s16 *)(arg0 + 0x386)) {
    case 0xB6: case 0xDE: case 0xDF: case 0xE0: case 0xE7:
        angle = func_800D35B0(angle, 0x800);
        break;
    }
    func_800D3890(arg0 + 0x6C, arg1 + 0x6C, &direction);
    angle = func_800D35B0(angle, func_800D3684(direction.angle, angle) / 2);
    if (func_800D3550(func_800D3684(*(s32 *)(arg1 + 0x58), angle)) < 0x400) {
        *(u64 *)(arg1 + 0x20) |= 0x08000000ULL;
        *(u32 *)(arg1 + 0x30) |= 0x1000;
    }
}
