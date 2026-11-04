/* @header
 * func_800AE5C4
 * VRAM 0x800AE5C4 | ROM 0x5AD34 | size 0xBC
 * asm: asm/nonmatchings/code_80090000/func_800AE5C4.s
 */
#include "common.h"

typedef struct { u8 pad0[0x22]; u16 f22; u8 pad24[0x148 - 0x24]; } El;
typedef struct { u8 pad0[0x48]; u8 name[4][9]; } Names;
extern El *D_800E8E74;
extern s16 D_800E8E6A;
extern s32 D_800E9F98[4][16];
extern Names D_8007E8C0;
extern s32 D_800E79A0[];
extern s32 D_800E7BF0[];

void func_800AE5C4(void) {
    El *e;
    s32 i, j, k;
    s32 *p;
    u16 x;
    s32 pad[4]; /* placeholder: the ROM has a 16-byte frame that nothing uses */

    e = D_800E8E74;
    D_800E8E6A = 9;
    for (i = 0; i < 4; i++, e++) {
        D_800E7BF0[i] = 1;
        D_800E79A0[i] = 0;
        /* through a u16 local, so the read is narrowed to the low halfword (lhu 2) */
        x = D_800E7BF0[i];
        e->f22 = x;
        p = D_800E9F98[i];
        for (j = 0, k = D_800E79A0[i]; j < 11; j++, k++, p++) {
            *p = k << 4;
            if (k >= 2) {
                *p = (k << 4) | D_8007E8C0.name[i][k - 2];
            }
        }
    }
}
