/* @header
 * func_800A442C
 * VRAM 0x800A442C | ROM 0x978CC | size 0x234
 * asm: asm/nonmatchings/code_8009D7A0/func_800A442C.s
 */
#include "common.h"

s32 func_800D2BEC(void *,void *,void *,f32,u16,s32);
void func_800A7D1C(void *, s32);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800B68A0(void *, void *, void *);
void func_800D427C(void *,s16,s32);
void func_800D4AD0(void *);
void func_800D7E80(void *, void *);
void func_800D8D74(void *, s32);
void func_800E2090(void *, void *);

/* Paired-action state machine between the D_800EB408 action object and its
 * target D_800EB40C, driven by step:
 *   first runs boundary correction (range 4.0), then
 *   0: choose an animation from the counterKind bits, kick it off, advance;
 *   1: once the animation ends, re-select an animation and advance;
 *   2: once it ends, start the grab reaction, clear attached[0] and flag 0x40000000. */
void func_800A442C(void) {
    s16 anim;
    u16 flags;
    u64 fl;
    Wrestler *o;
    func_800D2BEC(D_800EB408, D_800EB40C, 0, 4.0f, 0, 0xFFFFE);
    flags = D_800EB408->counterKind;
    switch (D_800EB408->step) {
    case 0:
        if (flags & 0x2200) anim = 0x101B;
        if (flags & 0x400) anim = 0x1008;
        if (flags & 0x4800) anim = 0x101F;
        if (flags & 0x1000) anim = 0x1010;
        func_800D427C(D_800EB408, anim, 2);
        func_800D7E80(D_800EB408, D_800EB40C);
        func_800A7F6C(D_800EB408, (-(((u16)D_800EB408->counterKind & 0x6000) != 0) & 0x27) | 0x26);
        func_800A837C(D_800EB408);
        D_800EB408->step++;
        /* fallthrough */
    case 1:
        func_800D8D74(D_800EB408, 0);
        if (D_800EB408->animFramesLeft <= 0) {
            func_800E2090(D_800EB408, D_800EB40C);
            if (flags & 0x2200) anim = 0x101D;
            if (flags & 0x400) anim = 0x1017;
            if (flags & 0x4800) anim = 0x1021;
            if (flags & 0x1000) anim = 0x1019;
            func_800D427C(D_800EB408, anim, 0);
            D_800EB408->step++;
        }
        break;
    case 2:
        if (D_800EB408->animFramesLeft <= 0) {
            s8 grabbed = -1;
            func_800A7D1C(D_800EB408, 0x1A);
            func_800B68A0(D_800EB408, D_800EB408, D_800EB40C);
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
            o = D_800EB408;
            fl = o->flags;
            o->attached[0] = grabbed;
            fl &= 0xFFFFFFFFBFFFFFFFULL;
            o->flags = fl;
        }
        break;
    }
}
