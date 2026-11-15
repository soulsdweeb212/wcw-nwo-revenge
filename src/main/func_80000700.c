/* @header
 * func_80000700
 * VRAM 0x80000700 | ROM 0x1300 | size 0x12C
 * asm: asm/nonmatchings/main/func_80000700.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: both overlays' code is compiled into the program, so the N64's copy of the overlay's code and data from the ROM
 * and the zeroing of its BSS become a fresh start of its variables (port.h's port_overlay_load); the caches have
 * nothing to do. The record arrives as the boot loop passes it, as its first four words and its last five (common.h's
 * Nw2InitRect and Nw2InitBig): on the N64 that is the same as one 36-byte record, on the PC's calling convention it
 * is not, so the PC version takes the two halves. */
void func_80000700(Nw2InitRect rect, Nw2InitBig regions) {
    (void)regions;
    port_overlay_load(port_overlay_of(rect.srcStart, rect.srcEnd));
}
#else
extern s32 D_8003DD98;
extern u8 D_8003DDA0;
extern s8 D_8003DDA2;
extern u32 D_8003DDA4;
extern s32 D_8003DDA8;
extern s32 D_8003DDAC;
extern s32 D_8003DDB0;
extern void osInvalICache(s32, s32);
extern s32 osEPiStartDma(s32, u8 *, s32);
extern void osInvalDCache(s32, s32);
extern void bzero(s32, s32);
extern void osCreateMesgQueue(u8 *, s32 *, s32);
extern void osRecvMesg(u8 *, s32 *, s32);

/* Range descriptor: each field is a {start, end} pair for one buffer range. */
typedef struct {
    s32 srcStart, srcEnd;   /* source range to copy */
    s32 dstStart;           /* destination start */
    s32 fC, f10;            /* extra cache range 1 */
    s32 f14, f18;           /* extra cache range 2 */
    s32 f1C, f20;           /* extra cache range 3 */
} Cfg;

/* Copy the [srcStart, srcEnd) byte range to dstStart in chunks of at most 0x200
 * bytes, waiting on the DMA command queue between chunks, and bracket the
 * transfer with cache maintenance over the three descriptor ranges. */
void func_80000700(Cfg c) {
    u8 cmd[0x18];
    s32 ret1;
    s32 ret2;
    s32 size, remaining, x, y, dst, src;
    size = c.srcEnd - c.srcStart;
    osInvalICache(c.fC, c.f10 - c.fC);
    remaining = size;
    osInvalDCache(c.f14, c.f18 - c.f14);
    x = c.srcStart;
    y = c.dstStart;
    osCreateMesgQueue(cmd, &ret1, 1);
    osInvalDCache(y, remaining);
    dst = x; src = y;
    if (remaining > 0) {
        do {
            s32 chunk = remaining;
            if (remaining >= 0x201) chunk = 0x200;
            D_8003DDA4 = (u32)cmd;
            D_8003DDA2 = 0;
            D_8003DDAC = dst;
            D_8003DDA8 = src;
            D_8003DDB0 = chunk;
            while (osEPiStartDma(D_8003DD98, &D_8003DDA0, 0)) {
            }
            osRecvMesg(cmd, &ret2, 1);
            dst += chunk;
            remaining -= chunk;
            src += chunk;
        } while (remaining > 0);
    }
    bzero(c.f1C, c.f20 - c.f1C);
}
#endif
