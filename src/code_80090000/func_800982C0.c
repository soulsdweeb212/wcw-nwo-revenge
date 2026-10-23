#include "common.h"

typedef struct {
    u8 pad0[4];
    void *f4;
    u8 pad8[4];
    s16 fC;
    s16 fE;
    s16 f10;
} Nw2PaletteRec;

typedef union {
    Nw2GfxCommand *p;
    f64 d;
} Nw2Out;

void *func_800B600C(s32, s32);
void appendPaletteSetupDisplayList(s32 *);
void buildTiledTextureDisplayList(u32 **, void *, s32, s32, s32, s32, s32, s32, s32, s32);
extern u32 D_C95F0;
extern u32 D_C95B8;

void func_800982C0(u32 **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6)
{
    Nw2PaletteRec *rec;
    Nw2GfxCommand *g;
    Nw2Out out;
    Nw2GfxCommand **pdl;
    s32 temp_a3, temp_t5, temp_a0;
    void *temp_a1;
    s32 t0, a2, t1, t2, t3, t4, t6;

    g = (Nw2GfxCommand *)*arg0;
    rec = func_800B600C(arg1, (arg5 & 0xFFFF) | 8);
    if (rec != NULL) {
        { Nw2GfxCommand *q = g++; q->w0 = 0xDE000000; q->w1 = (u32)&D_C95F0; }
        { Nw2GfxCommand *q = g++; q->w0 = 0xDE000000; q->w1 = (u32)&D_C95B8; }
        appendPaletteSetupDisplayList((s32 *)&g);
        t6 = arg3;
        out.p = g;
        pdl = &g;
        temp_a3 = rec->f10;
        temp_a1 = rec->f4;
        temp_t5 = rec->fC;
        temp_a0 = rec->fE;
        if (arg5 & 0x8000) {
            t0 = (temp_a3 * 0x1E0) / 320;
        } else {
            t0 = temp_a3;
        }
        a2 = temp_a0 * 2;
        if (arg6 & 0x10) {
            t0 *= 2;
        } else {
            a2 = temp_a0;
        }
        if (t0 >= 0x196) {
            a2 = (a2 * 0x195) / t0;
            t0 = 0x195;
        }
        if (arg6 & 0x200) {
            t3 = (temp_a0 * arg4) / 255;
            t2 = (a2 * t3) / temp_a0;
            t1 = temp_t5;
            t4 = t0;
            t6 += a2 - t2;
        } else {
            t1 = (temp_t5 * arg4) / 255;
            t3 = temp_a0;
            t2 = a2;
            t4 = (t0 * t1) / temp_t5;
        }
        if (t1 == 0 || t3 == 0 || t4 == 0 || t2 == 0) goto Ldl;
        buildTiledTextureDisplayList((u32 **)&out, temp_a1, 0, arg2 - (t0 / 2), t6 - (a2 / 2), t1, t3, t4, t2, temp_t5);
        *pdl = out.p;
    Ldl:
        { Nw2GfxCommand *q = g++; q->w0 = 0xDE000000; q->w1 = (u32)&D_C9620; }
        *arg0 = (u32 *)g;
    }
}
