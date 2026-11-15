/* @header
 * func_800B9640
 * VRAM 0x800B9640 | ROM 0x65DB0 | size 0x150
 * asm: asm/nonmatchings/code_80090000/func_800B9640.s
 */
#include "common.h"

typedef struct { u16 off; u16 pad2; u16 len; u16 pad6; } Blk;
#ifdef TARGET_PC
/* PC: as in func_800BAD80.c: D_800DCFD8 is the SRAM transfer request, port.h's PortIoMesg, written by field name
 * (the N64 writes it through the labels of its fields, which have no PC symbol), and D_800DCFD4 holds the SRAM handle
 * that func_80000A40 returns, a pointer. The SDK functions are declared with the port's types. */
extern PortIoMesg D_800DCFD8;
extern u8 D_800DCFF8[];
extern u8 *D_800DCFB8;
extern void *D_800DCFD4;
#else
extern u8 D_800DCFD8[], D_800DCFF8[];
extern u8 D_800DCFDA;
extern u8 *D_800DCFDC, *D_800DCFE0, *D_800DCFB8;
extern s32 D_800DCFD4, D_800DCFE4, D_800DCFE8;
#endif
extern Blk D_800D2900[];
extern s32 D_80038AA0;
#ifdef TARGET_PC
void osWritebackDCache(void *p, s32 size);
s32 osEPiStartDma(void *handle, PortIoMesg *mb, s32 direction);
s32 osRecvMesg(void *mq, u32 *msg, s32 flag);
#else
void osWritebackDCache(u8 *, s32);
s32 osEPiStartDma(s32, void *, s32);
void osRecvMesg(void *, void *, s32);
#endif

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
#ifdef TARGET_PC
    u32 sp10; /* PC: the port's osRecvMesg writes a 4-byte message as a u32 */
#else
    s32 sp10;
#endif

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
        osWritebackDCache(q, sz);
#ifdef TARGET_PC
        /* PC: the request's fields by name, as above */
        D_800DCFD8.retQueue = D_800DCFF8;
        D_800DCFD8.pri = 0;
        D_800DCFD8.devAddr = o;
        D_800DCFD8.dramAddr = q;
        D_800DCFD8.size = sz;
        while (osEPiStartDma(D_800DCFD4, &D_800DCFD8, 1) != 0) {
        }
#else
        D_800DCFDC = D_800DCFF8;
        D_800DCFDA = 0;
        D_800DCFE4 = o;
        D_800DCFE0 = q;
        D_800DCFE8 = sz;
        while (osEPiStartDma(D_800DCFD4, D_800DCFD8, 1) != 0) {
        }
#endif
        osRecvMesg(D_800DCFF8, &sp10, 1);
    }
    return 0;
}
