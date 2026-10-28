#include "common.h"

extern u8 D_80038E4C[];

/* Copies arg1 to arg0 while inside <> or {} tag pairs (the tag markers
 * themselves are dropped). Returns the end cursor. */
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
