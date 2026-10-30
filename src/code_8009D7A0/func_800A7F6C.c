#include "common.h"

extern struct {
    u8 pad[0x1B0];
    u32 stats[1][2];
} D_8007EF30;

void func_800A7F6C(u8 *e, s16 arg1) {
    s16 a2 = 0x57;
    s16 i;

    if (arg1 == 0) {
        u8 *att = *(u8 **)(e + 0x364);
        if (*(u64 *)(att + 0x38) & 1) {
            i = (s16)(*(u16 *)(e + 0x386) - 0x21);
            switch (i) {
            case 0: case 2: case 5: case 7: case 10: case 12: case 15: case 17: case 20: case 22:
                a2 = 9;
                break;
            }
        } else {
            i = (s16)(*(u16 *)(e + 0x386) - 0x21);
            switch (i) {
            case 0: case 5: case 10:
                a2 = 0xB;
                break;
            case 2: case 7: case 12:
                a2 = 0x1B;
                break;
            }
        }
        if (*(u64 *)(e + 0x20) & 9) {
            switch (*(s16 *)(e + 0x386)) {
            case 0x93: case 0x94: case 0x95: case 0x96:
                a2 = 0;
                break;
            case 0: case 1: case 2: case 3:
                a2 = 1;
                break;
            case 4:
                a2 = 3;
                break;
            case 5: case 6:
                a2 = 4;
                break;
            }
        } else {
            switch (*(s16 *)(e + 0x386)) {
            case 0x93: case 0x94:
                a2 = 0;
                break;
            case 0x95: case 0x96:
                a2 = 1;
                break;
            case 0: case 1: case 2: case 3:
                a2 = 0xA;
                break;
            case 4: case 5: case 6: case 7:
                a2 = 0x1A;
                break;
            }
        }
        i = (s16)(*(u16 *)(e + 0x386) - 8);
        switch (i) {
        case 173: case 174: case 175: case 176: a2 = 1; break;
        case 143: case 144: a2 = 2; break;
        case 164: a2 = 3; break;
        case 149: case 151: a2 = 4; break;
        case 153: a2 = 5; break;
        case 155: a2 = 6; break;
        case 157: a2 = 7; break;
        case 172: a2 = 8; break;
        case 0: case 5: a2 = 0xA; break;
        case 10: case 15: case 20: a2 = 0xB; break;
        case 50: case 52: a2 = 0xC; break;
        case 53: case 54: a2 = 0xD; break;
        case 55: case 56: a2 = 0xE; break;
        case 57: case 59: a2 = 0xF; break;
        case 62: case 66: a2 = 0x10; break;
        case 70: case 74: a2 = 0x11; break;
        case 78: a2 = 0x12; break;
        case 82: case 87: a2 = 0x14; break;
        case 92: case 97: a2 = 0x15; break;
        case 102: a2 = 0x16; break;
        case 116: case 120: a2 = 0x17; break;
        case 117: case 121: a2 = 0x18; break;
        case 118: case 122: a2 = 0x19; break;
        case 1: case 2: case 3: case 4: case 6: case 7: case 8: case 9:
            a2 = 0x1A; break;
        case 11: case 12: case 13: case 14: case 16: case 17: case 18: case 19: case 21: case 22: case 23: case 24: case 26: case 28: case 29: case 31: case 33: case 34: case 36: case 38: case 39:
            a2 = 0x1B; break;
        case 60: a2 = 0x1C; break;
        case 61: a2 = 0x1D; break;
        case 83: case 84: case 85: case 86: case 88: case 89: case 90: case 91: a2 = 0x1E; break;
        case 93: case 94: case 95: case 96: case 98: case 99: case 100: case 101: a2 = 0x1F; break;
        case 119: case 123: a2 = 0x20; break;
        case 145: a2 = 0x21; break;
        case 146: a2 = 0x22; break;
        case 150: case 152: a2 = 0x23; break;
        case 154: case 156: a2 = 0x24; break;
        case 158: a2 = 0x25; break;
        case 165: a2 = 0x28; break;
        case 189: case 191: a2 = 0x29; break;
        case 193: case 195: a2 = 0x2A; break;
        case 167: case 168: a2 = 0x2C; break;
        case 169: a2 = 0x2D; break;
        case 188: case 190:
            a2 = ((s8)e[0x384] != (s8)e[0]) ? 0x2F : 0x2E; break;
        case 192: case 194:
            a2 = ((s8)e[0x384] != (s8)e[0]) ? 0x31 : 0x30; break;
        case 201: case 205: case 208: case 209: a2 = 0x32; break;
        case 202: a2 = 0x33; break;
        case 206: a2 = 0x34; break;
        case 207: a2 = 0x35; break;
        case 210: case 211: a2 = 0x36; break;
        case 213: case 214: case 215: a2 = 0x37; break;
        case 216: a2 = 0x38; break;
        case 217: a2 = 0x39; break;
        case 218: case 219: a2 = 0x3A; break;
        case 220: a2 = 0x3B; break;
        case 223: a2 = 0x3C; break;
        case 181: case 183: case 184: case 185: case 186: case 212:
            a2 = 0x3E; break;
        case 182: a2 = 0x3F; break;
        case 224: case 225: case 226: a2 = 0x42; break;
        case 135: a2 = 0x43; break;
        case 112: case 113: a2 = 0x44; break;
        case 166: a2 = 0x45; break;
        case 177: case 178: a2 = 0x46; break;
        }
    } else {
        a2 = arg1;
    }
    *(s16 *)(e + 0x388) = a2;
    if (a2 != 0x57) {
        if (D_8007EF30.stats[(s8)e[0] * 87 + a2][0] < 0xFFFFFFFFu) {
            D_8007EF30.stats[(s8)e[0] * 87 + a2][0]++;
        }
    }
}
