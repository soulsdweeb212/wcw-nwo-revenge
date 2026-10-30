/* @header
 * func_800DF214
 * VRAM 0x800DF214 | ROM 0xD26B4 | size 0x1D0
 * asm: asm/nonmatchings/code_800DE9C0/func_800DF214.s
 */
#include "common.h"

/* Choose an attack direction when `flags` has bit 2 set. Derives a target angle
 * (from the entity's own +0x58 or the D_800E3CFC table via func_800D7A68),
 * builds a 5.0-unit direction vector with it, then scans the other 4 entity
 * slots for a valid target (shared flag 0x140, target flag 0x400000, not
 * 0x1000000000, and func_800D26A0 selection) whose bearing is within 0x200 of
 * the chosen angle; on a hit it stores the target index and queues action
 * 0x89 with func_800E212C, else it queues action 3. Always returns 1 when the
 * bit was set (0 otherwise). */
s8 func_800D26A0(void *, void *, s32);
extern s32 D_800E3CFC[]; extern u8 D_800F9D10[];
s16 func_800D7A68(u16, s32); void func_800D37C0(s32, f32, void *); f32 func_800D3890(void *, void *, void *); void func_800E212C(void *);
s32 func_800DF214(u8 *p, s32 flags) {
    f32 vec[3]; Nw2DirectionResult dir; s16 i; s16 index; s32 angle; u8 *q; s32 input;
    input = flags; flags &= 4;
    if (flags) {
        index = func_800D7A68(input, flags);
        if (index == 0) angle = *(s32 *)(p + 0x58); else angle = D_800E3CFC[index];
        do { func_800D37C0(angle, 5.0f, vec); } while (0);
        i = 0;
        for (; i < 4; i++) {
            if (i == *(s8 *)p) continue;
            if (*(s8 *)(p + 0x354) == i) continue;
            q = D_800F9D10 + i * 0x3B0;
            if (!(*(u64 *)(p + 0x20) & *(u64 *)(q + 0x20) & 0x140ULL)) continue;
            if (!(*(u64 *)(q + 0x20) & 0x400000ULL)) continue;
            if (*(u64 *)(q + 0x20) & 0x1000000000ULL) continue;
            if (func_800D26A0(p, (s32)vec, -1) != *(s8 *)q) continue;
            func_800D3890(p + 0x6C, q + 0x6C, &dir);
            if (func_800D3550(func_800D3684(dir.angle, *(s32 *)(p + 0x58))) < 0x200) {
                p[0x354] = *q; func_800A6C48(p, 0x89); func_800E212C(p); return 1;
            }
        }
        func_800A6C48(p, 3); return 1;
    }
    return 0;
}
