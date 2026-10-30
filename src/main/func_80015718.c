/* @header
 * func_80015718
 * VRAM 0x80015718 | ROM 0x16318 | size 0x140
 * asm: asm/nonmatchings/main/func_80015718.s
 */
#include "common.h"

typedef struct {
    u8 pad00[0x10];
    u64 endTime;      /* @0x10: sequence end time (fixed point) */
    u8 pad18[0x10];
    u64 timeAccum;    /* @0x28: running time accumulator (steps by 0x100) */
    u8 pad30[0x8];
    f32 outFreq;      /* @0x38: output frequency */
    u8 pad3C[0xC];
    u8 *seq;          /* @0x48: sequence byte stream cursor */
    u8 pad4C[0x40];
    f32 baseFreq;     /* @0x8C: base frequency */
    f32 pitch;        /* @0x90: current pitch (note value - 64) */
    u8 pad94[0x30];
    u16 duration;     /* @0xC4: remaining ticks of the current note */
} SoundChannel;

/* Advance a sound/sequence channel by one tick: bump the fixed-point time, and
 * when the current note's duration expires, read the next event byte from the
 * sequence stream (a byte >= 0x80 introduces a detune/length command) and update
 * the channel pitch and output frequency. */
void func_80015718(void *arg0) {
    SoundChannel *ch = (SoundChannel *)arg0;
    u8 cmd;
    u16 dur;
    do {
        dur = ch->duration - 1;
        ch->timeAccum += 0x100;
        ch->duration = dur;
        if (!dur) {
            cmd = *ch->seq++;
            if (cmd >= 0x80) {
                f32 v = (f32)(cmd & 0x7F) - 64.0;
                ch->pitch = v;
                ch->outFreq = v * ch->baseFreq;
                cmd = *ch->seq++;
                if (cmd >= 0x80) {
                    ch->duration = (cmd & 0x7F) << 8;
                    ch->duration += *ch->seq++ + 2;
                } else {
                    ch->duration = cmd + 2;
                }
            } else {
                f32 v = (f32)cmd - 64.0;
                ch->duration = 1;
                ch->pitch = v;
                ch->outFreq = v * ch->baseFreq;
            }
        }
    } while (ch->timeAccum < ch->endTime);
}
