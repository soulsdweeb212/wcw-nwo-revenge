/* @header
 * func_800B955C
 * VRAM 0x800B955C | ROM 0xAC9FC | size 0x1D4
 * asm: asm/nonmatchings/code_8009D7A0/func_800B955C.s
 */
#include "common.h"

/* Clear the flag bits `mask` from the flags of each of the 4 wrestler records.
 * For every record that had any of the bits set it clears them, builds two
 * {id, -1, -1, -1} buffers (the record's heldById, i.e. its attacker, and the
 * record index) and dispatches func_800B9730: either the
 * 0x10000 presentation path (with a sound and a possible func_800B8484
 * fallback) or the 0x100000/mode path, returning 1 on a hit. */
extern s16 D_800EB474;
extern s16 D_800EB478;
void func_800B9730(u8 *, u8 *, u32, s32);
void playEntitySound(s32, s32);
s32 func_800B8484(u32);
s8 func_800BA578(s8);
void func_800D5B74(s8, s8, u32);

typedef struct { u8 f0; s8 f1; s8 f2; s8 f3; } Rec;
#ifdef TARGET_PC
/* PC: on the big-endian N64 the first word of a u64 in memory is its upper half; on a little-endian PC (port.h checks
 * that the CPU is one) it is the lower half. With the words named in memory order, w.hi would read the lower half, so
 * for mask 0x2000 the test hi == 0 would fail and mode would never be set. The PC names them the other way round, so
 * hi and lo are the same halves of v as on the N64. */
typedef union { u64 v; struct { u32 lo; u32 hi; } w; } U64;
#else
typedef union { u64 v; struct { u32 hi; u32 lo; } w; } U64;
#endif

s8 func_800B955C(u64 mask) {
    U64 m;
    s32 mode;
    s16 i;
    u64 flags;
    Rec r0;
    Rec r1;

    m.v = mask;
    if (m.w.hi == 0) {
        if (m.w.lo == 0x2000) {
            mode = 0x8000;
        }
        if (m.w.lo == 0x1000) {
            mode = 0x1000;
        }
        if (m.w.lo == 0x800) {
            mode = 0x10000;
        }
    }
    for (i = 0; i < 4; i++) {
        flags = D_800F9D10[i].flags;
        if (flags & m.v) {
            D_800F9D10[i].flags = flags & ~m.v;
            r0.f0 = D_800F9D10[i].heldById;
            r0.f1 = -1;
            r1.f0 = (s8)i;
            r1.f1 = -1;
            r1.f2 = -1;
            if (mode == 0x10000) {
                if (D_800EB478 < D_800EB474) {
                    func_800B9730(&r0, &r1, 0x10000, 1);
                    playEntitySound(0, 2);
                } else {
                    return func_800B8484(0x10000);
                }
            } else if (func_800BA578((s8)i)) {
                func_800B9730(&r0, &r1, mode | 0x100000, 1);
                func_800D5B74((s8)r0.f0, (s8)r1.f0, mode);
                return 1;
            } else {
                func_800B9730(&r0, &r1, mode, 1);
            }
        }
    }
    return 0;
}
