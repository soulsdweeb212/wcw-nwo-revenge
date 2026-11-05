/* @header
 * nw2Sqrtf  (originally func_8001A480)
 * VRAM 0x8001A480 | ROM 0x1B080 | size 0x8
 * asm: asm/nonmatchings/main/nw2Sqrtf.s
 */
/* SDK: libultra 2.0I sqrtf (ultralib src/gu/sqrtf.s), a single sqrt.s. Named nw2Sqrtf because GCC expands a call named
 * sqrtf inline (sqrt.s plus a fallback call), which is what libultra's own callers (guAlignF ...) do in the ROM, while
 * the game calls this address directly; the symbol sqrtf in build.json is the second name the libultra callers use. */
#include "common.h"

/* machine draft (m2c) for gcc-2.7.2-kmc -G0 -mips3 -mgp32 -mfp32 -O2 -ffast-math, tried by autopilot */
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

f32 nw2Sqrtf(f32 arg0) {
    return sqrtf(arg0);
}
