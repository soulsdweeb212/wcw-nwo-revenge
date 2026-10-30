/* @header
 * func_80004658
 * VRAM 0x80004658 | ROM 0x5258 | size 0x98
 * asm: asm/nonmatchings/main/func_80004658.s
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

M2C_UNK releaseHeapBlock(M2C_UNK *);                /* extern */
extern M2C_UNK *nw2ResourceCacheHead;

void func_80004658(s32 arg0) {
    M2C_UNK *var_s0;
    M2C_UNK *var_v1;
    u16 temp_v0;

    var_s0 = nw2ResourceCacheHead;
    var_v1 = NULL;
    if (var_s0 != NULL) {
loop_1:
        if (M2C_FIELD(var_s0, s32 *, 4) != arg0) {
            var_v1 = var_s0;
            var_s0 = M2C_FIELD(var_s0, M2C_UNK **, 0);
            if (var_s0 != NULL) {
                goto loop_1;
            }
        }
        if (var_s0 != NULL) {
            temp_v0 = M2C_FIELD(var_s0, u16 *, 0xA) - 1;
            M2C_FIELD(var_s0, u16 *, 0xA) = temp_v0;
            if (!(temp_v0 & 0xFFFF)) {
                if (var_v1 == NULL) {
                    nw2ResourceCacheHead = M2C_FIELD(var_s0, M2C_UNK **, 0);
                } else {
                    *var_v1 = M2C_FIELD(var_s0, M2C_UNK **, 0);
                }
                releaseHeapBlock(M2C_FIELD(var_s0, M2C_UNK **, 4));
                releaseHeapBlock(var_s0);
            }
        }
    }
}
