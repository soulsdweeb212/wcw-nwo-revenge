/* @header
 * func_80007AFC
 * VRAM 0x80007AFC | ROM 0x86FC | size 0xC
 * asm: asm/nonmatchings/main/func_80007AFC.s
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
/* PC: arg0 is an arena in its PC layout (Nw2MeshArena, common.h), so the two "handed out" counts go by name: at the
 * N64's +6 and +0xE the PC layout has the middle of the two pool bases. Both blocks stay, as on the N64. */
void func_80007AFC(void *arg0) {
    Nw2MeshArena *a = arg0;

    a->vertUsed = 0;
    a->cmdUsed = 0;
}
#else
void func_80007AFC(void *arg0) {
    M2C_FIELD(arg0, s16 *, 6) = 0;
    M2C_FIELD(arg0, s16 *, 0xE) = 0;
}
#endif
