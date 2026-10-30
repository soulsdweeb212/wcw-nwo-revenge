#include "common.h"

typedef struct {
    s8 f0;
    u8 pad1[9];
    s16 fA;
    s16 fC;
    u8 padE[8];
    s16 f16;
    u8 pad18[8];
    u64 flags;
    u8 pad28[4];
    s32 f2C;
    s32 f30;
    u8 pad34[8];
    s16 f3C;
    s16 f3E;
    u8 pad40[0xC];
    f32 f4C;
    f32 f50;
    f32 f54;
    s32 f58;
    u8 pad5C[0x10];
    f32 f6C;
    f32 f70;
    f32 f74;
    u8 pad78[0x2C4];
    u8 f33C[0xC];
    s32 f348;
    u8 pad34C[0x20];
    u8 f36C;
    u8 pad36D[0x36];
    u8 f3A3;
    u8 pad3A4[8];
    s32 f3AC;
} E7E80;

extern f32 D_800E3C50[];
extern f32 D_800E3C54[];
extern s32 D_800E3C90[];
extern s32 D_800E3CA0[];
extern s32 D_800E3CB0[];
extern s32 D_800E3CC0[];
extern f64 D_800E6FC8, D_800E6FD0, D_800E6FD8, D_800E6FE0;
extern u16 D_800FAF8E[];

void func_800A7328(E7E80 *);
s32 func_800D35B0(s32, s32);
s32 func_800D3940(f32 *, f32 *);
void func_800D3E40(f32 *, f32 *, s32, f32 *);
void func_800D3838(void *, void *, s16, void *);

