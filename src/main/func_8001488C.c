/* @header
 * func_8001488C
 * VRAM 0x8001488C | ROM 0x1548C | size 0x4EC
 * asm: asm/nonmatchings/main/func_8001488C.s
 */
#include "common.h"

typedef u8 *(*Nw2Fn1488C)(Nw2Voice1488C *, u8 *);
extern Nw2Fn1488C D_80036E80[];
extern u8 *D_800604CC;
extern void *D_800604E0;
void func_80014D78(Nw2Voice1488C *, s32);
void func_80015068(Nw2Voice1488C *);
void func_80015468(Nw2Voice1488C *);
void func_800177D0(void *, s32);
void func_80017980(void *, s32, void *);
void func_80017AC0(void *);

void func_8001488C(Nw2Voice1488C *v, s32 idx)
{
    u8 *p;
    s32 note;
    u8 *inst;
    u8 *env;
    u8 *t;
    u8 c;
    u8 a, b;
    u16 key;
    f32 pitch;
    u8 ea;

    p = v->unk4;
    if (p != NULL) {
    loop:
        c = *p;
        if (c >= 0x80) {
            p = D_80036E80[c & 0x7F](v, p + 1);
            if (p != NULL) {
                goto loop;
            }
        }
    }
    v->unk4 = p;
    if (p == NULL) {
        goto stop;
    }
    v->unk68 = v->unk6C;
    note = *v->unk4++;
    if (v->unkF2 != 0) {
        v->unkDB = *v->unk4++;
    } else {
        v->unkDB = v->unkF3;
    }
    if (v->unkCC != 0) {
        if (v->unkD7 != 0) {
            v->unkD7 = 0;
            c = *v->unk4++;
            if (c < 0x80) {
                v->unkBA = c;
            } else {
                v->unkBA = *v->unk4++ + ((c & 0x7F) << 8);
            }
        } else {
            v->unkBA = v->unkCC;
        }
    } else {
        c = *v->unk4++;
        if (c < 0x80) {
            v->unkBA = c;
        } else {
            v->unkBA = *v->unk4++ + ((c & 0x7F) << 8);
        }
    }
    v->unkCA = 0;
    v->unkF1 = 0;
    *(u64 *)&v->unk58 = *(u64 *)&v->unk50;
    v->unkF0 = v->unkEF;
    *(u64 *)&v->unk50 += (u32)(v->unkBA << 8);
    if (note == 0x60) {
        goto rest;
    }
    inst = v->unk98;
    if (v->unkA0 != NULL) {
        u8 *tab;
        u8 ix;
        v->unkCE = v->unkA0[note * 4];
        v->unkDD = v->unkA0[note * 4 + 2] >> 1;
        tab = *(u8 **)(v->unk94 + 0x10);
        ix = v->unkA0[note * 4 + 1];
        t = (u8 *)((s32)(ix * 7) + (s32)tab);
        env = t;
        a = *t;
        if (a == 0) {
            a = 1;
        }
        v->unkDF = a;
        v->unk84 = 0x400 / a;
        v->unkE0 = env[1];
        a = env[2];
        v->unkE6 = a;
        b = env[3];
        v->unkE1 = b;
        v->unk78 = 1.0 / (f32)a * (f32)(b - v->unkE0);
        a = env[4];
        v->unkE7 = a;
        b = env[5];
        v->unkE2 = b;
        v->unk7C = 1.0 / (f32)a * (f32)(b - v->unkE1);
        a = env[6];
        v->unkE8 = a;
        v->unk80 = 1.0 / (f32)a;
        note = v->unkA0[note * 4 + 3];
    }
    if (v->unkF6 == 0) {
        func_80015068(v);
    }
    if (v->unkF4 != 0) {
        func_80015468(v);
    }
    key = v->unkCE;
    if (v->unkF7 == 0) {
        v->unk8 = (*(s32 **)(inst + 0x2C))[key];
        if (v->unkE9 != 0 && v->unkC0 != 0) {
            v->unkC0 = 0;
            func_80017980(D_800604CC + idx * 0x1C, 0, D_800604E0);
        } else {
            func_80014D78(v, idx);
        }
    }
    v->unk40 = note + (*(f32 **)(inst + 0x28))[key];
    c = v->unkD9 * (1 - v->unkDA);
    v->unk40 += (c & 0x80) ? c - 0x100 : c;
    ea = v->unkEA;
    if (ea != v->unkEC) {
        v->unkEC = ea;
        func_800177D0(D_800604CC + idx * 0x1C, (u8)(v->unkEB + (((0x80 - v->unkEB) * ea) >> 7)));
    }
    return;
rest:
    if (v->unkE3 < 4) {
        v->unkE3 = 4;
        v->unkE5 = 1;
        *(u64 *)&v->unk70 = *(u64 *)&v->unk10;
        v->unkED = v->unkE4;
    }
    return;
stop:
    if (v->unkE9 != 0) {
        v->unkE9 = 0;
        func_80017980(D_800604CC + idx * 0x1C, 0, D_800604E0);
        func_80017AC0(D_800604CC + idx * 0x1C);
    }
}
