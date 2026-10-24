#include "common.h"

typedef struct { u32 w0, w1; } Acmd18;
typedef struct ALFilter18 {
    struct ALFilter18 *source;
    Acmd18 *(*handler)(void *, s16 *, s32, s32, Acmd18 *);
    void *setParam;
    s16 inp;
    s16 outp;
    s32 type;
} ALFilter18;
typedef struct {
    ALFilter18 filter;
    void *state;
    s16 pan;
    s16 volume;
    s16 cvolL;
    s16 cvolR;
    s16 dryamt;
    s16 wetamt;
    u16 lratl;
    s16 lratm;
    s16 ltgt;
    u16 rratl;
    s16 rratm;
    s16 rtgt;
    s32 delta;
    s32 segEnd;
    s32 first;
    void *ctrlList;
    void *ctrlTail;
    void *sources;
    s32 motion;
} ALEnvMixer18;

extern s16 D_800373F0[];
extern char D_8003B710[];
extern char D_8003B714[];
void func_8001CEE0(char *, char *, s32);
u32 func_8001CE80(void *);
s16 func_8001ED64(f64, f64, s32, u16 *);

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define aSetBuffer(pkt, f, i, o, c) { Acmd18 *_a = (Acmd18 *)pkt; \
    _a->w0 = (_SHIFTL(8, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(i, 0, 16)); \
    _a->w1 = _SHIFTL(o, 16, 16) | _SHIFTL(c, 0, 16); }
#define aSetVolume(pkt, f, v, t, r) { Acmd18 *_a = (Acmd18 *)pkt; \
    _a->w0 = (_SHIFTL(9, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(v, 0, 16)); \
    _a->w1 = _SHIFTL(t, 16, 16) | _SHIFTL(r, 0, 16); }
#define aEnvMixer(pkt, f, s) { Acmd18 *_a = (Acmd18 *)pkt; \
    _a->w0 = (_SHIFTL(3, 24, 8) | _SHIFTL(f, 16, 8)); \
    _a->w1 = (u32)(s); }

Acmd18 *func_8001E960(void *filter, s16 *inp, s16 *outp, s32 outCount, s32 sampleOffset, Acmd18 *p)
{
    Acmd18 *ptr = p;
    ALEnvMixer18 *e = (ALEnvMixer18 *)filter;
    ALFilter18 *source = e->filter.source;

    if (e->motion != 1 || !outCount)
        return ptr;

    if (!source)
        func_8001CEE0(D_8003B710, D_8003B714, 0x16F);

    ptr = (*source->handler)(source, inp, outCount, sampleOffset, p);

    aSetBuffer(ptr++, 0, *inp, 0x440 + *outp, outCount << 1);
    aSetBuffer(ptr++, 8, 0x580 + *outp, 0x6C0 + *outp, 0x800 + *outp);

    if (e->first) {
        e->first = 0;
        e->ltgt = (e->volume * D_800373F0[e->pan]) >> 15;
        e->lratm = func_8001ED64((f64)e->cvolL, (f64)e->ltgt, e->segEnd, &e->lratl);
        e->rtgt = (e->volume * D_800373F0[128 - e->pan - 1]) >> 15;
        e->rratm = func_8001ED64((f64)e->cvolR, (f64)e->rtgt, e->segEnd, &e->rratl);

        aSetVolume(ptr++, 6, e->cvolL, 0, 0);
        aSetVolume(ptr++, 4, e->cvolR, 0, 0);
        aSetVolume(ptr++, 2, e->ltgt, e->lratm, e->lratl);
        aSetVolume(ptr++, 0, e->rtgt, e->rratm, e->rratl);
        aSetVolume(ptr++, 8, e->dryamt, 0, e->wetamt);
        aEnvMixer(ptr++, 1 | 8, func_8001CE80(e->state));
    } else
        aEnvMixer(ptr++, 0 | 8, func_8001CE80(e->state));

    *inp += (outCount << 1);
    e->delta += outCount;

    return ptr;
}
