#include "common.h"

typedef struct {
    u8 pad0[4];
    s32 inUse;      /* @0x4: nonzero once the voice is playing */
    u8 pad8[0x5C];
    s32 priority;   /* @0x64 */
    u8 pad68[0x5E];
    u16 soundId;    /* @0xC6 */
    u8 padC8[0x90];
} SoundVoice;

extern u32 D_800604C8;      /* number of sound voices */
extern u8 *D_800604D0;      /* voice array base (stride sizeof(SoundVoice)) */
extern s32 *D_800604D8;     /* per-sound priority table */
extern void *D_800604F0;
extern void *D_800604F4;
s32 func_80015F64(void *, s32, s32, s32, s32);

/* Find a voice for sound arg1 and start it. If arg4 is set, first reuse a voice
 * already playing arg1; otherwise prefer a free voice, else the playing voice
 * with the lowest priority below the threshold. Remembers/restores the current
 * voice-owner global around the call. */
s32 func_80014140(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    SoundVoice *p;
    SoundVoice *best;
    s32 threshold;
    s32 min;
    u32 i;
    s32 result;

    if (arg0 != NULL && *(s32 *)((u8 *)arg0 + 0x10) < 0)
        D_800604F0 = arg0;

    threshold = arg5;
    if (threshold == -1)
        threshold = D_800604D8[arg1];

    if (arg4 != 0) {
        p = (SoundVoice *)D_800604D0;
        for (i = 0; i < D_800604C8; i++, p++) {
            if (p->soundId == arg1) {
                result = func_80015F64(p, arg1, arg2, arg3, threshold);
                goto done;
            }
        }
    }

    min = threshold + 1;
    p = (SoundVoice *)D_800604D0;
    for (i = 0; i < D_800604C8; i++, p++) {
        if (p->inUse == 0) {
            result = func_80015F64(p, arg1, arg2, arg3, threshold);
            goto done;
        }
        if (p->soundId != 0 && p->priority < min) {
            min = p->priority;
            best = p;
        }
    }
    if (min < threshold)
        result = func_80015F64(best, arg1, arg2, arg3, threshold);
    else
        result = 0;
done:
    D_800604F0 = D_800604F4;
    return result;
}
