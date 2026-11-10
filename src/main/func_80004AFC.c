/* @header
 * func_80004AFC
 * VRAM 0x80004AFC | ROM 0x56FC | size 0x38
 * asm: asm/nonmatchings/main/func_80004AFC.s
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
/* PC: arg0 is a display record (func_80090380 passes its node), which is Nw2Descr4BA8 on PC, 0x50 bytes with 8-byte
 * address fields. The N64 code clears bytes 0-5 and the words at +0xC to +0x24; at those N64 offsets the PC would
 * clear halves of the addresses. So the PC clears the same fields by name: bytes 0-5, then fC to f24, all of them
 * pointers (f20 and f24 are work blocks). f6 and f28 stay, as on the N64. */
void func_80004AFC(void *arg0) {
    Nw2Descr4BA8 *d = arg0;

    d->pad0[0] = 0;
    d->pad0[1] = 0;
    d->f2 = 0;
    d->f3 = 0;
    d->pad4[0] = 0;
    d->pad4[1] = 0;
    d->fC = NULL;
    d->f10 = NULL;
    d->f14 = NULL;
    d->f18 = NULL;
    d->f1C = NULL;
    d->f20 = NULL;
    d->f24 = NULL;
}
#else
void func_80004AFC(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 0;
    M2C_FIELD(arg0, s8 *, 1) = 0;
    M2C_FIELD(arg0, s8 *, 2) = 0;
    M2C_FIELD(arg0, s8 *, 3) = 0;
    M2C_FIELD(arg0, s8 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 5) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
}
#endif
