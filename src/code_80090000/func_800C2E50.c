/* @header
 * func_800C2E50
 * VRAM 0x800C2E50 | ROM 0x6F5C0 | size 0x244
 * asm: asm/nonmatchings/code_80090000/func_800C2E50.s
 */
#include "common.h"


typedef struct { u8 p0[0x38]; u64 fl; s16 t[0x338]; s16 id; } P;
extern s16 D_800D5E88[][8];
extern s16 D_80030570[];

s32 func_800C2E50(P *p) {
    s32 a = p->id;
    u16 b = a; /* a u16 copy: the ROM keeps it in its own register (move v1,a1) for the last range check */
    s32 n;
    u64 f;
    s32 pad[2]; /* placeholder: the ROM has an 8-byte frame that nothing uses */

    if (a == -7) {
        if (p->fl & 0x2000) return 0x1083;
        if (p->fl & 0x4000) return 0x1084;
        if (p->fl & 0x8000) return 0x1085;
        if (p->fl & 0x10000) return 0x1086;
        return 0x1082;
    }
    if (a < 0) {
        n = -a;
        if (n >= 7) {
            return 0xE3E;
        }
        f = p->fl;
        if (f & 8) return D_800D5E88[1][n];
        if (f & 0x10) return D_800D5E88[2][n];
        if (f & 0x20) return D_800D5E88[3][n];
        if (f & 0x40) return D_800D5E88[4][n];
        if (f & 0x80) return D_800D5E88[5][n];
        if (p->fl & 0x100) return D_800D5E88[6][n];
        return D_800D5E88[0][n];
    }
    if (a < 0xEF) {
        return p->t[D_80030570[a]] + 0x110B;
    }
    if ((u32)((b - 0xE39) & 0xFFFF) < 0xFB1) {
        return a;
    } else {
        return 0xE3E;
    }
}
