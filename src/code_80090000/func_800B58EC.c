/* @header
 * func_800B58EC
 * VRAM 0x800B58EC | ROM 0x6205C | size 0x1F4
 * asm: asm/nonmatchings/code_80090000/func_800B58EC.s
 */
#include "common.h"


typedef struct { u8 p0[0x20]; u16 a; u16 b; } E;
typedef struct { f32 x; f32 y; u8 p0[0xE]; u8 c; u8 p1[0x9]; u16 k; } A;
extern u8 *D_800E9AA4;
extern s16 D_80038A90;
void func_800B51AC(void);

void func_800B58EC(A *a) {
    u8 *p = D_800E9AA4;
    E *e = (E *)(p + 0xB88);
    u16 x;

    func_800B51AC();
    if (a == 0) {
        return;
    }
    *(f32 *)(p + 0xB88) = a->x;
    *(f32 *)(p + 0xB8C) = a->y;
    p[0xB9E] = a->c;
    e->b = a->k;
    e->a = 0x1100;
    if (D_80038A90 == 0xA || D_80038A90 == 0xC || D_80038A90 == 0 || D_80038A90 == 0x16 || D_80038A90 == 0x17) {
        e->a = 0x1104;
        return;
    }
    if (D_80038A90 == 8) {
        *(u16 *)(p + 0xBA8) = 0x1105;
        return;
    }
    switch (e->b & 0xFF00) {
    case 0x7C00:
        *(u16 *)(p + 0xBA8) = 0xFFFF;
        return;
    case 0x5000:
        *(u16 *)(p + 0xBA8) = 0x1103;
        return;
    case 0x5A00:
    case 0x5B00:
    case 0x5C00:
        e->a = 0x1109;
        return;
    case 0x5900:
        *(u16 *)(p + 0xBA8) = 0x1108;
        return;
    case 0x6200:
        *(u16 *)(p + 0xBA8) = 0x1102;
        return;
    }
    x = e->b;
    if (x == 0xFFFF || (x >= 0x63 && x < 0x6F)) {
        e->a = 0x1104;
    } else if (x >= 0x94 && x < 0x98) {
        e->a = 0x1106;
    } else if (x >= 0x98 && x < 0x9B) {
        e->a = 0x1107;
    } else if (x >= 0x3F && x < 0x5E) {
        e->a = 0x1102;
    } else if (x >= 0x2B && x < 0x3F) {
        e->a = 0x1101;
    }
}
