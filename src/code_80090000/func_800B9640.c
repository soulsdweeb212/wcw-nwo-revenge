/* @header
 * func_800B9640
 * VRAM 0x800B9640 | ROM 0x65DB0 | size 0x150
 * asm: asm/nonmatchings/code_80090000/func_800B9640.s
 */
#include "common.h"

typedef struct { u16 off; u16 pad2; u16 len; u16 pad6; } Blk;
extern u8 D_800DCFD8[], D_800DCFF8[];
extern u8 D_800DCFDA;
extern u8 *D_800DCFDC, *D_800DCFE0, *D_800DCFB8;
extern s32 D_800DCFD4, D_800DCFE4, D_800DCFE8;
extern Blk D_800D2900[];
extern s32 D_80038AA0;
void func_8001C7E0(u8 *, s32);
s32 func_800219B0(s32, void *, s32);
void func_8001C990(void *, void *, s32);

static inline u32 checksum(u8 *p, s32 len) {
    s32 k;
    u32 sum = 0;
    for (k = 0; k < len; k++) {
        sum += (*p++ << (k & 0xF)) + k;
    }
    return sum;
}

s32 func_800B9640(s32 off, s32 sz) {
    u8 *d;
    u8 *c;
    u8 *p;
    u8 *q;
    s32 n, o;
    u32 sum;
    s32 sp10;

    if (D_80038AA0 == 0) {
        d = D_800DCFB8;
        for (n = 0; n < 4; n++) {
            p = D_800DCFB8;
            sum = checksum(p + (&D_800D2900[n])->off, (&D_800D2900[n])->len);
            c = d + ((&D_800D2900[n])->off + (&D_800D2900[n])->len);
            c[0] = sum >> 24;
            c[1] = sum >> 16;
            c[2] = sum >> 8;
            c[3] = sum;
        }
        q = D_800DCFB8 + off;
        o = off + 0x20;
        func_8001C7E0(q, sz);
        D_800DCFDC = D_800DCFF8;
        D_800DCFDA = 0;
        D_800DCFE4 = o;
        D_800DCFE0 = q;
        D_800DCFE8 = sz;
        while (func_800219B0(D_800DCFD4, D_800DCFD8, 1) != 0) {
        }
        func_8001C990(D_800DCFF8, &sp10, 1);
    }
    return 0;
}
