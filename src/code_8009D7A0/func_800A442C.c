#include "common.h"

extern void *D_800EB408;
extern void *D_800EB40C;
s32 func_800D2BEC(void *,void *,void *,f32,u16,s32);
void func_800A7D1C(void *, s32);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800A6C48(void *, s32);
void func_800B68A0(void *, void *, void *);
void func_800D427C(void *,s16,s32);
void func_800D4AD0(void *);
void func_800D7E80(void *, void *);
void func_800D8D74(void *, s32);
void func_800E2090(void *, void *);

/* Paired-action state machine between the D_800EB408 action object and its
 * target D_800EB40C, driven by the object's s16 state at +0xC:
 *   first runs boundary correction (range 4.0), then
 *   0: choose an animation from the +0x3A flag bits, kick it off, advance;
 *   1: once the timer +4 expires, re-select an animation and advance;
 *   2: once the timer expires, start the grab reaction and clear flag 0x40000000. */
void func_800A442C(void) {
    s16 anim;
    u16 flags;
    u64 fl;
    u8 *o;
    func_800D2BEC(D_800EB408, D_800EB40C, 0, 4.0f, 0, 0xFFFFE);
    flags = *(u16 *)((u8 *)D_800EB408 + 0x3A);
    switch (((Nw2F408 *)D_800EB408)->fC) {
    case 0:
        if (flags & 0x2200) anim = 0x101B;
        if (flags & 0x400) anim = 0x1008;
        if (flags & 0x4800) anim = 0x101F;
        if (flags & 0x1000) anim = 0x1010;
        func_800D427C(D_800EB408, anim, 2);
        func_800D7E80(D_800EB408, D_800EB40C);
        func_800A7F6C(D_800EB408, (-((*(u16 *)((u8 *)D_800EB408 + 0x3A) & 0x6000) != 0) & 0x27) | 0x26);
        func_800A837C(D_800EB408);
        ((Nw2F408 *)D_800EB408)->fC++;
        /* fallthrough */
    case 1:
        func_800D8D74(D_800EB408, 0);
        if (((Nw2F408 *)D_800EB408)->f4 <= 0) {
            func_800E2090(D_800EB408, D_800EB40C);
            if (flags & 0x2200) anim = 0x101D;
            if (flags & 0x400) anim = 0x1017;
            if (flags & 0x4800) anim = 0x1021;
            if (flags & 0x1000) anim = 0x1019;
            func_800D427C(D_800EB408, anim, 0);
            ((Nw2F408 *)D_800EB408)->fC++;
        }
        break;
    case 2:
        if (((Nw2F408 *)D_800EB408)->f4 <= 0) {
            s8 grabbed = -1;
            func_800A7D1C(D_800EB408, 0x1A);
            func_800B68A0(D_800EB408, D_800EB408, D_800EB40C);
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
            o = D_800EB408;
            fl = *(u64 *)(o + 0x20);
            *((s8 *)o + 0x362) = grabbed;
            fl &= 0xFFFFFFFFBFFFFFFFULL;
            *(u64 *)(o + 0x20) = fl;
        }
        break;
    }
}
