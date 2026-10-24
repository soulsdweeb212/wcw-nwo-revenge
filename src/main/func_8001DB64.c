#include "common.h"

typedef struct { u32 w0, w1; } Acmd19;
typedef struct ALFilter19 {
    struct ALFilter19 *source;
    Acmd19 *(*handler)(void *, s16 *, s32, s32, Acmd19 *);
    void *setParam;
    s16 inp;
    s16 outp;
    s32 type;
} ALFilter19;
typedef struct { u8 *base; s32 len; } ALWaveTable19;
typedef struct { u32 start; u32 end; u32 count; } ALRawLoop19;
typedef s32 (*ALDMAproc19)(s32, s32, void *);
typedef struct {
    ALFilter19 filter;
    void *dc_state;
    void *dc_lstate;
    ALRawLoop19 lp;
    ALWaveTable19 *table;
    s32 bookSize;
    ALDMAproc19 dma;
    void *dmaState;
    s32 sample;
    s32 lastsam;
    s32 first;
    s32 memin;
} ALLoadFilter19;

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define aSetBuffer(pkt, f, i, o, c) { Acmd19 *_a = (Acmd19 *)pkt; \
    _a->w0 = (_SHIFTL(8, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(i, 0, 16)); \
    _a->w1 = _SHIFTL(o, 16, 16) | _SHIFTL(c, 0, 16); }
#define aLoadBuffer(pkt, s) { Acmd19 *_a = (Acmd19 *)pkt; \
    _a->w0 = _SHIFTL(4, 24, 8); _a->w1 = (u32)(s); }
#define aDMEMMove(pkt, i, o, c) { Acmd19 *_a = (Acmd19 *)pkt; \
    _a->w0 = _SHIFTL(0x0A, 24, 8) | _SHIFTL(i, 0, 24); \
    _a->w1 = _SHIFTL(o, 16, 16) | _SHIFTL(c, 0, 16); }
#define aClearBuffer(pkt, d, c) { Acmd19 *_a = (Acmd19 *)pkt; \
    _a->w0 = _SHIFTL(2, 24, 8) | _SHIFTL(d, 0, 24); _a->w1 = (u32)(c); }
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

Acmd19 *func_8001DB64(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd19 *p)
{
    Acmd19 *ptr = p;
    ALLoadFilter19 *f = (ALLoadFilter19 *)filter;
    s32 nbytes;
    s32 dramLoc;
    s32 dramAlign;
    s32 dmemAlign;
    s32 overFlow;
    s32 startZero;
    s32 nSam;
    s32 op;

    if (outCount == 0)
        return ptr;

    if ((f->lp.end < outCount + f->sample) && (f->lp.count)) {
        nSam = f->lp.end - f->sample;
        if (nSam > 0) {
            nbytes = nSam << 1;
            op = *outp;
            dramLoc = (f->dma)((s32)f->memin, nbytes, f->dmaState);
            dramAlign = dramLoc & 0x7;
            nbytes += dramAlign;
            aSetBuffer(ptr++, 0, *outp, 0, nbytes + 8 - (nbytes & 0x7));
            aLoadBuffer(ptr++, dramLoc - dramAlign);
        } else
            dramAlign = 0;

        *outp += dramAlign;

        f->memin = (s32)f->table->base + (f->lp.start << 1);
        f->sample = f->lp.start;
        op = *outp;

        while (outCount > nSam) {
            op += (nSam << 1);
            outCount -= nSam;
            if ((f->lp.count != -1) && (f->lp.count != 0))
                f->lp.count--;

            nSam = MIN(outCount, f->lp.end - f->lp.start);
            nbytes = nSam << 1;

            dramLoc = (f->dma)((s32)f->memin, nbytes, f->dmaState);
            dramAlign = dramLoc & 0x7;
            nbytes += dramAlign;
            if ((op & 0x7))
                dmemAlign = 8 - (op & 0x7);
            else
                dmemAlign = 0;

            aSetBuffer(ptr++, 0, op + dmemAlign, 0, nbytes + 8 - (nbytes & 0x7));
            aLoadBuffer(ptr++, dramLoc - dramAlign);

            if (dramAlign || dmemAlign) {
                aDMEMMove(ptr++, op + dramAlign + dmemAlign, op, nSam << 1);
            }
        }

        f->sample += outCount;
        f->memin += (outCount << 1);

        return ptr;
    }

    nbytes = outCount << 1;
    overFlow = f->memin + nbytes - ((s32)f->table->base + f->table->len);
    if (overFlow < 0)
        overFlow = 0;
    if (overFlow > nbytes)
        overFlow = nbytes;

    if (overFlow < nbytes) {
        if (outCount > 0) {
            nbytes -= overFlow;
            dramLoc = (f->dma)((s32)f->memin, nbytes, f->dmaState);
            dramAlign = dramLoc & 0x7;
            nbytes += dramAlign;
            aSetBuffer(ptr++, 0, *outp, 0, nbytes + 8 - (nbytes & 0x7));
            aLoadBuffer(ptr++, dramLoc - dramAlign);
        } else
            dramAlign = 0;
        *outp += dramAlign;
        f->sample += outCount;
        f->memin += outCount << 1;
    } else {
        f->memin += outCount << 1;
    }

    if (overFlow) {
        startZero = (outCount << 1) - overFlow;
        if (startZero < 0)
            startZero = 0;
        aClearBuffer(ptr++, startZero + *outp, overFlow);
    }

    return ptr;
}
