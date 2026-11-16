/* @header
 * func_80099694
 * VRAM 0x80099694 | ROM 0x45E04 | size 0xC
 * asm: asm/nonmatchings/code_80090000/func_80099694.s
 */
#include "common.h"

/* identical to func_80000610 (matched), with its names changed by decompdecomp */
/* machine draft (m2c), tried by autopilot */
#ifndef M2C_DEFINES
#define M2C_DEFINES
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#endif

#ifdef TARGET_PC
/* PC: D_800C9434 is text, the letters of the costume name's keyboard ("abcde#7fghij..."), so it is declared as bytes.
 * tools/port_data.py converts a variable by the width its files give it, and as an M2C_UNK (an s32) the text would be
 * turned around 4 bytes at a time, which moves its line breaks: the keyboard is then drawn as one line six times as wide
 * as its picture, and the strips below it read past the picture's memory. */
extern u8 D_800C9434[];

M2C_UNK *func_80099694(void) {
    return (M2C_UNK *)D_800C9434;
}
#else
extern M2C_UNK D_800C9434;

M2C_UNK *func_80099694(void) {
    return &D_800C9434;
}
#endif
