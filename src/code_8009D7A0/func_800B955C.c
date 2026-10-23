#include "common.h"

/* Clear the flag bits `mask` from each of the 4 entity records (stride 0x3B0,
 * flag word at D_800F9D30). For every record that had any of the bits set it
 * clears them, builds two {id, -1, -1, -1} buffers (source record's byte at
 * D_800FA061, and the record index) and dispatches func_800B9730: either the
 * 0x10000 presentation path (with a sound and a possible func_800B8484
 * fallback) or the 0x100000/mode path, returning 1 on a hit. */
extern s16 D_800EB474;
extern s16 D_800EB478;
extern u8 D_800FA061[];
void func_800B9730(u8 *, u8 *, u32, s32);
void playEntitySound(s32, s32);
s32 func_800B8484(u32);
s8 func_800BA578(s8);
void func_800D5B74(s8, s8, u32);

typedef struct { u8 f0; s8 f1; s8 f2; s8 f3; } Rec;
typedef union { u64 v; struct { u32 hi; u32 lo; } w; } U64;

s8 func_800B955C(u64 mask) {
    U64 m;
    s32 mode;
    s16 i;
    s32 off = 0;
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
        off = i * 0x3B0;
        flags = *(u64 *)(D_800F9D30 + off);
        if (flags & m.v) {
            *(u64 *)(D_800F9D30 + off) = flags & ~m.v;
            r0.f0 = *(u8 *)(D_800FA061 + off);
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
