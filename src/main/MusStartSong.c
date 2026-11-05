/* @header
 * MusStartSong  (originally func_8001381C)
 * VRAM 0x8001381C | ROM 0x1441C | size 0x178
 * asm: asm/nonmatchings/main/MusStartSong.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

/*
 * Start playback for a sound request.  `notes[i]` == 0 means silent; every
 * active note gets a free audio voice (__MusIntFindChannel), which is reset
 * and loaded with the request's per-note values.  The parameter arrays are
 * copied per-voice only when they live below 0x400.  A fresh group id `base`
 * is assigned, handed to MusHandleUnPause and returned.
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

extern Nw2Voice1381C *mus_channels;
extern s32 mus_current_handle;
void __MusIntRemapPtrs(void *, void *, u32);
s32 __MusIntFindChannel(void *, s32);
void __MusIntInitialiseChannel(void *);
void MusHandleUnPause(s32);

s32 MusStartSong(Nw2SoundRequest *arg0) {
    u32 count;
    s32 prev;
    s32 base;
    s32 i;
    s32 val;
    u32 off;
    Nw2Voice1381C *voice;

    count = arg0->count;
    if ((u32)arg0->notes < 0x400) {
        __MusIntRemapPtrs(&arg0->notes, arg0, 5);
        __MusIntRemapPtrs(arg0->notes, arg0, count);
        __MusIntRemapPtrs(arg0->values1, arg0, count);
        __MusIntRemapPtrs(arg0->values2, arg0, count);
    }
    prev = mus_current_handle;
    i = 0;
    mus_current_handle = prev + 1;
    base = prev;
    for (i = 0; (u32)i < count; i++) {
        if (arg0->notes[i] == 0) {
            continue;
        }
        off = __MusIntFindChannel(arg0, i) * 0x158;
        voice = (Nw2Voice1381C *)((u8 *)mus_channels + off);
        __MusIntInitialiseChannel(voice);
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
    MusHandleUnPause(base);
    return base;
}
