/* @header
 * func_800966B8
 * VRAM 0x800966B8 | ROM 0x42E28 | size 0x10
 * asm: asm/nonmatchings/code_80090000/func_800966B8.s
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
/* PC: the N64 reads the address at D_800DB4FC + 0x184, which is the label D_800DB680: a pointer, 8 bytes on PC, which
 * the PC reads by its own name (func_800948BC and func_800945E0 declare it as a pointer too). The u16 at +6 of the
 * record it points at is where it is on the N64. */
extern u8 *D_800DB680;

u16 func_800966B8(void) {
    return *(u16 *)(D_800DB680 + 6);
}
#else
extern M2C_UNK D_800DB4FC;

u16 func_800966B8(void) {
    return M2C_FIELD(M2C_FIELD(&D_800DB4FC, void **, 0x184), u16 *, 6);
}
#endif
