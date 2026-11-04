/* @header
 * func_800B0F08
 * VRAM 0x800B0F08 | ROM 0x5D678 | size 0x2B4
 * asm: asm/nonmatchings/code_80090000/func_800B0F08.s
 */
#include "common.h"

extern struct { u8 pad[8]; u16 b; u8 p0[0x26]; u8 *p; u8 p1[0x118]; u8 m; u8 n; u16 x[5]; u16 y2; u16 z[5]; u16 w; u8 p2[0xB2A]; u16 q[4]; } D_8007EF30;
extern struct { u8 pad[0x688]; s32 a, b, c, d; } D_8007E228;
extern struct { u8 pad[0x70]; s32 a, b, c, d; } D_8007E8C0;
s32 func_8002B710(s32);
void func_800B9F18(void);

static inline s32 chk(s32 key) {
    s32 v = func_8002B710(key);
    if (v != 0 && !((D_8007EF30.m >> (v - 1)) & 1)) {
        D_8007EF30.m |= 1 << (v - 1);
        return 1;
    }
    return 0;
}

s32 func_800B0F08(void) {
    u8 n = 0;
    /* Placeholder: an if/else that only cse1 can fold (n is known 0 there). It ends cse1's block, so
       the later field accesses are related to the D_8007EF30+0x14D address in cse2 (base a2) instead of
       being folded back to symbols; a do { } while (0) does the same but adds a sched barrier. */
    if (n == 0) {
        D_8007EF30.n |= 1 << *D_8007EF30.p;
    } else {
        D_8007EF30.n = 0;
    }
    if (D_8007EF30.b & 0x20) {
        D_8007EF30.x[*D_8007EF30.p] = D_8007E228.a | ((D_8007E8C0.a & 3) << 12);
        D_8007EF30.y2 = D_8007E228.b | ((D_8007E8C0.b & 3) << 12);
        D_8007EF30.z[*D_8007EF30.p] = D_8007E228.c | ((D_8007E8C0.c & 3) << 12);
        D_8007EF30.w = D_8007E228.d | ((D_8007E8C0.d & 3) << 12);
        if (chk(D_8007E228.c)) {
            D_8007EF30.q[n] = D_8007E228.c;
            n++;
        }
        if (chk(D_8007E228.d)) {
            D_8007EF30.q[n] = D_8007E228.d;
            n++;
        }
    } else {
        D_8007EF30.x[*D_8007EF30.p] = D_8007E228.a | ((D_8007E8C0.a & 3) << 12);
        D_8007EF30.z[*D_8007EF30.p] = D_8007E228.b | ((D_8007E8C0.b & 3) << 12);
        if (chk(D_8007E228.b)) {
            D_8007EF30.q[n] = D_8007E228.b;
            n++;
        }
    }
    func_800B9F18();
    return n;
}
