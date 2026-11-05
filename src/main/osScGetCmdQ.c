/* @header
 * osScGetCmdQ  (originally func_80000E00)
 * VRAM 0x80000E00 | ROM 0x1A00 | size 0xC
 * asm: asm/nonmatchings/main/osScGetCmdQ.s
 */
/* SDK: libultra 2.0I, ultralib src/sched/sched.c (SDK code with changes, see docs/sdk_functions.md). */
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

extern M2C_UNK D_800440C0;

M2C_UNK *osScGetCmdQ(void) {
    return &D_800440C0;
}
