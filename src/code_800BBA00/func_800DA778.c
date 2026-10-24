#include "common.h"

extern u8 D_800FA063[];
extern u8 D_800FA065[];
extern u8 D_800F9D1A[];

s32 func_800DA778(s8 *arg0) {
    if (arg0[0] != arg0[0x355]) {
        switch ((s16)(*(u16 *)(D_800F9D1A + arg0[0x355] * 0x3B0) - 0x38)) {
        case 0:
        case 4:
        case 6:
        case 56:
        case 58:
            arg0[0x353] = D_800FA065[(s8)D_800FA063[arg0[0x355] * 0x3B0] * 0x3B0];
            break;
        case 1:
        case 5:
        case 7:
        case 57:
        case 59:
            arg0[0x353] = D_800FA063[arg0[0x355] * 0x3B0];
            break;
        case 60:
        case 61:
            break;
        }
    }
}