void func_800D7E80(E7E80 *e, E7E80 *o)
{
    f32 a[3];
    f32 b[3];
    f32 c[3];
    s32 ang;
    s16 n;
    s32 ang2;
    s16 calc;

    calc = 1;
    switch (e->fA) {
    case 10:
        b[0] = 0.0f;
        b[2] = 73.539108f;
        a[0] = D_800E3C50[e->f3E * 2];
        a[2] = D_800E3C54[e->f3E * 2];
        n = 8;
        ang = D_800E3CB0[e->f3E];
        ang2 = D_800E3CC0[e->f3E];
        break;
    case 123:
        b[0] = 0.0f;
        b[2] = 91.923881f;
        a[0] = D_800E3C50[e->f3E * 2];
        a[2] = D_800E3C54[e->f3E * 2];
        n = 10;
        ang = D_800E3CB0[e->f3E];
        ang2 = D_800E3CC0[e->f3E];
        break;
    case 124:
        calc = 0;
        n = 6;
        if (o->f2C & 0x40) {
            ang = D_800E3CB0[e->f3E];
            switch (e->f3E) {
            case 0:
                c[0] = 229.15f;
                c[2] = 229.15f;
                break;
            case 1:
                c[0] = 229.15f;
                c[2] = -229.15f;
                break;
            case 2:
                c[0] = -229.15f;
                c[2] = -229.15f;
                break;
            case 3:
                c[0] = -229.15f;
                c[2] = 229.15f;
                break;
            }
        } else {
            ang = D_800E3CC0[e->f3E];
            switch (e->f3E) {
            case 0:
                c[0] = 230.85f;
                c[2] = 230.85f;
                break;
            case 1:
                c[0] = 230.85f;
                c[2] = -230.85f;
                break;
            case 2:
                c[0] = -230.85f;
                c[2] = -230.85f;
                break;
            case 3:
                c[0] = -230.85f;
                c[2] = 230.85f;
                break;
            }
        }
        break;
    case 80:
        b[0] = 0.0f;
        b[2] = 80.0f;
        a[0] = o->f6C;
        a[2] = o->f74;
        n = 6;
        ang = func_800D35B0(o->f58, 0x800);
        ang2 = o->f58;
        break;
    case 125:
        ang = D_800E3C90[(s16)(e->f3E & ~0x2000)];
        c[0] = e->f6C;
        c[2] = e->f74;
        calc = 0;
        n = 6;
        if (e->f3E & 0x2000) {
            switch ((s16)(e->f3E & ~0x2000)) {
            case 1:
                c[0] = 119.0f;
                break;
            case 3:
                c[0] = -119.0f;
                break;
            }
        } else {
            switch ((s16)(e->f3E & ~0x2000)) {
            case 0:
                c[2] = 473.0f;
                break;
            case 1:
                c[0] = 473.0f;
                break;
            case 2:
                c[2] = -473.0f;
                break;
            case 3:
                c[0] = -473.0f;
                break;
            }
        }
        break;
    case 89:
        b[0] = 0.0f;
        b[2] = 100.0f;
        a[0] = o->f4C;
        a[2] = o->f54;
        n = 6;
        ang = func_800D35B0(o->f58, 0x800);
        ang2 = o->f58;
        break;
    case 100:
        ang = D_800E3C90[e->f3E];
        c[0] = e->f6C;
        c[2] = e->f74;
        calc = 0;
        n = 7;
        switch (e->f3E) {
        case 0:
            c[2] = 183.0f;
            break;
        case 1:
            c[0] = 183.0f;
            break;
        case 2:
            c[2] = -183.0f;
            break;
        case 3:
            c[0] = -183.0f;
            break;
        }
        break;
    case 101:
        ang = D_800E3C90[e->f3E];
        c[0] = e->f6C;
        c[2] = e->f74;
        calc = 0;
        n = 7;
        switch (e->f3E) {
        case 0:
            c[2] = 180.0f;
            break;
        case 1:
            c[0] = 180.0f;
            break;
        case 2:
            c[2] = -180.0f;
            break;
        case 3:
            c[0] = -180.0f;
            break;
        }
        break;
    case 102:
        b[0] = 0.0f;
        b[2] = 70.710678f;
        a[0] = D_800E3C50[e->f3E * 2];
        a[2] = D_800E3C54[e->f3E * 2];
        n = 7;
        ang = D_800E3CB0[e->f3E];
        ang2 = D_800E3CC0[e->f3E];
        break;
    case 75:
        b[0] = 0.0f;
        b[2] = 130.0f;
        a[0] = o->f6C;
        a[2] = o->f74;
        n = 6;
        ang = func_800D35B0(o->f58, 0x800);
        ang2 = o->f58;
        break;
    case 76:
        b[0] = 0.0f;
        if (e->f3A3 >= 0x99 && e->f3A3 <= 0xA6) {
            b[2] = 100.0f;
        }
        if (e->f3A3 != 0 && e->f3A3 < 0x3B) {
            b[2] = 73.5f;
        }
        if (e->f3A3 >= 0x3D && e->f3A3 <= 0x45) {
            b[2] = 53.5f;
        }
        a[0] = o->f6C;
        a[2] = o->f74;
        n = 6;
        ang = func_800D35B0(o->f58, 0x800);
        ang2 = o->f58;
        break;
    case 98:
        calc = 0;
        n = 6;
        if (e->f30 & 0x1000) {
            ang = D_800E3C90[e->f3E];
        } else {
            ang = D_800E3CA0[e->f3E];
        }
        c[0] = e->f6C;
        c[2] = e->f74;
        switch (e->f3E) {
        case 0:
            c[2] = 174.0f;
            break;
        case 1:
            c[0] = 174.0f;
            break;
        case 2:
            c[2] = -174.0f;
            break;
        case 3:
            c[0] = -174.0f;
            break;
        }
        break;
    case 96:
        ang = D_800E3C90[e->f3E];
        c[0] = e->f6C;
        c[2] = e->f74;
        calc = 0;
        n = 6;
        switch (e->f3E) {
        case 0:
            c[2] = 173.0f;
            break;
        case 1:
            c[0] = 173.0f;
            break;
        case 2:
            c[2] = -173.0f;
            break;
        case 3:
            c[0] = -173.0f;
            break;
        }
        break;
    case 97:
        ang = D_800E3CA0[e->f3E];
        c[0] = e->f6C;
        c[2] = e->f74;
        calc = 0;
        n = 6;
        switch (e->f3E) {
        case 0:
            c[2] = 335.0f;
            break;
        case 1:
            c[0] = 335.0f;
            break;
        case 2:
            c[2] = -335.0f;
            break;
        case 3:
            c[0] = -335.0f;
            break;
        }
        break;
    case 13: case 15:
        n = e->f36C;
        ang = e->f58;
        c[0] = e->f6C;
        c[2] = e->f74;
        calc = 0;
        switch (e->f3E) {
        case 0:
        case 2:
            if ((D_800FAF8E[e->f0] & 0x200) && e->f6C < D_800E6FC8) {
                c[0] = -125.0f;
            }
            if ((D_800FAF8E[e->f0] & 0x100) && D_800E6FD0 < e->f6C) {
                c[0] = 125.0f;
            }
            break;
        case 1:
        case 3:
            if ((D_800FAF8E[e->f0] & 0x400) && e->f74 < D_800E6FD8) {
                c[2] = -125.0f;
            }
            if ((D_800FAF8E[e->f0] & 0x800) && D_800E6FE0 < e->f74) {
                c[2] = 125.0f;
            }
            break;
        }
        break;
    case 128:
        if (e->fC < 2) {
            b[0] = 0.0f;
            b[2] = 80.0f;
            a[0] = o->f6C;
            a[2] = o->f74;
            ang = func_800D35B0(D_800E3CA0[o->f3C], 0x800);
            n = 8;
            ang2 = D_800E3CA0[o->f3C];
        } else {
            b[0] = 0.0f;
            b[2] = 80.0f;
            a[0] = o->f6C;
            a[2] = o->f74;
            n = 8;
            ang = D_800E3CB0[o->f3E];
            ang2 = D_800E3CC0[o->f3E];
        }
        break;
    case 90:
        b[0] = 0.0f;
        b[2] = 100.0f;
        a[0] = o->f6C;
        a[2] = o->f74;
        n = 6;
        ang = func_800D35B0(o->f58, 0x800);
        ang2 = o->f58;
        break;
    case 115:
        b[0] = 0.0f;
        b[2] = 73.0f;
        a[0] = o->f4C;
        a[2] = o->f54;
        ang = o->f58;
        n = 6;
        ang2 = ang;
        break;
    case 134:
        if (e->flags & 0x40) {
            ang = D_800E3C90[e->f3E];
            c[0] = e->f6C;
            c[2] = e->f74;
            calc = 0;
            n = 6;
            switch (e->f3E) {
            case 0:
                c[2] = 150.0f;
                break;
            case 1:
                c[0] = 150.0f;
                break;
            case 2:
                c[2] = -150.0f;
                break;
            case 3:
                c[0] = -150.0f;
                break;
            }
        } else {
            calc = 0;
            ang = D_800E3C90[e->f3E];
            c[0] = e->f6C;
            c[2] = e->f74;
            n = 6;
            switch (e->f3E) {
            case 0:
                c[2] = -335.0f;
                break;
            case 1:
                c[0] = -335.0f;
                break;
            case 2:
                c[2] = 335.0f;
                break;
            case 3:
                c[0] = 335.0f;
                break;
            }
        }
        break;
    case 24:
        b[0] = 0.0f;
        b[2] = 73.539108f;
        a[0] = D_800E3C50[e->f3E * 2];
        a[2] = D_800E3C54[e->f3E * 2];
        ang2 = D_800E3CC0[e->f3E];
        n = 8;
        if (e->f3AC & 0x18) {
            ang = ang2;
        } else {
            ang = D_800E3CB0[e->f3E];
        }
        break;
    case 52:
        b[0] = 0.0f;
        b[2] = 40.0f;
        a[0] = o->f4C;
        a[2] = o->f54;
        n = 8;
        ang = func_800D35B0(o->f58, 0x800);
        ang2 = o->f58;
        break;
    case 93:
        c[0] = e->f6C;
        calc = 0;
        n = 6;
        c[2] = e->f74;
        ang = func_800D3940(&e->f6C, &o->f6C);
        break;
    case 94:
        b[0] = 0.0f;
        b[2] = 100.0f;
        a[0] = o->f4C;
        a[2] = o->f54;
        ang2 = func_800D3940(&o->f6C, &e->f6C);
        n = 6;
        ang = func_800D35B0(ang2, 0x800);
        break;
    }
    func_800A7328(e);
    if (calc) {
        func_800D3E40(a, b, ang2, c);
    }
    func_800D3838(&e->f4C, c, n, e->f33C);
    e->f348 = func_800D3684(ang, e->f58) / n;
    e->f16 = n;
}
