#include "common.h"

typedef struct {
    u8 *str;
    s32 f4;
    s32 f8;
    s16 fC;
    s16 fE;
    s16 f10;
} Nw2Layout295B4;

s32 func_800291C0(u8 *, s32, s32, s32, s32, s32);
extern u8 D_80064AD8;

void func_800295B4(Nw2Layout295B4 *o, s32 arg1) {
    u8 *s;
    s32 a0, s2, s3, s4, s7, fp, a3;
    s32 s1;
    u8 v1;
    s32 m, t;

    switch (arg1 & 0x700) {
    case 0x100: D_80064AD8 = 0x52; break;
    case 0x200: D_80064AD8 = 0x47; break;
    case 0x300: D_80064AD8 = 0x42; break;
    case 0x400: D_80064AD8 = 0x59; break;
    case 0x500: D_80064AD8 = 0x44; break;
    default: D_80064AD8 = 0x57; break;
    }
    m = arg1 & 0x40;
    s1 = m == 0;
    s = o->str;
    a3 = (arg1 << 2) & 8;
    if (arg1 & 0x10) {
        s2 = o->f10 - a3;
    } else {
        s2 = a3;
    }
    if (arg1 & 0x20) {
        t = a3 + 1;
        s3 = (o->fE - t) * o->fC;
    } else {
        s3 = a3;
    }
    v1 = *s;
    if (v1 != 0) {
        s7 = arg1 & 0x10;
        s4 = arg1 & 0x40;
        fp = -(s4 == 0);
        do {
            a0 = 0;
            switch (v1) {
            case 0xA:
                if (s1 != 0) {
                    s2 = 0;
                    if (s7 != 0) {
                        s2 = o->f10;
                    }
                    if (arg1 & 0x20) {
                        s3 -= 0xE;
                    } else {
                        s3 += 0xE;
                    }
                }
                s++;
                break;
            case 0x3C:
                if (s4 != 0) {
                    s1 = 1;
                }
                s++;
                break;
            case 0x3E:
                s1 &= fp;
                s++;
                break;
            case 0x7B:
                s1 = s4 != 0;
                s++;
                break;
            case 0x7D:
                s1 = s4 == 0;
                s++;
                break;
            case 0x23:
                if (s1 != 0) {
                    v1 = s[1];
                    if (v1 >= '0' && v1 <= '9') {
                        a0 = v1 - '0';
                    } else if (v1 >= 'a' && v1 <= 'z') {
                        a0 = v1 - 'a' + 10;
                    } else if (v1 >= 'A' && v1 <= 'Z') {
                        a0 = v1 - 'A' + 10;
                    }
                }
                s += 2;
                break;
            case 0x40:
                if (s1 != 0) {
                    D_80064AD8 = s[1];
                }
                s += 2;
                break;
            default:
                if (s1 != 0) {
                    a0 = func_800291C0(s, o->f4, s2, s3, o->fC, arg1);
                }
                s++;
                break;
            }
            if (s7 != 0) {
                s2 -= a0;
            } else {
                s2 += a0;
            }
            v1 = *s;
        } while (v1 != 0);
    }
}
