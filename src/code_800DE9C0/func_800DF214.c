/* @header
 * func_800DF214
 * VRAM 0x800DF214 | ROM 0xD26B4 | size 0x1D0
 * asm: asm/nonmatchings/code_800DE9C0/func_800DF214.s
 */
#include "common.h"

/* Choose an attack direction when `flags` has bit 2 set. Derives a target angle
 * (from the wrestler's own heading or the D_800E3CFC table via func_800D7A68),
 * builds a 5.0-unit direction vector with it, then scans the other wrestler
 * slots for a valid target (shared zone flag 0x140, target flag 0x400000, not
 * 0x1000000000, and func_800D26A0 selection) whose bearing is within 0x200 of
 * the chosen angle; on a hit it stores the target in steppedOverId and queues action
 * 0x89 with func_800E212C, else it queues action 3. Always returns 1 when the
 * bit was set (0 otherwise). */
s8 func_800D26A0(void *, void *, s32);
extern s32 D_800E3CFC[]; 
s16 func_800D7A68(u16, s32); void func_800D37C0(s32, f32, void *); f32 func_800D3890(void *, void *, void *); void func_800E212C(void *);
s32 func_800DF214(Wrestler *p, s32 flags) {
    f32 vec[3]; Nw2DirectionResult dir; s16 i; s16 index; s32 angle; Wrestler *q; s32 input;
    input = flags; flags &= 4;
    if (flags) {
        index = func_800D7A68(input, flags);
        if (index == 0) angle = p->heading; else angle = D_800E3CFC[index];
        do { func_800D37C0(angle, 5.0f, vec); } while (0);
        i = 0;
        for (; i < 4; i++) {
            if (i == p->id) continue;
            if (p->steppedOverId == i) continue;
            q = &D_800F9D10[i];
            if (!(p->flags & q->flags & 0x140ULL)) continue;
            if (!(q->flags & 0x400000ULL)) continue;
            if (q->flags & 0x1000000000ULL) continue;
            if (func_800D26A0(p, (s32)vec, -1) != q->id) continue;
            func_800D3890(&p->jointA[1], &q->jointA[1], &dir);
            if (func_800D3550(func_800D3684(dir.angle, p->heading)) < 0x200) {
                p->steppedOverId = q->id; func_800A6C48(p, 0x89); func_800E212C(p); return 1;
            }
        }
        func_800A6C48(p, 3); return 1;
    }
    return 0;
}
