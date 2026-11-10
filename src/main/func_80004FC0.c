/* @header
 * func_80004FC0
 * VRAM 0x80004FC0 | ROM 0x5BC0 | size 0x1C
 * asm: asm/nonmatchings/main/func_80004FC0.s
 */
#include "common.h"

/* machine draft (m2c) for gcc-2.7.2-kmc -G0 -mips3 -mgp32 -mfp32 -O2, tried by autopilot */
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
/* PC: the type of func_80006E7C's definition: it takes the texture's address (its definition names the header struct
 * Nw2TextureHeader6E7C, which only its own file has) and returns nothing. */
void func_80006E7C(void *texture);
#else
M2C_UNK func_80006E7C(s32);                         /* extern */
#endif

#ifdef TARGET_PC
/* PC: arg0 is a display record of a mesh or a picture (func_8000C1B8 passes &s5[i], one of a slot's records), whose
 * field +0x18 on the N64 is the address of its texture (f18). On PC the record is Nw2Descr4BA8 (common.h), where f18
 * is a pointer at its own PC offset; an s32 read at +0x18 would get half of another field. */
void func_80004FC0(void *arg0) {
    func_80006E7C(((Nw2Descr4BA8 *)arg0)->f18);
}
#else
void func_80004FC0(void *arg0) {
    func_80006E7C(M2C_FIELD(arg0, s32 *, 0x18));
}
#endif
