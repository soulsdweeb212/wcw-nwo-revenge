/* @header
 * tryBeginBlockReaction  (originally func_800E2400)
 * VRAM 0x800E2400 | ROM 0xD58A0 | size 0x100
 * asm: asm/nonmatchings/code_800DE9C0/func_800E2400.s
 */
#include "common.h"

s16 func_800D7A68(u16);
s32 func_800D7A2C(u16);
extern u16 D_800E3CEE[];

/* Attempt a blocking reaction: when arg0 has flag 0x100, arg2 bit 8 is set, the
 * mask arg3 isn't 0x2800, and the direction's mask table entry intersects
 * arg1 & arg3, pick the reaction value, store it at +0x3E (with bit 0x2000 for
 * values 1/3 when arg3 has 0x2000), issue command 0x7D and return 1. Else 0. */
s32 tryBeginBlockReaction(void *arg0, s32 arg1, s32 arg2, u32 arg3) {
    s32 value;
    u16 key = arg3;
    if (*(u64 *)((u8 *)arg0 + 0x20) & 0x100) {
        if (arg2 & 8) {
            if ((arg3 & 0x2800) != 0x2800) {
                if (D_800E3CEE[func_800D7A68(key)] & (arg1 & arg3)) {
                    value = func_800D7A2C(key);
                    *(s16 *)((u8 *)arg0 + 0x3E) = value;
                    switch ((s16)value) {
                    case 1: case 3:
                        if (arg3 & 0x2000) *(s16 *)((u8 *)arg0 + 0x3E) = value | 0x2000;
                        break;
                    }
                    func_800A6C48(arg0, 0x7D);
                    return 1;
                }
                return 0;
            }
        }
        return 0;
    }
    return 0;
}
