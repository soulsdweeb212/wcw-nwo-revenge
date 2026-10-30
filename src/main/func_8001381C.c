/* @header
 * func_8001381C
 * VRAM 0x8001381C | ROM 0x1441C | size 0x178
 * asm: asm/nonmatchings/main/func_8001381C.s
 */
#include "common.h"

/*
 * Start playback for a sound request.  `notes[i]` == 0 means silent; every
 * active note gets a free audio voice (selectAudioVoiceSlot), which is reset
 * and loaded with the request's per-note values.  The parameter arrays are
 * copied per-voice only when they live below 0x400.  A fresh group id `base`
 * is assigned, handed to func_800142E8 and returned.
 */
typedef struct {
    u32 count;
    u32 *notes;
    u32 *values1;
    u32 *values2;
} Nw2SoundRequest;

typedef struct {
    u32 f0;
    s32 note;
    u8 pad8[0x40];
    s32 value2Start;
    s32 value2;
    u8 pad50[0x10];
    s32 group;
    u8 pad64[0x30];
    void *request;
    s32 f98;
    s32 noteStart;
    s32 fA0;
    s32 value1;
    s32 value1Start;
    u8 padAC[0xAC];
} Nw2Voice1381C;

extern Nw2Voice1381C *D_800604D0;
extern s32 D_800604E8;
void func_80015F2C(void *, void *, u32);
s32 selectAudioVoiceSlot(void *, s32);
void func_80015C18(void *);
void func_800142E8(s32);

s32 func_8001381C(Nw2SoundRequest *arg0) {
    u32 count;
    s32 prev;
    s32 base;
    s32 i;
    s32 val;
    u32 off;
    Nw2Voice1381C *voice;

    count = arg0->count;
    if ((u32)arg0->notes < 0x400) {
        func_80015F2C(&arg0->notes, arg0, 5);
        func_80015F2C(arg0->notes, arg0, count);
        func_80015F2C(arg0->values1, arg0, count);
        func_80015F2C(arg0->values2, arg0, count);
    }
    prev = D_800604E8;
    i = 0;
    D_800604E8 = prev + 1;
    base = prev;
    for (i = 0; (u32)i < count; i++) {
        if (arg0->notes[i] == 0) {
            continue;
        }
        off = selectAudioVoiceSlot(arg0, i) * 0x158;
        voice = (Nw2Voice1381C *)((u8 *)D_800604D0 + off);
        func_80015C18(voice);
        voice->request = arg0;
        voice->f0 = voice->f0 | 1;
        val = arg0->values1[i];
        voice->value1Start = val;
        voice->value2 = val;
        val = arg0->values2[i];
        voice->value1 = val;
        voice->value2Start = val;
        val = arg0->notes[i];
        voice->group = base;
        voice->noteStart = val;
        voice->note = val;
    }
    func_800142E8(base);
    return base;
}
