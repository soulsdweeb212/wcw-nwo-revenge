#include "common.h"

extern u8 D_800FA0BC[];
s32 func_800DACB4(void *);

/* Maps a target entity's state and flags to a close-combat action id.  Target
 * state 0x75 with substate <3 yields 0xE8/0xE9 by its flag 0x100.  Otherwise flag
 * 0x40 leads through a per-state switch (0x38/39 -> 0xD5; 0x3C..3F -> 0xD5/D6/D7
 * by the linked entity's flag 0x800000 and self flag 0x80000/0x40000000; default
 * via func_800DACB4).  Without flag 0x40: flag 0x80 -> 0xD8; no flag 0x100 ->
 * 0xD1; the 0x600000000000 group maps 0x38/39 -> 0xD9, 0x3C..3F -> 0xD8/0xD9 by
 * the linked flag, else 0xD8; and flag 0x400000 -> 0xD9. */
s16 func_800DA9C0(u8 *self, u8 *target) {
    s16 stateIndex;
    u32 linkedFlags;
    u8 *attachment;
    u64 flags;

    if (*(s16 *)(target + 0xA) == 0x75 && *(s16 *)(target + 0xC) < 3) {
        if (*(u64 *)(target + 0x20) & 0x100) {
            return 0xE9;
        }
        return 0xE8;
    }
    if (*(u64 *)(target + 0x20) & 0x40) {
        if (*(u64 *)(target + 0x20) & 0x400000) {
            attachment = *(u8 **)(self + 0x364);
            if (*(u64 *)(attachment + 0x38) & 0x40000000) {
                if (*(u64 *)(self + 0x20) & 0x80000) {
                    return 0xD7;
                }
                return 0xD6;
            }
            return 0xD5;
        }
        if (*(u64 *)(target + 0x20) & 0x600000000000ULL) {
            stateIndex = *(u16 *)(target + 0xA) - 0x38;
            switch (stateIndex) {
            case 0:
            case 1:
                return 0xD5;
            case 4:
            case 5:
            case 6:
            case 7:
                if (*(u64 *)(target + 0x20) & 0x200000000000ULL) {
                    linkedFlags = *(u32 *)(target + 0x3AC);
                } else {
                    linkedFlags = *(u32 *)(D_800FA0BC + (s8)*(u8 *)(target + 0x353) * 0x3B0);
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
    flags = *(u64 *)(target + 0x20);
    if (flags & 0x80) {
        return 0xD8;
    }
    if (!(flags & 0x100)) {
        return 0xD1;
    }
    if (flags & 0x600000000000ULL) {
        stateIndex = *(u16 *)(target + 0xA) - 0x38;
        switch (stateIndex) {
        case 0:
        case 1:
            return 0xD9;
        case 4:
        case 5:
        case 6:
        case 7:
            if (*(u64 *)(target + 0x20) & 0x200000000000ULL) {
                linkedFlags = *(u32 *)(target + 0x3AC);
            } else {
                linkedFlags = *(u32 *)(D_800FA0BC + (s8)*(u8 *)(target + 0x353) * 0x3B0);
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
