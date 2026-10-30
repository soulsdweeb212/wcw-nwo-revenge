/* @header
 * func_800B4C60
 * VRAM 0x800B4C60 | ROM 0xA8100 | size 0x6E0
 * asm: asm/nonmatchings/code_8009D7A0/func_800B4C60.s
 */
#include "common.h"

typedef struct {
    s32 f0;
    s16 f4;
    s16 f6;
    s32 f8;
    s16 fC;
    s16 fE;
    u8 pad10[0x10];
    u64 flags;
    u32 f28;
    u32 f2C;
    s32 f30;
    u8 pad34[8];
    u16 f3C;
    s16 f3E;
    u8 pad40[0x18];
    s32 f58;
    u8 pad5C[0x10];
    f32 f6C;
    u8 pad70[0x2CC];
    f32 vec[3];
    u8 pad348[0xB];
    s8 f353;
    u8 pad354[0xC];
} Ent4C60;

typedef struct { f32 x, z; } XZ4C60;
typedef struct { u8 pad[0x3B0]; } Big4C60;

extern u8 D_8007FC10;
extern s32 D_800E37A0[];
extern s32 D_800E37A8[];
extern XZ4C60 D_800E37B0[];
extern u16 D_800E3CF0[];
extern f64 D_800E54A8;
extern f64 D_800E54B0;
extern f64 D_800E54B8;
extern f64 D_800E54C0;
extern Big4C60 D_800F9D10[];

void func_800A7F6C(void *, s32);
void func_800A837C(void *);
s8 func_800A93C0(void);
s8 startEntityGrapple(void *, s16, u16);
s8 func_800C2634(void *, u16);
u32 func_800D2B64(void *, f32, s32, s32);
s16 findBoundaryQuadrant(void *, s32, s32);
s16 func_800D3638(s32);
s8 func_800D3B24(f32 *, f32 *, f32, s32);
s16 func_800D65D0(void *, u16);
s16 func_800D7A2C(u16);
s8 func_800DF924(void *, void *);
s8 func_800E07DC(void *);
void translateEntityXZ(void *, f32 *);

s32 func_800B4C60(Ent4C60 *o, void *other, u16 inputFlags, s16 mode) {
    f32 vec[3];
    u32 res;
    s16 i;
    u16 fl;
    s16 q;
    s32 st;

    translateEntityXZ(o, o->vec);
    if (startEntityGrapple(o, mode, inputFlags)) {
        return 1;
    }
    if (func_800A93C0()) {
        goto L5304;
    }
    res = func_800D2B64(o, 1.0f, 0, 2);
    if (res != 0) {
    if (mode == 1) {
        fl = *(u16 *)&o->f28;
        if (fl & 2) {
            if (fl & 0x20) {
                if (o->flags & 0x100) {
                    if (res & 0xFFFF) {
                        for (i = 0; i < 4; i++) {
                            vec[0] = D_800E37B0[i].x;
                            vec[2] = D_800E37B0[i].z;
                            if (func_800D3B24(&o->f6C, vec, 55.0f, 0)) {
                                func_800A6C48(o, 0x13);
                                return 1;
                            }
                        }
                        o->f3E = func_800D7A2C(res);
                        func_800A6C48(o, 0x11);
                        return 1;
                    }
                    res >>= 16;
                    o->f3E = func_800D7A2C(res);
                    if (res & 0x2000) {
                        if ((res & 0xF00) == 0x800) {
                            if (func_800D3550(func_800D3684(0, o->f58)) < 0x2AA) {
                                if ((D_8007FC10 == 2 && o->f6C > D_800E54A8 && o->f6C < D_800E54B0) ||
                                    (D_8007FC10 == 0 && o->f6C > D_800E54B8 && o->f6C < D_800E54C0)) {
                                    func_800A6C48(o, 0x8D);
                                    return 1;
                                }
                            }
                        }
                    }
                    if (res & D_800E3CF0[func_800D3638(o->f58)]) {
                        func_800A6C48(o, 0x12);
                        return 1;
                    }
                    return 0;
                }
                if (res & D_800E37A0[o->f3E & 1]) {
                    if (fl & 0x80) {
                        if (fl & 0x100) {
                            o->f30 = 0x1000;
                            if (o->f6 < 0x14 && func_800C2634(o, res)) {
                                func_800A6C48(o, 0x62);
                                return 1;
                            }
                        }
                        func_800A6C48(o, 4);
                        return 1;
                    }
                    func_800A6C48(o, 4);
                    return 1;
                }
            } else {
                if (fl & 0x10) {
                    goto L5304;
                }
                if (res & D_800E37A0[o->f3E & 1]) {
                    if (o->flags & 0x40) {
                        func_800A6C48(o, 4);
                        return 1;
                    }
                    if (o->flags & 0x80) {
                        if (func_800DF924(o, &D_800F9D10[o->f353]) && (inputFlags & 4)) {
                            q = o->f3C;
                            o->flags &= ~0x8000000000ULL;
                            if (func_800D65D0(o, res) == mode) {
                                o->flags |= 0x8000000000ULL;
                                q = (q - 1) & 3;
                            }
                            o->f3E = q;
                            if (func_800E07DC(o)) {
                                func_800A6C48(o, 0xA);
                                return 1;
                            }
                        }
                        goto L5304;
                    }
                    if (o->flags & 0x100) {
                        goto L5304;
                    }
                }
            }
        }
        if ((o->f28 & 0xE0000) == 0x40000) {
            for (i = 0; i < 2; i++) {
                if ((res & D_800E37A0[i]) &&
                    (u32)(func_800D3550(func_800D3684(o->f58, D_800E37A8[i])) - 0x17) < 0x7D3) {
                    goto L5304;
                }
            }
        }
    }
    }
    if ((o->f28 & 0x280000) == 0x80000) {
        q = findBoundaryQuadrant(o, 0, 2);
        if (q != -1 && q == o->f3E && (inputFlags & 4) && func_800E07DC(o)) {
            if (func_800DF924(o, other)) {
                func_800A6C48(o, 0xA);
                o->fC = 1;
                return 1;
            }
            if (!(o->flags & 1)) {
                func_800A6C48(o, 0x18);
                return 1;
            }
        }
    }
    if (*(u16 *)&o->f28 & 8) {
        s16 q2;
        do {
            q2 = findBoundaryQuadrant(o, 0, 0);
        } while (0);
        if (q2 == -1) {
            return 0;
        }
        if (*(u16 *)&o->f28 & 0xA0) {
            o->f3E = q2;
            if (*(u16 *)&o->f28 & 0x1000) {
                st = 0x15;
            } else if (*(u16 *)&o->f28 & 0x2000) {
                st = 0x16;
            } else {
                if (!func_800E07DC(o)) {
                    goto L5304;
                }
                st = 0x14;
                func_800A7F6C(other, 0x4F);
                func_800A837C(other);
            }
            func_800A6C48(o, st);
            return 1;
        }
        if (q2 == o->f3E) {
            goto L5304;
        }
    }
    return 0;
L5304:
    func_800A6C48(o, 3);
    o->fC = 3;
    return 1;
}
