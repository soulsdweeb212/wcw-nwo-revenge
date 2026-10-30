/* @header
 * func_80020D80
 * VRAM 0x80020D80 | ROM 0x21980 | size 0x1C
 * asm: asm/nonmatchings/main/func_80020D80.s
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

M2C_UNK func_80027390(M2C_UNK);                     /* extern */

void func_80020D80(void) {
    func_80027390(0x400);
}
