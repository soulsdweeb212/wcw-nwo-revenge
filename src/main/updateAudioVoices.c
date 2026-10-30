/* @header
 * updateAudioVoices  (originally func_80014500)
 * VRAM 0x80014500 | ROM 0x15100 | size 0x38C
 * asm: asm/nonmatchings/main/updateAudioVoices.s
 */
#include "common.h"

/* Per-frame audio voice update.
 * First drains the pending-event queue (func_80014418) from D_80060504 up to
 * D_80060508, wrapping at D_8006050C. Then for each of the D_800604C8 voices
 * (0x158-byte records at D_800604D0) it runs the envelope/lfo updates, advances
 * the voice time, handles note-off/release, decay and the pitch (func_800155CC)
 * / volume (func_80015574) modulations, and computes the elapsed time. Returns
 * the audio status word D_800604E0. */
extern s32 D_80060504,D_80060508,D_8006050C,D_80060500,D_800604E0;
extern u8 *D_80060510,*D_800604CC;
extern u32 D_800604C8;
extern u8 *D_800604D0;
void func_80014418(void *);void func_80014D78(void *,u32);void func_8001488C(void *,u32);void func_80015628(void *);void func_80015718(void *);void func_80017AC0(void *);void updateAudioVoiceEnvelope(void *);void func_8001548C(void *);f32 func_800155CC(void *);f32 func_80015574(void *);void func_80014F5C(void *,u32,f32);void updateAudioVoiceVolume(void *,u32);
#define A145(t,o) (*(t *)(p+(o)))
s32 updateAudioVoices(void) {
 u8 *p;u32 i;f32 value;
 while(D_80060504!=D_80060508) {
 func_80014418(D_80060510+D_80060504*8);
 D_80060504++;
 if(D_80060504==D_8006050C) D_80060504=0;
 }
 p=D_800604D0;
 for(i=0;i<D_800604C8;i++,p+=0x158) {
 if(!A145(s32,4) || (A145(s32,0)&1))continue;
 if(A145(s32,8))func_80014D78(p,i);
 A145(u64,0x10)+=A145(u16,0xBC);
 if(A145(u16,0xBA)!=0x7FFF) {
 while(A145(u64,0x10)>A145(u64,0x50)) {
 if(!A145(s32,4))goto next;
 func_8001488C(p,i);
 }
 if(!A145(s32,4))continue;
 }
 if(A145(s32,0x4C) && A145(u64,0x10)>A145(u64,0x20))func_80015628(p);
 if(A145(s32,0x48) && A145(u64,0x10)>A145(u64,0x28))func_80015718(p);
 if(A145(s32,0x18)!=-1 && --A145(s32,0x18)==-1) {
 A145(s32,0x4C)=0;A145(s32,0x48)=0;A145(s32,0x94)=0;A145(s16,0xC6)=0;A145(s32,0x60)=0;A145(s32,8)=0;A145(s32,4)=0;
 if(A145(u8,0xE9)) {A145(u8,0xE9)=0;func_80017AC0(D_800604CC+i*0x1C);} else goto elapsed;
 }
 if(A145(u8,0xE9)) {
 if(A145(u8,0xE3))updateAudioVoiceEnvelope(p);
 if(A145(u8,0xF4) && A145(u64,0x10)>A145(u64,0xB0))func_8001548C(p);
 value=A145(f32,0x44);
 if(A145(u8,0xF5))value+=func_800155CC(p);
 if(A145(u8,0xEE))value+=func_80015574(p);
 if(!A145(s32,8)) {func_80014F5C(p,i,value);updateAudioVoiceVolume(p,i);}
 }
 elapsed:A145(u16,0xCA)=(A145(u64,0x10)-A145(u64,0x58))>>8;
 next:;
 }
 D_80060500=0;return D_800604E0;
}
