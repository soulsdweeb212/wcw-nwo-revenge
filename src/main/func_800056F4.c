/* @header
 * func_800056F4
 * VRAM 0x800056F4 | ROM 0x62F4 | size 0x10
 * asm: asm/nonmatchings/main/func_800056F4.s
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
/* PC: the callers pass three floats (func_80099F70 declares them f32, as overlay 1's func_800C3110 does), which the
 * function stores at +0, +4 and +8. On the N64 they travel in a1 to a3, integer registers, where the N64 definition
 * takes them as s32 and stores their bits; on PC floats travel in float registers, so the PC definition takes them
 * as f32 and stores the same bits (port_decls.h declares it so). */
void func_800056F4(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    M2C_FIELD(arg0, f32 *, 0) = arg1;
    M2C_FIELD(arg0, f32 *, 4) = arg2;
    M2C_FIELD(arg0, f32 *, 8) = arg3;
}
#else
void func_800056F4(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 8) = arg3;
}
#endif
