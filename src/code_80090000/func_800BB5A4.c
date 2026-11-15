/* @header
 * func_800BB5A4
 * VRAM 0x800BB5A4 | ROM 0x67D14 | size 0x144
 * asm: asm/nonmatchings/code_80090000/func_800BB5A4.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the type of func_8002AEE0's definition, which takes the id to look up and returns a u16. */
u16 func_8002AEE0(s32 arg0);
#else
s32 func_8002AEE0(void);
#endif
s32 guRandom(void);

#ifdef TARGET_PC
/* PC: on the N64 this function does not touch a0 before it calls func_8002AEE0 (asm: the jal is its third
 * instruction), so func_8002AEE0 looks up the caller's first argument: the wrestler id that func_800BCDF4 passes (it
 * declares s32 func_800BB5A4(s32)). On PC an argument reaches only a parameter that is declared, so the PC definition
 * takes the id and passes it on. */
s32 func_800BB5A4(s32 id) {
    s32 t;
    switch (func_8002AEE0(id) & 0xF0) {
#else
s32 func_800BB5A4(void) {
    s32 t;
    switch (func_8002AEE0() & 0xF0) {
#endif
    case 0x00:
        return 1;
    case 0x10:
        return 2;
    case 0x20:
        return 3;
    case 0x30:
        return 4;
    case 0x40:
        return 5;
    case 0x50:
        return 6;
    case 0x60:
        return 7;
    case 0x70:
        return 8;
    }
    t = guRandom() % 100;
    if (t < 10) {
        return 1;
    }
    if (t < 15) {
        return 3;
    }
    if (t < 25) {
        return 4;
    }
    if (t < 30) {
        return 5;
    }
    if (t < 40) {
        return 6;
    }
    if (t < 50) {
        return 7;
    }
    return (t < 60) * 8;
}
