#include "common.h"

/* Applies the entity's mode byte (+0x36F): mode 7 clears and mode 8 sets the
 * 0x200000 flag; all higher modes are no-ops. Returns 1 when the mode is >= 7. */
s32 func_800D4CC4(u8 *arg0) {
    switch (arg0[0x36F]) {
    case 7:
        *(u64 *)(arg0 + 0x20) &= ~0x200000;
        break;
    case 8:
        *(u64 *)(arg0 + 0x20) |= 0x200000;
        break;
    case 9:
        break;
    case 10:
        break;
    case 11:
        break;
    case 12:
        break;
    case 13:
        break;
    case 14:
        break;
    case 15:
        break;
    case 16:
        break;
    case 17:
        break;
    case 18:
        break;
    case 19:
        break;
    case 20:
        break;
    case 21:
        break;
    case 22:
        break;
    case 23:
        break;
    case 24:
        break;
    case 25:
        break;
    case 26:
        break;
    case 27:
        break;
    case 28:
        break;
    case 29:
        break;
    case 30:
        break;
    case 31:
        break;
    case 32:
        break;
    }
    return arg0[0x36F] >= 7;
}
