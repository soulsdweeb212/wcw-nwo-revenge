#include "common.h"

typedef struct { u32 w0, w1; } Acmd;
typedef struct {
    s32 order;
    s32 npredictors;
    s16 book[1];
} ALADPCMBook;
typedef struct {
    void *loop;
    ALADPCMBook *book;
} ALADPCMWaveInfo;
typedef struct {
    u8 *base;
    s32 len;
    u8 type;
    u8 flags;
    union {
        ALADPCMWaveInfo adpcmWave;
    } waveInfo;
} ALWaveTable;
typedef struct {
    u32 start;
    u32 end;
    u32 count;
} ALRawLoop;
typedef struct {
    void *source;
    void *handler;
    void *setParam;
    s16 inp;
    s16 outp;
    s32 type;
} ALFilter;
typedef struct {
    ALFilter filter;
    ALRawLoop loop;
    ALWaveTable *table;
    s32 bookSize;
    void *dma;
    void *dmaState;
    s32 sample;
    s32 lastsam;
    s32 first;
    s32 memin;
} ALLoadFilter;

Acmd *buildAudioLoadBufferCommand(Acmd *ptr, ALLoadFilter *f, s32 tsam, s32 nbytes, s16 outp, s16 inp, u32 flags);

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define K0_TO_PHYS(x) ((u32)(x) & 0x1FFFFFFF)
#define aLoadADPCM(pkt, c, d) { Acmd *_a = (Acmd *)pkt; \
    _a->w0 = _SHIFTL(11, 24, 8) | _SHIFTL(c, 0, 24); _a->w1 = (u32)(d); }
#define aDMEMMove(pkt, i, o, c) { Acmd *_a = (Acmd *)pkt; \
    _a->w0 = _SHIFTL(10, 24, 8) | _SHIFTL(i, 0, 24); \
    _a->w1 = _SHIFTL(o, 16, 16) | _SHIFTL(c, 0, 16); }
#define aClearBuffer(pkt, d, c) { Acmd *_a = (Acmd *)pkt; \
    _a->w0 = _SHIFTL(2, 24, 8) | _SHIFTL(d, 0, 24); _a->w1 = (u32)(c); }
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define ADPCMFSIZE 16
#define ADPCMFBYTES 9
#define LFSAMPLES 4
#define A_LOOP 2

Acmd *func_80019070(void *filter, s16 *outp, s32 outCount, Acmd *p)
{
    Acmd *ptr = p;
    s16 inp;
    s32 tsam;
    s32 nframes;
    s32 nbytes;
    s32 overFlow;
    s32 startZero;
    s32 nOver;
    s32 nSam;
    s32 op;
    s32 nLeft;
    s32 bEnd;
    s32 decoded = 0;
    s32 looped = 0;

    ALLoadFilter *f = (ALLoadFilter *)filter;

    if (outCount == 0)
        return ptr;

    inp = 0;
    aLoadADPCM(ptr++, f->bookSize, K0_TO_PHYS(f->table->waveInfo.adpcmWave.book->book));

    looped = (outCount + f->sample > f->loop.end) && (f->loop.count != 0);
    if (looped)
        nSam = f->loop.end - f->sample;
    else
        nSam = outCount;

    if (f->lastsam)
        nLeft = ADPCMFSIZE - f->lastsam;
    else
        nLeft = 0;

    tsam = nSam - nLeft;
    if (tsam < 0) tsam = 0;

    nframes = (tsam + ADPCMFSIZE - 1) >> LFSAMPLES;
    nbytes = nframes * ADPCMFBYTES;

    if (looped) {
        ptr = buildAudioLoadBufferCommand(ptr, f, tsam, nbytes, *outp, inp, f->first);

        if (f->lastsam)
            *outp += (f->lastsam << 1);
        else
            *outp += (ADPCMFSIZE << 1);

        f->lastsam = f->loop.start & 0xf;
        f->memin = (s32)f->table->base + ADPCMFBYTES * ((s32)(f->loop.start >> LFSAMPLES) + 1);
        f->sample = f->loop.start;

        bEnd = *outp;
        while (outCount > nSam) {
            outCount -= nSam;
            op = (bEnd + ((nframes + 1) << (LFSAMPLES + 1)) + 16) & ~0x1f;
            bEnd += nSam << 1;

            if ((f->loop.count != -1) && (f->loop.count != 0))
                f->loop.count--;

            nSam = MIN(outCount, f->loop.end - f->loop.start);
            tsam = nSam - ADPCMFSIZE + f->lastsam;
            if (tsam < 0) tsam = 0;
            nframes = (tsam + ADPCMFSIZE - 1) >> LFSAMPLES;
            nbytes = nframes * ADPCMFBYTES;
            ptr = buildAudioLoadBufferCommand(ptr, f, tsam, nbytes, op, inp, f->first | A_LOOP);

            aDMEMMove(ptr++, op + (f->lastsam << 1), bEnd, nSam << 1);
        }

        f->lastsam = (outCount + f->lastsam) & 0xf;
        f->sample += outCount;
        f->memin += ADPCMFBYTES * nframes;
        return ptr;
    }

    nSam = nframes << LFSAMPLES;

    overFlow = f->memin + nbytes - ((s32)f->table->base + f->table->len);
    if (overFlow < 0)
        overFlow = 0;
    nOver = (overFlow / ADPCMFBYTES) << LFSAMPLES;
    if (nOver > nSam + nLeft)
        nOver = nSam + nLeft;

    nbytes -= overFlow;

    if ((nOver - (nOver & 0xf)) < outCount) {
        decoded = 1;
        ptr = buildAudioLoadBufferCommand(ptr, f, nSam - nOver, nbytes, *outp, inp, f->first);
        if (f->lastsam)
            *outp += (f->lastsam << 1);
        else
            *outp += (ADPCMFSIZE << 1);

        f->lastsam = (outCount + f->lastsam) & 0xf;
        f->sample += outCount;
        f->memin += ADPCMFBYTES * nframes;
    } else {
        f->lastsam = 0;
        f->memin += ADPCMFBYTES * nframes;
    }

    if (nOver) {
        f->lastsam = 0;
        if (decoded)
            startZero = (nLeft + nSam - nOver) << 1;
        else
            startZero = 0;
        aClearBuffer(ptr++, startZero + *outp, nOver << 1);
    }

    return ptr;
}
