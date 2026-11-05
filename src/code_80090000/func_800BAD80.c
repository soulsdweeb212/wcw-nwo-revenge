/* @header
 * func_800BAD80
 * VRAM 0x800BAD80 | ROM 0x674F0 | size 0x34C
 * asm: asm/nonmatchings/code_80090000/func_800BAD80.s
 */
#include "common.h"

typedef struct { u16 off; u16 pad2; u16 len; u16 pad6; } Blk;
extern u8 D_800DCFD8[], D_800DCFF8[];
extern u8 D_800DCFDA;
extern u8 *D_800DCFDC, *D_800DCFE0, *D_800DCFB8;
extern s32 D_800DCFD4, D_800DCFE4, D_800DCFE8;
extern Blk D_800D2900[];

static inline u32 checksum(u8 *p, s32 len) {
    s32 k;
    u32 sum = 0;
    for (k = 0; k < len; k++) {
        sum += (*p++ << (k & 0xF)) + k;
    }
    return sum;
}

static inline s32 valid(u8 *b) {
    s32 i;
    for (i = 0; i < 0x20; i += 4) {
        if (b[i] != 0x19 || b[i + 1] != 0x97 || b[i + 2] != 0x10 || b[i + 3] != 0x21) {
            return 0;
        }
    }
    return -1;
}

void func_800BAD80(void) {
    u8 *b;
    u8 *q;
    u8 *d;
    u8 *c;
    Blk *e;
    s32 j, n;
    u8 *p;
    u32 sum;
    s32 sp10;

    b = allocateHeap(0x100);
    osInvalDCache(b, 0x20);
    D_800DCFDC = D_800DCFF8;
    D_800DCFDA = 0;
    D_800DCFE4 = 0;
    D_800DCFE0 = b;
    D_800DCFE8 = 0x20;
    while (osEPiStartDma(D_800DCFD4, D_800DCFD8, 0) != 0) {
    }
    osRecvMesg(D_800DCFF8, &sp10, 1);
    if (valid(b) == 0) {
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
        q = D_800DCFB8;
        osWritebackDCache(q, 0x2D80);
        D_800DCFDC = D_800DCFF8;
        D_800DCFE4 = 0x20;
        D_800DCFDA = 0;
        D_800DCFE0 = q;
        D_800DCFE8 = 0x2D80;
        while (osEPiStartDma(D_800DCFD4, D_800DCFD8, 1) != 0) {
        }
        osRecvMesg(D_800DCFF8, &sp10, 1);
        for (j = 0; j < 0x20; j += 4) {
            b[j] = 0x19;
            b[j + 1] = 0x97;
            b[j + 2] = 0x10;
            b[j + 3] = 0x21;
        }
        osWritebackDCache(b, 0x20);
        D_800DCFDC = D_800DCFF8;
        D_800DCFDA = 0;
        D_800DCFE4 = 0;
        D_800DCFE0 = b;
        D_800DCFE8 = 0x20;
        while (osEPiStartDma(D_800DCFD4, D_800DCFD8, 1) != 0) {
        }
        osRecvMesg(D_800DCFF8, &sp10, 1);
    } else {
        q = D_800DCFB8;
        osInvalDCache(q, 0x2D80);
        D_800DCFDC = D_800DCFF8;
        D_800DCFE4 = 0x20;
        D_800DCFDA = 0;
        D_800DCFE0 = q;
        D_800DCFE8 = 0x2D80;
        while (osEPiStartDma(D_800DCFD4, D_800DCFD8, 0) != 0) {
        }
        osRecvMesg(D_800DCFF8, &sp10, 1);
        func_800B9330(-1);
    }
    releaseHeapBlock(b);
}
