/* @header
 * func_80018CC4
 * VRAM 0x80018CC4 | ROM 0x198C4 | size 0x220
 * asm: asm/nonmatchings/main/func_80018CC4.s
 */
#include "common.h"

typedef struct {
    u8 pad0[0x54];
    unsigned f54;
    s16 f58;
    s16 f5A;
    s16 f5C;
    s16 f5E;
    u16 f60;
    u16 f62;
    u16 f64;
    u16 f66;
    u16 f68;
    u16 f6A;
    u16 f6C;
    u16 f6E;
    s32 f70;
    unsigned int f74;
    unsigned f78;
    u8 pad7C[8];
    s32 f84;
} Nw2Obj18CC4;

typedef struct {
    long w0;
    u32 w1;
} Nw2Gfx18CC4;

u16 computeFixedPointStepRate(f64, f64, s32, u16 *);
Nw2Gfx18CC4 *func_80019790(void *, u16 *, void *, s32);
s32 func_8001CE80(s32);
extern s16 D_800370F0[];

#define RNUDGE(p) (Nw2Gfx18CC4 *)((u32)(p) | ((u32)(p) & ~(u32)(p)))

void *func_80018CC4(Nw2Obj18CC4 *obj, u16 *cmd, s32 arg2, s32 flag, Nw2Gfx18CC4 *out) {
    Nw2Gfx18CC4 *g;
    Nw2Gfx18CC4 *last;
    Nw2Gfx18CC4 *p;
    s32 v;
    long vol;
    Nw2Obj18CC4 *o;

    o = obj;
    g = out;
    if ((o->f84 != 1) | (flag == 0)) {
        return g;
    }
    g = func_80019790(o, cmd, g, flag == 0);
    if (o->f78 != 0) {
        o->f78 = 0;
        v = (s32)(o->f5A * D_800370F0[o->f58]) >> 15;
        o->f68 = v;
        vol = o->f74;
        o->f66 = computeFixedPointStepRate((f64)o->f5C, (f64)(s16)v, vol, &o->f64);
        v = (s32)(o->f5A * D_800370F0[0x7F - o->f58]) >> 15;
        vol = o->f74;
        o->f6E = v;
        *(volatile u16 *)&o->f6C = computeFixedPointStepRate((f64)o->f5E, (f64)(s16)v, vol, &o->f6A);
        p = g++;
        p->w0 = *(volatile u16 *)&o->f68 | 0x09000000;
        p->w1 = (o->f66 << 16) | o->f64;
        p = g++;
        p->w0 = (u16)o->f5C | 0x09060000;
        p->w1 = (o->f60 << 16) | o->f62;
        p = g++;
        p->w0 = o->f6E | 0x09040000;
        p->w1 = (o->f6C << 16) | o->f6A;
        last = g;
        last = RNUDGE(last);
        last = RNUDGE(last);
        last = RNUDGE(last);
        last = RNUDGE(last);
        last = RNUDGE(last);
        last->w0 = (u16)o->f5E | 0x03010000;
    } else {
        last = g;
        last = RNUDGE(last);
        last = RNUDGE(last);
        last = RNUDGE(last);
        last = RNUDGE(last);
        last = RNUDGE(last);
        last->w0 = 0x03000000;
    }
    g++;
    last->w1 = func_8001CE80(o->f54);
    *cmd += 0x170;
    o->f70 += 0xB8;
    return g;
}
