/* @header
 * func_800B5704
 * VRAM 0x800B5704 | ROM 0x61E74 | size 0x1E8
 * asm: asm/nonmatchings/code_80090000/func_800B5704.s
 */
#include "common.h"

typedef struct { u8 pad[0xA]; u16 f; u8 pad2[0x13C]; } E;
extern E *D_800E9AA4, *D_800E837C, *D_800E885C, *D_800E8994, *D_800E8724, *D_800E85EC, *D_800E8D3C;
extern E *D_800E996C[];
extern s16 D_800E836C, D_800E884C, D_800E8984, D_800E8714, D_800E85DC, D_800E8D2C;

void func_800B5704(s32 x) {
    E *a = 0;
    E *b = 0;
    u16 *q;

    switch (x) {
    case 1:
        a = &D_800E9AA4[1];
        b = &D_800E837C[D_800E836C];
        break;
    case 5:
        a = &D_800E9AA4[2];
        b = &D_800E885C[D_800E884C];
        break;
    case 6:
        a = &D_800E9AA4[2];
        b = &D_800E8994[D_800E8984];
        break;
    case 4:
        a = &D_800E9AA4[2];
        b = &D_800E8724[D_800E8714];
        break;
    case 3:
        b = &D_800E85EC[D_800E85DC];
    case 2:
        a = &D_800E9AA4[3];
        break;
    case 19:
        a = &D_800E9AA4[4];
        *(u16 *)((u8 *)D_800E996C[0] + 0x152) &= ~1;
        b = &D_800E996C[0][3];
        break;
    case 9:
        switch (D_800E8D2C) {
        case 0xE:
            a = &D_800E9AA4[4];
            b = &D_800E8D3C[14];
            break;
        case 0xF:
            a = &D_800E9AA4[4];
            b = &D_800E8D3C[15];
            break;
        }
        break;
    case -1:
        q = &D_800E9AA4[1].f;
        for (a = (E *)1; (s32)a < 9; a = (E *)((s32)a + 1), q += 0xA4) {
            *q |= 0x20;
        }
        a = 0;
        break;
    }
    if (a) {
        a->f |= 0x20;
    }
    if (b) {
        b->f &= ~1;
    }
}
