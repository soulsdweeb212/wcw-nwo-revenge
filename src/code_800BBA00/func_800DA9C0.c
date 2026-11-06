/* @header
 * func_800DA9C0
 * VRAM 0x800DA9C0 | ROM 0xCDE60 | size 0x2F4
 * asm: asm/nonmatchings/code_800BBA00/func_800DA9C0.s
 */
#include "common.h"

s32 func_800DACB4(Wrestler *);

/* Maps a target wrestler's state and flags to a close-combat action id.  Target
 * state 0x75 with step <3 yields 0xE8/0xE9 by its flag 0x100 (on floor).  Otherwise
 * flag 0x40 (in ring) leads through a per-state switch (0x38/39 -> 0xD5; 0x3C..3F
 * -> 0xD5 unless the move flags (own, or its opponent's) have 0x800000; flag
 * 0x400000 -> 0xD5/D6/D7 by profile bit and self flag 0x80000; default via
 * func_800DACB4).  Without flag 0x40: flag 0x80 -> 0xD8; no flag 0x100 ->
 * 0xD1; the 0x600000000000 group maps 0x38/39 -> 0xD9, 0x3C..3F -> 0xD8/0xD9 by
 * the linked flag, else 0xD8; and flag 0x400000 -> 0xD9. */
s16 func_800DA9C0(Wrestler *self, Wrestler *target) {
    s16 stateIndex;
    u32 linkedFlags;
    u8 *profile;
    u64 flags;

    if (target->state == 0x75 && target->step < 3) {
        if (target->flags & WR_FLAG_ON_FLOOR) {
            return 0xE9;
        }
        return 0xE8;
    }
    if (target->flags & WR_FLAG_IN_RING) {
        if (target->flags & 0x400000) {
            profile = self->profile;
            if (*(u64 *)(profile + 0x38) & 0x40000000) {
                if (self->flags & 0x80000) {
                    return 0xD7;
                }
                return 0xD6;
            }
            return 0xD5;
        }
        if (target->flags & 0x600000000000ULL) {
            stateIndex = (u16)target->state - 0x38;
            switch (stateIndex) {
            case 0:
            case 1:
                return 0xD5;
            case 4:
            case 5:
            case 6:
            case 7:
                if (target->flags & 0x200000000000ULL) {
                    linkedFlags = target->move.flags;
                } else {
                    linkedFlags = D_800F9D10[target->opponentId].move.flags;
                }
                if (!(linkedFlags & 0x800000)) {
                    return 0xD5;
                }
                break;
            case 2:
            case 3:
            case 8: case 9: case 10: case 11: case 12: case 13:
            case 14: case 15: case 16: case 17: case 18: case 19:
            case 20: case 21: case 22: case 23: case 24: case 25:
            case 26: case 27: case 28: case 29: case 30: case 31:
            case 32: case 33: case 34: case 35: case 36: case 37:
            case 38: case 39: case 40: case 41: case 42: case 43:
            case 44: case 45: case 46: case 47: case 48: case 49:
            case 50: case 51: case 52: case 53: case 54: case 55:
            case 56: case 57: case 58: case 59:
            default:
                break;
            }
        }
        return (s16)func_800DACB4(self);
    }
    flags = target->flags;
    if (flags & WR_FLAG_ON_APRON) {
        return 0xD8;
    }
    if (!(flags & WR_FLAG_ON_FLOOR)) {
        return 0xD1;
    }
    if (flags & 0x600000000000ULL) {
        stateIndex = (u16)target->state - 0x38;
        switch (stateIndex) {
        case 0:
        case 1:
            return 0xD9;
        case 4:
        case 5:
        case 6:
        case 7:
            if (target->flags & 0x200000000000ULL) {
                linkedFlags = target->move.flags;
            } else {
                linkedFlags = D_800F9D10[target->opponentId].move.flags;
            }
            return (linkedFlags & 0x800000) ? 0xD8 : 0xD9;
        case 2:
        case 3:
        case 8: case 9: case 10: case 11: case 12: case 13:
        case 14: case 15: case 16: case 17: case 18: case 19:
        case 20: case 21: case 22: case 23: case 24: case 25:
        case 26: case 27: case 28: case 29: case 30: case 31:
        case 32: case 33: case 34: case 35: case 36: case 37:
        case 38: case 39: case 40: case 41: case 42: case 43:
        case 44: case 45: case 46: case 47: case 48: case 49:
        case 50: case 51: case 52: case 53: case 54: case 55:
        case 56: case 57: case 58: case 59:
        default:
            return 0xD8;
        }
    }
    if (flags & 0x400000) {
        return 0xD9;
    }
    return 0xD8;
}
