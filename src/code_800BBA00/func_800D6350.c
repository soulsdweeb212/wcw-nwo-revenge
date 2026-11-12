/* @header
 * func_800D6350
 * VRAM 0x800D6350 | ROM 0xC97F0 | size 0x10
 * asm: asm/nonmatchings/code_800BBA00/func_800D6350.s
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

#ifdef TARGET_PC
/* PC: D_800FABD8 is an s32 (every other file declares it so, and the replay code sets its bit 0x10000). The N64
 * reads its first two bytes as a u16, which in the N64's byte order are the upper half, so it tests bit 0x10000; on
 * a PC the first two bytes are the lower half. The PC reads the s32 and tests that bit. */
extern s32 D_800FABD8;
#else
extern u16 D_800FABD8;
#endif

s32 func_800D6350(void) {
#ifdef TARGET_PC
    return (D_800FABD8 >> 16) & 1;
#else
    return D_800FABD8 & 1;
#endif
}
