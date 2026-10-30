/* @header
 * writeOscillatorSegment  (originally func_80019E70)
 * VRAM 0x80019E70 | ROM 0x1AA70 | size 0x210
 * asm: asm/nonmatchings/main/func_80019E70.s
 */
#include "common.h"

/* Resample cursor: playback fraction and the DMA sample state. */
typedef struct {
    u8 pad[0x14];
    void *state;
    u8 pad18[8];
    f32 fraction;
    u32 flags;
} Nw2ResampleState;

/* A looping oscillator over a sample buffer. */
typedef struct {
    s32 loopStart, loopEnd;
    u8 pad8[16];
    s32 position;
    u8 pad1C[8];
    Nw2ResampleState *resample;
} Nw2Oscillator;

/* Sample data source. */
typedef struct {
    u8 pad[24];
    s32 base;
} Nw2SampleSource;

extern f64 D_8003B520;
void *func_8001A080(void *, s32, s32, s32, void *);
u32 func_8001CE80(void *);
f32 updateTriangleOscillator(f32 *, s32);

/* Emits the audio command(s) for one oscillator segment: advances the resample
 * fraction by the triangle-LFO-derived rate over 184 samples, aligns the source
 * address, and writes the ADPCM command word. Returns the updated cmd pointer. */
void *writeOscillatorSegment(Nw2SampleSource *src, Nw2Oscillator *osc, s32 envParam, void *cmd) {
    f32 rate, whole;
    s32 sampleCount = 184;
    s32 wholeSamples;
    s32 loopSpan, byteAddr, alignedOffset, alignWords;
    u16 pitchWord;
    u32 physAddr;
    s32 *cmdWords;
    if (osc->resample) {
        loopSpan = osc->loopEnd - osc->loopStart;
        rate = (f32)(D_8003B520 - (f64)((f32)(s32)(updateTriangleOscillator((f32 *)osc, 184) / (f32)loopSpan * 32768.0f) / 32768.0f));
        whole = osc->resample->fraction + rate * (f32)sampleCount;
        wholeSamples = (s32)whole;
        osc->resample->fraction = whole - (f32)wholeSamples;
        byteAddr = src->base + (osc->position - osc->loopEnd) * 2;
        alignWords = (byteAddr & 7) >> 1;
        alignedOffset = alignWords * 2;
        cmd = func_8001A080(src, byteAddr - alignedOffset, 0x2E0, wholeSamples + alignWords, cmd);
        pitchWord = (s32)(rate * 32768.0f) & 0xFFFF;
        physAddr = func_8001CE80(osc->resample->state);
        cmdWords = cmd;
        cmd = (u8 *)cmd + 8;
        cmdWords[0] = (physAddr & 0xFFFFFF) | 0x05000000;
        {
            s32 x = envParam >> 8;
            cmdWords[1] = (osc->resample->flags << 30) | (pitchWord << 14) | ((alignedOffset | 0x2E0) << 2) | (x & 3);
        }
        osc->resample->flags = 0;
        {
            s32 d = wholeSamples - 184;
            osc->position += d;
        }
    } else {
        cmd = func_8001A080(src, src->base - osc->loopEnd * 2, envParam, 184, cmd);
    }
    return cmd;
}
