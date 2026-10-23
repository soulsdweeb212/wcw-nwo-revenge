#include "common.h"

extern u8 D_80038E4C[];

u8 *func_80028B48(s32 arg0) {
    return &D_80038E4C[arg0 & 0xF];
}

u8 *func_80028B5C(u8 *arg0, u8 *arg1) {
    *arg0 = *arg1;
    if (*arg1 == 0) {
        return arg0;
    }
    return func_80028B5C(arg0 + 1, arg1 + 1);
}

u8 *func_80028B80(u8 *arg0, u8 *arg1) {
    u8 *p;

    if (*arg0 != 0) {
        return func_80028B80(arg0 + 1, arg1);
    }
    p = arg0;
    for (;;) {
        *p = *arg1;
        if (*arg1 == 0) {
            break;
        }
        p++;
        arg1++;
    }
    return arg0;
}

u8 *func_80028BB8(u8 *arg0, u8 *arg1) {
    s32 f;
    u8 c;

    f = 0;
    c = *arg1;
    if (c != 0) {
        do {
            switch (c) {
            case 0x3C:
                f = 1;
                break;
            case 0x3E:
                f = 0;
                break;
            case 0x7B:
                f = 1;
                break;
            case 0x7D:
                f = 0;
                break;
            default:
                if (f != 0) {
                    *arg0 = *arg1;
                    arg0++;
                }
                break;
            }
            arg1++;
            c = *arg1;
        } while (c != 0);
    }
    return arg0;
}
