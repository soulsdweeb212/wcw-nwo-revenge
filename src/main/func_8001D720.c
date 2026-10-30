/* @header
 * func_8001D720
 * VRAM 0x8001D720 | ROM 0x1E320 | size 0x444
 * asm: asm/nonmatchings/main/func_8001D720.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } Acmd20;
typedef struct ALFilter20 {
    struct ALFilter20 *source;
    Acmd20 *(*handler)(void *, s16 *, s32, s32, Acmd20 *);
    void *setParam;
    s16 inp;
    s16 outp;
    s32 type;
} ALFilter20;
typedef struct { s32 order; s32 npredictors; s16 book[1]; } ALADPCMBook20;
typedef struct { void *loop; ALADPCMBook20 *book; } ALADPCMWaveInfo20;
typedef struct {
    u8 *base;
    s32 len;
    u8 type;
    u8 flags;
    union { ALADPCMWaveInfo20 adpcmWave; } waveInfo;
} ALWaveTable20;
typedef struct { u32 start; u32 end; u32 count; } ALRawLoop20;
typedef struct {
    ALFilter20 filter;
    void *state;
    void *lstate;
    ALRawLoop20 loop;
    ALWaveTable20 *table;
    s32 bookSize;
    void *dma;
    void *dmaState;
    s32 sample;
    s32 lastsam;
    s32 first;
    s32 memin;
} ALLoadFilter20;

Acmd20 *buildAudioLoadBufferCommands(Acmd20 *ptr, ALLoadFilter20 *f, s32 tsam, s32 nbytes, s16 outp, s16 inp, u32 flags);

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define aLoadADPCM(pkt, c, d) { Acmd20 *_a = (Acmd20 *)pkt; \
    _a->w0 = _SHIFTL(0x0B, 24, 8) | _SHIFTL(c, 0, 24); _a->w1 = (u32)(d); }
#define aDMEMMove(pkt, i, o, c) { Acmd20 *_a = (Acmd20 *)pkt; \
    _a->w0 = _SHIFTL(0x0A, 24, 8) | _SHIFTL(i, 0, 24); \
    _a->w1 = _SHIFTL(o, 16, 16) | _SHIFTL(c, 0, 16); }
#define aClearBuffer(pkt, d, c) { Acmd20 *_a = (Acmd20 *)pkt; \
    _a->w0 = _SHIFTL(2, 24, 8) | _SHIFTL(d, 0, 24); _a->w1 = (u32)(c); }
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define K0_TO_PHYS(x) ((u32)(x) & 0x1FFFFFFF)

Acmd20 *func_8001D720(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd20 *p)
{
    Acmd20 *ptr = p;
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
    ALLoadFilter20 *f = (ALLoadFilter20 *)filter;

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
        nLeft = 16 - f->lastsam;
    else
        nLeft = 0;
    tsam = nSam - nLeft;
    if (tsam < 0) tsam = 0;

    nframes = (tsam + 16 - 1) >> 4;
    nbytes = nframes * 9;

    if (looped) {
        ptr = buildAudioLoadBufferCommands(ptr, f, tsam, nbytes, *outp, inp, f->first);

        if (f->lastsam)
            *outp += (f->lastsam << 1);
        else
            *outp += (16 << 1);

        f->lastsam = f->loop.start & 0xf;
        f->memin = (s32)f->table->base + 9 * ((s32)(f->loop.start >> 4) + 1);
        f->sample = f->loop.start;

        bEnd = *outp;
        while (outCount > nSam) {
            outCount -= nSam;
            op = (bEnd + ((nframes + 1) << (4 + 1))) & ~0x1f;
            bEnd += nSam << 1;
            if ((f->loop.count != -1) && (f->loop.count != 0))
                f->loop.count--;
            nSam = MIN(outCount, f->loop.end - f->loop.start);
            tsam = nSam - 16 + f->lastsam;
            if (tsam < 0) tsam = 0;
            nframes = (tsam + 16 - 1) >> 4;
            nbytes = nframes * 9;
            ptr = buildAudioLoadBufferCommands(ptr, f, tsam, nbytes, op, inp, f->first | 2);
            aDMEMMove(ptr++, op + (f->lastsam << 1), bEnd, nSam << 1);
        }

        f->lastsam = (outCount + f->lastsam) & 0xf;
        f->sample += outCount;
        f->memin += 9 * nframes;
        return ptr;
    }

    nSam = nframes << 4;

    overFlow = f->memin + nbytes - ((s32)f->table->base + f->table->len);
    if (overFlow < 0)
        overFlow = 0;
    nOver = (overFlow / 9) << 4;
    if (nOver > nSam + nLeft)
        nOver = nSam + nLeft;

    nbytes -= overFlow;

    if ((nOver - (nOver & 0xf)) < outCount) {
        decoded = 1;
        ptr = buildAudioLoadBufferCommands(ptr, f, nSam - nOver, nbytes, *outp, inp, f->first);

        if (f->lastsam)
            *outp += (f->lastsam << 1);
        else
            *outp += (16 << 1);

        f->lastsam = (outCount + f->lastsam) & 0xf;
        f->sample += outCount;
        f->memin += 9 * nframes;
    } else {
        f->lastsam = 0;
        f->memin += 9 * nframes;
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
