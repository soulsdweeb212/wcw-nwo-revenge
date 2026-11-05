/* @header
 * __MusIntMain  (originally func_80014500)
 * VRAM 0x80014500 | ROM 0x15100 | size 0x38C
 * asm: asm/nonmatchings/main/__MusIntMain.s
 */
/* SDK: libmus, libmus/src/player.c (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

/* Per-frame audio voice update.
 * First drains the pending-event queue (__MusIntFifoProcessCommand) from fifo_start up to
 * fifo_current, wrapping at fifo_limit. Then for each of the max_channels voices
 * (0x158-byte records at mus_channels) it runs the envelope/lfo updates, advances
 * the voice time, handles note-off/release, decay and the pitch (__MusIntProcessVibrato)
 * / volume (__MusIntProcessWobble) modulations, and computes the elapsed time. Returns
 * the audio status word mus_next_frame_time. */
extern s32 fifo_start,fifo_current,fifo_limit,D_80060500,mus_next_frame_time;
extern u8 *fifo_addr,*mus_voices;
extern u32 max_channels;
extern u8 *mus_channels;
void __MusIntFifoProcessCommand(void *);void __MusIntFlushPending(void *,u32);void __MusIntGetNewNote(void *,u32);void __MusIntProcessContinuousVolume(void *);void __MusIntProcessContinuousPitchBend(void *);void n_alSynStopVoice(void *);void __MusIntProcessEnvelope(void *);void __MusIntProcessSweep(void *);f32 __MusIntProcessVibrato(void *);f32 __MusIntProcessWobble(void *);void __MusIntSetPitch(void *,u32,f32);void __MusIntSetVolumeAndPan(void *,u32);
#define A145(t,o) (*(t *)(p+(o)))
s32 __MusIntMain(void) {
    u8 *p;u32 i;f32 value;
    while(fifo_start!=fifo_current) {
        __MusIntFifoProcessCommand(fifo_addr+fifo_start*8);
        fifo_start++;
        if(fifo_start==fifo_limit) fifo_start=0;
    }
    p=mus_channels;
    for(i=0;i<max_channels;i++,p+=0x158) {
        if(!A145(s32,4) || (A145(s32,0)&1))continue;
        if(A145(s32,8))__MusIntFlushPending(p,i);
        A145(u64,0x10)+=A145(u16,0xBC);
        if(A145(u16,0xBA)!=0x7FFF) {
            while(A145(u64,0x10)>A145(u64,0x50)) {
                if(!A145(s32,4))goto next;
                __MusIntGetNewNote(p,i);
            }
            if(!A145(s32,4))continue;
        }
        if(A145(s32,0x4C) && A145(u64,0x10)>A145(u64,0x20))__MusIntProcessContinuousVolume(p);
        if(A145(s32,0x48) && A145(u64,0x10)>A145(u64,0x28))__MusIntProcessContinuousPitchBend(p);
        if(A145(s32,0x18)!=-1 && --A145(s32,0x18)==-1) {
            A145(s32,0x4C)=0;A145(s32,0x48)=0;A145(s32,0x94)=0;A145(s16,0xC6)=0;A145(s32,0x60)=0;A145(s32,8)=0;A145(s32,4)=0;
            if(A145(u8,0xE9)) {A145(u8,0xE9)=0;n_alSynStopVoice(mus_voices+i*0x1C);} else goto elapsed;
        }
        if(A145(u8,0xE9)) {
            if(A145(u8,0xE3))__MusIntProcessEnvelope(p);
            if(A145(u8,0xF4) && A145(u64,0x10)>A145(u64,0xB0))__MusIntProcessSweep(p);
            value=A145(f32,0x44);
            if(A145(u8,0xF5))value+=__MusIntProcessVibrato(p);
            if(A145(u8,0xEE))value+=__MusIntProcessWobble(p);
            if(!A145(s32,8)) {__MusIntSetPitch(p,i,value);__MusIntSetVolumeAndPan(p,i);}
        }
        elapsed:A145(u16,0xCA)=(A145(u64,0x10)-A145(u64,0x58))>>8;
        next:;
    }
    D_80060500=0;return mus_next_frame_time;
}
