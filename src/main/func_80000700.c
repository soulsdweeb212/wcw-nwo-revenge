#include "common.h"

extern s32 D_8003DD98;
extern u8 D_8003DDA0;
extern s8 D_8003DDA2;
extern u32 D_8003DDA4;
extern s32 D_8003DDA8;
extern s32 D_8003DDAC;
extern s32 D_8003DDB0;
extern void func_8001C660(s32, s32);
extern s32 func_800219B0(s32, u8 *, s32);
extern void func_8001C5B0(s32, s32);
extern void func_80021F60(s32, s32);
extern void func_8001C890(u8 *, s32 *, s32);
extern void func_8001C990(u8 *, s32 *, s32);

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
    func_8001C660(c.fC, c.f10 - c.fC);
    remaining = size;
    func_8001C5B0(c.f14, c.f18 - c.f14);
    x = c.srcStart;
    y = c.dstStart;
    func_8001C890(cmd, &ret1, 1);
    func_8001C5B0(y, remaining);
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
            while (func_800219B0(D_8003DD98, &D_8003DDA0, 0)) {
            }
            func_8001C990(cmd, &ret2, 1);
            dst += chunk;
            remaining -= chunk;
            src += chunk;
        } while (remaining > 0);
    }
    func_80021F60(c.f1C, c.f20 - c.f1C);
}
