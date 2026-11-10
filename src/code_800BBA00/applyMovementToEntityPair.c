/* @header
 * applyMovementToEntityPair  (originally func_800D6E78)
 * VRAM 0x800D6E78 | ROM 0xCA318 | size 0x2B0
 * asm: asm/nonmatchings/code_800BBA00/applyMovementToEntityPair.s
 */
#include "common.h"

/* Moves the two sides of a paired move together. A directional XZ step selected by `flags` bits 0x800 (+Z), 0x100 (+X),
 * 0x400 (-Z), 0x200 (-X) (magnitude from func_800D63F0, scaled by D_800E6D78 = 0.7071 unless func_800D7A68(flags)
 * returns an odd direction code, i.e. for diagonals) is added to source's x/z and to jointA[1..19] / jointB[1..19].
 * After func_800D2600(source, target->id) and func_800D2B64(source) run, source's total x/z change is carried to target
 * and its joints (then func_800D2BAC(target, source)), and both headings are turned by +0x22 (flag 0x8000), -0x22
 * (0x4000) or 0 when both or neither are set. */

/* x, y, z, heading of a record, copied as one 16-byte block */
typedef struct {
    f32 x, y, z;
    s32 heading;
} Nw2Quad;

typedef struct {
    f32 x, y, z;
} Nw2Vec3f;

extern f64 D_800E6D78;

f32 func_800D63F0(void *, void *, s16);
s32 func_800D7A68(s32);
void func_800D2600(void *, s32, f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
s32 func_800D2B64(void *, f32, u16, s32);
#endif
s32 func_800D35B0(s32, s32);

void applyMovementToEntityPair(Wrestler *source, Wrestler *target, u16 flags) {
    Nw2Vec3f delta;
    Nw2Quad q;
    s16 i;
    f32 *dp;
    f32 v;

    q = *(Nw2Quad *)&source->x;

    if (flags & 0xF00) {
        delta.x = 0.0f;
        delta.z = 0.0f;
        v = func_800D63F0(source, 0, 3);
        if (flags & 0x800) {
            delta.z = v;
        }
        if (flags & 0x100) {
            delta.x = v;
        }
        if (flags & 0x400) {
            delta.z = -v;
        }
        if (flags & 0x200) {
            delta.x = -v;
        }
        if (!(func_800D7A68(flags & 0xFFFF) & 1)) {
            delta.x *= D_800E6D78;
            delta.z *= D_800E6D78;
        }
        source->x += delta.x;
        source->z += delta.z;
        dp = &delta.x;
        for (i = 1; i < 0x14; i++) {
            source->jointA[i].x += dp[0];
            source->jointA[i].z += dp[2];
            source->jointB[i].x += dp[0];
            source->jointB[i].z += dp[2];
        }
    }
    func_800D2600(source, target->id, 4.0f);
    func_800D2B64(source, 1.0f, 0, 2);
    delta.x = source->x - q.x;
    delta.z = source->z - q.z;
    target->x += delta.x;
    target->z += delta.z;
    dp = &delta.x;
    for (i = 1; i < 0x14; i++) {
        target->jointA[i].x += dp[0];
        target->jointA[i].z += dp[2];
        target->jointB[i].x += dp[0];
        target->jointB[i].z += dp[2];
    }
    func_800D2BAC(target, source, 1.0f, 2);
    {
        s32 d = -((flags & 0x8000) != 0) & 0x22;
        if (flags & 0x4000) {
            d -= 0x22;
        }
        source->heading = func_800D35B0(source->heading, d);
        target->heading = func_800D35B0(target->heading, d);
    }
}
