/* @header
 * func_800A9010
 * VRAM 0x800A9010 | ROM 0x55780 | size 0xCC
 * asm: asm/nonmatchings/code_80090000/func_800A9010.s
 */
#include "common.h"

extern u8 D_8007EF30[];
#ifdef TARGET_PC
/* PC: each table is four points of three 16-bit values, x, y and z (func_800AEF28's Pt): where the screen before a
 * match puts each player's name and handicap meter. The PC starts game variables in its own byte order by the width
 * their declarations give (port/game_vars.tsv), so they are declared with that width here; the N64 code only takes
 * their addresses. As bytes they kept the N64's order, and the points landed thousands of pixels off the screen. */
extern s16 D_800CD054[], D_800CD06C[], D_800CD084[], D_800CD09C[], D_800CD0B4[], D_800CD0CC[];
#else
extern u8 D_800CD054[], D_800CD06C[], D_800CD084[], D_800CD09C[], D_800CD0B4[], D_800CD0CC[];
#endif
s32 func_800A9E40(void);

#ifdef TARGET_PC
s16 *func_800A9010(void) { /* PC: the tables' type (see above) */
#else
u8 *func_800A9010(void) {
#endif
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
