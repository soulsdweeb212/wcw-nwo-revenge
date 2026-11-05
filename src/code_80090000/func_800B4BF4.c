/* @header
 * func_800B4BF4
 * VRAM 0x800B4BF4 | ROM 0x61364 | size 0x1AC
 * asm: asm/nonmatchings/code_80090000/func_800B4BF4.s
 */
#include "common.h"

typedef struct { s16 f0; s16 id; u8 f4; u8 pad5[0xB]; } Pl;
typedef struct { u8 pad0[0x4C]; Pl pl[4]; } Game;
typedef struct { void *items; s16 cur; u8 pad6[4]; s16 fA; u8 padC[8]; u8 *el; u8 pad18[0x138 - 0x18]; } Menu;
extern Game D_8007EF30;
extern u8 D_8007E8C0[];
extern Menu D_800E8230[];
extern s16 D_800E9962[], D_800E995C;
extern u8 *D_800E996C;
extern s32 D_800E74D4, D_800EA348, D_800E79AC;
extern s32 D_800E73A4[3];
s16 func_8000B3DC(u32);
s16 func_8000B41C(u32);
s32 func_8002B7E0(s32, s32);
void bcopy(void *, void *, s32);

void func_800B4BF4(s32 a) {
    Menu *mn = &D_800E8230[19];
    s32 id;
    u8 *p;
    u8 *e;
    s32 n, i, m;
    u8 *r;
    u16 x, y;

    mn->fA = a;
    id = D_8007EF30.pl[a].id;
    p = mn->el;
    e = (u8 *)func_8002B7E0(id, D_8007EF30.pl[a].f4);
    bcopy(e, D_8007E8C0 + 0xB8, 0x18);
    bcopy(e + 0x19, D_8007E8C0 + 0xB8 + 0x22, 0xA);
    D_800E74D4 = e[0x24];
    D_800EA348 = e[0x25];
    D_800E73A4[0] = e[0x26];
    D_800E73A4[1] = e[0x27];
    D_800E73A4[2] = e[0x28];
    n = func_8000B3DC(id) - 1;
    m = func_8000B41C(id) - 1;
    *(s16 *)(p + 0x542) = n;
    if (m != 0) {
        *(s16 *)(p + 0x7D2) = m;
        x = *(u16 *)(p + 0x7BA) & 0xFFBF;
        y = *(u16 *)(p + 0x902) & 0xFFBF;
    } else {
        *(s16 *)(p + 0x7D2) = 0;
        x = *(u16 *)(p + 0x7BA) | 0x40;
        y = *(u16 *)(p + 0x902) | 0x40;
    }
    *(u16 *)(p + 0x7BA) = x;
    *(u16 *)(p + 0x902) = y;
    x = D_800EA348 | 0x5B00;
    y = D_800E74D4 | 0x5A00;
    *(s16 *)(p + 0x540) = x;
    *(s16 *)(p + 0x7D0) = y;
    r = mn->el + 0xA4A;
    for (i = 0; i < 2; i++) {
        r[2] = D_800E73A4[i + 1];
        *(u16 *)r |= 0x40;
        r += 0x148;
    }
    D_800E79AC = 0;
    D_800E8230[19].cur = 0;
}
