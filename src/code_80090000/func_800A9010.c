/* @header
 * func_800A9010
 * VRAM 0x800A9010 | ROM 0x55780 | size 0xCC
 * asm: asm/nonmatchings/code_80090000/func_800A9010.s
 */
#include "common.h"

extern u8 D_8007EF30[];
extern u8 D_800CD054[], D_800CD06C[], D_800CD084[], D_800CD09C[], D_800CD0B4[], D_800CD0CC[];
s32 func_800A9E40(void);

u8 *func_800A9010(void) {
    switch (*(u16 *)(D_8007EF30 + 8) & 0xF0) {
    case 0x10:
        return D_800CD054;
    case 0x20:
        return D_800CD06C;
    case 0x40:
        return D_800CD084;
    case 0x80:
        return D_800CD09C;
    }
    if ((*(u16 *)(D_8007EF30 + 8) & 0xF) == 6 && func_800A9E40()) {
        return D_800CD0CC;
    }
    return D_800CD0B4;
}
