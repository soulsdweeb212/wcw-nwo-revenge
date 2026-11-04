/* @header
 * func_800B9330
 * VRAM 0x800B9330 | ROM 0x65AA0 | size 0x144
 * asm: asm/nonmatchings/code_80090000/func_800B9330.s
 */
#include "common.h"

typedef struct { u16 off; u16 pad2; u16 len; u16 pad6; } Blk;
extern u8 *D_800DCFB8;
extern Blk D_800D2900[];
void func_800B8B44(void);
void func_800B8C4C(s32);
void func_800B9970(s32);

static inline u32 checksum(u8 *p, s32 len) {
    s32 k;
    u32 sum = 0;
    for (k = 0; k < len; k++) {
        sum += (*p++ << (k & 0xF)) + k;
    }
    return sum;
}

s32 func_800B9330(s32 id) {
    u8 *d;
    u8 *c;
    u8 *p;
    s32 n, i, end;
    u32 sum;

    d = D_800DCFB8;
    n = 0;
    if (id < 0) {
        i = 0;
        end = 4;
    } else {
        i = id;
        end = i + 1;
    }
    for (; i < end; i++) {
        p = D_800DCFB8;
        sum = checksum(p + (&D_800D2900[i])->off, (&D_800D2900[i])->len);
        c = d + ((&D_800D2900[i])->off + (&D_800D2900[i])->len);
        if (sum != ((c[0] << 24) | (c[1] << 16) | (c[2] << 8) | c[3])) {
            if (i == 2) {
                func_800B8B44();
            } else {
                func_800B8C4C(i);
            }
            n++;
        }
    }
    if (n != 0) {
        func_800B9970(4);
    }
    return n;
}
