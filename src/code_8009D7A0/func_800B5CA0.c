#include "common.h"

f32 func_800D3EEC(void *, void *, s32);
void func_800E212C(void *);
void func_800A6C48(void *, s32);
extern f64 D_800E54D8;
extern s32 D_800F9B14;

/* p: attacker  -- +0x20 u64 flags, +0x58 s32 heading, +0x6C f32[3] position
 * q: target    -- +0x20 u64 flags, +0x4C f32[3] position, +0x58 s32 heading
 *
 * If p may attack (flags & 0x4000) and p and q agree on an attack or pain flag
 * while q is in a vulnerable state, check whether p is within q's reach (3D
 * distance below reach + epsilon) and within facing range; if so issue command
 * 0x56 and the hit reaction, returning 1. Otherwise 0. */
s32 func_800B5CA0(u8 *p, u8 *q, s32 flags, f32 distance) {
    u64 common;
    if (flags & 0x4000) {
        common = *(u64 *)(p + 0x20) & *(u64 *)(q + 0x20);
        if (((common & 0x40) || (common & 0x100)) && (*(u64 *)(q + 0x20) & 0x400000) &&
            ((f64)distance < (f64)func_800D3EEC(q + 0x4C, p + 0x6C, *(s32 *)(q + 0x58)) + D_800E54D8)) {
            if (func_800D3550(func_800D3684(D_800F9B14, *(s32 *)(p + 0x58))) < 0x200) {
                func_800A6C48(p, 0x56);
                func_800E212C(p);
                return 1;
            }
        }
    }
    return 0;
}
