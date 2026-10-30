/* @header
 * func_800247C4
 * VRAM 0x800247C4 | ROM 0x253C4 | size 0x80
 * asm: asm/nonmatchings/main/func_800247C4.s
 */
#include "common.h"

typedef struct {
    u8 b[6];
} Nw2Six;

extern s32 D_8007E00C[];

extern u8 D_8007DFD0[];

/* Decodes the arg0-th controller response into arg1 (error nibble and, for a
 * good entry, the payload). */
void func_800247C4(s32 arg0, u8 *arg1) {
    u8 buf[16];
    u8 *p;
    s32 i;
    u32 v;

    p = D_8007DFD0;
    i = 0;
    if (arg0 > 0) {
        do {
            i++;
            p++;
        } while (i < arg0);
    }
    *(Nw2Six *)buf = *(Nw2Six *)p;
    v = (buf[1] & 0xC0) >> 4;
    arg1[3] = v;
    if (v == 0) {
        *(u16 *)arg1 = buf[3] | (buf[4] << 8);
        arg1[2] = buf[5];
    }
}

extern Nw2IdSubTable lookupSubTables[];
