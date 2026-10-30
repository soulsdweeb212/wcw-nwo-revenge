/* @header
 * func_80028C44
 * VRAM 0x80028C44 | ROM 0x29844 | size 0x7C
 * asm: asm/nonmatchings/main/func_80028C44.s
 */
#include "common.h"

u64 func_80028624(u32, u32, u32, u32);
u64 func_80028528(u32, u32, u32, u32);

extern u8 asciiCharTable[];
extern u8 sjisCodeTable[];

/* Copies arg1 to arg0 while outside {} braces (brace contents are dropped).
 * Returns the end cursor. */
u8 *func_80028C44(u8 *arg0, u8 *arg1) {
    s32 f;
    u8 c;

    f = 1;
    c = *arg1;
    if (c != 0) {
        do {
            switch (c) {
            case 0x3C:
                break;
            case 0x3E:
                break;
            case 0x7B:
                f = 0;
                break;
            case 0x7D:
                f = 1;
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
