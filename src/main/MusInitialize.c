/* @header
 * MusInitialize  (originally func_8001348C)
 * VRAM 0x8001348C | ROM 0x1408C | size 0x364
 * asm: asm/nonmatchings/main/MusInitialize.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

extern s32 osTvType,D_8007BD64,D_800604D4,D_800604D8,mus_next_frame_time,mus_current_handle,mus_random_seed,mus_last_fxtype;
extern volatile s32 mus_vsyncs_per_second;extern u32 max_channels;extern s32 D_800604B8,D_800604BC,D_800604A0;
extern u8 *mus_voices,*mus_channels,*mus_init_bank,*D_800604F4;
extern void *D_800604A4;extern s32 (*D_800604A8)(void);s32 __MusIntMain(void);
void __MusIntMemSet(void *,s32,s32);void alHeapInit(void *,void *,s32);void *alHeapDBAlloc(s32,s32,void *,s32,s32);void __MusIntFifoOpen(s32);void __MusIntRemapPtrBank(void *,s32);void amCreateAudioMgr(s32,void *,s32,void *,s32,s32,s32);void MusSetMasterVolume(s32,s32);void n_alSynAddPlayer(void *);void __MusIntInitialiseChannel(void *);void n_alSynAllocVoice(void *,void *);
typedef struct {s16 id,value;s8 mode;u8 pad[3];} AudioVoiceDesc;
typedef struct {u32 voices,physical; s32 updates,unused,zero;void *heap;s32 zero2;s8 mode;u8 pad[11];} AudioConfig;
typedef struct {s32 f0;u32 f4;s32 f8,fC;void *f10;s32 f14;u8 *f18;s32 f1C,f20,f24,f28,f2C,f30,f34,f38,f3C,f40,f44;} AudioInitParams;

/* Brings up the audio system from an AudioInitParams block: sets the voice count
 * and mix rate (50/60 Hz by region, mus_next_frame_time = 1000000/rate), allocates the
 * per-voice command arrays (stride 0x1C) and voice records (stride 0x158) from a
 * heap arena, loads the optional sample bank (arg->f18), fills the AudioConfig
 * (2 outputs, the given voice count and update/panning settings) and starts the
 * mixer via amCreateAudioMgr; then installs the voice-update callback and clears all
 * voice records.  Returns the heap arena size used. */
s32 MusInitialize(AudioInitParams *setup) {
    AudioVoiceDesc desc;AudioConfig config;s32 settings[4];u8 *sampleData;u32 i;s32 *voicePtr;
    D_8007BD64=setup->f0;max_channels=setup->f4;D_800604D4=setup->f20;D_800604D8=setup->f24;
    if(!osTvType)mus_vsyncs_per_second=50;else mus_vsyncs_per_second=60;
    mus_next_frame_time=1000000/mus_vsyncs_per_second;
    __MusIntMemSet(setup->f10,0,setup->f14);alHeapInit(&D_800604B8,setup->f10,setup->f14);
    mus_voices=alHeapDBAlloc(0,0,&D_800604B8,1,max_channels*0x1C);
    mus_channels=alHeapDBAlloc(0,0,&D_800604B8,1,max_channels*0x158);
    __MusIntFifoOpen(setup->f28);__MusIntMemSet(mus_voices,0,max_channels*0x1C);__MusIntMemSet(mus_channels,0,max_channels*0x158);
    if(setup->f18) {__MusIntRemapPtrBank(setup->f18,setup->f1C);sampleData=setup->f18;mus_init_bank=sampleData;D_800604F4=sampleData;} else D_800604F4=0;
    config.voices=max_channels;config.physical=max_channels;config.updates=setup->f30;config.mode=2;config.zero=0;config.zero2=0;config.heap=&D_800604B8;
    settings[0]=setup->f34;settings[1]=setup->f3C;settings[2]=setup->f38;
    mus_last_fxtype=2;amCreateAudioMgr(setup->f8,&config,setup->fC,settings,setup->f40,setup->f44,mus_vsyncs_per_second);
    MusSetMasterVolume(3,0x7FFF);
    voicePtr=&D_800604A0;
    mus_current_handle=1;mus_random_seed=0x12345678;*voicePtr=0;D_800604A8=__MusIntMain;D_800604A4=voicePtr;
    n_alSynAddPlayer(voicePtr);
    for(i=0;i<max_channels;i++) {mus_channels[i*0x158+0xE9]=0;__MusIntInitialiseChannel(mus_channels+i*0x158);desc.mode=0;desc.id=setup->fC;desc.value=0;n_alSynAllocVoice(mus_voices+i*0x1C,&desc);}
    return D_800604BC-D_800604B8;
}
