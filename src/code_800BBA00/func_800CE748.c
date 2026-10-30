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
extern u8 D_800F9D10[];
extern u8 D_800F9D30[];
extern u8 D_800F9D6C[];
extern u8 D_800F9D7C[];
typedef struct {
    f32 v[4];
} Nw2Vec4_800CE748;
#define V4(p) (*(Nw2Vec4_800CE748 *)(p))

s32 func_800CE748(u8 *ent)
{
    s8 buf[8];
    Nw2Vec4_800CE748 a;
    Nw2Vec4_800CE748 b;
    Nw2DirectionResult dir;
    s16 s3;
    s32 s0;
    int s1;
    u8 c;
    f32 fs;
    u8 *rec;
    u8 *r2;

    if (*(s16 *)(ent + 6) >= *(u8 *)(ent + 0x370) && *(u8 *)(ent + 0x371) >= *(s16 *)(ent + 6)) {
    s3 = 0;
    func_800C357C(ent, 0, buf);
    if (*(u32 *)(ent + 0x2C) & 4) {
        while (buf[s3] != -1) {
            s0 = buf[s3];
            rec = D_800F9D6C + s0 * 0x3B0;
            if (func_800D3B24(ent + 0x6C, rec + 0x10, 90.0f, &dir)) {
                if (func_800D3550(func_800D3684(*(s32 *)(ent + 0x58), dir.angle)) < 0xE3) {
                    return s0;
                }
            }
            s3++;
        }
        return -1;
    }
    a = V4(ent + 0xEC);
    b = V4(ent + 0x16C);
    while (buf[s3] != -1) {
        c = buf[s3];
        if (*(u64 *)(ent + 0x20) & 0x100ULL) {
            r2 = D_800F9D30 + (s8)c * 0x3B0;
            if (*(u64 *)r2 & 0x40ULL) {
                a = V4(ent + (u32)0x16C);
                b = V4(ent + 0x18C);
                fs = 45.0f;
                goto test;
            }
        }
        if (*(u32 *)(ent + 0x2C) & 0x10) {
            a = V4(ent + 0x16C);
            b = V4(ent + 0x17C);
            fs = 35.0f;
        } else {
            register s0 = (s8)c;
            if (func_800CEAE0(ent, D_800F9D10 + s0 * 0x3B0, c)) {
                return s0;
            }
            ++s3;
            continue;
        }
test:
        s1 = (s8)c;
        if (func_800D3B24(&a, D_800F9D7C + s1 * 0x3B0, fs, 0)) {
            return s1;
        }
        if (func_800D3B24(&b, D_800F9D7C + s1 * 0x3B0, fs, 0)) {
            return s1;
        }
        s3++;
    }
    }
    return -1;
}
