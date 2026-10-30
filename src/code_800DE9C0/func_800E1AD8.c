/* @header
 * func_800E1AD8
 * VRAM 0x800E1AD8 | ROM 0xD4F78 | size 0xC4
 * asm: asm/nonmatchings/code_800DE9C0/func_800E1AD8.s
 */
#include "common.h"

extern s8 D_800F98E0[];
extern s8 D_800F98E1[];
extern s8 D_800F98E2[];
extern u8 D_800F98E3[];
extern u8 D_800F98E4[];
extern u8 D_800F98E8[];
extern u8 D_800F98EC[];
extern u8 D_800F98F0[];
extern u8 D_800F98F4[];
extern u8 D_800F98F8[];
extern u8 D_800F98FC[];

/* Resets the four 0x30-byte records at D_800F98E0: id bytes set to -1 and all
 * remaining fields cleared. */
void func_800E1AD8(void) {
    s16 i;

    for (i = 0; i < 4; i++) {
        s32 off = i * 0x30;

        D_800F98E0[off] = -1;
        D_800F98E1[off] = -1;
        D_800F98E2[off] = -1;
        D_800F98E3[off] = 0;
        *(s32 *)(D_800F98E4 + off) = 0;
        *(s32 *)(D_800F98EC + off) = 0;
        *(s32 *)(D_800F98E8 + off) = 0;
        *(s32 *)(D_800F98F0 + off) = 0;
        *(s32 *)(D_800F98F8 + off) = 0;
        *(s32 *)(D_800F98F4 + off) = 0;
        *(s32 *)(D_800F98FC + off) = 0;
    }
}
