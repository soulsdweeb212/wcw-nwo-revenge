/* @header
 * func_800B9268
 * VRAM 0x800B9268 | ROM 0x659D8 | size 0xC8
 * asm: asm/nonmatchings/code_80090000/func_800B9268.s
 */
#include "common.h"


typedef struct { u16 off; u16 pad2; u16 len; u16 pad6; } Blk;
extern u8 *D_800DCFB8;
extern Blk D_800D2900[];

static inline u32 checksum(u8 *p, s32 len) {
    s32 k;
    u32 sum = 0;
    for (k = 0; k < len; k++) {
        sum += (*p++ << (k & 0xF)) + k;
    }
    return sum;
}

void func_800B9268(s32 id) {
    u8 *d;
    u8 *c;
    u8 *p;
    s32 i, end;
    u32 sum;

    d = D_800DCFB8;
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
        c[0] = sum >> 24;
        c[1] = sum >> 16;
        c[2] = sum >> 8;
        c[3] = sum;
    }
}
