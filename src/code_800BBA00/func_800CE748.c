/* @header
 * func_800CE748
 * VRAM 0x800CE748 | ROM 0xC1BE8 | size 0x398
 * asm: asm/nonmatchings/code_800BBA00/func_800CE748.s
 */
#include "common.h"

s8 func_800D3B24(void *, void *, f32, void *);
s8 func_800CEAE0(void *, void *, u8);
s32 func_800C357C(void *, s32, void *);
s32 func_800D3684(s32, s32);
s32 func_800D3550(s32);

s32 func_800CE748(Wrestler *ent)
{
    s8 buf[8];
    WrJointPos a;
    WrJointPos b;
    Nw2DirectionResult dir;
    s16 s3;
    s32 s0;
    int s1;
    u8 c;
    f32 fs;
    WrJointPos *rec;
    u64 *r2;

    if (ent->animFrame >= ent->anim.hitStart && ent->anim.hitEnd >= ent->animFrame) {
        s3 = 0;
        func_800C357C(ent, 0, buf);
        if (ent->grappleCtx & 4) {
            while (buf[s3] != -1) {
                s0 = buf[s3];
                rec = D_800F9D10[s0].jointA;
                if (func_800D3B24(&ent->jointA[1], &rec[1], 90.0f, &dir)) {
                    if (func_800D3550(func_800D3684(ent->heading, dir.angle)) < 0xE3) {
                        return s0;
                    }
                }
                s3++;
            }
            return -1;
        }
        a = ent->jointA[9];
        b = ent->jointA[17];
        while (buf[s3] != -1) {
            c = buf[s3];
            if (ent->flags & WR_FLAG_ON_FLOOR) {
                r2 = &D_800F9D10[(s8)c].flags;
                if (*r2 & 0x40ULL) {
                    a = ent->jointA[17];
                    b = ent->jointA[19];
                    fs = 45.0f;
                    goto test;
                }
            }
            if (ent->grappleCtx & 0x10) {
                a = ent->jointA[17];
                b = ent->jointA[18];
                fs = 35.0f;
            } else {
                register s0 = (s8)c;
                if (func_800CEAE0(ent, &D_800F9D10[s0], c)) {
                    return s0;
                }
                ++s3;
                continue;
            }
test:
            s1 = (s8)c;
            if (func_800D3B24(&a, &D_800F9D10[s1].jointA[1], fs, 0)) {
                return s1;
            }
            if (func_800D3B24(&b, &D_800F9D10[s1].jointA[1], fs, 0)) {
                return s1;
            }
            s3++;
        }
    }
    return -1;
}
