/* @header
 * func_800B4E18
 * VRAM 0x800B4E18 | ROM 0x61588 | size 0xE4
 * asm: asm/nonmatchings/code_80090000/func_800B4E18.s
 */
#include "common.h"


extern u8 D_8007EF30[], D_8007E8C0[];
extern u16 D_800E9962;
extern u8 *D_800E996C;
extern s32 D_800E73A4[3], D_800E74D4, D_800EA348;
void buildWrestlerNameRecord(s32, s32, void *);
void bcopy(void *, void *, s32);
#define F(t, o, i) (*(t *)(D_8007EF30 + (o) + ((i) << 4)))

void func_800B4E18(void) {
    u8 buf[0x30];
    u8 *p = D_800E996C;
    s32 a, b;
    u8 *d;
    buildWrestlerNameRecord(F(s16, 0x4E, D_800E9962), F(u8, 0x50, D_800E9962), buf);
    d = D_8007E8C0 + 0xB8;
    bcopy(buf, d, 0x18);
    bcopy(buf + 0x19, d + 0x22, 0xA);
    a = buf[0x24];
    b = buf[0x25];
    D_800E73A4[0] = buf[0x26];
    D_800E73A4[1] = buf[0x27];
    D_800E73A4[2] = buf[0x28];
    *(s16 *)(p + 0x540) = b | 0x5B00;
    *(s16 *)(p + 0x7D0) = a | 0x5A00;
    D_800E74D4 = a;
    D_800EA348 = b;
    p[0xA4C] = D_800E73A4[1];
    p[0xB94] = D_800E73A4[2];
}
