/* @header
 * func_80019790
 * VRAM 0x80019790 | ROM 0x1A390 | size 0x1BC
 * asm: asm/nonmatchings/main/func_80019790.s
 */
#include "common.h"

/* Emit the scroll/position command for a UI object: if it has an override
 * (f48) just emit one command; otherwise wrap the fractional offset into
 * [0,1), advance the pixel scroll and emit a scaled scroll command whose
 * payload uses the object's physical address. */
typedef struct {
    u8 pad0[0x40];
    void *f40;
    f32 f44;
    s32 f48;
    f32 f4C;
    u32 f50;
} Nw2Obj19790;

extern f64 D_8003B4E0;

void *func_80019070(void *, s16 *, s32, void *);
u32 func_8001CE80(void *);

void *func_80019790(Nw2Obj19790 *obj, u16 *value, void *cmd) {
    s16 cmdBits;
    f32 frac;
    f32 scroll;
    s32 scrollPixels;
    u16 fracBits;
    u32 physAddr;

    cmdBits = 0x170;
    if (obj->f48 != 0) {
        s32 *g;
        cmd = func_80019070(obj, &cmdBits, 0xB8, cmd);
        g = (s32 *)cmd;
        cmd = (u8 *)cmd + 8;
        g[0] = (cmdBits & 0xFFFFFF) | 0x0A000000;
        g[1] = (*value << 16) | 0x170;
    } else {
        s32 *g;
        if (D_8003B4E0 < (f64)obj->f44) {
            obj->f44 = 1.99996f;
        }
        frac = (f32)(s32)(obj->f44 * 32768.0f) / 32768.0f;
        scroll = obj->f4C + frac * 184.0f;
        scrollPixels = (s32)scroll;
        obj->f44 = frac;
        obj->f4C = scroll - (f32)scrollPixels;
        cmd = func_80019070(obj, &cmdBits, scrollPixels, cmd);
        fracBits = (s32)(obj->f44 * 32768.0f) & 0xFFFF;
        physAddr = func_8001CE80(obj->f40);
        g = (s32 *)cmd;
        cmd = (u8 *)cmd + 8;
        g[0] = (physAddr & 0xFFFFFF) | 0x05000000;
        g[1] = (obj->f50 << 30) | (fracBits << 14) | ((cmdBits & 0xFFF) << 2);
        obj->f50 = 0;
    }
    return cmd;
}
