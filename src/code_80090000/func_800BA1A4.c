/* @header
 * func_800BA1A4
 * VRAM 0x800BA1A4 | ROM 0x66914 | size 0x310
 * asm: asm/nonmatchings/code_80090000/func_800BA1A4.s
 */
#include "common.h"


typedef struct { u16 off; u16 pad2; u16 len; u16 pad6; } Blk;
typedef struct { u8 e[4][0x26]; s32 sum; } Rec;
typedef struct { u8 pad[0x600]; Rec recs[64]; } Save;
extern u8 *D_800DCFB8;
extern s32 D_800DCFC4, D_800DCFBC;
extern Blk D_800D2900[];
s32 func_8002B5AC(s32);
u8 *func_8002B790(s32, s32);
void func_80021C40(void *, void *, s32);
s32 func_8000424C(void);
s32 func_800B9640(s32, s32);
void func_80004290(void);

static inline u32 checksum(u8 *p, s32 len) {
    s32 k;
    u32 sum = 0;
    for (k = 0; k < len; k++) {
        sum += (*p++ << (k & 0xF)) + k;
    }
    return sum;
}

static inline s32 write(s32 a, s32 b) {
    D_800DCFC4 = func_8000424C();
    D_800DCFBC = func_800B9640(a, b);
    func_80004290();
    return D_800DCFBC;
}

static inline void copyRec(s32 i, s32 j) {
    u8 *d = func_8002B790(i, j);
    u8 *s = D_800DCFB8 + 0x600 + i * 0x9C + j * 0x26;
    func_80021C40(d, s, 0x18);
    func_80021C40(d + 0x19, s + 0x18, 0xA);
    s[0x22] = d[0x24];
    s[0x23] = d[0x25];
    *(u16 *)(s + 0x24) = (d[0x27] & 0x1F) | ((d[0x28] & 0x1F) << 5);
}

void func_800BA1A4(s32 a, s32 j) {
    s32 i, n, lo, hi;
    u32 sum;
    u32 t;
    u8 *p;
    u8 *b;
    u8 *c;

    i = func_8002B5AC(a);
    if (j < 0) {
        for (j = 0; j < 4; j++) {
            copyRec(i, j);
        }
    } else {
        copyRec(i, j);
    }
    /* Placeholder: the loop note of this block doubles the temps' allocation
       weight, so they take v0 and i * 0x9C lands in v1 (likely a macro). */
    do {
        lo = (i * 0x9C + 0x600) & ~0x1F;
        hi = (i * 0x9C + 0x6BB) & ~0x1F;
    } while (0);
    t = checksum((u8 *)&((Save *)D_800DCFB8)->recs[i], 0x98);
    ((Save *)D_800DCFB8)->recs[i].sum = t;
    b = D_800DCFB8;
    for (n = 0; n < 4; n++) {
        p = D_800DCFB8;
        sum = checksum(p + (&D_800D2900[n])->off, (&D_800D2900[n])->len);
        c = b + ((&D_800D2900[n])->off + (&D_800D2900[n])->len);
        c[0] = sum >> 24;
        c[1] = sum >> 16;
        c[2] = sum >> 8;
        c[3] = sum;
    }
    D_800DCFBC = write(lo, hi - lo);
    D_800DCFBC = write(0x2700, 0x620);
}
