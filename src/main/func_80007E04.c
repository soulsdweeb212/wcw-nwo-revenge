/* @header
 * func_80007E04
 * VRAM 0x80007E04 | ROM 0x8A04 | size 0x10
 * asm: asm/nonmatchings/main/func_80007E04.s
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
/* PC: the callers pass three floats, which the function stores at +0x30, +0x34 and +0x38 of the 4x4 float matrix at
 * arg0, its translation. func_80008CE8, func_80012CD0, updateBodyPartTransforms and func_8009A69C declare all three
 * f32. buildEntityPartTransforms declares the last one s32 and passes a float's bits there; on the PC it reads that
 * float as f32 and passes it.
 * On the N64 they travel in a1 to a3, integer registers, where the N64 definition takes them as s32 and stores their
 * bits; on PC floats travel in float registers, so the PC definition takes them as f32 and stores the same bits
 * (port_decls.h declares it so). */
void func_80007E04(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    M2C_FIELD(arg0, f32 *, 0x30) = arg1;
    M2C_FIELD(arg0, f32 *, 0x34) = arg2;
    M2C_FIELD(arg0, f32 *, 0x38) = arg3;
}
#else
void func_80007E04(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32 *, 0x30) = arg1;
    M2C_FIELD(arg0, s32 *, 0x34) = arg2;
    M2C_FIELD(arg0, s32 *, 0x38) = arg3;
}
#endif
