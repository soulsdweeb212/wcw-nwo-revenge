/* @header
 * __osViSwapContext  (originally func_80025C00)
 * VRAM 0x80025C00 | ROM 0x26800 | size 0x308
 * asm: asm/nonmatchings/main/__osViSwapContext.s
 */
#include "common.h"

extern s32 D_8003764C;
extern void *__osViCurr;
extern void *__osViNext;
extern f64 D_8003B900;
u32 func_8001CE80(void *);

typedef struct {
    s32 origin;
    s32 yScale;
    s32 vStart;
    u32 vBurst;
    u32 vIntr;
} ViFldRegs;

typedef struct {
    u8 pad0[8];
    u32 width;
    u32 burst;
    u32 vSync;
    u32 hSync;
    u32 leap;
    u32 hStart;
    u32 xScale;
    u8 pad24[4];
    ViFldRegs fldRegs[2];
} ViMode;

typedef struct {
    u16 state;
    u16 pad2;
    void *framep;
    ViMode *modep;
    u32 features;
    u8 pad10[0x10];
    u32 xScale;
    f32 yFactor;
    u16 yOffset;
    u16 pad2A;
    u32 yScale;
} ViContext;

void __osViSwapContext(void) {
    ViContext *viNext;
    ViMode *viMode;
    ViContext *viCurr;
    u32 field;
    u32 origin;
    u32 hStart;
    u32 vstart;
    f64 nomValue;
    s32 tmp;

    field = 0;
    viNext = (ViContext *)__osViNext;
    viMode = viNext->modep;
    field = *(vu32 *)0xA4400010 & 1;
    origin = func_8001CE80(viNext->framep) + viMode->fldRegs[field].origin;

    if (viNext->state & 2) {
        viNext->xScale |= viMode->xScale & 0xFFFFF000;
    } else {
        viNext->xScale = viMode->xScale;
    }
    if (viNext->state & 4) {
        tmp = viMode->fldRegs[field].yScale & 0xFFF;
        nomValue = (f64)tmp;
        if (tmp < 0) {
            nomValue += D_8003B900;
        }
        viNext->yScale = viNext->yFactor * (f32)nomValue;
        viNext->yScale |= viMode->fldRegs[field].yScale & 0xFFFFF000;
    } else {
        viNext->yScale = viMode->fldRegs[field].yScale;
    }

    vstart = (viMode->fldRegs[field].vStart - (D_8003764C << 16)) + D_8003764C;
    hStart = viMode->hStart;

    if (viNext->state & 0x20) {
        hStart = 0;
    }
    if (viNext->state & 0x40) {
        viNext->yScale = 0;
        origin = func_8001CE80(viNext->framep);
    }
    if (viNext->state & 0x80) {
        viNext->yScale = (viNext->yOffset << 16) & 0x3FF0000;
        origin = func_8001CE80(viNext->framep);
    }

    *(vu32 *)0xA4400004 = origin;
    *(vu32 *)0xA4400008 = viMode->width;
    *(vu32 *)0xA4400014 = viMode->burst;
    *(vu32 *)0xA4400018 = viMode->vSync;
    *(vu32 *)0xA440001C = viMode->hSync;
    *(vu32 *)0xA4400020 = viMode->leap;
    *(vu32 *)0xA4400024 = hStart;
    *(vu32 *)0xA4400028 = vstart;
    *(vu32 *)0xA440002C = viMode->fldRegs[field].vBurst;
    *(vu32 *)0xA440000C = viMode->fldRegs[field].vIntr;
    *(vu32 *)0xA4400030 = viNext->xScale;
    *(vu32 *)0xA4400034 = viNext->yScale;
    *(vu32 *)0xA4400000 = viNext->features;

    viCurr = (ViContext *)__osViCurr;
    __osViCurr = viNext;
    __osViNext = viCurr;
    *viCurr = *viNext;
}
