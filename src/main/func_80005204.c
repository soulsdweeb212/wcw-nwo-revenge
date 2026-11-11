/* @header
 * func_80005204
 * VRAM 0x80005204 | ROM 0x5E04 | size 0x8
 * asm: asm/nonmatchings/main/func_80005204.s
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
/* PC: the types of port_decls.h's line. obj is the 0xDC-byte object, which keeps its N64 layout (Nw2SceneObj in
 * common.h), so its display list at +0x10 is a 4-byte field that takes the list's handle (port.h's PTR_TO_SLOT). */
void func_80005204(void *obj, void *dl) {
    ((Nw2SceneObj *)obj)->dl = PTR_TO_SLOT(dl);
}
#else
void func_80005204(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x10) = arg1;
}
#endif
