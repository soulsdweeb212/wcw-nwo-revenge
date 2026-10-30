/* @header
 * func_8001F200
 * VRAM 0x8001F200 | ROM 0x1FE00 | size 0x1EC
 * asm: asm/nonmatchings/main/func_8001F200.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } Acmd17;
typedef struct ALFilter17 {
    struct ALFilter17 *source;
    Acmd17 *(*handler)(void *, s16 *, s32, s32, Acmd17 *);
    void *setParam;
    s16 inp;
    s16 outp;
    s32 type;
} ALFilter17;
typedef struct {
    ALFilter17 filter;
    void *state;
    f32 ratio;
    s32 upitch;
    f32 delta;
    s32 first;
} ALResampler17;
extern f64 D_8003B810;
u32 func_8001CE80(void *);

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))

Acmd17 *func_8001F200(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd17 *p)
{
    ALResampler17 *f = (ALResampler17 *)filter;
    Acmd17 *ptr = p;
    s16 inp;
    s32 inCount;
    ALFilter17 *source = f->filter.source;
    s32 incr;
    f32 finCount;

    inp = 0x140;
    if (!outCount)
        return ptr;

    if (f->upitch) {
        ptr = (*source->handler)(source, &inp, outCount, sampleOffset, p);
        {
            Acmd17 *_a = ptr++;
            _a->w0 = _SHIFTL(0x0A, 24, 8) | _SHIFTL(inp, 0, 24);
            _a->w1 = _SHIFTL(*outp, 16, 16) | _SHIFTL(outCount << 1, 0, 16);
        }
    } else {
        if (f->ratio > D_8003B810)
            f->ratio = 1.99996f;
        f->ratio = (s32)(f->ratio * 32768.0f);
        f->ratio = f->ratio / 32768.0f;
        finCount = f->delta + (f->ratio * (f32)outCount);
        inCount = (s32)finCount;
        f->delta = finCount - (f32)inCount;
        ptr = (*source->handler)(source, &inp, inCount, sampleOffset, p);
        incr = (s32)(f->ratio * 32768.0f);
        {
            Acmd17 *_a = ptr++;
            _a->w0 = _SHIFTL(0x08, 24, 8) | _SHIFTL(0, 16, 8) | _SHIFTL(inp, 0, 16);
            _a->w1 = _SHIFTL(*outp, 16, 16) | _SHIFTL(outCount << 1, 0, 16);
        }
        {
            Acmd17 *_a = ptr++;
            _a->w0 = _SHIFTL(0x05, 24, 8) | _SHIFTL(f->first, 16, 8) | _SHIFTL(incr, 0, 16);
            _a->w1 = func_8001CE80(f->state);
        }
        f->first = 0;
    }
    return ptr;
}
