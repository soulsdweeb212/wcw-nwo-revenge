/* @header
 * updateAudioVoiceEnvelope  (originally func_80015118)
 * VRAM 0x80015118 | ROM 0x15D18 | size 0x350
 * asm: asm/nonmatchings/main/updateAudioVoiceEnvelope.s
 */
#include "common.h"

/* Steps an audio voice's ADSR-style envelope.  Voice byte +0xE3 is the stage
 * (0 idle, 1 attack, 2 ramp, 3 hold, 4 release), +0xE4 the current level, +0xE5 a
 * tick divider reloaded from +0xDF, and +0xED the level captured at release.  It
 * advances every +0xE5 ticks: attack ramps the level from +0xE0 by F(0x78)*elapsed
 * up to +0xE6, the next stage ramps from +0xE1 up to +0xE7, and release ramps the
 * level down from +0xED by F(0x80)*elapsed over +0xE8.  The u64 at +0x10 is the
 * current time, +0x58 the ramp start time and +0x70 the release time (in 1/256
 * units); W(0x84) scales elapsed ticks. */
void updateAudioVoiceEnvelope(void *voice) {
#define B(o) (*(u8 *)((u8 *)voice+(o)))
#define W(o) (*(s32 *)((u8 *)voice+(o)))
#define Q(o) (*(u64 *)((u8 *)voice+(o)))
#define F(o) (*(f32 *)((u8 *)voice+(o)))
 s32 step;
 if (Q(0x10)>=Q(0x70) && B(0xE3)<4) {B(0xE3)=4; B(0xE5)=1; B(0xED)=B(0xE4);}
 if (--B(0xE5)==0) {
 B(0xE5)=B(0xDF);
 switch(B(0xE3)) {
 case 1:
 step=(((Q(0x10)-Q(0x58))>>8)*W(0x84))>>10;
 if(step<B(0xE6)) B(0xE4)=B(0xE0)+(s32)(F(0x78)*step);
 else {B(0xE3)++; B(0xE4)=B(0xE1);} break;
 case 2:
 step=((((Q(0x10)-Q(0x58))>>8)-B(0xE6))*W(0x84))>>10;
 if(step<B(0xE7)) B(0xE4)=B(0xE1)+(s32)(F(0x7C)*step);
 else {B(0xE3)++; B(0xE4)=B(0xE2);} break;
 case 3: break;
 case 4:
 step=(((Q(0x10)-Q(0x70))>>8)*W(0x84))>>10;
 if(step<B(0xE8)) B(0xE4)=B(0xED)-(s32)(F(0x80)*step*B(0xED));
 else {B(0xE3)++; B(0xE4)=0;} break;
 }
 }
#undef B
#undef W
#undef Q
#undef F
}
