/* @header
 * func_800A1550
 * VRAM 0x800A1550 | ROM 0x949F0 | size 0x1C
 * asm: asm/nonmatchings/code_8009D7A0/func_800A1550.s
 */
#include "common.h"

/* identical to func_80002C58 (matched), with its names changed by decompdecomp */
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

M2C_UNK func_800C5190();                            /* extern */

void func_800A1550(void) {
    func_800C5190();
}
