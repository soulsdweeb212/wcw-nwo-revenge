#include "common.h"

typedef struct { u32 w0, w1; } Acmd;
typedef struct ALFilter {
    struct ALFilter *source;
    void *handler;
    void *setParam;
    s16 inp;
    s16 outp;
    s32 type;
} ALFilter;
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
} ALDelay;
typedef struct {
    ALFilter filter;
    s16 *base;
    s16 *input;
    u32 length;
    ALDelay *delay;
    u8 section_count;
} ALFx;

extern u8 *D_80036F54;
Acmd *func_800180A0(void);
Acmd *writeOscillatorSegment(ALFx *r, ALDelay *d, s32 buff, Acmd *p);
Acmd *func_8001A080(ALFx *r, s16 *curr_ptr, s32 buff, s32 count, Acmd *p);
Acmd *func_8001A1A8(ALFx *r, s16 *curr_ptr, s32 buff, Acmd *p);
Acmd *func_8001A2C0(void *lp, s32 buff, Acmd *p);

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define aMix(pkt, f, g, i, o) { Acmd *_a = (Acmd *)pkt; \
    _a->w0 = (_SHIFTL(0x0C, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(g, 0, 16)); \
    _a->w1 = _SHIFTL(i, 16, 16) | _SHIFTL(o, 0, 16); }
#define aClearBuffer(pkt, d, c) { Acmd *_a = (Acmd *)pkt; \
    _a->w0 = _SHIFTL(2, 24, 8) | _SHIFTL(d, 0, 24); _a->w1 = (u32)(c); }
#define aDMEMMove(pkt, i, o, c) { Acmd *_a = (Acmd *)pkt; \
    _a->w0 = _SHIFTL(0x0A, 24, 8) | _SHIFTL(i, 0, 24); \
    _a->w1 = _SHIFTL(o, 16, 16) | _SHIFTL(c, 0, 16); }
#define SWAP(in, out) { s16 t = out; out = in; in = t; }

#define FIXED_SAMPLE 0xB8

Acmd *func_80019970(void)
{
    Acmd *ptr;
    ALFx *r = *(ALFx **)(*(u8 **)(D_80036F54 + 0x34) + 0x20);
    s16 i, buff1, buff2, input, output;
    s16 *in_ptr, *out_ptr, *prev_out_ptr = 0;
    ALDelay *d;

    ptr = func_800180A0();

    input = 0x7C0;
    output = 0x930;
    buff1 = 0;
    buff2 = 0x170;

    aMix(ptr++, 0, 0xda83, 0x7C0, input);
    aMix(ptr++, 0, 0x5a82, 0x930, input);
    ptr = func_8001A1A8(r, r->input, input, ptr);

    aClearBuffer(ptr++, output, FIXED_SAMPLE << 1);

    for (i = 0; i < r->section_count; i++) {
        d = &r->delay[i];
        in_ptr = &r->input[-d->input];
        out_ptr = &r->input[-d->output];

        if (in_ptr == prev_out_ptr) {
            SWAP(buff1, buff2);
        } else {
            ptr = func_8001A080(r, in_ptr, buff1, FIXED_SAMPLE, ptr);
        }
        ptr = writeOscillatorSegment(r, d, buff2, ptr);

        if (d->ffcoef) {
            aMix(ptr++, 0, (u16)d->ffcoef, buff1, buff2);
            if (!d->rs && !d->lp) {
                ptr = func_8001A1A8(r, out_ptr, buff2, ptr);
            }
        }

        if (d->fbcoef) {
            aMix(ptr++, 0, (u16)d->fbcoef, buff2, buff1);
            ptr = func_8001A1A8(r, in_ptr, buff1, ptr);
        }

        if (d->lp)
            ptr = func_8001A2C0(d->lp, buff2, ptr);

        if (!d->rs)
            ptr = func_8001A1A8(r, out_ptr, buff2, ptr);

        if (d->gain)
            aMix(ptr++, 0, (u16)d->gain, buff2, output);

        prev_out_ptr = &r->input[d->output];
    }

    r->input += FIXED_SAMPLE;
    if (r->input > &r->base[r->length])
        r->input -= r->length;

    aDMEMMove(ptr++, output, 0x7C0, FIXED_SAMPLE << 1);

    return ptr;
}
