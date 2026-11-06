/* @header
 * func_800AD7B0
 * VRAM 0x800AD7B0 | ROM 0xA0C50 | size 0x1A8
 * asm: asm/nonmatchings/code_8009D7A0/func_800AD7B0.s
 */
#include "common.h"

/* Returns a category 0..0x17 of w's action state (and step), for the AI (startEntityAction stores it for the
 * AI wrestler and for its opponent, other = the AI wrestler). States 3 and 4 depend on moveMode bit 0x20 (running);
 * for state 3 with a different id than other's, also on bit 0x8 (rope run). 0 means none of the listed states. */
s32 func_800AD7B0(Wrestler *w, Wrestler *other)
{
    s32 result = 0;
    s16 st = w->state - 1;
    switch (st) {
    case 2:
        result = 2;
        if (w->moveMode & 0x20) {
            if (w->id == other->id)
                result = 5;
            else if (w->moveMode & 0x8)
                result = 0xE;
            else
                result = 5;
        }
        break;
    case 19:
        result = 0xE;
        break;
    case 69:
        if (w->step == 2)
            result = 3;
        break;
    case 75:
        result = 3;
        break;
    case 43:
        {
            s32 fc = w->step;
            if (fc < 4) {
    case 86:
                result = 8;
            } else if (fc == 4)
                result = 0xD;
        }
        break;
    case 44:
        result = 9;
        break;
    case 46:
        result = 0x16;
        break;
    case 40: case 56: case 60: case 62: case 70: case 71:
        result = 4;
        break;
    case 3:
        if (w->moveMode & 0x20)
            result = 5;
        break;
    case 29:
        if (w->step >= 2)
            result = 6;
        break;
    case 6: case 21: case 26: case 27: case 28: case 30: case 31: case 32: case 33: case 34:
        result = 6;
        break;
    case 94:
        result = 7;
        break;
    case 0: case 22:
        result = 1;
        break;
    case 67:
        switch (w->step) {
        case 0: case 1: case 2: case 3:
            result = 1;
            break;
        case 4: case 7: case 8:
            result = 0xA;
            break;
        case 5: case 6:
            result = 0xC;
            break;
        }
        break;
    case 45:
        result = 0xC;
        break;
    case 66:
        result = 0xF;
        break;
    case 68:
        result = 0x10;
        break;
    case 9:
        if (w->step >= 3) {
            if (w->step < 5)
                result = 0x11;
            else if (w->step == 7)
                result = 0x11;
        }
        break;
    case 98: case 99: case 102: case 103: case 104: case 105:
        result = 0x17;
        break;
    case 106: case 107: case 108: case 109: case 110:
        result = 0x11;
        break;
    case 63:
        result = 0x12;
        break;
    case 92:
        result = 0x14;
        break;
    case 93:
        result = 0x15;
        break;
    case 10:
        result = 0x13;
        break;
    }
    return result;
}
