/* @header
 * func_8001653C
 * VRAM 0x8001653C | ROM 0x1713C | size 0x10
 * asm: asm/nonmatchings/main/func_8001653C.s
 */
#include "common.h"

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

s32 func_8001653C(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0xD7) = 1;
    return arg1;
}
