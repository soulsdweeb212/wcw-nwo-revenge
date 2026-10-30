/* @header
 * initializeAudioSystem  (originally func_8001348C)
 * VRAM 0x8001348C | ROM 0x1408C | size 0x364
 * asm: asm/nonmatchings/main/initializeAudioSystem.s
 */
#include "common.h"

extern s32 D_80000300,D_8007BD64,D_800604D4,D_800604D8,D_800604E0,D_800604E8,D_800604EC,D_800604FC;
extern volatile s32 D_800604DC;extern u32 D_800604C8;extern s32 D_800604B8,D_800604BC,D_800604A0;
extern u8 *D_800604CC,*D_800604D0,*D_800604F0,*D_800604F4;
extern void *D_800604A4;extern s32 (*D_800604A8)(void);s32 updateAudioVoices(void);
void func_80015ECC(void *,s32,s32);void func_80020270(void *,void *,s32);void *func_800202B0(s32,s32,void *,s32,s32);void func_8001439C(s32);void func_800159EC(void *,s32);void func_80016A30(s32,void *,s32,void *,s32,s32,s32);void func_800137F0(s32,s32);void func_80017590(void *);void func_80015C18(void *);void func_800175E0(void *,void *);
typedef struct {s16 id,value;s8 mode;u8 pad[3];} AudioVoiceDesc;
typedef struct {u32 voices,physical; s32 updates,unused,zero;void *heap;s32 zero2;s8 mode;u8 pad[11];} AudioConfig;
typedef struct {s32 f0;u32 f4;s32 f8,fC;void *f10;s32 f14;u8 *f18;s32 f1C,f20,f24,f28,f2C,f30,f34,f38,f3C,f40,f44;} AudioInitParams;

/* Brings up the audio system from an AudioInitParams block: sets the voice count
 * and mix rate (50/60 Hz by region, D_800604E0 = 1000000/rate), allocates the
 * per-voice command arrays (stride 0x1C) and voice records (stride 0x158) from a
 * heap arena, loads the optional sample bank (arg->f18), fills the AudioConfig
 * (2 outputs, the given voice count and update/panning settings) and starts the
 * mixer via func_80016A30; then installs the voice-update callback and clears all
 * voice records.  Returns the heap arena size used. */
s32 initializeAudioSystem(AudioInitParams *setup) {
 AudioVoiceDesc desc;AudioConfig config;s32 settings[4];u8 *sampleData;u32 i;s32 *voicePtr;
 D_8007BD64=setup->f0;D_800604C8=setup->f4;D_800604D4=setup->f20;D_800604D8=setup->f24;
 if(!D_80000300)D_800604DC=50;else D_800604DC=60;
 D_800604E0=1000000/D_800604DC;
 func_80015ECC(setup->f10,0,setup->f14);func_80020270(&D_800604B8,setup->f10,setup->f14);
 D_800604CC=func_800202B0(0,0,&D_800604B8,1,D_800604C8*0x1C);
 D_800604D0=func_800202B0(0,0,&D_800604B8,1,D_800604C8*0x158);
 func_8001439C(setup->f28);func_80015ECC(D_800604CC,0,D_800604C8*0x1C);func_80015ECC(D_800604D0,0,D_800604C8*0x158);
 if(setup->f18) {func_800159EC(setup->f18,setup->f1C);sampleData=setup->f18;D_800604F0=sampleData;D_800604F4=sampleData;} else D_800604F4=0;
 config.voices=D_800604C8;config.physical=D_800604C8;config.updates=setup->f30;config.mode=2;config.zero=0;config.zero2=0;config.heap=&D_800604B8;
 settings[0]=setup->f34;settings[1]=setup->f3C;settings[2]=setup->f38;
 D_800604FC=2;func_80016A30(setup->f8,&config,setup->fC,settings,setup->f40,setup->f44,D_800604DC);
 func_800137F0(3,0x7FFF);
 voicePtr=&D_800604A0;
 D_800604E8=1;D_800604EC=0x12345678;*voicePtr=0;D_800604A8=updateAudioVoices;D_800604A4=voicePtr;
 func_80017590(voicePtr);
 for(i=0;i<D_800604C8;i++) {D_800604D0[i*0x158+0xE9]=0;func_80015C18(D_800604D0+i*0x158);desc.mode=0;desc.id=setup->fC;desc.value=0;func_800175E0(D_800604CC+i*0x1C,&desc);}
 return D_800604BC-D_800604B8;
}
