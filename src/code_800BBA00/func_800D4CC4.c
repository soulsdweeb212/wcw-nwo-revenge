#include "common.h"

/* Applies the entity's mode byte (+0x36F): odd modes 7..31 clear and even modes
 * 8..32 set the 0x200000 flag. Returns 1 when the mode is >= 7. */
s32 func_800D4CC4(u8 *arg0) {
    switch (arg0[0x36F]) {
    case 7:
    case 9:
    case 11:
    case 13:
    case 15:
    case 17:
    case 19:
    case 21:
    case 23:
    case 25:
    case 27:
    case 29:
    case 31:
        *(u64 *)(arg0 + 0x20) &= ~0x200000;
        break;
    case 8:
    case 10:
    case 12:
    case 14:
    case 16:
    case 18:
    case 20:
    case 22:
    case 24:
    case 26:
    case 28:
    case 30:
    case 32:
        *(u64 *)(arg0 + 0x20) |= 0x200000;
        break;
    }
    return arg0[0x36F] >= 7;
}
