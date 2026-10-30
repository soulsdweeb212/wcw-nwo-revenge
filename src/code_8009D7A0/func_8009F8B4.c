/* @header
 * func_8009F8B4
 * VRAM 0x8009F8B4 | ROM 0x92D54 | size 0x1C
 * asm: asm/nonmatchings/code_8009D7A0/func_8009F8B4.s
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

M2C_UNK func_800BE908();                            /* extern */

void func_8009F8B4(void) {
    func_800BE908();
}
