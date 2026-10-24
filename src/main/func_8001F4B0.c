#include "common.h"

typedef struct { u32 w0, w1; } Acmd21;
typedef struct ALFilter21 {
    struct ALFilter21 *source;
    Acmd21 *(*handler)(void *, s16 *, s32, s32, Acmd21 *);
    void *setParam;
    s16 inp;
    s16 outp;
    s32 type;
} ALFilter21;
typedef struct {
    u32 input;
    u32 output;
    s16 ffcoef;
    s16 fbcoef;
    s16 gain;
    f32 rsinc;
    f32 rsval;
    s32 rsdelta;
    f32 rsgain;
    void *lp;
    void *rs;
} ALDelay21;
typedef struct {
    ALFilter21 filter;
    s16 *base;
    s16 *input;
    u32 length;
    ALDelay21 *delay;
    u8 section_count;
} ALFx21;

Acmd21 *loadResampledAudioRingBuffer(ALFx21 *r, ALDelay21 *d, s32 buff, s32 incount, Acmd21 *p);
Acmd21 *loadAudioRingBuffer(ALFx21 *r, s16 *curr_ptr, s32 buff, s32 count, Acmd21 *p);
Acmd21 *saveAudioRingBuffer(ALFx21 *r, s16 *curr_ptr, s32 buff, s32 count, Acmd21 *p);
Acmd21 *func_8001FF5C(void *lp, s32 buff, s32 count, Acmd21 *p);
void func_8001CEE0(char *, char *, s32);
extern char D_8003B840[];
extern char D_8003B844[];

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define aSetBuffer(pkt, f, i, o, c) { Acmd21 *_a = (Acmd21 *)pkt; \
    _a->w0 = (_SHIFTL(8, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(i, 0, 16)); \
    _a->w1 = _SHIFTL(o, 16, 16) | _SHIFTL(c, 0, 16); }
#define aMix(pkt, f, g, i, o) { Acmd21 *_a = (Acmd21 *)pkt; \
    _a->w0 = (_SHIFTL(0x0C, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(g, 0, 16)); \
    _a->w1 = _SHIFTL(i, 16, 16) | _SHIFTL(o, 0, 16); }
#define aClearBuffer(pkt, d, c) { Acmd21 *_a = (Acmd21 *)pkt; \
    _a->w0 = _SHIFTL(2, 24, 8) | _SHIFTL(d, 0, 24); _a->w1 = (u32)(c); }
#define aDMEMMove(pkt, i, o, c) { Acmd21 *_a = (Acmd21 *)pkt; \
    _a->w0 = _SHIFTL(0x0A, 24, 8) | _SHIFTL(i, 0, 24); \
    _a->w1 = _SHIFTL(o, 16, 16) | _SHIFTL(c, 0, 16); }
#define SWAP(in, out) { s16 t = out; out = in; in = t; }

Acmd21 *func_8001F4B0(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd21 *p)
{
    Acmd21 *ptr = p;
    ALFx21 *r = (ALFx21 *)filter;
    ALFilter21 *source = r->filter.source;
    s16 i, buff1, buff2, input, output;
    s16 *in_ptr, *out_ptr, *prev_out_ptr = 0;
    ALDelay21 *d;

    if (!source)
        func_8001CEE0(D_8003B840, D_8003B844, 0x4B);

    ptr = (*source->handler)(source, outp, outCount, sampleOffset, p);

    input = 0x6C0;
    output = 0x800;
    buff1 = 0;
    buff2 = 0x140;

    aSetBuffer(ptr++, 0, 0, 0, outCount << 1);
    aMix(ptr++, 0, 0xda83, 0x6C0, input);
    aMix(ptr++, 0, 0x5a82, 0x800, input);
    ptr = saveAudioRingBuffer(r, r->input, input, outCount, ptr);

    aClearBuffer(ptr++, output, outCount << 1);

    for (i = 0; i < r->section_count; i++) {
        d = &r->delay[i];
        in_ptr = &r->input[-d->input];
        out_ptr = &r->input[-d->output];

        if (in_ptr == prev_out_ptr) {
            SWAP(buff1, buff2);
        } else {
            ptr = loadAudioRingBuffer(r, in_ptr, buff1, outCount, ptr);
        }
        ptr = loadResampledAudioRingBuffer(r, d, buff2, outCount, ptr);

        if (d->ffcoef) {
            aMix(ptr++, 0, (u16)d->ffcoef, buff1, buff2);
            if (!d->rs && !d->lp) {
                ptr = saveAudioRingBuffer(r, out_ptr, buff2, outCount, ptr);
            }
        }

        if (d->fbcoef) {
            aMix(ptr++, 0, (u16)d->fbcoef, buff2, buff1);
            ptr = saveAudioRingBuffer(r, in_ptr, buff1, outCount, ptr);
        }

        if (d->lp)
            ptr = func_8001FF5C(d->lp, buff2, outCount, ptr);

        if (!d->rs)
            ptr = saveAudioRingBuffer(r, out_ptr, buff2, outCount, ptr);

        if (d->gain)
            aMix(ptr++, 0, (u16)d->gain, buff2, output);

        prev_out_ptr = &r->input[d->output];
    }

    r->input += outCount;
    if (r->input > &r->base[r->length])
        r->input -= r->length;

    aDMEMMove(ptr++, output, 0x6C0, outCount << 1);

    return ptr;
}
