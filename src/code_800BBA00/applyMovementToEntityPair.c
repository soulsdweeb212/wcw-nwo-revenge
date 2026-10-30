/* @header
 * applyMovementToEntityPair  (originally func_800D6E78)
 * VRAM 0x800D6E78 | ROM 0xCA318 | size 0x2B0
 * asm: asm/nonmatchings/code_800BBA00/func_800D6E78.s
 */
#include "common.h"

/* Moves a paired entity: a directional XZ step selected by `flags` bits 0x100/0x200/
 * 0x400/0x800 (magnitude from func_800D63F0) is applied to `source` and its limb
 * parts; the resulting displacement is then carried to `target` and its parts, and
 * both headings are turned by the 0x4000/0x8000 offset. */
typedef struct {
    f32 x, y, z, pad;
} Nw2Part;

typedef struct {
    f32 x, y, z;
    s32 heading;
} Nw2Quad;

typedef struct {
    f32 x, y, z;
} Nw2Vec3f;

typedef struct {
    s8 id;
    u8 pad1[0x4B];
    Nw2Quad q;
    Nw2Part partA[20];
    u8 pad2[0x30];
    Nw2Part partB[20];
} Nw2Entity;

extern f64 D_800E6D78;

f32 func_800D63F0(void *, void *, s16);
s32 func_800D7A68(s32);
void func_800D2600(void *, s32, f32);
s32 func_800D2B64(void *, f32, u16, s32);
s32 func_800D2BAC(void *, void *, f32, s32);
s32 func_800D35B0(s32, s32);

void applyMovementToEntityPair(Nw2Entity *source, Nw2Entity *target, u16 flags) {
    Nw2Vec3f delta;
    Nw2Quad q;
    s16 i;
    f32 *dp;
    f32 v;

    q = source->q;

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
        source->q.x += delta.x;
        source->q.z += delta.z;
        dp = &delta.x;
        for (i = 1; i < 0x14; i++) {
            source->partA[i].x += dp[0];
            source->partA[i].z += dp[2];
            source->partB[i].x += dp[0];
            source->partB[i].z += dp[2];
        }
    }
    func_800D2600(source, target->id, 4.0f);
    func_800D2B64(source, 1.0f, 0, 2);
    delta.x = source->q.x - q.x;
    delta.z = source->q.z - q.z;
    target->q.x += delta.x;
    target->q.z += delta.z;
    dp = &delta.x;
    for (i = 1; i < 0x14; i++) {
        target->partA[i].x += dp[0];
        target->partA[i].z += dp[2];
        target->partB[i].x += dp[0];
        target->partB[i].z += dp[2];
    }
    func_800D2BAC(target, source, 1.0f, 2);
    {
        s32 d = -((flags & 0x8000) != 0) & 0x22;
        if (flags & 0x4000) {
            d -= 0x22;
        }
        source->q.heading = func_800D35B0(source->q.heading, d);
        target->q.heading = func_800D35B0(target->q.heading, d);
    }
}
